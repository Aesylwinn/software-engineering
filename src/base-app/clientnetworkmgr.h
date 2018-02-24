#ifndef BASE_CLIENTNETWORK_MGR_H
#define BASE_CLIENTNETWORK_MGR_H

#include <QObject>
#include <QString>
#include <QTcpSocket>

namespace base {
    /* Implemented by Kyle and Anthony */
    class ClientNetworkMgr : public QObject {
        Q_OBJECT
    public:
        ClientNetworkMgr(QObject* parent=NULL);

        void connect(QString address, int port);
        void disconnect();

        void log(QString message);
    private:
        QTcpSocket* mSocket;
    signals:
        void connected();
        void disconnected();
    };
}

#endif
