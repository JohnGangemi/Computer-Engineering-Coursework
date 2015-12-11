// John Gangemi
// Raymond Lian
#include "Reel3.h"
#include <ctime>


Reel3::Reel3()
	:Symbols()
{
	buildReel();
}


Reel3::~Reel3()
{
	
}


void Reel3::buildReel()
{
	srand((unsigned)time(NULL));

	for (unsigned int i = 0; i < 10; ++i)
		reel[i] = fruits[i];

	for (unsigned int j = 9; j > 0; --j)
	{
		unsigned int random = rand() % 6; // favors lower half index

		if (j != random)
		{
			std::string temp = reel[j];
			reel[j] = reel[random];
			reel[random] = temp;
		}
	}
}