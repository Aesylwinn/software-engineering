#include "networkobject.h"

#include <QAbstractSocket>

namespace base {
    const QDataStream::Version NetworkDataVersion = QDataStream::Qt_5_10;

    NetworkObject::NetworkObject()
    {
        init(PT_None, QByteArray());
        mTicket = -1;
    }

    NetworkObject::NetworkObject(const NetworkObject& other) {
        init(other.mPayloadType, other.mPayload);
        mTicket = other.mTicket;
    }

    NetworkObject::NetworkObject(PayloadType type, QByteArray payload)
    {
        init(type, payload);
        mTicket = -1;
    }

    NetworkObject::NetworkObject(const Message& message) {
        init(PT_Message, QByteArray());
        mTicket = -1;

        // Combine into a single object
        QDataStream stream;
        setupWrite(stream);
        stream << message.category << message.message;
    }

    NetworkObject::NetworkObject(const LoginRequest& request)
    {
        init(PT_LoginRequest, QByteArray());
        mTicket = -1;

        // Combine into a single object
        QDataStream stream;
        setupWrite(stream);
        stream << request.username << request.password;
    }

    NetworkObject::NetworkObject(const LoginResponse& response)
    {
        init(PT_LoginResponse, QByteArray());
        mTicket = -1;

        // Combine into a single object
        QDataStream stream;
        setupWrite(stream);
        stream << response.valid << response.details;
    }

    NetworkObject::PayloadType NetworkObject::getPayloadType() const {
        return mPayloadType;
    }

    QByteArray NetworkObject::getPayload() const {
        // Check for valid type
        if (mPayloadType == PT_None) {
            throw std::runtime_error("Payload type is none!");
        }
        return mPayload;
    }

    qint32 NetworkObject::getTicket() const {
        return mTicket;
    }

    void NetworkObject::setPayload(PayloadType type, QByteArray payload) {
        mPayloadType = type;
        mPayload = payload;
    }

    void NetworkObject::setTicket(qint32 ticket) {
        mTicket = ticket;
    }

    void NetworkObject::write(QIODevice* device) const {
        if (!(device->openMode() & QIODevice::WriteOnly))
            return;

        if (isInvalidSocket(device))
            return;

        // Data to write, must use platform independant types
        quint32 type = getPayloadType();
        QByteArray payload = getPayload();
        qint64 size = payload.size();
        qint32 ticket = getTicket();

        // Write all of the data
        writeBlocking(device, (const char*) &ticket, sizeof(ticket));
        writeBlocking(device, (const char*) &type, sizeof(type));
        writeBlocking(device, (const char*) &size, sizeof(size));
        writeBlocking(device, payload.data(), payload.size());
    }

    bool NetworkObject::tryRead(QIODevice* device) {
        if (!(device->openMode() & QIODevice::ReadOnly))
            return false;

        if (isInvalidSocket(device))
            return false;

        // Data
        qint32 ticket = -1;
        quint32 type = -1;
        qint64 size = -1;
        QByteArray payload;

        // Check that the full header is available
        qint64 headerSize = sizeof(ticket) + sizeof(type) + sizeof(size);
        if (device->bytesAvailable() < headerSize)
            return false;

        // Set up to rollback if not all the data is available
        QDataStream stream(device);
        stream.startTransaction();

        // Read the header
        stream.readRawData((char*) &ticket, sizeof(ticket));
        stream.readRawData((char*) &type, sizeof(type));
        stream.readRawData((char*) &size, sizeof(size));

        // Copy the data
        payload.resize(size);
        if (stream.readRawData(payload.data(), size) < size) {
            // Rollback, missing data
            stream.rollbackTransaction();
            return false;
        }

        // Set values
        init((PayloadType) type, payload);
        setTicket(ticket);
        return true;
    }

    NetworkObject::Message NetworkObject::getMessage() const {
        mustMatch(PT_Message);

        // Convert
        QDataStream stream;
        setupRead(stream);

        Message result;
        stream >> result.category >> result.message;
        return result;
    }

    NetworkObject::LoginRequest NetworkObject::getLoginRequest() const {
        mustMatch(PT_LoginRequest);

        // Convert
        QDataStream stream;
        setupRead(stream);

        LoginRequest result;
        stream >> result.username >> result.password;
        return result;
    }

    NetworkObject::LoginResponse NetworkObject::getLoginResponse() const {
        mustMatch(PT_LoginResponse);

        // Convert
        QDataStream stream;
        setupRead(stream);

        LoginResponse result;
        stream >> result.valid >> result.details;
        return result;
    }

    NetworkObject NetworkObject::createResponse(const LoginResponse& data) {
            mustMatch(PT_LoginRequest);

            // Construct response and match the ticket
            NetworkObject response(data);
            response.setTicket(getTicket());
            return response;
    }

    void NetworkObject::init(PayloadType type, QByteArray payload) {
        mPayloadType = type;
        mPayload = payload;
        mBuffer.setBuffer(nullptr);
    }

    void NetworkObject::setupRead(QDataStream& stream) const {
        // Set up stream for writing
        mBuffer.close();
        // We are reading, so this const_cast will not effect anything.
        // The cast is required because of Qt's api.
        mBuffer.setBuffer(const_cast<QByteArray*>(&mPayload));
        mBuffer.open(QIODevice::ReadOnly);
        // Attach stream to buffer
        stream.setDevice(&mBuffer);
        stream.setVersion(NetworkDataVersion);
    }

    void NetworkObject::setupWrite(QDataStream& stream) {
        // Set up buffer for writing
        mBuffer.close();
        mBuffer.setBuffer(&mPayload);
        mBuffer.open(QIODevice::WriteOnly);
        // Attach stream to buffer
        stream.setDevice(&mBuffer);
        stream.setVersion(NetworkDataVersion);
    }

    void NetworkObject::mustMatch(PayloadType type) const {
        if (type != mPayloadType) {
            throw std::runtime_error("Payload type does not match");
        }
    }

    void NetworkObject::writeBlocking(QIODevice* device, const char* data,
            qint64 size) const {
        qint64 written = 0;
        while (written < size) {
            // Try to write what remains
            written += device->write(&data[written], size-written);
            // Filled up buffer, must wait for space
            if (written < size) {
                device->waitForBytesWritten(-1);
            }
        }
    }

    bool NetworkObject::isInvalidSocket(QIODevice* device) const {
        auto socket = dynamic_cast<QAbstractSocket*>(device);
        if (socket && socket->state() != QAbstractSocket::ConnectedState)
            return true;
        else
            return false;
    }
}
