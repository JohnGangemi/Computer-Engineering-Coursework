// John Gangemi
// Raymond Lian
#ifndef MACHINE_H
#define MACHINE_H

#include "Symbols.h"
#include "Reel.h"
#include "Reel2.h"
#include "Reel3.h"
#include <vector>
#include <string>

class Machine
{
	friend std::ostream &operator<<(std::ostream &output, const Machine &object);
public:
	Machine(const float &gambler_funds);
	~Machine();
	void setBet();
	unsigned int getBet() const;
	void pullHandle();
	float calculateScreen() const;

protected:
	bool threeCenter() const;
	bool twoCenter() const;
	bool threeScreen() const;
	bool twoScreen() const;
	int stopPostion() const;

private:
	unsigned int bet;
	std::string screen[3][3];
	std::vector<Symbols*> reels;
};

#endif