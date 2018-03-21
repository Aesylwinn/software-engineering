#ifndef BASE_NETWORKOBJECT_H
#define BASE_NETWORKOBJECT_H

#include <QByteArray>
#include <QBuffer>
#include <QDataStream>
#include <QIODevice>
#include <QString>

#include "base-app_global.h"
#include "event.h"

namespace base {
    /* Implemented by Kyle and Anthony */
    class BASEAPPSHARED_EXPORT NetworkObject {
    public:
        // The types of payloads
        enum PayloadType {
            PT_None,

            PT_CreateAccountRequest,
            PT_LoginRequest,
            PT_CreateEventRequest,

            PT_CreateAccountResponse,
            PT_LoginResponse,
            PT_CreateEventResponse,

            PT_Message
        };

        struct Message {
            QString category;
            QString message;
        };

        struct CreateAccountRequest {
            QString username;
            QString password;
            QString email;
            QString firstName;
            QString lastName;
            QString gender;
            QString birthDate;
        };

        struct LoginRequest {
            QString username;
            QString password;
        };

        struct LoginResponse {
            qint32 valid;
            QString details;
        };

        struct CreateAccountResponse {
            qint32 valid;
            QString details;
        };

        struct CreateEventRequest{
            event data;
        };

        //Darius and Parker inserted
        struct EventRequest {
            QString username;
        };

        //Darius and Parker inserted
        struct EventResponse {
            qint32 valid;
            QVector<event> multipleEvents;
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
        NetworkObject(const CreateEventRequest& data);

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

        // Converts payload to a create account request
        CreateAccountRequest getCreateAccountRequest() const;

        // Converts payload to a login request
        LoginRequest getLoginRequest() const;

        CreateEventRequest getCreateEventRequest() const;

        // Converts payload to a login response
        LoginResponse getLoginResponse() const;

        // Converts payload to a create account response
        CreateAccountResponse getCreateAccountResponse() const;

        // Creates a response to a CreateAccountRequest
        NetworkObject createResponse(const CreateAccountResponse& data);

        // Creates a response to a LoginRequest
        NetworkObject createResponse(const LoginResponse& data);

    private:

        // Login response ctor
        NetworkObject(const LoginResponse& response);

        // CreateAccount response ctor
        NetworkObject(const CreateAccountResponse& response);

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
