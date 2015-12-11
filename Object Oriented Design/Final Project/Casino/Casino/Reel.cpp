// John Gangemi
// Raymond Lian
#include "Reel.h"
#include <ctime>


Reel::Reel()
	:Symbols()
{
	buildReel();
}


Reel::~Reel()
{
}


void Reel::buildReel()
{
	srand((unsigned)time(NULL));

	for (unsigned int i = 0; i < 10; ++i)
		reel[i] = fruits[i];

	for (unsigned int j = 9; j > 0; --j)
	{
		unsigned int random = rand() % 3; // favors lower 4th index

		if (j != random)
		{
			std::string temp = reel[j];
			reel[j] = reel[random];
			reel[random] = temp;
		}
	}
}