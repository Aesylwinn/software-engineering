#include "networkobject.h"

namespace base {
    NetworkObject::NetworkObject()
        : mPayloadType(PT_None)
    {
    }

    NetworkObject::NetworkObject(PayloadType type, QByteArray payload)
        : mPayloadType(type)
        , mPayload(payload)
    {
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

    NetworkObject NetworkObject::fromMessage(QString msg) {
        return NetworkObject(PT_Message, msg.toUtf8());
    }
}
