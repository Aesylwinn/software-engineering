#include "networkobject.h"

#include <QDataStream>

namespace base {
    const QDataStream::Version NetworkDataVersion = QDataStream::Qt_5_10;

    NetworkObject::NetworkObject()
        : mPayloadType(PT_None)
    {
    }

    NetworkObject::NetworkObject(PayloadType type, QByteArray payload)
        : mPayloadType(type)
        , mPayload(payload)
    {
    }

    NetworkObject::NetworkObject(const LoginRequest& request)
    {
        // Combine into a single object
        QByteArray payload;
        QDataStream stream(&payload, QIODevice::WriteOnly);
        stream.setVersion(NetworkDataVersion);
        stream << request.username << request.password;

        init(PT_LoginRequest, payload);
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

    QString NetworkObject::getMessage() {
        // Type check
        if (mPayloadType != PT_Message) {
            throw std::runtime_error("Payload is not a message!");
        }
        // Convert
        return QString(mPayload);
    }

    NetworkObject::LoginRequest NetworkObject::getLoginRequest() {
        // Type check
        if (mPayloadType != PT_LoginRequest) {
            throw std::runtime_error("Payload is not a login request!");
        }

        // Convert
        QByteArray data = getPayload();
        QDataStream stream(&data, QIODevice::ReadOnly);
        stream.setVersion(NetworkDataVersion);

        LoginRequest result;
        stream >> result.username >> result.password;
        return result;
    }

    NetworkObject NetworkObject::fromMessage(QString msg) {
        return NetworkObject(PT_Message, msg.toUtf8());
    }

    void NetworkObject::init(PayloadType type, QByteArray payload) {
        mPayloadType = type;
        mPayload = payload;
    }
}
