// John Gangemi
#ifndef BJCARD_H
#define BJCARD_H

#include <string>
#include <array>

// represents face and suit of card object
enum Ranks{ Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };
enum Suits{ Clubs, Diamonds, Hearts, Spades };

class BJCard
{
public:
	BJCard(const Ranks &rank_name, const Suits &suit_name); // construct a BJCard object
	~BJCard();

	Ranks getRank() const; // return data of type Rank
	Suits getSuit() const; // return data of type Suit
	unsigned int getRankValue() const; // return numerical representation of type Rank 
	unsigned int getSuitValue() const; // return numerical representation of type Suit

	std::string toString() const; // return literal representation of type Rank and Suit

	BJCard &operator=(const BJCard &object); // overloaded assignment operator

private:
	Ranks rank; // store data of type Rank
	Suits suit; // store data of type Suit
	static const std::array<std::string, 13> ranks_str; // array of string literals representing face names
	static const std::array<std::string, 4> suits_str; // array of string literals representing suit names
};

#endif