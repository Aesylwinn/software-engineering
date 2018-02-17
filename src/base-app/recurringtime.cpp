#include "recurringtime.h"

namespace base {
	RecurringTime::RecurringTime()
	{
		reset();
		// Use defaults
	}

	RecurringTime::RecurringTime(unsigned int daysAvailable, int hour, int minute)
	{
		reset();
		// Set properties
		setHour(hour);
		setMinute(minute);
		setAvailableDays(daysAvailable);
	}

	RecurringTime::RecurringTime(QString formattedString)
	{
		fromString(formattedString);
	}

	void RecurringTime::reset() {
		setHour(0);
		setMinute(0);
		setAvailableDays(0);
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
		// String should be in form: -M-W-F-
		QString buffer("-------");
		if (availableOnAny(Sunday))
			buffer[0] = 'S';
		if (availableOnAny(Monday))
			buffer[1] = 'M';
		if (availableOnAny(Tuesday))
			buffer[2] = 'T';
		if (availableOnAny(Wednesday))
			buffer[3] = 'W';
		if (availableOnAny(Thursday))
			buffer[4] = 'R';
		if (availableOnAny(Friday))
			buffer[5] = 'F';
		if (availableOnAny(Saturday))
			buffer[6] = 'S';
		// Final result
	    return buffer;
	}

	void RecurringTime::setHour(int hour)
	{
		mHour = hour % 24;
	}

	void RecurringTime::setMinute(int min)
	{
		mMinute = min % 60;
	}

	void RecurringTime::setAvailableDays(int dayMask)
	{
		mDayMask = dayMask & AllDays;
	}

	void RecurringTime::enableDays(int dayMask)
	{
		mDayMask |= dayMask & AllDays;
	}

	void RecurringTime::disableDays(int dayMask)
	{
		mDayMask &= ~dayMask;
	}

	bool RecurringTime::availableOnAny(unsigned int dayMask)
	{
		return dayMask & mDayMask;
	}

	bool RecurringTime::availableOnAll(unsigned int dayMask)
	{
		dayMask &= AllDays;
		return (dayMask & mDayMask) == dayMask;
	}

	RecurringTime& RecurringTime::fromString(QString formattedString) {
		reset();
		// String should be in form: -M-W-F-.14:30
		// Validate format
		if (formattedString.size() == 13 && formattedString[7] == '.' &&
				formattedString[10] == ':') {
			// Set days
			if (formattedString[0] == 'S')
				enableDays(Sunday);
			if (formattedString[1] == 'M')
				enableDays(Monday);
			if (formattedString[2] == 'T')
				enableDays(Tuesday);
			if (formattedString[3] == 'W')
				enableDays(Wednesday);
			if (formattedString[4] == 'R')
				enableDays(Thursday);
			if (formattedString[5] == 'F')
				enableDays(Friday);
			if (formattedString[6] == 'S')
				enableDays(Saturday);
			// Convert hours to int and set
			QStringRef hourStr(&formattedString, 8, 2);
			bool ok = false;
			int hour = hourStr.toInt(&ok);
			if (ok)
				setHour(hour);
			// Convert minutes to int and set
			QStringRef minuteStr(&formattedString, 11, 2);
			int minute = minuteStr.toInt(&ok);
			if (ok)
				setMinute(minute);
		}

		return *this;
	}

	QString RecurringTime::toString()
	{
		// String should be in the form: -M-W-F-.02:35
		QString result;
		result.append(getDays());
		result.append('.');
		result.append(QString("%1").arg(getHour(), 2, 10, QChar('0')));
		result.append(':');
		result.append(QString("%1").arg(getMinute(), 2, 10, QChar('0')));
		return result;
	}
}
