#include <stdlib.h>
#include <stdio.h>
#include <string.h>



char *libFun[12];

int isLibraryFunction(char *name);

void errorLibFunction(int lineno, char *name);

void printdb(char *s);

void error(char *str, int lineno);