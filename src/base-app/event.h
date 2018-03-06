/*Implemented by Jake*/

#ifndef EVENT_H
#define EVENT_H

#include <Qstring>
#include <QVector>
#include "venue.h"

#include "base-app_global.h"

namespace  base{
    class event
    {
    public:
        //constructors
        event();
        event(QString theHost);
        event(QString theHost, QVector<QString> theHosts);
        event(QString theHost, QVector<QString> theHosts, QVector<QString> theUsers);
        event(QString theHost, QVector<QString> theHosts, QVector<QString> theUsers, venue theVenue);

        //setters
        bool setHost(QString theHost);
        bool setHosts(QVector<QString> theHosts);
        bool setUsers(QVector<QString> theUsers);
        bool setLocation(venue theVenue);

        //adders
        bool addHost(QString newHost);
        bool addUser(QString newUser);

    private:
        QString mainHost;
        QVector<QString> hosts;
        QVector<QString> attendingUsers;
        venue location;

    };
}
#endif // EVENT_H
