#include "parserUtilities.h"
// #include "../dataStructs/symb.h"

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
            printf("synartisi biblio8ikis %s\n",name);
            return 1;
        }
    }
    return 0;
}


