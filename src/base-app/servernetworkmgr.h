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
        ServerNetworkMgr(QObject* parent=NULL);
        void listen(int port);

    private:
        void handleRequest(QTcpSocket* socket, NetworkObject obj);
        void sendResponse(QTcpSocket* socket, NetworkObject obj);

        UserData* getUserData(QTcpSocket* socket);
        void removeUserData(QTcpSocket* socket);

        QTcpServer* mServer;

    private slots:
        void readyRead(QTcpSocket* socket);

        void newConnection();
        void acceptError(QAbstractSocket::SocketError error);
        void acceptSocketError(QAbstractSocket::SocketError error);

        void logMessage(QString message);
    };
}

#endif
