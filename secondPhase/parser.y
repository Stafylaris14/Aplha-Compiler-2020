%{

#include "dataStructs/linkedList.h"
#include "dataStructs/commentStack.h"
#include "dataStructs/symb.h"
#include "utilities/parserUtilities.h"


int yyerror(char *yaccProvideMessage);
int yylex(void);

int scopeCounter = 0;
extern int yylineno;
extern char* yytext;
extern FILE* yyin;



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

Stmt: Expression semicolon {;}
    | Ifstmt {;}
    | Whilestmt {;}
    | Forstmt {;}
    | Returnstmt {;}
    | Break semicolon {;}
    | Continue semicolon {;}
    | Block {;}
    | Funcdef {;}
    | semicolon   {;}
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
        | plus_plus Lvalue {;}
        | Lvalue plus_plus {;}
        | minus_minus Lvalue {;}
        | Lvalue minus_minus {;}
        | Primary {;}
        ;

Assignexpression: Lvalue assign Expression {;}
                    ;




Primary: Lvalue {;}
        | Call {;}
        | Objectdef {;}
        | left_parenthesis Funcdef right_parenthesis {;}
        | Const {;}
        ;




Lvalue: id {
                if(!isLibraryFunction($1)){
                        item* new = newItem($1,"id", scopeCounter , yylineno );
                        insert_symTable(new);
                }else{
                        errorLibFunction(yylineno , $1);
                }

        }
        | local id {
                        if(!isLibraryFunction($2)){
                                item* new = newItem($2,"id", scopeCounter , yylineno );
                                insert_symTable(new);
                        }else{
                                errorLibFunction(yylineno , $2);
                        }
        }
        | double_colons id {;}
        | Member {;}
        ;


Member: Lvalue dot id {;}
        | Lvalue left_bracket Expression right_bracket {;}
        | Call dot id {;}
        | Call left_bracket Expression right_bracket {;}
        ;


Call: Call left_parenthesis Elist right_parenthesis {;}
        | Lvalue Callsuffix {;}
        | left_parenthesis Funcdef right_parenthesis left_parenthesis Elist right_parenthesis {;}
        ;



Callsuffix: Normalcall {;}
            | Methodcall {;}
            ;

Normalcall: left_parenthesis Elist right_parenthesis {;}
            ;



Methodcall: double_dots id left_parenthesis Elist right_parenthesis {;}
            ;



Elist:  Expression Multy_exp {;}
        | {;}
        ;

Multy_exp: comma Expression Multy_exp {;}
        | {;}
        ;

Objectdef: left_bracket Elist right_bracket {;}
        | left_bracket Indexed right_bracket {;}
        ;


Indexed: Indexedelement Multy_ind {;}
         ;

Multy_ind: Multy_ind comma Indexedelement {;}
        | {;}
         ;

Indexedelement: left_curle_bracket{scopeCounter++;
                if(scopeCounter > maxScope) maxScope = scopeCounter;}
                Expression colon Expression right_curle_bracket {
                        hide(scopeCounter);
                        scopeCounter--;
                        printSymTable();
                 }
                ;


Block: left_curle_bracket{scopeCounter++;
        if(scopeCounter > maxScope) maxScope = scopeCounter;}
        States right_curle_bracket {
            hide(scopeCounter);
            scopeCounter--;}
        ;




Funcdef: Function id {;}
        | Function left_parenthesis Idlist right_parenthesis {;}
        ;



Const: integer {fprintf(stderr,"integer %d on line %d\n",$1,yylineno);;}
        | real {;}
        | string {;}
        | nil {;}
        | True {;}
        | False {;}
        ;



Idlist: id Multy_id {;}
        | {;}
        ;

Multy_id: Multy_id comma id {;}
        | {;}
        ;




Ifstmt: If left_parenthesis Expression right_parenthesis Stmt {;}
        | If left_parenthesis Expression right_parenthesis Stmt Else Stmt {;}
        ;

Whilestmt: While left_parenthesis Expression right_parenthesis Stmt {;}
    ;

Forstmt: For left_parenthesis Elist semicolon Expression semicolon Elist right_parenthesis Stmt {;}
        ;


Returnstmt: Return semicolon {;}
            | Return Expression semicolon {;}
            ;



%%


//tin ftiaxoyme

int yyerror (char * YaccProvidedMessage){
        fprintf(stderr,"%s\n",YaccProvidedMessage);
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
    printSymTable();
    printHash();
}
