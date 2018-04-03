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


    NetworkObject::NetworkObject(const CreateAccountRequest& request) {
        init(PT_CreateAccountRequest, QByteArray());
        mTicket = -1;

        // Combine into a single object
        QDataStream stream;
        setupWrite(stream);
        stream << request.username << request.password;
        stream << request.email;
        stream << request.firstName << request.lastName;
        stream << request.gender;
        stream << request.birthDate;
    }

    NetworkObject::NetworkObject(const CreateEventRequest& input)
    {
        init(PT_CreateEventRequest, QByteArray());
        mTicket = -1;

        //Combine into single object
        QDataStream stream;
        setupWrite(stream);
        stream << input.data;
    }

    NetworkObject::NetworkObject(const SuggestEventsRequest& request) {
        init(PT_SuggestEventsRequest, QByteArray());
        mTicket = -1;

        QDataStream stream;
        setupWrite(stream);

        stream << request.count;
    }

    NetworkObject::NetworkObject(const CreateHostRequest& request) {
        init(PT_CreateHostRequest, QByteArray());
        mTicket = -1;

        QDataStream stream;
        setupWrite(stream);

        stream << request.username << request.password;
        stream << request.displayName;
        stream << request.businessName;
        stream << request.bio;
    }

    NetworkObject::NetworkObject(const JoinEventRequest& request) {
        init(PT_JoinEventRequest, QByteArray());
        mTicket = -1;

        QDataStream stream;
        setupWrite(stream);

        stream << request.eventId;
    }

    NetworkObject::NetworkObject(const RetrieveMyEventsRequest& request) {
        init(PT_RetrieveMyEventsRequest, QByteArray());
        mTicket = -1;

        QDataStream stream;
        setupWrite(stream);

        stream << request.count;
    }

    NetworkObject::NetworkObject(const LoginResponse& response)
    {
        init(PT_LoginResponse, QByteArray());
        mTicket = -1;

        // Combine into a single object
        QDataStream stream;
        setupWrite(stream);
        stream << response.valid << response.details << response.isHost;
    }

    NetworkObject::NetworkObject(const CreateAccountResponse& response) {
        init(PT_CreateAccountResponse, QByteArray());
        mTicket = -1;

        // Combine into a single object
        QDataStream stream;
        setupWrite(stream);
        stream << response.valid << response.details;
    }

    NetworkObject::NetworkObject(const CreateEventResponse& response) {
        init(PT_CreateEventResponse, QByteArray());
        mTicket = -1;

        // Combine
        QDataStream stream;
        setupWrite(stream);
        stream << response.valid << response.details;
    }

    NetworkObject::NetworkObject(const SuggestEventsResponse& response) {
        init(PT_SuggestEventsResponse, QByteArray());
        mTicket = -1;

        QDataStream stream;
        setupWrite(stream);
        stream << response.events;
    }

    NetworkObject::NetworkObject(const CreateHostResponse& response) {
        init(PT_CreateHostResponse, QByteArray());
        mTicket = -1;

        QDataStream stream;
        setupWrite(stream);
        stream << response.valid;
    }

    NetworkObject::NetworkObject(const JoinEventResponse& response) {
        init(PT_JointEventResponse, QByteArray());
        mTicket = -1;

        QDataStream stream;
        setupWrite(stream);

        stream << response.valid;
        stream << response.details;
    }

    NetworkObject::NetworkObject(const RetrieveMyEventsResponse& response) {
        init(PT_RetrieveMyEventsResponse, QByteArray());
        mTicket = -1;

        QDataStream stream;
        setupWrite(stream);

        stream << response.events;
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

        stream.commitTransaction();

        // Set values
        init((PayloadType) type, payload);
        setTicket(ticket);
        return true;
    }

    Message NetworkObject::getMessage() const {
        mustMatch(PT_Message);

        // Convert
        QDataStream stream;
        setupRead(stream);

        Message result;
        stream >> result.category >> result.message;
        return result;
    }

    LoginRequest NetworkObject::getLoginRequest() const {
        mustMatch(PT_LoginRequest);

        // Convert
        QDataStream stream;
        setupRead(stream);

        LoginRequest result;
        stream >> result.username >> result.password;
        return result;
    }

    CreateAccountRequest NetworkObject::getCreateAccountRequest() const {
        mustMatch(PT_CreateAccountRequest);

        // Convert
        QDataStream stream;
        setupRead(stream);

        CreateAccountRequest result;
        stream >> result.username >> result.password;
        stream >> result.email;
        stream >> result.firstName >> result.lastName;
        stream >> result.gender;
        stream >> result.birthDate;
        return result;
    }

    CreateEventRequest NetworkObject::getCreateEventRequest() const {
        mustMatch(PT_CreateEventRequest);

        // Convert
        QDataStream stream;
        setupRead(stream);

        CreateEventRequest result;
        stream >> result.data;
        return result;
    }

    SuggestEventsRequest NetworkObject::getSuggestEventsRequest() const {
        mustMatch(PT_SuggestEventsRequest);

        // Convert
        QDataStream stream;
        setupRead(stream);

        SuggestEventsRequest result;
        stream >> result.count;
        return result;
    }

    CreateHostRequest NetworkObject::getCreateHostRequest() const {
        mustMatch(PT_CreateHostRequest);

        // Convert
        QDataStream stream;
        setupRead(stream);

        CreateHostRequest result;
        stream >> result.username >> result.password;
        stream >> result.displayName;
        stream >> result.businessName;
        stream >> result.bio;

        return result;
    }

    JoinEventRequest NetworkObject::getJoinEventRequest() const {
        mustMatch(PT_JoinEventRequest);

        // Convert
        QDataStream stream;
        setupRead(stream);

        JoinEventRequest result;
        stream >> result.eventId;

        return result;
    }

    RetrieveMyEventsRequest NetworkObject::getRetrieveMyEventsRequest() const {
        mustMatch(PT_RetrieveMyEventsRequest);

        // Convert
        QDataStream stream;
        setupRead(stream);

        RetrieveMyEventsRequest result;
        stream >> result.count;

        return result;
    }

    LoginResponse NetworkObject::getLoginResponse() const {
        mustMatch(PT_LoginResponse);

        // Convert
        QDataStream stream;
        setupRead(stream);

        LoginResponse result;
        stream >> result.valid >> result.details >> result.isHost;
        return result;
    }

    CreateAccountResponse NetworkObject::getCreateAccountResponse() const {
        mustMatch(PT_CreateAccountResponse);

        // Convert
        QDataStream stream;
        setupRead(stream);

        CreateAccountResponse result;
        stream >> result.valid >> result.details;
        return result;
    }

    CreateEventResponse NetworkObject::getCreateEventResponse() const {
        mustMatch(PT_CreateEventResponse);

        // Convert
        QDataStream stream;
        setupRead(stream);

        CreateEventResponse result;
        stream >> result.valid >> result.details;
        return result;
    }

    SuggestEventsResponse NetworkObject::getSuggestEventsResponse() const {
        mustMatch(PT_SuggestEventsResponse);

        // Convert
        QDataStream stream;
        setupRead(stream);

        SuggestEventsResponse result;
        stream >> result.events;
        return result;
    }

    CreateHostResponse NetworkObject::getCreateHostResponse() const {
        mustMatch(PT_CreateHostResponse);

        // Convert
        QDataStream stream;
        setupRead(stream);

        CreateHostResponse result;
        stream >> result.valid;

        return result;
    }

    JoinEventResponse NetworkObject::getJoinEventResponse() const {
        mustMatch(PT_JointEventResponse);

        // Convert
        QDataStream stream;
        setupRead(stream);

        JoinEventResponse result;
        stream >> result.valid;
        stream >> result.details;

        return result;
    }

    RetrieveMyEventsResponse NetworkObject::getRetrieveMyEventsResponse() const {
        mustMatch(PT_RetrieveMyEventsResponse);

        // Convert
        QDataStream stream;
        setupRead(stream);

        RetrieveMyEventsResponse result;
        stream >> result.events;

        return result;
    }

    NetworkObject NetworkObject::createResponse(const LoginResponse& data) {
        mustMatch(PT_LoginRequest);

        // Construct response and match the ticket
        NetworkObject response(data);
        response.setTicket(getTicket());
        return response;
    }

    NetworkObject NetworkObject::createResponse(const CreateAccountResponse& data) {
        mustMatch(PT_CreateAccountRequest);

        // Construct response and match the ticket
        NetworkObject response(data);
        response.setTicket(getTicket());
        return response;
    }

    NetworkObject NetworkObject::createResponse(const CreateEventResponse& data) {
        mustMatch(PT_CreateEventRequest);

        // Construct response
        NetworkObject response(data);
        response.setTicket(getTicket());
        return response;
    }

    NetworkObject NetworkObject::createResponse(const SuggestEventsResponse& data) {
        mustMatch(PT_SuggestEventsRequest);

        // Construct response and match the ticket
        NetworkObject response(data);
        response.setTicket(getTicket());
        return response;
    }

    NetworkObject NetworkObject::createResponse(const CreateHostResponse& data) {
        mustMatch(PT_CreateHostRequest);

        // Construct response
        NetworkObject response(data);
        response.setTicket(getTicket());
        return response;
    }

    NetworkObject NetworkObject::createResponse(const JoinEventResponse& data) {
        mustMatch(PT_JoinEventRequest);

        // Construct response
        NetworkObject response(data);
        response.setTicket(getTicket());
        return response;
    }

    NetworkObject NetworkObject::createResponse(const RetrieveMyEventsResponse& data) {
        mustMatch(PT_RetrieveMyEventsRequest);

        // Construct response
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
            QString msg = "Payload type does not match { ";
            msg += "Expected: " + QVariant(type).toString() + " ";
            msg += "Actual: " + QVariant(mPayloadType).toString() + " }";
            throw std::runtime_error(qUtf8Printable(msg));
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
