#include "databaseconnection.h"

#include <sstream>
#include <thread>

namespace base {

DatabaseConnection::DatabaseConnection(QString databaseName)
{
    SetUp("localhost",databaseName,"ubuntu","");
}

DatabaseConnection::~DatabaseConnection()
{
    db->close();
    delete db;
    // db needs to be destroyed before removeDatabase is called
    QSqlDatabase::removeDatabase(connectionName);
}

void DatabaseConnection::SetUp(QString hostname, QString databaseName, QString username, QString password)
{
    // Create a unique connection name for the current thread
    {
        std::ostringstream os;
        os << "SE_CONNECTION_" << std::this_thread::get_id();
        connectionName = QString(os.str().c_str());
    }

    db = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL", connectionName));
    db->setHostName(hostname);
    db->setDatabaseName(databaseName);
    db->setUserName(username);
    db->setPassword(password);

    if ( !db->open() )
        throw std::runtime_error("invalid database connection");

}

bool DatabaseConnection::checkPassword(QString username, QString password)
{
    QSqlQuery query(*db);

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

bool DatabaseConnection::createEvent(base::event evt)
{
    int hostID, venueID;

    QSqlQuery query(*db);

    //search for hostID
    if (!query.prepare("SELECT id_user FROM User_Host WHERE displayName = :dispName"))
        throw std::runtime_error("Unable to retrieve hostID, unable to prepare query");

    query.bindValue(":dispName", evt.getMainHost());

    if (!query.exec()) {
        return false;
    }

    if( query.isSelect() && query.first() )
    {
        hostID = query.value("id_user").toInt();
    } else {
        return false;
    }

    //search for venueID
    if (!query.prepare("SELECT id FROM Venue WHERE displayName = :dispName"))
        throw std::runtime_error("Unable to retrieve venueID, unable to prepare query");

    query.bindValue(":dispName", evt.getLocation().getName());

    if (!query.exec()) {
        return false;
    }

    if( query.isSelect() && query.first() )
    {
        venueID = query.value("id").toInt();
    } else {
        return false;
    }

    //set db values
    if (!query.prepare("INSERT INTO Event (id_host,standardOperation, recurring, displayName, id_category, id_venue, dateStart, description)"
                                 " VALUES (  :host,            FALSE,     FALSE,       :disp,        :cat,     :ven,     :date,        :bio)"))
        throw std::runtime_error("Unable to create account, unable to prepare query");

    query.bindValue(":host", hostID);
    query.bindValue(":disp", evt.getName());
    query.bindValue(":cat", 0);
    query.bindValue(":ven", 0);
    query.bindValue(":date", "2018-4-20");
    query.bindValue(":bio", evt.getDescription());

    if (!query.exec()) {
        return false;
    }

    return true;
}

bool DatabaseConnection::createAccount(QString username, QString password)
{
    QSqlQuery query(*db);

    if (!query.prepare("INSERT INTO User_basic (username, password) VALUES ( :usern, :passw )"))
        throw std::runtime_error("Unable to create account, unable to prepare query");

    query.bindValue(":usern",username);
    query.bindValue(":passw",password);

    if (!query.exec()) {
        // Username is already taken
        return false;
    }

    return true;
}

bool DatabaseConnection::createHost(qint64 userId, QString displayName, QString businessName, QString bio) {
    // Start transaction
    db->transaction();

    // Add host record
    {
        QSqlQuery query(*db);
        QString statement = "INSERT INTO User_Host (id_user, displayName, businessName, bio) VALUES ( :id, :displayName, :businessName, :bio )";

        if (!query.prepare(statement)) {
            db->rollback();
            throw std::runtime_error("Unable to create host account, unable to prepare query");
        }

        query.bindValue(":id", userId);
        query.bindValue(":displayName", displayName);
        query.bindValue(":businessName", businessName);
        query.bindValue(":bio", bio);

        if (!query.exec()) {
            db->rollback();
            return false;
        }
    }

    // Set userType to host
    {

        QSqlQuery query(*db);
        QString statement = "UPDATE User_basic SET userType = 'HOST' WHERE id = :id";

        if (!query.prepare(statement)) {
            db->rollback();
            throw std::runtime_error("Unable to create host account, unable to prepare query; 2");
        }

        query.bindValue(":id", userId);

        if (!query.exec()) {
            db->rollback();
            return false;
        }
    }

    return db->commit();
}

bool DatabaseConnection::getId(QString username, qint64& id) {
    // Create query
    QSqlQuery query(*db);
    QString statement = "SELECT id FROM User_basic WHERE username = :usr";

    if (!query.prepare(statement))
        throw std::runtime_error("Unable to get user id, unable to prepare query");

    query.bindValue(":usr", username);

    // Run and process
    if (!query.exec())
        return false;

    if (query.isSelect() && query.first()) {
        id = query.value("id").toInt();
        return true;
    }

    return false;
}

bool DatabaseConnection::isHost(QString username) {
    // Create query
    QSqlQuery query(*db);
    QString statement = "SELECT userType FROM User_basic WHERE username = :usr";

    if (!query.prepare(statement))
        throw std::runtime_error("Unable to create host account, unable to prepare query");

    query.bindValue(":usr", username);

    // Run and process
    if (!query.exec()) {
        return false;
    }

    if (query.isSelect() && query.first()) {
        QString type = query.value("userType").toString();
        return type == "HOST";
    }

    return false;
}

bool DatabaseConnection::getEvents(QVector<base::event>& events) {
    // Create query
    QSqlQuery query(*db);
    QString statement = "SELECT * FROM Event";

    if (!query.prepare(statement))
        throw std::runtime_error("Unable to select events, unable to prepare query");

    // Run and process
    if (!query.exec()) {
        return false;
    }

    if (query.isSelect() && query.first()) {
        do {
            QString displayName = query.value("displayName").toString();
            // TODO other fields
            events.push_back(base::event(displayName));
        } while (query.next());

        return true;
    }

    return false;
}


}
