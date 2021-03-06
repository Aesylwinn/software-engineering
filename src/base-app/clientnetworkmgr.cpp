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
        QObject::connect(mSocket, &QTcpSocket::readyRead,
                this, &ClientNetworkMgr::readyRead);
        // Yick... Unfortunately necessary.
        QObject::connect(mSocket, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
                this, &ClientNetworkMgr::socketError);
    }

    void ClientNetworkMgr::connect(QString address, int port) {
        mSocket->connectToHost(address, port);
    }

    void ClientNetworkMgr::disconnect() {
    }

    qint32 ClientNetworkMgr::sendRequest(NetworkObject request) {
        // Note: this would preferably be done asynchronously
        qint32 ticket = mRequestCounter++;
        request.setTicket(ticket);
        request.write(mSocket);
        return ticket;
    }

    void ClientNetworkMgr::readyRead() {
        NetworkObject netObj;
        if (netObj.tryRead(mSocket))
            emit responseRecieved(netObj);
    }

    void ClientNetworkMgr::socketError(QAbstractSocket::SocketError err)
    {
        switch (err) {
        case QAbstractSocket::SocketError::ConnectionRefusedError:
        case QAbstractSocket::SocketError::HostNotFoundError:
            emit disconnected();
            break;

        default:
            // Do nothing
            break;
        }
    }
}
