// John Gangemi
#include "Gambler.h"
#include <iomanip>


Gambler::Gambler()
	:BJPlayer()
{
	setObjectIdentifier();
}


Gambler::~Gambler()
{
	std::vector<unsigned int>().swap(gamblers_bets);
}


std::ostream &Gambler::print(std::ostream &out) const
{
	for (unsigned int i = 0; i < players_hands.size(); ++i)
	{
		unsigned int new_line = 0;

		if (players_hands.size() == 1)
			out << std::endl;
		else
			out << "\nHand " << i + 1 << ":\n";

		if (players_hands[i]->getHandSize() != 0)
		{
			out << "Wager: $" << gamblers_bets[i] << std::endl;

			for (unsigned int j = 0; j < players_hands[i]->getHandSize(); ++j)
			{
				out << std::left << std::setw(20);
				out << players_hands[i]->referenceCard(j).toString();

				if((j + 1) % 2 == 0)
					out << std::endl;

				new_line = j + 1;
			}
		}
		else
			out << "empty hand...";

		if (new_line % 2 != 0)
			out << std::endl;
	}

	return out;
}


void Gambler::setObjectIdentifier()
{
	// DO NOT CHANGE
	object_id = gambler;
}


void Gambler::setBet()
{
	while (true)
	{
		bool valid = true;
		unsigned int bet = 0;

		std::cout << "Enter a bet for the hand ($5 to $100):\n:: ";

		try
		{
			std::cin >> bet;
			if (std::cin.fail() || (bet < 5 || bet > 100))
				throw 1;
		}
		catch (int)
		{
			valid = false;
		}

		if (valid)
		{
			gamblers_bets.push_back(bet);
			break;
		}
		else
		{
			std::cout << "please, enter a valid bet\n";
			std::cin.clear();
		}
	}
}


unsigned int Gambler::getBet(const unsigned int &hand) const
{
	return gamblers_bets[hand];
}


bool Gambler::canSplit(const unsigned int &split_hand) const
{
	bool flag = false;

	if (players_hands[split_hand]->getHandSize() > 1 && players_hands.size() < 4)
	{
		// get index of last BJCard object from referenced hand object
		const unsigned int last_card = players_hands[split_hand]->getHandSize() - 1;

		// check for two of a kind as last pair in hand
		if (players_hands[split_hand]->referenceCard(last_card).getRankValue()
			== players_hands[split_hand]->referenceCard(last_card - 1).getRankValue())
			flag = true;
	}

	if (flag)
		return true;
	else
		return false;
}


void Gambler::split(const unsigned int &split_hand)
{
	if (players_hands[split_hand]->getHandSize() > 1 && players_hands.size() < 4)
	{
		// get index of last BJCard object from referenced hand object
		const unsigned int last_card = players_hands[split_hand]->getHandSize() - 1; 

		// check for two of a kind as last pair in hand
		if (players_hands[split_hand]->referenceCard(last_card).getRankValue()
			== players_hands[split_hand]->referenceCard(last_card - 1).getRankValue())
		{
			// remove selected BJCard object from hand
			BJCard split_card = players_hands[split_hand]->referenceCard(last_card); // store last BJCard object from referenced hand object 
			players_hands[split_hand]->pullCard(); // remove last BJCard object from referenced hand object

			// add selected BJCard object to new hand
			players_hands.push_back(new Hand()); // create new hand object
			players_hands.back()->addCard(split_card); // add last BJCard object from previous hand object to newly created hand object
		}
	}
	else
		throw std::invalid_argument("Maximum number of hands is four and each hand must have at least two cards to split");
}