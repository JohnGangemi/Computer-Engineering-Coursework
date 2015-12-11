#ifndef DATE_H
#define DATE_H

class Date
{
public:
	static const unsigned int monthsPerYear = 12; // months in a year
	Date(); // default constructor that sets system date
	Date(int, int); // ddd yyyy constructor
	Date(int, int, int); // mm dd yy constructor
	Date(std::string, int, int); // Month, dd yyyy constructor
	const void print(); // print date in month/day/year format
	const void printDDDYYYY(); // print date in days year format
	const void printMMDDYY(); // print date in month/day/abbreviated year format
	const void printMonthDDYYYY(); // print date in string month/day/year format
private:
	unsigned int month; // 1-12 (January-December)
	unsigned int day; // 1-31 based on month
	unsigned int year; // any year

	// utility function to check if day is proper for month and year
	const unsigned int checkDay(int);
};

#endif