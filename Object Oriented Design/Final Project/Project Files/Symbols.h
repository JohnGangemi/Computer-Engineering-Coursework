// John Gangemi
// Raymond Lian

// abstract base class
#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <array>
#include <string>

class Symbols
{
public:
	Symbols();
	virtual ~Symbols();
	virtual void buildReel() = 0;
	bool loadedReel() const;
	std::string getTopSymbol(const int &position) const;
	std::string getCenterSymbol(const int &position) const;
	std::string getBottomSymbol(const int &position) const;

protected:
	std::array<std::string, 10> reel;
	static const std::array<std::string, 10> fruits;
};

#endif