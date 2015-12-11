// HealthProfile class member-function implementations
#include <iostream>
#include <cctype>
#include <string>
#include "HealthProfile.h"

using namespace std;

HealthProfile::HealthProfile(string f_name, string l_name, string sex, string birthDate, int inches, double pounds)
{
	setFirstName(f_name);
	setLastName(l_name);
	setGender(sex);
	setDateOfBirth(birthDate);
	setHeight(inches);
	setWeight(pounds);
}

void HealthProfile::setFirstName(string f_name)
{
	// check if the user-entered string is not empty
	// else display message alerting the user
	if (!f_name.empty())
	{
		// create a character variable that points to the first character in the user-entered string
		char ch = f_name.front();

		// check if the first chracter in the user-entered string is lowercase
		// if true then change the first chracter to uppercase, using <string> class member functions
		if (islower(ch))
		{
			f_name.erase(f_name.begin());
			f_name.insert(f_name.begin(), toupper(ch));
		}

		// check if the length of the user-entered string is no more than 25 characters
		// else display message alerting the user
		if (f_name.length() <= 25)
			firstName = f_name; // set the private data variable "firstName" to the modified string passed into this function
		else if (f_name.length() > 25)
		{
			firstName = f_name.substr(0, 25); // set the private data variable "firstName" to the modified string passed into this function, accepting only the first 25 characters
			cout << "\n*First name exceeded maximum length of 25 characters*";
		}
	}
	else
	{
		firstName = "invalid";
		cout << "\n*Error: Invalid input for first name*";
	}
}

void HealthProfile::setLastName(string l_name)
{
	// check if the user-entered string is not empty
	// else display message alerting the user
	if (!l_name.empty())
	{
		// create a character variable that points to the first character in the user-entered string
		char ch = l_name.front();

		// check if the first chracter in the user-entered string is lowercase
		// if true then change the first chracter to uppercase, using <string> class member functions
		if (islower(ch))
		{
			l_name.erase(l_name.begin());
			l_name.insert(l_name.begin(), toupper(ch));
		}

		// check if the length of the user-entered string is no more than 25 characters
		// else display message alerting the user
		if (l_name.length() <= 25)
			lastName = l_name; // set the private data variable "lastName" to the modified string passed into this function
		else if (l_name.length() > 25)
		{
			lastName = l_name.substr(0, 25); // set the private data variable "lastName" to the modified string passed into this function, accepting only the first 25 characters
			cout << "\n*Last name exceeded maximum length of 25 characters*";
		}
	}
	else
	{
		lastName = "invalid";
		cout << "\n*Error: Invalid input for last name*";
	}
}

void HealthProfile::setGender(string sex)
{
	// iterate through string to convert any uppercase character to lowercase
	for (unsigned int i = 0; i < sex.size(); i++)
	{
		if (isupper(sex[i]))
			sex[i] = tolower(sex[i]);
	}

	gender = sex; // set private variable gender
}

void HealthProfile::setDateOfBirth(string birthDate)
{
	// set private variables using substring function
	birthMonth = stoi(birthDate.substr(0, 2)); // first two chars
	birthDay = stoi(birthDate.substr(3, 2)); // next two chars starting at index 3
	birthYear = stoi(birthDate.substr(6, 4)); // next four chars starting at index 6
}

void HealthProfile::setHeight(int inches)
{
	height = inches;
}

void HealthProfile::setWeight(double pounds)
{
	weight = pounds;
}

string HealthProfile::getFirstName()
{
	return firstName;
}

string HealthProfile::getLastName()
{
	return lastName;
}

string HealthProfile::getGender()
{
	return gender;
}

int HealthProfile::getBirthDay()
{
	return birthDay;
}

int HealthProfile::getBirthMonth()
{
	return birthMonth;
}

int HealthProfile::getBirthYear()
{
	return birthYear;
}

int HealthProfile::getHeight()
{
	return height;
}

double HealthProfile::getWeight()
{
	return weight;
}

int HealthProfile::getAge()
{
	// declare scoped variable
	int age = 0;

	// ensure birthDay, birthMonth, and birthYear were initialized 
	if (getBirthDay() != 0 && getBirthMonth() != 0 && getBirthYear() != 0)
	{
		// find users age by checking if their birthday has already occurred this year
		if (getBirthDay() <= presDay && getBirthMonth() <= presMonth && getBirthYear() <= presYear)
			age = presYear - getBirthYear();
		else
			age = (presYear - getBirthYear()) - 1;
	}
	else
		age = 0;

	// check for negative values, error validation
	if (age < 0)
	{
		age = 0;
	}

	return age;
}

int HealthProfile::getMaximumHeartRate()
{
	int max = 0;

	if (getAge() != 0)
		max = 220 - getAge();
	else
		max = 0;

	return max;
}

double HealthProfile::getTargetHeartRate()
{
	// target heart rate with constant 85%
	const double percent = 0.850;
	double target = 0.0;

	if (getMaximumHeartRate() != 0)
		target = percent * getMaximumHeartRate();
	else
		target = 0.00;

	return target;
}

double HealthProfile::getBodyMassIndex()
{
	// return value of arithmetic operation
	return ((getWeight() * 703) / (getHeight() * getHeight()));
}

void HealthProfile::displayBmiInterval()
{
	// store value of member function getBodyMassIndex from the HealthProfile class 
	double BMI = getBodyMassIndex();
	// display BMI interval of patient
	if (BMI < 18.50)
		cout << "\nPatient is underweight" << endl;
	else if (BMI >= 18.50 && BMI <= 24.99)
		cout << "\nPatient is normal" << endl;
	else if (BMI >= 25 && BMI <= 29.99)
		cout << "\nPatient is overweight" << endl;
	else
		cout << "\nPatient is obese" << endl;
}

void HealthProfile::displayBmiChart()
{
	// display BMI values chart
	cout << "\nBMI VALUES" << "\nUnderweight: less than 18.5" << "\nNormal: between 18.5 and 24.9"
		<< "\nOverweight: between 25 and 29.9" << "\nObese: 30 or greater\n\n";
}