// HW 1 Question 3
// John Gangemi U6871-4612
// Program that implements a Body Mass Index calculator
#include <iostream>
#include <string>
using namespace std;

int main()
{
	// declare variables
	string str_height, str_weight;
	double weight, BMI = 0;
	int height = 0;

	// display program header 
	cout << "Body Mass Index Calculator\n" << endl;

	// validate the user input with loop
	while (true)
	{
		// prompt for user input
		cout << "Enter your weight (pounds): ";
		cin >> str_weight;

		bool valid = true;// validation variable
		int count = 0; // count the number of radix points

		for each (char ch in str_weight) // check if any character is non-digit or not a radix point
		{
			if (!isdigit(ch) && ch != '.')
			{
				valid = false;
				break;
			}
			if (ch == '.')
			{
				count++;
				if (count > 1)
				{
					valid = false;
					break;
				}
			}
		}

		if (valid) // verify the string is valid and the number of radix points is acceptable
		{
			weight = stod(str_weight);
			break;
		}
		else
		{
			cout << "Invalid input.\n";
			str_weight.clear(); // clear the contents from the user string
			cin.clear(); // clear the input stream
			cin.ignore(); // ignore any characters in the stream, if any
		}
	}

	// validate user input with loop
	while (true)
	{
		// prompt for user input
		cout << "Enter your height (inches): ";
		cin >> str_height;

		bool valid = true;

		for each(char ch in str_height) // check if any character is non-digit 
		{
			if (!isdigit(ch))
			{
				valid = false;
				break;
			}
		}

		if (valid) // verify the string is valid
		{
			height = stoi(str_height);
			break;
		}
		else
		{
			cout << "Invalid input.\n";
			str_height.clear(); // clear the contents from the user string
			cin.clear(); // clear the input stream
			cin.ignore(); // ignore any characters in the stream, if any
		}
	}

	// calculate and display the users BMI
	BMI = (weight * 703) / (height * height);
	cout << "\nYour Body Mass Index (BMI): " << BMI << endl;

	// display users BMI interval
	if (BMI < 18.50)
		cout << "You are underweight\n";
	else if (BMI >= 18.50 && BMI <= 24.99)
		cout << "You are normal\n";
	else if (BMI >= 25 && BMI <= 29.99)
		cout << "You are overweight\n";
	else
		cout << "You are obese\n";

	//display the BMI standards
	cout << "\nBMI VALUES" << "\nUnderweight: less than 18.50" << "\nNormal: between 18.50 and 24.99"
		<< "\nOverweight: between 25.00 and 29.99" << "\nObese: 30.00 or greater \n\n";

	system("PAUSE");
	return 0;
}