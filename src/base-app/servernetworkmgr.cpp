#include "servernetworkmgr.h"

#include <exception>
#include <iostream>

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

    void ServerNetworkMgr::newConnection() {
        std::cout << "New connection!\n";
    }

    void ServerNetworkMgr::acceptError(QAbstractSocket::SocketError error) {
        std::cout << "Error: " << error << "\n";
    }
}
