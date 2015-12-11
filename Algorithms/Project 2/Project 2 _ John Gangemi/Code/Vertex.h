#ifndef _VERTEX_H
#define _VERTEX_H

#include <string>

class Vertex
{
public:
	Vertex();

	void setId(int num);
	void setDiscovered(bool val);
	void setColor(char ch);
	void setDirection(std::string str);

	int getId();
	bool isDiscovered();
	char getColor();
	std::string getDirection();

private:
	int id;
	bool discovered;
	char color;
	std::string direction;
};

#endif

