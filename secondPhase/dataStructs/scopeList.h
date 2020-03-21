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