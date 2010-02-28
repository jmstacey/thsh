/**
 * @file
 * Main program header file for thsh [this shell].
 */

/**
 * Include needed system libraries.
 *
 * @include stdio.h
 *   Standard input output library.
 * @include stdlib.h
 *   Standard library.
 * @include signal.h
 *   Signal library.
 * @include string.h
 *   C String library.
 * @include unistd.h
 *   Standard symbolic constants and types.
 * @include sys/types.h
 *   Data types.
 * @include sys/wait.h
 *   Declarations for waiting.
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * Declare constants and globals.
 */
// TODO: Determine appropriate buffer sizes
int CHAR_BUFFER = 100; // Character input buffer size
int MAX_ARGS 	= 100; // Maximum number of arguments

extern char **environ; 		  // Retrieve external environment.
const  char *SEPARATOR = " "; // Separator used to explode user input.

/**
 * Parses user input (exploding on " ") and creates an array of arguments.
 *
 * The user input will be exploded on space characters [" "] and added
 * to a predefined array of arguments. The array element after the last
 * argument will be set to NULL.
 *
 * Note: The arguments[] array may contain trash from previous runs. The first
 * NULL encountered represents the end of the current command.
 *
 * @param char *input
 * 	 A pointer to the input character array.
 * @param char *arguments[]
 * 	 A pointer to the array of character arrays in which the arguments will be
 *   stored.
 */
void parse_input(char *input, char *arguments[]);

/**
 * Prints the environment variables.
 *
 * The environment is obtained via "extern char **environ" and written
 * to the active output location.
 */
void print_environment_variables();

/**
 * Prints given message to the active output location.
 *
 * This echo command is very similar to the traditional *nix echo command.
 * The given message will simply be printed to the active output location.
 *
 * @param char *message[]
 * 	 A pointer to the message character array.
 */
void echo(char *message[]);

/**
 * Prints the command prompt asking for user input.
 *
 * The standard command prompt looks similar to the following:
 * smith@smith-local:/current/working/directory$
 */
void print_prompt();

/**
 * Runs an external program and passes any arguments along.
 *
 * This function will fork and then execvp() the contents of cmd[0].
 * Any additional items in the array (e.g. cmd[1], cmd[2]...) will be passed as
 * arguments/options to the executed program in cmd[0].
 *
 * If the last character in the cmd[] character array (before the first NULL)
 * is an ampersand (&), then this function will not wait for the forked (child)
 * process to finish and instead immediately return.
 *
 * Note: If an ampersand is present before the first NULL in cmd[], then it
 * will be removed and replaced with a NULL so that execvp() does not get
 * tripped.
 *
 * @param char *cmd[]
 * 	 A pointer to the input character array.
 */
void run_external_program(char *cmd[]);


/**
 * Main program entry point for thsh [this shell].
 *
 * @param int argc
 * 	 Number of arguments.
 * @param char *argv[]
 *   The arguments character array.
 *   Pointer to the array of character arrays containing the arguments
 * @param char *envp[]
 *   The environment character arrays.
 */
int main(int argc, char *argv[], char *envp[]);
