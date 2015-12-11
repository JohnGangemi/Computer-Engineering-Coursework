// John Gangemi
// Raymond Lian
#include "Player.h"
#include <math.h>
#include <random>
#include<iostream>
using namespace std;

Player::Player()
{
}
Player::Player(Card hand1, Card hand2, Card board1 , Card board2 , Card board3 , Card board4 , Card board5, int x, string player, int combo, int strCb)
{
	pocket1= hand1;
	pocket2 = hand2;
	flop1 = board1;
	flop2 = board2;
	flop3 = board3;
	flop4 = board4;
	flop5 = board5;
	player_chip = x;
	player_Name = player; 
	highestCombo = combo;
	strengthOfCombo = strCb;
	value_1stPair = 0;
	value_2ndPair = 0;
	strFullHouse2=0;
	strFullHouse3=0;



}
Player::Player( int x, string player, int combo, int strCb)
{
	player_chip = x;
	player_Name = player; 
	highestCombo = combo;
	strengthOfCombo = strCb;

}
Player::~Player(void)
{
}

bool Player::operator>(const Player &operand2) const{
	if(highestCombo > operand2.highestCombo){
        return true;
    }
	else{
		return false;
	}
	if(highestCombo == operand2.highestCombo){
		if(highestCombo == 2){
			if(value_1stPair > operand2.value_1stPair){
				return true;
			}
			if(value_1stPair < operand2.value_1stPair){
				return false;
			}
			if(value_1stPair == operand2.value_1stPair){
				if(value_2ndPair > operand2.value_2ndPair){
					return true;
				}
				if(value_2ndPair < operand2.value_2ndPair){
					return false;
				}
			}
		}
		if(highestCombo == 6){
			if(strFullHouse3 > operand2.strFullHouse3){
				return true;
			}
			if(strFullHouse3 < operand2.strFullHouse3){
				return false;
			}
			if(strFullHouse3 == operand2.strFullHouse3){
				if(strFullHouse2 > operand2.strFullHouse2){
					return true;
				}
				if(strFullHouse2 < operand2.strFullHouse2){
					return false;
				}
			}

		}
		if(highestCombo == 1 && operand2.highestCombo ==1){
			if(strPair > operand2.strPair){
				return true;
			}
			else{
				return false;
			}
		}
		if(highestCombo == 3 && operand2.highestCombo ==3){
			if(str3Kind > operand2.str3Kind){
				return true;
			}
			else{
				return false;
			}
		}
		if(highestCombo == 4 && operand2.highestCombo ==4){
			if(strStraight> operand2.strStraight){
				return true;
			}
			else{
				return false;
			}
		}
		if(highestCombo == 5 && operand2.highestCombo ==5){
			if(strFlush> operand2.strFlush){
				return true;
			}
			else{
				return false;
			}
		}
		if(highestCombo == 7 && operand2.highestCombo ==7){
			if(str4Kind> operand2.str4Kind){
				return true;
			}
			else{
				return false;
			}
		}

	}
	


   
}

bool Player::operator==(const Player &operand2) const{
	if(highestCombo == operand2.highestCombo){
        return true;
    }
	else 
		return false;
}
void Player:: setPlayerCombo(int x){
	highestCombo = x;
}
void Player:: setPlayerStr(int x){
	playerStr = x;
}
void Player:: setPlayerID(int x){
	playerID = x;
}
int Player:: getPlayerID(){
	return playerID;
}
void Player:: setPlayerChips(int x){
	player_chip = x;
}
int Player:: getPlayerChips(){
	return player_chip;
}
void Player:: winChips(int x){
	player_chip = player_chip+ x;
}
void Player:: loseChips(int x){
	player_chip = player_chip- x;
}
void Player:: setPocket(Card first, Card second){
	pocket1 = first;
	pocket2 = second;
	hold1 = first;
	hold2 = second;
}
void Player:: setFlop(Card first, Card second, Card third){
	flop1 = first;
	flop2 = second;
	flop3 = third;
}
void Player:: setTurn(Card turn ){
	flop4 = turn;

}
void Player:: setRiver(Card river){
	flop5 = river;

}
void Player:: setHandOrder(){
	Card possibleCombo[7];
	possibleCombo[0]= pocket1;
	possibleCombo[1]= pocket2;
	possibleCombo[2]= flop1;
	possibleCombo[3]=flop2;
	possibleCombo[4]=flop3;
	possibleCombo[5]=flop4;
	possibleCombo[6]=flop5;
	Card hold;

	 for(int a=0; a<7;++a){
		 for(int x=0; x<6; ++x){
			 if(possibleCombo[x].getFaceValue() < possibleCombo[x+1].getFaceValue()){
				 hold = possibleCombo[x];
				 possibleCombo[x] = possibleCombo[x+1];
				 possibleCombo[x+1] = hold;
			 }

		 }
	 }
	pocket1=possibleCombo[0];
	pocket2=possibleCombo[1];
	flop1=possibleCombo[2];
	flop2=possibleCombo[3];
	flop3=possibleCombo[4];
	flop4=possibleCombo[5];
	flop5=possibleCombo[6];
	highestKicker = pocket1.getFaceValue();



}
void Player::checkFor4Kind(){
	if(first_Pair == 4){
		isThere4kind = true;
	}
	str4Kind = value_1stPair;
	
}
void Player::checkForFullHouse(){

	if((first_Pair == 3 && second_Pair == 2)){

		isThereFullHouse = true;
		strFullHouse3 = value_1stPair;
		strFullHouse2 = value_2ndPair;

	}
	if((first_Pair == 2 && second_Pair == 3)){

		isThereFullHouse = true;
		strFullHouse3 = value_2ndPair;
		strFullHouse2 = value_1stPair;
		
		
	}
	
	
}
void Player:: checkForFlush(){
	setHandOrder();
	Card possibleCombo[7];
	possibleCombo[0]= pocket1;
	possibleCombo[1]= pocket2;
	possibleCombo[2]= flop1;
	possibleCombo[3]=flop2;
	possibleCombo[4]=flop3;
	possibleCombo[5]=flop4;
	possibleCombo[6]=flop5;
	Card matching;
	int numOfSuits;
	int typeOfSuit;

	for (int x=0; x<7;++x){
		numOfSuits=1;
		matching = possibleCombo[x];
		for(int a=0; a<7;++a){
			if( matching.getSuitValue() == possibleCombo[a].getSuitValue() && a!=x ){
				++numOfSuits;
				if(numOfSuits > 3){
					typeOfSuit = matching.getSuitValue();
				}
			}
		}
		if (numOfSuits >= 5){
			isThereFlush = true;
			}
		if(possibleCombo[2].getSuitValue()== typeOfSuit){
			strFlush = possibleCombo[0].getFaceValue() + 1;
		}
		if(possibleCombo[1].getSuitValue()== typeOfSuit){
			strFlush = possibleCombo[0].getFaceValue() + 1 ;
		}
		
		if(possibleCombo[0].getSuitValue() == typeOfSuit){
			strFlush = possibleCombo[0].getFaceValue() + 1 ;
		}
		
		

	}


}

void Player::checkForStraight(){
	
	Card possibleCombo[7];
	setHandOrder();
	possibleCombo[0]= pocket1;
	possibleCombo[1]= pocket2;
	possibleCombo[2]= flop1;
	possibleCombo[3]=flop2;
	possibleCombo[4]=flop3;
	possibleCombo[5]=flop4;
	possibleCombo[6]=flop5;
	int inOrder=0;
	int row=0;
	int strengthOfStraight=0;
	int lead=0;
	int front=0, back=0;
	for(int x=0; x<3; ++x){
		row = x;
		inOrder=0;
		front = possibleCombo[x].getFaceValue();
		back = possibleCombo[x+1].getFaceValue();
		if((front - back)==1){
			++inOrder;
			++row;
			front = possibleCombo[row].getFaceValue();
			back = possibleCombo[row+1].getFaceValue();
			       if((front - back)==1||(front - back)==0){
					   if((front - back)==1){
			        ++inOrder;
					   }
			        ++row;
					front = possibleCombo[row].getFaceValue();
					back = possibleCombo[row+1].getFaceValue();
					      if((front - back)==1||(front - back)==0){
			                 if((front - back)==1){
			        ++inOrder;
					   }
			              ++row;
						       front = possibleCombo[row].getFaceValue();
			                   back = possibleCombo[row+1].getFaceValue();
						         if((front - back)==1||(front - back)==0){
			                        if((front - back)==1){
			        ++inOrder;
					   }
			                      ++row;
								  front = possibleCombo[row].getFaceValue();
			                     back = possibleCombo[row+1].getFaceValue();
								    if((front - back)==1||(front - back)==0){
			                        if((front - back)==1){
			        ++inOrder;
					   }
			                        ++row;
		                     }
		                    }
		                }
		           }
				   if(inOrder >= 4){
					   isThereStraight = true;
					   lead = possibleCombo[x].getFaceValue() +1 ;
					   strStraight = possibleCombo[x].getFaceValue() + 1;

					   if(strengthOfStraight < lead){
						   strStraight = possibleCombo[x].getFaceValue() + 1;
				   }
					   
				 }
		}

	}
	
   
	

}
void Player::checkFor3Kind(){
	if(first_Pair == 3 && second_Pair <= 1){
		isThere3kind = true;
	}
	str3Kind = value_1stPair;
	
}
void Player::checkFor2Pair(){
	if(first_Pair == 2 && second_Pair ==2){
		isThere2Pair = true;
	}
	if(value_1stPair > value_2ndPair){
		str2Pair1st = value_1stPair;
		str2Pair2nd = value_2ndPair;
	}
	if(value_1stPair < value_2ndPair){
		str2Pair1st = value_2ndPair;
		str2Pair2nd = value_1stPair;
	}
	
}
void Player::checkFor1Pair(){
	if(first_Pair == 2 && second_Pair ==0){
		isThere1Pair = true;
		strPair = value_1stPair;
	}
	

}
void Player::resetPlayer(){
	highestCombo = 0;
	comboSet = 0;
	strengthOfCombo = 0;
	first_Pair = 0;
	second_Pair = 0;
	value_1stPair = 0;
	value_2ndPair = 0;
	isThereFlush = false;
	isThereFullHouse = false;
	isThere3kind= false;
	isThere4kind= false;
	isThereStraight= false;
	isThere2Pair= false;
}
void Player:: checkForPairs(){
	setHandOrder();
	Card possibleCombo[7];
	possibleCombo[0]= pocket1;
	possibleCombo[1]= pocket2;
	possibleCombo[2]= flop1;
	possibleCombo[3]=flop2;
	possibleCombo[4]=flop3;
	possibleCombo[5]=flop4;
	possibleCombo[6]=flop5;
	first_Pair = 0;
	second_Pair = 0;
	value_1stPair = 0;
	value_2ndPair = 0;
	int variable = 14;
	Card holdCard;
	int valueOfCards[7];
	int ab=0;
	for(int a=0; a<=6;++a){
		valueOfCards[a] = possibleCombo[a].getFaceValue();
	}
	
	for(int x = 0; x<=6;++x){
		holdCard = possibleCombo[x];
		for(int y = 0; y < 7; ++y){
			if( holdCard.getFaceValue() == possibleCombo[y].getFaceValue() && x != y && valueOfCards[y] == holdCard.getFaceValue()){
				if( first_Pair == 0){
					value_1stPair = holdCard.getFaceValue();
			       
				}
				if( value_1stPair == holdCard.getFaceValue() ){
					++first_Pair;
					valueOfCards[y] = y * variable;
					variable = 2000 + rand() % 123421421;//prevents repeating of matching pairs
				}
				if( first_Pair > 0 && holdCard.getFaceValue() != value_1stPair){
					value_2ndPair = holdCard.getFaceValue();
				}
				if(value_2ndPair == holdCard.getFaceValue() ){
					++second_Pair;
					valueOfCards[y] = y * variable;
					variable = 2000 + rand() % 1234214;
				}			
			}
		}
	}
}

void Player:: highestHand(){
	resetPlayer();
	checkForPairs();
	checkFor1Pair();
	checkFor2Pair();
	checkFor3Kind();
	checkFor4Kind();
	checkForFlush();
	checkForFullHouse();
	checkForStraight();
	
	highestCombo = 0;
	highestKicker=pocket1;
	 if ( isThere1Pair == true && isThere2Pair == false ){
		highestCombo = 1;
		strengthOfCombo = strPair;
		
	}
	    if (isThere2Pair == true && isThereStraight == false){
		highestCombo =2 ;
	}
	 
	   if (isThere3kind == true && isThereStraight == false){
		highestCombo =3 ;
		strengthOfCombo = str3Kind;
	}
	  if (isThereStraight == true  && isThereFlush == false){
		highestCombo =4 ;
		strengthOfCombo = strStraight;
	}
	  if (isThereFlush == true && isThereFullHouse == false){
		highestCombo =5 ;
		strengthOfCombo = strFlush;
	}
	  if (isThereFullHouse == true && isThere4kind == false){
		highestCombo = 6;
	}
	  if(isThere4kind == true){
		highestCombo = 7;
		strengthOfCombo = str4Kind;
	}

	
}

int Player:: getFlushStr()
{
	return strFlush ;
}
int Player:: getPlayerCombo()
{
	return highestCombo ;
}
unsigned int Player:: get_1stPair()
{
	return first_Pair;
}
unsigned int Player:: get_2ndPair()
{
	return second_Pair;
}
unsigned int Player:: get_Value1stPair()
{
	return value_1stPair;
}
unsigned int Player:: get_Value2ndPair()
{
	return value_2ndPair;
}
unsigned int Player:: get_Flush()
{
	return flushValue;
}
string Player:: getName(){
	return player_Name;
}
void Player:: print(){
	cout << pocket1.toString()<< endl << pocket2.toString()<<endl; 
	cout << flop1.toString() << endl << flop2.toString()<<  endl << flop3.toString()<<endl;
	cout << flop4.toString() <<endl << flop5.toString()<< endl;
}
void Player:: printHand(){
	cout <<"\nPocket Hand \n"<< hold1.toString()<<" || "<< hold2.toString()<<endl; 
}	
void Player:: printFlop(){
	cout <<"\nThe flop is: \n"<< flop1.toString()<< " || "<< flop2.toString()<< " || "<< flop3.toString()<<endl; 
}	
void Player:: printTurn2(){
	cout <<"Table after the turn: \n"<< flop1.toString()<< " || "<< flop2.toString()<<" || "<< flop3.toString()<<" || "<< flop4.toString()<<endl; 
}	
void Player:: printTurn3(){
	cout <<"Table after the river: \n"<< flop1.toString()<< " || "<< flop2.toString()<< " || "<<flop3.toString()<<" || "<< flop4.toString()<<" || "<< flop5.toString()<<endl; 
}	
void Player:: printBestCombo(){
	Card temp1(1,1), temp2(2,2);
	if(highestCombo==7){
		temp1.setFace(str4Kind);
		cout<<getName()<< " : has four of a kind of "<<temp1.toStringFace()<<endl;
	}
	if(highestCombo==6){
		temp1.setFace(strFullHouse2);
		temp2.setFace(strFullHouse3);
		cout<<getName()<< " : has a full house made of "<<temp1.toStringFace()<< " and "<< temp2.toStringFace()<<endl;
	}
	if(highestCombo==5){
		temp1.setFace(strFlush);
		cout<<getName()<< " : has a flush with a lead of "<<temp1.toStringFace()<<endl;
		
	}
	if(highestCombo==4){
		temp1.setFace(strStraight);
		cout<<getName()<< " : has a straight with a lead of "<<temp1.toStringFace()<<endl;
	}
	if(highestCombo==3){
		temp1.setFace(str3Kind);
		cout<<getName()<< " : has three of a kind of "<<temp1.toStringFace()<<endl;
	}
	if(highestCombo==2){
		temp1.setFace(value_1stPair);
		temp2.setFace(value_2ndPair);
		cout<<getName()<< " : has two pairs "<<temp1.toStringFace()<< " and "<< temp2.toStringFace()<<endl;
	}
	if(highestCombo==1){
		temp1.setFace(value_1stPair);
		cout<<getName()<< " : has a single pair "<<temp1.toStringFace()<<endl;
	}
	if(highestCombo==0){
		cout<<getName()<< " has no combos and has a "<< highestKicker.toString()<< " as a kicker"<<endl;

	}
}