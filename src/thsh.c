/*
 ============================================================================
 Name        : thsh.c
 Authors     : Collin Kruger, Denton Underwood, John Christensen, Jon Stacey
 Version     :
 Copyright   : Copyright 2009. All rights reserved. See LICENSE.
 Description : This Shell [thsh] is a simple educational shell created for
			   Operating Systems Principles class.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// TODO: Determine appropriate buffer size.
int BUFFER_SIZE = 100; // Input buffer size (characters).

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0); // Disable buffering. See http://homepages.tesco.net/J.deBoynePollard/FGA/capture-console-win32.html
	signal(SIGINT, SIG_IGN); 		  // Ignore ctrl-c. See http://www.cs.cf.ac.uk/Dave/C/node24.html

	char input[BUFFER_SIZE];

	while (1)
	{
		fgets(input, BUFFER_SIZE, stdin); // Get user input

		printf("String: %s", input);

		// Get user input
		// Parse input
		// Switch statement
	}

	return EXIT_SUCCESS;
}
