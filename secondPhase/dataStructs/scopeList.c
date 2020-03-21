#include "../dataStructs/linkedList.h"
#include "scopeList.h"

scopeItem *head;
int maxScope;
void initList()
{
    maxScope = 0;
    head = newItem(0);
}

scopeItem *newItem(int scope)
{
    scopeItem* tmp = malloc(sizeof(scopeItem));
    tmp ->scope = 0;
    tmp->sameScope = NULL;
    tmp->next = NULL;
    return tmp;
}

scopeItem *search(int scope)
{
    scopeItem *tmp = head;

    while (tmp != NULL)
    {
        if (tmp->scope == scope)
            break;
        tmp = tmp->next;
    }
    return tmp;
}

/* void addNewItem(item* new)
{
    int scope = new->scope;

    scopeItem* tmpScope = search(scope);

    item* tmpItem = tmpScope->sameScope;

    while(tmpItem!=NULL)
    {
        
        tmpItem = tmpItem->sameScope;
    }
} */
