#include <array>
#include <cctype>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include "Date.h"
using namespace std;

Date::Date() // default constructor 
{

	// create an empty variable of type, 'time_t',
	// from the <ctime> class, capable of representing
	// time returned from time() function of <ctime>
	time_t rawtime; 

	// create an empty struct of type, 'tm',
	// from the <ctime> class, containing calendar date
	// and time components
	struct tm timeinfo; 

	// get the current date & time, then store data
	// in the variable of type 'time_t' passed by reference
	time(&rawtime);

	// use of non-depreciable function localtime_s() to
	// instantiate data members of struct
	localtime_s(&timeinfo, &rawtime);

	month = timeinfo.tm_mon + 1; // set private data member month
	day = timeinfo.tm_mday; // set private data member day
	year = timeinfo.tm_year + 1900; // set private data member year,
}

Date::Date(int d, int y) // ddd yyyy constructor
{
	bool isLeapYr = false;

	// set private data member year
	// assuming that a valid period for year is 100 year interval
	if (y >= 1916 && y <= 2015)
		year = y; 
	else
		throw invalid_argument("Year must be a number 1916-2015");

	// check if leap year
	if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
		isLeapYr = true;

	// check if number of days is valid
	if (d <= 0)
		throw invalid_argument("Day must be a number greater than 0");
	else if ((isLeapYr && d > 366) || (!isLeapYr && d > 365))
		throw invalid_argument("Too many days in the year");

	// set private data members day and month
	if (isLeapYr)
	{
		if (d <= 31)
		{
			month = 1;
			day = d;
		}
		else if (d > 31 && d <= 60)
		{
			month = 2;
			day = d - 31;
		}
		else if (d > 60 && d <= 91)
		{
			month = 3;
			day = d - 60;
		}
		else if (d > 91 && d <= 121)
		{
			month = 4;
			day = d - 91;
		}
		else if (d > 121 && d <= 152)
		{
			month = 5;
			day = d - 121;
		}
		else if (d > 152 && d <= 182)
		{
			month = 6;
			day = d - 152;
		}
		else if (d > 182 && d <= 213)
		{
			month = 7;
			day = d - 182;
		}
		else if (d > 213 && d <= 244)
		{
			month = 8;
			day = d - 213;
		}
		else if (d > 244 && d <= 274)
		{
			month = 9;
			day = d - 244;
		}
		else if (d > 274 && d <= 305)
		{
			month = 10;
			day = d - 274;
		}
		else if (d > 305 && d <= 335)
		{
			month = 11;
			day = d - 305;
		}
		else if (d > 335 && d <= 366)
		{
			month = 12;
			day = d - 335;
		}
	}
	else
	{
		if (d <= 31)
		{
			month = 1;
			day = d;
		}
		else if (d > 31 && d <= 59)
		{
			month = 2;
			day = d - 31;
		}
		else if (d > 59 && d <= 90)
		{
			month = 3;
			day = d - 59;
		}
		else if (d > 90 && d <= 120)
		{
			month = 4;
			day = d - 90;
		}
		else if (d > 120 && d <= 151)
		{
			month = 5;
			day = d - 120;
		}
		else if (d > 151 && d <= 181)
		{
			month = 6;
			day = d - 151;
		}
		else if (d > 181 && d <= 212)
		{
			month = 7;
			day = d - 181;
		}
		else if (d > 212 && d <= 243)
		{
			month = 8;
			day = d - 212;
		}
		else if (d > 243 && d <= 273)
		{
			month = 9;
			day = d - 243;
		}
		else if (d > 273 && d <= 304)
		{
			month = 10;
			day = d - 273;
		}
		else if (d > 304 && d <= 334)
		{
			month = 11;
			day = d - 304;
		}
		else if (d > 334 && d <= 365)
		{
			month = 12;
			day = d - 334;
		}
	}
}

Date::Date(int m, int d, int y) // mm dd yy constructor
{
	// set private data member month
	if (m > 0 && m <= monthsPerYear)
		month = m; 
	else
		throw invalid_argument("Month must be a number 1-12");

	//////////////////////////// PLEASE READ //////////////////////////////
	// Assuming the 20 to 21st century for abbreviated year, no possible // 
	// way to determine millennium/century from abbreviated year format! //
	///////////////////////////////////////////////////////////////////////

	// set private data member year
	if (y >= 0 && y < 100)
		// Handling the change in millennium
		if (y > 15)
			year = y + 1900;
		else if (y <= 15)
			year = y + 2000;
	else
		throw invalid_argument("Year must be a number 00-99");

	// set private data member day with function checkDay()
	day = checkDay(d); 
}

Date::Date(string m, int d, int y) // Month, dd yyyy constructor
{
	string month_lowercase = ""; 
	static const array<string, monthsPerYear> month_string =
	{"january", "february", "march", "april", "may", "june", "july", "august", 
	"september", "october", "november", "december"};

	// store each char of user entered string as lowercase
	for (unsigned int i = 0; i < m.size(); ++i)
		month_lowercase += tolower(m[i]);

	// compare user entered string to 'correct' strings in array
	for (unsigned int j = 0; j < month_string.size(); ++j)
	{
		if (month_lowercase == month_string[j])
		{
			// set private data member month
			month = (j + 1); 
			break;
		}

		if (month_lowercase != month_string[j] && (j == month_string.size() - 1))
			throw invalid_argument("Month must be of type \"January\", \"February\", etc...");
	}

	// set private data member year
	if (y >= 1916 && y <= 2015)
		year = y; 
	else
		throw invalid_argument("Year must be a number 1916-2015");

	// set private data member day with function checkDay()
	day = checkDay(d); 
}

const void Date::print()
{
	cout << setw(2) << setfill('0') << month << '/' << setw(2) << 
		setfill('0') << day << '/' << setw(4) << setfill('0') << 
		year << endl;
}

const void Date::printDDDYYYY()
{
	bool isLeapYr = false;
	unsigned int total_days = 0;
	static const array<int, monthsPerYear + 1> daysInMonth =
	{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	// sum the days in each month less than value of private data
	// member 'month'
	for (unsigned int i = 0; i < month; ++i)
		total_days += daysInMonth[i];

	// check for leap year
	if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
		isLeapYr = true;
	
	// add private data member day to total_days
	if (!isLeapYr || (isLeapYr && month < 2))
		total_days += day;
	else
		total_days += day + 1;

	cout << setw(3) << setfill('0') << total_days << " " << 
		setw(4) << setfill('0') << year << endl;
}

const void Date::printMMDDYY()
{
	if (year >= 100)
		cout << setw(2) << setfill('0') << month << '/' <<
		setw(2) << setfill('0') << day << '/' << setw(2) << setfill('0') <<
		year % 100 << endl;
	else
		cout << setw(2) << setfill('0') << month << '/' << 
		setw(2) << setfill('0') << day << '/' << setw(2) << setfill('0') <<
		year << endl;
}

const void Date::printMonthDDYYYY()
{
	static const array<string, monthsPerYear> months =
	{ "January", "February", "March", "April", "May", "June", "July", "August",
	"September", "October", "November", "December" };

	cout << months[month-1] << ", " << day << " " << setw(4) << setfill('0') << year << endl;
}

const unsigned int Date::checkDay(int testDay)
{
	static const array< int, monthsPerYear + 1 > daysPerMonth =
	{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	// determine whether testDay is valid for specified month
	if (testDay > 0 && testDay <= daysPerMonth[month])
		return testDay;

	// February 29 check for leap year 
	if (month == 2 && testDay == 29 && (year % 400 == 0 ||
		(year % 4 == 0 && year % 100 != 0)))
		return testDay;

	throw invalid_argument("Invalid day for current month and year");
}