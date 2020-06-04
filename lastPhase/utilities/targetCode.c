#include "targetCode.h"
#include "../dataStructs/linkedList.h"

int total_instraction_size = 0; 
int current_instraction;
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
int total_globals=0;
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
    generate_IF_GREATEREQ,
    generate_IF_LESS,
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
    instr i;
    i.op = mul_v;
    i.arg1 = make_operand(q.arg1);
    i.res = make_operand(q.result);
    i.arg2 = malloc(sizeof(vmarg));
    i.arg2->type = number_a;
    i.arg2->val = consts_add_numconst(-1);
    emit_instruction(i);
}
void generate_AND(quad q){
    // vmarg *vmarg1 ,*vmarg2 , *vmres; 
    // vmarg1 = make_operand(q.arg1); 
    // vmarg2 = make_operand(q.arg2 );
    // vmres = make_operand(q.result );    
}
void generate_OR(quad q){
   

    // _TODO
}
void generate_NOT(quad q){
    // instr i;


    // i.op = jeq_v;
    // i.arg1 = make_operand(q.arg1);
    // i.arg2 =  make_operand_boolean(0);
    // i.res->val = get_next_instr_label()+3;
    // i.res->type = label_a;
    // emit_instruction(i);

    // i.op = assign_v;
    // i.arg1 = make_operand_boolean(0);
    // i.arg2 = NULL;
    // i.res = make_operand(q.result);
    // emit_instruction(i);

    // i.op = jump_v;
    // i.arg1 = NULL;
    // i.arg2 = NULL;
    // i.res->type =label_a;
    // i.res->val = get_next_instr_label()+2;
    // emit_instruction(i);

    // i.op = assign_v;
    // i.arg1 = make_operand_boolean(1);
    // i.arg2 = NULL;
    // i.res = make_operand(q.result);
    // emit_instruction(i); 
}
void generate_IF_EQ(quad q){generate_single_relational(jeq_v,&q);}
void generate_IF_NOTEQ(quad q){generate_single_relational(jne_v , &q);}
void generate_IF_LESSEQ(quad q){generate_single_relational(jle_v , &q);}
void generate_IF_GREATEREQ(quad q){generate_single_relational(jge_v , &q);}
void generate_IF_LESS(quad q){generate_single_relational(jle_v , &q);}
void generate_IF_GREATER(quad q){generate_single_relational(jgt_v , &q);}
void generate_JUMP(quad q){generate_single_relational(jump_v , &q);}
void generate_CALL(quad q)
{
    
    instr i;
    q.next_instr_label = get_next_instr_label();
    i.op = callfunc_v;
   
    i.arg1 = make_operand(q.arg1);
    emit_instruction(i);
}
void generate_PARAM(quad q){
    instr i;
    q.next_instr_label = get_next_instr_label();
    //print_quad(q);
    i.arg2 = NULL;
    i.arg1 = make_operand(q.arg1);
    i.op = pusharg_v;
    emit_instruction(i);
}
void generate_RETURN(quad q){
    instr i ;
    i.op = assign_v;
    i.res = make_operand_returnval();
    i.arg1 = make_operand(q.result);
    mag();
    //print_quad(q);
   // printf("to val arg1 einia %d\n" , q.arg1->sym->);
    wht();
    emit_instruction(i);

}
void generate_GETRETVAL(quad q){
    q.next_instr_label = get_next_instr_label();
    instr i; 
    i.op = assign_v;
    i.res = make_operand(q.arg1);
    i.arg1 = make_operand_returnval();
    emit_instruction(i);
}
void generate_FUNCSTART(quad q){
    // printf("FUNCSTART\n");
    // generate_single_quad(enterfunc_v , &q);
    instr i;
    i.res = make_operand(q.arg1);
    i.arg2 = NULL;
    i.op = enterfunc_v;
    emit_instruction(i);
}
void generate_FUNCEND(quad q){
    instr i;    
    i.res = make_operand(q.arg1);
    i.op = exitfunc_v;
    emit_instruction(i);
}
void generate_TABLECREATE(quad q){generate_single_quad(newtable_v, &q);}
void generate_TABLEGETELEM(quad q){generate_single_quad(tablegetelem_v, &q);}
void generate_TABLESETELEM(quad q){generate_single_quad(tablesetelem_v, &q);}
// void generate_NOP(quad q){return;}
void generate(){
    init_instructions();
    init_const_arrays();
    int i;
    for (i = 0; i < currQuad; ++i)
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
    i.res->val = label_q-1;
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
    printf("i:|opcode|\t|res|\t|arg1|\t |arg2|\n\n\n");
    for (i = 0; i < current_instraction; i++)
    {

        if(instructions[i].arg1 == NULL || instructions[i].arg1->type < 0 || instructions[i].arg1->type > 10) {
            instructions[i].arg1 = malloc(sizeof(vmarg));
            instructions[i].arg1->val = -1;
            instructions[i].arg1->type = -1;
        }
        if(instructions[i].arg2 == NULL||instructions[i].arg2->type < 0|| instructions[i].arg2->type > 10) {
            instructions[i].arg2 = malloc(sizeof(vmarg));
            instructions[i].arg2->val = -1;
            instructions[i].arg2->type = -1;
        }
        if(instructions[i].res == NULL || instructions[i].res->type < 0 || instructions[i].res->type > 10) {
            instructions[i].res = malloc(sizeof(vmarg));
            instructions[i].res->val = -1;
            instructions[i].res->type = -1;
        }
       
        printf("%d:" , i);
        printf("%s|%d\t\t" , get_string_vmopcode(instructions[i].op) ,instructions[i].op );
         if(instructions[i].res->type != -1)
            printf("%d(%s)%d\t\t" , instructions[i].res->val , get_string_vmargtype(instructions[i].res) , instructions[i].res->type);
        else
            printf("\t\t\t");
        if(instructions[i].arg1->type != -1)
            printf("%d(%s)%d\t\t" , instructions[i].arg1->val , get_string_vmargtype(instructions[i].arg1) , instructions[i].arg1->type);
        else
            printf("\t\t\t");
        if(instructions[i].arg2->type != -1)
            printf("%d(%s)%d\t\t" , instructions[i].arg2->val , get_string_vmargtype(instructions[i].arg2) , instructions[i].arg2->type);
        else
            printf("\t\t\t");
        
        printf("\n");

        // printf("%d:|%s|\t|%d(%s)|\t|%d , (%s)|\t|%d , (%s)|\n",
        //  1+i,
        // get_string_vmopcode(instructions[i].op),
        // instructions[i].res->val,
        // get_string_vmargtype(instructions[i].res),
        // instructions[i].arg1->val,
        // get_string_vmargtype(instructions[i].arg1),
        // instructions[i].arg2->val,
        // get_string_vmargtype(instructions[i].arg2));
    }
    //printf("eimai edw gia to curr einai %d\n" ,current_instraction );
    print_const_arrays();
}

void print_const_arrays()
{
    int i;
    grn();
    printf("to total globals einia %d\n" , total_globals);
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
    
    vmarg* arg = (vmarg*)malloc(sizeof(vmarg));
    if(e == NULL) {
        arg = NULL;
        return NULL ;
    }
    expr_t expressionType = e->type;
    
    if(!arg) exit(-1);
    mag();
    // printf("\n\n\n\neimai edw sto make op kai to expression type einai %d\n\n\n\n" , expressionType);
    wht();
    switch (expressionType)
    {
    case boolexpr_:
    case arthmexp_: 
    case newtable_:
    case var_: 
    case tableitem_:
    {
        
        arg->val = e->sym->offset;

        switch (e->sym->scope_spase)
        {
        case program_variable:
            arg->type = global_a;
            total_globals++;
            break;
        case function_local:
            arg->type = local_a;
            break;
        case formal_argument:
            yel();
            printf("----------------------------------------------eimai edw1\n");
            wht();
            arg->type = formal_a;
            break;
        default:
            assert(0);
        }
        
        break;
        //return arg;
    }
    case constnum_:
        arg->type = number_a;
        arg->val = consts_add_numconst(e->numConst);
        break;
    case constbool_:
        arg->type = bool_a;
        arg->val = e->boolConst;
        break;
    case conststring_:
        arg->type = string_a;
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

vmarg* make_operand_boolean(int val)
{
    if (val != 0 || val!=1)assert(0);
    vmarg* new = malloc(sizeof(vmarg));
    new->type = bool_a;
    new->val = val;
    return new;
}

vmarg *make_operand_returnval()
{
    vmarg* a1 = malloc(sizeof(vmarg));
    a1->type = retval_a;
    //a1->val = -1;
    return a1;
}

void init_const_arrays()
{
    numConsts = malloc(sizeof(int) * CONST_ARR_SIZE);
    stringConsts = malloc(CONST_ARR_SIZE);
    namedLibFuncs = malloc(sizeof(struct userFunc) * CONST_ARR_SIZE);
    int i;
    for (i = 0; i < CONST_ARR_SIZE; i++)
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
    int i;
    for(i = 0; i < stringConstSize; i++)
        if(!strcmp(stringConsts[i] , str))return i;
    stringConsts[stringConstSize] = strdup(str);
    stringConstSize++;
    return stringConstSize - 1;
}

int consts_add_namedLibFuncs(char *funcName)
{
    int i;
     for(i = 0; i < namedLibFuncsSize; i++)
        if(!strcmp(namedLibFuncs[i] , funcName))return i;
    namedLibFuncs[namedLibFuncsSize] = funcName;
    namedLibFuncsSize++;
    return namedLibFuncsSize - 1;
}

//to address einai to quad pou 3ekinaei h sinartisi kai to localsize einai to plithos tws formal arguments
int newUserFunction(int address, int localsize, char *name)
{
    int i;
    for(i = 0; i < namedLibFuncsSize; i++)
        if(!strcmp(namedLibFuncs[i] , name)){
            printf("mpika edw!\n");
            return i;
        }
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
    printf("eimai edw sto functions user %s\n" , e->sym->name);
    // userFuncs[userFuncSize] = func;
    int i;
    for (i = 0; i < userFuncSize; i++)
        if(!strcmp(e->sym->name , userFuncs[i]->id)) return i;
    
    userFunc* function = malloc(sizeof(userFunc));
    function->id = strdup(e->sym->name);
    // function->address = ;
    function->localsize = e->sym->formal_count;
    function->address =current_instraction; 
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
        return "add\t";
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
        return "jump\t";
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

char* get_string_vmargtype(vmarg *v)
{
    switch (v->type)
    {
    case label_a:
        return "label";
    case  global_a:
        return "global";
    case formal_a:
        return "formal";
    case local_a:
        return "local";
    case number_a:
        return "number";
    case string_a:
        return "string";
    case bool_a:
        return "bool";
    case nill_a:
        return "nill";
    case userFunc_a:
        return "userFunctin";
    case libFunc_a:
        return "libfunction";
    case retval_a:
        return "return val";
    default:
        return " ";
        break;
    }
    return "something";
}

void write_bin()
{
    FILE *fp;
    fp = fopen("instructions" , "wb+");
    size_t size = 0;
    // instr
    int i;
    fwrite(&total_globals , sizeof(int) , 1 , fp);
    fwrite(&current_instraction , sizeof(int) , 1 , fp);
    for(i =0 ; i < current_instraction; i++)
        fwrite(&instructions[i] , sizeof(instr) ,1, fp);
    //sizes
    size = sizeof(stringConsts);
    fwrite(&size , sizeof(size_t) , 1 , fp);
    size = sizeof(numConsts);
    fwrite(&size , sizeof(size_t) , 1 , fp);
    size = sizeof(namedLibFuncs);
    fwrite(&size , sizeof(size_t) , 1 , fp);
    size = sizeof(userFuncs);
    fwrite(&size , sizeof(size_t) , 1 , fp);
    // consts
    for(i =0 ; i< numConstSize;i++)
        fwrite(&numConsts[i] ,sizeof(numConsts[i]) , 1 , fp );
    for(i = 0; i < stringConstSize; i++)
        fwrite(stringConsts[i] ,sizeof(char*) , 1 , fp );
    for(i = 0; i < namedLibFuncsSize; i ++)
        fwrite(namedLibFuncs[i] , sizeof(char*) ,1 , fp);
    for(i = 0; i < userFuncSize; i++)
        fwrite(userFuncs[i] , sizeof(userFunc) , 1 , fp);
    fclose(fp);
}

// util
void print_quad(quad q)
{
    red();
    printf("-----------------------------------\n");
    printf("|%d|\t\t\n" ,q.op);
    if(q.result)
    {
        printf("res ->type -> |%d|\n" , q.result->type);
        if((q.result->sym))
            printf("res ->ssym-> %s\n" , q.result->sym->name);
    }
     if(q.arg1)
    {
        printf("arg1->type -> |%d|\n" , q.arg1->type);
        if((q.arg1->sym))
            printf("arg1->sym-> %s\n" , q.arg1->sym->name);
            // printf("arg1->sym->%d\n" , q.arg1->sym->scope_spase);
            //printf("arg1->sym->%s\n" , q.arg1->sym->);
    }
    if(q.arg2)
    {
        printf("arg2->stype -> |%d|\n" , q.arg2->type);
        if((q.arg2->sym))
            printf("sym-> %s\n" , q.arg2->sym->name);
    }
    printf("-----------------------------------\n");
    wht();
}


