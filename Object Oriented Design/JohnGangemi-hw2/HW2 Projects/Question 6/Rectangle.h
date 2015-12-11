#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle
{
public:
	Rectangle(float = 1.0, float = 1.0);
	
	// set functions
	void setLength(float);
	void setWidth(float);

	// get functions
	float getLength();
	float getWidth();

	// utility functions
	float perimeter();
	float area();
private:
	float length;
	float width;
};

#endif