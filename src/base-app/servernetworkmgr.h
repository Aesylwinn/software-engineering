#ifndef BASE_SERVERNETWORKMGR_H
#define BASE_SERVERNETWORKMGR_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "base-app_global.h"

namespace base {
    /* Implemented by Kyle and Anthony */
    class BASEAPPSHARED_EXPORT ServerNetworkMgr : public QObject {
        Q_OBJECT
    public:
        ServerNetworkMgr(QObject* parent=NULL);
        void listen(int port);
    private:
        QTcpServer* mServer;
    signals:
        void logMessageRecieved(QString message);
    private slots:
        void readyRead(QTcpSocket* socket);

        void newConnection();
        void acceptError(QAbstractSocket::SocketError error);
        void acceptSocketError(QAbstractSocket::SocketError error);

        void logMessage(QString message);
    };
}

#endif
