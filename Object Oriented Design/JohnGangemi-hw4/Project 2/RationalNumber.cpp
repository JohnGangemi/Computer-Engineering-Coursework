#include "RationalNumber.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

RationalNumber::RationalNumber(const int &numerator_ref, const int &denominator_ref)
{
	// check value in denominator_ref
	if (denominator_ref == 0) 
		throw std::invalid_argument("Denominator must be  greater than zero");
	else if (denominator_ref < 0)
	{
		// change order of negative sign
		numerator = numerator_ref * -1; 
		denominator = denominator_ref * -1;
	}
	else
	{
		numerator = numerator_ref;
		denominator = denominator_ref;
	}

	// call private member function to reduce private data members
	ReducedForm(numerator, denominator);
}

const RationalNumber RationalNumber::operator+(const RationalNumber &obj)
{
	
	return RationalNumber((numerator * obj.denominator) + (denominator * obj.numerator), (denominator * obj.denominator));
}

const RationalNumber RationalNumber::operator-(const RationalNumber &obj)
{
	return RationalNumber((numerator * obj.denominator) - (denominator * obj.numerator), (denominator * obj.denominator));
}

const RationalNumber RationalNumber::operator*(const RationalNumber &obj)
{
	return RationalNumber((numerator * obj.numerator), (denominator * obj.denominator));
}

const RationalNumber RationalNumber::operator/(const RationalNumber &obj)
{
	return RationalNumber((numerator * obj.denominator),(denominator * obj.numerator));
}

RationalNumber &RationalNumber::operator=(const RationalNumber &obj)
{
	if (this != &obj) // avoid self-assignment
	{
		numerator = obj.numerator;
		denominator = obj.denominator;
	}
	// return reference to this, allows cascading assignment operator
	return *this; 
}

bool RationalNumber::operator>(const RationalNumber &obj)
{
	// compare floating-point value of fractions
	if (float(numerator) / denominator > float(obj.numerator) / obj.denominator)
		return true;
	else
		return false;
}

bool RationalNumber::operator<(const RationalNumber &obj)
{
	// compare floating-point value of fractions
	if (float(numerator) / denominator < float(obj.numerator) / obj.denominator)
		return true;
	else
		return false;
}

bool RationalNumber::operator>=(const RationalNumber &obj)
{
	// compare floating-point value of fractions
	if (float(numerator) / denominator >= float(obj.numerator) / obj.denominator)
		return true;
	else
		return false;
}

bool RationalNumber::operator<=(const RationalNumber &obj)
{
	// compare floating-point value of fractions
	if (float(numerator) / denominator <= float(obj.numerator) / obj.denominator)
		return true;
	else
		return false;
}

bool RationalNumber::operator==(const RationalNumber &obj)
{
	// compare floating-point value of fractions
	if (float(numerator) / denominator == float(obj.numerator) / obj.denominator)
		return true;
	else
		return false;
}

bool RationalNumber::operator!=(const RationalNumber &obj)
{
	// compare floating-point value of fractions
	if (float(numerator) / denominator != float(obj.numerator) / obj.denominator)
		return true;
	else
		return false;
}

const void RationalNumber::printRational()
{
	if (numerator != 0)
		std::cout << "(" << numerator << "/" << denominator << ")";
	else
		std::cout << "0";
}

void RationalNumber::ReducedForm(int &numerator_ref, int &denominator_ref)
{
	// store reference values as non-modifiable variables
	const int numerator_const = numerator_ref; 
	const int denominator_const = denominator_ref; 

	if (numerator_const > denominator_const) // numerator is larger than denominator
	{
		int numerator_temp = numerator_const;
		int denominator_temp = denominator_const;

		for (int i = 1; i <= std::abs(denominator_const); i++)
		{
			if (numerator_const % i == 0 && denominator_const % i == 0) // check possible common denominators
			{
				numerator_temp = numerator_const / i;
				denominator_temp = denominator_const / i;
			}
		}
		// update reference variables
		numerator_ref = numerator_temp; 
		denominator_ref = denominator_temp;
	}
	else if (denominator_const > numerator_const) // denominator is larger than numerator
	{
		int numerator_temp = numerator_const;
		int denominator_temp = denominator_const;

		for (int i = 1; i <= std::abs(numerator_const); i++)
		{
			if (numerator_const % i == 0 && denominator_const % i == 0) // check possible common denominators
			{
				numerator_temp = numerator_const / i;
				denominator_temp = denominator_const / i;
			}
		}
		// update reference variables
		numerator_ref = numerator_temp;
		denominator_ref = denominator_temp;
	}
	else
	{
		// update reference variables
		numerator_ref = 1;
		denominator_ref = 1;
	}
}