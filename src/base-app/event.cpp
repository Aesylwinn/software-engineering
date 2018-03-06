/*Implemented by Jake*/

#include "event.h"

namespace base{
    event::event()
    {
        mainHost = NULL;
        hosts = NULL;
        attendingUsers = NULL;
        location = NULL;
    }

    event::event(QString theHost)
    {
        setHost(theHost);
        hosts = NULL;
        attendingUsers = NULL;
        location = NULL;
    }

    base::event::event(QString theHost, QVector<QString> theHosts)
    {
        setHost(theHost);
        setHosts(theHosts);
        attendingUsers = NULL;
        location = NULL;
    }

    event::event(QString theHost, QVector<QString> theHosts, QVector<QString> theUsers)
    {
        setHost(theHost);
        setHosts(theHosts);
        setUsers(theUsers);
        location = NULL;
    }

    event::event(QString theHost, QVector<QString> theHosts, QVector<QString> theUsers, base::venue theVenue)
    {
        setHost(theHost);
        setHosts(theHosts);
        setUsers(theUsers);
        setLocation(theVenue);
    }

    bool event::setHost(QString theHost)
    {
        if (theHost.size() == 0)
                return false;
        mainHost = theHost;
        return true;
    }

    bool event::setHosts(QVector<QString> theHosts)
    {
        if (theHosts.size() == 0)
                return false;
        hosts.clear();
        hosts = theHosts;
        return true;
    }

    bool event::setUsers(QVector<QString> theUsers)
    {
        if (theUsers.size() == 0)
                return false;
        attendingUsers.clear();
        attendingUsers = theUsers;
        return true;
    }

    bool event::setLocation(base::venue theVenue)
    {
        if (theVenue == NULL)
            return false;
        location.setAddress(theVenue.getAddress());
        location.setEntryFee(theVenue.getEntryFee());
        location.setName(theVenue.getName());
        location.setPhoneNumber(theVenue.getPhoneNumber());
        return true;
    }

    bool event::addHost(QString newHost)
    {
        if (newHost == NULL)
            return false;
        hosts.push_back(newHost);
        return true;
    }

    bool event::addUser(QString newUser)
    {
        if (newUser == NULL)
            return false;
        attendingUsers.push_back(newUser);
        return true;
    }

}
