#include "scopeList.h"

#include "linkedList.h"


scopeItem *head;
int maxScope;
void initList()
{
    maxScope = 0;
    head = newScope(0);
}

scopeItem *newScope(int scope)
{
    scopeItem *tmp = malloc(sizeof(scopeItem));
    tmp->scope = scope;
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

scopeItem *addNewScope()
{
    maxScope++;
    scopeItem *tmp = newScope(maxScope);
    return tmp;
}

void linkItemToScope(item *new)
{
    int scope = new->scope;
    mag();
    printf("trying to link with maxScope ==  %d\n" , maxScope);
    scopeItem *scopeHead = search(scope);

    if (scopeHead == NULL)
    {
        red();
        printf("cant find scope %d to insert item %s ... with maxscope = %d\n", scope, new->name , maxScope);

        /* Creating one */
        scopeHead = addNewScope();

        if (scopeHead->sameScope == NULL)
        {
            grn();
            printf("list is empty\n");
            scopeHead->sameScope = new;
            new->sameScope = NULL;
        }
        else
        {
            printf("list is not empty %d \n" , scope);
            item *tmp = scopeHead->sameScope;
            while (tmp != NULL)
            {
                tmp = tmp->sameScope;
            }
            tmp = new;
            wht();
        }
    }
    else
    {
        /* EDW TON PAIZEI */
        if (scopeHead->sameScope == NULL)
        {
            grn();
            printf("list is empty denneinai NULL\n");
            scopeHead->sameScope = new;
            new->sameScope = NULL;
        }
        else
        {
            grn();
            printf("list is not empty %d \n", scope);
            item *tmp = scopeHead->sameScope;
            while (tmp != NULL)
            {
                tmp = tmp->sameScope;
            }
            tmp = new;
            wht();
        }
    }
    printScopeList();
}

void printScopeList()
{
    scopeItem *tmp = head;
    
    while (tmp != NULL)
    {
        item *tmpItem = tmp->sameScope;
        cyn();
        printf("| %d | --->>" ,tmp->scope );
        while (tmpItem != NULL)
        {
            mag();
            printf(" ( %s ) " , tmpItem->name);
            tmpItem = tmpItem->sameScope;
        }
        printf("\n");
        tmp = tmp->next;
    }
}