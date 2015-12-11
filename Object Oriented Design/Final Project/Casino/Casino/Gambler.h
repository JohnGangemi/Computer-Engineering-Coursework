// John Gangemi
// Raymond Lian
#ifndef GAMBLER_H
#define GAMBLER_H

#include "BJPlayer.h" // is-a relationship
#include <vector>

class Gambler : public BJPlayer
{
public:
	Gambler();
	~Gambler();

	virtual std::ostream &print(std::ostream &out) const override;
	virtual void setObjectIdentifier() override; // set identifier to 'gambler'

	virtual void setBet();
	virtual unsigned int getBet(const unsigned int &hand) const;
	virtual bool canSplit(const unsigned int &split_hand) const;
	virtual void split(const unsigned int &split_hand);

private:
	std::vector<unsigned int> gamblers_bets; // store the bets for gambler
};

#endif