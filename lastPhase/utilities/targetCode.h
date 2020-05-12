
#include "quad.h"
#include <assert.h>
typedef enum vmopcode
{
    assign_v,
    add_v,
    sub_v,
    mul_v,
    div_v,
    mod_v,
    uminus_v,
    callfunc_v,
    enterfunc_v,
    exitfunc_v,
    and_v,
    or_v,
    not_v,
    jump_v,
    jeq_v,
    jne_v,
    jgt_v,
    jge_v,
    jle_v,
    newtable_v,
    tablegetelem_v,
    tablesetelem_v,
    pusharg_v,
    nop_v
} vmop;


typedef enum vmarg_t
{
    label_a,
    global_a,
    formal_a,
    local_a,
    number_a,
    string_a,
    bool_a,
    nill_a,
    userFunc_a,
    libFunc_a,
    retval_a
}vmarg_t;


typedef struct vmarg 
{ 
    vmarg_t   type; 
    unsigned int val; 
} vmarg;


typedef struct instruction
{
    vmop op;
    vmarg arg1;
    vmarg arg2;
    vmarg res;
    int line;
}instr;

struct userFunc
{
    int address;
    int localsize;
    int id;
};


int* numConsts;                             
int numConstSize = 0;;
char** stringConsts;
int stringConstSize = 0;
char** namedLibFuncs;
int namedLibFuncsSize = 0;
struct userFunc* userFuncs;
int userFuncSize = 0;


void make_operand(expr* e , vmarg* argumnent);

void emit_target(instr *i);