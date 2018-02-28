#ifndef BASE_CLIENTNETWORK_MGR_H
#define BASE_CLIENTNETWORK_MGR_H

#include <QObject>
#include <QString>
#include <QTcpSocket>

#include "base-app_global.h"

namespace base {
    /* Implemented by Kyle and Anthony */
    class BASEAPPSHARED_EXPORT ClientNetworkMgr : public QObject {
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
