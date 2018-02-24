#ifndef BASE_NETWORKOBJECT_H
#define BASE_NETWORKOBJECT_H

#include <QByteArray>
#include <QString>

namespace base {
    /* Implemented by Kyle and Anthony */
    class NetworkObject {
    public:
        // The types of payloads
        enum PayloadType {
            PT_None,
            PT_Message
        };

        // Default ctor, PT_None
        NetworkObject();
        // Parameterized ctor
        NetworkObject(PayloadType type, QByteArray payload);

        // Type and raw data retrieval
        PayloadType getPayloadType();
        QByteArray getPayload();

        // Type and data setting
        void setPayload(PayloadType type, QByteArray payload);

        // Converts payload to a message
        QString getMessage();

        // Static creators
        static NetworkObject fromMessage(QString msg);
    private:
        PayloadType mPayloadType;
        QByteArray mPayload;
    };
}

#endif
