#include "networkmanager.h"

#include <QByteArray>
#include <QDataStream>

namespace base {
	NetworkManager::NetworkManager()
		: connection(new QTcpSocket(this))
	{
	}

	void NetworkManager::connectToServer(QString address, int port) {
		connection->connectToHost(address, port);
	}

	void NetworkManager::startServer(int port) {
		server = new QTcpServer(this);
		server->listen(QHostAddress::Any,port);
	}

	void NetworkManager::logToServer(QString data){
		// Set up communication channel
		QByteArray block;
		QDataStream stream(&block, QIODevice::WriteOnly);
		stream.setVersion(QDataStream::Qt_5_10);
		// Send message
		stream << data;
	}
}
