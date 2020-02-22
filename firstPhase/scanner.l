%{
    #if defined(WIN32)
    #define YY_NO_UNISTD_H
    static int isatty{int i} {return 0;}
    #elif defined(_WIN32_WCE)
    #define YY_NO_UNISTD_H
    static int isatty{int i} {return 0;}
    #endif
    int token_counter = 1;


    #include "dataStructs/linkedList.h"
    #include "dataStructs/commentStack.h"

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
string                      "\""
comment1                    "//".*
comment2                    "#".*
multy_comment               "/*"


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

%x COMMENT
%x STRING

%%


{comment1} {token* tmp = createNewNode(yylineno , token_counter++ , "" , "COMMENT", "LINE_COMMENT","enumerated");
        insert(tmp);
    }
{comment2} {token* tmp = createNewNode(yylineno , token_counter++ , yytext ,"COMMENT", "COMMENT2","enumerated");
        insert(tmp);
    }
{multy_comment} BEGIN(COMMENT); int lineCounter = 0; push(yylineno);

<COMMENT>{
    "/*" {
        wht();
        push(yylineno);
    }
    "\n"   lineCounter++;
    "*/" {
            /*ean theloyme na emfanizei to ending line prepei na alla3oyme opou startLine -> yylineno*/
            
            // fprintf(stderr,"kleinw %d\n",yylineno);

            printStack();
            int startLine = pop();

            char buffer[100];
            sprintf(buffer,"%d - %d",startLine,yylineno);
            if(isEmpty()){
            token* tmp = createNewNode(startLine , token_counter++ , buffer ,"COMMENT", "BLOCK_COMMENT","enumerated");
            insert(tmp);
            }else{
              token* tmp = createNewNode(startLine , token_counter++ , buffer ,"NESTED COMMENT", "BLOCK_COMMENT","enumerated");
              insert(tmp);
            }
            if(isEmpty())BEGIN(INITIAL);
            else BEGIN(COMMENT);



        }
    .

    <<EOF>> {
        if(!isEmpty()){
            red();
            fprintf(stderr , "EXPECTING *\\ in line %d " , yylineno);
            wht();
            exit(0);
        }
    }
}



{string} BEGIN(STRING);int size = 100; char* myString = malloc(size);int count = 1;int real =1;


<STRING>{
    "\"" {
        // cyn();
        token* tmp = createNewNode(yylineno , token_counter++ , myString ,"STRING", myString,"char*");
        insert(tmp);
        
        myString = NULL;
        BEGIN(INITIAL);
        wht();
    }

    "\\n" {
            count++;
            if(count > size*real){
              real++;
              myString = realloc(myString,size*real);
            }
            strcat(myString , "\n");
    }
    "\\t" {
            count++;
            if(count > size*real){
              real++;
              myString = realloc(myString,size*real);
            }
            strcat(myString , "\t");
    }
    "\\r" {
            count++;
            if(count > size*real){
              real++;
              myString = realloc(myString,size*real);
            }
            strcat(myString , "\r");
    }
    "\\v" {
            count++;
            if(count > size*real){
              real++;
              myString = realloc(myString,size*real);
            }
            strcat(myString , "\v");
    }
    "\\\"" {
            count++;
            if(count > size*real){
              real++;
              myString = realloc(myString,size*real);
            }
            strcat(myString , "\"");
    }
    "\\"{
        count++;
            if(count > size*real){
              real++;
              myString = realloc(myString,size*real);
            }
            strcat(myString , "\"); 
    }
    . {
        cyn();
            count++;
            if(count > size*real){
              real++;
              myString = realloc(myString,size*real);
            }
            strcat(myString , yytext);
    }
    <<EOF>> {
        red();
        fprintf(stderr , "EXPECTED  CLOSING STRING WITH \" IN LINE %d" , yylineno);
        wht();
        exit(0);
    }
}

{if} { token* tmp = createNewNode(yylineno , token_counter++ , yytext , "KEYWORD" , "IF" , "keyword");insert(tmp);}
{else} { token* tmp = createNewNode(yylineno , token_counter++ , yytext , "KEYWORD" , "ELSE" , "keyword");insert(tmp);}
{while} { token* tmp = createNewNode(yylineno , token_counter++ , yytext , "KEYWORD" , "WHILE" , "keyword");insert(tmp);}
{for} { token* tmp = createNewNode(yylineno , token_counter++ , yytext , "KEYWORD" , "FOR" , "keyword");insert(tmp);}
{function} { token* tmp = createNewNode(yylineno , token_counter++ , yytext , "KEYWORD" , "FUNCTION" , "keyword");insert(tmp);}
{return} { token* tmp = createNewNode(yylineno , token_counter++ , yytext , "KEYWORD" , "RETURN" , "keyword");insert(tmp);}
{break} { token* tmp = createNewNode(yylineno , token_counter++ , yytext , "KEYWORD" , "BREAK" , "keyword");insert(tmp);}
{continue} { token* tmp = createNewNode(yylineno , token_counter++ , yytext , "KEYWORD" , "CONTINUE" , "keyword");insert(tmp);}
{and} { token* tmp = createNewNode(yylineno , token_counter++ , yytext , "KEYWORD" , "AND" , "keyword");insert(tmp);}
{not} { token* tmp = createNewNode(yylineno , token_counter++ , yytext , "KEYWORD" , "NOT" , "keyword");insert(tmp);}
{or} { token* tmp = createNewNode(yylineno , token_counter++ , yytext , "KEYWORD" , "OR" , "keyword");insert(tmp);}
{local} { token* tmp = createNewNode(yylineno , token_counter++ , yytext , "KEYWORD" , "LOCAL" , "keyword");insert(tmp);}
{true} { token* tmp = createNewNode(yylineno , token_counter++ , yytext , "KEYWORD" , "TRUE" , "keyword");insert(tmp);}
{false} { token* tmp = createNewNode(yylineno , token_counter++ , yytext , "KEYWORD" , "FALSE" , "keyword");insert(tmp);}
{nil} { token* tmp = createNewNode(yylineno , token_counter++ , yytext , "KEYWORD" , "NIL" , "keyword");insert(tmp);}
{integer} {
        token* tmp = createNewNode(yylineno , token_counter++ , yytext , "CONST_INT" , yytext ,"integer");

        insert(tmp);
    }
{real} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "REALCONST", yytext ,"enumerated");
        insert(tmp);
    }
{space} {
    }
{assign} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR" , "ASSIGN","enumerated");
        insert(tmp);
    }
{plus} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR" , "PLUS","enumerated");
        insert(tmp);
    }
{minus} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR" , "MINUS","enumerated");
        insert(tmp);
    }
{multiply} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR" , "MULTIPLY","enumerated");
        insert(tmp);
    }
{division} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR" , "DIVISION","enumerated");
        insert(tmp);
    }
{mod} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR" , "MOD","enumerated");
        insert(tmp);
    }
{equal} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR" , "EQUAL","enumerated");
        insert(tmp);
    }
{n_equal} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR" , "NOT_EQUAL","enumerated");
        insert(tmp);
    }
{plus_plus} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR" , "PLUS_PLUS","enumerated");
        insert(tmp);
    }
{minus_minus} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR" , "MINUS_MINUS","enumerated");
        insert(tmp);
    }
{greater} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR" , "GREATER","enumerated");
        insert(tmp);
    }
{less} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR" , "LESS","enumerated");
        insert(tmp);
    }
{g_equal} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR" , "GREATER_EQUAL","enumerated");
        insert(tmp);
    }
{l_equal} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "OPERATOR" , "LESS_EQUAL","enumerated");
        insert(tmp);
    }
{left_curle_bracket} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION" , "LEFT_CURLY_BRACE","enumerated");
        insert(tmp);
    }
{right_curle_bracket} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION" , "RIGHT_CURLY_BRACE","enumerated");
        insert(tmp);
    }
{left_bracket} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION" , "LEFT_BRACE","enumerated");
        insert(tmp);
    }
{right_bracket} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION" , "RIGHT_BRACE","enumerated");
        insert(tmp);
    }
{left_parenthesis} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION" , "LEFT_PARENTHESIS","enumerated");
        insert(tmp);
    }
{right_parenthesis} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION" , "RIGHT_PARENTHESIS","enumerated");
        insert(tmp);
    }
{semicolon} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION" , "SEMI_COLON","enumerated");
        insert(tmp);
    }
{comma} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION" , "COMMA","enumerated");
        insert(tmp);
    }
{colon} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION" , "COLON","enumerated");
        insert(tmp);
    }
{double_colons} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION" , "DOUBLE_COLONS","enumerated");
        insert(tmp);
    }
{dot} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION" , "DOT","enumerated");
        insert(tmp);
    }
{double_dots} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "PUNCTUATION" , "DOUBLE_DOTS","enumerated");
        insert(tmp);
    }

{id} {token* tmp = createNewNode(yylineno , token_counter++ , yytext , "ID" ,yytext ,"char*");
        insert(tmp);
    }

{other} {
        red();

        fprintf(stderr , "UNDEFINED CHARACTER");
        token* tmp = createNewNode(yylineno , token_counter++ , yytext , "UNDEFINED_TOKEN","","enumerated");
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
