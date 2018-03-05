#include "servernetworkmgr.h"

#include <exception>
#include <iostream>

#include <QByteArray>
#include <QDataStream>

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

    void ServerNetworkMgr::handleRequest(NetworkObject obj) {
        qInfo("handling request\n");
        switch (obj.getPayloadType()) {
            case NetworkObject::PT_Message:
                {
                    NetworkObject::Message msg = obj.getMessage();
                    qInfo("%s: %s\n", qUtf8Printable(msg.category),
                            qUtf8Printable(msg.message));
                }
                break;
            case NetworkObject::PT_LoginRequest:
                {
                    NetworkObject::LoginRequest request = obj.getLoginRequest();
                    qInfo("%s: is trying to login with %s\n",
                            qUtf8Printable(request.username),
                            qUtf8Printable(request.password));
                }
                break;
            default:
                qInfo("Unknown request encountered: %d", obj.getPayloadType());
                break;
        }
    }

    void ServerNetworkMgr::sendResponse(QTcpSocket* socket, NetworkObject obj) {
        // This should eventually be asynchronous
        obj.write(socket);
    }

    void ServerNetworkMgr::readyRead(QTcpSocket* socket) {
        qInfo("readReady\n");

        // Try to read
        NetworkObject netObj;
        if (netObj.tryRead(socket))
            handleRequest(netObj);
    }

    void ServerNetworkMgr::newConnection() {
        // Get the socket
        QTcpSocket* socket = nullptr;
        while ((socket = mServer->nextPendingConnection()) != nullptr) {
            // Log connection
            qInfo("Incoming connection: host %s port %d\n",
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
        qWarning("Server failed to accept connection: error code %d\n", error);
    }

    void ServerNetworkMgr::acceptSocketError(QAbstractSocket::SocketError error) {
        // Log the error
        QTcpSocket* socket = (QTcpSocket*)  sender();
        qWarning("Connection error: host %s port %d: error code %d\n",
                qUtf8Printable(socket->peerAddress().toString()),
                socket->peerPort(), error);
    }

    void ServerNetworkMgr::logMessage(QString message) {
        qInfo("%s\n", qUtf8Printable(message));
    }
}
