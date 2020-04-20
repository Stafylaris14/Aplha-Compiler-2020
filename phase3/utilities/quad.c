#include "quad.h"
#include "../dataStructs/linkedList.h"
#include <assert.h>
#define STARTING_SIZE 1024

#define EXTEND 1024
#define CURR_SIZE (total * sizeof(quad))
#define NEW_SIZE (STARTING_SIZE * sizeof(quad) + CURR_SIZE)

#define NULL_NUM 0
#define NULL_BOOL 2
#define NULL_STR NULL

extern int yylineno;
extern int scopeCounter;

quad *quads = (quad *)0;
unsigned int total = 0;
unsigned int currQuad = 0;
int tmp_count = 0;

void init_quads()
{
    currQuad = 0;
    quads = malloc(sizeof(quad) * STARTING_SIZE);
    total = STARTING_SIZE;
    int i;
    for (i = 0; i < STARTING_SIZE; i++)
    {
        /* quads[i].label = 0; */
        quads[i].arg1 = NULL;
        quads[i].arg2 = NULL;
        quads[i].label = -1;
        quads[i].op = -1;
        quads[i].result = NULL;
    }
}

void extend_quads()
{
    assert(total == currQuad);
    quad *p = malloc(NEW_SIZE);
    if (quads)
    {
        memcpy(p, quads, CURR_SIZE);
        free(quads);
    }
    quads = p;
    total += EXTEND;
}

void print_quads()
{
    cyn();
    printf("quad#\t opcode\t result \t arg1 \t arg2 \t label \n");
    printf("-------------------------------------------------------------------------\n");

    int i;
    for (i = 0; i < total; i++)
    {

        /* printf("%d:\t %s\t %s\t %s\t %s\t %d  \n", i, quads[i].op, quads[i].result->); */
    }
}

void print_quads_not_empty()
{
    int i = 0;
    for (i = 0; i < total; i++)
    {
        if (quads[i].arg1 != NULL)
            printf("%d (%d)\n", quads[i].label, i);
    }
}

quad newQuad(iopcode op, expr *arg1, expr *arg2, expr *res)
{
    quad tmp;
    tmp.op = op;
    tmp.arg1 = arg1;
    tmp.arg2 = arg2;
    tmp.result = res;
    tmp.lineno = yylineno;
    /* kati gia to label */
    return tmp;
}

void emit(iopcode op, expr *arg1, expr *arg2, expr *res)
{
    /* ean den ftanei o xwros kanei extend */
    if (currQuad >= total)
        extend_quads();
    /* create a new Quad */
    quad tmp = newQuad(op, arg1, arg2, res);
    /* add it to array */
    quads[currQuad] = tmp;
    /* increse currQuad with 1 */
    currQuad = currQuad + 1;

    printf("op  %s\n", get_opcode_string(op));
}

item *tmp_item()
{
    item *tmp = malloc(sizeof(item));
    char *str = malloc(35 + tmp_count);
    sprintf(str, "_t%d", tmp_count);
    tmp = newItem(str, "local Expression", scopeCounter, yylineno);
    tmp_count++;
    return tmp;
}

expr *new_expression(expr_t type)
{
    expr *tmp_expression = malloc(sizeof(expr));
    tmp_expression->type = type;
    

    return tmp_expression;
}

expr *switch_expression_type(expr *tmp_expression, void *value)
{
    switch (tmp_expression->type)
    {
    case constnum_:
        tmp_expression->numConst = (int)value;
        tmp_expression->boolConst = NULL_BOOL;
        tmp_expression->stringConst = NULL_STR;
        break;
    case constbool_:
        tmp_expression->numConst = NULL_NUM;
        tmp_expression->stringConst = NULL_STR;
        tmp_expression->boolConst = NULL_BOOL;
        break;
    case conststring_:
        tmp_expression->numConst = NULL_NUM;
        tmp_expression->stringConst = (char *)value;
        tmp_expression->boolConst = NULL_BOOL;
        break;
    case var_:
        tmp_expression->numConst = NULL_NUM;
        tmp_expression->stringConst = NULL_STR;
        tmp_expression->boolConst = NULL_BOOL;
        break;
    case tableitem_:
        tmp_expression->numConst = NULL_NUM;
        tmp_expression->stringConst = NULL_STR;
        tmp_expression->boolConst = NULL_BOOL;
        break;
    case pfunc_:
        tmp_expression->numConst = NULL_NUM;
        tmp_expression->stringConst = NULL_STR;
        tmp_expression->boolConst = NULL_BOOL;
        break;
    case lfunc_:
        tmp_expression->numConst = NULL_NUM;
        tmp_expression->stringConst = NULL_STR;
        tmp_expression->boolConst = NULL_BOOL;
        break;
    case arthmexp_:
        tmp_expression->numConst = NULL_NUM;
        tmp_expression->stringConst = NULL_STR;
        tmp_expression->boolConst = NULL_BOOL;
        break;
    case assignexp_:
        tmp_expression->numConst = NULL_NUM;
        tmp_expression->stringConst = NULL_STR;
        tmp_expression->boolConst = NULL_BOOL;
        break;
    case newtable_:
        tmp_expression->numConst = NULL_NUM;
        tmp_expression->stringConst = NULL_STR;
        tmp_expression->boolConst = NULL_BOOL;
        break;
    case nill_:
        tmp_expression->numConst = NULL_NUM;
        tmp_expression->stringConst = NULL_STR;
        tmp_expression->boolConst = NULL_BOOL;
        break;
    default:
        break;
    }
    return tmp_expression;
}

char *get_opcode_expr_string(expr_t str)
{
    switch (str)
    {
    case constnum_:
        return "constnum_";
        break;
    case constbool_:
        return "constbool_";
        break;
    case conststring_:
        return "conststring_";
        break;
    case var_:
        return "var_";
        break;
    case tableitem_:
        return "tableitem_";
        break;
    case pfunc_:
        return "pfunc_";
        break;
    case lfunc_:
        return "lfunc_";
        break;
    case arthmexp_:
        return "arthmexp_";
        break;
    case assignexp_:
        return "assignexp_";
        break;
    case newtable_:
        return "newtable_";
        break;
    default:
        break;
    }
    return NULL;
}

char *get_opcode_string(iopcode op)
{
    switch (op)
    {
    case ASSIGN:
        return "ASSIGN";
        break;
    case ADD:
        return "ADD";
        break;
    case SUB:
        return "SUB";
        break;
    case MUL:
        return "MUL";
        break;
    case DIV:
        return "DIV";
        break;
    case MOD:
        return "MOD";
        break;
    case UMINUS:
        return "UMINUS";
        break;
    case AND:
        return "AND";
        break;
    case OR:
        return "OR";
        break;
    case NOT:
        return "NOT";
        break;
    case IF_EQ:
        return "IF_EQ";
        break;
    case IF_NOTEQ:
        return "IF_NOTEQ";
        break;
    case IF_LESSEQ:
        return "IF_LESSEQ";
        break;
    case IF_GREATEREQ:
        return "IF_GREATEREQ";
        break;
    case IF_LESS:
        return "IF_LESS";
        break;
    case IF_GREATER:
        return "IF_GREATER";
        break;
    case JUMP:
        return "JUMP";
        break;
    case CALL:
        return "CALL";
        break;
    case PARAM:
        return "PARAM";
        break;
    case RETURN:
        return "RETURN";
        break;
    case GETRETVAL:
        return "GETRETVAL";
        break;
    case FUNCSTART:
        return "FUNCSTART";
        break;
    case FUNCEND:
        return "FUNCEND";
        break;
    case TABLECREATE:
        return "TABLECREATE";
        break;
    case TABLEGETELEM:
        return "TABLEGETELEM";
        break;
    case TABLESETELEM:
        return "TABLESETELEM";
        break;
    default:
        exit(1);
        break;
    }
    return NULL;
}

/* 

int main()
{
    init_quads();
    expr *db1 = malloc(sizeof(expr));
    db1->next = NULL;
    db1->boolConst = 1;

    emit(ASSIGN, db1, db1, db1);
    print_quads_not_empty();
    printf("AFTER EXTENTION1---------\n");

    printf("%u \n", total);
    return 0;
}
 */