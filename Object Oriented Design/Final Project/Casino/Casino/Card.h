// John Gangemi
// Raymond Lian
#ifndef CARD_H
#define CARD_H

#include <string>
#include <array>

class Card
{
public:
	Card(const unsigned int &face = 1, const unsigned int &suit = 1);
	~Card();
    Card &operator=(const Card &);

	const unsigned int getFaceValue();
	const unsigned int getSuitValue();
	void setFace(int);

	const std::string toString();
	const std::string toStringFace();
private:
	unsigned int rank;
	unsigned int order;
    
	static const std::array<std::string, 13> ranks;
	static const std::array<std::string, 4> orders;
};


#endif
