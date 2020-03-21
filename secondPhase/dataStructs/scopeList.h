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


void initList();

scopeItem *newScope(int scope);

scopeItem *search(int scope);

scopeItem *addNewScope();

void linkItemToScope(item *new);

void printScopeList();