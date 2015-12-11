// Raymond Lian
#ifndef PLAYER_H
#define PLAYER_H

#include "Deck.h"
#include "Card.h"
#include <string>
using namespace std;

class Player
{
	friend class holdem; 
public:
	Player();
	Player(Card, Card, Card, Card, Card, Card, Card, int,string,int, int);
	Player( int,string,int, int);
	~Player(void);
	
	bool operator>(const Player &) const;
	bool operator==(const Player &) const;

	int getPlayerCombo();
	int getPlayerStr();
	void setPlayerCombo(int);
	void setPlayerStr( int);
	int getPlayerID();
	void setPlayerID(int);
	int getPlayerChips();
	void setPlayerChips(int);
	void winChips(int);
	void loseChips(int);
	void setHandOrder();
	void checkFor1Pair();
	void checkFor2Pair();
	void checkForPairs();
	void checkForFlush();
	void checkForFullHouse();
	void checkFor4Kind();
	void checkForStraight();
	void checkFor3Kind();
	void resetPlayer();
	void highestHand();
	
	void setPocket( Card, Card);
	void setFlop(Card, Card, Card);
	void setTurn(Card);
	void setRiver(Card);


	unsigned int get_1stPair();
	unsigned int get_2ndPair();
	unsigned int get_Value1stPair();
	unsigned int get_Value2ndPair();
	unsigned int get_Flush();
	int getFlushStr();
	string getName();
	void print();
	void printBestCombo();
	void printHand();
	void printFlop();
	void printTurn2();
	void printTurn3();

protected:
	
	int highestFace;
	int setStrength;
	Card highestKicker;
	int player_chip;

	int playerStr;
	int playerID;
	//0: high card------ 1: pair---- 2:two pair--- 3: three of a kind -----4:straight----- 5:flush---- 6:Full house------ 7: four of a kind------ 8: straight flush
	int highestCombo;
	int comboSet;
	int strengthOfCombo;
	int strStraight;
	int strFlush;
	int str4Kind;
	int strFullHouse3;
	int strFullHouse2;
	int str3Kind;
	int str2Pair1st;
	int str2Pair2nd;
	int strPair;
	unsigned int first_Pair, second_Pair;
	unsigned int value_1stPair;
	unsigned int  value_2ndPair;
	bool isThereFlush;   //1 if there is, zero if there isnt.
	bool isThereFullHouse;
	bool isThere4kind;
	bool isThereStraight;
	bool isThere2Pair;
	bool isThere3kind;
	bool isThere1Pair;
	int flushValue;
	string player_Name;
	Card pocket1, pocket2, flop1, flop2, flop3, flop4, flop5;
	Card hold1, hold2;
};

#endif