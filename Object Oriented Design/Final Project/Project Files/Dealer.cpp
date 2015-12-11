// John Gangemi

#include "Dealer.h"
#include <iomanip>


Dealer::Dealer()
	:BJPlayer(), flip_card(false)
{
	setObjectIdentifier();
}


Dealer::~Dealer()
{
}


std::ostream &Dealer::print(std::ostream &out) const
{
	unsigned int new_line = 0;

	if (players_hands.size() > 1)
		throw std::invalid_argument("Dealer can only have one hand");
	else
	{
		if (players_hands[0]->getHandSize() != 0)
		{
			out << std::endl;

			if (!getFlipCard())
			{
				out << std::left << std::setw(20);
				out << "Face Down Card";
				out << players_hands[0]->referenceCard(1).toString();
			}
			else
			{
				for (unsigned int i = 0; i < players_hands[0]->getHandSize(); ++i)
				{
					out << std::left << std::setw(20);
					out << players_hands[0]->referenceCard(i).toString();

					if ((i + 1) % 2 == 0)
						out << std::endl;

					new_line = i + 1;
				}
			}
		}
		else
			out << "empty hand...";

		if (new_line % 2 != 0)
			out << std::endl;
	}

	return out;
}


void Dealer::setObjectIdentifier()
{
	// DO NOT CHANGE
	object_id = dealer;
}


void Dealer::setFlipCard(const bool &expression)
{
	if (expression)
		flip_card = true;
	else 
		flip_card = false;
}


bool Dealer::getFlipCard() const
{
	return flip_card;
}