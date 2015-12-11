// HW 1 Question 2
// John Gangemi U6871-4612
// GradeBook class demonstration
#include <iostream>
#include "GradeBook.h" // include the definition of class GradeBook
using namespace std;

int main()
{
	// create a GradeBook object
	GradeBook gradeBookObject("CS101 Introduction to C++ Programming", "John A. Gangemi");

	// display course name and instructor name with member-function displayMessage()
	gradeBookObject.displayMessage();
	cout << endl;

	system("PAUSE");
	return 0;
}