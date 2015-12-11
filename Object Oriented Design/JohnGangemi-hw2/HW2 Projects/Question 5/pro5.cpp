// John A. Gangemi U6871-4612
// Exercise 9.8 Solution: Ex09_08.cpp
#include <iostream> 
#include <stdexcept>
#include "Date.h" // include definitions of class Date
using namespace std;

int main()
{
	const unsigned int MAXDAYS = 16;
	try
	{
		Date d(12, 24, 2013); // instantiate object d of class Date

		// output Date object d's value
		for (unsigned int loop = 1; loop <= MAXDAYS; ++loop)
		{
			d.print(); // invokes function print
			d.nextDay(); // invokes function next day
		} // end for
	}
	catch (invalid_argument &e)
	{
		cout << "\nError: " << e.what() << endl;
	}

	cout << endl;

	system("PAUSE");
	return 0;
} // end main

/**************************************************************************
* (C) Copyright 1992-2014 by Deitel & Associates, Inc. and               *
* Pearson Education, Inc. All Rights Reserved.                           *
*                                                                        *
* DISCLAIMER: The authors and publisher of this book have used their     *
* best efforts in preparing the book. These efforts include the          *
* development, research, and testing of the theories and programs        *
* to determine their effectiveness. The authors and publisher make       *
* no warranty of any kind, expressed or implied, with regard to these    *
* programs or to the documentation contained in these books. The authors *
* and publisher shall not be liable in any event for incidental or       *
* consequential damages in connection with, or arising out of, the       *
* furnishing, performance, or use of these programs.                     *
**************************************************************************/