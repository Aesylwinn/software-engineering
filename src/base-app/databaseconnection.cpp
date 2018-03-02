#include "databaseconnection.h"

namespace base {

DatabaseConnection::DatabaseConnection(QString databaseName)
{
    SetUp("localhost",databaseName,"ubuntu","");
}

DatabaseConnection::~DatabaseConnection()
{
    db.close();
}

void DatabaseConnection::SetUp(QString hostname, QString databaseName, QString username, QString password)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(hostname);
    db.setDatabaseName(databaseName);
    db.setUserName(username);
    db.setPassword(password);

    if ( !db.open() )
        throw std::runtime_error("invalid database connection");

}

}
