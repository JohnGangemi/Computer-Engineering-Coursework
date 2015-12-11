// John Gangemi
// Raymond Lian
#include "Hand.h"
#include <stdexcept>


Hand::Hand()
:hand_value(0), hand_status(Status::play) // initialize data members
{
}


Hand::~Hand()
{
}


void Hand::addCard(const BJCard &card_object)
{
	hand.push_back(card_object); // insert a BJCard object to vector
	setHandValue(card_object.getRankValue()); // update numerical value for contents of vector
}


void Hand::pullCard()
{
	if (!hand.empty())
	{
		setHandValue(hand.back().getRankValue() * -1); // update numerical value for contents of vector
		hand.pop_back(); // remove last BJCard object
	}
	else
		throw std::invalid_argument("No cards in hand to remove");
}


BJCard &Hand::referenceCard(const unsigned int &card_location)
{
	if (card_location >= 0 && card_location < hand.size())
	{
		 return this->hand[card_location];
	}
	else
		throw std::invalid_argument("BJCard does not exist within the hand");
}


void Hand::setHandValue(const int &value)
{
	// assign appropriate numerical value based on BJCard object's rank
	if (value == 1 && hand_value >= 11 || value >= 2 && value <= 10)
		hand_value += value;
	else if (value == 1 && hand_value < 11)
		hand_value += 11;
	else if (value >= 11 && value <= 13)
		hand_value += 10;
	else if (value == -1 && hand_value > 11 || value <= -2 && value >= -10)
		hand_value += value;
	else if (value == -1 && hand_value <= 11)
		hand_value += -11;
	else if (value <= -11 && value >= -13)
		hand_value += -10;
	else
		throw std::invalid_argument("Face value of BJCard is not within scope of standard BJDeck");

}


void Hand::setHandStatus(const Status &state)
{
	hand_status = state;
}


Status Hand::getHandStatus() const
{
	return hand_status;
}


unsigned int Hand::getHandValue() const
{
	return hand_value;
}


unsigned int Hand::getHandSize() const
{
	return hand.size();
}
