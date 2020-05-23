#include "targetCode.h"
#include "../dataStructs/linkedList.h"

int total_instraction_size = 0; 
int current_instraction = 1;
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
    generate_ADD,
    generate_SUB,
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
    generate_TABLESETELEM,
    // generate_NOP
};


void generate_ASSIGN(quad q){generate_single_quad(assign_v , &q);}
void generate_ADD(quad q){generate_single_quad(add_v, &q);}
void generate_SUB(quad q){generate_single_quad(sub_v, &q);}
void generate_MUL(quad q){generate_single_quad(mul_v, &q);}
void generate_DIV(quad q){generate_single_quad(div_v, &q);}
void generate_MOD(quad q){generate_single_quad(mod_v, &q);}
void generate_UMINUS(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    vmarg1 = make_operand(q.arg1);
    vmarg2 = make_operand(q.arg2 );
    vmres = make_operand(q.result );
    //TODO na to dw to uminus
}
void generate_AND(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    vmarg1 = make_operand(q.arg1); 
    vmarg2 = make_operand(q.arg2 );
    vmres = make_operand(q.result );    
}
void generate_OR(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    vmarg1 = make_operand(q.arg1);
    vmarg2 = make_operand(q.arg2 );
    vmres = make_operand(q.result );
    // _TODO
}
void generate_NOT(quad q){
        vmarg *vmarg1 ,*vmarg2 , *vmres; 
    vmarg1 = make_operand(q.arg1);
    vmarg2 = make_operand(q.arg2 );
    vmres = make_operand(q.result );
    //TODO
}
void generate_IF_EQ(quad q){generate_single_relational(jeq_v,&q);}
void generate_IF_NOTEQ(quad q){generate_single_relational(jne_v , &q);}
void generate_IF_LESSEQ(quad q){generate_single_relational(jle_v , &q);}
void generate_IF_GREATEREQ(quad q){generate_single_relational(jge_v , &q);}
void generate_IF_LESS(quad q){generate_single_relational(jle_v , &q);}
void generate_IF_GREATER(quad q){generate_single_relational(jgt_v , &q);}
void generate_JUMP(quad q){generate_single_relational(jump_v , &q);}
void generate_CALL(quad q){
    instr i;
    q.next_instr_label = get_next_instr_label();
    i.op = callfunc_v;
    i.arg1 = make_operand(q.arg1);
    emit_instruction(i);
    //TODO edw prepei na einai me to onoma tis func apo ton pinaka
}
void generate_PARAM(quad q){
    q.next_instr_label = get_next_instr_label();
    instr i;
    i.op = pusharg_v;
    make_operand(q.arg1);
}
void generate_RETURN(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    vmarg1 = make_operand(q.arg1);
    vmarg2 = make_operand(q.arg2 );
    vmres = make_operand(q.result );
    //TODO DEN EINAII SWOSTO
}
void generate_GETRETVAL(quad q){
    q.next_instr_label = get_next_instr_label();
    instr i; 
    i.op = assign_v;
    i.res = make_operand(q.result);
    // i.arg1 = make_operand_returnval(i.arg1);
    emit_instruction(i);
}
void generate_FUNCSTART(quad q){
    printf("FUNCSTART\n");
    generate_single_quad(FUNCSTART , &q);
}
void generate_FUNCEND(quad q){
    vmarg *vmarg1 ,*vmarg2 , *vmres; 
    vmarg1 = make_operand(q.arg1);
    vmarg2 = make_operand(q.arg2 );
    vmres = make_operand(q.result );
    
}
void generate_TABLECREATE(quad q){generate_single_quad(newtable_v, &q);}
void generate_TABLEGETELEM(quad q){generate_single_quad(tablegetelem_v, &q);}
void generate_TABLESETELEM(quad q){generate_single_quad(tablesetelem_v, &q);}
// void generate_NOP(quad q){return;}
void generate(){
    init_instructions();
    init_const_arrays();
    for (int i = 0; i < currQuad; ++i)
    {
        (*generators[quads[i].op])(quads[i]);
    }
}

void generate_single_quad(vmop op , quad *q){
    instr i ;
    i.op = op;
    
    i.arg1 = make_operand(q->arg1);
    // grn();
    //  printf("arg1.val -> %d\n" , i.arg1->val);
    //  printf("arg1.type -> %d\n" , i.arg1->type);

    i.arg2 = make_operand(q->arg2);
    // red();
    // if(i.arg2){
    //     printf("arg2.val -> %d\n" , i.arg2->val);
    //     printf("arg2.type -> %d\n" , i.arg2->type);
    // }

    i.res = make_operand(q->result);
    // cyn();
    // printf("res.val -> %d\n" , i.res->val);
    // printf("res.type -> %d\n" , i.res->type);
    // wht();
    

   // printf("eimai edw gia to quad %d , \n kai instr \t %d , %d , \n" , q->op , i.res->val ,i.res->type );
    emit_instruction(i);
}

void generate_single_relational(vmop op , quad *q)
{
    int label_q = q->label;
    instr  i ;
    i.arg1 = make_operand(q->arg1);
    i.arg2 = make_operand(q->arg2);
    i.res = malloc(sizeof(vmarg));
    i.res->val = label_q;
    i.res->type = label_a;
    i.op = op;
    emit_instruction(i);

}

int get_next_instr_label(){return 1+current_instraction;}

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
    printf("i:|opcode|\t|res|\t|arg1|\t |arg2|\n");
    for (i = 0; i < current_instraction; i++)
    {

        if(instructions[i].arg1 == NULL) {
            instructions[i].arg1 = malloc(sizeof(vmarg));
            instructions[i].arg1->val = -1;
        }
        if(instructions[i].arg2 == NULL) {
            instructions[i].arg2 = malloc(sizeof(vmarg));
            instructions[i].arg2->val = -1;
        }
        if(instructions[i].res == NULL) {
            instructions[i].res = malloc(sizeof(vmarg));
            instructions[i].res->val = -1;
        }
        // printf("%d:|%d|\t|%d|\t|%d|\t|%d|\n", i,  instructions[i].op, instructions[i].res->val, instructions[i].arg1->val, instructions[i].arg2->val);
       
        // if (instructions[i].) 
        printf("%d:|%s|\t|%d , %d|\t|%d , %d|\t|%d , %d|\n", 1+i,  get_string_vmopcode(instructions[i].op), instructions[i].res->val,instructions[i].res->type, instructions[i].arg1->val,instructions[i].arg1->type ,instructions[i].arg2->val , instructions[i].arg2->type);
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
        if(namedLibFuncs[i])
        printf("%d: %s\n", i, namedLibFuncs[i]);
    }
    printf("-----USER FUNCTIONS -----\n");
    for (i = 0; i < userFuncSize; i++)
    {
        if(userFuncs[i])
        printf("%d: name = %s , localsize = %d , address = %d\n", i, userFuncs[i]->id , userFuncs[i]->localsize , userFuncs[i]->address);
    }
    wht();
    
}
// EDW EINAI-----------------------------------------------------------------------------
vmarg* make_operand(expr *e)
{
    
    vmarg* arg = malloc(sizeof(vmarg));
    if(e == NULL) {
        arg = NULL;
        return NULL ;
    }
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
        red();
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
        break;
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
        arg->val = consts_add_userFunc(e);
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
        arg->val = e->sym->offset; 
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
        //printf("eimai gia to assignexpr\n");
         break;
    default:
        assert(0);
        break;
    }
    return arg;
}

vmarg* make_operand_constNum(int val)
{
    vmarg* tmp = malloc(sizeof(vmarg));
    tmp->type = number_a;
    tmp->val = val;
}

// vmarg make_operand_returnval(vmarg a)
// {
//     vmarg a1 = a;
//     a1.type = retval_a;
//     return a1;
// }

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

    int i;
    for (i = 0; i < numConstSize; i ++)
    {
        if(numConsts[i] == val) return i;
    }
    numConsts[numConstSize] = val;
    numConstSize++;
    return numConstSize - 1;
}

int consts_add_stringconst(char *str)
{
    for(int i = 0; i < stringConstSize; i++)
        if(!strcmp(stringConsts[i] , str))return i;
    stringConsts[stringConstSize] = strdup(str);
    stringConstSize++;
    return stringConstSize - 1;
}

int consts_add_namedLibFuncs(char *funcName)
{
     for(int i = 0; i < namedLibFuncsSize; i++)
        if(!strcmp(namedLibFuncs[i] , funcName))return i;
    namedLibFuncs[namedLibFuncsSize] = funcName;
    namedLibFuncsSize++;
    return namedLibFuncsSize - 1;
}

//to address einai to quad pou 3ekinaei h sinartisi kai to localsize einai to plithos tws formal arguments
int newUserFunction(int address, int localsize, char *name)
{
    for(int i = 0; i < namedLibFuncsSize; i++)
        if(!strcmp(namedLibFuncs[i] , name))return i;
    userFunc *tmp = malloc(sizeof(userFunc));
    tmp->address = address;
    tmp->localsize = localsize;
    tmp->id = strdup(name);

    userFuncs[userFuncSize] = tmp;
    userFuncSize++;

    return userFuncSize-1;
}

int consts_add_userFunc(expr *e)
{
    // printf("eimai edw sto functions user %s\n" , func->id);
    // userFuncs[userFuncSize] = func;
    userFunc* function = malloc(sizeof(userFunc));
    function->id = strdup(e->sym->name);
    // function->address = ;
    function->localsize = e->sym->formal_count;
    function->address =e->sym->iaddress; 
    userFuncs[userFuncSize] = function;
    userFuncSize++;
    return userFuncSize - 1;
}

//pairnei ola ta arguments kai ta vazei ston pinaka (opws kai sta quads)

void emit_instruction(instr i){
    if(current_instraction >= total_instraction_size )
        expand_instructions();
    instructions[current_instraction] = i;
    red();
    // printf("eimai mesa gia sto emit gia %d , %d\n" , instructions[current_instraction].res->type ,instructions[current_instraction].res->val );
    wht();
    current_instraction++;
    return;
}

char* get_string_vmopcode(vmop op)
{ 
    // red();
    // printf("op------------------------------------------>%d\n" , op);
    // wht();
    switch (op)
    {
    case 0:
        return "assign";
        break;
    case add_v:
        return "add";
        break;
    case sub_v:
        return "sub";
        break;
    case mul_v:
        return "mul";
        break;
    case div_v:
        return "div";
        break;
    case mod_v:
        return "mod";
        break;
    case uminus_v:
        return "uminus";
        break;
    case callfunc_v:
        return "callFunc";
        break;
    case enterfunc_v:
        return "enterFunc";
        break;
    case exitfunc_v:
        return "exitfunc";
        break;
    case and_v:
        return "and";
        break;
    case or_v:
        return "or";
        break;
    case not_v:
        return "not";
        break;
    case jump_v:
        return "jump";
        break;
    case jeq_v:
        return "jeq\t";
        break;
    case jne_v:
        return "jne\t";
        break;
    case jgt_v:
        return "jgt\t";
        break;
    case jge_v:
        return "jge\t";
        break;
    case jle_v:
        return "jle\t";
        break;
    case newtable_v:
        return "newTable";
        break;
    case tablegetelem_v:
        return "tablegetelement";
        break;
    case tablesetelem_v:
        return "teblesetelement";
        break;
    case pusharg_v:
        return "pusharg";
        break;
    case nop_v:
        return "nop";
        break;
    default:
        assert(0);
        break;
    }
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