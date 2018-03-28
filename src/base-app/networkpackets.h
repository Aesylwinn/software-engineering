#ifndef BASE_NETWORK_PACKETS_H
#define BASE_NETWORK_PACKETS_H

#include <QVector>

#include "event.h"

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

    struct CreateEventRequest{
        event data;
    };

    struct CreateHostRequest {
        QString username;
        QString password;
        QString displayName;
        QString businessName;
        QString bio;
    };

    struct SuggestEventsRequest {
        int count;
    };

    struct CreateAccountResponse {
        qint32 valid;
        QString details;
    };

    struct LoginResponse {
        qint32 valid;
        QString details;

        qint32 isHost;
    };

    struct CreateEventResponse {
        qint32 valid;
        QString details;
    };

    struct SuggestEventsResponse {
        QVector<event> events;
    };

    struct CreateHostResponse {
        qint32 valid;
    };
}

#endif
