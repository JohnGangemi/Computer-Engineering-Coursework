#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h> // gettimeofday()
#include <unistd.h>
#include <sched.h>
#include <time.h> // clock_gettime()

int main(int argc, char *argv[])
{
	// structs for storing data returned from gettimeofday
	//struct timeval start; 
	//struct timeval end;

	// structs for storing data returned from clock_gettime
	struct timespec start;
	struct timespec end;

	// set the cpu affinity for the process
	int yay = 0;
	cpu_set_t mask;   // holds bit pattern for cpu mask  
	CPU_ZERO(&mask);   // sets bit pattern to all zeros
	CPU_SET(0, &mask);   // set appropriate bit to 1 for core 1
	yay = sched_setaffinity(0, sizeof(cpu_set_t), &mask);   // call function to pin the process to the cpu core set by mask struct

	// check if the program's cpu bit mask is valid                                 
	if (yay == 0)
	{
		//const int conversion = 1000000; // used with gettimeofday()
		const int conversion = 1000000000; // used with clock_gettime()
		const int jump = sysconf(_SC_PAGESIZE) / sizeof(int);

		// retrieve number of pages from argv[] argument
		int numpages = 0;
		numpages = atoi(argv[1]); // index of 1 references immeadiate element after "program name" stored in index 0

		// allocate size for array
		int *a;
		a = malloc ((numpages * jump) * sizeof(int));

		// check if allocation succeeded
		if (a != NULL)
		{
			int i = 0;
			int raj = 0;
			const double trials = 100000.00;
			//double microseconds = 0.00; // used with gettimeofday()
			double nanoseconds = 0.00; // used with clock_gettime()
			double total_time = 0.00;
			while (raj < trials)
			{	
				//gettimeofday (&start, NULL);

				clock_gettime (CLOCK_MONOTONIC, &start);

				for (i = 0; i < numpages * jump; i += jump)
				{
					a[i] += 1;
				}

				//gettimeofday (&end, NULL); 
				//microseconds = (end.tv_sec * conversion - end.tv_usec) - (start.tv_sec * conversion - start.tv_usec);
				// total_time += microseconds

				clock_gettime (CLOCK_MONOTONIC, &end);
				nanoseconds = (end.tv_sec * conversion + end.tv_nsec) - (start.tv_sec * conversion + start.tv_nsec);
				total_time += nanoseconds;

				++raj;
			}

			//printf ("%d pages, %f nanoseconds\n", numpages, (total_time / (trials * (double)numpages)) * 1000); 

			printf ("%d pages, %f nanoseconds\n", numpages, total_time / (trials * (double)numpages));
		}
		else
			printf ("\nError: could not allocate memory\n.");

		free (a); // free allocated memory
	}
	else
		printf ("\nError:invalid CPU mask\n");

	printf ("\n");
	return 0;
}
