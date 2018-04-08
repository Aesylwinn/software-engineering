#ifndef BASE_NETWORK_PACKETS_H
#define BASE_NETWORK_PACKETS_H

#include <QDataStream>
#include <QVector>

#include "event.h"
#include "userprofile.h"

namespace base {
    /* Implemented by Kyle and Anthony */
    /* Some packets partially implemented by Darius and Parker */

    // Constants used to ensure consistency between the server and clients
    const qint32 IsValid = 1;
    const qint32 NotValid = 0;

    // Packet Identifiers
    enum PayloadType {
        PT_None=0,

        PT_CreateAccountRequest=0x1,
        PT_LoginRequest,
        PT_CreateEventRequest,
        PT_SuggestEventsRequest,
        PT_CreateHostRequest,
        PT_JoinEventRequest,
        PT_RetrieveMyEventsRequest,
        PT_SetInterestsRequest,
        PT_FindMatchRequest,
        PT_RetrieveMatchesRequest,

        PT_CreateAccountResponse=0x200,
        PT_LoginResponse,
        PT_CreateEventResponse,
        PT_SuggestEventsResponse,
        PT_CreateHostResponse,
        PT_JoinEventResponse,
        PT_RetrieveMyEventsResponse,
        PT_SetInterestsResponse,
        PT_FindMatchResponse,
        PT_RetrieveMatchesResponse,

        PT_Message=0x400
    };

    // A packet to store a generic message
    struct Message {
        static const size_t Type = PT_Message;

        QString category;
        QString message;
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const Message& msg);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, Message& msg);

    // A packet to store a request to create an account
    struct CreateAccountRequest {
        static const size_t Type = PT_CreateAccountRequest;

        QString username;
        QString password;
        UserProfile profile;
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const CreateAccountRequest& req);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, CreateAccountRequest& req);

    // A packet to store a request to log in to an account
    struct LoginRequest {
        static const size_t Type = PT_LoginRequest;

        QString username;
        QString password;
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const LoginRequest& req);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, LoginRequest& req);

    // A packet to store a request to create an event
    struct CreateEventRequest{
        static const size_t Type = PT_CreateEventRequest;

        Event data;
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const CreateEventRequest& req);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, CreateEventRequest& req);

    // A packet to store a request to become a host
    struct CreateHostRequest {
        static const size_t Type = PT_CreateHostRequest;

        QString username;
        QString password;
        QString displayName;
        QString businessName;
        QString bio;
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const CreateHostRequest& req);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, CreateHostRequest& req);

    // A packet to store a request to receive interesting events
    struct SuggestEventsRequest {
        static const size_t Type = PT_SuggestEventsRequest;

        int count;
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const SuggestEventsRequest& req);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, SuggestEventsRequest& req);

    // A packet to store a request to attend an event
    struct JoinEventRequest {
        static const size_t Type = PT_JoinEventRequest;

        qint64 eventId;
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const JoinEventRequest& req);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, JoinEventRequest& req);

    // A packet to store a request for a users events (attending)
    struct RetrieveMyEventsRequest {
        static const size_t Type = PT_RetrieveMyEventsRequest;

        qint32 count;
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const RetrieveMyEventsRequest& req);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, RetrieveMyEventsRequest& req);

    // A packet to store a request to set a users interests
    struct SetInterestsRequest {
        static const size_t Type = PT_SetInterestsRequest;

        QVector<QString> interests;
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const SetInterestsRequest& req);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, SetInterestsRequest& req);

    // A packet to store a request for a match at an event
    struct FindMatchRequest {
        static const size_t Type = PT_FindMatchRequest;

        qint64 event_id;
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const FindMatchRequest& req);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, FindMatchRequest& req);

    // A packet to store a request for a users's matches
    struct RetrieveMatchesRequest {
        static const size_t Type = PT_RetrieveMatchesRequest;

        qint32 unused;
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const RetrieveMatchesRequest& req);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, RetrieveMatchesRequest& req);

    // A packet to store a response regarding account creation
    struct CreateAccountResponse {
        static const size_t Type = PT_CreateAccountResponse;
        static const size_t RequestType = PT_CreateAccountRequest;

        qint32 valid;
        QString details;
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const CreateAccountResponse& resp);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, CreateAccountResponse& resp);

    // A packet to store a response regarding logging in
    struct LoginResponse {
        static const size_t Type = PT_LoginResponse;
        static const size_t RequestType = PT_LoginRequest;

        qint32 valid;
        QString details;

        qint32 isHost;
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const LoginResponse& resp);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, LoginResponse& resp);

    // A packet to store a response regarding event creation
    struct CreateEventResponse {
        static const size_t Type = PT_CreateEventResponse;
        static const size_t RequestType = PT_CreateEventRequest;

        qint32 valid;
        QString details;
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const CreateEventResponse& resp);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, CreateEventResponse& resp);

    // A packet to store a response for recommended events
    struct SuggestEventsResponse {
        static const size_t Type = PT_SuggestEventsResponse;
        static const size_t RequestType = PT_SuggestEventsRequest;

        QVector<Event> events;
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const SuggestEventsResponse& resp);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, SuggestEventsResponse& resp);

    // A packet to store a response to upgrade an account to become a host
    struct CreateHostResponse {
        static const size_t Type = PT_CreateHostResponse;
        static const size_t RequestType = PT_CreateHostRequest;

        qint32 valid;
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const CreateHostResponse& resp);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, CreateHostResponse& resp);

    // A packet to store a response to attend an event
    struct JoinEventResponse {
        static const size_t Type = PT_JoinEventResponse;
        static const size_t RequestType = PT_JoinEventRequest;

        qint32 valid;
        QString details;
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const JoinEventResponse& resp);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, JoinEventResponse& resp);

    // A packet to store a response for a users events (attending)
    struct RetrieveMyEventsResponse {
        static const size_t Type = PT_RetrieveMyEventsResponse;
        static const size_t RequestType = PT_RetrieveMyEventsRequest;

        QVector<base::Event> events;
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const RetrieveMyEventsResponse& resp);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, RetrieveMyEventsResponse& resp);

    // A packet to store a request to set a users interests
    struct SetInterestsResponse {
        static const size_t Type = PT_SetInterestsResponse;
        static const size_t RequestType = PT_SetInterestsRequest;

        int valid;
        QString details;
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const SetInterestsResponse& req);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, SetInterestsResponse& req);

    // A packet to store a response to a find a match
    struct FindMatchResponse {
        static const size_t Type = PT_FindMatchResponse;
        static const size_t RequestType = PT_FindMatchRequest;

        int valid;
        QString details;
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const FindMatchResponse& req);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, FindMatchResponse& req);

    // A packet to store a response for the users a user is matched with
    struct RetrieveMatchesResponse {
        static const size_t Type = PT_RetrieveMatchesResponse;
        static const size_t RequestType = PT_RetrieveMatchesRequest;

        QVector<UserProfile> matches;
        QVector<base::Event> events;
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const RetrieveMatchesResponse& resp);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, RetrieveMatchesResponse& resp);
}

#endif
