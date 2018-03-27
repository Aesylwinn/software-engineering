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
        // The types of payloads
        enum PayloadType {
            PT_None=0,

            PT_CreateAccountRequest=0x1,
            PT_LoginRequest,
            PT_CreateEventRequest,
            PT_SuggestEventsRequest,

            PT_CreateAccountResponse=0x200,
            PT_LoginResponse,
            PT_CreateEventResponse,
            PT_SuggestEventsResponse,

            PT_Message=0x400
        };


        // Default ctor, PT_None
        NetworkObject();

        // Copy ctor
        NetworkObject(const NetworkObject& other);

        // Parameterized ctor
        NetworkObject(PayloadType type, QByteArray payload);

        // Message ctor
        NetworkObject(const Message& message);

        // Create account request
        NetworkObject(const CreateAccountRequest& request);

        // Login request ctor
        NetworkObject(const LoginRequest& request);

        // Event request ctor
        NetworkObject(const CreateEventRequest& request);

        // Suggest events request ctor
        NetworkObject(const SuggestEventsRequest& request);


        // Type and raw data retrieval
        PayloadType getPayloadType() const;
        QByteArray getPayload() const;
        // Response tracking
        qint32 getTicket() const;

        // Type and data setting
        void setPayload(PayloadType type, QByteArray payload);
        void setTicket(qint32 ticket);


        // Writes to any IO device including sockets!
        void write(QIODevice* device) const;

        // Reads the IO device in a nonblocking manner.
        bool tryRead(QIODevice* device);


        // Converts payload to a message
        Message getMessage() const;

        // Converts payload to a login request
        LoginRequest getLoginRequest() const;

        // Converts payload to a create account request
        CreateAccountRequest getCreateAccountRequest() const;

        // Converts a payload to a create event request
        CreateEventRequest getCreateEventRequest() const;

        // Converts a payload to a create event request
        SuggestEventsRequest getSuggestEventsRequest() const;


        // Converts payload to a login response
        LoginResponse getLoginResponse() const;

        // Converts payload to a create account response
        CreateAccountResponse getCreateAccountResponse() const;

        // Converts payload to a suggest events response
        SuggestEventsResponse getSuggestEventsResponse() const;


        // Creates a response to a LoginRequest
        NetworkObject createResponse(const LoginResponse& data);

        // Creates a response to a CreateAccountRequest
        NetworkObject createResponse(const CreateAccountResponse& data);

        // Creates a response to a SuggestEventsRequest
        NetworkObject createResponse(const SuggestEventsResponse& data);

    private:

        // Login response ctor
        NetworkObject(const LoginResponse& response);

        // CreateAccount response ctor
        NetworkObject(const CreateAccountResponse& response);

        // SuggestEvents response ctor
        NetworkObject(const SuggestEventsResponse& response);

        // Ctor helper function
        void init(PayloadType type, QByteArray payload);

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
