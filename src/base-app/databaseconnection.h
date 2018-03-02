#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include "base-app_global.h"
#include "networkobject.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <exception>


namespace base {
    /* Implemented by Kyle and Anthony */
    class BASEAPPSHARED_EXPORT DatabaseConnection : public QObject {
        Q_OBJECT
    public:
        DatabaseConnection(QString hostname);
        ~DatabaseConnection();

        bool testConnection();

    private:
        void SetUp(QString hostname, QString databaseName, QString username, QString password);

        bool validConnect;
        QSqlDatabase db;
    };
}

#endif // DATABASECONNECTION_H
