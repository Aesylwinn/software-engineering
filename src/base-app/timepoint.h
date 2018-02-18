#ifndef TIMEPOINT_H
#define TIMEPOINT_H

#include "base-app_global.h"
#include <QObject>

namespace base {
    // An example of a class for unit testing purposes
    class BASEAPPSHARED_EXPORT TimePoint : public QObject {
        Q_OBJECT
    public:
        TimePoint(); //initializes to 0 seconds after Epoch
        TimePoint(int secondsPastEpoch);
        TimePoint(int month, int day, int year, int hour, int minute);
        TimePoint(QString formattedString); //Converts string formatted as mm/dd/yyyy.hour:min
        enum Month{January,February,March,April,May,June,July,August,September,October,November,December};
        Month getMonth();
        int getDay();
        int getYear();
        int getHour();
        int getMinute();
        void setMonth(Month month); //throws outofbounds exception if invalid; resets day to first of month
        void setDay(int day); // throws OutOfBounds exception if day is invalid
        void setYear(int year);

        void setHour();
        void setYear();

        QString toString(); // Returns a string representation as mm/dd/yyyy.hour:min

    private:
        long seconds; // num of seconds beyond the Epoc, can be positive or negative

    };
}

#endif
