#ifndef POINT_H
#define POINT_H

class Point
{
public:
	// parameters with assignment => default constructor
	Point(const double & = 1, const double & = 1);
	// get member functions
	const double getX();
	const double getY();
private:
	double x; // store the value for the horizontal axis
	double y; // store the value for the vertical axis
};

#endif