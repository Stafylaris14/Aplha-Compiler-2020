#include "targetCode.h"
#include "../dataStructs/linkedList.h"

int total_instraction_size = 0; 
int current_instraction = 0;
instr *instructions = (instr *)0;
extern int currQuad;

int *numConsts;
int numConstSize = 0;
char **stringConsts;
int stringConstSize = 0;
char **namedLibFuncs;
int namedLibFuncsSize = 0;
struct userFunc *userFuncs[CONST_ARR_SIZE];
int userFuncSize = 0;
generator_func_t generators[] = {
    generate_ASSIGN,
    generate_SUB,
    generate_ADD,
    generate_MUL,
    generate_DIV,
    generate_MOD,
    generate_UMINUS,
    generate_AND,
    generate_OR,
    generate_NOT,
    generate_IF_EQ,
    generate_IF_NOTEQ,
    generate_IF_LESSEQ,
    generate_IF_LESS,
    generate_IF_GREATEREQ,
    generate_IF_GREATER,
    generate_JUMP,
    generate_CALL,
    generate_PARAM,
    generate_RETURN,
    generate_GETRETVAL,
    generate_FUNCSTART,
    generate_FUNCEND,
    generate_TABLECREATE,
    generate_TABLEGETELEM,
    generate_TABLESETELEM
};


void generate_ASSIGN(quad q){generate_single_quad(assign_v , &q);}
void generate_ADD(quad q){generate_single_quad(add_v, &q);}
void generate_SUB(quad q){generate_single_quad(sub_v, &q);}
void generate_MUL(quad q){generate_single_quad(mul_v, &q);}
void generate_DIV(quad q){generate_single_quad(div_v, &q);}
void generate_MOD(quad q){generate_single_quad(mod_v, &q);}
void generate_UMINUS(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    //TODO na to dw to uminus
}
void generate_AND(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1); 
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);    
}
void generate_OR(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    // _TODO
}
void generate_NOT(quad q){
        vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    //TODO
}
void generate_IF_EQ(quad q){
        vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
}
void generate_IF_NOTEQ(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
}
void generate_IF_LESSEQ(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
}
void generate_IF_GREATEREQ(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
}
void generate_IF_LESS(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
// TODO
}
void generate_IF_GREATER(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
}
void generate_JUMP(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
}
void generate_CALL(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    //TODO edw prepei na einai me to onoma tis func apo ton pinaka
}
void generate_PARAM(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
}
void generate_RETURN(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    //TODO DEN EINAII SWOSTO
}
void generate_GETRETVAL(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres); //TODO idia fasi me panw
}
void generate_FUNCSTART(quad q){
    printf("FUNCSTART\n");
}
void generate_FUNCEND(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    make_operand(q.arg1 , vmarg1);
    make_operand(q.arg2 , vmarg2);
    make_operand(q.result , vmres);
    
}
void generate_TABLECREATE(quad q){generate_single_quad(newtable_v, &q);}
void generate_TABLEGETELEM(quad q){generate_single_quad(tablegetelem_v, &q);}
void generate_TABLESETELEM(quad q){generate_single_quad(tablesetelem_v, &q);}
void generate(){
    init_instructions();
    init_const_arrays();
    cyn();
    printf("gia dew kai to total->%d\n", total);
    for (int i = 0; i < currQuad; ++i)
    {
        (*generators[quads[i].op])(quads[i]);
    }
}

void generate_single_quad(vmop op , quad *q){
    instr i ;
    i.op = op;
    red();

    make_operand(q->arg1 , i.arg1);
    grn();
    // printf("arg2\n");
    make_operand(q->arg2 , &i.arg2);
    // printf("res\n");
    make_operand(q->result , &i.res);
    cyn();
    printf("res.val -> %d\n" , i.res->val);
     printf("res.type -> %d\n" , i.res->type);
    wht();
    emit_instruction(i);
}

void expand_instructions(){
    assert(I_CURRENT_SIZE == current_instraction);
    instr *a = malloc(I_NEW_SIZE);
    int i;
    if (instructions)
    {
        memcpy(a, instructions, I_CURRENT_SIZE);
        free(instructions);
    }
    instructions = a;
    total_instraction_size += I_EXPAND;
}

void init_instructions()
{
    int i;
    current_instraction = 0;
    instructions = malloc(sizeof(instr)*I_SIZE);
    // printf("to size apo malloc %d\n" ,sizeof(instra) );
    // printf("eimai edw gia na dw to size%d\n" ,sizeof(instructions) );
    for (i = 0; i < I_SIZE; i++)
    {
        
        instructions[i].res = NULL;
        instructions[i].arg1 = NULL;
        instructions[i].arg2 = NULL;
        instructions[i].op = -1;
        //instructions[i].line = -1;
    }
}

void print_instructions()
{
    int i;
    cyn();
    printf("-----------instructions (target CODE) -----------------\n");
    for (i = 0; i < current_instraction; i++)
    {
        if (!instructions[i].res)
            printf("%d:|%d|\t|%d|\t|%d|\t|%d|\n", i, instructions[i].op, instructions[i].res->val, instructions[i].arg1->val, instructions[i].arg2->val);
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

    if(e == NULL) {
        arg = NULL;
        return;
    }
    printf("gia des to type %d\n" , e->type);
    expr_t expressionType = e->type;
    arg = NULL;
    arg = malloc(sizeof(vmarg));
    if(!arg) exit(-1);
    switch (expressionType)
    {
    case boolexpr_:
    case arthmexp_:
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
        red();
        printf("%d\n" , e->numConst);
        wht();
        arg->val = consts_add_numconst(e->numConst);
        printf("arg->val = %d\n" , arg->val);
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
    case  assignexp_:
        printf("eimai gia to assignexpr\n");
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
    printf("eimai edw gia to numConst %d\n" , val);
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

void emit_instruction(instr i){
    if(current_instraction >= total_instraction_size )
        expand_instructions();
    instructions[current_instraction] = i;
    current_instraction++;
    return;
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