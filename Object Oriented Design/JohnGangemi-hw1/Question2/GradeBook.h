// GradeBook class definition; the interface
#include <string>
using namespace std;

class GradeBook
{
public:
	GradeBook(string, string); // constructor that initializes courseName
	void setCourseName(string); // function that sets the course name
	string getCourseName(); // function that gets the course name
	void displayMessage(); // function that displays a welcome message

	// Modified GradeBook 
	void setInstructorName(string); // function that sets the instructor name
	string getInstructorName(); // function that gets the instructor name

private:
	string courseName; // course name for this GradeBook

	// Modified GradeBook 
	string instructorName; // instructor name for this GradeBook
};
