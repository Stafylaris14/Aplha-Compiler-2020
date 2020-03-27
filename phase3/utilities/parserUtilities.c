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

char* returnErrorString(char* text,char* name)
{
  char *str = malloc(35 + sizeof(name));
  sprintf(str, "%s : %s" , text, name);
  return str;
}

int accessToFunction(item* new){
  if (returnFlag == 1)
    return 1;
  if (callFlag == 1)
    return 1;
  item *proigoumeno;
  proigoumeno = lookupScopeAbove(new->name, new->scope - 1);
  item *twra;
  twra = lookupScope(new->name, new->scope);
  item *glob;
  glob = lookupScope(new->name, 0);
  //if(glob != NULL) printf("global  %s\n",glob->name);
  
  if (proigoumeno != NULL)
  {
    
    if(twra != NULL){
     if(!strcmp(twra->type, "local variable")) return 1;
    }
   //printf(" proi %s k type %s k scope %d\n",proigoumeno->name,proigoumeno->type,proigoumeno->scope);
    char *str = returnErrorString("Not access",new->name);
    error(str, yylineno);
  }
  else if (glob != NULL)
  {
    
    if (!strcmp(glob->type, "User Function"))
    {
      if(twra != NULL)
      if(!strcmp(twra->type, "formal argument")) return 1;

      char *str = returnErrorString("Not access", new->name);
      
      error(str, yylineno);
      
     
    }
    else
      return 1;
  }
  else if (twra != NULL)
    return 1;
  else
  {
    insert_symTable(new);
    return 1;
  }
  return 0;
}



void new_check(item *new){
  int i=0;
  item *tmp = NULL;
  for (i = 0; i < HASH_SIZE; i++) {
      tmp = symtable[i];
      while (tmp != NULL){
        if (!strcmp(tmp->name, new->name) && tmp->isActive){      //an einai idio onoma meta 3ekinaw elenxoys
          // printf("idio onoma %s ka newitype %s kai tmptypw %s kai scope %d k scope idio %d k diko m line %d\n",tmp->name,new->type,tmp->type,new->scope,tmp->scope,new->lineno);
          //tsekarw an einai local to type pou 8elw na balw
          if(!strcmp(new->type, "local variable")){
          //  printf("ti fasss %s k socpe %d\n",new->name,new->scope);
            //den borei na einai library
            if (isLibraryFunction(new->name)){
              return;
              //den borei na exei idio onoma me function
            } else if(!strcmp(tmp->type, "User Function") && tmp->scope == new->scope){
                char *str = returnErrorString("Redeclaration Funtion",new->name);
                if(returnFlag ==1)return;
                error(str, yylineno);
                return;
                //den kanei insert gt iparxei idi
            }else if(functionFlag > 0){
                if(accessToFunction(new))return;
              }else return;
          //tsekarw an einai global
              
          }else if(!strcmp(new->type, "local")){
            new->type = strdup("local variable");
            //den borei na einai library
            if (isLibraryFunction(new->name)){
               char *str = returnErrorString("Library same Function", new->name);
               error(str, yylineno);
              return;
              //den borei na exei idio onoma me function
            }else if(!strcmp(tmp->type, "User Function") && tmp->scope == new->scope){
              char *str = returnErrorString("Redeclaration Function", new->name);
              error(str, yylineno);
              return;
              //den kanei insert gt iparxei idi
              }else if((!strcmp(tmp->type, "local variable") || !strcmp(tmp->type, "formal argument")) && tmp->scope == new->scope){
                return;
              }
          //tsekarw an einai global
         // printf("telos apo Sketo Local %s k scope %d\n",new->name,new->scope);
          }  else if(!strcmp(new->type, "global variable")){
            if (isLibraryFunction(new->name)){
                      
                     // red();
                    //  printf( "Library Funtion : %s\n", new->name);
                    //  wht();
                     // error(str, yylineno);
                      return;

              //den borei na exei idio onoma me function
            }else if(!strcmp(tmp->type, "User Function") && tmp->scope == new->scope){
              char *str = malloc(35 + sizeof(new->name)); 
             // if(callFlag == 1)error(str, yylineno);
              return;
            }else if((!strcmp(tmp->type, "local variable") || !strcmp(tmp->type, "formal argument")) && new->scope !=tmp->scope){
                red();
             // printf("preeeeeepeeeiieie na to doymeeeeeeeeeeeeeeeeeee\n" );
              return;
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
               char *str = returnErrorString("Library same Function", new->name);
               error(str, yylineno);
               return;
              }
            else if(!strcmp(tmp->type, "User Function") && tmp->scope == new->scope){
              char *str = returnErrorString("Redeclaration Function ", new->name);
              error(str, yylineno);
              return;
            }else if((!strcmp(tmp->type, "local variable") || !strcmp(tmp->type, "global variable") || !strcmp(tmp->type, "formal argument")) && new->scope == tmp->scope ){
              char *str = returnErrorString("Redeclaration with variable", new->name);
              error(str, yylineno);
              return;
            }
          }else if(!strcmp(new->type, "formal argument")){

            if (isLibraryFunction(new->name)){
              char *str = returnErrorString("Formal same Function", new->name);
              error(str, yylineno);
              return;
              }
            else if(!strcmp(tmp->type, "formal argument") && tmp->scope == new->scope){
              char *str = returnErrorString("Redeclaration formal argument ",new->name);
              error(str, yylineno);
              return;
            }else if(!strcmp(tmp->type, "User Function") && tmp->scope == new->scope){
              char *str = returnErrorString("Redeclaration Function", new->name);
              error(str, yylineno);
              return;
            }

          }

        }
        tmp = tmp->next;
      }
  }
  if(!strcmp(new->type, "local"))new->type = strdup("local variable");
  //printf("bazw %s se scope %d k type\n",new->name,new->scope,new->type);
  insert_symTable(new);
}


/* is Formal Argument

*/
int isFA(char *name)
{
    item *tmp = NULL;
    int i;
    int function = 0;
    for (i = 0; i < HASH_SIZE; i++)
    {
        tmp = symtable[i];
        while (tmp != NULL)
        {
            if (!strcmp(tmp->name, name) && !strcmp(tmp->type, "User Function")){
             if (function == 0)function= 1;
              }else  if (!strcmp(tmp->name, name) && !strcmp(tmp->type, "formal argument") && tmp->isActive){
                function= 2;
              }

            tmp = tmp->next;
        }
    }

    if(function == 1) return 1;
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
        
        formals = malloc(sizeof(formal));
        formals->arg = lookupScope(name , tmp->scope+1);
        formals->next = NULL;
        tmp->formalArg = formals;
    }
    else
    {
        
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
    
    if(args != NULL) 
    {
        while (args != NULL)
        {
            printf("(%s)\n" , args->arg->name);
            args = args->next;
            
        }
    }
}