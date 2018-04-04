#ifndef BASE_NETWORKOBJECT_H
#define BASE_NETWORKOBJECT_H

#include <QByteArray>
#include <QBuffer>
#include <QDataStream>
#include <QIODevice>
#include <QString>

#include "base-app_global.h"
#include "event.h"
#include "networkpackets.h"

namespace base {
    /* Implemented by Kyle and Anthony */
    class BASEAPPSHARED_EXPORT NetworkObject {
    public:

        // Default ctor, PT_None
        NetworkObject();

        // Copy ctor
        NetworkObject(const NetworkObject& other);

        // Parameterized ctor, only use this if you know what you are doing
        NetworkObject(PayloadType type, QByteArray payload);

        template <typename Request>
        explicit NetworkObject(const Request& request)  {
            init((PayloadType)Request::Type);

            // Combine into a single object
            QDataStream stream;
            setupWrite(stream);

            stream << request;
        }

        // Type and raw data retrieval
        PayloadType getPayloadType() const;
        QByteArray getPayload() const;

        // Enables response tracking
        qint32 getTicket() const;

        // Type and data setting
        void setPayload(PayloadType type, QByteArray payload);
        void setTicket(qint32 ticket);

        // Writes to any IO device including sockets!
        void write(QIODevice* device) const;

        // Reads the IO device in a nonblocking manner.
        bool tryRead(QIODevice* device);

        template <typename Packet>
        Packet convert() const {
            mustMatch((PayloadType)Packet::Type);

            // Convert
            QDataStream stream;
            setupRead(stream);

            Packet result;
            stream >> result;
            return result;
        }

        template <typename Response>
        NetworkObject createResponse(const Response& response) {
            mustMatch((PayloadType)Response::RequestType);

            // Construct response and match the ticket
            NetworkObject obj(response);
            obj.setTicket(getTicket());
            return obj;
        }

    private:

        // Ctor helper function
        void init(PayloadType type, QByteArray payload=QByteArray());

        // Buffer setup helper functions
        void setupRead(QDataStream& stream) const;
        void setupWrite(QDataStream& stream);

        // Conversion helper function
        void mustMatch(PayloadType type) const;

        // Device writing helper function
        void writeBlocking(QIODevice* device, const char* data, qint64 size) const;

        bool isInvalidSocket(QIODevice* device) const;

        PayloadType mPayloadType;
        QByteArray mPayload;
        qint32 mTicket;

        mutable QBuffer mBuffer;
    };
}

#endif
