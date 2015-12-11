// John Gangemi
// Raymond Lian
#include "Holdem.h"
#include <math.h>
#include <random>
#include <string>
#include <iostream>
using namespace std;


holdem::holdem()
{
}


holdem::~holdem(void)
{
}
Player holdem:: dealHand(){
	gameDeck.shuffleFullDeck();
	Card dealerPckt1, dealerPckt2;
	Card UserPckt1, UserPckt2;

	dealerPckt1 = gameDeck.dealCard();
	dealerPckt2 = gameDeck.dealCard();
	UserPckt1 = gameDeck.dealCard();
	UserPckt2 = gameDeck.dealCard();

	dealer.setPocket(dealerPckt1, dealerPckt2);
	user.setPocket(UserPckt1, UserPckt2);
	return dealer;
	return user;

}
void holdem:: dealFlop(){
	Card flop1, flop2,flop3;

	flop1 = gameDeck.dealCard();
	flop2 = gameDeck.dealCard();
	flop3 = gameDeck.dealCard();
	tbCard1 = flop1;
	tbCard2 = flop2;
	tbCard3 = flop3;
	dealer.setFlop(tbCard1,tbCard2,tbCard3);
	user.setFlop(tbCard1,tbCard2,tbCard3);
	

}
void holdem:: dealTurn(){
	Card flop1;

	flop1 = gameDeck.dealCard();
	tbCard4 = flop1;
	dealer.setTurn(tbCard4);
	user.setTurn(tbCard4);
}
void holdem:: dealRiver(){
	Card flop1;
	
	flop1 = gameDeck.dealCard();
	tbCard5 = flop1;
	dealer.setRiver(tbCard4);
	user.setRiver(tbCard5);
	

}
void holdem:: printRound1(){
	cout<<"Cards on Table "<< tbCard1.toString() << " "<< tbCard2.toString() << " "<< tbCard3.toString() <<endl;
}
void holdem:: printRound2(){
	cout<<"Cards on Table "<< tbCard1.toString() << " "<< tbCard2.toString() << " "<< tbCard3.toString() << " "<< tbCard4.toString() <<endl;
}
void holdem:: printRound3(){
	cout<<"Cards on Table "<< tbCard1.toString() << " "<< tbCard2.toString() << " "<< tbCard3.toString()<< " "<< tbCard4.toString() << " "<< tbCard5.toString() <<endl;
}
void holdem:: shuffleDeck(){
	gameDeck.shuffleFullDeck();
	
}