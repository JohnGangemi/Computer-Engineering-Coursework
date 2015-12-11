#include <iostream>
#include <stdexcept>
#include "Point.h"
using namespace std;

Point::Point(const double &horizontal, const double &vertical)
{
	if ((horizontal >= 0 && horizontal <= 20.0) && (vertical >= 0 && vertical <= 20.0))
	{
		x = horizontal;
		y = vertical;
	}
	else
		throw invalid_argument("Not a valid point.");
}

const double Point::getX()
{
	return x;
}

const double Point::getY()
{
	return y;
}