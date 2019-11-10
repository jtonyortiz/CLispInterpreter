//==================================================================
//File: basic_functionality.c
//Author: James Anthony Ortiz
//Description: This program explores the
//basic functionalities of C99.
//gcc -std=c99 -g -o basic_functionality basic_functionality.c
//==================================================================

//STL Libraries for functionality support:
#include <stdio.h> 
#include <math.h>

//------------------------------------------------
//Function: add_together()
//Description: adds two numbers
//together.
//parameters:
//x: integer
//y: integer
//------------------------------------------------
int add_together(int x, int y)
{
	int result = x + y;
	return result;
}//end add_together()


//Example of a datastruct 
//and typedef 

typedef struct{
	float x;
	float y;
	
}point;

//Initialization of struct with values:

int main()
{
	
	int a;
	
	//50 + 55 = 105
	a = add_together(50, 55);
	
	int num_of_helloworlds;
	
	printf("Enough of that, now, let's enter a number to generate n Hello Worlds:\n");
	scanf("%d", &num_of_helloworlds);
	
	
	while(num_of_helloworlds > 0)
	{
		//Print statement:
		printf("Hello, World!\n");
		
		//Decrement variable of counter:
		num_of_helloworlds--;
	}//end while
	
	
	
	
	//Exploring data-type sizes.. (output may differ on computer hardware):
	
	printf("The size of a short is: %lu\n", sizeof(short));
	
	printf("The size of a char is: %lu\n", sizeof(char));
	
	printf("The size of an integer is: %lu\n", sizeof(int));
	
	printf("The size of a float is: %lu\n", sizeof(float));
	
	printf("The size of a double is: %lu\n", sizeof(double));
	
	printf("If we add 50 and 55 together we get: %d\n", a);
	
	point p;
	p.x = 0.1;
	p.y = 10.0;

	float length = sqrt(p.x * p.x + p.y * p.y);
	
	printf("The square root of two random numbers is: %f\n", length);
	
	
	return 0;
}//end main