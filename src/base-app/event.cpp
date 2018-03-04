#include "event.h"

event::event()
{

}

base::event::event()
{
    mainHost = NULL;
    hosts = NULL;
    attendingUsers = NULL;
    location = NULL;
}

base::event::event(QString theHost)
{
    mainHost = theHost;
    hosts = NULL;
    attendingUsers = NULL;
    location = NULL;
}

base::event::event(QString theHost, QVector<QString> theHosts)
{
    mainHost = theHost;
    for (int i = 0; i < theHosts.size(); i++)
        hosts.push_back(theHosts[i]);
    attendingUsers = NULL;
    location = NULL;
}

base::event::event(QString theHost, QVector<QString> theHosts, QVector<QString> theUsers)
{
    mainHost = theHost;
    for (int i = 0; i < theHosts.size(); i++)
        hosts.push_back(theHosts[i]);
    for (int i = 0; i < theUsers.size(); i++)
        attendingUsers.push_back(theUsers[i]);
    location = NULL;
}

base::event::event(QString theHost, QVector<QString> theHosts, QVector<QString> theUsers, base::venue theVenue)
{
    mainHost = theHost;
    for (int i = 0; i < theHosts.size(); i++)
        hosts.push_back(theHosts[i]);
    for (int i = 0; i < theUsers.size(); i++)
        attendingUsers.push_back(theUsers[i]);
    location.setAddress(theVenue.getAddress());
    location.setEntryFee(theVenue.getEntryFee());
    location.setName(theVenue.getName());
    location.setPhoneNumber(theVenue.getPhoneNumber());
}

bool base::event::setHost(QString theHost)
{
    for ()
}
