/*Implemented by Jake and Anthony*/

#include "event.h"

namespace base{
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
        if (theVenue.getName().isEmpty() && theVenue.getAddress().isEmpty() && theVenue.getPhoneNumber().isEmpty() && theVenue.getEntryFee() == 0)
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

    bool event::setID(qint32 a)
    {
        if (a < 0)
            return false;
        id = a;
        return true;
    }

    QString event::getName() const
    {
        return name;
    }

    QString event::getCategory() const
    {
        return category;
    }

    QString event::getMainHost() const
    {
        return mainHost;
    }

    QVector<QString> event::getAttendingUsers() const
    {
        return attendingUsers;
    }

    venue event::getLocation() const
    {
        return location;
    }

    QString event::getDescription() const
    {
        return description;
    }

    qint32 event::getID() const
    {
        return id;
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

    bool operator==(const event& right, const event& left) {
        return
            right.getName() == left.getName() &&
            right.getCategory() == left.getCategory() &&
            right.getAttendingUsers() == left.getAttendingUsers() &&
            right.getMainHost() == left.getMainHost() &&
            right.getDescription() == left.getDescription() &&
            right.getLocation() == left.getLocation() &&
            right.getID() == left.getID();
    }

    QDataStream& operator<<(QDataStream& ostream, const event& evt) {
        // Write everything
        ostream << evt.getName();
        ostream << evt.getCategory();
        ostream << evt.getMainHost();
        ostream << evt.getAttendingUsers();
        ostream << evt.getLocation().toString();
        ostream << evt.getDescription();
        ostream << evt.getID();

        return ostream;
    }

    QDataStream& operator>>(QDataStream& istream, event& evt) {
        // Read everything
        QString str;
        QVector<QString> users;
        qint32 val;

        istream >> str; evt.setName(str);
        istream >> str; evt.setCategory(str);
        istream >> str; evt.setHost(str);
        istream >> users; evt.setUsers(users);
        istream >> str; evt.setLocation(venue(str));
        istream >> str; evt.setDescription(str);
        istream >> val; evt.setID(val);

        return istream;
    }
}
