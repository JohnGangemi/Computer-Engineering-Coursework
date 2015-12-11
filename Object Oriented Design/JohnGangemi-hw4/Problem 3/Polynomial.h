#pragma once
#include <vector>

class Polynomial
{
public:
	Polynomial(const std::vector<float> &coefficients_vector = std::vector<float>(), 
		const std::vector<unsigned int> &exponents_vector = std::vector<unsigned int>()); // default constructor
	Polynomial &operator=(const Polynomial &object); // equals operator overloading
	const Polynomial operator+(const Polynomial &object); // addition operator overloading
	const Polynomial operator-(const Polynomial &object); // subtraction operator overloading
	const Polynomial operator*(const Polynomial &object); // multiplication operator overloading
	Polynomial& operator+=(const Polynomial &object); // addition assignment operator overloading
	Polynomial& operator-=(const Polynomial &object); // subtraction assignment operator overloading
	Polynomial& operator*=(const Polynomial &object); // multiplication assignment operator overloading
	const void enterTerms(); // get user input for coefficient and exponent terms

	// access function
	const void printPolynomial(); // print the polynomial
private:
	// set and get functions
	void setCoefficient(const float &coefficient); // push value to coefficients_vec
	void setExponent(const unsigned int &exponent); // push value to exponent_vec
	const float getCoefficent(const unsigned int &index); // get value in coefficients_vec at index
	const unsigned int getExponent(const unsigned int &index); // get value in exponent_vec at index

	// utility functions
	const void validateCoefficient(float &coefficent_input); // validate format of user input
	const void validateExponent(unsigned int &exponent_input); // validate format of user input
	const void standardForm(); // arrange vectors to represent standard form polynomial

	// private data members
	std::vector<float> coefficients_vec; // store coefficient values
	std::vector<unsigned int> exponents_vec; // store exponent values
};

