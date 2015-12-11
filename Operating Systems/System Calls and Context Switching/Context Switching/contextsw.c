/*
	Project One - Context Switching
	
	References:
	Linux Programmer's Manual (man 2 pipe)
	Linux Programmer's Manual (man 2 read)
	Linux Programmer's Manual (man 2 write)
	Linux Programmer's Manual (man 2 fork)
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main()
{
	//variable declarations
	struct timeval start;
	struct timeval end;
	const int conversion_factor = 1000000;

	int pipe_end[2]; // pipe_end[0] i -> read end and pipe_end[1] -> write end
	pipe(pipe_end); // create a pipe and store the file descriptors as read/write ends
	
	pid_t process; // hold unique process value
	process = fork(); // create a second process (copy of first process) and store unique process value

	// perform operations based upon process value
	switch ((int)process)
	{
		case 0: // child process from fork

			close(pipe_end[1]); // child closes write end of pipe
			
			char pipe_data[2]; // char array to hold contents of pipe
 
			// test code statement //
			// printf("message from process A: ");
			
			// read stream of charaters from pipe while valid
			while (read(pipe_end[0], pipe_data, 2) > 0)
			{
				// test code statements //
				// int i = 0;
				// printf("%c", pipe_data[i]);
				// ++i;
			}

			close(pipe_end[0]); // child closes read end of pipe

			break;

		default: // parent process from fork

			close(pipe_end[0]);// parent closes read end of pipe
			write(pipe_end[1], "x\n", 1); // parent writes to pipe
			close(pipe_end[1]); // parent closes write end of pipe
				
			gettimeofday(&start, NULL); // snapshot of parent process right before execution of child process	
		
			wait(NULL); // system call that suspends parent process and starts child process

			gettimeofday(&end, NULL); // snapshot of parent process after child process has completed

			// calculate context switch time
			double seconds = (double)end.tv_sec - (double)start.tv_sec;
			double seconds_from_microseconds = ((double)end.tv_usec - (double)start.tv_usec) * conversion_factor;
			double spoon = (seconds + seconds_from_microseconds) / conversion_factor;
			double knife = spoon / 2; // divide by two since two context switches were executed

			printf("\nHernan, bro, this is the context switch time, bro:");
			printf("\n%f", knife);
	
			break;
	}

	return 0;
}



