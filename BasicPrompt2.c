//===============================================================
//Author: James Anthony Ortiz
//File:	BasicPrompt2.c
//Description: A basic prompt that works on windows, and 
//Linux.
//Compile: gcc -std=c99 -Wall -o BasicPrompt2 -g BasicPrompt2.c
//================================================================

#include <stdio.h>
#include <stdlib.h>

//If we compile from Windows OS, compile these functions */
#ifdef _WIN32
#include <string.h>

/*
Declare a buffer that is large enough:
*/

static char buffer[2048];

//Fake readline function:
char* readline(char* prompt)
{
	fputs(prompt, stdout);
	fgets(buffer, 2048, stdin);
	char* cpy = malloc(strlen(buffer)+1);
	strcpy(cpy, buffer);
	cpy[strlen(cpy)-1] = '\0';
	return cpy;
	
}//end readline()

void add_history(char* unused){}


//Otherwise, include editline headers

#else 
#include <editline/readline.h>
#include <editline/history.h>
#endif

int main(int argc, char** argv)
{
	puts("CLISP Version 0.0.0.0.1");
	puts("Press Ctrl+c to Exit\n");
	
	while(1)
	{
		char* input = readline("CLISP> ");
		add_history(input);
		
		printf("No, you're a %s\n", input);
		free(input);
	}

	return 0;
}//end main


/*
Test-trial:
CLISP> Hello World!
No, you're a Hello World!
CLISP> balloon
No, you're a balloon
CLISP> house
No, you're a house
CLISP> cat
No, you're a cat
CLISP> lunatic
No, you're a lunatic
CLISP> No, you're a lunatic
CLISP> ^C

*/