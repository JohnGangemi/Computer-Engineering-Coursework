#ifndef CARD_H
#define CARD_H
#include <array>
#include <string>

class Card
{
public:
	Card(const unsigned int & = 1, const unsigned int & = 1); // constructor with parameter assignment => default constructor
	std::string toString(); // return a string representing a card
private:
	unsigned int face; // represent face value
	unsigned int suit; // represent suit value
	static const std::array<std::string, 13> faces;
	static const std::array<std::string, 4> suits;
};

#endif