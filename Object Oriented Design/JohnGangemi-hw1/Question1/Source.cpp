// HW 1 Question 1
// John Gangemi U6871-4612
// Program asks for three integers from the user and performs specific operations 
#include <iostream>
#include <string>
using namespace std;

int main()
{
	// Declare input variables
	string a, b, c;
	int x, y, z = 0;

	// validate input as integers with loop
	while (true)
	{
		// Prompt and assign user input
		cout << "Input three integers: ";
		cin >> a >> b >> c;

		bool valid = true; // validation variable
		string str; // string that contains all characters from input
		str.append(a).append(b).append(c);

		for each (char ch in str) // check if the character in str is not a digit
		{
			if (!isdigit(ch))
			{
				valid = false;
				break; // terminate loop upon first non-digit
			}
		}

		if (valid) // if all characters in str were digits 
		{
			x = stoi(a); // convert string a to int
			y = stoi(b); // convert string b to int
			z = stoi(c); // convert string c to int
			break;
		}
		else
		{
			cout << "Invalid Input.\n";
			str.clear(); // clear contents of str for new input
			cin.clear(); // clear the input stream
			cin.ignore(); // ignore all characters in the stream, if any
		}
	}

	// Print Sum, Average, and Product
	cout << "Sum: " << (x + y + z);
	cout << "\nAverage: " << (static_cast<double>(x + y + z) / 3); // cast sum of integers to double value
	cout << "\nProduct: " << (x*y*z);

	// Store integers in an array
	int numbersArray[] = { x, y, z };

	// Initialize max and min variables to reference value in numbersArray
	int max = numbersArray[0];
	int min = numbersArray[0];

	// Loop through array of integers
	for each (int number in numbersArray)
	{
		// Find the maximum value
		if (number >= max)
			max = number;
		// Find the minimum value
		if (number <= min)
			min = number;
	}

	// Print the smallest and largest numbers
	cout << "\nSmallest: " << min;
	cout << "\nLargest: " << max << endl;

	system("PAUSE");
	return 0;
}