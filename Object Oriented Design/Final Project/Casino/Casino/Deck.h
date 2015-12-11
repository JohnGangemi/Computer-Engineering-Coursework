// John Gangemi
// Raymond Lian
#pragma once
#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>

class Deck
{
public:
	Deck();
	~Deck();
	Card dealCard();
	void shuffleFullDeck();
	void shuffleRemainingDeck();
	const bool moreCards();
   
private:
	unsigned int next_card;
	std::vector<Card> english_deck;
};

#endif