// John Gangemi

#include "BJGame.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>


BJGame::BJGame(const float &gamblers_funds)
	:shoe(), balance(0)
{
	if (gamblers_funds < 5.00)
		throw std::invalid_argument("Gambler does not have sufficent funds to play Black Jack");

	// create two new player objects
	// order of players is known, do not have to use overloaded [] to reference elsewhere
	players.push_back(new Dealer()); // vector.front()
	players.push_back(new Gambler()); // vector.back()
}


BJGame::~BJGame()
{
	for (unsigned int i = 0; i < players.size(); ++i)
		delete players[i];

	std::vector<BJPlayer*>().swap(players);
}


void BJGame::setGameBalance(const float &amount)
{
	balance = amount;
}


float BJGame::getGameBalance() const
{
	return balance;
}


void BJGame::game()
{
	// instantiate game variables
	unsigned int number_of_busts = 0;
	bool skip_dealer_turn = false;

	// perform game set-up
	placeBets();
	dealTwo();

	std::cout << "\nDealer..." << *players.front() << std::endl;
	std::cout << "\nGambler..." << *players.back();

	// update status of hand for dealer
	players.front()->checkPlayersHand(0);

	// loop over each hand of gambler
	for (unsigned int j = 1; j < players.back()->getNumberOfHands() + 1; ++j)
	{
		unsigned int original_num_hands =players.back()->getNumberOfHands();

		// update status of hands for gambler
		players.back()->checkPlayersHand(j - 1);

		// check for two card blackjack
		if (isBlackjack(j))
		{
			skip_dealer_turn = true;
			break;
		}

		// play hand till otherwise
		do
		{
			gamblersTurn(j);

			std::cout << "\nGambler..." << *players.back();

			// check for split and then check for two card blackjack
			if (players.back()->getNumberOfHands() > original_num_hands && players.back()->playHand(j).getHandSize() == 2)
			{
				if (isBlackjack(j))
				{
					skip_dealer_turn = true;
					break;
				}
			}

		} while (players.back()->playHand(j).getHandStatus() == play);

		// count the number of busted hands
		if (players.back()->playHand(j).getHandStatus() == bust)
			++number_of_busts;
	}

	// process dealer's turn or skip if appropriate
	if (number_of_busts != players.back()->getNumberOfHands() && !skip_dealer_turn)
	{
		dealersTurn();

		std::cout << "\nDealer..." << *players.front();

		calculateRound();
	}
	else if (number_of_busts == players.back()->getNumberOfHands() 
		|| (skip_dealer_turn && players.front()->playHand(1).getHandStatus() != Status::push))
	{
		players.front()->setFlipCard(true);

		std::cout << "\nDealer..." << *players.front();

		calculateRound();
	}
	else if (skip_dealer_turn && players.front()->playHand(1).getHandStatus() == Status::push)
		std::cout << "\nGambler's \"BlackJack\" forced a push with Dealer's \"BlackJack\"\nAll hands result in a tie\n";

	std::cout << std::endl;
	std::cout << "\nEnd of round...";
}


void BJGame::placeBets()
{
	// example using a derived object's identifier
	for (unsigned int i = 0; i < players.size(); ++i)
		if (players[i]->getObjectIdentifier() == gambler)
			players[i]->setBet();
}


void BJGame::dealTwo()
{
	for (unsigned int i = 0; i < players.size(); ++i)
		for (unsigned int j = 0; j < 2; ++j)
			players[i]->playHand(1).addCard(shoe.dealCard());
}


void BJGame::gamblersTurn(const unsigned int &hand)
{
	if (players.back()->playHand(hand).getHandStatus() == play)
	{
		std::cout << "\nOptions for hand " << hand << ":\n";

		if (players.back()->playHand(hand).getHandSize() == 1)
		{
			twoOptions(hand);
		}
		else if (players.back()->playHand(hand).getHandSize() == 2)
		{
			if (players.back()->canSplit(hand - 1))
				fiveOptions(hand);
			else
				fourOptions(hand);
		}
		else if (players.back()->playHand(hand).getHandSize() > 2)
		{
			if (players.back()->canSplit(hand - 1))
				threeOptions(hand);
			else
				twoOptions(hand);
		} 
		else
			throw std::invalid_argument("No options exists for an empty hand");
	} 
}


void BJGame::dealersTurn()
{
	while (players.front()->playHand(1).getHandValue() < 17)
	{
		players.front()->playHand(1).addCard(shoe.dealCard());
		players.front()->checkPlayersHand(0);
	}

	players.front()->setFlipCard(true);
}


unsigned int BJGame::validateOption(const unsigned int &number_of_options) const
{
	while (true)
	{
		bool valid = true;
		unsigned int selection = 0;

		try
		{
			std::cin >> selection;
			if (std::cin.fail() || (selection < 1 || selection > number_of_options))
				throw 1;
		}
		catch (int)
		{
			valid = false;
		}

		if (valid)
			return selection;
		else
		{
			std::cout << "\nplease, enter a valid number";
			std::cin.clear();
		}
	}
}


void BJGame::twoOptions(const unsigned int &hand)
{
	std::cout << "(1) Hit (2) Stand \n:: ";

	switch (validateOption(2))
	{
	case 1:
		players.back()->playHand(hand).addCard(shoe.dealCard());
		players.back()->checkPlayersHand(hand - 1);
		break;
	case 2:
		players.back()->playHand(hand).setHandStatus(stand);
		break;
	default:
		break;
	}
}


void BJGame::threeOptions(const unsigned int &hand)
{
	std::cout << "(1) Hit (2) Stand (3) Split\n:: ";

	switch (validateOption(3))
	{
	case 1:
		players.back()->playHand(hand).addCard(shoe.dealCard());
		players.back()->checkPlayersHand(hand - 1);
		break;
	case 2:
		players.back()->playHand(hand).setHandStatus(stand);
		break;
	case 3:
		players.back()->split(hand - 1);
		players.back()->setBet();
		break;
	default:
		break;
	}
}


void BJGame::fourOptions(const unsigned int &hand)
{
	std::cout << "(1) Hit (2) Stand (3) Double Down (4) Surrender\n:: ";

	switch (validateOption(4))
	{
	case 1:
		players.back()->playHand(hand).addCard(shoe.dealCard());
		players.back()->checkPlayersHand(hand - 1);
		break;
	case 2:
		players.back()->playHand(hand).setHandStatus(stand);
		break;
	case 3:
		players.back()->playHand(hand).addCard(shoe.dealCard());
		players.back()->playHand(hand).setHandStatus(doubleDown);
		break;
	case 4:
		players.back()->playHand(hand).setHandStatus(surrender);
		break;
	default:
		break;
	}
}


void BJGame::fiveOptions(const unsigned int &hand)
{
	std::cout << "(1) Hit (2) Stand (3) Split (4) Double Down (5) Surrender\n:: ";

	switch (validateOption(5))
	{
	case 1:
		players.back()->playHand(hand).addCard(shoe.dealCard());
		players.back()->checkPlayersHand(hand - 1);
		break;
	case 2:
		players.back()->playHand(hand).setHandStatus(stand);
		break;
	case 3:
		players.back()->split(hand - 1);
		players.back()->setBet();
		break;
	case 4:
		players.back()->playHand(hand).addCard(shoe.dealCard());
		players.back()->playHand(hand).setHandStatus(doubleDown);
		break;
	case 5:
		players.back()->playHand(hand).setHandStatus(surrender);
		break;
	default:
		break;
	}
}


void BJGame::calculateRound()
{
	static const float three_two_odds = 1.50;
	static const float half_odds = 0.50;
	static const float double_odds = 2.00;

	const unsigned int dealer_hand_val = players.front()->playHand(1).getHandValue(); 

	for (unsigned int m = 1; m < players.back()->getNumberOfHands() + 1; ++m)
	{
		unsigned int  gamblers_hand_val = players.back()->playHand(m).getHandValue();

		// evaluate push condition
		if ((players.back()->playHand(m).getHandStatus() != surrender 
			&& players.back()->playHand(m).getHandStatus() != blackJack 
			&& players.back()->playHand(m).getHandStatus() != push)
			&& gamblers_hand_val == dealer_hand_val)
		{
			players.back()->playHand(m).setHandStatus(push);
		}

		// update gambler's balance
		switch (players.back()->playHand(m).getHandStatus())
		{
		case stand:
			if ((gamblers_hand_val > dealer_hand_val && gamblers_hand_val <= 21)
				|| (players.front()->playHand(1).getHandStatus() == Status::bust))
			{
				setGameBalance((float)players.back()->getBet(m - 1));
				std::cout << "\nHand " << m << " beats Dealer's hand!";
			}
			else if (gamblers_hand_val < dealer_hand_val && dealer_hand_val <= 21)
			{
				setGameBalance((float)players.back()->getBet(m - 1) * -1);
				std::cout << "\nHand " << m << " losses to Dealer's hand";
			}
			break;

		case push:
			std::cout << "\nHand " << m << " is a push";
			break;

		case doubleDown:
			if ((gamblers_hand_val > dealer_hand_val && gamblers_hand_val <= 21)
				|| (gamblers_hand_val <= 21 && players.front()->playHand(1).getHandStatus() == bust))
			{
				setGameBalance((float)players.back()->getBet(m - 1) * double_odds);
				std::cout << "\nHand " << m << " beats Dealer's hand!";
			}
			else if ((gamblers_hand_val < dealer_hand_val && dealer_hand_val <= 21)
				|| (gamblers_hand_val > dealer_hand_val && gamblers_hand_val > 21 && dealer_hand_val <= 21))
			{
				setGameBalance((float)players.back()->getBet(m - 1) * -double_odds);
				std::cout << "\nHand " << m << " losses to Dealer's hand";
			}
			break;

		case surrender:
			setGameBalance((float)players.back()->getBet(m - 1) * -half_odds);
			break;

		case bust:
			setGameBalance((float)players.back()->getBet(m - 1) * -1);
			std::cout << "\nHand " << m << " busted";
			break;

		case twentyOne:
			setGameBalance((float)players.back()->getBet(m - 1));
			std::cout << "\nHand " << m << " beats Dealer's hand";
			break;

		case blackJack:
			setGameBalance((float)players.back()->getBet(m - 1) * three_two_odds);
			std::cout << "\nCongratulations, hand " << m << " wins with Black Jack!";
			break;

		default:
			break;
		}
	}
}


bool BJGame::isBlackjack(const unsigned int &hand) const
{
	if (players.back()->playHand(hand).getHandStatus() == blackJack)
	{
		if (players.front()->playHand(1).getHandStatus() == blackJack)
		{
			players.back()->playHand(hand).setHandStatus(push);
			players.front()->playHand(0).setHandStatus(push);
		}

		return true;
	}
	else
		return false;
}