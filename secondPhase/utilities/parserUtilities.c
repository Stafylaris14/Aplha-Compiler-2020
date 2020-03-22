#include "parserUtilities.h"

#include "../dataStructs/linkedList.h"
extern int scopeCounter;
extern int functionFlag;
extern int yylineno;
extern int returnFlag;
extern char* functionName;
int isLibraryFunction(char *name)
{
    int i = 0;
    for (i = 0; i < 12; i++)
    {
        if (strcmp(name, libFun[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void printdb(char *s)
{
    grn();
    fprintf(stderr, "-- %s --\n", s);
    wht();
}

void error(char *str, int lineno)
{
    red();
    fprintf(stderr, "error ");
    mag();
    fprintf(stderr, "in line : %d ", lineno);
    wht();
    fprintf(stderr, "%s \n", str);
    exit(1);
}

int isFunction(char *name)
{
    item *tmp = lookup(name);

    if (tmp == NULL)
        return 0;

    //edw koitaw gia idio id
    if (tmp->isActive == 1 && strcmp(tmp->type, "User Function") == 0)
    {
        red();
        if(returnFlag == 0)
            error("User Function " , yylineno);
        wht();
        return 1;
    }

    return 0;
}

/* sprintf(str, "Value of Pi = %f", M_PI); */
void check(item *new)
{
        grn();
        printf("eimai edw gia na checkarw ------------%s\n" , new->name);
        //tsekaroume gia library
        if (isLibraryFunction(new->name))
        {
            char *str = malloc(35 + sizeof(new->name));
            sprintf(str, "Library Funtion : %s", new->name);
            error(str, yylineno);
            return;
        }

        if (!strcmp(new->type, "local variable"))
        {
            item *tmp = lookupScope(new->name, scopeCounter);
            if (tmp == NULL)
            {
                printf("komple gia local \n");
                red();
                insert_symTable(new);
                wht();
                return;
            }
            else
            {
                error("you cant access local veriable", yylineno);
            }
        }

        //tseck gia function
        if (isFunction(new->name))
        {
            char *str = malloc(35 + sizeof(new->name));
            sprintf(str, "User Function exist : %s", new->name);
            error(str, yylineno);
            return;
        }

        //tsekaroume an einai function scope
        if (isFA(new->name))
            return;
    
    item *tmp = lookup(new->name);
    if (tmp != NULL)
    {
        if (tmp->isActive == 1)
        {
            char *str = malloc(35 + sizeof(new->name));
            sprintf(str, "Already Exists: %s", new->name);
            error(str, yylineno);
            return;
        }
    }

    insert_symTable(new);
}

/* is Formal Argument
    
*/
int isFA(char *name)
{
    item *tmp = NULL;
    int i;
    int flag = 0;
    for (i = 0; i < HASH_SIZE; i++)
    {
        tmp = symtable[i];
        while (tmp != NULL)
        {

            if (!strcmp(tmp->name, name))
            {
                printf("type %s kai scope %d kai scopecounter %d\n", tmp->type, tmp->scope, scopeCounter);
            }
            /* if (!strcmp(tmp->type, "local variable") && !strcmp(tmp->name, name))
            {
                printf("komple gia local\n");
                return 0;
            } */

            if(!strcmp(tmp->type, "local variable") && !strcmp(tmp->name, name) && tmp->scope == scopeCounter && tmp->isActive){
                flag =1;
            }


            if (tmp->isActive && strcmp(tmp->name, name) == 0 && (strcmp(tmp->type, "formal argument") == 0 ||strcmp(tmp->type, "local variable") == 0)  && tmp->scope < functionFlag)
            {
                if(flag == 0) flag = 2;
            }

            tmp = tmp->next;
        }
    }
    if(flag == 0) return 0; //den brike tpt
    else if(flag ==1)return 0;//brike local se idio scope
    else{error("RIPAPAS", yylineno); return 1;} //einai formal varaible
}


void DEBUG(char* s )
{
    red();
    printf("%s:%d  -> %s\n" , __FILE__ , __LINE__ , s);
    wht();
}

void insert_formal_arg(char* functionName , char* name)
{
    item* tmp = lookup(functionName);
    if(!tmp)return ;
    formal* formals = tmp->formalArg;

    if(formals == NULL)
    {
        DEBUG("EINAI ADEIA");
        formals = malloc(sizeof(formal));
        formals->arg = lookupScope(name , tmp->scope+1);
        formals->next = NULL;
        tmp->formalArg = formals;
    }
    else
    {
        DEBUG("DEN EINAI ADEIA");
        formal* tmp_f = formals;
        while(tmp_f->next!=NULL)
        {
            tmp_f = tmp_f->next;
        }
        
        tmp_f->next = malloc(sizeof(formal));
        tmp_f->next->arg = lookupScope(name, tmp->scope + 1);
        tmp_f->next->next = NULL;
        tmp->formalArg = formals;
    }
    /* print_formal_arguments(); */

}
/* just for debug */
void print_formal_arguments()
{
    item* funciton = lookup(functionName);
    formal* args = funciton->formalArg;
    cyn();
    printf("---%s---\n" , functionName);
    grn();
    if(args == NULL) DEBUG("EINAI NULL");
    else
    {
        while (args != NULL)
        {
            printf("(%s)\n" , args->arg->name);
            args = args->next;
            
        }
    }
}