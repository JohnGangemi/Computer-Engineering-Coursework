// John A. Gangemi u6871-4612
// Exercise 9.19 Solution: ex09_19.cpp
// Driver program for class Date.
#include <iostream> 
#include <stdexcept>
#include "Date.h" // include Date class definition
using namespace std;

int main()
{
	try
	{
		Date date1(256, 1999); // initialize using ddd yyyy format 
		Date date2(3, 25, 04); // initialize using mm/dd/yy format
		Date date3("September", 1, 2000); // "month" dd, yyyy format
		Date date4; // initialize to current date with default constructor

		// print Date objects in default format
		date1.print();
		date2.print();
		date3.print();
		date4.print();
		cout << '\n';

		// print Date objects in 'ddd yyyy' format
		date1.printDDDYYYY();
		date2.printDDDYYYY();
		date3.printDDDYYYY();
		date4.printDDDYYYY();
		cout << '\n';

		// print Date objects in 'mm/dd/yy' format
		date1.printMMDDYY();
		date2.printMMDDYY();
		date3.printMMDDYY();
		date4.printMMDDYY();
		cout << '\n';

		// print Date objects in '"month" d, yyyy' format
		date1.printMonthDDYYYY();
		date2.printMonthDDYYYY();
		date3.printMonthDDYYYY();
		date4.printMonthDDYYYY();
		cout << endl;
	}
	catch (invalid_argument &e)
	{
		cout << "\nException: " << e.what() << endl;
	}

	system("PAUSE");
	return 0;
} // end main
