#pragma once

class RationalNumber
{
public:
	RationalNumber(const int &numerator_reference = 1, const int &denominator_reference = 1); // default constructor
	const RationalNumber operator+(const RationalNumber &object); // addition operator overloading
	const RationalNumber operator-(const RationalNumber &object); // subtraction operator overloading
	const RationalNumber operator*(const RationalNumber &object); // multiplication operator overloading
	const RationalNumber operator/(const RationalNumber &object); // division operator overloading
	RationalNumber &operator=(const RationalNumber &object); // assignment operator overloading
	bool operator>(const RationalNumber &object); // greater than operator overloading
	bool operator<(const RationalNumber &object); // less than operator overloading
	bool operator>=(const RationalNumber &object); // greater than equal to operator overloading
	bool operator<=(const RationalNumber &object); // less than equal to operator overloading
	bool operator==(const RationalNumber &object); // equals to operator overloading
	bool operator!=(const RationalNumber &object); // not equals to operator overloading
	// access function
	const void printRational(); // print function 
private:
	int numerator; // store numerator
	int denominator; // store denominator
	// utility function
	void ReducedForm(int &numerator_reference, int &denominator_reference);
};