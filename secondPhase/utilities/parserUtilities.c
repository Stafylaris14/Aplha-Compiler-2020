#include "parserUtilities.h"
#include "../dataStructs/linkedList.h"

char *libFun[12] = {
    "print",
    "input",
    "objectmemberkeys",
    "objecttotalmembers",
    "objectcopy",
    "totalarguments",
    "argument",
    "typeof",
    "strtonum",
    "sqrt",
    "cos",
    "sin"
};

int isLibraryFunction(char *name)
{
    int i = 0;
    for (i = 0; i < 12; i++)
    {
        if (strcmp(name, libFun[i]) == 0){
            return 1;
        }
    }
    return 0;
}

void errorLibFunction(int lineno, char *name)
{
    red();
    fprintf(stderr, "Library function detected in line %d   %s\n", lineno, name);
    wht();
}
