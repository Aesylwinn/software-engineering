// Google test
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

// Qt
#include <QString>
#include <QDateTime>
#include <QDate>


// Class being tested
#include "../base-app/event.h"

using namespace testing;
using namespace base;

/* Implemented by Yianni and Jake */

TEST(Event, startTime) {
    Event obj;

    QString startStr;

    ASSERT_TRUE(obj.setStartTime(QString("04/20/2018.16:20")));
    startStr = obj.getStartTime().toString(QString("MM/dd/yyyy.hh:mm"));

    ASSERT_EQ(startStr, QString("04/20/2018.16:20"));

    ASSERT_EQ(obj.addTimes(obj.getStartTime(), obj.getEndTime()), 0);
}

TEST(Event, endTime) {
    Event obj;

    QString endStr;

    ASSERT_TRUE(obj.setEndTime(QString("05/20/2018.16:20")));
    endStr = obj.getEndTime().toString(QString("MM/dd/yyyy.hh:mm"));

    ASSERT_EQ(endStr, QString("05/20/2018.16:20"));

    ASSERT_EQ(obj.addTimes(obj.getStartTime(), obj.getEndTime()), 0);
}

TEST(Event, checkStartAndEndTimes) {
    Event obj;

    QString startStr;
    QString endStr;

    ASSERT_TRUE(obj.setStartTime(QString("04/20/2018.16:20")));
    startStr = obj.getStartTime().toString(QString("MM/dd/yyyy.hh:mm"));
    ASSERT_EQ(startStr, QString("04/20/2018.16:20"));

    ASSERT_TRUE(obj.setEndTime(QString("05/20/2018.16:20")));
    endStr = obj.getEndTime().toString(QString("MM/dd/yyyy.hh:mm"));
    ASSERT_EQ(endStr, QString("05/20/2018.16:20"));
}

TEST(Event, addTimes) {
    Event obj;

    // make sure timeSlots is empty
    ASSERT_EQ(obj.getTimes().size(), 0);

    // create and pushback new timeslot
    obj.setStartTime(QString("04/20/2018.16:20"));
    obj.setEndTime(QString("05/20/2018.16:20"));
    ASSERT_EQ(obj.addTimes(obj.getStartTime(), obj.getEndTime()), 1);

    // make sure timeSlots has 1 item
    ASSERT_EQ(obj.getTimes().size(), 1);

    // attempt to insert new timeslot with same parameters
    obj.setStartTime(QString("04/20/2018.16:20"));
    obj.setEndTime(QString("05/20/2018.16:20"));
    ASSERT_EQ(obj.addTimes(obj.getStartTime(), obj.getEndTime()), -1);

    /* conflicts */
    // attempt to insert with coinciding start time
    obj.setStartTime(QString("04/21/2018.16:20"));
    obj.setEndTime(QString("05/20/2018.16:20"));
    ASSERT_EQ(obj.addTimes(obj.getStartTime(), obj.getEndTime()), -2);

    // attempt to insert with coinciding end time
    obj.setStartTime(QString("04/19/2018.16:20"));
    obj.setEndTime(QString("05/19/2018.16:20"));
    ASSERT_EQ(obj.addTimes(obj.getStartTime(), obj.getEndTime()), -2);

    // attempt to insert with both start and end times coinciding
    obj.setStartTime(QString("04/20/2018.17:20"));
    obj.setEndTime(QString("04/20/2018.19:20"));
    ASSERT_EQ(obj.addTimes(obj.getStartTime(), obj.getEndTime()), -2);

    /* adding timeslots */
    // insert new timeslot before initial timeslot
    obj.setStartTime(QString("04/19/2018.16:20"));
    obj.setEndTime(QString("04/19/2018.17:20"));
    ASSERT_EQ(obj.addTimes(obj.getStartTime(), obj.getEndTime()), 1);

    // insert new timeslot after initial timeslot
    obj.setStartTime(QString("05/20/2018.17:20"));
    obj.setEndTime(QString("05/21/2018.17:20"));
    ASSERT_EQ(obj.addTimes(obj.getStartTime(), obj.getEndTime()), 1);

    // make sure timeSlots has 3 items
    ASSERT_EQ(obj.getTimes().size(), 3);
}

TEST(Event, setReoccurring) {
    Event obj;

    QDateTime start;
    QDateTime end;

    obj.setStartTime(QString("04/20/2018.16:20"));
    obj.setEndTime(QString("04/20/2018.20:20"));
    obj.addTimes(obj.getStartTime(), obj.getEndTime());

    // set to reoccurr for 3 additional weeks
    ASSERT_EQ(obj.setReoccurring(3), 1);

    start = QDateTime::fromString("04/20/2018.16:20", "MM/dd/yyyy.hh:mm");
    end = QDateTime::fromString("04/20/2018.20:20", "MM/dd/yyyy.hh:mm");
    ASSERT_EQ(obj.getTimes().at(0).first, start);
    ASSERT_EQ(obj.getTimes().at(0).second, end);

    start = QDateTime::fromString("04/27/2018.16:20", "MM/dd/yyyy.hh:mm");
    end = QDateTime::fromString("04/27/2018.20:20", "MM/dd/yyyy.hh:mm");
    ASSERT_EQ(obj.getTimes().at(1).first, start);
    ASSERT_EQ(obj.getTimes().at(1).second, end);

    start = QDateTime::fromString("05/04/2018.16:20", "MM/dd/yyyy.hh:mm");
    end = QDateTime::fromString("05/04/2018.20:20", "MM/dd/yyyy.hh:mm");
    ASSERT_EQ(obj.getTimes().at(2).first, start);
    ASSERT_EQ(obj.getTimes().at(2).second, end);

    start = QDateTime::fromString("05/11/2018.16:20", "MM/dd/yyyy.hh:mm");
    end = QDateTime::fromString("05/11/2018.20:20", "MM/dd/yyyy.hh:mm");
    ASSERT_EQ(obj.getTimes().at(3).first, start);
    ASSERT_EQ(obj.getTimes().at(3).second, end);

    // check to see if the vector has the correct elements after turning off reoccur
    ASSERT_EQ(obj.setReoccurring(0), 0);
    start = QDateTime::fromString("04/20/2018.16:20", "MM/dd/yyyy.hh:mm");
    end = QDateTime::fromString("04/20/2018.20:20", "MM/dd/yyyy.hh:mm");
    ASSERT_EQ(obj.getTimes().at(0).first, start);
    ASSERT_EQ(obj.getTimes().at(0).second, end);

    ASSERT_EQ(obj.getTimes().size(), 1);
}

TEST(Event, delTime) {
    Event obj;

    // add and delete object
    obj.setStartTime(QString("04/20/2018.16:20"));
    obj.setEndTime(QString("04/20/2018.20:20"));
    obj.addTimes(obj.getStartTime(), obj.getEndTime());
    ASSERT_TRUE(obj.delTime(0));
    ASSERT_EQ(obj.getTimes().size(), 0);

    // test to see if you can add back in the same object after
    obj.setStartTime(QString("04/20/2018.16:20"));
    obj.setEndTime(QString("04/20/2018.20:20"));
    obj.addTimes(obj.getStartTime(), obj.getEndTime());
    ASSERT_EQ(obj.getTimes().size(), 1);
}
