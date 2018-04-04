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

bool DatabaseConnection::createEvent(base::event evt, qint64 hostID, qint64 venueID)
{
    QSqlQuery query(*db);

    //set db values
    if (!query.prepare("INSERT INTO Event (id_host,standardOperation, recurring, displayName, id_category, id_venue, dateStart, dateEnd, timeStart, timeEnd, description)"
                                 " VALUES (  :host,            FALSE,     FALSE,       :disp,        :cat,     :ven, :dateStrt,:dateEnd, :timeStrt,:timeEnd,        :bio)"))
        throw std::runtime_error("Unable to create event, unable to prepare query");

    query.bindValue(":host", hostID);
    query.bindValue(":disp", evt.getName());
    query.bindValue(":cat", 0);
    query.bindValue(":ven", venueID);
    query.bindValue(":dateStrt", evt.getStartTime().date());
    query.bindValue(":dateEnd", evt.getEndTime().date());
    query.bindValue(":timeStrt", evt.getStartTime().time());
    query.bindValue(":timeEnd", evt.getEndTime().time());
    query.bindValue(":bio", evt.getDescription());

    if (!query.exec()) {
        return false;
    }

    return true;
}

bool DatabaseConnection::getVenueId(venue location, qint64& id) {
    // Try to retrieve the id from the database
    QSqlQuery query(*db);

    // Should never fail
    if (!query.prepare("SELECT id FROM Venue WHERE displayName = :dispName"))
        throw std::runtime_error("Unable to get venue, preparation failed");

    // Try running
    query.bindValue(":dispName", location.getName());
    if (!query.exec()) {
        return false;
    }

    // Retrieve first value if it exists
    if (query.isSelect() && query.first()) {
        id = query.value("id").toInt();
        return true;
    } else {
        return false;
    }
}

bool DatabaseConnection::getOrCreateVenueId(venue location, qint64& id) {
    // Check for existing
    if (getVenueId(location, id)) {
        return true;
    }

    // Try adding it
    {
        QSqlQuery query(*db);

        // Should never fails
        if (!query.prepare("INSERT INTO Venue (displayName, address, phoneNumber, entryFee)"
                           "           VALUES (      :disp,   :addr,      :phone,     :fee)"))
            throw std::runtime_error("Unable to create venue, unable to prepare query");

        query.bindValue(":disp", location.getName());
        query.bindValue(":addr", location.getAddress());
        query.bindValue(":phone", location.getPhoneNumber());
        query.bindValue(":fee", location.getEntryFee());

        // Try running
        if (!query.exec()) {
            return false;
        }
    }

    // Look it up
    return getVenueId(location, id);
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

bool DatabaseConnection::getUserId(QString username, qint64& id) {
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

    id = -1;
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
            base::event evt;
            QDateTime dateTime;

            evt.setName(query.value("displayName").toString());
            evt.setDescription(query.value("description").toString());
            evt.setID(query.value("id").toInt());

            dateTime.setDate(query.value("dateStart").toDate());
            dateTime.setTime(query.value("timeStart").toTime());
            evt.setStartTime(dateTime);

            dateTime.setDate(query.value("dateEnd").toDate());
            dateTime.setTime(query.value("timeEnd").toTime());
            evt.setEndTime(dateTime);

            // TODO other fields

            events.push_back(evt);
        } while (query.next());

        return true;
    }

    return false;
}

bool DatabaseConnection::getMyEvents(qint64 userId, QVector<base::event>& events) {
    // Create query
    QSqlQuery query(*db);
    QString statement = "SELECT * from Event where id in (SELECT id_event from Join_Event where id_user = :id)";

    if (!query.prepare(statement))
        throw std::runtime_error("Unable to select user events, unable to prepare query");

    query.bindValue(":id", userId);

    // Run and process
    if (!query.exec()) {
        return false;
    }

    if (query.isSelect() && query.first()) {
        do {
            base::event evt;
            QDateTime dateTime;

            evt.setName(query.value("displayName").toString());
            evt.setDescription(query.value("description").toString());
            evt.setID(query.value("id").toInt());

            dateTime.setDate(query.value("dateStart").toDate());
            dateTime.setTime(query.value("timeStart").toTime());
            evt.setStartTime(dateTime);

            dateTime.setDate(query.value("dateEnd").toDate());
            dateTime.setTime(query.value("timeEnd").toTime());
            evt.setEndTime(dateTime);

            // TODO other fields

            events.push_back(evt);
        } while (query.next());

        return true;
    }

    return false;
}

bool DatabaseConnection::joinEvent(qint64 userId, qint64 eventId)
{
    QSqlQuery query(*db);
    QString statement = "INSERT INTO Join_Event (id_user, id_event) VALUES (:user, :event)";

    if (!query.prepare(statement))
        throw std::runtime_error("Unable to join event, unable to prepare query");

    query.bindValue(":user", userId);
    query.bindValue(":event", eventId);

    return query.exec();
}

QString UserData::ObjectName = "UserData";

UserData::UserData(QObject *parent, QString dbName, QString username, QString password)
    : QObject(parent)
{
    DatabaseConnection dbConnection(dbName);

    // Validate
    if (dbConnection.checkPassword(username, password)) {
        mValid = true;
        mHost = dbConnection.isHost(username);
        dbConnection.getUserId(username, mUserId);
    } else {
        mValid = false;
        mHost = false;
        mUserId = -1;
    }
}


}
