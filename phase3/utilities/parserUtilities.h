#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* #include "../dataStructs/symb.h" */
#include "../dataStructs/scopeList.h"

extern int yylineno;

/* extern char*libFun[]; */

int isLibraryFunction(char *name);





void printdb(char *s);

void error(char *str, int lineno);

/*
returns -1 if item with name is not found
returns 0 if is not a function
returns 1 if is function
*/
int isFunction(char *name);

int isFA(char *name);

void check(item *new);

void DEBUG(char *s);

void insert_formal_arg(char *functionName, char *name);

void print_formal_arguments();

void new_check(item *new);