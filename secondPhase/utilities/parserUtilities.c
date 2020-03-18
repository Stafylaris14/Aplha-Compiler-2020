#include "parserUtilities.h"

#include "../dataStructs/linkedList.h"
extern int scopeCounter;
extern int functionFlag;
extern int yylineno;
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
    grn();
    printf("%d\n" , functionFlag);
    wht();
    //tsekaroume gia library
    if (isLibraryFunction(new->name))
    {
        char *str = malloc(35+sizeof(new->name));
        sprintf(str , "Library Funtion : %s" , new->name);
        error(str, yylineno);
        return;
    }
    
    //tseck gia function
    if (isFunction(new->name))
    {
        char *str = malloc(35+sizeof(new->name));
        sprintf(str, "User Function exist : %s", new->name);
        error(str, yylineno);
        return;
    }

    item *tmp = lookup(new->name);
    
    if (isFA(new->name)) return;
    
    if (tmp != NULL)
    {
        if (tmp->isActive == 1)
        {
            char *str = malloc(35+sizeof(new->name));
            sprintf(str, "Already Exists: %s", new->name);
            error(str, yylineno);
            return;
        }
    }

    

    insert_symTable(new);
}

/* is Formal Argument
    
*/
int isFA(char* name)
{
    item* tmp = NULL;
    int i;
    for(i = 0; i < HASH_SIZE; i++)
    {
        tmp =  symtable[i];
        while(tmp != NULL)
        {   

            if(!strcmp(tmp->name , name)){
                printf("type %s kai scope %d kai scopecounter %d\n",tmp->type,tmp->scope,scopeCounter);

            }
            if(!strcmp(tmp->type , "local variable")  && !strcmp(tmp->name , name)){
                printf("komple gia local\n");
                return 0;
            }
            if(tmp->isActive && strcmp(tmp->name , name)==0 && strcmp(tmp->type , "formal argument") == 0 && tmp->scope < functionFlag ){
                error("RIPAPAS" , yylineno);
                return 1;
            }


            tmp  = tmp->next;
        }
    }
    return 0;
}