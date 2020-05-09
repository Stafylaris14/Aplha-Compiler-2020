%{

#include "utilities/quad.h"
#include "dataStructs/linkedList.h"
#include "dataStructs/commentStack.h"





int yyerror(char *yaccProvideMessage);
int yylex(void);
int offset = 0;
int scopeCounter = 0;
int formal_flag  =0 ;
extern int yylineno;
int returnFlag = 0;
extern char* yytext;
extern FILE* yyin;
int functionCounter = 0; /* for no name functions */
int functionFlag  = 0;  /*1 if is inside a function for RETURN stmt*/
int callFlag =0; // an exw call
int objectHide = 1;//na min kanei hide an einai se object
int assign_flag = 0;
stack1 *loopcounterstack; //krataei poses anakikloseis exoun anoi3ei
/* iopcode op; */



expr *result;


int loopFlag = 0;       /*1 if its inside a loop (for break and Continue)*/
int libcheck = 0;
char* functionName ; /* used to ADD formal arguments to linked list */
%}



%union{
    struct expression* EXPR;
    int intVal;
    char* strVal;
    double doubleVal;
    struct Item *item; 
    int opcode;                         /* gia ta arithimika  STAF */
    int ifs;                            /* gia ta sigritika einai ayto STAF */
    int boolop ;                         /* gia ta boolean STAF */
    int label_jumps;                       /* gia ta jumps */
    struct for_call *for_call;
    struct for_init *for_init;
    struct indexstr *indexstr;
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

%right assign
%left or
%left and
%nonassoc equal n_equal
%nonassoc greater g_equal less l_equal
%left plus minus
%left multiply division mod
%right not plus_plus minus_minus uminus
%left  double_dots dot
%left left_bracket right_bracket
%left left_parenthesis right_parenthesis


%type <EXPR> Expression
%type <EXPR> Assignexpression
%type <EXPR> Elist Block Funcbody
%type <EXPR> Call Stmts 
%type <EXPR> Term   Multy_exp Ifstmt Forstmt
%type <EXPR> Lvalue Primary Objectdef Const Member Stmt
%type <item> Funcdef
%type <item> Funcprefix
%type <strVal> Funcname
%type <label_jumps> Whilestart
%type <EXPR> Whilestmt  Returnstmt
%type <label_jumps> whilecont M N 
%type <label_jumps> elseFix ifFix
%type <for_call> Methodcall
%type <for_call> Callsuffix
%type <for_call> Normalcall
%type <for_init> ForFix
%type <indexstr> Indexed Indexedelement Multy_ind



%%

program: States 
    ;

States: States Stmt {;}
    |
    ;


Stmts:Stmts Stmt {
        
        $$ = $2;
        $$->breaklist = mergelist($1->breaklist,$2->breaklist);
        $$->contlist = mergelist($1->contlist,$2->contlist);
        $$->returnlist = mergelist($1->returnlist,$2->returnlist);
} 
| {$$ = malloc(sizeof(expr));}
;

Stmt: Expression semicolon {
        libcheck =0;
        if(assign_flag ==1){
        emit(ASSIGN,newexpr_constbool(1),NULL,$1,-1);
        emit(JUMP,NULL,NULL,NULL,nextquad() +3);
        emit(ASSIGN,newexpr_constbool(0),NULL,$1,-1);
        backpatch($1->truelist, nextquad()-2);
        backpatch($1->falselist, nextquad());
        assign_flag = 0;
        }else if(assign_flag ==2){
                backpatch($1->truelist, nextquad()-2);
                backpatch($1->falselist, nextquad());
                assign_flag = 0;
        }
        $$ = $1;
    } 
    | Ifstmt {$$ = $1;}
    | Whilestmt {$$ = $1;}
    | Forstmt {$$ = $1;}
    | Returnstmt {
            $$ = $1;
            if(functionFlag == 0)error("no function to return" , yylineno);
            }
    | Break semicolon {
            libcheck =0;
            $$ = malloc(sizeof(expr));
            if(loopFlag == 0)error("no loop to break" , yylineno);
            $$->breaklist = new_list(nextquad());
            emit(JUMP,NULL,NULL,NULL,-1);
            }
    | Continue semicolon {
            libcheck =0;
            $$ = malloc(sizeof(expr));
            if(loopFlag == 0)error("no loop to Continue" , yylineno);
            $$->contlist = new_list(nextquad());
            emit(JUMP,NULL,NULL,NULL,-1);
            }
    | Block {$$ = $1;}
    | Funcdef {$$=  malloc(sizeof(expr));}
    | semicolon {libcheck =0;$$ = malloc(sizeof(expr));}
    ;




Expression: Assignexpression {$$ = $1;}
            | Expression plus Expression {                     
                $$ = new_expression(arthmexp_ );  
                $$->sym = tmp_item();
                emit(ADD , $1 , $3 , $$ , -1);}
            | Expression minus Expression {
                $$ = new_expression(arthmexp_ );  
                $$->sym = tmp_item();
                emit(SUB , $1 , $3 , $$ , -1);
            }
            | Expression multiply Expression {              
                $$ = new_expression(arthmexp_ );  
                $$->sym = tmp_item();
                emit(MUL , $1 , $3 , $$ , -1);}
            | Expression division Expression {
                $$ = new_expression(arthmexp_ );  
                $$->sym = tmp_item();
                emit(DIV , $1 , $3 , $$ , -1);}
            |Expression and  {if($1->type != boolexpr_ ) {
                emit(IF_EQ , $1 , newexpr_constbool(1) , NULL , -1);
                emit(JUMP,NULL,NULL,NULL,-1);
                printf("pro %d\n",nextquad()-2);
                $1->truelist = new_list(nextquad()-2);
                $1->falselist = new_list(nextquad()-1);
        }} M Expression {
                $$  =  new_expression(boolexpr_ );
                $$->sym = tmp_item();
                if($5->type != boolexpr_ ){
                    emit(IF_EQ , $5 , newexpr_constbool(1) , NULL, -1);
                    emit(JUMP,NULL,NULL,NULL,-1);
                    $5->truelist = new_list(nextquad()-2);
                    $5->falselist = new_list(nextquad()-1);
                    printf("de %d\n",nextquad()-2);
                }
                printf("se gamaw\n");
                backpatch($1->truelist, $4+1); // + 1 einai to swsto mallon
                $$->truelist = $5->truelist;
                $$->falselist = mergelist($1->falselist,$5->falselist);
                if(assign_flag !=2)
                assign_flag = 1;

            }       
            | Expression or  {if($1->type != boolexpr_ ) {
                emit(IF_EQ , $1 , newexpr_constbool(1) , NULL , -1);
                emit(JUMP,NULL,NULL,NULL,-1);
                printf("pro %d\n",nextquad()-2);
                $1->truelist = new_list(nextquad()-2);
                $1->falselist = new_list(nextquad()-1);
        }}  M Expression {
                $$  =  new_expression(boolexpr_ );
                $$->sym = tmp_item();
                if($5->type != boolexpr_ ){
                    emit(IF_EQ , $5 , newexpr_constbool(1) , NULL, -1);
                    emit(JUMP,NULL,NULL,NULL,-1);
                    $5->truelist = new_list(nextquad()-2);
                    $5->falselist = new_list(nextquad()-1);
                    printf("de %d\n",nextquad()-2);
                }
                printf("den se\n");
                backpatch($1->falselist,$4+1);
                $$->truelist = mergelist($1->truelist, $5->truelist);
                $$->falselist = $5->falselist;
                 if(assign_flag !=2)
                assign_flag = 1;           
                }
            | Expression mod Expression {
                 $$ = new_expression(arthmexp_ );  
                $$->sym = tmp_item();
                emit(MOD , $1 , $3 , $$ , -1);}
            | Expression equal Expression {
                $$ = new_expression(boolexpr_);
                $$->sym = tmp_item();
                emit(IF_EQ , $1 , $3 ,NULL , -1);
                emit(JUMP,NULL,NULL,NULL,-1);
                $$->truelist = new_list(nextquad()-2);
                $$->falselist = new_list(nextquad()-1);
                assign_flag = 1; 
                    }
            | Expression n_equal Expression {
                $$ = new_expression(boolexpr_);
                $$->sym = tmp_item();
                emit(IF_NOTEQ , $1 , $3 ,NULL , -1);
                emit(JUMP,NULL,NULL,NULL,-1);
                $$->truelist = new_list(nextquad()-2);
                $$->falselist = new_list(nextquad()-1);
                assign_flag = 1; 
            }
            | Expression greater Expression {
                $$ = new_expression(boolexpr_);
                $$->sym = tmp_item();
                emit(IF_GREATER , $1 , $3 ,NULL , -1);
                emit(JUMP,NULL,NULL,NULL,-1);
                $$->truelist = new_list(nextquad()-2);
                $$->falselist = new_list(nextquad()-1);
                assign_flag = 1;     
                    }
            | Expression less Expression {
                $$ = new_expression(boolexpr_);
                $$->sym = tmp_item();
                emit(IF_LESS , $1 , $3 ,NULL , -1);
                emit(JUMP,NULL,NULL,NULL,-1);
                $$->truelist = new_list(nextquad()-2);
                $$->falselist = new_list(nextquad()-1);
                printf("lessss\n");
                assign_flag = 1; 
            }
            | Expression g_equal Expression {
                $$ = new_expression(boolexpr_);
                $$->sym = tmp_item();
                emit(IF_GREATEREQ , $1 , $3 ,NULL , -1);
                emit(JUMP,NULL,NULL,NULL,-1);
                $$->truelist = new_list(nextquad()-2);
                $$->falselist = new_list(nextquad()-1);
                assign_flag = 1; 
            }
            | Expression l_equal Expression {
                $$ = new_expression(boolexpr_);
                $$->sym = tmp_item();
                emit(IF_LESSEQ , $1 , $3 ,NULL , -1);
                emit(JUMP,NULL,NULL,NULL,-1);
                $$->truelist = new_list(nextquad()-2);
                $$->falselist = new_list(nextquad()-1);
                assign_flag = 1;               
            }
            | Term {$$ = $1;}
             ;





Term:   left_parenthesis Expression right_parenthesis {$$ = $2;}
        | minus Expression %prec uminus {
                check_arith($2,"uminus");
                $$ = newexpr(arthmexp_);
                $$->sym = istempexpr($2) ? $2->sym: tmp_item();
                emit(UMINUS,$2,NULL,$$,-1);
        }
        | not Expression {
                $$ = newexpr(boolexpr_); 
                $$->sym = tmp_item();
                emit(IF_EQ,$2,newexpr_constbool(1),NULL,nextquad()+5);
                emit(JUMP,NULL,NULL,NULL,nextquad()+2);
                printf("not tru %d kai false %d\n",nextquad()-1,nextquad()-2);
                 $$->truelist = new_list(nextquad()-1);
                 $$->falselist = new_list(nextquad()-2);
                if($2->type != boolexpr_ )printf("booleeen notttt\n");
                emit(ASSIGN,newexpr_constbool(1),NULL,$$ , -1);
                emit(JUMP,NULL,NULL,NULL , nextquad() + 3);
                emit(ASSIGN,newexpr_constbool(0),NULL,$$ , -1); 
                backpatch($2->truelist, nextquad() -2);
                backpatch($2->falselist, nextquad());
                                

                assign_flag = 2;
        }
        | plus_plus Lvalue {
                if(libcheck == 1){
                        error("Den boreis na kaneis pra3eis me synartiseis", yylineno); 
                        libcheck=0;
                }
                check_arith($2,"++ lvalue");
                if($2->type == tableitem_){


                         $$ = newexpr(var_);
                         $$->sym = tmp_item();
                         emit(TABLEGETELEM, $2, $2->index, $$, -1);

                        emit(ADD,$$,newexpr_constnum(1),$$,-1);
                        emit(TABLESETELEM,$2->index,$$,$2,-1);
                }else{
                        emit(ADD,$2,newexpr_constnum(1),$2,-1);
                        $$ = newexpr(arthmexp_);
                        $$->sym = tmp_item();
                        emit(ASSIGN,$2,NULL,$$,-1);
                }
                        
        }
        | Lvalue plus_plus {
                if(libcheck == 1){
                error("Den boreis na kaneis pra3eis me synartiseis", yylineno); 
                libcheck=0;}
                check_arith($1,"lvalue ++");
                $$ = newexpr(boolexpr_); 
                $$->sym = tmp_item();
                if($1->type==tableitem_){

                        expr *val = newexpr(var_);
                        val->sym = tmp_item();
                        emit(TABLEGETELEM, $1, $1->index, val, -1);

                        emit(ASSIGN,val,NULL,$$,-1);
                        emit(ADD,val,newexpr_constnum(1),val , -1);
                        emit(TABLESETELEM,$1->index,val,$1 , -1);
                       // $$= val;

                }else{
                        emit(ASSIGN,$1,NULL,$$,-1);
                        emit(ADD,$1,newexpr_constnum(1),$1,-1);
                        //$$ = $1;
                }

        }
        | minus_minus Lvalue {
                if(libcheck == 1){
                        error("Den boreis na kaneis pra3eis me synartiseis", yylineno); 
                        libcheck=0;
                        }
                check_arith($2,"-- lvalue");
                if($2->type == tableitem_){

                        $$ = newexpr(var_);
                        $$->sym = tmp_item();
                        emit(TABLEGETELEM, $2, $2->index, $$, -1);


                        emit(SUB,$$,newexpr_constnum(1),$$ ,-1);
                        emit(TABLESETELEM,$2->index,$$,$2 , -1);
                }else{
                        emit(SUB,$2,newexpr_constnum(1),$2 , -1);
                        $$ = newexpr(arthmexp_);
                        $$->sym = tmp_item();
                        emit(ASSIGN,$2,NULL,$$ , -1);
                }
                
        }
        | Lvalue minus_minus {
                if(libcheck == 1){
                        error("Den boreis na kaneis pra3eis me synartiseis", yylineno);
                        libcheck=0;
                }
              check_arith($1,"lvalue --");
                $$ = newexpr(boolexpr_); 
                $$->sym = tmp_item();
                if($1->type==tableitem_){
                        expr *val = newexpr(var_);
                        val->sym = tmp_item();
                        emit(TABLEGETELEM, $1, $1->index, val, -1);

                        emit(ASSIGN,val,NULL,$$,-1);
                        emit(SUB,val,newexpr_constnum(1),val , -1);
                        emit(TABLESETELEM,$1->index,val,$1 , -1);
                       // $$= val;
                }else{
                        emit(ASSIGN,$1,NULL,$$ , -1);
                        emit(SUB,$1,newexpr_constnum(1),$1 ,-1);
                       // $$ = $1;
                }
                
        }
        | Primary {$$ = $1;}
        ;

Assignexpression: Lvalue {if(libcheck == 1){error("Den boreis na kaneis pra3eis me synartiseis", yylineno); libcheck=0;}} assign Expression {
        
                if($1->type == tableitem_){ 
                        emit(TABLESETELEM, $1->index,$4 , $1 , -1);
                        $$ = emit_iftableitem($1);
                        $$->type = assignexp_;
                }else{
                        $$ = newexpr(assignexp_);
                        $$->sym = tmp_item();
                        if($4->type == boolexpr_){
                        if(assign_flag==1){
                                emit(ASSIGN,newexpr_constbool(1),NULL,$$ , -1);
                                emit(JUMP,NULL,NULL,NULL , nextquad() + 3);
                                emit(ASSIGN,newexpr_constbool(0),NULL,$$ , -1); 
                                printf("ti leeee\n");
                                backpatch($4->truelist, nextquad() -2);
                                backpatch($4->falselist, nextquad());
                                assign_flag = 0;
                        }else if(assign_flag==2){
                                backpatch($4->truelist, nextquad() -2);
                                backpatch($4->falselist, nextquad());

                        }
                        }
                        emit(ASSIGN,$4,NULL,$1 , -1);
                        emit(ASSIGN,$1,NULL,$$ , -1);
                        
                }    

                }
                ;




Primary: Lvalue {$$ = emit_iftableitem($1);}
        | Call {callFlag =1; $$ = $1;}
        | Objectdef {$$ = $1;}
        | left_parenthesis Funcdef right_parenthesis {
                $$=newexpr(pfunc_);
                $$->sym = $2;
        }
        | Const {$$ = $1;}
        ;




Lvalue: id {   
                                if(isLibraryFunction($1)){libcheck =1;}
                                if(isFA($1))libcheck =1;
                                item* new;
                                if(scopeCounter == 0){new = newItem($1,"global variable", scopeCounter , yylineno);new_check(new); }
                                else {new = newItem($1,"local variable", scopeCounter , yylineno );new_check(new);}
                                $$ = lvalue_expr(new);
                                 

        }
        | local id {
                                if(isLibraryFunction($2))libcheck =1;
                              //  if(isFA($2))libcheck =1;
                                item* new = NULL;
                                new = newItem($2,"local", scopeCounter , yylineno );
                                new_check(new);
                                $$ = lvalue_expr(new);
        }
        | double_colons id {
                                if(isFA($2))libcheck =1;
                                item* tmp = lookupScope($2 , 0);
                                if(tmp == NULL){error("Cant find Global " , yylineno);} 
                                $$ = lvalue_expr(tmp);               
        }
        | Member {$$ = $1;};
        ;


Member: Lvalue dot id {libcheck = 0;
            $$ = member_item($1,$3);    
        }
        | Lvalue left_bracket Expression right_bracket {
                libcheck = 0;
                $1 = emit_iftableitem($1);
                $$ = newexpr(tableitem_);
                $$->sym = $1->sym;
                $$->index = $3;
                }
        | Call {callFlag =1;libcheck =0;} dot id {callFlag =0;libcheck = 0;printf("emaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");}
        | Call {callFlag =1;libcheck=0;} left_bracket Expression right_bracket {callFlag =0;libcheck = 0;printf("emaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");}
        ;


Call: Call {callFlag =1;libcheck = 0;} left_parenthesis Elist right_parenthesis {$$=make_call($1,$4);callFlag =0;}
        |  Lvalue {callFlag =1;libcheck = 0;} Callsuffix {
                if($3->method){
                        expr* t = $1;
                        $1 = emit_iftableitem(member_item(t,$3->name));
                        $3->elist->next = t;
                }         
                $$ = make_call($1,$3->elist);
                callFlag =0;}
        | left_parenthesis Funcdef right_parenthesis {callFlag =1;libcheck = 0;} left_parenthesis Elist right_parenthesis {
                expr* func = newexpr(pfunc_);
                func->sym = $2;
                $$ = make_call(func,$6);
                callFlag =0;}
        ;



Callsuffix: Normalcall {
                callFlag =1; 
                $$ = $1;
        }
            | Methodcall {
                callFlag =1;
                $$ = $1;
        }
            ;

Normalcall: left_parenthesis {callFlag =1;} Elist right_parenthesis {
        $$ = insert_call($3,0,NULL);
        }
        ;



Methodcall: double_dots {callFlag =1;} id left_parenthesis Elist right_parenthesis {
                $$ = insert_call($5,1,$3);
        }
        ;



Elist:  Expression Multy_exp {
                $1->next = $2;
                $$ = $1;  
        }
        | {$$ = NULL;}
        ;

Multy_exp: comma Expression Multy_exp {
                 $2->next = $3;
                 $$ = $2;
        }
        | {$$ = NULL;}
        ;

Objectdef: left_bracket {scopeCounter--;objectHide =0;} Elist right_bracket {
        scopeCounter++;
        objectHide=1;
        expr *t = newexpr(newtable_);
        t->sym = tmp_item();
        emit(TABLECREATE,t,NULL,NULL,-1);
        int i = 0;
        while($3){
                emit(TABLESETELEM, newexpr_constnum(i++),$3, t,-1);
                $3 = $3->next;
        }
        $$ = t;
        }
        | left_bracket {scopeCounter--;objectHide =0;} Indexed right_bracket {
                scopeCounter++;
                objectHide=1;
                expr *t = newexpr(newtable_);
                t->sym = tmp_item();
                emit(TABLECREATE,t,NULL,NULL,-1);
                while($3){
                        emit(TABLESETELEM, $3->ena,$3->dio,t,-1);
                        
                        
                        $3 = $3->next;
                }     
                $$ = t;  
        }
        ;


Indexed: Indexedelement Multy_ind {
                 $1->next=$2;
                 $$ = $1;
        }
         ;

Multy_ind:  comma Indexedelement Multy_ind  {
                // if($3 == NULL){
                //         cyn();
                //         $1 = malloc(sizeof(indexstr));
                //         $1 = $3;
                // }else{
                //      red();
                //      $1->next = $3;  
                // }
                
                $2->next = $3;
                $$ = $2;}
        | {$$= NULL;}
         ;

Indexedelement: left_curle_bracket {scopeCounter++;
                if(scopeCounter > maxScope) maxScope = scopeCounter;}
                Expression colon Expression right_curle_bracket {       
                        if(objectHide)hide(scopeCounter);
                        scopeCounter--;
                        $$ = malloc(sizeof(indexstr));
                        $$->ena = $3;
                        $$->dio = $5;
                        $$->next = NULL;
                 }
                ;


Block: left_curle_bracket {scopeCounter++;
        if(scopeCounter > maxScope) maxScope = scopeCounter;}
        Stmts right_curle_bracket {
                if(objectHide)hide(scopeCounter);
                scopeCounter--;
                if($3 == NULL)printf("gameeee\n");
                $$ = $3;
                }
        ;


Funcdef: Funcprefix  Funcargs Funcblockstart Funcbody Funcblockend {

        backpatch($4->returnlist, nextquad()+1);
        expr*temp = newexpr(pfunc_);
        temp->sym = $1;
        emit(FUNCEND,temp,NULL,NULL,-1);
        patchlabel($1->jump,nextquad()+1);
        $$ = $1;
        }
        ;

Funcprefix: Function Funcname{
        item* new = newItem($2,"User Function", scopeCounter , yylineno );
        new_check(new);
        expr*temp = newexpr(pfunc_);
        temp->sym = new;
        emit(JUMP,NULL,NULL,NULL,-1);
        emit(FUNCSTART,temp,NULL,NULL,-1);
        functionName = strdup($2);
        offset =0;
        new->jump = nextquad()-2;
        $$ = new;
}
;

Funcname: id {
                $$ = $1;
        }
        | {
                char noname[20];
                sprintf(noname,"function$%d",functionCounter);
                functionCounter++;
                $$ = noname;
        }
;

Funcargs: left_parenthesis {scopeCounter++;} Idlist  right_parenthesis {offset = 0;scopeCounter--;functionFlag++; }
        ;

Funcbody: Block {
        $$=$1;
        functionFlag --;getoffset();
        }
        ;

Funcblockstart: {push1(loopcounterstack, loopFlag); loopFlag = 0;}        
        ;

Funcblockend: {
        loopFlag = pop1(loopcounterstack);}
        ;

Const:  integer {$$ = newexpr_constint($1);
        }
        | real {$$ = newexpr_constnum($1);}
        | string {$$ = newexpr_constring($1);}
        | nil {$$ = newexpr(nill_);}
        | True {$$ = newexpr_constbool(1);}
        | False {$$ = newexpr_constbool(0);}
        ;



Idlist: id Multy_id {
        
                item* new = newItem($1,"formal argument", scopeCounter , yylineno );
                    formal_flag = 1;
                    new_check(new);
                    insert_formal_arg(functionName , $1);
                    formal_flag = 0;
                    
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




Ifstmt: ifFix Stmt {
               
                patchlabel($1-1 , nextquad()+1);
                $$ = $2;
        }
        | ifFix Stmt elseFix Stmt {
                patchlabel($1 -1 , $3+2);
                patchlabel($3 , nextquad()+1);
                $$ = $2;
                //kati 8elei gia brek/co nti
        }
        ;

ifFix: If left_parenthesis Expression right_parenthesis{
                if($3->type== boolexpr_){
                emit(ASSIGN,newexpr_constbool(1),NULL,$3,-1);
                emit(JUMP,NULL,NULL,NULL,nextquad() +3);
                emit(ASSIGN,newexpr_constbool(0),NULL,$3,-1);
                assign_flag =0 ;
                backpatch($3->truelist, nextquad()-2);
                backpatch($3->falselist, nextquad());
                }else{
                        backpatch($3->truelist, nextquad()+1);
                        backpatch($3->falselist, nextquad()+3);    
                } 
                emit(IF_EQ , $3 , new_expr_constbool(1) ,NULL, nextquad() +3);
                emit(JUMP , NULL , NULL , NULL , -1);
              
                $$ = nextquad();
};

elseFix: Else {
        $$ = nextquad();                                        /* STAF */
        emit(JUMP , NULL , NULL ,NULL, -1);
}
;

Whilestart: While {
        $$ = nextquad();
}
;

whilecont: left_parenthesis Expression right_parenthesis {
       //
        if($2->type== boolexpr_){ 
        if(assign_flag != 2){       
        emit(ASSIGN,newexpr_constbool(1),NULL,$2,-1);
        emit(JUMP,NULL,NULL,NULL,nextquad()+3);
        emit(ASSIGN,newexpr_constbool(0),NULL,$2,-1);
        backpatch($2->truelist, nextquad()-2);
        backpatch($2->falselist, nextquad());
        assign_flag = 0;
        }
                red();
        printf("prepei na dw\n");
        wht();
        }


        //
        emit(IF_EQ , $2 , new_expr_constbool(1) , NULL , nextquad()+3);
        emit(JUMP , NULL , NULL , NULL , -1);
        $$ = nextquad();
}
;

Whilestmt: Whilestart whilecont {loopFlag ++;} Stmt {
                loopFlag--;
                
                emit(JUMP , NULL , NULL , NULL,$1+1);         
                patchlabel($2 -1, nextquad()+1);

                backpatch($4->breaklist, nextquad()+1); 
                backpatch($4->contlist,$1+ 1);
                $$=$4;
                $$->breaklist = NULL;
                $$->contlist = NULL;
        }
    ;

Forstmt: ForFix N Elist right_parenthesis {loopFlag ++;} N Stmt N {
        loopFlag --;
        
        patchlabel($1->enter,$6+2);
        patchlabel($2,nextquad()+1);
        patchlabel($6,$1->test+1);
        patchlabel($8,$2+2);
        
        backpatch($7->breaklist,nextquad()+1);
        backpatch($7->contlist,$2+2);
        
        $$ = $7;
        $$->breaklist = NULL;
        $$->contlist = NULL;
}
        ;

ForFix: For left_parenthesis Elist semicolon M Expression semicolon {
        backpatch($6->truelist, nextquad()+1);
        backpatch($6->falselist, nextquad()+3);
        if($6->type == boolexpr_){  
                emit(ASSIGN,newexpr_constbool(1),NULL,$6,-1);
                emit(JUMP,NULL,NULL,NULL,nextquad()+3);
                emit(ASSIGN,newexpr_constbool(0),NULL,$6,-1);
                assign_flag = 0;
        }
        $$ = malloc(sizeof(for_init));
        $$->test = $5;
        $$->enter = nextquad();
        emit(IF_EQ,$6,newexpr_constbool(1),NULL,-1);
}
;

M:{
        $$ = nextquad();
};

N:{
        $$ = nextquad();
         emit(JUMP,NULL,NULL,NULL,-1);
};

Returnstmt: Return semicolon {libcheck =0;
         emit(RETURN, NULL, NULL, NULL, -1);
         emit(JUMP,NULL,NULL,NULL,-1);
         $$ = malloc(sizeof(expr));
         $$->returnlist = new_list(nextquad()-1);
        }
        | Return {returnFlag = 1; 
        } Expression semicolon {libcheck =0;
        returnFlag =0; 
        emit(RETURN, $3, NULL, NULL, -1);
        emit(JUMP,NULL,NULL,NULL,-1);
        $$= $3;
        $$->returnlist = new_list(nextquad()-1);
        }
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
    loopcounterstack = arxikopoisi();
    yyparse();
    //printSymTable();
    //printHash();
    //printScopeList();
    
    print_quads();
   
}
