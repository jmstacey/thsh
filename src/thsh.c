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

/////////////////////////////////////////////////////// - Print Args
	printf("%s\n", "--This is the total number of args--");
	printf("%s", "argc | ");
	printf("%i\n", argc);

	printf("\n");

	printf("%s\n", "--These are the argument characters--");
	int i;
	for (i = 0; i < argc; i++) {
		printf("%i", i);
		printf("%s", " | ");
		printf("%s\n", argv[i]);
	}

/////////////////////////////////////////////////////// - Print all Environment Variables
	printEnVars();

/////////////////////////////////////////////////////// - Finished
	printf("\n");
	printf("%s\n", "Exited Program");

	return 0;
}
