// John Gangemi
// Raymond Lian
#include "BJDeck.h"
#include <stdexcept>
#include <ctime>


unsigned int BJDeck::deck_size = 52;


BJDeck::BJDeck()
:Hand()
{
	createDeck();
	shuffleDeck();
}


BJDeck::~BJDeck()
{
}


void BJDeck::createDeck()
{
	// iterating Rank and Suit enumerations to create 52 BJCard objects
	for (Ranks rank_itr = Ace; rank_itr <= King; rank_itr = Ranks(rank_itr + 1))
	{
		for (Suits suit_itr = Clubs; suit_itr <= Spades; suit_itr = Suits(suit_itr + 1))
		{
			addCard(BJCard(rank_itr, suit_itr));
		}
	}
}


void BJDeck::shuffleDeck()
{
	BJCard temp_card(Ace,Clubs);
	std::srand((unsigned)time(NULL));

	for (unsigned int i = 0; i < getHandSize(); ++i)
	{
		unsigned int random_num = rand() % getHandSize();

		if (i != random_num)
		{
			temp_card = referenceCard(i);
			referenceCard(i) = referenceCard(random_num);
			referenceCard(random_num) = temp_card;
		}
	}
}


BJCard BJDeck::dealCard()
{
	if (!moreCards())
	{
		createDeck();
		shuffleDeck();
	}

	BJCard top_card = referenceCard(deck_size - 1); // create a local BJCard object 
	pullCard(); // remove from vector the last BJCard object
	--deck_size; // decrement static counter

	return top_card; // return local BJCard object
}


bool BJDeck::moreCards() const
{
	if (getHandSize() > 0)
		return true;
	else
		return false;
}