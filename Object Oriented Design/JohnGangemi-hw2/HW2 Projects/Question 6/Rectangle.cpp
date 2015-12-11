#include <iostream>
#include <stdexcept>
#include "Rectangle.h"
using namespace std;

Rectangle::Rectangle(float a, float b)
{
	setLength(a);
	setWidth(b);
}

void Rectangle::setLength(float len)
{
	if (len >= 0.0 && len < 20.0)
		length = len;
	else
		throw invalid_argument("Length must be 0-20.");
}

void Rectangle::setWidth(float wid)
{
	if (wid >= 0.0 && wid < 20.0)
		width = wid;
	else
		throw invalid_argument("Width must be 0-20.");
}

float Rectangle::getLength()
{
	return length;
}

float Rectangle::getWidth()
{
	return width;
}

float Rectangle::perimeter()
{
	return ((2 * getLength()) + (2 * getWidth()));
}

float Rectangle::area()
{
	return (getLength() * getWidth());
}