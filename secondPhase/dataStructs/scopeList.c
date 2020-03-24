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
    

    scopeItem *scopeHead = search(scope);

    if (scopeHead == NULL)
    {
        red();
        

        /* Creating one */
        scopeHead = addNewScope(new->scope);

        if (scopeHead->sameScope == NULL)
        {
            red();
        
            scopeHead->sameScope = new;
            new->sameScope = NULL;
        }
        else
        {
        
          
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
        
            scopeHead->sameScope = new;
            new->sameScope = NULL;
        }
        else
        {
            grn();
            item *tmp = scopeHead->sameScope;
        
            while (tmp->sameScope != NULL)
            {
                tmp = tmp->sameScope;
            }
            tmp->sameScope = new;
            wht();
            
        }
    }
    
}

void printScopeList()
{
    scopeItem *tmp = scopeHead;

    while (tmp != NULL)
    {
        item *tmpItem = tmp->sameScope;
        cyn();
        printf("|%d|---> ", tmp->scope);
        while (tmpItem != NULL)
        {
            mag();
            printf("(%s) ", tmpItem->name);
            tmpItem = tmpItem->sameScope;
        }
        printf("\n");
        tmp = tmp->next;
    }
    wht();
}