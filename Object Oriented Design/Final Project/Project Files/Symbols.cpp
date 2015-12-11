// John Gangemi
// Raymond Lian
#include "Symbols.h"
#include <stdexcept>


const std::array<std::string, 10> Symbols::fruits =
{"Apple", "Banana", "Orange", "Kiwi", "Grape", "Strawberry", "Lime", "Melon", "Peach", "Cherry"};


Symbols::Symbols()
{
}


Symbols::~Symbols()
{
}


bool Symbols::loadedReel() const
{
	if (!reel.empty())
		return true;
	else
		return false;
}


std::string Symbols::getTopSymbol(const int &pos) const
{
	if (pos >= 0 && (unsigned)pos < reel.size())
		if (pos + 1 >= 10)
			return reel[0];
		else
			return reel[pos + 1];
	else
		throw std::invalid_argument("invalid stop position for reel");
}


std::string Symbols::getCenterSymbol(const int &pos) const
{
	if (pos >= 0 && (unsigned)pos < reel.size())
		return reel[pos];
	else
		throw std::invalid_argument("invalid stop position for reel");
}


std::string Symbols::getBottomSymbol(const int &pos) const
{
	if (pos >= 0 && (unsigned)pos < reel.size())
		if (pos - 1 < 0)
			return reel[9];
		else
			return reel[pos - 1];
	else
		throw std::invalid_argument("invalid stop position for reel");
}