#include <stdio.h>
#include <stdlib.h>
/* #include "../dataStructs/sym.h" */
#include "parserUtilities.h"

/* tha ta valw me tin seira */
/* kapoia einai me kefalaio kai alla oxi giati to exoyme lousei me tis deilwseis */
typedef enum Iopcode
{
    ASSIGN,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    UMINUS,
    AND,
    OR,
    NOT,
    IF_EQ,
    IF_NOTEQ,
    IF_LESSEQ,
    IF_GREATEREQ,
    IF_LESS,
    IF_GREATER,
    JUMP,
    CALL,
    PARAM,
    RETURN,
    GETRETVAL,
    FUNCSTART,
    FUNCEND,
    TABLECREATE,
    TABLEGETELEM,
    TABLESETELEM
} iopcode;

//ti mporei na einai to expression
typedef enum expression_template
{
    constnum_,    /* Const number */
    constbool_,   /* const boolean */
    conststring_, /* const String*/

    var_,
    tableitem_, /* table item exprastion */

    pfunc_, /* program Function  */
    lfunc_, /* library Function */

    arthmexp_,  /* arithmetic expression */
    assignexp_, /* assign Expression */
    newtable_,  /* new Table expression */

    nill_
} expr_t;

typedef struct expression
{
    expr_t type;
    item *sym;
    struct expression *index;
    double numConst;
    char *stringConst;
    int boolConst;
    struct expression *next;
} expr;

typedef struct Quad
{
    /* enum  opcode  */
    iopcode op;
    expr *result;
    expr *arg1;
    expr *arg2;
    int label; /* ???????? */
    int lineno;
} quad;

void init_quads();

void extend_quads();

void print_quads();

void print_quads_not_empty();

quad newQuad(iopcode op, expr *arg1, expr *arg2, expr *res);

void emit(iopcode op, expr *arg1, expr *arg2, expr *res);

item *tmp_item();

expr *new_expression(expr_t type, item *Item, void *value);

expr *switch_expression_type(expr *tmp_expression, void *value);

char *get_opcode_string(iopcode op);

char *get_opcode_expr_string(expr_t str);

/* katse na doume */
expr *new_expr(expr_t e);