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

    QVector< QPair<QDateTime, QDateTime> > event::getTimes() {
        return timeSlots;
    }

    QDateTime event::getStartTime() {
        return startTime;
    }

    QDateTime event::getEndTime() {
        return endTime;
    }

    qint64 event::getDaysTo() {
        //no idea how to convert qint64 to QString, but doing
        //QDebug() << getDaysTo(); should show the correct
        //result in the output
        return QDateTime::currentDateTime().daysTo(startTime);
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

        startTime = QDateTime::currentDateTime();
        endTime = QDateTime::currentDateTime();
        startTimeSet = false;
        endTimeSet = false;
        reoccurring = false;
    }

    bool event::setStartTime(QString date) {
        QString format = "MM/dd/yyyy.hh:mm";
        QDateTime temp = QDateTime::fromString(date, format);
        // valid input must be current time or greater, might
        // return false if the user's system clock is wrong
        if(temp < QDateTime::currentDateTime()) {
            return false;
        }
        else {
            startTime = temp;
            startTimeSet = true;
            return true;
        }
    }

    bool event::setEndTime(QString date) {
        QString format = "MM/dd/yyyy.hh:mm";
        QDateTime temp = QDateTime::fromString(date, format);
        // valid input must be greater than startTime
        if(temp <= startTime) {
            return false;
        }
        else {
            endTime = temp;
            endTimeSet = true;
            return true;
        }
    }

    int event::setReoccurring(int o) {
    /* Assumes that this function can't be called unless
     * there is ONLY 1 element in timeSlots
     *
     * -2: this should never be reached
     * -1: error (really bad)
     *  0: not reoccurring
     *  1: reoccurring weekly
     */
        QDateTime newStart;
        QDateTime newEnd;

        // not reoccurring
        if(o == 0) {
            reoccurring = false;
            // keep initial timeSlot and delete all other timeSlots
            newStart = timeSlots.at(0).first;
            newEnd = timeSlots.at(0).second;
            timeSlots.clear();
            timeSlots.push_back(qMakePair(newStart, newEnd));
            return 0;
        }

        // reoccurring weekly
        if(o > 0) {
            // might cause outofbounds error if addTimes() returns an error
            // not sure how to check to see
            for(int i = 0; i < o; i++) {
                newStart = timeSlots.at(i).first.addDays(7);
                newEnd = timeSlots.at(i).second.addDays(7);
                startTimeSet = true;
                endTimeSet = true;
                if(addTimes(newStart, newEnd) != 1) {
                    return -1;
                }
            }
            reoccurring = true;
            return 1;
        }
        return -2;
    }

    int event::addTimes(QDateTime start, QDateTime end) {
    /*
     * -2: coinciding timeslots
     * -1: timeslot has already been created
     *  0: missing either start or end time
     *  1: success
     */
        if(startTimeSet && endTimeSet) {    // checks if both start and end times are set

            // user-input error checking
            for(int i = 0; i < timeSlots.size(); i++) {
                // checks if the new pair does not already exist
                if(start == timeSlots.at(i).first && end == timeSlots.at(i).second) {
                    return -1;
                }
                // checks if the new timeslot coincides with another timeslot
                if(start > timeSlots.at(i).first && start < timeSlots.at(i).second) {
                    return -2;
                }
                if(end > timeSlots.at(i).first && end < timeSlots.at(i).second) {
                    return -2;
                }
            }

            // creates a new pair, resets values, and returns 1
            timeSlots.push_back(qMakePair(start, end));
            startTime = QDateTime::currentDateTime();
            endTime = QDateTime::currentDateTime();
            startTimeSet = false;
            endTimeSet = false;

            return 1;
        }
        else {
            return 0;
        }
    }

    bool event::delTime(int pos) {
        if(timeSlots.size() > 0) {
            timeSlots.erase(timeSlots.begin() + pos);
            return true;
        }
        else {
            return false;
        }
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
