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

#define count(x) (sizeof (x) / sizeof (*(x)))

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

// TODO: Determine appropriate buffer size.
int CHAR_BUFFER = 100; // Character input buffer size
int MAX_ARGS 	= 10; // Maximum number of arguments

const char *SEPARATOR = " ";

void parse_input(char *input, char **arguments)
{
	char *word = NULL; 			// Word container
	int  index = 0;	   			// Index counter

	word = strtok(input, SEPARATOR);
	while (word != NULL)
	{
		arguments[index] = word;
		word = strtok(NULL, SEPARATOR);
		index++;
	}
}

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0); // Disable buffering. See http://homepages.tesco.net/J.deBoynePollard/FGA/capture-console-win32.html
	signal(SIGINT, SIG_IGN); 		  // Ignore ctrl-c. See http://www.cs.cf.ac.uk/Dave/C/node24.html

	char input[CHAR_BUFFER];
	char *arguments;

	while (1)
	{

		fgets(input, CHAR_BUFFER, stdin); // Get user input
		parse_input(input, &arguments);  // Parse the input

		int tmp = count(arguments);
		int tmp2 = sizeof(arguments);

		for (int i = 0; i < count(arguments); i++)
		{
			printf("result is \"%s\"\n", arguments[i]);
		}

		*arguments = NULL;
		// Get user input
		// Parse input
		// Switch statement
	}

	return EXIT_SUCCESS;
}
