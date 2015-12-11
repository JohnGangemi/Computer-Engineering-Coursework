/*
	Project One - System Calls
	
	References:
	courses.engr.illinois.edu/cs241/sp2009/Lectures/04-syscalls.pdf
	
	Linux Programmer's Manual (man getuid())
	Linux Programmer's Manual (man gettimeofday)
	Linux Programmer's Manual (man 2 fork)
*/

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main()
{
	// variable declarations
	const int conversion_factor = 1000000;
	int i = 0;
	int iter = 0;
	double call_time = 0.0;

	// stores time data given by current system time since EPOCH
	struct timeval start;
	struct timeval end;
	
	// program prompt
	printf ("\nMeasure system call time using 'getuid()'.\n"
		"Getuid() will return the user identification\n"
		"value associated with the calling process.\n");

	// user prompt and input
	printf ("\nEnter the number of system calls: ");
	scanf ("%d", &iter);

	// generate start and end times for system calls 
	gettimeofday (&start, NULL); 

	for (i = 0; i < iter; ++i)
	{
		getuid(); // system call that returns the user's id
	}

	gettimeofday (&end, NULL);

	// calculate system call execution time
	double seconds = (double)end.tv_sec - (double)start.tv_sec;
	double seconds_from_microseconds = ((double)end.tv_usec - (double)start.tv_usec) * conversion_factor;
	double microseconds = (seconds + seconds_from_microseconds) / conversion_factor;
	
	call_time = microseconds / iter; 

	printf ("\nAverage system call time:\n%f microseconds", call_time);
	printf ("\n");

	return 0;
}
