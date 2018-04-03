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
            PT_CreateHostRequest,
            PT_JoinEventRequest,
            PT_RetrieveMyEventsRequest,

            PT_CreateAccountResponse=0x200,
            PT_LoginResponse,
            PT_CreateEventResponse,
            PT_SuggestEventsResponse,
            PT_CreateHostResponse,
            PT_JoinEventResponse,
            PT_RetrieveMyEventsResponse,

            PT_Message=0x400
        };


        // Default ctor, PT_None
        NetworkObject();

        // Copy ctor
        NetworkObject(const NetworkObject& other);

        // Parameterized ctor, only use this if you know what you are doing
        NetworkObject(PayloadType type, QByteArray payload);

        // Message packet ctor
        NetworkObject(const Message& message);

        // CreateAccountRequest packet ctor
        NetworkObject(const CreateAccountRequest& request);

        // LoginRequest packet ctor
        NetworkObject(const LoginRequest& request);

        // CreateEventRequest packet ctor
        NetworkObject(const CreateEventRequest& request);

        // SuggestEventsRequest packet ctor
        NetworkObject(const SuggestEventsRequest& request);

        // CreateHostRequest packet ctor
        NetworkObject(const CreateHostRequest& request);

        // JoinEventRequest packet ctor
        NetworkObject(const JoinEventRequest& request);

        // RetrieveMyEventsRequest packet ctor
        NetworkObject(const RetrieveMyEventsRequest& request);


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


        // Converts payload to a Message packet
        Message getMessage() const;

        // Converts payload to a LoginRequest packet
        LoginRequest getLoginRequest() const;

        // Converts payload to a CreateAccountRequest packet
        CreateAccountRequest getCreateAccountRequest() const;

        // Converts a payload to a CreateEventRequest packet
        CreateEventRequest getCreateEventRequest() const;

        // Converts a payload to a SuggestEventsRequest packet
        SuggestEventsRequest getSuggestEventsRequest() const;

        // Converts a payload to a CreateHostRequest packet
        CreateHostRequest getCreateHostRequest() const;

        // Converts a payload to a JoinEventRequest packet
        JoinEventRequest getJoinEventRequest() const;

        // Converts a payload to a RetrieveMyEventsRequest packet
        RetrieveMyEventsRequest getRetrieveMyEventsRequest() const;


        // Converts payload to a LoginResponse packet
        LoginResponse getLoginResponse() const;

        // Converts payload to a CreateAccountResponse packet
        CreateAccountResponse getCreateAccountResponse() const;

        // Converts payload to a CreateEventResponse packet
        CreateEventResponse getCreateEventResponse() const;

        // Converts payload to a SuggestEventsResponse packet
        SuggestEventsResponse getSuggestEventsResponse() const;

        // Converts payload to a CreateHostResponse packet
        CreateHostResponse getCreateHostResponse() const;

        // Converts payload to a JoinEventResponse packet
        JoinEventResponse getJoinEventResponse() const;

        // Converts payload to a RetrieveMyEventsResponse packet
        RetrieveMyEventsResponse getRetrieveMyEventsResponse() const;


        // Creates a NetworkObject containing a LoginResponse packet
        NetworkObject createResponse(const LoginResponse& data);

        // Creates a NetworkObject containing a CreateAccountResponse packet
        NetworkObject createResponse(const CreateAccountResponse& data);

        // Creates a NetworkObject containing a CreateEventResponse packet
        NetworkObject createResponse(const CreateEventResponse& data);

        // Creates a NetworkObject containing a SuggestEventsResponse packet
        NetworkObject createResponse(const SuggestEventsResponse& data);

        // Creates a NetworkObject containing a CreateHostResponse packet
        NetworkObject createResponse(const CreateHostResponse& data);

        // Create a NetworkObject containing a JoinEventResponse packet
        NetworkObject createResponse(const JoinEventResponse& data);

        // Create a NetworkObject containing a RetrieveMyEventsResponse packet
        NetworkObject createResponse(const RetrieveMyEventsResponse& data);

    private:

        // LoginResponse packet ctor
        NetworkObject(const LoginResponse& response);

        // CreateAccountResponse packet ctor
        NetworkObject(const CreateAccountResponse& response);

        // CreateEventResponse packet ctor
        NetworkObject(const CreateEventResponse& response);

        // SuggestEventsResponse packet ctor
        NetworkObject(const SuggestEventsResponse& response);

        // CreateHostResponse packet ctor
        NetworkObject(const CreateHostResponse& response);

        // JoinEventResponse packet ctor
        NetworkObject(const JoinEventResponse& response);

        // RetrieveMyEventsResponse packet ctor
        NetworkObject(const RetrieveMyEventsResponse& data);


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
