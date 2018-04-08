#ifndef BASE_RECURRINGTIME_H
#define BASE_RECURRINGTIME_H

#include "base-app_global.h"

#include <QObject>

namespace base {
    /* Implemented by Kyle and Yianni */
    // A class to represent times that occur on a weekly basis
    class BASEAPPSHARED_EXPORT RecurringTime : public QObject {
        Q_OBJECT
    public:
        enum { Sunday = 1, Monday = 2, Tuesday = 4, Wednesday = 8,
                Thursday = 16, Friday = 32, Saturday = 64 };

        const unsigned int AllDays = Sunday | Monday | Tuesday | Wednesday |
                        Thursday | Friday | Saturday;

        // Default ctor. Never available.
        RecurringTime();
        RecurringTime(unsigned int daysAvailable, int hour, int minute);
        // See fromString for the format of formattedString
        RecurringTime(QString formattedString);

        // Resets to never available.
        void reset();

        int getHour();
        int getMinute();
        QString getDays();

        void setHour(int hour);
        void setMinute(int minute);
        // The dayMask can be 0 to all of the days ORed together
        void setAvailableDays(int dayMask);

        void enableDays(int dayMask);
        void disableDays(int dayMask);

        bool availableOnAll(unsigned int dayMask);
        bool availableOnAny(unsigned int dayMask);

        // The format is expected to match SMTWRFS.02:15
        // All days should be specified or be replaced with a '-'
        // For example, '--T-R--.15:05'
        RecurringTime& fromString(QString formattedString);
        // Returns a string in the same format is fromString expects
        QString toString();

    private:
        int mHour;
        int mMinute;
        unsigned int mDayMask;
    };
}

#endif
