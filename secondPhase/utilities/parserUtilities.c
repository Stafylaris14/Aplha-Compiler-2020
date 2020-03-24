#include "parserUtilities.h"

#include "../dataStructs/linkedList.h"
extern int scopeCounter;
extern int functionFlag;
extern int yylineno;
extern int returnFlag;
extern char* functionName;
extern int callFlag;



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


void new_check(item *new){
  int i=0;
  item *tmp = NULL;

  for (i = 0; i < HASH_SIZE; i++) {
      tmp = symtable[i];
      while (tmp != NULL){
        if (!strcmp(tmp->name, new->name) && tmp->isActive){      //an einai idio onoma meta 3ekinaw elenxoys
        //  printf("idio onoma %s ka newitype %s kai tmptypw %s kai scope %d k scope idio %d\n",tmp->name,new->type,tmp->type,new->scope,tmp->scope);
          //tsekarw an einai local to type pou 8elw na balw
          if(!strcmp(new->type, "local variable")){
            //den borei na einai library
            if (isLibraryFunction(new->name)){
              char *str = malloc(35 + sizeof(new->name));
              red();
              printf( "Library Funtion : %s\n", new->name);
              wht();
              //error(str, yylineno);
              return;
              //den borei na exei idio onoma me function
                } else if(!strcmp(tmp->type, "User Function") && tmp->scope == new->scope){
                     char *str = malloc(35 + sizeof(new->name));
                     red();
                     printf( "Redeclaration Function : %s\n", new->name);
                     wht();
                     if(returnFlag ==1)return;
                     sprintf(str, "Function name exist : %s", new->name);
                     error(str, yylineno);
                    return;
                   //den kanei insert gt iparxei idi
              }else if(functionFlag > 0){
                if(returnFlag ==1)return;
                if(callFlag ==1)return;
              //  printf("se gamaw apo kolo %d k onoma %s\n",functionFlag,new->name );
                item* proigoumeno;
                proigoumeno = lookupScopeAbove(new->name,new->scope-1);
              // if(proigoumeno != NULL) printf("above  %s\n",proigoumeno->name);
                item* twra;
                twra = lookupScope(new->name,new->scope);
               //  if(twra != NULL) printf("abovtwra  %s\n",twra->name);
                item* glob;
                glob = lookupScope(new->name,0);
                //if(glob != NULL) printf("global  %s\n",glob->name);
                if(proigoumeno != NULL){
                     char *str = malloc(35 + sizeof(new->name));
                     wht();
                     sprintf(str, "Not access : %s", new->name);
                     error(str, yylineno);
                }else if(glob != NULL){
                  if(!strcmp(glob->type, "User Function")){
                    char *str = malloc(35 + sizeof(new->name));
                     wht();
                     sprintf(str, "Not access : %s", new->name);
                     error(str, yylineno);
                  }else return;
                }else if (twra != NULL)return;
                else{
                  insert_symTable(new);
                  return;
                }
              }else return;
          //tsekarw an einai global
              
          }else if(!strcmp(new->type, "local")){
            new->type = strdup("local variable");

            //den borei na einai library
            if (isLibraryFunction(new->name)){
              char *str = malloc(35 + sizeof(new->name));
              red();
              printf( "Library Funtion : %s\n", new->name);
              wht();
              //error(str, yylineno);
              return;
              //den borei na exei idio onoma me function
            }else if(!strcmp(tmp->type, "User Function") && tmp->scope == new->scope){
                char *str = malloc(35 + sizeof(new->name));
                red();
                printf( "Redeclaration Function : %s\n", new->name);
                wht();
                sprintf(str, "Function name exist : %s", new->name);
                error(str, yylineno);
                return;
                //den kanei insert gt iparxei idi
              }else if((!strcmp(tmp->type, "local variable") || !strcmp(tmp->type, "formal argument")) && tmp->scope == new->scope){
                return;
              }
          //tsekarw an einai global
          }  else if(!strcmp(new->type, "global variable")){
            if (isLibraryFunction(new->name)){
                      char *str = malloc(35 + sizeof(new->name));
                      red();
                      printf( "Library Funtion : %s\n", new->name);
                      wht();
                     // error(str, yylineno);
                      return;

              //den borei na exei idio onoma me function
            }else if(!strcmp(tmp->type, "User Function") && tmp->scope == new->scope){
              char *str = malloc(35 + sizeof(new->name));
              red();

              printf(str, "Redeclaration Function : %s", new->name);
              wht();
              sprintf(str, "Function name exist : %s", new->name);
             // if(callFlag == 1)error(str, yylineno);
              return;
            }else if((!strcmp(tmp->type, "local variable") || !strcmp(tmp->type, "formal argument")) && new->scope !=tmp->scope){
                red();
              printf("preeeeeepeeeiieie na to doymeeeeeeeee\n" );
              //yparxei swsta
            }else if((!strcmp(tmp->type, "local variable") || !strcmp(tmp->type, "formal argument"))&& new->scope == tmp->scope){
              return;
              //yparxei sto scope 0 ara dn kanw init
            }else if(new->scope == tmp->scope){
                return;
              }
          //koitaw an einai function
          }else if(!strcmp(new->type, "User Function")){
             if (isLibraryFunction(new->name)){
                      char *str = malloc(35 + sizeof(new->name));
                      red();
                      //printf( "Library Funtion : %s\n", new->name);
                      wht();
                      sprintf(str, "Library same Function : %s", new->name);
                      error(str, yylineno);
                      return;
              }
            else if(!strcmp(tmp->type, "User Function") && tmp->scope == new->scope){
              char *str = malloc(35 + sizeof(new->name));
              red();
              printf( "Redeclaration Function : %s\n", new->name);
              wht();
              sprintf(str, "User argument : %s", new->name);
              error(str, yylineno);
              return;
            }else if((!strcmp(tmp->type, "local variable") || !strcmp(tmp->type, "global variable") || !strcmp(tmp->type, "formal argument")) && new->scope == tmp->scope ){
              char *str = malloc(35 + sizeof(new->name));
              sprintf(str, "Redeclaration with variable : %s", new->name);
              error(str, yylineno);
              return;
            }
          }else if(!strcmp(new->type, "formal argument")){

            if (isLibraryFunction(new->name)){
                      char *str = malloc(35 + sizeof(new->name));
                      red();
                    //  printf( "Library Funtion : %s\n", new->name);
                      wht();
                      sprintf(str, "Formal same Function : %s", new->name);
                      error(str, yylineno);
                      return;
              }
            else if(!strcmp(tmp->type, "formal argument") && tmp->scope == new->scope){
              char *str = malloc(35 + sizeof(new->name));
              sprintf(str, "Redeclaration formal argument : %s", new->name);
              error(str, yylineno);
              return;
            }else if(!strcmp(tmp->type, "User Function") && tmp->scope == new->scope){
                char *str = malloc(35 + sizeof(new->name));
                red();
                printf( "Redeclaration Function : %s\n", new->name);
                wht();
                sprintf(str, "Function argument : %s", new->name);
                error(str, yylineno);
                return;
            }

          }

        }
        tmp = tmp->next;
      }
  }
  if(!strcmp(new->type, "local"))new->type = strdup("local variable");
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
            if (!strcmp(tmp->name, name) && !strcmp(tmp->type, "User Function"))flag = 1;
            tmp = tmp->next;
        }
    }

    if(flag ==1){return 1;}//brike User Function me idio onoma
    return 0;

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