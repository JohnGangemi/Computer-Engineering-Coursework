#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
#include "DeckOfCards.h"
using namespace std;

DeckOfCards::DeckOfCards()
:currentCard(0) // initialize private data member currentCard
{
	unsigned int index = 0;

	// initialize each Card object representing a deck of cards
	for (unsigned int i = 0; i < 13; ++i)
	{
		for (unsigned int j = 0; j < 4; ++j)
		{
			deck[index] = Card((i + 1), (j + 1));
			++index;
		}
	}
}

const void DeckOfCards::shuffle()
{
	Card temp; // temp object of card class
	srand(unsigned(time(NULL))); // seed the random number generation

	// iterate through the array of Card objects
	for (unsigned int i = 0; i < deck.size(); ++i)
	{
		unsigned int random = rand() % deck.size(); // random number

		// swap two Card objects from the array
		if (i != random) // unnecessary to swap the same object
		{
			temp = deck[i];
			deck[i] = deck[random];
			deck[random] = temp;
		}
	}
}

Card DeckOfCards::dealCard()
{
	unsigned int card_temp = currentCard;
	++currentCard;

	if (card_temp >= deck.size())
		throw invalid_argument("Card count exceeded the deck size");
	else
		return deck[card_temp];
}

bool DeckOfCards::moreCards()
{
	if (currentCard < deck.size())
		return true;
	else
		return false;
}