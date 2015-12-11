// John Gangemi
// Raymond Lian
#include "Reel2.h"
#include <ctime>


Reel2::Reel2()
	:Symbols()
{
	buildReel();
}


Reel2::~Reel2()
{
	
}


void Reel2::buildReel()
{
	srand((unsigned)time(NULL));

	for (unsigned int i = 0; i < 10; ++i)
		reel[i] = fruits[i];

	for (unsigned int j = 0; j < 10; ++j)
	{
		unsigned int random = rand() % 10; // favors no index

		if (j != random)
		{
			std::string temp = reel[j];
			reel[j] = reel[random];
			reel[random] = temp;
		}
	}
}