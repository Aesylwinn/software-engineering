#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include "base-app_global.h"
#include "event.h"
#include "networkobject.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QVector>
#include <QString>
#include <exception>


namespace base {
    /* Implemented by Kyle and Anthony */
    class BASEAPPSHARED_EXPORT DatabaseConnection : public QObject {
        Q_OBJECT
    public:
        DatabaseConnection(QString hostname);
        ~DatabaseConnection();
        bool checkPassword(QString username, QString password); //can throw run-time error if server unavailable

        bool createAccount(QString username, QString password); //can throw run-time error if server unavailable
        bool createHost(qint64 userId, QString displayName, QString businessName, QString data);
        bool createEvent(base::event event);

        bool getId(QString username, qint64& id);
        bool isHost(QString username);

        bool getEvents(QVector<base::event>& events);

    private:
        void SetUp(QString hostname, QString databaseName, QString username, QString password);

        bool validConnect;
        QSqlDatabase *db;
        QString connectionName;
    };
}

#endif // DATABASECONNECTION_H
