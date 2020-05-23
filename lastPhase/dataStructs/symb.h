#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 509

char *libFun[12];
int maxScope;
typedef struct formalArgs formal;

typedef enum Scope_spase
{
    program_variable,
    function_local,
    formal_argument
} sc_spase;

typedef struct Item
{
    int isActive;
    char *name;
    char *type;
    enum Scope_spase scope_spase;                       /* scope Space 3 phase */
    int offset;
    int scope;
    int jump;
    struct Item *sameScope; /* dixnei sto epomeno me to idio scope */
    int lineno;
    formal *formalArg;
    int formal_count;
    int iaddress;
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

item *lookupScopeAbove(char *name, int scope);

sc_spase get_scope_spase(item *new);

void getoffset();


