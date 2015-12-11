#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Point.h"

class Rectangle
{
public:
	// constructor with objects of point class as function arguments
	Rectangle(Point &, Point &, Point &, Point &);
	// utility member functions
	const double length();
	const double width();
	const double perimeter();
	const double area();
	// predicate functions
	bool square(); // check if the given length and width are equal
private:
	// set function not accessible to user
	const void setCoordinates(Point &, Point &, Point &, Point &); // check points from constructor
	// member objects of Point class
	Point p1; // point class object
	Point p2; // point class object
	Point p3; // point class object
	Point p4; // point class object
};

#endif