#include "AGKTime.h"
#include "agk.h"

AGKTime::AGKTime()
{
}

AGKTime::~AGKTime()
{
}

//Returned format is YYYY-MM-DD
Text AGKTime::GetCurrentDate(void)
{
	return Text(agk::GetCurrentDate());
}

//Returned format is HH:MM:SS
Text AGKTime::GetCurrent(void)
{
	return Text(agk::GetCurrentTime());
}

//0 = Sunday, 6 = Saturday
unsigned short AGKTime::GetDayOfWeek(void)
{
	return agk::GetDayOfWeek();
}

//Gets Day Value from Unix
//unixTime is generated with GetUnixFromDate call
//returns 1-31, can be negative
short AGKTime::GetDaysFromUnix(int unixTime)
{
	return agk::GetDaysFromUnix(unixTime);
}

//Gets Hour Value from Unix
//unixTime is generated with GetUnixFromDate call
//returns 0-23, can be negative
short AGKTime::GetHoursFromUnix(int unixTimeValue)
{
	return agk::GetHoursFromUnix(unixTimeValue);
}

//Returns true if argument year is a leap year
bool AGKTime::GetLeapYear(unsigned short year)
{
	if (agk::GetLeapYear(year))
		return true;

	return false;
}

//Returns Minutes Value from Unix
//unixTimeValue is generated with GetUnixFromDate call
//returns 0-59, can be negative
short AGKTime::GetMinutesFromUnix(int unixTimeValue)
{
	return agk::GetMinutesFromUnix(unixTimeValue);
}

//Returns Month Value from Unix
//unixTimeValue is generated with GetUnixFromDate call
//returns 1-12, can be negative
short AGKTime::GetMonthFromUnix(int unixTimeValue)
{
	return agk::GetMonthFromUnix(unixTimeValue);
}

//Returns Seconds Value from Unix
//unixTimeValue is generated with GetUnixFromDate call
//return 0-59, can be negative
short AGKTime::GetSecondsFromUnix(int unixTimeValue)
{
	return agk::GetSecondsFromUnix(unixTimeValue);
}

//Returns unixTimeValue
int AGKTime::GetUnixFromDate(unsigned short year, unsigned short month, unsigned short days, unsigned short hours, unsigned short minutes, unsigned short seconds)
{
	return agk::GetUnixFromDate(year, month, days, hours, minutes, seconds);
}

//Returns Year Value from Unix
//unixTimeValue is generated with GetUnixFromDate call
//returns year
unsigned int AGKTime::GetYearFromUnix(int unixTimeValue)
{
	return agk::GetYearFromUnix(unixTimeValue);
}