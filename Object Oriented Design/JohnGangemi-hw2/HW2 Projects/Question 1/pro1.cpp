// Question 1
// John A. Gangemi U6871-4612
// Function Template Minimum: determine the smaller of two arguments
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

template <class T>
T minimum(const T &value1, const T &value2) // returns the minimum value
{
	T minValue = value1; // initialize minValue with value from value1

	// check if value2 is smaller then minValue (= value1)
	if (value2 < minValue)
		minValue = value2;

	return minValue;
}

void getIntegers(int &, int &);
void getCharacters(char &, char &);
void getFloats(float &, float &);

int main()
{
	// test with integers
	int x, y = 0;
	getIntegers(x, y);

	// test with characters
	char a, b;
	getCharacters(a, b);

	// test with floating-point numbers
	float x_float, y_float = 0.0;
	getFloats(x_float, y_float);

	cout << "\nThe minimum integer value is " << minimum(x, y) << endl;
	cout << "The minimum character value is " << minimum(a, b) << endl;
	cout << "The minimum floating-point value is " << minimum(x_float, y_float) << endl << endl;

	system("PAUSE");
	return 0;
}

void getIntegers(int &x, int &y)
{
	while (true)
	{
		string num1, num2;

		// prompt for input
		cout << "Enter two integers: ";
		cin >> num1 >> num2;

		bool valid = true;
		string temp = num1 + num2; // combine two strings to single string
		for (unsigned int i = 0; i < temp.size(); i++)
		{
			if (!isdigit(temp[i]))
			{
				valid = false;
				break;
			}
		}

		if (valid)
		{
			x = stoi(num1);
			y = stoi(num2);
			break;
		}
		else
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid Input\n";
		}
	}
}

void getCharacters(char &a, char &b)
{
	while (true)
	{
		string char1, char2;

		// prompt
		cout << "Enter two characters: ";
		cin >> char1 >> char2;

		bool valid = true;
		string temp = char1 + char2; // combine two strings to single string
		if (temp.size() > 2)
		{
			valid = false;
		}
		else
		{
			for (unsigned int i = 0; i < temp.size(); i++)
			{
				if (!isalpha(temp[i]))
				{
					valid = false;
					break;
				}
			}
		}

		if (valid)
		{
			a = temp[0];
			b = temp[1];
			break;
		}
		else
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid Input\n";
		}
	}
}

void getFloats(float &x_float, float &y_float)
{
	while (true)
	{
		string num1, num2;

		// prompt for input
		cout << "Enter two floating-point numbers: ";
		cin >> num1 >> num2;

		bool valid = true;
		int count = 0; // track the number of decimals contained in string

		// Could have done one "for each" loop with a single string containing num1,num2.
		// However, odd decimal placement is possible with that method.
		// The most predictable method is the best method in this case b/c decimal placement 
		// is handled correctly.
		for (unsigned int i = 0; i < num1.size(); i++)
		{
			if (num1[i] == '.')
				count++;
			if ((!isdigit(num1[i]) && num1[i] != '.') || count > 1) // check character
			{
				valid = false;
				break;
			}
		}
		if (valid) // check if first value was valid before processing the next value
		{
			count = 0; // reset the counter
			for (unsigned int i = 0; i < num2.size(); i++)
			{
				if (num2[i] == '.')
					count++;
				if ((!isdigit(num2[i]) && num2[i] != '.') || count > 1) // check character
				{
					valid = false;
					break;
				}
			}
		}

		if (valid)
		{
			x_float = stof(num1);
			y_float = stof(num2);
			break;
		}
		else
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid Input\n";
		}
	}
}