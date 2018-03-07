/*Implemented by Jake*/

#include "event.h"

namespace base{
    event::event()
    {
    }

    event::event(QString theHost)
    {
        setHost(theHost);
    }

    event::event(QString theHost, QVector<QString> theHosts)
    {
        setHost(theHost);
        setHosts(theHosts);
    }

    event::event(QString theHost, QVector<QString> theHosts, QVector<QString> theUsers)
    {
        setHost(theHost);
        setHosts(theHosts);
        setUsers(theUsers);
    }

    event::event(QString theHost, QVector<QString> theHosts, QVector<QString> theUsers, base::venue theVenue)
    {
        initialize(theHost, theHosts, theUsers, theVenue);
    }

    bool event::setHost(QString theHost)
    {
        if (theHost.isEmpty())
                return false;
        mainHost = theHost;
        return true;
    }

    bool event::setHosts(QVector<QString> theHosts)
    {
        if (theHosts.isEmpty())
                return false;
        hosts.clear();
        hosts = theHosts;
        return true;
    }

    bool event::setUsers(QVector<QString> theUsers)
    {
        if (theUsers.isEmpty())
                return false;
        attendingUsers.clear();
        attendingUsers = theUsers;
        return true;
    }

    bool event::setLocation(base::venue theVenue)
    {
        if (theVenue.getName().isEmpty())
            return false;
        location.setAddress(theVenue.getAddress());
        location.setEntryFee(theVenue.getEntryFee());
        location.setName(theVenue.getName());
        location.setPhoneNumber(theVenue.getPhoneNumber());
        return true;
    }

    bool event::addHost(QString newHost)
    {
        if (newHost.isEmpty())
            return false;
        hosts.push_back(newHost);
        return true;
    }

    bool event::addUser(QString newUser)
    {
        if (newUser.isEmpty())
            return false;
        attendingUsers.push_back(newUser);
        return true;
    }
    bool event::initialize(QString theHost, QVector<QString> theHosts, QVector<QString> theUsers, venue theVenue)
    {
        setHost(theHost);
        setHosts(theHosts);
        setUsers(theUsers);
        setLocation(theVenue);
        return true;
    }
}
