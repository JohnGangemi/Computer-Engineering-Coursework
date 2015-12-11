// John Gangemi
// Raymond Lian
#include "Card.h"
#include <stdexcept>
#include <iostream>

const std::array<std::string, 13> Card::ranks =
{"Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
    "Nine", "Ten", "Jack", "Queen", "King", "Ace" };

const std::array<std::string, 4> Card::orders =
{ "Clubs", "Diamonds", "Hearts", "Spades" };


Card::Card(const unsigned int &face, const unsigned int &suit)
{
	if ((face >= 1 && face <= 13 )|| (suit >= 1 && suit <= 4))
	{
		rank = face;
		order = suit;
	}
  else{
		throw std::invalid_argument("Card is not defined in a standard 52 deck");
  }
}


Card::~Card()
{
}

Card &Card::operator=(const Card &operand2)
{
 if( this != &operand2)
 {
     rank = operand2.rank;
     order = operand2.order;
 }
    return *this;
}
void Card:: setFace(int x){
	rank = x;
}
const unsigned int Card::getFaceValue()
{
	return rank;
}


const unsigned int Card::getSuitValue()
{
	return order;
}


const std::string Card::toStringFace()
{
	return ranks[rank - 1];
}
const std::string Card::toString()
{
	return ranks[rank - 1] + " of " + orders[order - 1];
}