%{
    #if defined(WIN32)
    #define YY_NO_UNISTD_H
    static int isatty{int i} {return 0;}
    #elif defined(_WIN32_WCE)
    #define YY_NO_UNISTD_H
    static int isatty{int i} {return 0;}
    #endif
    int token_counter = 0;

    
    #include "linkedList.h"
        
    #define  YY_DECL int alpha_yylex ()
   

    /*
    Includes 
    */
%}

%option noyywrap
%option yylineno




/*regex*/

id                          [a-zA-Z][a-zA-Z_0-9]*
integer                     (0[xX][0-9A-Fa-f]+)|([0-9]+)
real                        [0-9]*\.[0-9](e|E)?[0-9]*
space                       [ \r\n\t\v]

comment1                    "//".*
comment2                    "#".*
multyLineComment            "///*"





/*keywords*/

if              "if"
else            "else"
while           "while"
for             "for"
function        "function"
return          "return"
break           "break"
continue        "continue"
and             "and"
not             "not"
or              "or"
local           "local"
true            "true"
false           "false"
nil             "nil"



/*operators*/

assign        "="
plus          "+"
minus         "-"
multiply      "*"
division      "/"
mod           "%"
equal         "=="
n_equal       "!="
plus_plus     "++"
minus_minus   "--"
greater       ">"
less          "<"
g_equal       ">="
l_equal       "<="


/*braces*/

left_curle_bracket    "{"
right_curle_bracket   "}"
left_bracket          "["
right_bracket         "]"
left_parenthesis      "("
right_parenthesis     ")"
semicolon             ";"
comma                 ","
colon                 ":"
double_colons         "::"
dot                   "."
double_dots           ".."
other                 .


    
%%

{id} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "ID","enumerated"); 
        insert(tmp);
    }
{comment1} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "COMMENT1","enumerated"); 
        insert(tmp);
    }
{comment2} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "COMMENT2","enumerated"); 
        insert(tmp);
    }  
{integer} {
        token* tmp = createNewNode(yylineno , token_counter++ , yytext , "INTCONST","enumerated");
        
        insert(tmp);
    }
{real} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "REALCONST","enumerated"); 
        insert(tmp);
    }
{space} {
    }
{multyLineComment} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "COMMENT_BLOCK_COMMENT","enumerated"); 
        insert(tmp);
    }




{assign} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR_ASSIGN","enumerated"); 
        insert(tmp);
    }
{plus} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR_PLUS","enumerated"); 
        insert(tmp);
    }
{minus} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR_MINUS","enumerated"); 
        insert(tmp);
    }
{multiply} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR_MULTIPLY","enumerated"); 
        insert(tmp);
    }
{division} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR_DIVISION","enumerated"); 
        insert(tmp);
    }
{mod} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR_MOD","enumerated"); 
        insert(tmp);
    }
{equal} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR_EQUAL","enumerated"); 
        insert(tmp);
    }
{n_equal} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR_NOT_EQUAL","enumerated"); 
        insert(tmp);
    }
{plus_plus} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR_PLUS_PLUS","enumerated"); 
        insert(tmp);
    }
{minus_minus} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR_MINUS_MINUS","enumerated"); 
        insert(tmp);
    }
{greater} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR_GREATER","enumerated"); 
        insert(tmp);
    }
{less} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR_LESS","enumerated"); 
        insert(tmp);
    }
{g_equal} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR_GREATER_EQUAL","enumerated"); 
        insert(tmp);
    }
{l_equal} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR_LESS_EQUAL","enumerated"); 
        insert(tmp);
    }





{left_curle_bracket} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION_LEFT_CURLY_BRACE","enumerated"); 
        insert(tmp);
    }
{right_curle_bracket} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION_RIGHT_CURLY_BRACE","enumerated"); 
        insert(tmp);
    }
{left_bracket} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION_LEFT_BRACE","enumerated"); 
        insert(tmp);
    }
{right_bracket} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION_RIGHT_BRACE","enumerated"); 
        insert(tmp);
    }
{left_parenthesis} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION_LEFT_PARENTHESIS","enumerated"); 
        insert(tmp);
    }
{right_parenthesis} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION_RIGHT_PARENTHESIS","enumerated"); 
        insert(tmp);
    }
{semicolon} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION_SEMI_COLON","enumerated"); 
        insert(tmp);
    }
{comma} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION_COMMA","enumerated"); 
        insert(tmp);
    }
{colon} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION_COLON","enumerated"); 
        insert(tmp);
    }
{double_colons} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION_DOUBLE_COLONS","enumerated"); 
        insert(tmp);
    }
{dot} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION_DOT","enumerated"); 
        insert(tmp);
    }
{double_dots} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION_DOUBLE_DOTS","enumerated"); 
        insert(tmp);
    }
{other} {
        red();
       
        fprintf(stderr , "UNDEFINED CHARACTER");
        token* tmp = createNewNode(yylineno , token_counter++ , yytext , "UNDEFINED_TOKEN","enumerated"); 
        insert(tmp);
    
        
        wht();
    }

%%





int main(int argc , char** argv)
{
    if(argc>1)
    {
        if(!(yyin = fopen(argv[1] , "r"))){
            
            fprintf(stderr , "Cannot open file\n");    
        }
    }else
        yyin = stdin;
    
    alpha_yylex();
    printList();
    return 0;
}
