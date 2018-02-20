#ifndef BASE_SERVERNETWORKMGR_H
#define BASE_SERVERNETWORKMGR_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

namespace base {
    class ServerNetworkMgr : public QObject {
        Q_OBJECT
    public:
        ServerNetworkMgr(QObject* parent=NULL);

        void listen(int port);
    private:
        QTcpServer* mServer;
    signals:
        void logMessageRecieved(QString message);
    private slots:
        void newConnection();
        void acceptError(QAbstractSocket::SocketError error);
    };
}

#endif
