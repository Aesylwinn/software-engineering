#ifndef BASE_SERVERNETWORKMGR_H
#define BASE_SERVERNETWORKMGR_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "base-app_global.h"
#include "networkobject.h"

namespace base {
    class UserData;

    /* Implemented by Kyle and Anthony */
    class BASEAPPSHARED_EXPORT ServerNetworkMgr : public QObject {
        Q_OBJECT
    public:
        //constructor
        ServerNetworkMgr(QObject* parent=NULL);

        //attempts to "listen" to certain ports, returns error if the port isn't talking
        void listen(int port);

    private:
        //Runs through any requests from the client (i.e. create/join/set/get/search)
        void handleRequest(QTcpSocket* socket, NetworkObject obj);

        //writes a response to a socket
        void sendResponse(QTcpSocket* socket, NetworkObject obj);

        //returns user data
        UserData* getUserData(QTcpSocket* socket);

        //deletes user data
        void removeUserData(QTcpSocket* socket);

        QTcpServer* mServer;

    private slots:
        //tries to read a packet
        void readyRead(QTcpSocket* socket);

        //Creates new connection from client-side
        void newConnection();

        //logs errors created when server fails to accept connection
        void acceptError(QAbstractSocket::SocketError error);

        //logs errors created when client failed to connect
        void acceptSocketError(QAbstractSocket::SocketError error);

        //prints message to the log
        void logMessage(QString message);
    };
}

#endif
