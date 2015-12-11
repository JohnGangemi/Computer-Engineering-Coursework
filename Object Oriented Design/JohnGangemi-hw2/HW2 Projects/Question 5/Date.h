#ifndef DATE_H
#define DATE_H

class Date
{
public:
	Date(int=1, int=1, int=2000); // constructor with default initializations

	// set functions
	void setMonth(const int &);
	void setDay(const int &);
	void setYear(const int &);

	// get functions
	int getMonth();
	int getDay();
	int getYear();

	// utility functions
	void print();
	void nextDay();
	bool isLeapYear(); // check if year is leap year
private:
	int month;
	int day;
	int year;
};

#endif