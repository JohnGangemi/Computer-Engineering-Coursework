// John A. Gangemi U6871-4612
// Exercise 9.18 Solution: Ex09_12.cpp
#include <iostream>
#include <stdexcept>
#include "Rectangle.h" 
#include "Point.h"
using namespace std;

int main()
{
	Point w(1.0, 1.0);
	Point x(5.0, 1.0);
	Point y(5.0, 3.0);
	Point z(1.0, 3.0);
	Point j(0.0, 0.0);
	Point k(1.0, 0.0);
	Point m(1.0, 1.0);
	Point n(0.0, 1.0);

	Rectangle r1(z, y, x, w);
	cout << "Rectangle 1:\n";
	cout << "length = " << r1.length();
	cout << "\nwidth = " << r1.width();
	cout << "\nperimeter = " << r1.perimeter();
	cout << "\narea = " << r1.area();
	cout << "\nThe rectangle "
		<< (r1.square() ? "is" : "is not")
		<< " a square.\n";

	Rectangle r2(j, k, m, n);
	cout << "\nRectangle 2:\n";
	cout << "length = " << r2.length();
	cout << "\nwidth = " << r2.width();
	cout << "\nperimeter = " << r2.perimeter();
	cout << "\narea = " << r2.area();
	cout << "\nThe rectangle "
		<< (r2.square() ? "is" : "is not")
		<< " a square.\n";

	try
	{
		Rectangle r3(w, x, m, n);
	}
	catch (invalid_argument &e)
	{
		cout << "\nException: " << e.what() << endl;
	}

	try
	{
		Point v(99.0, -2.3);
	}
	catch (invalid_argument &e)
	{
		cout << "\nException: " << e.what() << endl;
	}

	cout << endl;
	system("PAUSE");
	return 0;
} // end main
