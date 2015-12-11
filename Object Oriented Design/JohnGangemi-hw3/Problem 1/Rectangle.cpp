#include <iostream>
#include <array>
#include <stdexcept>
#include "Rectangle.h"
using namespace std;

Rectangle::Rectangle(Point &point_1, Point &point_2, Point &point_3, Point &point_4)
{
	setCoordinates(point_1, point_2, point_3, point_4);
}

const void Rectangle::setCoordinates(Point &p_1, Point &p_2, Point &p_3, Point &p_4)
{
	static const unsigned int array_size = 4; 
	int count_x = 0; // count the occurence of equivalence for x
	int	count_y = 0; // count the occurence of equivalence for y
	const array<double, array_size> x_vals = 
	{ p_1.getX(), p_2.getX(), p_3.getX(), p_4.getX() };
	const array<double, array_size> y_vals = 
	{ p_1.getY(), p_2.getY(), p_3.getY(), p_4.getY() };

	///////////////////////////////////////////////////////////////////////////////////////////
	// verify that each x-and-y component is in the first quadrant and not greater than 20.0 //
	///////////////////////////////////////////////////////////////////////////////////////////
	for (unsigned int i = 0; i < array_size; ++i)
		if ((x_vals[i] < 0 || x_vals[i] > 20.0) || (y_vals[i] < 0 || y_vals[i] > 20.0))
			throw invalid_argument("Not a valid set of points.");

	////////////////////////////////////////////////
	// verify the coordinates specify a rectangle //
	////////////////////////////////////////////////
	for (unsigned int i = 0; i < array_size; i++)
	{
		// iterate the horizontal axis
		if (x_vals[0] == x_vals[i])
			count_x++;
		else
		{
			for (unsigned int j = 0; j < array_size; j++)
				if ((i != j) && (x_vals[i] == x_vals[j]))
					count_x++;
		} 

		// iterate the vertical axis
		if (y_vals[0] == y_vals[i])
			count_y++;
		else
		{
			for (unsigned int j = 0; j < array_size; j++)
				if ((i != j) && (y_vals[i] == y_vals[j]))
					count_y++;
		}
	}
	
	if (count_x != 4 || count_y != 4)
		throw invalid_argument("Not a valid rectangle.");
	else
	{
		// set private data member objects
		p1 = p_1;
		p2 = p_2;
		p3 = p_3;
		p4 = p_4;
	}
}

const double Rectangle::length()
{
	static const unsigned int array_size = 4; // required size of array
	const array<double, array_size> x_vals = 
	{ p1.getX(), p2.getX(), p3.getX(), p4.getX() };
	const array<double, array_size> y_vals = 
	{ p1.getY(), p2.getY(), p3.getY(), p4.getY() };
	double max_x = 0.0;
	double min_x = 0.0;
	double max_y = 0.0;
	double min_y = 0.0;

	/////////////////////////////
	// find min and max values //
	/////////////////////////////
	min_x = x_vals[0]; // set a minimum value of x to random point x
	min_y = y_vals[0]; // set a minimum value of y to random point y
	for (unsigned int i = 1; i < array_size; i++)
	{
		if (x_vals[i] < min_x)
			min_x = x_vals[i];

		if (y_vals[i] < min_y)
			min_y = y_vals[i];
	} 

	for (unsigned int j = 0; j < array_size; j++)
	{
		if (x_vals[j] > min_x)
			max_x = x_vals[j];

		if (y_vals[j] > min_y)
			max_y = y_vals[j];
	} 

	/////////////////////////////////////////////////////////////////////////////
	// find the size of the sides of the rectangle and return the largest side //
	/////////////////////////////////////////////////////////////////////////////
	double side_a = (max_x - min_x);
	double side_b = (max_y - min_y);

	if (side_a >= side_b)
		return side_a;
	else
		return side_b;
}

const double Rectangle::width()
{
	static const unsigned int array_size = 4; // required size of array
	const array<double, array_size> x_vals = 
	{ p1.getX(), p2.getX(), p3.getX(), p4.getX() };
	const array<double, array_size> y_vals = 
	{ p1.getY(), p2.getY(), p3.getY(), p4.getY() };
	double max_x = 0.0;
	double min_x = 0.0;
	double max_y = 0.0;
	double min_y = 0.0;

	/////////////////////////////
	// find min and max values //
	/////////////////////////////
	min_x = x_vals[0]; // set a minimum value of x to random point x
	min_y = y_vals[0]; // set a minimum value of y to random point y
	for (unsigned int i = 1; i < array_size; i++)
	{
		if (x_vals[i] < min_x)
			min_x = x_vals[i];

		if (y_vals[i] < min_y)
			min_y = y_vals[i];
	}

	for (unsigned int j = 0; j < array_size; j++)
	{
		if (x_vals[j] > min_x)
			max_x = x_vals[j];

		if (y_vals[j] > min_y)
			max_y = y_vals[j];
	}

	//////////////////////////////////////////////////////////////////////////////
	// find the size of the sides of the rectangle and return the smallest side //
	//////////////////////////////////////////////////////////////////////////////
	double side_a = (max_x - min_x);
	double side_b = (max_y - min_y);

	if (side_a <= side_b)
		return side_a;
	else
		return side_b;
}

const double Rectangle::perimeter()
{
	return (2 * (length() + width()));
}

const double Rectangle::area()
{
	return (length() * width());
}

bool Rectangle::square()
{
	if (length() == width())
		return true;
	else
		return false;
}