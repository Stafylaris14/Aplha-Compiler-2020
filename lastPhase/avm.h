#include "./utilities/targetCode.h"

// executers

typedef void (*execute_func_t)(instr);


// typedef struct avm_memcell avm_memcell; //na ta 3anadwwwww
// typedef struct avm_table_bucket avm_table_bucket;

execute_func_t executeFuncs[] = {

    execute_ASSIGN,
    execute_ADD,
    execute_SUB,
    execute_MUL,
    execute_DIV,
    execute_MOD,
    execute_UMINUS,
    execute_AND,
    execute_OR,
    execute_NOT,
    execute_IF_EQ,
    execute_IF_NOTEQ,
    execute_IF_LESSEQ,
    execute_IF_LESS,
    execute_IF_GREATEREQ,
    execute_IF_GREATER,
    execute_JUMP,
    execute_CALL,
    execute_PARAM,
    execute_RETURN,
    execute_GETRETVAL,
    execute_FUNCSTART,
    execute_FUNCEND,
    execute_TABLECREATE,
    execute_TABLEGETELEM,
    execute_TABLESETELEM,
};

typedef struct avm_table
{
  unsigned refCounter;
  avm_table_bucket *strIndexed[AVM_TABLE_HASHSIZE];
  avm_table_bucket *numIndexed[AVM_TABLE_HASHSIZE];
  unsigned total;
} avm_table;



typedef enum avm_memcell_t
{
    number_m,
    string_m,
    bool_m,
    table_m,
    userfunc_m,
    libfunc_m,
    nill_m,
    undef_m
} avm_memcell_t;

typedef struct avm_memcell
{
    avm_memcell_t type;
    union {
        double numVal;
        char *strVal;
        unsigned char boolVal;
        avm_table *tableVal;
        unsigned funcVal;
        char *libFuncVal;
    } data;
} avm_memcell;

typedef struct avm_table_bucket
{
  avm_memcell key;
  avm_memcell value;
  avm_table_bucket *next;
}avm_table_bucket;
///////////translation////////////////
avm_memcell *avm_translate_operand(vmarg *arg, avm_memcell *reg);

//consts
char* consts_get_libFunction(int index);

userFunc* consts_get_userfunction(int index);

char* consts_get_string(int index);

int consts_get_number(int index);

//////////////////////////////////////////functions
static void avm_initstack(void);

void avm_tableincrefcounter(avm_table *t);

void avm_tabledecrefcounter(avm_table *t);

void avm_tablebucketsinit(avm_table_bucket **p);

avm_table *avm_tablenew(void);

void avm_tablebucketsdestroy(avm_table_bucket **p);

void avm_tabledestroy(avm_table *t);