#include <iostream>
#include <stdexcept>
#include "Card.h"
using namespace std;					

const array<string, 13> Card::faces =
{ "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
"Nine", "Ten", "Jack", "Queen", "King" };
const array<string, 4> Card::suits =
{ "Clubs", "Diamonds", "Hearts", "Spades" };

Card::Card(const unsigned int &face_val, const unsigned int &suit_val)
{
	// check if values for face_val and suit_val are within range
	// and initialize the private data members
	// or use default parameters
	if ((face_val > 0 && face_val <= 13) && (suit_val > 0 && suit_val <= 4))
	{
		face = face_val;
		suit = suit_val;
	}
	else
		throw invalid_argument("Card is not defined in the standard 52 card deck");
}

string Card::toString()
{
	// return a string in the form of "face of suit"
	return (faces[face - 1] + " of " + suits[suit - 1]);
}