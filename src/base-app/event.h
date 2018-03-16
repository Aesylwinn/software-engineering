/*Implemented by Jake and Anthony*/

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
        event(QString n);
        event(QString n, int a);
        event(QString n, int a, QString des);
        event(QString n, int a, QString des, QString theHost);
        event(QString n, int a, QString des, QString theHost, bool standardOp);
        event(QString n, int a, QString des, QString theHost, bool standardOp, QVector<QString> theUsers);
        event(QString n, int a, QString des, QString theHost, bool standardOp, QVector<QString> theUsers, venue theVenue);
        event(QString n, int a, QString des, QString theHost, bool standardOp, QVector<QString> theUsers, venue theVenue, QString cat);

        //setters
        bool setHost(QString theHost);
        bool setUsers(QVector<QString> theUsers);
        bool setLocation(venue theVenue);
        bool setName(QString n);
        bool setDescription(QString des);
        bool setOperation(bool standardOp);
        bool setCategory(QString cat);
        bool setID(qint32 a);

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

        void initialize(QString n, int a, QString des, QString theHost, bool standardOp, QString cat);
        friend class NetworkObject;
    };
}
#endif // EVENT_H
