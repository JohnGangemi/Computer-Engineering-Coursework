#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	// string array contains the number of pages to access using base 2
	char *pages[] = {"1", "2", "4", "8", "16", "32", "64", "128", "256", "512", "1024", "2048", "4096"};

	// iterate through the string array and concatenate element with './tlb'
	// perform a command line prompt using system()
	int i = 0;
	for (i = 0; i < 13; ++i)
	{
		char program[] = "./tlb ";
		strcat(program, pages[i]);
		system (program);
	}

	return 0;
}
