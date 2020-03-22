
#include "scopeList.h"
#include "linkedList.h"

extern int yylineno;
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
    "sin"};

void init_symTable()
{
    int index;
    initList();
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
    /* printf("kanw insert sto sym to %s\n",i->name); */
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
    linkItemToScope(i);
}

item* lookupScopeAbove(char* name , int scope)
{
    int index = scope;
    item *tmp = lookupScope(name, scope);
    while(scope != 0 && tmp !=NULL){
        scope--;
        tmp = lookupScope(name , scope);
    }
    return tmp;
}


/*lookup in selected scope*/
item *lookupScope(char *name, int scope)
{
    int index = hash(strlen(name));
    item *tmp = symtable[index];
    
    scopeItem* headScope = search(scope);

    if(headScope == NULL)return NULL;

    item *indexScope = headScope->sameScope;

    while (indexScope != NULL)
    {
        if(!strcmp(name , indexScope->name)) break;
        indexScope = indexScope->sameScope;
    }
    
    return indexScope;
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
       // printf("sto lookup apli\n");
        tmp = tmp->next;
    }
    /* printf("lookupscope den brika \n"); */
    return NULL;
}



item *newItem(char *name, char *type, int scope, double lineno)
{
    item *tmp = malloc(sizeof(item));
    if(tmp == NULL)exit(1);
    tmp->name = strdup(name);
    tmp->type = strdup(type);
    tmp->scope = scope;
    tmp->lineno = lineno;
    tmp->isActive = 1;
    tmp->next = NULL;
    tmp->sameScope = NULL;
    tmp->formalArg = NULL;
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
            if(tmp->scope != 0){
                if (tmp->scope == scope && tmp->isActive == 1)
                 {
                     tmp->isActive = 0;
                     /* printf("inactive %s\n",tmp->name ); */
                 }
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
                       if(isLibraryFunction(tmp->name))cyn();
                       else red();
                    }
                    fprintf(stderr, "\"%s\" [%s] (line %d) (scope %d) \n", tmp->name, tmp->type, tmp->lineno, tmp->scope);

                }
                tmp = tmp->next;
             //   printf("sti sprint\n");
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
