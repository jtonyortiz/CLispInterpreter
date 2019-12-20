//=================================================================
//File: error_handling.c
//Author: James Anthony Ortiz
//Description: Provides error-handling for 
//evaluator, avoiding crashes in program.One
//compile: gcc -std=c99 -Wall mpc.c error_handling.c -o errhandle
//==================================================================

#include "mpc.h"
#ifdef _WIN32

static char buffer[2048];

char* readline(char* prompt)
{
	fputs(prompt, stdout);
	fgets(buffer, 2048, stdin);
	char* cpy = malloc(strlen(buffer)+1);
	strcpy(cpy, buffer);
	cpy[strlen(cpy)-1] = '\0';
	return cpy;
}

void add_history(char* unused){}

#else 
#include <editline/readline.h>
#include <editline/history.h>
#endif

/* Create Enumeration of Possible Error Types */
enum{ LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM};

/* Create Enumeration of Possible lval Types:
	If type is 0 then the structure is a Number.
	If type is 1 then the structure is an Error. 
*/
enum { LVAL_NUM, LVAL_ERR };


/* Declare new lval struct */
typedef struct{
	int type;
	long num;
	int err;
}lval;

/* Create a new member type lval */
lval lval_num(long x)
{
	lval v;
	v.type = LVAL_NUM;
	v.num = x;
	return v;
}

/* Create a new error type lval */

lval lval_err(int x)
{
	lval v;
	v.type = LVAL_ERR;
	v.err = x;
	return v;
}

/* Print an "lval" */

void lval_print(lval v)
{
	

	switch (v.type)
	{
		//In the case the type is a number, print the value:
		//Then, break out of the switch statement.
		case LVAL_NUM: printf("%li", v.num); break;
		
		//In case the value is an error:
		case LVAL_ERR:
		//Check the type of error present:
		if(v.err == LERR_DIV_ZERO)
		{
			printf("Error: Division By Zero!");
		}
		if(v.err == LERR_BAD_OP)
		{
			printf("Error: Invalid Operator!");
		}
		if(v.err == LERR_BAD_NUM)
		{
			printf("Error: Invalid Number!");
		}
		break;
	}//end switch
}//end lval_print()

/* Print an "lval" followed by a newline */
void lval_println(lval v) {
	lval_print(v);
	putchar('\n');
}

lval eval_op(lval x, char* op, lval y)
{
	if(x.type == LVAL_ERR)
	{
		return x;
	}
	if(y.type == LVAL_ERR)
	{
		return y;
	}
	
	//Otherwise do mathematical calculations on number values:
	if(strcmp(op, "+") == 0) { return lval_num(x.num + y.num); }
	if(strcmp(op, "-") == 0) { return lval_num(x.num - y.num); }
	if(strcmp(op, "*") == 0) { return lval_num(x.num * y.num); }
	if(strcmp(op, "%") == 0) { return lval_num(x.num % y.num); }
	if(strcmp(op, "/") == 0)
	{
		return y.num == 0 ? lval_err(LERR_DIV_ZERO) : lval_num(x.num/y.num);
		
	}
	
	return lval_err(LERR_BAD_OP);
	
}//end eval_op()

lval eval(mpc_ast_t* t)
{
	  
  if (strstr(t->tag, "number"))
  {
    /* Check if there is some error in conversion */
    errno = 0;
    long x = strtol(t->contents, NULL, 10);
    return errno != ERANGE ? lval_num(x) : lval_err(LERR_BAD_NUM);
  }
  
  char* op = t->children[1]->contents;  
  lval x = eval(t->children[2]);
  
  int i = 3;
  while (strstr(t->children[i]->tag, "expr")) {
    x = eval_op(x, op, eval(t->children[i]));
    i++;
  }
  
  return x;  
	
}//end eval()


int main(int argc, char** argv)
{
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Lispy = mpc_new("lispy");
  
  
  mpca_lang(MPCA_LANG_DEFAULT,
    "                                                     \
      number   : /-?[0-9]+/ ;                             \
      operator : '+' | '-' | '*' | '/' ;                  \
      expr     : <number> | '(' <operator> <expr>+ ')' ;  \
      lispy    : /^/ <operator> <expr>+ /$/ ;             \
    ",
    Number, Operator, Expr, Lispy);
	
  puts("CLISP Version 0.0.0.0.4");
  puts("Press Ctrl+c to Exit\n");
  
  while (1) {
  
    char* input = readline("CLISP> ");
    add_history(input);
    
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      lval result = eval(r.output);
      lval_println(result);
      mpc_ast_delete(r.output);
    } else {    
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }
    
    free(input);
    
  }
  
  mpc_cleanup(4, Number, Operator, Expr, Lispy);
  
  return 0;
	
}//END MAIN


/* Trial:
CLISP> / 10 0
Error: Division By Zero!
CLISP> / 10 2
5
CLISP> + 500 50
550
CLISP> + 7700 90
7790
CLISP> + 7999 500
8499
CLISP> * 45 60
2700
*/





