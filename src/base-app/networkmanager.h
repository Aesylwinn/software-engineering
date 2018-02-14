#ifndef BASE_NETWORKMANAGER_H
#define BASE_NETWORKMANAGER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "base-app_global.h"

namespace base {
	class BASEAPPSHARED_EXPORT NetworkManager : public QObject {
		Q_OBJECT
	public:
		NetworkManager();
		void connectToServer(QString address, int port);
		void startServer(int port);

		void logToServer(QString data);
	private:
		QTcpSocket* connection;
		QTcpServer* server;
	};
}

#endif
