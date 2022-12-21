#pragma once

#include "Text.h"

class AGKTime
{
public:
	AGKTime();
	~AGKTime();

	Text GetCurrentDate();
	Text GetCurrent();
	unsigned short GetDayOfWeek();
	short GetDaysFromUnix(int unixTime);
	short GetHoursFromUnix(int unixTime);
	bool GetLeapYear(unsigned short year);
	short GetMinutesFromUnix(int unixTime);
	short GetMonthFromUnix(int unixTime);
	short GetSecondsFromUnix(int unixTime);
	int GetUnixFromDate(unsigned short year, unsigned short month, unsigned short days, unsigned short hours, unsigned short minutes, unsigned short seconds);
	unsigned int GetYearFromUnix(int unixTime);
};