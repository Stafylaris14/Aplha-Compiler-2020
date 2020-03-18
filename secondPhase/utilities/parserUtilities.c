#include "parserUtilities.h"

#include "../dataStructs/linkedList.h"


int isLibraryFunction(char *name)
{
    int i = 0;
    for (i = 0; i < 12; i++)
    {
        if (strcmp(name, libFun[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}



void printdb(char *s)
{
    grn();
    fprintf(stderr, "-- %s --\n", s);
    wht();
}

void error(char *str, int lineno)
{
    red();
    fprintf(stderr, "error ");
    mag();
    fprintf(stderr, "in line : %d ", lineno);
    wht();
    fprintf(stderr, "%s \n", str);
}

int isFunction(char *name)
{
    item *tmp = lookup(name);

    if (tmp == NULL)
        return 0;

    //edw koitaw gia idio id
    if (tmp->isActive == 1 && strcmp(tmp->type, "User Function") == 0)
    {
        red();
        fprintf(stderr, "function detected in : %d \n", yylineno);
        wht();
        return 1;
    }

    return 0;
}

/* sprintf(str, "Value of Pi = %f", M_PI); */
void check(item *new)
{
    if (isLibraryFunction(new->name))
    {
        char* str;
        sprintf(str , "Library Funtion : %s" , new->name);
        error(str, yylineno);
        return;
    }
    if (isFunction(new->name))
    {
        char *str;
        sprintf(str, "User Function exist : %s", new->name);
        error(str, yylineno);
        return;
    }

    item *tmp = lookup(new->name);
    if (tmp != NULL)
    {
        if (tmp->isActive == 1)
        {
            char *str;
            sprintf(str, "Already Exists: %s", new->name);
            error(str, yylineno);
            return;
        }
    }
    insert_symTable(new);
}