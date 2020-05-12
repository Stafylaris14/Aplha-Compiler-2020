#include "scopeList.h"

#include "linkedList.h"

scopeItem *scopeHead;
extern int formal_flag;
int maxScope;

void initList()
{
    maxScope = 0;
    scopeHead = newScope(0);
}

scopeItem *newScope(int scope)
{
    scopeItem *tmp = malloc(sizeof(scopeItem));
    if (tmp == NULL)
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

    scopeItem *main = scopeHead;
    scopeItem *tmp = newScope(scope);
    while (main->next != NULL)
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
            if (formal_flag == 0)
            {
                while (tmp->sameScope != NULL)
                {
                    tmp = tmp->sameScope;
                }
                tmp->sameScope = new;
            }
            else
            {
                while (tmp->sameScope != NULL)
                {
                    if (!strcmp(tmp->sameScope->type, "formal argument") && tmp->sameScope->isActive == 1)
                    {
                        break;
                    }
                    tmp = tmp->sameScope;
                }
                if (tmp->sameScope == NULL)
                {
                    tmp->sameScope = new;
                }
                else
                {
                    if (!strcmp(scopeHead->sameScope->name, tmp->name) && !strcmp(tmp->type, "formal argument"))
                    {
                        new->sameScope = tmp;
                        scopeHead->sameScope = new;
                    }
                    else
                    {
                        new->sameScope = tmp->sameScope;
                        tmp->sameScope = new;
                    }
                }
            }
            wht();
        }
    }
}

void printScopeList()
{
    scopeItem *tmpScope = scopeHead;
    int scopeIndex;
    while (tmpScope != NULL)
    {
        item *tmpItem = tmpScope->sameScope;
        scopeIndex = tmpScope->scope;
        cyn();
        fprintf(stderr, "-------Scope #%d------\n", scopeIndex);
        while (tmpItem != NULL)
        {
            fprintf(stderr, "\"%s\" [%s] (line %d) (scope %d) -->(%d) ---> (%u)\n", tmpItem->name, tmpItem->type, tmpItem->lineno, tmpItem->scope, tmpItem->offset, tmpItem->scope_spase);
            /* mag();
            printf("(%s) ", tmpItem->name); */
            tmpItem = tmpItem->sameScope;
        }
        printf("\n");
        tmpScope = tmpScope->next;
    }
    wht();
}

item *get_last()
{
    scopeItem *tmp_s = search(scopeCounter);
    item *tmp_i = tmp_s->sameScope;
    while (tmp_i->sameScope != NULL)
        tmp_i = tmp_i->sameScope;
    return tmp_i;
}