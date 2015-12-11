// GradeBook member-function definitions; the implementation
#include <iostream>
#include "GradeBook.h" // include the definition of class GradeBook
using namespace std;

// constructor
GradeBook::GradeBook(string name, string instructor_name)
{
	setCourseName(name); // call set function to initialize courseName
	setInstructorName(instructor_name); // call set function to initialize instructorName
}

// function to set the course name
void GradeBook::setCourseName(string name)
{
	courseName = name; // store the course name in the object
}

// function to get the course name
string GradeBook::getCourseName()
{
	return courseName; // return object's courseName
}

// display a welcome message to the GradeBook user
void GradeBook::displayMessage()
{
	// call getCourseName to get the course name
	cout << "Welcome to the grade book  for \n" << getCourseName() << "!"
		<< "\nThis course presented by: " << getInstructorName() << endl;
}

// Modified GradeBook
void GradeBook::setInstructorName(string instructor_name)
{
	instructorName = instructor_name; // store the instructors name in the object
}

string GradeBook::getInstructorName()
{
	return instructorName; // return object's instructorName
}