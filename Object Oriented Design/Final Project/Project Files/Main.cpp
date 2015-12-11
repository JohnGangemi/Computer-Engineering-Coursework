#include <iostream>
#include <stdexcept>
#include <string>
#include <ctime>
#include <limits>

#include "Machine.h"
#include "BJGame.h"
#include "Holdem.h"
using namespace std;

inline void chrono()
{
	time_t now;
	struct tm info;
	time(&now);
	localtime_s(&info, &now);

	cout << "Date: " << (info.tm_mon + 1) 
		<< "/" << info.tm_mday << "/" 
		<< (info.tm_year + 1900) << endl;
}

inline void welcomeMessage()
{
	std::string message = "The Casino comps $1000 for Slots or Blackjack with new gamblers.";

	cout << "\nWelcome!\n" 
		<< "The Casino comps $1000 for Slots or Blackjack with new gamblers.\n";

	for (unsigned int i = 0; i < message.length(); ++i)
		cout << "-";

	cout << endl;
}

inline void slotsRules()
{
	cout << "Three of a kind in center row: 300 * credit\n"
		<< "Two of a kind in center row: 30 * credit\n"
		<< "Three of a kind on screen: 5 * credit\n"
		<< "Two of a kind on screen: 2 * credit\n";
}

inline void blackjackRules()
{
	cout << "Beat dealer's hand by being closer to 21 than dealer\n"
		<< "21 in first two cards pays out 3 to 2 odds\n"
		<< "Dealer must hit on total less than 17\n";
}

template<typename T> 
T input(string prompt)
{
	while (true)
	{
		bool valid = true;
		T user_input;

		cout << prompt;

		try
		{
			cin >> user_input;
			if (cin.fail())
				throw 1;
		}
		catch (int)
		{
			valid = false;
		}

		if (valid)
			return user_input;
		else
		{
			cout << "please enter a valid response\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
}

int main()
{
	// initialize game variables
	float gamblers_balance = 1000.00;
	char again = 'y';

	// display date
	chrono();

	// display a welcome message
	welcomeMessage();

	do
	{
		// prompt for game
		cout << "\nPlease choose from our game options to begin gambling...";
		int game = 0;
		while (game < 1 || game > 3)
		{		
			game = input<int>("\n(1) Slots (2) Blackjack (3) Texas Hold'em\n:: ");
		}

		// process selection
		switch(game)
		{
		case 1: // slots

			//////////////////////////////////////////////////////////////////////////////
			try
			{
				char cont = 'y';

				do 
				{
					cout << "\n--Slots 2014--\n";
					slotsRules();
					cout << "\nGambler's funds: $" << gamblers_balance << endl << endl;

					// game logic
					Machine slots(gamblers_balance);
					slots.setBet();
					slots.pullHandle();
					cout << slots << endl;
					gamblers_balance += slots.calculateScreen();
					cout << "\nGambler's total is $" << gamblers_balance << endl;

					// prompt for another round
					cont = input<char>("Play again? (y)es or (n)o\n:: ");
					while (cont != 'n' && cont != 'y')
						cont = input<char>("Play again? (y)es or (n)o\n:: ");

					if (cont == 'n')
						cout << "Exiting Slots\n";

				}while (cont == 'y');
			}
			catch(invalid_argument &e)
			{
				cout << "Oops there's a problem, " << e.what() << endl;
			}
			break;
			//////////////////////////////////////////////////////////////////////////////

		case 2: // blackjack

			//////////////////////////////////////////////////////////////////////////////
			try
			{
				char cont = 'y';

				do 
				{
					cout << "\n--Blackjack 2014--\n";
					blackjackRules();
					cout << "\nGambler's funds: $" << gamblers_balance << endl << endl;

					// game logic
					BJGame BJ(gamblers_balance);
					BJ.game();
					gamblers_balance += BJ.getGameBalance();
					cout << "\nGambler's total is $" << gamblers_balance << endl;

					// prompt for another round
					cont = input<char>("Play again? (y)es or (n)o\n:: ");
					while (cont != 'n' && cont != 'y')
						cont = input<char>("Play again? (y)es or (n)o\n:: ");

					if (cont == 'n')
						cout << "Exiting Blackjack\n";

				}while (cont == 'y');
			}
			catch(invalid_argument &e)
			{
				cout << "Oops there's a problem, " << e.what() << endl;
			}
			break;
			//////////////////////////////////////////////////////////////////////////////

		case 3: // texas holdem

			//////////////////////////////////////////////////////////////////////////////
			try
			{
				string UserName;
				cout<<"\nWelcome to Poker\nEnter your name"<<endl;
				cin>> UserName; 

				Player Dealer(1000000,"Dealer",0,0);
				Player Gambler(100, UserName,0,0);
				int dealersChoice=0;
				int wager=0;
				int totalPot=0;
				int gameCondition=1;
				int roundCondition=1;

				cout<<"\nGreat!\nYou will first start off with 100 Chips\nYour opponent is the dealer\n\nGOOD LUCK!!"<<endl;

				Deck gameDeck;
				Card pocket1, pocket2;
				Card tbCard1, tbCard2, tbCard3, tbCard4, tbCard5;

				do 
				{
					gameDeck.shuffleFullDeck();
					pocket1 = gameDeck.dealCard();
					pocket2 = gameDeck.dealCard();
					Gambler.setPocket(pocket1,pocket2);
					pocket1 = gameDeck.dealCard();
					pocket2 = gameDeck.dealCard();
					Dealer.setPocket(pocket1,pocket2);
					Gambler.printHand();
					cout<<"\nDo you want to check or bet?\nEnter 1 for bet and 0 for check\n:: ";
					cin>>roundCondition;

					if(roundCondition == 1){
						cout<<"Enter your wager\n:: ";
						cin>>wager;

						while(wager > Gambler.getPlayerChips()){
							cout<<"Sorry you cannot bet more than you have. Please enter chips equal to or less than your remaining balance of :"<< Gambler.getPlayerChips()<<endl;
							cin>>wager;
						}

						Gambler.loseChips(wager);
						totalPot += (wager*2);
					}

					tbCard1 = gameDeck.dealCard();
					tbCard2 = gameDeck.dealCard();
					tbCard3 = gameDeck.dealCard();
					Gambler.setFlop(tbCard1,tbCard2,tbCard3);
					Dealer.setFlop(tbCard1,tbCard2,tbCard3);
					Gambler.printFlop();
					cout<<"\nDo you want to check or bet?\nEnter 1 for bet and 0 for check\n:: ";
					cin>>roundCondition;

					if(roundCondition == 1){
						cout<<"Enter your wager\n:: ";
						cin>>wager;

						while(wager > Gambler.getPlayerChips()){
							cout<<"Sorry you cannot bet more than you have. Please enter chips equal to or less than your remaining balance of :"<< Gambler.getPlayerChips()<<endl;
							cin>>wager;
						}

						Gambler.loseChips(wager);
						totalPot += (wager*2);
					}

					tbCard4 = gameDeck.dealCard();
					Gambler.setTurn(tbCard4);
					Dealer.setTurn(tbCard4);
					Gambler.printTurn2();
					cout<<"\nDo you want to check or bet?\nEnter 1 for bet and 0 for check\n:: ";
					cin>>roundCondition;

					if(roundCondition == 1){
						cout<<"Enter your wager\n:: ";
						cin>>wager;

						while(wager > Gambler.getPlayerChips()){
							cout<<"Sorry you cannot bet more than you have. Please enter chips equal to or less than your remaining balance of :"<< Gambler.getPlayerChips()<<endl;
							cin>>wager;
						}

						Gambler.loseChips(wager);
						totalPot += (wager*2);
					}

					tbCard5 = gameDeck.dealCard();
					Gambler.setTurn(tbCard5);
					Dealer.setTurn(tbCard5);
					Gambler.printTurn3();	
					cout<<"\nDo you want to check or bet?\nEnter 1 for bet and 0 for check\n:: ";
					cin>>roundCondition;

					if(roundCondition == 1){
						cout<<"Enter your wager\n:: ";
						cin>>wager;

						while(wager > Gambler.getPlayerChips()){
							cout<<"Sorry you cannot bet more than you have. Please enter chips equal to or less than your remaining balance of :"<< Gambler.getPlayerChips()<<endl;
							cin>>wager;
						}

						Gambler.loseChips(wager);
						totalPot += (wager*2);
					}

					Gambler.highestHand();
					Dealer.highestHand();
					Gambler.printHand();
					Dealer.printHand();
					Gambler.printBestCombo();
					Dealer.printBestCombo();

					if(Gambler > Dealer){
						Gambler.winChips(totalPot);

						cout<<"You won the pot!\nEarnings: "<<totalPot<< "\nTotal Chips Remaining: "<<Gambler.getPlayerChips()<< endl;
					}
					if(Gambler.getPlayerCombo() < Dealer.getPlayerCombo()){
						cout<<"You Lost the pot\nRemaining chips: "<< Gambler.getPlayerChips()<< endl;
					}
					if(Gambler.getPlayerCombo() == Dealer.getPlayerCombo()){
						Gambler.winChips(totalPot/2);
						cout<<"It is a split\nRemaining chips: "<< Gambler.getPlayerChips()<< endl;
					}
		
					if(Gambler.getPlayerChips() == 0){
						gameCondition = 0;
					}

					cout<<"Do you want to play another round?\nEnter 1 for Yes and 0 for No\n:: ";
					cin>>gameCondition;

				}while (gameCondition == 1 && Gambler.getPlayerChips() > 0);
			}
			catch(invalid_argument &e)
			{
				cout << "Oops there's a problem, " << e.what() << endl;
			}
			break;
			//////////////////////////////////////////////////////////////////////////////

		default:
			break;
		}

		// propmt for another game to be played
		again = input<char>("\nWould you like to play another game? (y)es or (n)o\n:: ");
		while (again != 'y' && again != 'n')
			again = input<char>("\nWould you like to play another game? (y)es or (n)o\n:: ");

	}while(again == 'y');

	cout << "\nThank-you for playing our games!" << endl;

	cout << endl;
	system("PAUSE");
	return 0;
}