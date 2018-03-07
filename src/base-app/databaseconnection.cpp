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

bool DatabaseConnection::checkPassword(QString username, QString password)
{
    QSqlQuery query(db);

    if (!query.prepare("SELECT password FROM User_basic WHERE username = :usern"))
        throw std::runtime_error("Unable to check password, unable to prepare query");

    query.bindValue(":usern", username);

    if (!query.exec())
        throw std::runtime_error("Unable to check password, unable to execute query");

    if( query.isSelect() && query.first() )
    {
        QString actualPassword = query.value("password").toString();
        return actualPassword == password;
    }

    return false;

}

bool DatabaseConnection::createAccount(QString username, QString password)
{
    QSqlQuery query(db);

    if (!query.prepare("INSERT INTO User_basic (username, password) VALUES ( :usern, :passw )"))
        throw std::runtime_error("Unable to create account, unable to prepare query");

    query.bindValue(":usern",username);
    query.bindValue(":passw",password);

    if (!query.exec())
        throw std::runtime_error("Unable to create account, unable to execute query");

    return true;
}

}
