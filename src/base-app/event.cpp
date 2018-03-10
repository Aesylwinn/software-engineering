/*Implemented by Jake and Anthony*/

#include "event.h"

namespace base{
    event::event()
    {
        initialize("",0,"","",false,"");
    }

    event::event(QString n)
    {
        initialize(n,0,"","",false,"");
    }
    event::event(QString n, int a)
    {
        initialize(n,a,"","",false,"");
    }
    event::event(QString n, int a, QString des)
    {
        initialize(n,a,des,"",false,"");
    }

    event::event(QString n, int a, QString des, QString theHost)
    {
        initialize(n,a,des,theHost,false,"");
    }

    event::event(QString n, int a, QString des, QString theHost, bool standardOp)
    {
        initialize(n,a,des,theHost,standardOp,"");
    }

    event::event(QString n, int a, QString des, QString theHost, bool standardOp, QVector<QString> theUsers)
    {
        initialize(n,a,des,theHost,standardOp,"");
        setUsers(theUsers);
    }
    event::event(QString n, int a, QString des, QString theHost, bool standardOp, QVector<QString> theUsers, venue theVenue)
    {
        initialize(n,a,des,theHost,standardOp,"");
        setUsers(theUsers);
        setLocation(theVenue);
    }
    event::event(QString n, int a, QString des, QString theHost, bool standardOp, QVector<QString> theUsers, venue theVenue, QString cat)
    {
        initialize(n,a,des,theHost,standardOp,cat);
        setUsers(theUsers);
        setLocation(theVenue);
    }

    bool event::setHost(QString theHost)
    {
        if (theHost.isEmpty())
                return false;
        mainHost = theHost;
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

    bool event::setName(QString n)
    {
        if (n.isEmpty())
            return false;
        name = n;
        return true;
    }

    bool event::setDescription(QString des)
    {
        if (des.isEmpty())
            return false;
        description = des;
        return true;
    }

    bool event::setOperation(bool standardOp)
    {
        if (standardOp != true && standardOp != false)
            return false;
        standardOperation = standardOp;
        return true;
    }

    bool event::setCategory(QString cat)
    {
        if (cat.isEmpty())
            return false;
        category = cat;
        return true;
    }

    bool event::setID(int a)
    {
        if (a < 0)
            return false;
        id = a;
        return true;
    }

    bool event::addUser(QString newUser)
    {
        if (newUser.isEmpty())
            return false;
        attendingUsers.push_back(newUser);
        return true;
    }
    void event::initialize(QString n, int a, QString des, QString theHost, bool standardOp, QString cat)
    {
        if (n.isEmpty())
            n = "";
        else
            setName(n);

        if (a < 0)
            id = 0;
        else
            id = a;
        if (des.isEmpty())
            des = "";
        else
            setDescription(des);

        if (theHost.isEmpty())
            mainHost = "";
        else
            setHost(theHost);

        setOperation(standardOp);

        if (cat.isEmpty())
            category = "";
        else
            category = cat;

    }
}