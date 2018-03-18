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
                        NetworkObject::Message msg = obj.getMessage();
                        qInfo("%s: %s", qUtf8Printable(msg.category),
                                qUtf8Printable(msg.message));
                    }
                    break;
                case NetworkObject::PT_CreateAccountRequest:
                    {
                        NetworkObject::CreateAccountRequest request = obj.getCreateAccountRequest();
                        NetworkObject::CreateAccountResponse response = { 0, "DB error" };
                        qInfo("create account request for username: %s", qUtf8Printable(request.username));
                        // Add to database
                        try {
                            DatabaseConnection dbConnection(DbName);
                            if (dbConnection.createAccount(request.username, request.password)) {
                                response = { 1, "Account created" };
                            }
                            else {
                                response = { 0, "Username taken" };
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
                        NetworkObject::LoginRequest request = obj.getLoginRequest();
                        NetworkObject::LoginResponse response = {0, "DB Error"};

                        qInfo("%s: is trying to login with %s",
                                qUtf8Printable(request.username),
                                qUtf8Printable(request.password));
                        try {
                            DatabaseConnection dbConnection(DbName);
                            if (dbConnection.checkPassword(request.username, request.password)) {
                                response = { 1, "Authenticated" };
                            }
                            else {
                                response = { 0, "Unknown Username or Bad Password" };
                            }
                        } catch (std::exception& e) {
                            qInfo("db error: %s", e.what());
                        }
                        // Send response
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

    void ServerNetworkMgr::readyRead(QTcpSocket* socket) {
        // Try to read
        NetworkObject netObj;
        if (netObj.tryRead(socket))
            handleRequest(socket, netObj);
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
