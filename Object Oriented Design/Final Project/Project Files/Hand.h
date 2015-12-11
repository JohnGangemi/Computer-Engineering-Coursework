// John Gangemi
#ifndef HAND_H
#define HAND_H

#include "BJCard.h" // has-a relationship
#include <vector>

// represents status of hand object
enum Status{ play, stand, push, bust, doubleDown, surrender, twentyOne, blackJack }; 

class Hand
{
public:
	Hand(); // construct a hand object
	~Hand();

	void addCard( const BJCard &card_object); // add a BJCard object to vector
	void pullCard(); // remove last BJCard object from vector
	BJCard &referenceCard(const unsigned int &card_location); // return referenced BJCard object

	void setHandStatus(const Status &state); // change the status of a hand object
	Status getHandStatus() const; // return the status of a hand object
	unsigned int getHandValue() const; // return the numerical value of BJCard objects
	unsigned int getHandSize() const; // return the number of BJCard objects

private:
	void setHandValue(const int &value); // change the numerical value of BJCard objects

	int hand_value; // store the numerical value of BJCard objects
	Status hand_status; // store the status of a hand object
	std::vector<BJCard> hand; // store BJCard objects
};

#endif