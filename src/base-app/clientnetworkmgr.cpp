#include "clientnetworkmgr.h"

#include <QByteArray>
#include <QDataStream>

namespace base {
    ClientNetworkMgr::ClientNetworkMgr(QObject* parent)
        : QObject(parent)
        , mSocket(new QTcpSocket(this))
    {
        QObject::connect(mSocket, &QTcpSocket::connected,
                this, &ClientNetworkMgr::connected);
        QObject::connect(mSocket, &QTcpSocket::disconnected,
                this, &ClientNetworkMgr::disconnected);
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
        stream << message;
        // Send the message
        mSocket->write(block);
    }
}
