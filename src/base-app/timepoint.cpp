#include "timepoint.h"
#include <ctime>

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
        epoch.tm_year = 0;
        now.tm_hour = hour;
        now.tm_min = minute;
        now.tm_mon = month;
        now.tm_mday = day;
        now.tm_year = year;
        now.tm_sec = 0;

        seconds = std::difftime(std::mktime(&now), std::mktime(&epoch));
    }

    TimePoint::TimePoint(QString formattedString){ //Converts string formatted as mm/dd/yyyy.hh:mm
        struct std::tm epoch, now;
        epoch.tm_hour = 0;
        epoch.tm_min = 0;
        epoch.tm_sec = 0;
        epoch.tm_mon = 0;
        epoch.tm_mday = 0;
        epoch.tm_year = 0;
        now.tm_mon = formattedString[0] * 10 + formattedString[1];
        now.tm_mday = formattedString[3] * 10 + formattedString[4];
        now.tm_year = formattedString[6] * 1000 + formattedString[7] * 100 + formattedString[8] * 10 + formattedString[9];
        now.tm_hour = formattedString[11] * 10 + formattedString[12];
        now.tm_min = formattedString[14] * 10 + formattedString[15];

        seconds = std::difftime(std::mktime(&now), std::mktime(&epoch));
    }
    TimePoint::Month TimePoint::getMonth(){
        int yearsSinceEpoch = seconds / 31536000;
        int years = yearsSinceEpoch + 1970;
        int secondsIntoYear = seconds - yearsSinceEpoch * 31536000;
        int currentDay = secondsIntoYear / 86400;
        if (currentDay >= 1 && currentDay <= 31)
               return January;
        if (years % 4 == 0){
            if (currentDay >= 32 && currentDay <= 60)
                return February;
            if(currentDay >= 61 && currentDay <= 91)
                return March;
            if(currentDay >= 92 && currentDay <= 121)
                return April;
            if(currentDay >= 122 && currentDay <= 152)
                return May;
            if(currentDay >= 153 && currentDay <= 182)
                return June;
            if(currentDay >= 183 && currentDay <= 213)
                return July;
            if(currentDay >= 214 && currentDay <= 244)
                return August;
            if(currentDay >= 245 && currentDay <= 274)
                return September;
            if(currentDay >= 275 && currentDay <= 305)
                return October;
            if(currentDay >= 306 && currentDay <= 335)
                return November;
            if(currentDay >= 336 && currentDay <= 366)
                return December;
        }
        else{
            if (currentDay >= 32 && currentDay <= 59)
                return February;
            if(currentDay >= 60 && currentDay <= 90)
                return March;
            if(currentDay >= 91 && currentDay <= 120)
                return April;
            if(currentDay >= 121 && currentDay <= 151)
                return May;
            if(currentDay >= 152 && currentDay <= 181)
                return June;
            if(currentDay >= 182 && currentDay <= 212)
                return July;
            if(currentDay >= 213 && currentDay <= 243)
                return August;
            if(currentDay >= 244 && currentDay <= 273)
                return September;
            if(currentDay >= 274 && currentDay <= 304)
                return October;
            if(currentDay >= 305 && currentDay <= 334)
                return November;
            if(currentDay >= 335 && currentDay <= 365)
                return December;
        }

    }
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
/*
}
