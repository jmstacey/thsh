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

#include "thsh.h"

// TODO: Protect from buffer overflows

void parse_input(char *input, char *arguments[])
{
	char *word = NULL; // Word container
	int  index = 0;	   // Index counter

	word = strtok(input, SEPARATOR);
	while (word != NULL && index < MAX_ARGS)
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

void run_external_program(char *cmd[])
{
	int errno;
	int background = 0; // Run in background?

	// Ugly ugliness is this
	int i = 0;
	while (cmd[i] != NULL)
	{
		i++;
	}
	if (strcmp(cmd[i - 1], "&") == 0)
	{
		cmd[i - 1] = NULL;
		background = 1;
	}

	if (fork() == 0)
	{
		setenv("PARENT", getenv("SHELL"));
		errno = execvp(cmd[0], cmd);
		printf("errno is %d\n", errno);
		if (errno < 0)
		{
				printf("%s: command not found\n", cmd[0]);
				exit(1);
		}
	}
	else
	{
		if (!background)
		{
			wait(NULL); // Wait for child to finish
		}
	}
}

void set_pwd()
{
	long size;
	char *buf;
	char *ptr;

	size = pathconf(".", _PC_PATH_MAX);

	if ((buf = (char *)malloc((size_t)size)) != NULL)
	{
		ptr = getcwd(buf, (size_t)size);
	}

	setenv("PWD", buf);
	free(buf); // getcwd() mallocs buf
}

void handle_signal(int signo)
{
	printf("\n");
}

void override_stdout(char* cmdargs[])
{
	int found_stdin  = 0;
	int found_stdout = 0;

	int i = 0;
	while(cmdargs[i] != NULL)
	{
		if (strcmp(cmdargs[i], "<") == 0)
		{
//			if(strcmp(cmdargs[i+2], ">") == 0)
//			{
//				// Redirect both input and output
//				if (freopen(cmdargs[1], "r", stdin) != 0)
//				{
//					printf("stdin Redirection Error: %s\n", strerror(errno));
//					found_stdin = 1;
//				}
//				if(freopen(cmdargs[i+1], "a+", stdout) != 0)
//				{
//					printf("stdout Redirection Error: %s\n", strerror(errno));
//				}
//				break;
//			}
			// Redirect input exclusively
			found_stdin = 1;
			if (freopen(cmdargs[1], "r", stdin) != 0)
			{
				printf("stdin Redirection Error: %s\n", strerror(errno));
				found_stdin = 0;
			}
			break;
		}
		else if (strcmp(cmdargs[i], ">") == 0)
		{
			// Redirect output exclusively
			if(freopen(cmdargs[i+1], "a+", stdout) != 0)
			{
				printf("stdout Redirection Error: %s\n", strerror(errno));
			}
			break;
		}

		i++;
	}

	if (found_stdin == 0)
	{
		freopen("/dev/tty", "a", stdin);
	}

	if (found_stdout == 0)
	{
		freopen("/dev/tty", "a", stdout);
	}
}

int main(int argc, char *argv[], char *envp[])
{
	setvbuf(stdout, NULL, _IONBF, 0); // Disable buffering. See http://homepages.tesco.net/J.deBoynePollard/FGA/capture-console-win32.html
	signal(SIGINT, SIG_IGN); 		  // Ignore ctrl-c. See http://www.cs.cf.ac.uk/Dave/C/node24.html


	char input[CHAR_BUFFER];
	char *arguments[MAX_ARGS];
	char *batch_script_arguments[MAX_ARGS];
	char shell_path[BUFSIZ];

	// Initialize shell
	set_pwd(); // Update the current working directory
	readlink("/proc/self/exe", shell_path, BUFSIZ);
	setenv("SHELL", shell_path, 1);

	// Main run loop
	while (1)
	{
		signal(SIGINT, handle_signal); // Register ctrl-c interrupt handler

		print_prompt();

		fgets(input, CHAR_BUFFER, stdin); // Get user input
		parse_input(input, arguments);    // Parse the input
		override_stdout(arguments);

		// Check if first argument is a batch file and process it if necessary
		FILE *fp = fopen(arguments[1], "r");
		if (fp != NULL)
		{
			char line[CHAR_BUFFER];
			while ( fgets ( line, CHAR_BUFFER, fp ) != NULL ) /* read a line */
			{
				parse_input(line, batch_script_arguments);
				if (batch_script_arguments[0] == NULL)
				{
					continue;
				}
				run_external_program(batch_script_arguments);
			}
			fclose(fp);
		}

		// Perform our operations
		if (arguments[0] == NULL)
		{
			// strcmp() will crash and burn if arguments[0] is NULL
			continue;
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
			if (arguments[1] == NULL)
			{
				system("/bin/dir");
			}
			else
			{
				if (chdir(arguments[1]) != 0)
				{
					printf("dir: %s: %s\n", arguments[1], strerror(errno));
				}
				else
				{
					system("/bin/dir");
					chdir(getenv("PWD"));
				}
			}
		}
		else if (strcmp(arguments[0], "cd") == 0)
		{
			if (arguments[1] == NULL)
			{
				printf("%s\n", getenv("PWD"));
			}
			else if (chdir(arguments[1]) != 0)
			{
				printf("cd: %s: %s\n", arguments[1], strerror(errno));
			}
			else
			{
				set_pwd();
			}
		}
		else if (strcmp(arguments[0], "pause") == 0)
		{
			printf("Shell operations have been paused. Press the <enter> key to resume.");
			fgets(input, CHAR_BUFFER, stdin); // Wait for user to press enter
		}
		else if (strcmp(arguments[0], "help") == 0)
		{
			char more_cmd[CHAR_BUFFER];
			strcpy(more_cmd, "more ");
			strcat(more_cmd, getenv("HOME"));
			strcat(more_cmd, "/README");
			system(more_cmd);
		}
		else
		{
			// Attempt to run existing system command
			run_external_program(arguments);
		}
	}

	return EXIT_SUCCESS;
}
