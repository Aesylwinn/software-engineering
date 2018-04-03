#include "servernetworkmgr.h"

#include <exception>
#include <iostream>

#include <QByteArray>
#include <QDataStream>

#include "databaseconnection.h"

namespace base {
    ServerNetworkMgr::ServerNetworkMgr(QObject* parent)
        : QObject(parent)
        , mServer(new QTcpServer(this))
    {
        connect(mServer, &QTcpServer::newConnection,
                this, &ServerNetworkMgr::newConnection);
        connect(mServer, &QTcpServer::acceptError,
                this, &ServerNetworkMgr::acceptError);
    }

    void ServerNetworkMgr::listen(int port) {
        if (!mServer->listen(QHostAddress::Any, port)) {
            throw std::runtime_error("Server failed to listen!");
        }
    }

    void ServerNetworkMgr::handleRequest(QTcpSocket* socket, NetworkObject obj) {
        try {
            const char* DbName = "se";
            switch (obj.getPayloadType()) {
                case NetworkObject::PT_Message:
                    {
                        Message msg = obj.getMessage();
                        qInfo("%s: %s", qUtf8Printable(msg.category),
                                qUtf8Printable(msg.message));
                    }
                    break;
                case NetworkObject::PT_CreateAccountRequest:
                    {
                        CreateAccountRequest request = obj.getCreateAccountRequest();
                        CreateAccountResponse response = { NotValid, "DB error" };
                        qInfo("create account request for username: %s", qUtf8Printable(request.username));
                        // Add to database
                        try {
                            DatabaseConnection dbConnection(DbName);
                            if (dbConnection.createAccount(request.username, request.password)) {
                                response = { IsValid, "Account created" };
                            }
                            else {
                                response = { NotValid, "Username taken" };
                            }
                        } catch (std::exception& e) {
                            qInfo("db error: %s", e.what());
                        }
                        // Send response
                        sendResponse(socket, obj.createResponse(response));
                    }
                    break;
                case NetworkObject::PT_LoginRequest:
                    {
                        LoginRequest request = obj.getLoginRequest();
                        LoginResponse response = { NotValid, "DB Error", 0};

                        qInfo("%s: is trying to login", qUtf8Printable(request.username));

                        try {
                            // Get rid of the old
                            removeUserData(socket);

                            // Add the new
                            UserData* userData = new UserData(socket, DbName, request.username, request.password);
                            userData->setObjectName(UserData::ObjectName);

                            // Generate response
                            if (userData->isValid()) {
                                response = { IsValid, "Success", userData->isHost() };
                            }
                        } catch (std::exception& e) {
                            qInfo("db error: %s", e.what());
                        }
                        // Send response
                        sendResponse(socket, obj.createResponse(response));
                    }
                    break;
                case NetworkObject::PT_CreateEventRequest:
                    {
                        CreateEventRequest request = obj.getCreateEventRequest();
                        CreateEventResponse response = { NotValid, "Event was not created" };

                        qInfo("create event: %s", qUtf8Printable(request.data.getName()));

                        try {
                            UserData* userData = getUserData(socket);
                            if (userData && userData->isValid()) {
                                // Set up db access
                                DatabaseConnection dbConnection(DbName);
                                qint64 venueId;

                                // Handle venue
                                if (dbConnection.getOrCreateVenueId(request.data.getLocation(), venueId)) {
                                    // Event
                                    if (dbConnection.createEvent(request.data, userData->getUserId(), venueId)) {
                                        response = { IsValid, "Event created" };
                                    } else {
                                        response = { NotValid, "Invalid event" };
                                    }
                                } else {
                                    response = { NotValid, "Invalid venue" };
                                }
                            } else {
                                response = { NotValid, "Not logged in" };
                            }
                        } catch (std::exception& e) {
                            qInfo("db error: %s", e.what());
                        }

                        sendResponse(socket, obj.createResponse(response));
                    }
                    break;
                case NetworkObject::PT_CreateHostRequest:
                    {
                        CreateHostRequest request = obj.getCreateHostRequest();
                        CreateHostResponse response = { NotValid };

                        qInfo("create host: %s", qUtf8Printable(request.username));

                        try {
                            DatabaseConnection dbConnection(DbName);
                            if (dbConnection.checkPassword(request.username, request.password)) {
                                qint64 id = 0;
                                if (dbConnection.getUserId(request.username, id)) {
                                    if (dbConnection.createHost(id, request.displayName, request.businessName, request.bio)) {
                                        response = { IsValid };
                                    }
                                }
                            }
                        } catch (std::exception& e) {
                            qInfo("db error: %s", e.what());
                        }

                        sendResponse(socket, obj.createResponse(response));
                    }
                    break;
                case NetworkObject::PT_SuggestEventsRequest:
                    {
                        SuggestEventsRequest request = obj.getSuggestEventsRequest();
                        SuggestEventsResponse response = {};

                        qInfo("suggest events: %d", request.count);

                        try {
                            DatabaseConnection dbConnection(DbName);
                            if (dbConnection.getEvents(response.events)) {
                                // Trim count, eventually choose best fit
                                if (response.events.count() > request.count)
                                    response.events.resize(request.count);
                            } else {
                                qInfo("failed to retrieve any events");
                            }
                        } catch (std::exception& e) {
                            qInfo("db error: %s", e.what());
                        }

                        sendResponse(socket, obj.createResponse(response));
                    }
                    break;
                case NetworkObject::PT_JoinEventRequest:
                    {
                        JoinEventRequest request = obj.getJoinEventRequest();
                        JoinEventResponse response = { NotValid, "Failed to join the event" };

                        qInfo("join event: %lld", request.eventId);

                        try {
                            UserData* userData = getUserData(socket);
                            if (userData && userData->isValid()) {
                                DatabaseConnection dbConnection(DbName);
                                if (dbConnection.joinEvent(userData->getUserId(), request.eventId)) {
                                    response = { IsValid, "Event joint" };
                                }
                            } else {
                                response = { NotValid, "Not logged in" };
                            }
                        } catch (std::exception& e) {
                            qInfo("db error: %s", e.what());
                        }

                        sendResponse(socket, obj.createResponse(response));
                    }
                    break;
                case NetworkObject::PT_RetrieveMyEventsRequest:
                    {
                        RetrieveMyEventsRequest request = obj.getRetrieveMyEventsRequest();
                        RetrieveMyEventsResponse response;

                        qInfo("my events: %d", request.count);

                        try {
                            UserData* userData = getUserData(socket);
                            if (userData && userData->isValid()) {
                                DatabaseConnection dbConnection(DbName);
                                dbConnection.getMyEvents(userData->getUserId(), response.events);
                            }
                        } catch (std::exception& e) {
                            qInfo("DB error: %s", e.what());
                        }

                        sendResponse(socket, obj.createResponse(response));
                    }
                    break;
                default:
                    qInfo("Unknown request encountered: %d", obj.getPayloadType());
                    break;
            }
        } catch (std::exception& e) {
            qInfo("Exception in handleRequest: %s", e.what());
        } catch (...) {
            qInfo("Unrecognized exception in handleRequest");
        }
    }

    void ServerNetworkMgr::sendResponse(QTcpSocket* socket, NetworkObject obj) {
        // This should eventually be asynchronous
        obj.write(socket);
    }

    UserData* ServerNetworkMgr::getUserData(QTcpSocket *socket)
    {
        return socket->findChild<UserData*>(UserData::ObjectName);
    }

    void ServerNetworkMgr::removeUserData(QTcpSocket *socket)
    {
        UserData* userData = getUserData(socket);
        delete userData;
    }

    void ServerNetworkMgr::readyRead(QTcpSocket* socket) {
        // Try to read
        try {
            NetworkObject netObj;
            if (netObj.tryRead(socket)) {
                handleRequest(socket, netObj);
            }
        } catch (std::exception& e) {
            qInfo("Exception in readyRead: %s", e.what());
        } catch (...) {
            qInfo("Unrecognized exception in readyRead");
        }
    }

    void ServerNetworkMgr::newConnection() {
        // Get the socket
        QTcpSocket* socket = nullptr;
        while ((socket = mServer->nextPendingConnection()) != nullptr) {
            // Log connection
            qInfo("Incoming connection: host %s port %d",
                    qUtf8Printable(socket->peerAddress().toString()),
                    socket->peerPort());
            // Set up packet reading
            connect(socket, &QTcpSocket::readyRead, this, [=]() {
                this->readyRead(socket);
            });
            // Error handling, old style declaration because error is ambiguous
            connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
                    this, SLOT(acceptSocketError(QAbstractSocket::SocketError)));
        }
    }

    void ServerNetworkMgr::acceptError(QAbstractSocket::SocketError error) {
        // Log the error
        qWarning("Server failed to accept connection: error code %d", error);
    }

    void ServerNetworkMgr::acceptSocketError(QAbstractSocket::SocketError error) {
        // Log the error
        QTcpSocket* socket = (QTcpSocket*)  sender();
        qWarning("Connection error: host %s port %d: error code %d",
                qUtf8Printable(socket->peerAddress().toString()),
                socket->peerPort(), error);
    }

    void ServerNetworkMgr::logMessage(QString message) {
        qInfo("%s\n", qUtf8Printable(message));
    }
}
