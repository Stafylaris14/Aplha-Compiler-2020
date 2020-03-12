#include <symb.h>

void init_symTable()
{
    int index;
    for (index = 0; index < HASH_SIZE; index++)
    {
        symtable[index] = malloc(sizeof(item));
        symtable[index]->lineno = -1;
        symtable[index]->name = NULL;
        symtable[index]->next = NULL;
        symtable[index]->scope = NULL;
        symtable[index]->type = NULL;
    }
}

int hash(int val)
{
    return val % HASH_SIZE;
}

void insert_list(item *i, int index)
{
    item *tmp = symtable[index]->next;
    if (tmp == NULL)
    {
        tmp = i;
        tmp->next = NULL;
    }
    else
    {
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp = i;
    }
}

void insert_symTable(item *i)
{
    int index = hash((int)i->name);
    insert_list(i, index);
}


/*returns NULL if name not found*/
item *lookup(char *name)
{
    int index = hash((int)name);
    item *tmp = symtable[index];
    while (tmp != NULL)
    {
        if (!strcmp(tmp->name, name))
        {
            return tmp;
        }

        tmp = tmp->next;
    }
    return NULL;
}