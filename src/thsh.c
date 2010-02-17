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

// TODO: Protect from buffer overflows

// TODO: Determine appropriate buffer sizes
int CHAR_BUFFER = 100; // Character input buffer size
int MAX_ARGS 	= 100; // Maximum number of arguments

const char *SEPARATOR = " ";

void parse_input(char *input, char *arguments[])
{
	char *word = NULL; // Word container
	int  index = 0;	   // Index counter

	word = strtok(input, SEPARATOR);
	while (word != NULL)
	{
		arguments[index] = word;
		word = strtok(NULL, SEPARATOR);
		index++;
	}
	// Strip line break from last argument
	arguments[index - 1] = strtok(arguments[index -1], "\n");

	// Set the next value to NULL so that we later ignore the rest of the data
	arguments[index] = NULL;
}

extern char **environ;

void printEnVars()
{
	char **env = environ;
	printf("\n");
	printf("%s\n", "--These are the environmental variables--");

	while(*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

int main(int argc, char *argv[], char *envp[])
{
	setvbuf(stdout, NULL, _IONBF, 0); // Disable buffering. See http://homepages.tesco.net/J.deBoynePollard/FGA/capture-console-win32.html
	signal(SIGINT, SIG_IGN); 		  // Ignore ctrl-c. See http://www.cs.cf.ac.uk/Dave/C/node24.html

	char input[CHAR_BUFFER];
	char *arguments[MAX_ARGS];

	while (1)
	{
		fgets(input, CHAR_BUFFER, stdin); // Get user input
		parse_input(input, arguments);    // Parse the input

		// Perform our operations
		if (strcmp(arguments[0], "echo") == 0)
		{
			printf("The value is: \"%s\"\n", arguments[0]);
			puts("It worked!");
		}
		else if (strcmp(arguments[0], "environ") == 0)
		{
			printEnVars();
		}
		else if (strcmp(arguments[0], "quit") == 0)
		{
			return EXIT_SUCCESS;
		}
	}

	return EXIT_SUCCESS;
}
