#include <stdio.h>
#include <stdlib.h>
#include "parserUtilities.h"



/* kapoia einai me kefalaio kai alla oxi giati to exoyme lousei me tis deilwseis */
typedef enum Iopcode {
    Assign , Mul , Uminus ,
    Not , if_lesseq , if_greater ,
    Ret ,  Funcend , Tablegetelem , 
    Add , Div ,And , if_eq , 
    if_greatereq , Call , Getretval , 
    Tablecreate , Tablesetelem ,
    Sub , Mod , Or,
    if_noteq , if_less , Param ,
     Funcstart
} iopcode;

typedef enum expression_template{
    var_ ,                                  
    tableitem_ ,                    /* table item exprastion */
    pfunc_ ,                        /* program Function  */
    lfunc_ ,                        /* library Function */
    arthmexp_ ,                     /* arithmetic expression */
    assignexp_ ,                    /* assign Expression */
    newtable_ ,                     /* new Table expression */
    constnum_ ,                     /* Const number */
    constbool_ ,                    /* const boolean */
    conststring_ ,                  /* const String*/
    nill_
}expr_t;


typedef struct expression {
    expr_t type;
    item* sym;
    struct expression* index;
    double numConst;
    char* stringConst;
    int boolConst;
    struct expression* next;
}expr;

typedef struct Quad{
    /* enum  opcode  */
    iopcode* op;
    expr* resault;
    expr* arg1;
    expr* arg2;
    int label;          /* ???????? */
    int lineno;
}quad;