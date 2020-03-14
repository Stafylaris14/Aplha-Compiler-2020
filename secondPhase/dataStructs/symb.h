#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define HASH_SIZE 509

int maxScope;

typedef struct Item
{
    int isActive;
    char *name;
    char *type;
    int scope;
    int lineno;
    struct Item *next;
} item;

item *symtable[HASH_SIZE];

void init_symTable();

int hash(int val);

void insert_list(item *i, int index);

void insert_symTable(item *i);

item *lookupScope(char *name, int scope);

item *lookup(char *name);

item *newItem(char *name, char *type, int scope, double lineno);

void printSymTable();

void printHash();

void hide(int scope);

/*
returns -1 if item with name is not found
returns 0 if is not a function
returns 1 if is function
*/
int isFunction(char *name);