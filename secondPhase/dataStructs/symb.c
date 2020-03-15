#include "symb.h"
#include "../utilities/parserUtilities.h"
#include "../dataStructs/linkedList.h"

extern int yylineno;

void init_symTable()
{
    int index;
    for (index = 0; index < HASH_SIZE; index++)
    {
        symtable[index] = NULL;
    }
    for (index = 0; index < 12; index++)
    {
        item *tmp = newItem(libFun[index], "library function", 0, 0);
        insert_symTable(tmp);
    }
}

int hash(int val)
{
    return val % HASH_SIZE;
}

void insert_list(item *i, int index)
{
    item *tmp = symtable[index];
    if (symtable[index] == NULL)
    {
        symtable[index] = i;
        symtable[index]->next = NULL;
        return;
    }
    else
    {
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = i;
    }
}

void insert_symTable(item *i)
{
    int index = hash(strlen(i->name));
    insert_list(i, index);
    
}

/*lookup in selected scope*/
item *lookupScope(char *name, int scope)
{
    int index = hash(strlen(name));
    item *tmp = symtable[index];
    while (tmp != NULL)
    {
        if (!strcmp(tmp->name, name))
        {
            if (tmp->scope == scope){
                grn();
                 printf("lookupscope brika id %s sto scope %d \n",name,scope);
                 wht();
                return tmp;
            }
        }

        tmp = tmp->next;
    }
    printf("lookupscope den brika \n");
    return NULL;
}


int isFunction(char* name)
{
    item* tmp = lookup(name);
    
    if(tmp == NULL)return -1;
    
    if(tmp->isActive == 1){
        red();
        fprintf(stderr , "function detected in : %d \n" , yylineno);
        wht();
        return 0;
    }
    
    if (strcmp(tmp->type, "User Function") == 0)return 1;

    return -1;
}






/*returns NULL if name not found with in any scope*/
item *lookup(char *name)
{
    int index = hash(strlen(name));
    item *tmp = symtable[index];
    while (tmp != NULL)
    {
        if (strcmp(tmp->name, name) == 0)
        {
            return tmp;
        }

        tmp = tmp->next;
    }
    printf("lookupscope den brika \n");
    return NULL;
}



item *newItem(char *name, char *type, int scope, double lineno)
{
    item *tmp = malloc(sizeof(item));
    tmp->name = strdup(name);
    tmp->type = strdup(type);
    tmp->scope = scope;
    tmp->lineno = lineno;
    tmp->isActive = 1;
    tmp->next = NULL;
    return tmp;
}

void hide(int scope)
{
    int i;
    for (i = 0; i < HASH_SIZE; i++)
    {
        item *tmp = symtable[i];
        while (tmp != NULL)
        {
            if (tmp->scope == scope && tmp->isActive == 1)
            {
                printf("inactive %s\n",tmp->name );
                tmp->isActive = 0;
            }
            tmp = tmp->next;
        }
    }
}

void printSymTable()
{
    int index, scopeIndex;
    for (scopeIndex = 0; scopeIndex <= maxScope; scopeIndex++)
    {
        cyn();
        fprintf(stderr, "-------Scope #%d------\n", scopeIndex);
        for (index = 0; index < HASH_SIZE; index++)
        {
            item *tmp = symtable[index];
            while (tmp != NULL)
            {
                if (tmp->scope == scopeIndex)
                {
                    if(tmp->isActive == 0){
                        red();
                    }else {
                        cyn();
                    }
                    fprintf(stderr, "\"%s\" [%s] (line %d) (scope %d) \n", tmp->name, tmp->type, tmp->lineno, tmp->scope);
                    
                }
                tmp = tmp->next;
                wht();
            }
        }
    }
}

void printHash()
{
    int index ;
    for(index = 0; index < HASH_SIZE; index++){
            item* tmp = symtable[index];
            grn();
            if(tmp != NULL)
                fprintf(stderr , "\n");
            while(tmp != NULL){
                fprintf(stderr , "   |  %s  " , tmp->name);
                mag();
                fprintf(stderr , "%s|" , tmp->type);
                tmp = tmp->next;
                grn();
            }
            wht();
    }
}
   



