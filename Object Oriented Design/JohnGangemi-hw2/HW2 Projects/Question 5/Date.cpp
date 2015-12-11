#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Date.h"
using namespace std;

Date::Date(int m, int d, int y)
{
	setMonth(m);
	setDay(d);
	setYear(y);
}

void Date::setMonth(const int &m)
{
	if (m > 0 && m <= 12)
		month = m;
	else if (m > 12)
	{
		month = m % 12;
		setYear(getYear() + (m / 12));
	}
	else
		throw invalid_argument("Month must be greater than zero.");
}

void Date::setDay(const int &d)
{
	switch (getMonth())
	{
	case 2:
		if (isLeapYear())
		{
			if (d > 0 && d <= 29)
				day = d;
			else if (d > 29)
			{
				day = d % 29;
				setMonth(getMonth() + (d / 29));
			}
			else
				throw invalid_argument("Day must be greater than zero.");
		}
		else
		{
			if (d > 0 && d <= 28)
				day = d;
			else if (d > 28)
			{
				day = d % 28;
				setMonth(getMonth() + (d / 28));
			}
			else
				throw invalid_argument("Day must be greater than zero.");
		}
		break;

	case 4: case 6: case 9: case 11:
		if (d > 0 && d <= 30)
			day = d;
		else if (d > 30)
		{
			day = d % 30;
			setMonth(getMonth() + (d / 30));
		}
		else
			throw invalid_argument("Day must be greater than zero.");
		break;

	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		if (d > 0 && d <= 31)
			day = d;
		else if (d > 31)
		{
			day = d % 31;
			setMonth(getMonth() + (d / 31));
		}
		else
			throw invalid_argument("Day must be greater than zero.");
		break;

	default:
		break;
	}
}

void Date::setYear(const int &y)
{
	if (y > 0)
		year = y;
	else
		throw invalid_argument("Year must be greater than zero.");
}

int Date::getMonth()
{
	return month;
}

int Date::getDay()
{
	return day;
}

int Date::getYear()
{
	return year;
}

void Date::print()
{
	cout << setfill('0') << setw(2) << month << "/" << setw(2)
		<< day << "/" << setw(2) << year << endl;
}

void Date::nextDay()
{
	setDay(getDay() + 1);
}

bool Date::isLeapYear()
{
	if (getYear() % 400 == 0 || (getYear() % 4 == 0 && getYear() % 100 != 0))
		return true;
	else
		return false;
}