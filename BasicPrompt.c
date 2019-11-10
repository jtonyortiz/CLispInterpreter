//=================================================================
//File: 	BasicPrompt.c
//Author: 	James Anthony Ortiz
//Description: An Interactive prompt, includes a basic 
//loop to repeatedly write a message, and then waits 
//for input from the user.
//Compile: 	gcc -std=c99 -Wall -o BasicPrompt -g BasicPrompt.c
//==================================================================

//Include STL Library for C99:
#include <stdio.h>

/*
Declare a buffer for user of size 2048:
*/
static char input[2048];

int main(int argc, char** argv)
{
	
	//Print Version and Exiting information:
	puts("C-LISP Version 0.0.0.0.1");
	puts("Press Ctrl+c to Exit\n");
	
	//Infinite Loop:
	while(1)
	{
		//Output prompt:
		fputs("C-LISP> ", stdout);
		
		//Read a line of user input up to the size 2048:
		fgets(input, 2048, stdin);
		
		//Echo the input back to the user:
		printf("No you're a %s", input);
		
		
	}//end while
	
	return 0;
}