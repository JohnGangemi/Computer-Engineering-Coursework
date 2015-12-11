#pragma once
#include <iostream>

class Complex
{
	friend std::ostream &operator<<(std::ostream &output, const Complex &object); // stream extraction operator overloading
	friend std::istream &operator>>(std::istream &input, Complex &object); // stream insertion operator overloading
public:
	explicit Complex(double real_number = 0.0, double imaginary_number = 0.0); // default constructor
	const Complex operator+(const Complex &object); // addition operator overloading
	const Complex operator-(const Complex &object); // subtraction operator overloading
	const Complex operator*(const Complex &object); // multiplication operator overloading
	Complex &operator=(const Complex &object); // assignment operator overloading
	bool operator==(const Complex &object); // "equal to" operator overloading
	bool operator!=(const Complex &object); // "not equal to" operator overloading
private:
	double real; // real number
	double imaginary; // imaginary number
};