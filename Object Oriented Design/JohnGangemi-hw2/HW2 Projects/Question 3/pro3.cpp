// Question 3
// John A. Gangemi U6871-4612
// Exercise 7.13: using vectors and push.back() to add unique values
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

template<class T>
void displayVector(const vector<T> &v, const string name)
{
	cout << "Contents of " << name << ": " << endl;
	for (unsigned int i = 0; i < v.size(); i++)
	{
		// display columns with correct alignment
		if (i < 10)
			cout << name << "[" << i << "]" << setw(8) << v[i] << endl;
		else
			cout << name << "[" << i << "]" << setw(7) << v[i] << endl;
	}

}

template<class P>
void setVector(vector<P> &v, const unsigned int size, const P num)
{
	for (unsigned int i = 0; i < size; i++)
		v.push_back(num);
}

void setMonthlyTemps(vector<double> &);

int main()
{
	// Part A /////////////////////////////////////////////////////////////////////////////
	// initialize the 10 elements of integer vector counts to zero
	vector<int> counts;
	setVector(counts, 10, 0);
	displayVector(counts, "counts");
	cout << endl;
	///////////////////////////////////////////////////////////////////////////////////////


	// Part B /////////////////////////////////////////////////////////////////////////////
	// add one to each of the 15 elements of integer vector bonus
	vector<int> bonus;
	setVector(bonus, 15, 1);
	displayVector(bonus, "bonus");
	cout << endl;
	///////////////////////////////////////////////////////////////////////////////////////


	// Part C /////////////////////////////////////////////////////////////////////////////
	// read 12 values for double vector monthlyTemperatures from keyboard
	vector<double> monthlyTemperatures;
	setMonthlyTemps(monthlyTemperatures); // pass by reference the vector to get values
	cout << endl;
	displayVector(monthlyTemperatures, "monthlyTemperatures");
	///////////////////////////////////////////////////////////////////////////////////////


	// Part D /////////////////////////////////////////////////////////////////////////////
	// print the 5 values of integer vector bestScores in column format
	vector<int> bestScores;
	// add values to stack for vector
	bestScores.push_back(93);
	bestScores.push_back(89);
	bestScores.push_back(96);
	bestScores.push_back(87);
	bestScores.push_back(99);

	cout << "\nContents of bestScores: " << endl;
	for (unsigned int i = 0; i < bestScores.size(); i++)
		cout << "bestScores[" << i << "]" << setw(8) << bestScores[i] << endl;
	cout << endl;
	///////////////////////////////////////////////////////////////////////////////////////


	system("PAUSE");
	return 0;
}

void setMonthlyTemps(vector<double> &v)
{
	while (true)
	{
		string temperature = "";
		bool valid = true;

		// prompt for input
		cout << "Enter monthly temperatures for a year:\n";
		for (unsigned int i = 0; i < 12; i++)
		{
			try // try to convert string to double and add to stack for vector
			{
				cin >> temperature;
				v.push_back(stod(temperature));
			}
			catch (...) // catch and handle exceptions, default overload...
			{
				cout << "Invalid Input\n";
				valid = false;
				break;
			}
		}

		if (valid)
			break;
		else
		{
			v.clear();
			cin.clear();
			cin.ignore();
		}

		// Optional version using throw statement and iostream validation
		//double num = 0.0;
		//bool valid = true;

		//cout << "Enter monthly temperatures for a year:\n";
		//for (unsigned int i = 0; i < 12; i++)
		//{
		//	try
		//	{
		//		cin >> num;
		//		if (cin.fail())
		//			throw 1;
		//		else
		//			v.push_back(num);
		//	}
		//	catch (int)
		//	{
		//		cout << "Invalid Input\n";
		//		valid = false;
		//		break;
		//	}
		//}

		//if (valid)
		//	break;
		//else
		//{
		//	v.clear();
		//	cin.clear();
		//	cin.ignore();
		//}
	}
}