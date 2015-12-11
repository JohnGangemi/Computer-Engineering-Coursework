#ifndef TIME_H
#define TIME_H

class Time
{
public:
	Time(int = 0, int = 0, int = 0); // constructor with default initializers

	void setTime(const int &, const int &, const int&); // initialize setHour, setMinute, and setSecond
	void setHour(const int &); // set value for private data member hour
	void setMinute(const int &); // set value for private data member minute
	void setSecond(const int &); // set value for private data member second

	int getHour(); // get the value stored in the private data member hour
	int getMinute(); // get the value stored in the private data member minute
	int getSecond(); // get the value stored in the private data member second

	void printUniversal(); // print the time in "military" format
	void printStandard(); // print the time in standard format

	// tick function added
	void tick(); // increment the time by one second
private:
	int hour;
	int minute;
	int second;
};

#endif