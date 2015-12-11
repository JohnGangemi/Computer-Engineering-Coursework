#include "Polynomial.h"
#include <cctype>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

Polynomial::Polynomial(const std::vector<float> &coef, const std::vector<unsigned int> &expo)
:coefficients_vec(coef), exponents_vec(expo) // member initialization list
{
	if (coefficients_vec.size() != exponents_vec.size())
		throw std::invalid_argument("Vector arguments must be of equal size");
}

Polynomial &Polynomial::operator=(const Polynomial &obj)
{
	if (this != &obj) // avoid self-assignment
	{
		coefficients_vec = obj.coefficients_vec;
		exponents_vec = obj.exponents_vec;
	}
	// return reference to this, allows cascading the assignment operator
	return *this;
}

const Polynomial Polynomial::operator+(const Polynomial &obj)
{
	std::vector<float> coef;
	std::vector<unsigned int> expo;

	// push contents of vectors *this and reference to temp vectors
	for (unsigned int i = 0; i < exponents_vec.size(); i++)
	{
		coef.push_back(coefficients_vec[i]);
		expo.push_back(exponents_vec[i]);
	}

	for (unsigned int j = 0; j < obj.exponents_vec.size(); j++)
	{
		coef.push_back(obj.coefficients_vec[j]);
		expo.push_back(obj.exponents_vec[j]);
	} 

	for (unsigned int k = 0; k < expo.size(); k++)
	{
		for (unsigned int l = 0; l < expo.size(); l++)
		{
			if (expo[k] == expo[l] && k != l)
			{
				coef[k] += coef[l]; // add coefficients with like exponents to index k
				coef.erase(coef.begin() + l); // erase element at index l
				expo.erase(expo.begin() + l); // erase element at index l

				if (l > 0)
					l--;
				else
					l = 0;
			}
		} 
	} 

	return Polynomial(coef, expo);
}

const Polynomial Polynomial::operator-(const Polynomial &obj)
{
	std::vector<float> coef;
	std::vector<unsigned int> expo;

	// push contents of vectors *this and reference to temp vectors
	for (unsigned int i = 0; i < exponents_vec.size(); i++)
	{
		coef.push_back(coefficients_vec[i]);
		expo.push_back(exponents_vec[i]);
	} 

	for (unsigned int j = 0; j < obj.exponents_vec.size(); j++)
	{
		coef.push_back(obj.coefficients_vec[j] * -1); // change sign of reference polynomial terms
		expo.push_back(obj.exponents_vec[j]);
	} 

	for (unsigned int k = 0; k < expo.size(); k++)
	{
		for (unsigned int l = 0; l < expo.size(); l++)
		{
			if (expo[k] == expo[l] && k != l)
			{
				coef[k] += coef[l]; // add coefficients with like exponents to index k
				coef.erase(coef.begin() + l); // erase element at index l
				expo.erase(expo.begin() + l); // erase element at index l

				if (l > 0)
					l--;
				else
					l = 0;
			}
		} 
	}

	return Polynomial(coef, expo);
}

const Polynomial Polynomial::operator*(const Polynomial &obj)
{
	std::vector<float> coef;
	std::vector<unsigned int> expo;

	const unsigned int this_size = coefficients_vec.size();
	const unsigned int ref_size = obj.coefficients_vec.size();

	if (this_size <= ref_size) // check for the larger vector
	{
		for (unsigned int i = 0; i < ref_size; i++)
		{
			for (unsigned int j = 0; j < this_size; j++)
			{
				coef.push_back(coefficients_vec[j] * obj.coefficients_vec[i]); // multiply coefficients
				expo.push_back(exponents_vec[j] + obj.exponents_vec[i]); // sum exponents
			} // end for
		} // end for
	}
	else
	{
		for (unsigned int i = 0; i < this_size; i++)
		{
			for (unsigned int j = 0; j < ref_size; j++)
			{
				coef.push_back(coefficients_vec[i] * obj.coefficients_vec[j]); // multiply coefficients
				expo.push_back(exponents_vec[i] + obj.exponents_vec[j]); // sum exponents
			} // end for
		} // end for
	}

	return Polynomial(coef, expo);
}

Polynomial& Polynomial::operator+=(const Polynomial &obj)
{
	*this = *this + obj;
	return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial &obj)
{
	*this = *this - obj;
	return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial &obj)
{
	*this = *this * obj;
	return *this;
}

const void Polynomial::enterTerms()
{
	float coef = 0.0;
	unsigned int expo = 0;

	std::cout << "Enter the terms of a polynomial...\n";
	do{
		std::cout << std::endl;
		validateCoefficient(coef);
		if (coef != 0)
		{
			setCoefficient(coef);
			validateExponent(expo);
			setExponent(expo);
		}
	} while (coef != 0);

	std::cout << std::endl;
}

const void Polynomial::printPolynomial()
{
	standardForm(); // arrange vectors in standard form 

	const unsigned int size = exponents_vec.size(); // reduce function calls to size() of vector class

	for (unsigned int i = 0; i < size; i++)
	{
		if (getExponent(i) > 1)
		{
			if (getCoefficent(i) != 0)
			{
				if (i < size - 1)
					std::cout << std::fixed << std::setprecision(2) << getCoefficent(i)
					<< "x^" << getExponent(i) << " + ";
				else
					std::cout << std::fixed << std::setprecision(2) << getCoefficent(i)
					<< "x^" << getExponent(i);
			}
		}
		else if (getExponent(i) == 1)
		{
			if (getCoefficent(i) != 0)
			{
				if (i < size - 1)
					std::cout << std::fixed << std::setprecision(2) << getCoefficent(i)
					<< "x + ";
				else
					std::cout << std::fixed << std::setprecision(2) << getCoefficent(i)
					<< "x";
			}
		}
		else
			if (getCoefficent(i) != 0)
				std::cout << std::fixed << std::setprecision(2) << getCoefficent(i);
	}
	std::cout << std::endl; 
}

void Polynomial::setCoefficient(const float &coef)
{
	coefficients_vec.push_back(coef);
}

void Polynomial::setExponent(const unsigned int &expon)
{
	exponents_vec.push_back(expon);
}

const float Polynomial::getCoefficent(const unsigned int &index)
{
	return coefficients_vec.at(index);
}

const unsigned int Polynomial::getExponent(const unsigned int &index)
{
	return exponents_vec.at(index);
}

const void Polynomial::validateCoefficient(float &coef_in)
{
	// function accepts fractonal or decimal values
	while (true)
	{
		bool valid = true;
		int divisor_count = 0;
		int period_count = 0;
		int negative_count = 0;
		std::string input;

		std::cout << "  enter coefficient (0 to stop) : ";
		std::getline(std::cin, input);

		// check user input
		if (std::cin.fail() 
			|| (!isdigit(input.front()) && input.front() != '-' && input.front() != '.') 
			|| !isdigit(input.back()))
			valid = false;
		else
		{
			for (unsigned int i = 0; i < input.length(); i++)
			{
				if (input[i] == '/')
					divisor_count++;
				else if (input[i] == '.')
					period_count++;
				else if (input[i] == '-')
					negative_count++;
				else if ((!isdigit(input[i]) && input[i] != '/' && input[i] != '.')
					|| (divisor_count > 0 && period_count > 0)
					|| divisor_count > 1
					|| period_count > 1
					|| negative_count > 1)
				{
					valid = false;
					break;
				}
			} // end for
		}

		if (valid)
		{
			try // process exceptions at runtime
			{
				if (divisor_count != 0)
				{
					std::string numerator;
					std::string denominator;

					for (unsigned int i = 0; i < input.length(); i++)
					{
						if (input[i] != '/')
							numerator += input[i];
						else
						{
							for (unsigned int j = i + 1; j < input.length(); j++)
							{
								denominator += input[j];
							}
							break;
						}
					}
					coef_in = std::stof(numerator) / std::stof(denominator);
					break;
				}
				else
				{
					coef_in = std::stof(input);
					break;
				}
			}
			catch (...)
			{
				throw std::invalid_argument("Error with conversion from string to float");
			}
		}
		else
		{
			std::cout << "  fraction, decimal or integer only\n";
			std::cin.clear();
		}
	}
}

const void Polynomial::validateExponent(unsigned int &expo_in)
{
	// function accepts only positive integer values
	while (true)
	{
		bool valid = true;
		std::string exponent;

		std::cout << "  enter exponent (0 for constant) : ";
		std::getline(std::cin, exponent);

		if (std::cin.fail())
			valid = false;
		else
		{
			for (unsigned int i = 0; i < exponent.length(); i++)
			{
				if (!isdigit(exponent[i])) // also handles negative 
					valid = false;
			} // end for
		}

		if (valid)
		{
			try // process exceptions at runtime
			{
				expo_in = std::stoi(exponent);
				break;
			}
			catch (...)
			{
				throw std::invalid_argument("Error with conversion from string to integer");
			}
		}
		else
		{
			std::cout << "  positive integer only\n";
			std::cin.clear();
		}
	}
}

const void Polynomial::standardForm()
{
	const unsigned int size = exponents_vec.size();

	if (size > 1) // unnecessary for single term polynomial
	{
		// modified bubble sort in descending order
		for (unsigned int i = 1; i < size; i++)
		{
			bool sorted = true;
			for (unsigned int j = 0; j < size - i; j++)
			{
				if (exponents_vec[j] < exponents_vec[j + 1])
				{
					// sort exponents vector in descending order
					unsigned int expo_temp = exponents_vec[j + 1];
					exponents_vec[j + 1] = exponents_vec[j];
					exponents_vec[j] = expo_temp;

					// sort coefficients vector corresponding to exponents vector
					float coef_temp = coefficients_vec[j + 1];
					coefficients_vec[j + 1] = coefficients_vec[j];
					coefficients_vec[j] = coef_temp;
					
					sorted = false;
				}
			} 
			if (sorted)
				break;
		} 

		// combine like terms based on exponent values
		for (unsigned int k = 0; k < exponents_vec.size(); k++)
		{
			for (unsigned int l = 0; l < exponents_vec.size(); l++)
			{
				if (exponents_vec[k] == exponents_vec[l] && k != l)
				{
					coefficients_vec[k] += coefficients_vec[l];
					coefficients_vec.erase(coefficients_vec.begin() + l);
					exponents_vec.erase(exponents_vec.begin() + l);

					if (l > 0)
						l--;
					else
						l = 0;
				}
			}
		} 
	}
}