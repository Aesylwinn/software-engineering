#ifndef BASE_RECURRINGTIME_H
#define BASE_RECURRINGTIME_H

#include "base-app_global.h"

#include <QObject>

namespace base {
    // An example of a class for unit testing purposes
    class BASEAPPSHARED_EXPORT RecurringTime : public QObject {
        Q_OBJECT
    public:
        enum {Sunday = 1, Monday = 2, Tuesday = 4, Wednesday = 8, Thursday = 16, Friday = 32, Saturday = 64};

        RecurringTime();
        RecurringTime(unsigned int daysAvailable, int hour, int minute);
        RecurringTime(QString formatedString);

        int getHour();
        int getMinute();
        QString getDays();

		void setHour(int hour);
		void setMinute(int minute);
		void setAvailableDays(int dayMask);

        bool availableOnAll(unsigned int dayMask);
        bool availableOnAny(unsigned int dayMask);

    private:
        int mHour;
        int mMinute;
        unsigned int mDayMask;
    };
}

/*
Constructors:
- RecurringTime() // Never recurrs
- RecurringTime(unsigned int daysAvailable, int hour, int minute) // daysAvailable is a bit mask
- RecurringTime(QString formatedString) // ex: MWF.13:50
Enums:
- Day // Sunday=1, Monday=2, Tuesday=4, Wednesday=8, etc...
Public methods:
- int getHour()
- int getMinute()
- QString getDays()
- void setHour(int) // throws exception if hour is out of range
- void setMinute(int) // throws exception if minute is invalid
- void setAvailableDays(int dayMask)
- bool availableOnAny(int dayMask)
- bool availableOnAll(int dayMask)
- QString toString() // / ex: SMTWRFS.13:50
*/

#endif
