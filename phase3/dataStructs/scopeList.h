#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "symb.h"

typedef struct scopeListElement
{
    int scope;
    struct scopeListElement *next;
    struct Item *sameScope;

} scopeItem;

extern int scopeCounter;

void initList();

scopeItem *newScope(int scope);

scopeItem *search(int scope);

scopeItem *addNewScope( int scope);

void linkItemToScope(item *new);

void printScopeList();

item *get_last();
