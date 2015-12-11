// John Gangemi
// Raymond Lian
#ifndef BJGAME_H
#define BJGAME_H

// John Gangemi
// Raymond Lian
#include "BJDeck.h"
#include "BJPlayer.h"
#include "Dealer.h"
#include "Gambler.h"

class BJGame
{
public:
	BJGame(const float &gambler_funds);
	~BJGame();

	void game(); // game loop for single round
	float getGameBalance() const; // return gambler's single round balance

protected:
	void setGameBalance(const float &amount); // set gambler's balance
	void placeBets(); // set the bet amount for gambler
	void dealTwo(); // deal two cards to dealer and gambler
	void gamblersTurn(const unsigned int &hand); // show game options for gambler
	void dealersTurn(); // dealer's game logic
	unsigned int validateOption(const unsigned int &number_of_options) const; // check user input
	void twoOptions(const unsigned int &hand); // options for gambler with more than two cards
	void threeOptions(const unsigned int &hand); // options for gambler with possible split and more than two cards
	void fourOptions(const unsigned int &hand); // options for gambler with two cards
	void fiveOptions(const unsigned int &hand); // options for gambler with two cards and possible split
	void calculateRound(); // calculate results of round and update gambler's balance
	bool isBlackjack(const unsigned int &hand) const; // check for two BJCard blackjack

private:
	float balance; // store gambler's round balance
	std::vector<BJPlayer*> players; // container for base class pointers
	BJDeck shoe; // represents a BJDeck of cards
};

#endif