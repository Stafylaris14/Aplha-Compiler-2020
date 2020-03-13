#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define KWHT "\x1B[37m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"

char *libFun[12];

int isLibraryFunction(char *name);

void errorLibFunction(int lineno, char *name);