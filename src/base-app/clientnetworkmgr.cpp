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

    qint32 ClientNetworkMgr::sendRequest(const NetworkObject& request) {
        // Note: this would preferably be done asynchronously
        // Extract details
        quint32 type = (quint64) request.getPayloadType();
        QByteArray payload = request.getPayload();
        quint32 size = (quint32) payload.size();

        // Send data to the server
        writeToSocket((char*)&type, sizeof(quint32));
        writeToSocket((char*)&size, sizeof(quint32));
        writeToSocket(payload.data(), payload.size());

        return mRequestCounter++;
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

    void ClientNetworkMgr::writeToSocket(const char* data, long long size) {
        // Unfortunately, Qt provides no mechanism to automatically do this.
        qint64 written = 0;
        while (written < size) {
            written += mSocket->write(&data[written], size - written);
            mSocket->waitForBytesWritten(100);
        }
    }
}
