// John A. Gangemi U6871-4612
// Exercise 9.23 Solution: ex09_23.cpp
// Card shuffling and dealing program.
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "DeckOfCards.h" // DeckOfCards class definition

using namespace std;

int main()
{
	try{
		DeckOfCards myDeckOfCards;
		myDeckOfCards.shuffle(); // place Cards in random order

		// print all 52 Cards in the order in which they are dealt
		for (int i = 1; myDeckOfCards.moreCards(); ++i)
		{
			// deal and display a Card
			cout << left << setw(19) << myDeckOfCards.dealCard().toString();

			if (i % 4 == 0) // output newline every 4 cards
				cout << endl;
		} // end for
	}
	catch (invalid_argument &e)
	{
		cout << "\nException: " << e.what() << endl;
	}

	system("PAUSE");
	return 0;
} // end main
