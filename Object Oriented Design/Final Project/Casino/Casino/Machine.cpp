// John Gangemi
// Raymond Lian
#include "Machine.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <ctime>


std::ostream &operator<<(std::ostream &out, const Machine &obj)
{
	out << std::endl;

	for (unsigned int i = 0; i < 3; i++)
	{
		for (unsigned int j = 0; j < 3; ++j)
		{
			out << std::left << std::setw(15);
			out << obj.screen[i][j];
		}
		out << std::endl;
	}

	return out;
}


Machine::Machine(const float &gambler_funds)
	:bet(0)
{
	if (gambler_funds <= 0)
		throw std::invalid_argument("not enough funds to play a slot machine");

	for (unsigned int i = 0; i < 3; ++i)
	{
		for (unsigned int j = 0; j < 3; ++j)
			screen[i][j] = "pull handle";
	}

	reels.push_back(new Reel());
	reels.push_back(new Reel2());
	reels.push_back(new Reel3());
}


Machine::~Machine()
{
	for (unsigned int i=0; i < 3; i++)
		delete reels[i];

	std::vector<Symbols*>().swap(reels);
}


void Machine::setBet()
{
	while (true)
	{
		bool valid = true;
		unsigned int selection = 0;
		std::cout << "Insert credits: $1, $2, $5, $10\n:: ";
		try
		{
			std::cin >> selection;
			if (std::cin.fail() || selection < 1 || selection > 10)
				throw 1;
		}
		catch (int)
		{
			valid = false;
		}

		if (valid)
		{
			bet = selection;
			break;
		}
		else
		{
			std::cout << "please, enter a number\n";
			std::cin.clear();
		}
	}
}


unsigned int Machine::getBet() const
{
	return bet;
}


void Machine::pullHandle() 
{
	const int random = stopPostion();

	for (unsigned int i = 0; i < 3; ++i)
	{
		for (unsigned int j = 0; j < 3; ++j)
		{
			if (i == 0)
				screen[i][j] = reels[j]->getTopSymbol(random);
			else if (i == 1)
				screen[i][j] = reels[j]->getCenterSymbol(random);
			else
				screen[i][j] = reels[j]->getBottomSymbol(random);
		}
	}
}


float Machine::calculateScreen() const
{
	if (threeCenter())
	{
		std::cout << "Three Matching Center\n";
		std::cout << "Congratulations! You have won $" << (300 * getBet()) << std::endl;
		return (300 * (float)getBet());
	}
	else if (twoCenter())
	{
		std::cout << "Two Matching Center\n";
		std::cout << "Congratulations! You have won $" << (30 * getBet()) << std::endl;
		return (30 * (float)getBet());
	}
	else if (threeScreen())
	{
		std::cout << "Three Matching Screen\n";
		std::cout << "Congratulations! You have won $" << (5 * getBet()) << std::endl;
		return (5 * (float)getBet());
	}
	else if (twoScreen())
	{
		std::cout << "Two Matching Screen\n";
		std::cout << "Congratulations! You have won $" << (2 * getBet()) << std::endl;
		return (2 * (float)getBet());
	}
	else
	{
		std::cout << "Sorry, you have lost" << std::endl;
		return (-1 * (float)getBet());
	}
}


bool Machine::threeCenter() const
{
	if (screen[1][0] == screen[1][1] && screen[1][1] == screen[1][2])
	{
		return true;
	}
	else
		return false;
}


bool Machine::twoCenter() const
{
	if (screen[1][0] == screen[1][1] || 
		screen[1][0] == screen[1][2] || 
		screen[1][1] == screen[1][2])
		return true;
	else
		return false;
}


bool Machine::threeScreen() const
{
	unsigned int matches = 0;

	for (unsigned int i = 0 ; i < 3; ++i)
	{
		if (i == 0)
		{
			if (screen[i][0] == screen[i][1] || screen[i][0] == screen[i][2])
				++matches;
			else if (screen[i][0] == screen[1][0] || screen[i][0] == screen[1][1] || screen[i][0] == screen[1][2])
				++matches;
			else if (screen[i][0] == screen[2][0] || screen[i][0] == screen[2][1] || screen[i][0] == screen[2][2])
				++matches;

			if (matches >= 2)
				break;
		}
		else if (i == 1)
		{
			if (screen[i][0] == screen[0][0] || screen[i][0] == screen[0][1] || screen[i][0] == screen[0][2])
				++matches;
			else if (screen[i][0] == screen[1][1] || screen[i][0] == screen[1][2])
				++matches;
			else if (screen[i][0] == screen[2][0] || screen[i][0] == screen[2][1] || screen[i][0] == screen[2][2])
				++matches;

			if (matches >= 2)
				break;
		}
		else
		{
			if (screen[i][0] == screen[0][0] || screen[i][0] == screen[0][1] || screen[i][0] == screen[0][2])
				++matches;
			else if (screen[i][0] == screen[1][0] || screen[i][0] == screen[1][1] || screen[i][0] == screen[1][2])
				++matches;
			else if (screen[i][0] == screen[2][1] || screen[i][0] == screen[2][2])
				++matches;

			if (matches >= 2)
				break;
		}

		matches = 0; // reset counter
	}

	if (matches >= 2)
		return true;
	else
		return false;
}


bool Machine::twoScreen() const
{
	unsigned int matches = 0;

	for (unsigned int i = 0 ; i < 3; ++i)
	{
		if (i == 0)
		{
			if (screen[i][0] == screen[i][1] || screen[i][0] == screen[i][2])
				++matches;
			else if (screen[i][0] == screen[1][0] || screen[i][0] == screen[1][1] || screen[i][0] == screen[1][2])
				++matches;
			else if (screen[i][0] == screen[2][0] || screen[i][0] == screen[2][1] || screen[i][0] == screen[2][2])
				++matches;

			if (matches >= 1)
				break;
		}
		else if (i == 1)
		{
			if (screen[i][0] == screen[0][0] || screen[i][0] == screen[0][1] || screen[i][0] == screen[0][2])
				++matches;
			else if (screen[i][0] == screen[1][1] || screen[i][0] == screen[1][2])
				++matches;
			else if (screen[i][0] == screen[2][0] || screen[i][0] == screen[2][1] || screen[i][0] == screen[2][2])
				++matches;

			if (matches >= 1)
				break;
		}
		else
		{
			if (screen[i][0] == screen[0][0] || screen[i][0] == screen[0][1] || screen[i][0] == screen[0][2])
				++matches;
			else if (screen[i][0] == screen[1][0] || screen[i][0] == screen[1][1] || screen[i][0] == screen[1][2])
				++matches;
			else if (screen[i][0] == screen[2][1] || screen[i][0] == screen[2][2])
				++matches;

			if (matches >= 1)
				break;
		}

		matches = 0; // reset counter
	}

	if (matches >= 1)
		return true;
	else
		return false;
}


int Machine::stopPostion() const
{
	srand((unsigned)time(NULL));
	return rand() % 10;
}