#ifndef DECKOFCARDS_H
#define DECKOFCARDS_H
#include <array>
#include "Card.h"

class DeckOfCards
{
public:
	DeckOfCards(); // default constructor
	const void shuffle(); // shuffle the deck of cards
	Card dealCard(); // return the Card object pointed to by currentCard value
	bool moreCards(); // predicate function, check if there are more cards to be dealt
private:
	unsigned int currentCard; // represents next card to deal
	std::array<Card, 52> deck; // represents a deck of 52 cards
};

#endif