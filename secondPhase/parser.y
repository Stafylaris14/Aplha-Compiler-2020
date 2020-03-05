%{

#include "dataStructs/linkedList.h"
#include "dataStructs/commentStack.h"
#include "dataStructs/symb.h"
%}



%union{
    int intVal;
    char* strVal;
    symrec *tptr;
    double doubleVal;

}


%start program

%token <intVal> integer
%token <StrVal> id
%token <doubleVal> real
%token <strVal> string


/*keywords*/


%token if
%token else
%token while
%token for
%token function
%token return
%token break
%token continue
%token and
%token not
%token or
%token local
%token true
%token false
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



/*prepei na kanoume protereothta*/




%%

program: States
    ;

States: States Stmt 
    |   /*kati*/
    ;

Stmt: Expression semicolon
    | Ifstmt
    | Whilestmt
    | Forstmt
    | Returnstmt
    | break semicolon
    | continue semicolon
    | Block
    | Funcdef
    | semicolon    
    ;
Expression: Assignexpression
            | Expression plus Expression
            | Expression minus Expression
            | Expression and Expression
            | Expression or Expression
            | Expression multiply Expression
            | Expression division Expression    
            | Expression mod Expression
            | Expression equal Expression
            | Expression n_equal Expression
            | Expression greater Expression
            | Expression less Expression
            | Expression g_equal Expression
            | Expression l_equal Expression
            | Term
             ;

    
Term:   left_parenthesis Expression right_parenthesis
        | minus Expression
        | not Expression
        | plus_plus Lvalue
        | Lvalue plus_plus
        | minus_minus Lvalue
        | Lvalue minus_minus
        | Primary
        ;

Assignexpression: Lvalue assign Expression
                    ;




Primary: Lvalue
        | Call
        | Objectdef
        | left_parenthesis Funcdef right_parenthesis
        | Const
        ;




Lvalue: id
        | Local id
        | double_colons id 
        | Member
        ;


Member: Lvalue dot id
        | Lvalue left_bracket Expression right_bracket
        | Call dot id
        | Call left_bracket Expression right_bracket
        ;


Call: Call left_parenthesis Elist right_parenthesis
        | Lvalue Callsuffix
        | left_parenthesis Funcdef right_parenthesis left_parenthesis Elist right_parenthesis 

        ;



Callsuffix: Normalcall
            | Methodcall
            ;

Normalcall: left_bracket Elist right_parenthesis
            ;


            
MethodCall: double_dots id left_parenthesis Elist right_parenthesis



/*na to ftia3oumeee*/
Elist: 
        | 
        ;



Objectdef: left_bracket Elist right_bracket
        | left_bracket Indexed right_bracket
        ;


/*na to ftia3oume */
Indexed: Indexedelement
        | 


    ;

Indexedelement: left_curle_bracket Expression colon Expression right_curle_bracket
                ;


Block: left_curle_bracket States right_curle_bracket
        ;
        



Funcdef: function
        | function id
        | function left_parenthesis idlist right_parenthesis
        ;



Const: integer
        | real
        | string
        | nil
        | true
        | false
        ;

/* na to ftia3oume */

Idlist:
    ;
    
Ifstmt: if left_parenthesis Expression right_parenthesis Stmt
        | if left_parenthesis Expression right_parenthesis Stmt else Stmt
        ;

Whilestmt: while left_parenthesis Expression right_parenthesis Stmt
    ;

Forstmt: for left_parenthesis Elist semicolon Expression semicolon Elist right_parenthesis Stmt
        ;


Returnstmt: return semicolon
            | return Expression semicolon
            ;



%%