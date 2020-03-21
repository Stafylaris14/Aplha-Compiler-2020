#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 509

char *libFun[12];
int maxScope;
typedef struct formalArgs formal;

typedef struct Item
{
    int isActive;
    char *name;
    char *type;
    int scope;
    struct Item *sameScope; /* dixnei sto epomeno me to idio scope */
    int lineno;
    formal *formalArg;
    struct Item *next;
} item;


struct formalArgs
{
    item *arg;
    struct formalArgs *next;
};

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
