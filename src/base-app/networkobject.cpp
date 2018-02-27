#include "networkobject.h"

namespace base {
    const QDataStream::Version NetworkDataVersion = QDataStream::Qt_5_10;

    NetworkObject::NetworkObject()
    {
        init(PT_None, QByteArray());
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

    NetworkObject::PayloadType NetworkObject::getPayloadType() {
        return mPayloadType;
    }

    QByteArray NetworkObject::getPayload() {
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

    NetworkObject::Message NetworkObject::getMessage() {
        mustMatch(PT_Message);

        // Convert
        QDataStream stream;
        setupRead(stream);

        Message result;
        stream >> result.category >> result.message;
        return result;
    }

    NetworkObject::LoginRequest NetworkObject::getLoginRequest() {
        mustMatch(PT_LoginRequest);

        // Convert
        QDataStream stream;
        setupRead(stream);

        LoginRequest result;
        stream >> result.username >> result.password;
        return result;
    }

    void NetworkObject::init(PayloadType type, QByteArray payload) {
        mPayloadType = type;
        mPayload = payload;
        mBuffer.setBuffer(nullptr);
    }

    void NetworkObject::setupRead(QDataStream& stream) {
        // Set up stream for writing
        mBuffer.close();
        mBuffer.setBuffer(&mPayload);
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

    void NetworkObject::mustMatch(PayloadType type) {
        if (type != mPayloadType) {
            throw std::runtime_error("Payload type does not match");
        }
    }
}
