#ifndef BASE_CLIENTNETWORK_MGR_H
#define BASE_CLIENTNETWORK_MGR_H

#include <QObject>
#include <QString>
#include <QTcpSocket>

#include "base-app_global.h"
#include "networkobject.h"

namespace base {
    /* Implemented by Kyle and Anthony */
    class BASEAPPSHARED_EXPORT ClientNetworkMgr : public QObject {
        Q_OBJECT
    public:
        ClientNetworkMgr(QObject* parent=NULL);

        void connect(QString address, int port);
        void disconnect();

        // The returned int is the identifier to listen for
        qint32 sendRequest(NetworkObject request);

    private:
        QTcpSocket* mSocket;
        qint32 mRequestCounter;
    private slots:
        void readyRead();
    signals:
        void connected();
        void disconnected();

        void responseRecieved(NetworkObject response);
    };
}

#endif
