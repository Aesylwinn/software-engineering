#include "networkobject.h"

namespace base {
    const QDataStream::Version NetworkDataVersion = QDataStream::Qt_5_10;

    NetworkObject::NetworkObject()
    {
        init(PT_None, QByteArray());
    }

    NetworkObject::NetworkObject(const NetworkObject& other) {
        init(other.mPayloadType, other.mPayload);
    }

    NetworkObject::NetworkObject(PayloadType type, QByteArray payload)
    {
        init(type, payload);
    }

    NetworkObject::NetworkObject(const Message& message) {
        init(PT_Message, QByteArray());

        // Combine into a single object
        QDataStream stream;
        setupWrite(stream);
        stream << message.category << message.message;
    }

    NetworkObject::NetworkObject(const LoginRequest& request)
    {
        init(PT_LoginRequest, QByteArray());

        // Combine into a single object
        QDataStream stream;
        setupWrite(stream);
        stream << request.username << request.password;
    }

    NetworkObject::NetworkObject(const LoginResponse& response)
    {
        init(PT_LoginResponse, QByteArray());

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

    void NetworkObject::setPayload(PayloadType type, QByteArray payload) {
        mPayloadType = type;
        mPayload = payload;
    }

    void NetworkObject::write(QIODevice* device) const {
        // Data to write, must use platform independant types
        quint32 type = getPayloadType();
        QByteArray payload = getPayload();
        qint64 size = payload.size();

        // Write all of the data
        writeBlocking(device, (const char*) &type, sizeof(type));
        writeBlocking(device, (const char*) &size, sizeof(size));
        writeBlocking(device, payload.data(), payload.size());
    }

    bool NetworkObject::tryRead(QIODevice* device) {
        // Data
        quint32 type = -1;
        qint64 size = -1;
        QByteArray payload;

        // Check that the full header is available
        if (device->bytesAvailable() < sizeof(quint32) + sizeof(qint64))
            return false;

        // Set up to rollback if not all the data is available
        QDataStream stream(device);
        stream.startTransaction();

        // Read the header
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
}
