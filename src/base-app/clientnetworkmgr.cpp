#include "clientnetworkmgr.h"

#include <QByteArray>
#include <QDataStream>

namespace base {
    ClientNetworkMgr::ClientNetworkMgr(QObject* parent)
        : QObject(parent)
        , mSocket(new QTcpSocket(this))
    {
    }

    void ClientNetworkMgr::connect(QString address, int port) {
        mSocket->connectToHost(address, port);
    }

    void ClientNetworkMgr::disconnect() {
    }

    void ClientNetworkMgr::log(QString message) {
        // Set up a communication channel
        QByteArray block;
        QDataStream stream(&block, QIODevice::WriteOnly);
        stream.setVersion(QDataStream::Qt_5_10);
        // Send the message
        stream << message;
    }
}
