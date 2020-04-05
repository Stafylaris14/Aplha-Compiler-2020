%{

#include "dataStructs/linkedList.h"
#include "dataStructs/commentStack.h"


#include "./utilities/parserUtilities.h"


int yyerror(char *yaccProvideMessage);
int yylex(void);

int scopeCounter = 0;
extern int yylineno;
int returnFlag = 0;
extern char* yytext;
extern FILE* yyin;
int functionCounter = 0; /* for no name functions */
int functionFlag  = 0;  /*1 if is inside a function for RETURN stmt*/
int callFlag =0; // an exw call
int objectHide = 1;//na min kanei hide an einai se object


int loopFlag = 0;       /*1 if its inside a loop (for break and Continue)*/
int libcheck = 0;
char* functionName ; /* used to add formal arguments to linked list */
%}



%union{
    int intVal;
    char* strVal;
    double doubleVal;
}


%start program

%token <intVal> integer
%token <strVal> id
%token <doubleVal> real
%token <strVal> string


/*keywords*/


%token If
%token Else
%token While
%token For
%token Function
%token Return
%token Break
%token Continue
%token and
%token not
%token or
%token local
%token True
%token False
%token nil




/*operators*/

%token assign
%token plus
%token minus
%token multiply
%token division
%token mod
%token equal
%token n_equal
%token plus_plus
%token minus_minus
%token greater
%token less
%token g_equal
%token l_equal



/*braces*/

%token left_curle_bracket
%token right_curle_bracket
%token left_bracket
%token right_bracket
%token left_parenthesis
%token right_parenthesis
%token semicolon
%token comma
%token colon
%token double_colons
%token dot
%token double_dots
%token other



/*protereothta*/

%left assign
%left or
%left and
%nonassoc equal n_equal
%nonassoc greater g_equal less l_equal
%left plus minus
%left multiply division mod
%left not plus_plus minus_minus Uminus
%left dot
%left double_dots
%left left_bracket right_bracket
%left left_parenthesis right_parenthesis


%%

program: States {;}
    ;

States: States Stmt {;}
    |
    ;

Stmt: Expression semicolon {libcheck =0;}
    | Ifstmt {;}
    | Whilestmt {;}
    | Forstmt {;}
    | Returnstmt {if(functionFlag == 0)error("no function to return" , yylineno);}
    | Break semicolon {libcheck =0;if(loopFlag == 0)error("no loop to break" , yylineno);}
    | Continue semicolon {libcheck =0;if(loopFlag == 0)error("no loop to Continue" , yylineno);}
    | Block {;}
    | Funcdef {;}
    | semicolon {libcheck =0;}
    ;


Expression: Assignexpression {;}
            | Expression plus Expression {;}
            | Expression minus Expression {;}
            | Expression multiply Expression {;}
            | Expression division Expression {;}
            | Expression and Expression {;}
            | Expression or Expression {;}
            | Expression mod Expression {;}
            | Expression equal Expression {;}
            | Expression n_equal Expression {;}
            | Expression greater Expression {;}
            | Expression less Expression {;}
            | Expression g_equal Expression {;}
            | Expression l_equal Expression {;}
            | Term {;}
             ;


Term:   left_parenthesis Expression right_parenthesis {;}
        | minus Expression %prec Uminus {;}
        | not Expression {;}
        | plus_plus Lvalue {if(libcheck == 1){error("Den boreis na kaneis pra3eis me synartiseis", yylineno); libcheck=0;}}
        | Lvalue plus_plus {if(libcheck == 1){error("Den boreis na kaneis pra3eis me synartiseis", yylineno); libcheck=0;}}
        | minus_minus Lvalue {if(libcheck == 1){error("Den boreis na kaneis pra3eis me synartiseis", yylineno); libcheck=0;}}
        | Lvalue minus_minus {if(libcheck == 1){error("Den boreis na kaneis pra3eis me synartiseis", yylineno); libcheck=0;}}
        | Primary {;}
        ;

Assignexpression: Lvalue {if(libcheck == 1){error("Den boreis na kaneis pra3eis me synartiseis", yylineno); libcheck=0;}} assign Expression {


                }
                ;




Primary: Lvalue {;}
        | Call {callFlag =1;}
        | Objectdef {;}
        | left_parenthesis Funcdef right_parenthesis {;}
        | Const {;}
        ;




Lvalue: id {
                                if(isLibraryFunction($1)){libcheck =1;}
                                if(isFA($1))libcheck =1;
                                item* new;
                                if(scopeCounter == 0){new = newItem($1,"global variable", scopeCounter , yylineno );new_check(new); }
                                else {item* new = newItem($1,"local variable", scopeCounter , yylineno );new_check(new);}
        }
        | local id {
                                if(isLibraryFunction($2))libcheck =1;
                              //  if(isFA($2))libcheck =1;
                                item* new = NULL;
                                new = newItem($2,"local", scopeCounter , yylineno );
                                new_check(new);
        }
        | double_colons id {
                                if(isFA($2))libcheck =1;
                                item* tmp = lookupScope($2 , 0);
                                if(tmp == NULL){error("Cant find Global " , yylineno);}                
        }
        | Member {;};
        ;


Member: Lvalue dot id {libcheck = 0;}
        | Lvalue left_bracket Expression right_bracket {libcheck = 0;}
        | Call {callFlag =1;libcheck =0;} dot id {callFlag =0;libcheck = 0;}
        | Call {callFlag =1;libcheck=0;} left_bracket Expression right_bracket {callFlag =0;libcheck = 0;}
        ;


Call: Call {callFlag =1;libcheck = 0;}left_parenthesis Elist right_parenthesis {callFlag =0;}
        |  Lvalue{callFlag =1;libcheck = 0;} Callsuffix {callFlag =0;}
        | left_parenthesis{callFlag =1;libcheck = 0;} Funcdef right_parenthesis left_parenthesis Elist right_parenthesis {callFlag =0;}
        ;



Callsuffix: Normalcall {callFlag =1;}
            | Methodcall {callFlag =1;}
            ;

Normalcall: left_parenthesis {callFlag =1;} Elist right_parenthesis {;}
            ;



Methodcall: double_dots {callFlag =1;} id left_parenthesis Elist right_parenthesis {;}
            ;



Elist:  Expression Multy_exp {;}
        | {;}
        ;

Multy_exp: comma Expression Multy_exp {;}
        | {;}
        ;

Objectdef: left_bracket{scopeCounter--;objectHide =0;}Elist right_bracket {scopeCounter++;objectHide=1;}
        | left_bracket{scopeCounter--;objectHide =0;} Indexed right_bracket {scopeCounter++;objectHide=1;}
        ;


Indexed: Indexedelement Multy_ind {;}
         ;

Multy_ind: Multy_ind comma Indexedelement {;}
        | {;}
         ;

Indexedelement: left_curle_bracket{scopeCounter++;
                if(scopeCounter > maxScope) maxScope = scopeCounter;}
                Expression colon Expression right_curle_bracket {
                        if(objectHide)hide(scopeCounter);
                        scopeCounter--;

                 }
                ;


Block: left_curle_bracket{scopeCounter++;
        if(scopeCounter > maxScope) maxScope = scopeCounter;}
        States right_curle_bracket {
                if(objectHide)hide(scopeCounter);
                scopeCounter--;}
        ;


Funcdef: Function id {
                                item* new = newItem($2,"User Function", scopeCounter , yylineno );
                                new_check(new);
                                functionName = strdup($2);
        } left_parenthesis{scopeCounter++;} Idlist  right_parenthesis{scopeCounter--;functionFlag++;} Block{functionFlag --;}
        | Function{
                        char noname[20];
                        sprintf(noname,"function$%d",functionCounter);
                        functionCounter++;
                        functionName = strdup(noname);
                        item* new = newItem(noname,"User Function", scopeCounter , yylineno );
                        new_check(new);
        }
         left_parenthesis{scopeCounter++;} Idlist right_parenthesis {scopeCounter--;functionFlag++;} Block{functionFlag --;}
        ;



Const:  integer {;}
        | real {;}
        | string {;}
        | nil {;}
        | True {;}
        | False {;}
        ;



Idlist: id Multy_id {
                item* new = newItem($1,"formal argument", scopeCounter , yylineno );
                    new_check(new);
                    insert_formal_arg(functionName , $1);
        }
        | {;}
        ;

Multy_id: Multy_id comma id {
                item* new = newItem($3,"formal argument", scopeCounter , yylineno );
                  new_check(new);
                  insert_formal_arg(functionName , $3);
        }
        | {;}
        ;




Ifstmt: If left_parenthesis Expression right_parenthesis Stmt {;}
        | If left_parenthesis Expression right_parenthesis Stmt Else Stmt {;}
        ;

Whilestmt: While left_parenthesis Expression right_parenthesis {loopFlag ++;} Stmt {loopFlag--;}
    ;

Forstmt: For left_parenthesis Elist semicolon Expression semicolon Elist right_parenthesis {loopFlag ++;} Stmt {loopFlag --;}
        ;


Returnstmt: Return semicolon{libcheck =0;}
        | Return{returnFlag = 1; } Expression semicolon {libcheck =0;returnFlag =0; }
            ;



%%




int yyerror (char * YaccProvidedMessage){
        red();
        fprintf(stderr,"%s in :%d\n",YaccProvidedMessage , yylineno);
        wht();
        exit(1);
        return 0;
}


int main(int argc, char** argv)
{
  maxScope = 0;
  init_symTable();
  if(argc > 1){
    if (!(yyin = fopen(argv[1], "r"))){
        fprintf(stderr,"Cannot read file: %s\n", argv[1]);
	return 1;
    }
  }

    yyparse();
    //printSymTable();
    
    //printHash();
    printScopeList();
   
}
