/*Implemented by Jake and Anthony*/

#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QVector>
#include "venue.h"

#include "base-app_global.h"

namespace  base{
    class BASEAPPSHARED_EXPORT event
    {
    public:
        //constructors
        event(QString n = "", qint32 a = 0, QString des = "", QString theHost = "", bool standardOp = false, QVector<QString> theUsers = {""}, venue theVenue = venue(QString("name,address,8675-309,0.00")), QString cat = "");

        //setters
        bool setHost(QString theHost);
        bool setUsers(QVector<QString> theUsers);
        bool setLocation(venue theVenue);
        bool setName(QString n);
        bool setDescription(QString des);
        bool setOperation(bool standardOp);
        bool setCategory(QString cat);
        bool setID(qint32 a);

        //getters
        QString getName()const;
        QString getCategory() const;
        QString getMainHost() const;
        QVector<QString> getAttendingUsers() const;
        venue getLocation() const;
        QString getDescription() const;
        qint32 getID() const;

        //adders
        bool addHost(QString newHost);
        bool addUser(QString newUser);


    private:
        bool standardOperation;
        QString name;
        QString category;
        QString mainHost;
        QVector<QString> attendingUsers;
        venue location;
        QString description;
        qint32 id;

        void initialize(QString n, qint32 a, QString des, QString theHost, bool standardOp, QString cat);
    };
}
#endif // EVENT_H
