#include "scopeList.h"

#include "linkedList.h"

scopeItem *scopeHead;
int maxScope;


void initList()
{
    maxScope = 0;
    scopeHead = newScope(0);
}

scopeItem *newScope(int scope)
{
    scopeItem *tmp = malloc(sizeof(scopeItem));
    if(tmp == NULL)
    {
        red();
        printf("isNULL\n");
        exit(1);
    }
    tmp->scope = scope;
    tmp->sameScope = NULL;
    tmp->next = NULL;
    return tmp;
}

scopeItem *search(int scope)
{
    scopeItem *tmp = scopeHead;
    while (tmp != NULL)
    {
        if (tmp->scope == scope)
            break;
        tmp = tmp->next;
    }
    return tmp;
}

scopeItem *addNewScope(int scope)
{
    
    scopeItem* main = scopeHead;
    scopeItem *tmp = newScope(scope);
    while(main->next!= NULL)
    {
        main = main->next;
    }
    main->next = tmp;
    return tmp;
}

void linkItemToScope(item *new)
{
   
    int scope = new->scope;
    grn();
    printf("------------eimai gia na valw to  %s --------\n",new->name);

    scopeItem *scopeHead = search(scope);

    if (scopeHead == NULL)
    {
        red();
        printf("cant find scope %d to insert item %s ... with maxscope = %d\n", scope, new->name, maxScope);

        /* Creating one */
        scopeHead = addNewScope(new->scope);

        if (scopeHead->sameScope == NULL)
        {
            red();
            printf("list is empty\n");
            scopeHead->sameScope = new;
            new->sameScope = NULL;
        }
        else
        {
            printf("list is not empty %d \n", scope);
          
            item *tmp = scopeHead->sameScope;
            
            while (tmp->sameScope != NULL)
            {
                tmp = tmp->sameScope;
            }
     
            tmp->sameScope = new;
            wht();
             
        }
    }
    else
    {

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
            item *tmp = scopeHead->sameScope;
            printf("list is not empty %d \n", scope);
            while (tmp->sameScope != NULL)
            {
                tmp = tmp->sameScope;
            }
            tmp->sameScope = new;
            wht();
            
        }
    }
    printScopeList();
}

void printScopeList()
{
    scopeItem *tmp = scopeHead;

    while (tmp != NULL)
    {
        item *tmpItem = tmp->sameScope;
        cyn();
        printf("| %d | --->>", tmp->scope);
        while (tmpItem != NULL)
        {
            mag();
            printf(" ( %s ) ", tmpItem->name);
            tmpItem = tmpItem->sameScope;
        }
        printf("\n");
        tmp = tmp->next;
    }
}