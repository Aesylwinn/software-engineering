#ifndef EVENT_H
#define EVENT_H

#include <QDataStream>
#include <QString>
#include <QVector>
#include <QDateTime>
#include "venue.h"

#include "base-app_global.h"

namespace  base{
    /* Implemented by Jake and Anthony */
    /* Functionality added by Jake and Yianni */
    class BASEAPPSHARED_EXPORT Event
    {
    public:
        //constructors
        Event(QString n = "", qint32 a = 0, QString des = "", QString theHost = "", bool standardOp = false, QVector<QString> theUsers = {""}, venue theVenue = venue(QString("name,address,8675-309,0.00")), QString cat = "");

        //setters
        bool setHost(QString theHost);
        bool setUsers(QVector<QString> theUsers);
        bool setLocation(venue theVenue);
        bool setName(QString n);
        bool setDescription(QString des);
        bool setOperation(bool standardOp);
        bool setCategory(QString cat);
        bool setID(qint32 a);
        bool setTimes(QDateTime t);
        bool setStartTime(QString date);
        bool setStartTime(QDateTime date);
        bool setEndTime(QDateTime date);
        bool setEndTime(QString date);
        int setReoccurring(int o);

        //getters
        QString getName()const;
        QString getCategory() const;
        QString getMainHost() const;
        QVector<QString> getAttendingUsers() const;
        venue getLocation() const;
        QString getDescription() const;
        qint32 getID() const;
        QVector< QPair<QDateTime, QDateTime> > getTimes();
        QDateTime getStartTime() const;
        QDateTime getEndTime() const;
        qint64 getDaysTo();

        //adders
        bool addHost(QString newHost);
        bool addUser(QString newUser);
        int addTimes(QDateTime start, QDateTime end);

        //not adders
        bool delTime(int pos);


    private:
        bool standardOperation;
        QString name;
        QString category;
        QString mainHost;
        QVector<QString> attendingUsers;
        venue location;
        QString description;
        qint32 id;

        QVector< QPair<QDateTime, QDateTime> > timeSlots;
        QDateTime startTime;
        QDateTime endTime;
        qint64 daysTo;
        bool reoccurring;
        bool startTimeSet;
        bool endTimeSet;

        void initialize(QString n, qint32 a, QString des, QString theHost, bool standardOp, QString cat);

        friend BASEAPPSHARED_EXPORT bool operator==(const Event&, const Event&);
        friend BASEAPPSHARED_EXPORT bool operator!=(const Event&, const Event&);
        friend BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream&, const Event&);
        friend BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream&, Event&);
    };

    // Equality
    BASEAPPSHARED_EXPORT bool operator==(const Event&, const Event&);
    BASEAPPSHARED_EXPORT bool operator!=(const Event&, const Event&);

    // Stream output
    BASEAPPSHARED_EXPORT QDataStream&  operator<<(QDataStream&, const Event&);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream&, Event&);
}
#endif // EVENT_H
