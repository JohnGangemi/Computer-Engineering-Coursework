// John Gangemi
// Raymond Lian
#include "Deck.h"
#include <stdexcept>
#include <ctime>


Deck::Deck()
:next_card(0)
{
	for (unsigned int i = 1; i <= 13; ++i)
	{
		for (unsigned int j = 1; j <= 4; ++j)
			english_deck.push_back(Card(i, j));
	}
}


Deck::~Deck()
{
}


Card Deck::dealCard()
{
	const unsigned int this_card = next_card;
	++next_card;
    
	if (this_card < english_deck.size())
		return english_deck[this_card];
	else
		throw std::invalid_argument("Cannot deal more than 52 cards");
    
}


void Deck::shuffleFullDeck()
{
	Card temp;
	srand(unsigned(time(NULL)));
    
	if (next_card != 0)
		next_card = 0;
    
	for (unsigned int i = next_card; i < english_deck.size(); ++i)
	{
		unsigned int random = rand() % english_deck.size();
        
		if (i != random)
		{
			temp = english_deck[i];
			english_deck[i] = english_deck[random];
			english_deck[random] = temp;
		}
	}
}


void Deck::shuffleRemainingDeck()
{
	Card temp;
	srand(unsigned(time(NULL)));
    
	for (unsigned int i = next_card; i < english_deck.size(); ++i)
	{
		unsigned int random = rand() % english_deck.size();
        
		if (i != random)
		{
			temp = english_deck[i];
			english_deck[i] = english_deck[random];
			english_deck[random] = temp;
		}
	}
}


const bool Deck::moreCards()
{
	if (next_card < english_deck.size())
		return true;
	else
		return false;
}

//Holdem possible combination check