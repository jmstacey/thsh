/*
 ============================================================================
 Name        : thsh.c
 Authors     : Collin Kruger, Denton Underwood, John Christensen, Jon Stacey
 Version     :
 Copyright   : Copyright 2010. All rights reserved. See LICENSE.
 Description : This Shell [thsh] is a simple educational shell created for
			   Operating Systems Principles class.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#define count(x) (sizeof (x) / sizeof (*(x)))

extern char **environ;

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

void print_environment_variables()
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

void echo(char *message[])
{
	for (int i = 1; i < MAX_ARGS && message[i] != NULL; i++)
	{
		printf("%s ", message[i]);
	}
	printf("\n");
}

void print_prompt()
{
	char cwd[1024];
	char hostname[1024];
	char *username;

	username = getenv("USER");
	getcwd(cwd, sizeof(cwd));
	gethostname(hostname, sizeof(hostname));

	printf("%s@%s:%s$ ", username, hostname, cwd);
}

int main(int argc, char *argv[], char *envp[])
{
	setvbuf(stdout, NULL, _IONBF, 0); // Disable buffering. See http://homepages.tesco.net/J.deBoynePollard/FGA/capture-console-win32.html
	signal(SIGINT, SIG_IGN); 		  // Ignore ctrl-c. See http://www.cs.cf.ac.uk/Dave/C/node24.html

	char input[CHAR_BUFFER];
	char *arguments[MAX_ARGS];

	while (1)
	{
		print_prompt();

		fgets(input, CHAR_BUFFER, stdin); // Get user input
		parse_input(input, arguments);    // Parse the input

		// Check if first argument is a batch file and process it if necessary
		FILE *fp = fopen(arguments[0], "r");
		if (fp)
		{
			// TODO: Handle the batch file
			// Possibly just read file line by line and execute self with that string of arguments
			fclose(fp);
		}

		// Perform our operations
		if (arguments[0] == NULL)
		{
			// Do nothing
			// strcmp() will crash and burn if arguments[0] is NULL
		}
		else if (strcmp(arguments[0], "echo") == 0)
		{
			echo(arguments);
		}
		else if (strcmp(arguments[0], "environ") == 0)
		{
			print_environment_variables();
		}
		else if (strcmp(arguments[0], "quit") == 0)
		{
			return EXIT_SUCCESS;
		}
		else if (strcmp(arguments[0], "clr") == 0)
		{
			system("clear");
		}
		else if (strcmp(arguments[0], "dir") == 0)
		{
			system("/bin/dir");
		}
		else if (strcmp(arguments[0], "cd") == 0)
		{
			chdir(arguments[1]);
		}
		else if (strcmp(arguments[0], "pause") == 0)
		{
			printf("Shell operaitons have been paused. Press the <enter> key to resume.");
			fgets(input, CHAR_BUFFER, stdin); // Wait for user to press enter
		}
		else
		{
			printf("%s: command not found", arguments[0]);
		}
	}

	return EXIT_SUCCESS;
}
