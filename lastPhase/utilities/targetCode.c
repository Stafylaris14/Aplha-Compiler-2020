#include "targetCode.h"
#include "../dataStructs/linkedList.h"



void generate_ASSIGN(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(assign_v , vmres , vmarg1 , vmarg2);
}
void generate_ADD(quad q)
{
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(add_v , vmres , vmarg1 , vmarg2);
}
void generate_SUB(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(sub_v , vmres , vmarg1 , vmarg2);
}
void generate_MUL(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(mul_v , vmres , vmarg1 , vmarg2);
}
void generate_DIV(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(div_v , vmres , vmarg1 , vmarg2);
}
void generate_MOD(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(mod_v , vmres , vmarg1 , vmarg2);
}
void generate_UMINUS(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(assign_v , vmres , vmarg1 , vmarg2);//TODO na to dw to uminus
}
void generate_AND(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1); 
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(and_v , vmres , vmarg1 , vmarg2);
}
void generate_OR(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(or_v , vmres , vmarg1 , vmarg2);//TODO
}
void generate_NOT(quad q){
        vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(assign_v , vmres , vmarg1 , vmarg2);//TODO
}
void generate_IF_EQ(quad q){
        vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(jeq_v , vmres , vmarg1 , vmarg2);
}
void generate_IF_NOTEQ(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(jne_v , vmres , vmarg1 , vmarg2);
}
void generate_IF_LESSEQ(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(jle_v , vmres , vmarg1 , vmarg2);
}
void generate_IF_GREATEREQ(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(jge_v , vmres , vmarg1 , vmarg2);
}
void generate_IF_LESS(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(jle_v , vmres , vmarg1 , vmarg2);//TODO
}
void generate_IF_GREATER(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(jgt_v , vmres , vmarg1 , vmarg2);
}
void generate_JUMP(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(jump_v , vmres , vmarg1 , vmarg2);
}
void generate_CALL(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(callfunc_v , vmres , vmarg1 , vmarg2);//TODO edw prepei na einai me to onoma tis func apo ton pinaka
}
void generate_PARAM(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(jge_v , vmres , vmarg1 , vmarg2);
}
void generate_RETURN(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(nop_v , vmres , vmarg1 , vmarg2);//TODO DEN EINAII SWOSTO
}
void generate_GETRETVAL(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres); //TODO idia fasi me panw
    // emit_instraction( , vmres , vmarg1 , vmarg2);
}
void generate_FUNCSTART(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(enterfunc_v , vmres , vmarg1 , vmarg2);
}
void generate_FUNCEND(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(exitfunc_v , vmres , vmarg1 , vmarg2);
}
void generate_TABLECREATE(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(newtable_v , vmres , vmarg1 , vmarg2);
}
void generate_TABLEGETELEM(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(tablegetelem_v , vmres , vmarg1 , vmarg2);
}
void generate_TABLESETELEM(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    emit_instraction(tablesetelem_v , vmres , vmarg1 , vmarg2);
}
void generate(){
    init_instractions();
    for (int i = 0; i < total; ++i)
    {
        (*generators[quads[i].op])(quads[i]);
    }
}

void expand_instractions()
{
    assert(I_CURRENT_SIZE == current_instraction);
    instr *a = malloc(I_NEW_SIZE);
    int i;
    if (instractions)
    {
        memcpy(a, instractions, I_CURRENT_SIZE);
        free(instractions);
    }
    instractions = a;
    total_instraction_size += I_EXPAND;
}

void init_instractions()
{
    int i;
    current_instraction = 0;
    instractions = malloc(sizeof(instractions) * I_SIZE);

    for (i = 0; i < I_SIZE; i++)
    {
        instractions[i].res = NULL;
        instractions[i].arg1 = NULL;
        instractions[i].arg2 = NULL;
        instractions[i].op = -1;
        instractions[i].line = -1;
    }
}

void print_instractions()
{
    int i;
    cyn();
    printf("-----------instractions (target CODE) -----------------\n");
    for (i = 0; i < current_instraction; i++)
    {
        if (!instractions[i].res)
            printf("%d:|%d|\t|%d|\t|%d|\t|%d|\n", i, instractions[i].op, instractions[i].res->val, instractions[i].arg1->val, instractions[i].arg2->val);
    }
    print_const_arrays();
}

void print_const_arrays()
{
    int i;
    grn();
    printf("-----NUM CONSTS -----\n");
    for (i = 0; i < numConstSize; i++)
    {
        printf("%d: %d\n", i, numConsts[i]);
    }
    printf("-----STRING CONSTS -----\n");
    for (i = 0; i < stringConstSize; i++)
    {
        printf("%d: %s\n", i, stringConsts[i]);
    }

    printf("-----NAMED LIB FUNCTIONS -----\n");
    for (i = 0; i < namedLibFuncsSize; i++)
    {
        printf("%d: %s\n", i, namedLibFuncs[i]);
    }
    printf("-----USER FUNCTIONS -----\n");
    for (i = 0; i < userFuncSize; i++)
    {
        printf("%d: %s\n", i, userFuncs[i]->id);
    }
    wht();
}

void make_operand(expr *e, vmarg *arg)
{
    expr_t expressionType = e->type;
    arg = malloc(sizeof(vmarg));

    switch (expressionType)
    {
    case boolexpr_:
    case assignexp_:
    case newtable_:
    case var_:
    case tableitem_:
    {
        arg->val = e->sym->offset; //na to to offset
        switch (e->sym->scope_spase)
        {
        case program_variable:
            arg->type = global_a;
            break;
        case function_local:
            arg->type = local_a;
            break;
        case formal_argument:
            arg->type = formal_a;
            break;
        default:
            assert(0);
        }
    }
    case constnum_:
        arg->type = number_a;
        arg->val = consts_add_numconst(e->numConst);
        break;
    case constbool_:
        arg->type = constbool_;
        arg->val = e->boolConst;
        break;
    case conststring_:
        arg->type = conststring_;
        arg->val = consts_add_stringconst(e->stringConst);
        break;
    case pfunc_:
        arg->type = userFunc_a;
        //arg->val= e->sym-> TODO thelei to taddress leei pou einai mesa sto symbol
        // TODO ????????
        break;
    case lfunc_:
        arg->type = libFunc_a;
        arg->val = consts_add_namedLibFuncs(e->sym->name);
        break;
    case nill_:
        arg->type = nill_a;
        break;
    default:
        assert(0);
        break;
    }
}

void init_const_arrays()
{
    numConsts = malloc(sizeof(int) * CONST_ARR_SIZE);
    stringConsts = malloc(CONST_ARR_SIZE);
    namedLibFuncs = malloc(sizeof(struct userFunc) * CONST_ARR_SIZE);

    for (int i = 0; i < CONST_ARR_SIZE; i++)
    {
        // numConsts[i] = NULL;
        stringConsts[i] = NULL;
        namedLibFuncs[i] = NULL;
    }
}

int consts_add_numconst(int val)
{
    numConsts[numConstSize] = val;
    numConstSize++;
    return numConstSize - 1;
}

int consts_add_stringconst(char *str)
{
    stringConsts[stringConstSize] = strdup(str);
    stringConstSize++;
    return stringConstSize - 1;
}

int consts_add_namedLibFuncs(char *funcName)
{
    namedLibFuncs[namedLibFuncsSize] = funcName;
    namedLibFuncsSize++;
    return namedLibFuncsSize - 1;
}

//to address einai to quad pou 3ekinaei h sinartisi kai to localsize einai to plithos tws formal arguments
userFunc *newUserFunction(int address, int localsize, char *name)
{
    userFunc *tmp = malloc(sizeof(userFunc));
    tmp->address = address;
    tmp->localsize = localsize;

    tmp->id = strdup(name);

    return tmp;
}

int consts_add_userFunc(userFunc *func)
{
    userFuncs[userFuncSize] = func;
    userFuncSize++;
    return userFuncSize - 1;
}

//pairnei ola ta arguments kai ta vazei ston pinaka (opws kai sta quads)
void emit_instraction(vmop op, vmarg *res, vmarg *arg1, vmarg *arg2)
{
    if(current_instraction >= total_instraction_size )
        expand_instractions();
    
    instr tmp;

    tmp.op = op;
    tmp.arg1 = arg1;
    tmp.arg2 = arg2;
    tmp.res = res;

    instractions[current_instraction] = tmp;

    current_instraction++;
}


// static void avm_initstack(void)
// {
//     unsigned i;
//     for (i = 0; i < AVM_STACKSIZE; i++)
//     {
//         AVM_WIPEOUT(stack[i]);
//         stack[i].type = undef_m;
//     }
// }

// void avm_tableincrefcounter(avm_table *t)
// {
//     ++t->refCounter;
// }

// void avm_tabledecrefcounter(avm_table *t)
// {
//     assert(t->refCounter > 0);
//     if (!--t->refCounter)
//         avm_tabledestroy(t);
// }

// void avm_tablebucketsinit(avm_table_bucket **p)
// {
//     unsigned i;
//     for (i = 0; i < AVM_TABLE_HASHSIZE; i++)
//         p[i] = (avm_table_bucket *)0;
// }

// avm_table *avm_tablenew(void)
// {
//     avm_table *t = (avm_table *)malloc(sizeof(avm_table));
//     AVM_WIPEOUT(*t);

//     t->refCounter = t->total = 0;
//     avm_tablebucketsinit(t->numIndexed);
//     avm_tablebucketsinit(t->strIndexed);

//     return t;
// }

// void avm_tablebucketsdestroy(avm_table_bucket **p)
// {
//     unsigned i;
//     for (i = 0; i < AVM_TABLE_HASHSIZE; ++i, ++p)
//     {
//         avm_table_bucket *b;
//         for (*b = *p; b;) //den exw idea! TODO
//         {
//             avm_table_bucket *del = b;
//             b = b->next;
//             avm_memcellclear(&del->key);
//             avm_memcellclear(&del->value);
//             free(del);
//         }
//         p[i] = (avm_table_bucket *)0;
//     }
// }

// void avm_tabledestroy(avm_table *t)
// {
//     avm_tablebucketsdestroy(t->strIndexed);
//     avm_tablebucketsdestroy(t->numIndexed);
//     free(t);
// }