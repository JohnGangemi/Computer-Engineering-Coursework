// John Gangemi
// Raymond Lian
#ifndef BJDECK_H
#define BJDECK_H

#include "Hand.h"

class BJDeck : public Hand // is-a relationship
{
public:
	BJDeck(); // construct a BJDeck object
	~BJDeck();

	void createDeck(); // assemble a BJDeck of BJCard objects
	void shuffleDeck(); // randomly order BJCard objects
	BJCard dealCard(); // return a BJCard object
	bool moreCards() const; // check the number of BJCard objects 

private:
	static unsigned int deck_size; // store number of BJCard objects
};

#endif