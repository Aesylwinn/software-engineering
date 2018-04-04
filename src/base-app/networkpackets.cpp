#include "networkpackets.h"

namespace base {
    // Message
    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const Message& msg) {
        return ds << msg.category << msg.message;
    }

    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, Message& msg) {
        return ds >> msg.category >> msg.message;
    }

    // CreateAccountRequest
    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const CreateAccountRequest& req) {
        ds << req.username << req.password;
        ds << req.email;
        ds << req.firstName << req.lastName;
        ds << req.gender;
        ds << req.birthDate;

        return ds;
    }

    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, CreateAccountRequest& req) {
        ds >> req.username >> req.password;
        ds >> req.email;
        ds >> req.firstName >> req.lastName;
        ds >> req.gender;
        ds >> req.birthDate;

        return ds;
    }

    // LoginRequest
    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const LoginRequest& req) {
        return ds << req.username << req.password;
    }

    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, LoginRequest& req) {
        return ds >> req.username >> req.password;
    }

    // CreateEventRequest
    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const CreateEventRequest& req) {
        return ds << req.data;
    }

    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, CreateEventRequest& req) {
        return ds >> req.data;
    }

    // CreateHostRequest
    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const CreateHostRequest& req) {
        ds << req.username << req.password;
        ds << req.displayName;
        ds << req.businessName;
        ds << req.bio;

        return ds;
    }

    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, CreateHostRequest& req) {
        ds >> req.username >> req.password;
        ds >> req.displayName;
        ds >> req.businessName;
        ds >> req.bio;

        return ds;
    }

    // SuggestEventsRequest
    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const SuggestEventsRequest& req) {
        return ds << req.count;
    }

    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, SuggestEventsRequest& req) {
        return ds >> req.count;
    }

    // JoinEventRequest
    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const JoinEventRequest& req) {
        return ds << req.eventId;
    }

    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, JoinEventRequest& req) {
        return ds >> req.eventId;
    }

    // RetrieveMyEventsRequest
    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const RetrieveMyEventsRequest& req) {
        return ds << req.count;
    }

    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, RetrieveMyEventsRequest& req) {
        return ds >> req.count;
    }

    // SetInterestsRequest
    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const SetInterestsRequest& req) {
        return ds << req.interests;
    }

    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, SetInterestsRequest& req) {
        return ds >> req.interests;
    }

    // FindMatchRequest
    BASEAPPSHARED_EXPORT QDataStream &operator<<(QDataStream &ds, const FindMatchRequest &req)
    {
        return ds << req.event_id;
    }

    BASEAPPSHARED_EXPORT QDataStream &operator>>(QDataStream &ds, FindMatchRequest &req)
    {
        return ds >> req.event_id;
    }

    // RetrieveMatchesRequest
    BASEAPPSHARED_EXPORT QDataStream &operator<<(QDataStream &ds, const RetrieveMatchesRequest &req)
    {
        return ds << req.unused;
    }

    BASEAPPSHARED_EXPORT QDataStream &operator>>(QDataStream &ds, RetrieveMatchesRequest &req)
    {
        return ds >> req.unused;
    }


    // CreateAccountResponse
    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const CreateAccountResponse& resp) {
        return ds << resp.valid << resp.details;
    }

    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, CreateAccountResponse& resp) {
        return ds >> resp.valid >> resp.details;
    }

    // LoginResponse
    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const LoginResponse& resp) {
        return ds << resp.valid << resp.details << resp.isHost;
    }

    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, LoginResponse& resp) {
        return ds >> resp.valid >> resp.details >> resp.isHost;
    }

    // CreateEventResponse
    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const CreateEventResponse& resp) {
        return ds << resp.valid << resp.details;
    }

    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, CreateEventResponse& resp) {
        return ds >> resp.valid >> resp.details;
    }

    // SuggestEventsResponse
    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const SuggestEventsResponse& resp) {
        return ds << resp.events;
    }

    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, SuggestEventsResponse& resp) {
        return ds >> resp.events;
    }

    // CreateHostResponse
    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const CreateHostResponse& resp) {
        return ds << resp.valid;
    }

    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, CreateHostResponse& resp) {
        return ds >> resp.valid;
    }

    // JoinEventResponse
    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const JoinEventResponse& resp) {
        return ds << resp.valid << resp.details;
    }

    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, JoinEventResponse& resp) {
        return ds >> resp.valid >> resp.details;
    }

    // RetrieveMyEventsResponse
    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const RetrieveMyEventsResponse& resp) {
        return ds << resp.events;
    }

    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, RetrieveMyEventsResponse& resp) {
        return ds >> resp.events;
    }

    // SetInterestsResponse
    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const SetInterestsResponse& req) {
        return ds << req.valid << req.details;
    }

    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, SetInterestsResponse& req) {
        return ds >> req.valid >> req.details;
    }

    // FindMatchResponse
    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const FindMatchResponse& req) {
        return ds << req.valid << req.details;
    }

    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, FindMatchResponse& req) {
        return ds >> req.valid >> req.details;
    }

    // RetrieveMatchesResponse
    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const RetrieveMatchesResponse& resp) {
        return ds << resp.todo;
    }

    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, RetrieveMatchesResponse& resp) {
        return ds >> resp.todo;
    }
}
