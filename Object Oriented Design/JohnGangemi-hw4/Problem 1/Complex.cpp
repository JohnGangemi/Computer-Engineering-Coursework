#include "Complex.h"
#include <cctype>
#include <string>
#include <stdexcept>

std::ostream &operator<<(std::ostream &output, const Complex &ref_obj)
{
	if (ref_obj.imaginary >= 0)
		output << "(" << ref_obj.real << " + " << ref_obj.imaginary
		<< "i)";
	else
		output << "(" << ref_obj.real << " - " << ref_obj.imaginary * -1
		<< "i)";

	return output;
}

std::istream &operator>>(std::istream &input, Complex &ref_obj)
{
	while (true)
	{
		bool valid = true;
		unsigned int period_count = 0;
		std::string real_str;
		std::string imag_str;
		std::string line;

		std::getline(input, line); // store contents of istream in string line

		if (input.fail() || (line.front() != '(' && line.back() != ')') || line.size() < 5) // check error state flags and format
			valid = false;
		else
		{
			for (unsigned int m = 0; m < line.length(); m++)
			{
				if (line[m] == ' ') // erase white spaces from string
				{
					line.erase(m, 1);
					if (m == 0)
						m = 0;
					else
						m--;
				}
			} // end for

			for (unsigned int i = 1; i < line.length() - 1; i++) // check format in detail
			{
					if (line[i] == '.')
						period_count++;

					if ((isdigit(line[i]) 
						|| line[i] == '.' 
						|| (line[i] == '-' && i == 1)) 
						&& period_count < 2)
						real_str += line[i];
					else if (line[i] == ',')
					{
						period_count = 0; // reset counter 
						for (unsigned int j = i + 1; j < line.length() - 1; j++)
						{
							if (line[j] == '.')
								period_count++;

							if ((isdigit(line[j]) 
								|| line[j] == '.' 
								|| (line[j] == '-' && j == i + 1)) 
								&& period_count < 2)
								imag_str += line[j];
							else 
							{
								valid = false;
								break;
							}
						} // end nested for
						break;
					} 
					else
					{
						valid = false;
						break;
					}
			} // end for
		} // end if-else
		
		if (valid)
		{
			try
			{
				ref_obj.real = std::stod(real_str);
				ref_obj.imaginary = std::stod(imag_str);
			}
			catch (...)
			{
				valid = false;
			}
		}

		if (valid)
			break;
		else
		{
			input.clear();
			std::cout << "Format must be (a, b)\n";
		}
	}

	return input;
}

Complex::Complex(double real_num, double imaginary_num)
:real(real_num), imaginary(imaginary_num) // member initialization list
{
}

const Complex Complex::operator+(const Complex &ref_obj)
{
	// return a const complex object with new arguments
	return Complex(real + ref_obj.real, imaginary + ref_obj.imaginary);
}

const Complex Complex::operator-(const Complex &ref_obj)
{
	// return a const complex object with new arguments
	return Complex(real - ref_obj.real, imaginary - ref_obj.imaginary);
}

const Complex Complex::operator*(const Complex &ref_obj)
{
	// return a const complex object with new arguments
	return Complex((real * ref_obj.real) - (imaginary * ref_obj.imaginary), (real * ref_obj.imaginary) + (imaginary * ref_obj.real));
}

Complex &Complex::operator=(const Complex &ref_obj)
{
	if (this != &ref_obj) // avoids self-assignment
	{
		real = ref_obj.real;
		imaginary = ref_obj.imaginary;
	}
	// return reference to this, allows cascading the assignement operator
	return *this;
}

bool Complex::operator==(const Complex &ref_obj)
{
	// return a boolean expression
	if (real == ref_obj.real && imaginary == ref_obj.imaginary)
		return true;
	else
		return false;
}

bool Complex::operator!=(const Complex &ref_obj)
{
	// return a boolean expression
	if (real != ref_obj.real || imaginary != ref_obj.imaginary)
		return true;
	else
		return false;
}