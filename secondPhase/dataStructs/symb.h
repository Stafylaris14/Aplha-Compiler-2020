#include <string.h>
#define HASH_SIZE 1409



typedef struct Item
{
    char* name;
    char* type;
    int scope;
    double lineno;
    struct Item* next;
} item;



item* symtable[HASH_SIZE];


void init_symTable();

int hash(int val);

void insert_list(item *i, int index);

void insert_symTable(item *i);

item *lookup(char *name);