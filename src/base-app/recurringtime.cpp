#include "recurringtime.h"

namespace base {
	RecurringTime::RecurringTime()
	{
	    mHour = 0;
	    mMinute = 0;
	    mDayMask = 0;
	}

	RecurringTime::RecurringTime(unsigned int daysAvailable, int hour, int minute)
	{
	    mHour = hour;
	    mMinute = minute;
	    mDayMask = daysAvailable;
	}

	RecurringTime::RecurringTime(QString formatedString)
	{

	}

	int RecurringTime::getHour()
	{
	    return mHour;
	}

	int RecurringTime::getMinute()
	{
	    return mMinute;
	}

	QString RecurringTime::getDays()
	{
	    return "";
	}

	void RecurringTime::setHour(int hour)
	{
		mHour = hour;
	}

	void RecurringTime::setMinute(int min)
	{
		mMinute = min;
	}

	void RecurringTime::setAvailableDays(int dayMask)
	{
		mDayMask = dayMask;
	}

	bool RecurringTime::availableOnAny(unsigned int dayMask)
	{
		return dayMask & mDayMask;
	}

	bool RecurringTime::availableOnAll(unsigned int dayMask)
	{
		return (dayMask & mDayMask) == dayMask;
	}
}
