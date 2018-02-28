#ifndef BASE_NETWORKOBJECT_H
#define BASE_NETWORKOBJECT_H

#include <QByteArray>
#include <QBuffer>
#include <QDataStream>
#include <QString>

#include "base-app_global.h"

namespace base {
    /* Implemented by Kyle and Anthony */
    class BASEAPPSHARED_EXPORT NetworkObject {
    public:
        // The types of payloads
        enum PayloadType {
            PT_None,
            PT_LoginRequest,
            PT_Message
        };

        struct Message {
            QString category;
            QString message;
        };

        struct LoginRequest {
            QString username;
            QString password;
        };

        // Default ctor, PT_None
        NetworkObject();
        // Parameterized ctor
        NetworkObject(PayloadType type, QByteArray payload);
        // Message ctor
        NetworkObject(const Message& message);
        // Login request ctor
        NetworkObject(const LoginRequest& request);

        // Type and raw data retrieval
        PayloadType getPayloadType();
        QByteArray getPayload();

        // Type and data setting
        void setPayload(PayloadType type, QByteArray payload);

        // Converts payload to a message
        Message getMessage();

        // Converts payload to a login request
        LoginRequest getLoginRequest();

    private:

        void init(PayloadType type, QByteArray payload);

        void setupRead(QDataStream& stream);
        void setupWrite(QDataStream& stream);

        void mustMatch(PayloadType type);

        PayloadType mPayloadType;
        QByteArray mPayload;

        QBuffer mBuffer;
    };
}

#endif
