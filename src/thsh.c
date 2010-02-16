/*
 ============================================================================
 Name        : thsh.c
 Authors     : Collin Kruger, Denton Underwood, John Christensen, Jon Stacey
 Version     :
 Copyright   : Copyright 2009 Jon Stacey. All rights reserved.
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0); // Disable buffering in accordance to http://homepages.tesco.net/J.deBoynePollard/FGA/capture-console-win32.html

	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
