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

/* void print_quads()
{
    cyn();
    printf("quad#\t opcode\t result \t arg1 \t arg2 \t label \n");
    printf("-------------------------------------------------------------------------\n");

    int i;
    for (i = 0; i < total; i++)
    {

        
    }
} */

void print_quads()
{
    cyn();
    printf("-------------------------------------------------------------------------\n");
    /* 0-> normal arg | 1-> boolConst 2-> NumConst | 3-> StringConst */
    int flag = 0;
    int i;
    char *a1;
    char *a2;
    char *a3;
    for (i = 0; i < currQuad; i++)
    {
        if (quads != NULL)
        {
            a1 = malloc(sizeof(char) * 200);
            a2 = malloc(sizeof(char) * 200);
            a3 = malloc(sizeof(char) * 200);
            if (quads[i].arg1 != NULL)
            {
                 // printf("typee arg1 %d\n" ,quads[i].arg1->type);
                switch (quads[i].arg1->type)
                {
                case nill_:
                    a1 = "nill";
                    break;
                case newtable_:
                    a1 = "newTable";
                    break; /* den exw idea */
                case assignexp_:
                    a1 = quads[i].arg1->sym->name;
                    break;
                case arthmexp_:
                    //itoa(quads[i].arg1->numConst, a1 ,10 );
                    a1 = quads[i].arg1->sym->name;
                    break;
                case var_:
                    a1 = quads[i].arg1->sym->name;
                    break;
                case conststring_:
                    a1 = quads[i].arg1->stringConst;
                    break;
                case constbool_:
                    if (quads[i].arg1->boolConst == 1)
                        a1 = "TRUE";
                    else if (quads[i].arg1->boolConst == 0)
                        a1 = "FALSE";
                    else
                    {
                        red();
                        printf("den exei oristei to boolean\n");
                        wht();
                    }
                    break;
                case constnum_:
                    sprintf(a1, "%d", quads[i].arg1->numConst);
                    break;
                case pfunc_:
                    a1 = quads[i].arg1->sym->name;
                    break;
                case boolexpr_:
                    a1 = quads[i].arg1->sym->name;
                    break;
                case tableitem_:
                    a1 = quads[i].arg1->sym->name;
                    break;
                case lfunc_:
                    red();
                    printf("na to libb\n");
                    cyn();
                    break;
                default:
                    a1 = get_opcode_expr_string(quads[i].arg1->type);
                    break;
                }
               // printf("feugw arg1 %s\n" ,a1);
            }
            if (quads[i].arg2 != NULL)
            {
               // printf("typee a2 %d\n" ,quads[i].arg2->type);
                switch (quads[i].arg2->type)
                {
                case nill_:
                    a2 = "nill";
                    break;
                case newtable_:
                    a2 = "newTable";
                    break; /* den exw idea */
                case assignexp_:
                    a2 = quads[i].arg2->sym->name;
                    break;
                case arthmexp_:
                    //itoa(quads[i].arg2->numConst, a2 ,10 );
                    a2 = quads[i].arg2->sym->name;
                    break;
                case var_:
                    a2 = quads[i].arg2->sym->name;
                    break;
                case conststring_:
                    a2 = quads[i].arg2->stringConst;
                    break;
                case constbool_:
                    if (quads[i].arg2->boolConst == 1)
                        a2 = "TRUE";
                    else if (quads[i].arg2->boolConst == 0)
                        a2 = "FALSE";
                    else
                    {
                        red();
                        printf("den exei oristei to boolean\n");
                        wht();
                    }
                    break;
                case constnum_:
                    sprintf(a2, "%d", quads[i].arg2->numConst);
                    break;
                case pfunc_:
                    a2 = quads[i].arg2->sym->name;
                break;
                case boolexpr_:
                    a1 = quads[i].arg2->sym->name;
                    break;
                case tableitem_:
                    a2 = quads[i].arg2->sym->name;
                    break;
                case lfunc_:
                    red();
                    printf("na to libb\n");
                    cyn();
                    break;
                default:
                    a2 = get_opcode_expr_string(quads[i].arg2->type);
                    break;
                }
              //  printf("feugw arg2 %s\n" ,a2);
            }

            if (quads[i].result == NULL)
                a3 = "";
            else{
             //   printf("typee resy %d\n" ,quads[i].result->type);
                switch (quads[i].result->type)
                {
                case nill_:
                    a3= "nill";
                    break;
                case newtable_:
                    a3= "newTable";
                    break; /* den exw idea */
                case assignexp_:
                    a3 = quads[i].result->sym->name;
                    break;
                case arthmexp_:
                    //itoa(quads[i].arg2->numConst, a3,10 );
                    a3= quads[i].result->sym->name;
                    break;
                case var_:
                    a3= quads[i].result->sym->name;
                    break;
                case conststring_:
                    a3= quads[i].result->stringConst;
                    break;
                case constbool_:
                    if (quads[i].result->boolConst == 1)
                        a3= "TRUE";
                    else if (quads[i].result->boolConst == 0)
                        a3= "FALSE";
                    else
                    {
                        red();
                        printf("den exei oristei to boolean\n");
                        wht();
                    }
                    break;
                case constnum_:
                    sprintf(a3, "%d", quads[i].result->numConst);
                    break;
                case pfunc_:
                    a3= quads[i].result->sym->name;
                break;
                case boolexpr_:
                    a1 = quads[i].result->sym->name;
                    break;
                case tableitem_:
                    a3 = quads[i].result->sym->name;
                    break;
                case lfunc_:
                    red();
                    printf("na to libb\n");
                    cyn();
                    break;
                default:
                    a3= get_opcode_expr_string(quads[i].result->type);
                    break;
                }
               // printf("feugw res %s\n" ,a3);
            }
            
            if (quads[i].op == JUMP)
            {
                printf("%d: %s %d [line %d]\n",
                       i + 1,
                       get_opcode_string(quads[i].op),
                       quads[i].label,
                       quads[i].lineno);
            }
            else
            {
                if (quads[i].label < 0)
                {
                    printf("%d: %s %s %s %s [line %d]\n",
                           i + 1,
                           get_opcode_string(quads[i].op),
                           a3,
                           a1,
                           a2,
                           quads[i].lineno);
                }
                else
                {
                    printf("%d: %s %s %s %s %d [line %d] \n",
                           i + 1,
                           get_opcode_string(quads[i].op),
                           a3,
                           a1,
                           a2,
                           quads[i].label,
                           quads[i].lineno);
                }
            }
        }
    }
    wht();
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

void emit(iopcode op, expr *arg1, expr *arg2, expr *res, int label)
{
    /* ean den ftanei o xwros kanei extend */
    if (currQuad >= total)
        extend_quads();
    /* create a new Quad */
    quad tmp = newQuad(op, arg1, arg2, res);
    tmp.label = label;
    /* add it to array */
    quads[currQuad] = tmp;
    /* increse currQuad with 1 */
    currQuad = currQuad + 1;
}

item *tmp_item()
{
    item *tmp = malloc(sizeof(item));
    char *str = malloc(35 + tmp_count);
    sprintf(str, "^%d", tmp_count);
    tmp = newItem(str, "local Expression", scopeCounter, yylineno);
    tmp_count++;
    return tmp;
}

expr *new_expression(expr_t type)
{
    expr *tmp_expression = malloc(sizeof(expr));
    tmp_expression->type = type;
    /* init lists */
    // tmp_expression->truelist = NULL;
    // tmp_expression->falselist = NULL;
    // tmp_expression->contlist = NULL;
    // tmp_expression->breaklist = NULL;

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
        printf("exw =exi %d\n", op);
        exit(1);
        break;
    }
    return NULL;
}

expr *new_expr_constbool(int boolean)
{
    expr *tmp = new_expression(constbool_);
    tmp->boolConst = boolean;
    return tmp;
}

void patchlabel(int quadNo, int label)
{
    assert(quadNo < currQuad);
    quads[quadNo].label = label;
}

int nextquad()
{
    return currQuad;
}

expr *make_call(expr *lv, expr *reversed_elist)
{
    expr *func = emit_iftableitem(lv);
    while (reversed_elist)
    {
        emit(PARAM, reversed_elist, NULL, NULL, -1);
        reversed_elist = reversed_elist->next;
    }
    emit(CALL, func, NULL, NULL, -1);
    expr *result = newexpr(var_);
    result->sym = tmp_item();
    emit(GETRETVAL, result, NULL, NULL, -1);
    return result;
}

expr *newexpr(expr_t t)
{
    expr *e = (expr *)malloc(sizeof(expr));
    memset(e, 0, sizeof(expr));
    e->type = t;
    return e;
}

expr *newexpr_constring(char *s)
{ 
    
    expr *e = newexpr(conststring_);
    e->stringConst = strdup(s);
    return e;
}

expr *emit_iftableitem(expr *e)
{
    if (e->type != tableitem_)
        return e;
    else
    {
        expr *result = newexpr(var_);
        result->sym = tmp_item();
        emit(TABLEGETELEM, e, e->index, result, -1);
        return result;
    }
}

expr *newexpr_constint(int i)
{
    expr *e = newexpr(constnum_);
    // e->contlist = NULL;
    // e->breaklist = NULL;
    // e->falselist = NULL;
    // e->truelist = NULL;
    e->numConst = i;
    return e;
}

expr *member_item(expr *lv, char *name)
{
    lv = emit_iftableitem(lv);
    expr *ti = newexpr(tableitem_);
    // ti->contlist = NULL;
    // ti->breaklist = NULL;
    // ti->falselist = NULL;
    // ti->truelist = NULL;
    ti->sym = lv->sym;
    ti->index = newexpr_constring(name);
    return ti;
}

expr *lvalue_expr(item *sym)
{
    assert(sym);
    expr *e = (expr *)malloc(sizeof(expr));
    // e->contlist = NULL;
    // e->breaklist = NULL;
    // e->falselist = NULL;
    // e->truelist = NULL;
    memset(e, 0, sizeof(expr));
    e->next = (expr *)0;
    e->sym = sym;
    enum Scope_spase sp = get_scope_spase(sym);
    switch (sp)
    {
    case program_variable:
        e->type = var_;
        break;
    case function_local:
        e->type = pfunc_;
        break;
    case formal_argument:
        e->type = var_;
        break;
    default:
        e->type = lfunc_;
        assert(0);
    }
    return e;
}

expr *newexpr_constnum(int i)
{
    expr *e = newexpr(constnum_);
    e->numConst = i;
    return e;
}

void check_arith(expr *e, char *context)
{
    if (e->type == constbool_ ||
        e->type == conststring_ ||
        e->type == nill_ ||
        e->type == newtable_ ||
        e->type == pfunc_ ||
        e->type == lfunc_ ||
        e->type == boolexpr_)
    {
        printf("Illegal expr used in %s", context);
        exit(1);
    }
}

void add_to_contlist(expr *e, int label)
{
    zavo *head = e->contlist;

    if (head == NULL)
    {
        head->label = label;
        head->next = NULL;
    }
    else
    {
        zavo *tmp = head;
        while (tmp != NULL)
        {
            tmp = tmp->next;
        }
        tmp = malloc(sizeof(zavo));
        tmp->label = label;
        tmp->next = NULL;
    }
}

void add_to_breaklist(expr *e, int label)
{
    zavo *head = e->breaklist;

    if (head == NULL)
    {
        head->label = label;
        head->next = NULL;
    }
    else
    {
        zavo *tmp = head;
        while (tmp != NULL)
        {
            tmp = tmp->next;
        }
        tmp = malloc(sizeof(zavo));
        tmp->label = label;
        tmp->next = NULL;
    }
}

void add_to_truelist(expr *e, int label)
{
    zavo *head = e->truelist;

    if (head == NULL)
    {
        head->label = label;
        head->next = NULL;
    }
    else
    {
        zavo *tmp = head;
        while (tmp != NULL)
        {
            tmp = tmp->next;
        }
        tmp = malloc(sizeof(zavo));
        tmp->label = label;
        tmp->next = NULL;
    }
}

void add_to_falselist(expr *e, int label)
{
    zavo *head = e->falselist;

    if (head == NULL)
    {
        head->label = label;
        head->next = NULL;
    }
    else
    {
        zavo *tmp = head;
        while (tmp != NULL)
        {
            tmp = tmp->next;
        }
        tmp = malloc(sizeof(zavo));
        tmp->label = label;
        tmp->next = NULL;
    }
}

void backpatch(zavo *list, int label)
{
    if (list != NULL)
    {
        zavo *tmp = list;
        printf("back\n");
        while (tmp != NULL)
        {
            printf("quad %d labell %d\n",tmp->label,label);
            quads[tmp->label].label = label;
            tmp = tmp->next;
        }
    }
}

expr *newexpr_constbool(unsigned int b)
{
    expr *e = newexpr(constbool_);
    // e->contlist = NULL;
    // e->breaklist = NULL;
    // e->falselist = NULL;
    // e->truelist = NULL;
    e->boolConst = b;
    return e;
}

stack1 *arxikopoisi()
{
    stack1 *tmp = malloc(sizeof(stack1));
    tmp->maxsize = 250;
    tmp->top = -1;
    tmp->stackarray = malloc(tmp->maxsize * sizeof(int));
    return tmp;
}

int isfull(stack1 *stiba)
{
    if (stiba->top == stiba->maxsize)
        return 1;
    else
        return 0;
}

int push1(stack1 *stiba, int data)
{
    if (isfull(stiba))
        return -1;
    stiba->stackarray[++stiba->top] = data;
    return 0;
}

int pop1(stack1 *stiba)
{
    if (isfull(stiba))
        return -1;
    return stiba->stackarray[stiba->top--];
}

for_call *insert_call(expr *elist, unsigned char method, char *name)
{
    for_call *tmp = malloc(sizeof(for_call));
    tmp->elist = elist;
    tmp->method = method;
    tmp->name = name;
    return tmp;
}

zavo *new_list(int i)
{
    zavo *quads = malloc(sizeof(zavo));
    quads->label = i;
    quads->next = NULL;
    return quads;
}

zavo *insert_before_zavo(zavo *head, int i)
{
    if (head == NULL)
    {
        head = malloc(sizeof(zavo));
        head->label = i;
        head->next = NULL;
    }
    else
    {
        zavo *newNode = malloc(sizeof(zavo));
        newNode->label = i;
        newNode->next = head;
        head = newNode;
    }

    return head;
}

zavo *mergelist(zavo *first, zavo *second)
{
    zavo *temp = first;
    zavo *temp1 = second;
    zavo *newListhead = NULL;

    while (temp != NULL)
    {
        newListhead = insert_before_zavo(newListhead, temp->label);
        temp = temp->next;
    }

    while (temp1 != NULL)
    {
        newListhead = insert_before_zavo(newListhead, temp1->label);
        temp1 = temp1->next;
    }
    return newListhead;
}


unsigned int istempname(char *s)
{
    return *s == '_';
}

unsigned int istempexpr(expr *e)
{
    return e->sym && istempname(e->sym->name);
}