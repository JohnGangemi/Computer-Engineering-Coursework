// Raymond Lian
#ifndef HOLDEM_H
#define HOLDEM_H

#include "Deck.h"
#include "Card.h"
#include "Player.h"

class holdem
{
	
public:
	holdem();
	~holdem(void);
	Player dealHand();
	void dealFlop();
	void dealTurn();
	void dealRiver();
	void shuffleDeck();
	void whoWins();
	void printRound1();
	void printRound2();
	void printRound3();

private:
	int winnerID;
	int currentPot;
	Player user;
	Player dealer;
	Deck gameDeck;
	Card tbCard1, tbCard2, tbCard3, tbCard4, tbCard5;
};

#endif