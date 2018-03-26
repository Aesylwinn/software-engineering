#ifndef BASE_NETWORK_PACKETS_H
#define BASE_NETWORK_PACKETS_H

namespace base {
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
}

#endif
