#include "timepoint.h"
#include <time.h>

namespace base{

    TimePoint::TimePoint(){ //initializes to 0 seconds after Epoch
        seconds = 0;
    }
    TimePoint::TimePoint(int secondsPastEpoch){
        seconds = secondsPastEpoch;
    }
    TimePoint::TimePoint(int month, int day, int year, int hour, int minute){
        struct std::tm epoch, now;
        epoch.tm_hour = 0;
        epoch.tm_min = 0;
        epoch.tm_sec = 0;
        epoch.tm_mon = 0;
        epoch.tm_mday = 0;
        now.tm_hour = hour;
        now.tm_min = minute;
        now.tm_mon = month;
        now.tm_mday = day;
        now.tm_sec = 0;

        //seconds =std::difftime(std::mktime(&now), std::mktime(&epoch));
    }

    TimePoint::TimePoint(QString formattedString){ //Converts string formatted as mm/dd/yyyy.hour:min
        // formattedString
    }
    /*TimePoint::Month TimePoint::getMonth();
    int TimePoint::getDay();
    int TimePoint::getYear();
    int TimePoint::getHour();
    int TimePoint::getMinute();
    void TimePoint::setMonth(Month month); //throws outofbounds exception if invalid; resets day to first of month
    void TimePoint::setDay(int day); // throws OutOfBounds exception if day is invalid
    void TimePoint::setYear(int year);

    void TimePoint::setHour();
    void TimePoint::setYear();

    QString TimePoint::toString(); // Returns a string representation as mm/dd/yyyy.hour:min
*/

}
