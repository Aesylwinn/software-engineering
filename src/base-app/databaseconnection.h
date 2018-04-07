#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include "base-app_global.h"
#include "event.h"
#include "networkobject.h"
#include "userprofile.h"

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
        bool createProfile(UserProfile profile);
        bool createHost(qint64 userId, QString displayName, QString businessName, QString data);
        bool createEvent(base::Event event, qint64 hostId, qint64 venueId);

        bool getVenueId(venue location, qint64& id);
        bool getOrCreateVenueId(venue location, qint64& id);

        bool getCategory(qint64 id, QString &category);
        bool getCategoryId(QString category, qint64& id);
        bool getOrCreateCategoryId(QString category, qint64& id);

        bool getUserId(QString username, qint64& id);
        bool isHost(QString username);
        bool getUserProfile(qint64 userId, UserProfile& profile);
        bool getMatches(qint64 userId, QVector<UserProfile>& profiles, QVector<Event>& events);

        bool getEvent(qint64, Event& event);
        bool getVenue(qint64 venueId, venue& ven);
        bool getEvents(QVector<base::Event>& events);
        bool getMyEvents(qint64 userId, QVector<base::Event>& events);
        bool findMatches(qint64 userId, qint64 eventId, QVector<UserProfile>& matches);

        bool joinEvent(qint64 userId, qint64 eventId);
        bool addMatch(qint64 userA, qint64 userB, qint64 eventId);

    private:
        void SetUp(QString hostname, QString databaseName, QString username, QString password);
        void readProfile(QSqlQuery& query, UserProfile& profile);
        void readEvent(QSqlQuery& query, Event& evt);

        bool validConnect;
        QSqlDatabase *db;
        QString connectionName;
    };

    class BASEAPPSHARED_EXPORT UserData : public QObject {
        Q_OBJECT
    public:
        static QString ObjectName;

        UserData(QObject* parent, QString dbName, QString username, QString password);

        bool isValid() const { return mValid; }
        bool isHost() const { return mHost; }
        qint64 getUserId() const { return mUserId; }

     private:
        bool mValid;
        bool mHost;
        qint64 mUserId;
    };
}

#endif // DATABASECONNECTION_H
