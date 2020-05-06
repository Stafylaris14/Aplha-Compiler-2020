#include <stdio.h>
#include <stdlib.h>
/* #include "../dataStructs/sym.h" */
#include "parserUtilities.h"

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
    boolexpr_,
    arthmexp_,  /* arithmetic expression */
    assignexp_, /* assign Expression */
    newtable_,  /* new Table expression */

    nill_
} expr_t;

typedef struct zavolist
{
    int label;
    struct zavolist *next;
} zavo;

typedef struct expression
{
    expr_t type;
    item *sym;
    struct expression *index;
    int numConst;
    char *stringConst;
    int boolConst;
    zavo *breaklist;
    zavo *contlist;
    zavo *falselist;
    zavo *truelist;
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

typedef struct for_call
{
    expr *elist;
    unsigned char method;
    char *name;
} for_call;

typedef struct for_init
{
    int test;
    int enter;
} for_init;

typedef struct stack1
{
    int top;
    int maxsize;
    int *stackarray;
} stack1;

typedef struct indexstr{
    expr *ena;
    expr *dio;
    struct indexstr *next;
}indexstr;

void init_quads();

void extend_quads();

void print_quads();

void print_quads_not_empty();

quad newQuad(iopcode op, expr *arg1, expr *arg2, expr *res);

void emit(iopcode op, expr *arg1, expr *arg2, expr *res, int label);

item *tmp_item();

expr *new_expression(expr_t type);

expr *switch_expression_type(expr *tmp_expression, void *value);

char *get_opcode_string(iopcode op);

char *get_opcode_expr_string(expr_t str);

expr *new_expr_constbool(int boolean);

void patchlabel(int quadNo, int label); /* apo oti katalaba einai apla gia na to vazei sto quad to sugkekrimeno label */

int nextquad(); /* epistrefei to epomeno quad (jumps) */

expr *make_call(expr *lv, expr *reversed_elist);

expr *newexpr(expr_t t);

expr *newexpr_constring(char *s);

expr *emit_iftableitem(expr *e);

expr *newexpr_constint(int i);

expr *member_item(expr *lv, char *name);

expr *lvalue_expr(item *sym);

expr *newexpr_constnum(int i);

void check_arith(expr *e, char *context);

void add_to_contlist(expr *e, int label);

void add_to_breaklist(expr *e, int label);

void add_to_truelist(expr *e, int label);

void add_to_falselist(expr *e, int label);

void backpatch(zavo *list, int label);

expr *newexpr_constbool(unsigned int b);

stack1 *arxikopoisi();

int isfull(stack1 *stiba);

int push1(stack1 *stiba, int data);

int pop1(stack1 *stiba);

for_call *insert_call(expr *elist, unsigned char method, char *name);

zavo *new_list(int i);

zavo *mergelist(zavo *first, zavo *second);

unsigned int istempname(char *s);

unsigned int istempexpr(expr *e);

