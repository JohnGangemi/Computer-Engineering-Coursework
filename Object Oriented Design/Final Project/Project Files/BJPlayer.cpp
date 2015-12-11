// John Gangemi

#include "BJPlayer.h"
#include <stdexcept>


BJPlayer::BJPlayer()
	:object_id(dealer) // default the data member
{
	// add hand object to all objects derived
	players_hands.push_back(new Hand());
}


BJPlayer::~BJPlayer()
{
	for (unsigned int i = 0; i < players_hands.size(); ++i)
		delete players_hands[i];

	std::vector<Hand*>().swap(players_hands);
}


void BJPlayer::setFlipCard(const bool &expression)
{
	// provide no implementation, targets only dealer object
}


bool BJPlayer::getFlipCard() const
{
	return false; // default 
}


bool BJPlayer::canSplit(const unsigned int &split_hand) const 
{
	return false; // default
}


void BJPlayer::split(const unsigned int &hand)
{
	// provide no implementation, targets only gambler object
}


void BJPlayer::setBet()
{
	// provide no implementation, targets only gambler object
}


unsigned int BJPlayer::getBet(const unsigned int &hand) const
{
	return 0; // default
}


unsigned int BJPlayer::getNumberOfHands() const
{
	return players_hands.size();
}


void BJPlayer::checkPlayersHand(const unsigned int &hand)
{
	// set status of player's hand if appropriate
	if(players_hands[hand]->getHandStatus() == Status::play)
	{
		const unsigned int hand_val = players_hands[hand]->getHandValue();
		const unsigned int hand_size = players_hands[hand]->getHandSize();

		if (hand_val == 21 && hand_size == 2)
			players_hands[hand]->setHandStatus(Status::blackJack);
		else if (hand_val == 21 && hand_size > 2)
			players_hands[hand]->setHandStatus(Status::twentyOne);
		else if (hand_val > 21)
			players_hands[hand]->setHandStatus(Status::bust);
	}
	else if (hand >= players_hands.size() || hand < 0)
		throw std::invalid_argument("Hand does not exist for BJPlayer");
}


Type BJPlayer::getObjectIdentifier() const
{
	return object_id;
}


Hand &BJPlayer::playHand(const unsigned int &hand)
{
	if (hand > 0 && hand <= players_hands.size())
	{
		return *this->players_hands[hand - 1];
	}
	else
		throw std::invalid_argument("Hand does not exist for BJPlayer");
}