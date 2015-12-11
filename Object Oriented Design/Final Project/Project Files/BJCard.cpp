// John Gangemi
#include "BJCard.h"
#include <stdexcept>

const std::array<std::string, 13> BJCard::ranks_str =
{ "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
"Nine", "Ten", "Jack", "Queen", "King" };

const std::array<std::string, 4> BJCard::suits_str =
{ "Clubs", "Diamonds", "Hearts", "Spades" };


BJCard::BJCard(const Ranks &rank_name, const Suits &suit_name)
:rank(rank_name), suit(suit_name) // initialize data members
{
}


BJCard::~BJCard()
{
}


Ranks BJCard::getRank() const
{
	return rank;
}


Suits BJCard::getSuit() const
{
	return suit;
}


unsigned int BJCard::getRankValue() const
{
	return (unsigned int)rank + 1;
}


unsigned int BJCard::getSuitValue() const
{
	return (unsigned int)suit + 1;
}

 
std::string BJCard::toString() const
{
	return ranks_str[(unsigned int)rank] + " of " + suits_str[(unsigned int)suit];
}


BJCard &BJCard::operator=(const BJCard &object)
{
	// avoid self assignment
	if (this != &object)
	{
		rank = object.rank;
		suit = object.suit;
	}

	return *this; // return reference to this pointer for cascading
}
