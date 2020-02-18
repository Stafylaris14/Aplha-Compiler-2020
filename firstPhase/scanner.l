%{
    #if defined(WIN32)
    #define YY_NO_UNISTD_H
    static int isatty{int i} {return 0;}
    #elif defined(_WIN32_WCE)
    #define YY_NO_UNISTD_H
    static int isatty{int i} {return 0;}
    #endif


    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
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
space                       [\r\n\t\v]
newline                     "\\n"

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



    
%%

{id} {fprintf(stderr , "Found a Id in line %d with value %s\n" , yylineno , yytext);}
{comment1} {fprintf(stderr , "Found a singlecomment1 in line %s \n" , yytext);}
{integer} {fprintf(stderr , "found an integer in line %d , with value %s\n" , yylineno , yytext);}
{real} {fprintf(stderr , "found an real in line %d , with value %s\n" , yylineno , yytext);}
{space} {fprintf(stderr , "found an space in line %d , with value %s\n" , yylineno , yytext);}
{newline} {fprintf(stderr , "found an newline in line %d , with value %s\n" , yylineno , yytext);}
{multyLineComment} {fprintf(stderr , "found an multyLineComment in line %d \n" , yylineno);}


{assign} {fprintf(stderr , "found an assignment in line %d , with value %s\n" , yylineno , yytext);}
{plus} {fprintf(stderr , "found a plus in line %d , with value %s\n" , yylineno , yytext);}
{minus} {fprintf(stderr , "found an minus in line %d , with value %s\n" , yylineno , yytext);}
{multiply} {fprintf(stderr , "found a multiply in line %d , with value %s\n" , yylineno , yytext);}
{division} {fprintf(stderr , "found a division in line %d , with value %s\n" , yylineno , yytext);}
{mod} {fprintf(stderr , "found a mod in line %d , with value %s\n" , yylineno , yytext);}
{equal} {fprintf(stderr , "found an equal in line %d , with value %s\n" , yylineno , yytext);}
{n_equal} {fprintf(stderr , "found a not equal in line %d , with value %s\n" , yylineno , yytext);}
{plus_plus} {fprintf(stderr , "found a plus plus in line %d , with value %s\n" , yylineno , yytext);}
{minus_minus} {fprintf(stderr , "found a minus minus in line %d , with value %s\n" , yylineno , yytext);}
{greater} {fprintf(stderr , "found a greater in line %d , with value %s\n" , yylineno , yytext);}
{less} {fprintf(stderr , "found a less in line %d , with value %s\n" , yylineno , yytext);}
{g_equal} {fprintf(stderr , "found a greater equal in line %d , with value %s\n" , yylineno , yytext);}
{l_equal} {fprintf(stderr , "found a less equal in line %d , with value %s\n" , yylineno , yytext);}





{left_curle_bracket} {fprintf(stderr , "found a left curle bracket in line %d \n" ,yylineno);}
{right_curle_bracket} {fprintf(stderr , "found a right curle bracket in line %d \n" ,yylineno);}
{left_bracket} {fprintf(stderr , "found a left curle bracket in line %d \n" , yylineno);}
{right_bracket} {fprintf(stderr , "found a right curle bracket in line %d \n" , yylineno);}
{left_parenthesis} {fprintf(stderr , "found an left_parenthesis in line %d , with value %s\n" , yylineno , yytext);}
{right_parenthesis} {fprintf(stderr , "found an right_parenthesis in line %d , with value %s\n" , yylineno , yytext);}
{semicolon} {fprintf(stderr , "found an semicolon in line %d , with value %s\n" , yylineno , yytext);}
{comma} {fprintf(stderr , "found an comma in line %d , with value %s\n" , yylineno , yytext);}
{colon} {fprintf(stderr , "found an colon in line %d , with value %s\n" , yylineno , yytext);}
{double_colons} {fprintf(stderr , "found an double_colons in line %d , with value %s\n" , yylineno , yytext);}
{dot} {fprintf(stderr , "found an dot in line %d , with value %s\n" , yylineno , yytext);}
{double_dots} {fprintf(stderr , "found an double_dots in line %d , with value %s\n" , yylineno , yytext);}


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
    
    yylex();
    return 0;
}
