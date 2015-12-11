// John Gangemi
// Raymond Lian
#ifndef BJPLAYER_H
#define BJPLAYER_H

#include "Hand.h" // has-a relationship
#include <iostream>
#include <vector>

// represents derived objects
enum Type{dealer, gambler}; 

// abstract base class
class BJPlayer
{
public:
	BJPlayer();
	virtual ~BJPlayer(); // virtual destructor

	/////////////////////////////
	// pure virtual functions //
	///////////////////////////
	virtual std::ostream &print(std::ostream &out) const = 0; // interface for non-member overloaded extraction operator function
	virtual void setObjectIdentifier() = 0; // sets identifier of derived objects, used when order of objects in a container is unknown
	
	//////////////////////////////////////////////////////
	// dealer object redefines these virtual functions //
	////////////////////////////////////////////////////
	virtual void setFlipCard(const bool &expression); // changes visual state of dealer's first card
	virtual bool getFlipCard() const; // return visual state of dealer's first card

	////////////////////////////////////////////////////////
	// gambler objects redefines these virtual functions //
	//////////////////////////////////////////////////////
	virtual bool canSplit(const unsigned int &split_hand) const; // check if gambler can split a hand
	virtual void split(const unsigned int &split_hand); // split specified hand for gambler
	virtual void setBet(); // set bet for gambler's hand
	virtual unsigned int getBet(const unsigned int &hand) const; // return bet of a gambler's hand
	
	///////////////////////////////////
	// non-virtual member functions //
	/////////////////////////////////
	unsigned int getNumberOfHands() const; // return number of dynamically allocated hands
	void checkPlayersHand(const unsigned int &hand); // check for critical states of a hand
	Type getObjectIdentifier() const; // return the identifier for a derived object
	Hand &playHand(const unsigned int &hand); // return reference to a player's hand

protected:
	///////////////////
	// data members //
	/////////////////
	Type object_id; // store the object identifier for a derived class
	std::vector<Hand*> players_hands; // store pointers of hand objects
};


////////////////////////////////////////////////////////////////////////////
// non-member function overloads extraction operator for derived classes //
//////////////////////////////////////////////////////////////////////////
inline std::ostream &operator<<(std::ostream &out, const BJPlayer &object)
{
	return object.print(out);
}

#endif