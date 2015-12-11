#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Time.h"

using namespace std;

Time::Time(int hour, int minute, int second)
{
	setTime(hour, minute, second);
}

void Time::setTime(const int &h, const int &m, const int &s)
{
	setHour(h);
	setMinute(m);
	setSecond(s);
}

void Time::setHour(const int &h)
{
	if (h >= 0 && h < 24)
		hour = h;
	else if (h >= 24)
	{
		hour = h % 24; // reset the hour to interval 1-24
	}
	else
		throw invalid_argument("hour must be 1-24");
}

void Time::setMinute(const int &m)
{
	if (m >= 0 && m < 60)
		minute = m;
	else if (m >= 60) // check for values larger than 60 minutes
	{
		minute = m % 60; // set minute to the remainder of division
		setHour(getHour() + (m / 60)); // add the integer of division to the hour member
	}
	else
		throw invalid_argument("minute must be 0-59"); 
}

void Time::setSecond(const int &s)
{
	if (s >= 0 && s < 60)
		second = s;
	else if (s >= 60) // check for values larger than 60 seconds
	{
		second = s % 60; // set second to the remainder of division
		setMinute(getMinute() + (s / 60)); // add the integer of division to the minute member
	}
	else
		throw ("second must be 0-59");
}

int Time::getHour()
{
	return hour;
}

int Time::getMinute()
{
	return minute;
}

int Time::getSecond()
{
	return second;
}

void Time::printUniversal()
{
	cout << setfill('0') << setw(2) << getHour() << ":"
		<< setw(2) << getMinute() << ":" << setw(2) << getSecond();
}

void Time::printStandard()
{
	cout << ((getHour() == 0 || getHour() == 12) ? 12 : getHour() % 12)
		<< ":" << setfill('0') << setw(2) << getMinute()
		<< ":" << setw(2) << getSecond() << (getHour() < 12 ? " AM" : " PM");
}

void Time::tick()
{
	// increment the time by one second
	setSecond(getSecond() + 1);
}