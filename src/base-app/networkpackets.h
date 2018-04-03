#ifndef BASE_NETWORK_PACKETS_H
#define BASE_NETWORK_PACKETS_H

#include <QVector>

#include "event.h"

namespace base {
    // Constants used to ensure consistency between the server and clients
    const qint32 IsValid = 1;
    const qint32 NotValid = 0;

    // A packet to store a generic message
    struct Message {
        QString category;
        QString message;
    };

    // A packet to store a request to create an account
    struct CreateAccountRequest {
        QString username;
        QString password;
        QString email;
        QString firstName;
        QString lastName;
        QString gender;
        QString birthDate;
    };

    // A packet to store a request to log in to an account
    struct LoginRequest {
        QString username;
        QString password;
    };

    // A packet to store a request to create an event
    struct CreateEventRequest{
        event data;
    };

    // A packet to store a request to become a host
    struct CreateHostRequest {
        QString username;
        QString password;
        QString displayName;
        QString businessName;
        QString bio;
    };

    // A packet to store a request to receive interesting events
    struct SuggestEventsRequest {
        int count;
    };

    // A packet to store a request to attend an event
    struct JoinEventRequest {
        qint64 eventId;
    };

    // A packet to store a request for a users events (attending)
    struct RetrieveMyEventsRequest {
        qint32 count;
    };

    // A packet to store a response regarding account creation
    struct CreateAccountResponse {
        qint32 valid;
        QString details;
    };

    // A packet to store a response regarding logging in
    struct LoginResponse {
        qint32 valid;
        QString details;

        qint32 isHost;
    };

    // A packet to store a response regarding event creation
    struct CreateEventResponse {
        qint32 valid;
        QString details;
    };

    // A packet to store a response for recommended events
    struct SuggestEventsResponse {
        QVector<event> events;
    };

    // A packet to store a response to upgrade an account to become a host
    struct CreateHostResponse {
        qint32 valid;
    };

    // A packet to store a response to attend an event
    struct JoinEventResponse {
        qint32 valid;
        QString details;
    };

    // A packet to store a response for a users events (attending)
    struct RetrieveMyEventsResponse {
        QVector<base::event> events;
    };
}

#endif
