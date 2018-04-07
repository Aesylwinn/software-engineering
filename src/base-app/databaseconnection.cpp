#include "databaseconnection.h"

#include <sstream>
#include <thread>
#include <QCryptographicHash>

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

void DatabaseConnection::readEvent(QSqlQuery &query, Event &evt)
{
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

    // TODO others
}

void DatabaseConnection::readProfile(QSqlQuery& query, UserProfile& profile) {
    profile.setFirstName(query.value("firstName").toString());
    profile.setLastName(query.value("lastName").toString());
    profile.setBirthday(query.value("birtday").toDate());
    profile.setEmail(query.value("email").toString());
    profile.setGender(query.value("gender").toString());
    profile.setBio(query.value("bio").toString());
    profile.setUserId(query.value("id_user").toInt());
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
        QCryptographicHash qchash(QCryptographicHash::Sha512);
        qchash.addData(password.toUtf8());
        QString actualHashedPassword = query.value("password").toString();
        QString hashedAttemptPassword(qchash.result().toBase64());
        return actualHashedPassword == hashedAttemptPassword;
    }

    return false;

}

bool DatabaseConnection::createEvent(base::Event evt, qint64 hostID, qint64 venueID)
{
    db->transaction();

    // Get category
    qint64 categoryId = 0;
    if (!getOrCreateCategoryId(evt.getCategory(), categoryId)) {
        db->rollback();
        return false;
    }

    // Create event
    {
        QSqlQuery query(*db);

        //set db values
        if (!query.prepare("INSERT INTO Event (id_host,standardOperation, recurring, displayName, id_category, id_venue, dateStart, dateEnd, timeStart, timeEnd, description)"
                                     " VALUES (  :host,            FALSE,     FALSE,       :disp,        :cat,     :ven, :dateStrt,:dateEnd, :timeStrt,:timeEnd,        :bio)"))
            throw std::runtime_error("Unable to create event, unable to prepare query");

        query.bindValue(":host", hostID);
        query.bindValue(":disp", evt.getName());
        query.bindValue(":cat", categoryId);
        query.bindValue(":ven", venueID);
        query.bindValue(":dateStrt", evt.getStartTime().date());
        query.bindValue(":dateEnd", evt.getEndTime().date());
        query.bindValue(":timeStrt", evt.getStartTime().time());
        query.bindValue(":timeEnd", evt.getEndTime().time());
        query.bindValue(":bio", evt.getDescription());

        if (!query.exec()) {
            db->rollback();
            return false;
        }
    }

    db->commit();
    return true;
}

bool DatabaseConnection::setUserInterests(qint64 userId, QVector<QString> interests)
{
    // TODO
    return true;
}

bool DatabaseConnection::getVenueId(venue location, qint64& id) {
    // Try to retrieve the id from the database
    QSqlQuery query(*db);

    // Should never fail
    if (!query.prepare("SELECT id FROM Venue WHERE address = :address"))
        throw std::runtime_error("Unable to get venue, preparation failed");

    // Try running
    query.bindValue(":address", location.getAddress());
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

bool DatabaseConnection::getCategory(qint64 id, QString& category)
{
    QSqlQuery query(*db);
    QString statement = "SELECT displayName FROM Category where id = :id";

    if (!query.prepare(statement))
        throw std::runtime_error("Unable to get category, failed to prepare");

    query.bindValue(":id", id);

    if (!query.exec())
        return false;

    if (query.isSelect() && query.first()) {
        category = query.value("displayName").toString();
        return true;
    }

    return false;
}

bool DatabaseConnection::getCategoryId(QString category, qint64 &id)
{
    QSqlQuery query(*db);
    QString statement = "SELECT id FROM Category WHERE displayName = :cat";

    if (!query.prepare(statement))
        throw std::runtime_error("Unable to get category id, failed to prepare");

    query.bindValue(":cat", category);

    if (!query.exec())
        return false;

    if (query.isSelect() && query.first()) {
        id = query.value("id").toInt();
        return true;
    }

    return false;
}

bool DatabaseConnection::getOrCreateCategoryId(QString category, qint64 &id)
{
    if (getCategoryId(category, id)) {
        return true;
    }

    // Add it
    {
        QSqlQuery query(*db);
        QString statement = "INSERT INTO Category (displayName) VALUES (:disp)";

        if (!query.prepare(statement))
            throw std::runtime_error("Unable to create category, failed to prepare");

        query.bindValue(":disp", category);
        query.exec();
    }

    return getCategoryId(category, id);
}

bool DatabaseConnection::createAccount(QString username, QString password)
{
    QSqlQuery query(*db);

    QCryptographicHash qchash(QCryptographicHash::Sha512);
    qchash.addData(password.toUtf8());
    QString hashedPassword(qchash.result().toBase64());

    if (!query.prepare("INSERT INTO User_basic (username, password) VALUES ( :usern, :passw )"))
        throw std::runtime_error("Unable to create account, unable to prepare query");

    query.bindValue(":usern",username);
    query.bindValue(":passw",hashedPassword);

    if (!query.exec()) {
        // Username is already taken
        return false;
    }

    return true;
}

bool DatabaseConnection::createProfile(UserProfile profile)
{
    QSqlQuery query(*db);
    QString statement = "INSERT INTO User_Profile (id_user, firstName, lastName, birtday, email, gender, otherGender, orientation, bio)"
                                          "VALUES (   :usr,    :fname,   :lname,   :bday,:email,:gender,        NULL,        NULL,:bio)";

    if (!query.prepare(statement))
        throw std::runtime_error("Unable to create profile, unable to prepare query");

    query.bindValue(":usr", profile.getUserId());
    query.bindValue(":fname", profile.getFirstName());
    query.bindValue(":lname", profile.getLastName());
    query.bindValue(":bday", profile.getBirthday());
    query.bindValue(":email", profile.getEmail());
    query.bindValue(":gender", profile.getGender());
    query.bindValue(":bio", profile.getBio());

    if (!query.exec())
        return false;

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

bool DatabaseConnection::getUserProfile(qint64 userId, UserProfile &profile) {
    // Setup
    QSqlQuery query(*db);
    QString statement = "SELECT * FROM User_Profile WHERE id_user = :id";

    if (!query.prepare(statement))
        throw std::runtime_error("Unable to get user profile, prepare failed");

    query.bindValue(":id", userId);

    // Run
    if (!query.exec()) {
        return false;
    }

    if (query.isSelect() && query.first()) {
        readProfile(query, profile);
        return true;
    }

    return false;
}

bool DatabaseConnection::getMatches(qint64 userId, QVector<UserProfile> &profiles, QVector<Event> &events)
{
    struct TempData {
        qint64 eventId;
        qint64 userId;
    };

    // Retrieve matches
    QVector<TempData> matchData;
    {
        QSqlQuery query(*db);
        QString statement = "SELECT * FROM Join_Date WHERE id_userA = :id OR id_userB = :id";

        if (!query.prepare(statement))
            throw std::runtime_error("Failed to get matches, Join_Date select statement did not prepare");

        query.bindValue(":id", userId);

        if (!query.exec())
            return false;

        if (query.isSelect() && query.first()) {
            do {
                qint64 eventId = query.value("id_event").toInt();
                qint64 user1 = query.value("id_userA").toInt();
                qint64 user2 = query.value("id_userB").toInt();

                matchData.push_back(TempData{ eventId, (user1 == userId) ? user2 : user1 });
            } while (query.next());
        }
    }

    // Process events and matches
    for (const TempData& data : matchData) {
        Event evt;
        UserProfile profile;

        getEvent(data.eventId, evt);
        events.push_back(evt);

        getUserProfile(data.userId, profile);
        profiles.push_back(profile);
    }

    return true;
}

bool DatabaseConnection::getUserInterests(qint64 userId, QVector<QString> &interests)
{
    // TODO
    interests.push_back("Fun");
    return true;
}

bool DatabaseConnection::getEvent(qint64 eventId, Event &evt)
{
    qint64 venueId;
    qint64 categoryId;

    // Event
    {
        QSqlQuery query(*db);
        QString statement = "SELECT * FROM Event WHERE id = :id";

        if (!query.prepare(statement))
            throw std::runtime_error("Failed to get event, failed to prepare");

        query.bindValue(":id", eventId);

        if (!query.exec())
            return false;

        if (query.isSelect() && query.first()) {
            readEvent(query, evt);
            venueId = query.value("id_venue").toInt();
            categoryId = query.value("id_category").toInt();
        } else
            return false;
    }

    // Venue
    venue ven;
    if (getVenue(venueId, ven))
        evt.setLocation(ven);

    // Category
    QString category;
    if (getCategory(categoryId, category))
        evt.setCategory(category);

    return true;
}

bool DatabaseConnection::getVenue(qint64 venueId, venue& ven) {
    QSqlQuery query(*db);
    QString statement = "SELECT * FROM Venue WHERE id = :id";

    if (!query.prepare(statement))
        throw std::runtime_error("Failed to get event, failed to prepare");

    query.bindValue(":id", venueId);

    if (!query.exec())
        return false;

    if (query.isSelect() && query.first()) {
        ven.setName(query.value("displayName").toString());
        ven.setAddress(query.value("address").toString());
        ven.setPhoneNumber(query.value("phoneNumber").toString());
        ven.setEntryFee(query.value("entryFee").toDouble());

        return true;
    }

    return false;
}

bool DatabaseConnection::getEvents(QVector<base::Event>& events) {
    QVector<qint64> venueIds;
    QVector<qint64> categoryIds;

    // Get events
    {
        // Create query
        QSqlQuery query(*db);
        QString statement = "SELECT * FROM Event";

        if (!query.prepare(statement))
            throw std::runtime_error("Unable to select events, unable to prepare query");

        // Run and process
        if (!query.exec())
            return false;

        if (query.isSelect() && query.first()) {
            do {
                base::Event evt;
                qint64 venueId, categoryId;

                readEvent(query, evt);
                venueId = query.value("id_venue").toInt();
                categoryId = query.value("id_category").toInt();

                events.push_back(evt);
                venueIds.push_back(venueId);
                categoryIds.push_back(categoryId);
            } while (query.next());
        }
        else return false;
    }

    // Venues
    for (int i = 0; i < venueIds.count(); ++i) {
        venue ven;

        if (getVenue(venueIds[i], ven))
            events[i].setLocation(ven);
    }

    // Categories
    for (int i = 0; i < categoryIds.count(); ++i) {
        QString category;

        if (getCategory(categoryIds[i], category))
            events[i].setCategory(category);
    }

    return true;
}

bool DatabaseConnection::getMyEvents(qint64 userId, QVector<base::Event>& events) {
    QVector<qint64> venueIds;
    QVector<qint64> categoryIds;

    // Get my events
    {
        // Create query
        QSqlQuery query(*db);
        QString statement = "SELECT * from Event where id in (SELECT id_event from Join_Event where id_user = :id)";

        if (!query.prepare(statement))
            throw std::runtime_error("Unable to select user events, unable to prepare query");

        query.bindValue(":id", userId);

        // Run and process
        if (!query.exec())
            return false;

        if (query.isSelect() && query.first()) {
            do {
                base::Event evt;
                qint64 venueId;
                qint64 categoryId;
                QDateTime dateTime;

                readEvent(query, evt);
                venueId = query.value("id_venue").toInt();
                categoryId = query.value("id_category").toInt();

                events.push_back(evt);
                venueIds.push_back(venueId);
                categoryIds.push_back(categoryId);
            } while (query.next());
        }
        else return false;
    }

    // Venues
    for (int i = 0; i < venueIds.size(); ++i) {
        venue ven;

        if (getVenue(venueIds[i], ven))
            events[i].setLocation(ven);
    }

    // Categories
    for (int i = 0; i < categoryIds.size(); ++i) {
        QString category;

        if (getCategory(categoryIds[i], category))
            events[i].setCategory(category);
    }

    return true;
}

bool DatabaseConnection::findMatches(qint64 userId, qint64 eventId, QVector<UserProfile>& matches) {
    QSqlQuery query(*db);
    QString statement = "SELECT * FROM User_Profile WHERE id_user IN (SELECT id_user FROM Join_Event where id_event = :evtId AND id_user != :userId)";

    if (!query.prepare(statement))
        throw std::runtime_error("Unable to find matches, failed to prepare");

    query.bindValue(":evtId", eventId);
    query.bindValue(":userId", userId);

    if (!query.exec())
        return false;

    if (query.isSelect() && query.first()) {
        do {
            UserProfile profile;
            readProfile(query, profile);
            matches.push_back(profile);
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

bool DatabaseConnection::addMatch(qint64 userA, qint64 userB, qint64 eventId) {
    QSqlQuery query(*db);
    QString statement = "INSERT INTO Join_Date (id_event, id_userA, id_userB, confirmedA, confirmedB)"
                                       "VALUES (    :evt,    :usrA,    :usrB,      FALSE,      FALSE)";

    if (!query.prepare(statement))
        throw std::runtime_error("Unable to add match, unable to prepare query");

    query.bindValue(":evt", eventId);
    query.bindValue(":usrA", userA);
    query.bindValue(":usrB", userB);

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
