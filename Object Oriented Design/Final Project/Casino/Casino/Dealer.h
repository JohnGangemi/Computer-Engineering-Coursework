// John Gangemi
// Raymond Lian
#ifndef DEALER_H
#define DEALER_H

#include "BJPlayer.h" // is-a relationship

class Dealer : public BJPlayer
{
public:
	Dealer();
	~Dealer();

	virtual std::ostream &print(std::ostream &out) const override;
	virtual void setObjectIdentifier() override; // set identifier to 'dealer'

	virtual void setFlipCard(const bool &expression);
	virtual bool getFlipCard() const;

private:
	bool flip_card; // store visual state of first card
};

#endif