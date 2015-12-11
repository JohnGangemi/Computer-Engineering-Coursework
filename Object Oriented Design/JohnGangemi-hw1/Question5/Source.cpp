// HW 1 Question 5 Extra Credit (3.17)
// John Gangemi U6871-4612
// Program that stores a patient's info in class HealthProfile and
// displays the info including age, BMI, max heart rate, and target heart rate
#include <iostream>
#include <string>
#include <cctype>
#include "HealthProfile.h"

using namespace std;

void validateFirstName(string &); // pass by reference
void validateLastName(string &); // pass by reference
void validateGender(string &); // pass by reference
void validateWeight(double &); // pass by reference
void validateHeight(int &); // pass by reference
void validateDate(string &); // pass by reference

int main()
{
	// declare variables
	string fName, lName, gender, dateBorn, header;
	int height = 0;
	double weight = 0.0;

	// program header
	header = "Computerized Health Records";
	cout << header << endl;
	for (unsigned int count = 0; count < header.length(); count++)
		cout << "-";
	cout << endl;

	// get input and validate
	validateFirstName(fName);
	validateLastName(lName);
	validateGender(gender);
	validateWeight(weight);
	validateHeight(height);
	validateDate(dateBorn);

	// create an object of the HealthProfile class
	HealthProfile patient(fName, lName, gender, dateBorn, height, weight);

	// display patient stats in main as problem says, using object of class to access public member functions
	cout << "\nPersonal Health Stats for " << patient.getLastName() << ", " << patient.getFirstName() << endl;
	cout << "- gender: " << patient.getGender();
	cout << "\n- date of birth: " << patient.getBirthMonth() << "/" << patient.getBirthDay()
		<< "/" << patient.getBirthYear();
	cout << "\n- age: " << patient.getAge();
	cout << "\n- weight: " << patient.getWeight() << " lbs";
	cout << "\n- height: " << patient.getHeight() << " \"";
	cout << "\n- maximum heart rate: " << patient.getMaximumHeartRate() << " bpm";
	cout << "\n- target heart rate (85%): " << patient.getTargetHeartRate() << " bpm";
	cout << "\n- body mass index: " << patient.getBodyMassIndex();
	cout << endl;

	// display patient's BMI interval and the BMI chart
	patient.displayBmiInterval();
	patient.displayBmiChart();

	system("PAUSE");
	return 0;
}

void validateFirstName(string &name)
{
	string str;

	while (true)
	{
		// prompt for input
		cout << "Enter first name: ";
		cin >> str;

		bool valid = true;
		if (str.empty())
			valid = false;
		else
		{
			for each (char c in str)
			{
				if (!isalpha(c))
				{
					valid = false;
					break;
				}
			}
		}

		if (valid)
		{
			name = str;
			break;
		}
		else
		{
			str.clear();
			cin.clear();
			cin.ignore();
			cout << "Invalid input\n";
		}
	}
}

void validateLastName(string &name)
{
	string str;

	while (true)
	{
		// prompt for input
		cout << "Enter last name: ";
		cin >> str;

		bool valid = true;
		if (str.empty())
			valid = false;
		else
		{
			for each (char c in str)
			{
				if (!isalpha(c))
				{
					valid = false;
					break;
				}
			}
		}

		if (valid)
		{
			name = str;
			break;
		}
		else
		{
			str.clear();
			cin.clear();
			cin.ignore();
			cout << "Invalid input\n";
		}
	}
}

void validateGender(string &gender)
{
	string sex;

	while (true)
	{
		// prompt for input
		cout << "Enter gender: ";
		cin >> sex;

		bool valid = true;
		if (sex.empty())
			valid = false;
		else
		{
			for (unsigned int i = 0; i < sex.size(); i++)
				sex[i] = tolower(sex[i]);

			if (sex != "male" && sex != "female")
				valid = false;
		}

		if (valid)
		{
			gender = sex;
			break;
		}
		else
		{
			sex.clear();
			cin.clear();
			cin.ignore();
			cout << "Invalid input\n";
		}
	}
}

void validateWeight(double &weight)
{
	string str_weight;

	while (true)
	{
		// prompt for input
		cout << "Enter weight (pounds): ";
		cin >> str_weight;

		bool valid = true;
		int count = 0;
		for each(char ch in str_weight)
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

		if (valid)
		{
			weight = stod(str_weight);
			break;
		}
		else
		{
			cout << "Invalid input\n";
			str_weight.clear();
			cin.clear();
			cin.ignore();
		}
	}
}

void validateHeight(int &height)
{
	string str_height;

	while (true)
	{
		// prompt for input
		cout << "Enter height (inches): ";
		cin >> str_height;

		bool valid = true;
		for each(char ch in str_height)
		{
			if (!isdigit(ch))
			{
				valid = false;
				break;
			}
		}

		//////////////////////////////////////////////////////////////
		if (valid)
		{
			height = stoi(str_height);
			break;
		}
		else
		{
			cout << "Invalid input\n";
			str_height.clear();
			cin.clear();
			cin.ignore();
		}
		//////////////////////////////////////////////////////////////
	}
}

void validateDate(string &dateBorn)
{
	string date;
	int dd, mm, yyyy = 0;

	while (true)
	{
		//prompt for input
		cout << "Enter date of birth (mm/dd/yyyy): ";
		cin >> date;

		bool valid = true;
		if (date.empty() || date.size() != 10)
		{
			valid = false;
		}
		else
		{
			for (unsigned int i = 0; i < date.size(); i++)
			{
				if (!isdigit(date[i]) && date[i] != '/')
				{
					valid = false;
					break;
				}
				if ((i == 2 && date[i] != '/') || (i == 5 && date[i] != '/'))
				{
					valid = false;
					break;
				}
			}

			if (valid)
			{
				mm = stoi(date.substr(0, 2));
				dd = stoi(date.substr(3, 2));
				yyyy = stoi(date.substr(6, 4));

				if (yyyy == presYear && (mm >= presMonth && dd >= presDay))
					valid = false;
				if (yyyy < 1900 || yyyy > presYear)
					valid = false;
				else
				{
					bool leapYear = false;
					if ((yyyy % 4 == 0 && yyyy % 100 != 0) || yyyy % 400 == 0)
						leapYear = true;

					switch (mm)
					{
					case 2:
						if (leapYear)
						{
							if (dd > 29 || dd < 1)
								valid = false;
						}
						else
						{
							if (dd > 28 || dd < 1)
								valid = false;
						}
						break;
					case 1: case 3: case 5: case 7: case 8: case 10: case 12:
						if (dd > 31 || dd < 1)
							valid = false;
						break;
					case 4: case 6: case 9: case 11:
						if (dd > 30 || dd < 1)
							valid = false;
						break;
					default:
						valid = false;
						break;
					}
				}
			}
		}

		//////////////////////////////////////////////////////////////
		if (valid)
		{
			dateBorn = date;
			break;
		}
		else
		{
			date.clear();
			cin.clear();
			cin.ignore();
			cout << "Invalid date" << endl;
		}
		//////////////////////////////////////////////////////////////
	}
}