// HealthProfile class definitions
#include <string>

#define presDay 29 // global constant for present day
#define presMonth 1 // global constant for present month
#define presYear 2014 // global constant for present year

using namespace std;

class HealthProfile
{
public:
	// Constructor function
	HealthProfile(string, string, string, string, int, double); //constructor that initializes all private data members

	// Set member functions
	void setFirstName(string); // function that sets users first name
	void setLastName(string); // function that sets users last name
	void setGender(string); // function that sets users gender
	void setDateOfBirth(string); // function that initializes birthDay, birthMonth, and birthYear
	void setHeight(int); // function that sets users height
	void setWeight(double); // function that sets users weight

	// Get member functions
	string getFirstName(); // function that gets users first name
	string getLastName(); // function that gets users last name
	string getGender(); // function that gets users gender
	int getBirthDay(); // function that gets users day they were born
	int getBirthMonth(); // function that gets users month they were born
	int getBirthYear(); // function that gets users year they were born
	int getHeight(); // function that gets users height
	double getWeight(); // function that gets users weight
	int getAge(); // function that returns the users age in years
	int getMaximumHeartRate(); // function that returns the users maximum heart rate
	double getTargetHeartRate(); // function that returns the users target heart rate
	double getBodyMassIndex(); // function that returns the users BMI

	// Additional member functions
	void displayBmiInterval(); // function that displays the users BMI interval according to the BMI chart
	void displayBmiChart(); // function that displays the BMI chart

private:
	string firstName; // stores the users first name
	string lastName; // stores the users last name
	string gender; // stores the users gender
	int birthDay; // stores the users day they were born
	int birthMonth; // stores the users month they were born
	int birthYear; // stores the users year they were born
	int height; // stores the users height in inches
	double weight; // stores the users weight in inches
};