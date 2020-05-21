#include "quad.h"
#include <assert.h>

#define CONST_ARR_SIZE 1000

//gia ton pinaka tou telikou kwdika
#define I_SIZE 499
#define I_EXPAND 1024
#define I_CURRENT_SIZE current_instraction * sizeof(instr)
#define I_NEW_SIZE (I_SIZE * sizeof(instr) + I_CURRENT_SIZE)



//
 extern unsigned int total;
extern quad* quads;

#define AVM_STACKSIZE 4096
#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))
#define AVM_TABLE_HASHSIZE 211

typedef struct avm_memcell avm_memcell; //na ta 3anadwwwww
typedef struct avm_table_bucket avm_table_bucket;


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
} vmarg_t;

typedef struct vmarg
{
  vmarg_t type;
  unsigned int val;
} vmarg;

typedef struct instruction
{
  vmop op;
  vmarg *arg1;
  vmarg *arg2;
  vmarg *res;
  int line;
} instr;

typedef struct userFunc
{
  int address;
  int localsize;
  char *id;
} userFunc;

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
  nil_m,
  undef_m
} avm_memcell_t;

struct avm_memcell
{
  avm_memcell_t type;
  union {
    double numVal;
    char *strVal;
    unsigned char boolVal;
    avm_table *tableVal;
    unsigned funcVal;
    char *libfuncVal;
  } data;
};

struct avm_table_bucket
{
  avm_memcell key;
  avm_memcell value;
  avm_table_bucket *next;
};

typedef void (*generator_func_t)(quad );

extern void generate_ASSIGN(quad q);
extern void generate_ADD(quad q);
extern void generate_SUB(quad q);
extern void generate_MUL(quad q);
extern void generate_DIV(quad q);
extern void generate_MOD(quad q);
extern void generate_UMINUS(quad q);
extern void generate_AND(quad q);
extern void generate_OR(quad q);
extern void generate_NOT(quad q);
extern void generate_IF_EQ(quad q);
extern void generate_IF_NOTEQ(quad q);
extern void generate_IF_LESSEQ(quad q);
extern void generate_IF_GREATEREQ(quad q);
extern void generate_IF_LESS(quad q);
extern void generate_IF_GREATER(quad q);
extern void generate_JUMP(quad q);
extern void generate_CALL(quad q);
extern void generate_PARAM(quad q);
extern void generate_RETURN(quad q);
extern void generate_GETRETVAL(quad q);
extern void generate_FUNCSTART(quad q);
extern void generate_FUNCEND(quad q);
extern void generate_TABLECREATE(quad q);
extern void generate_TABLEGETELEM(quad q);
extern void generate_TABLESETELEM(quad q);


void generate_single_quad(vmop op , quad *q);

void generate_single_relational(vmop op , quad *q);

int get_next_instr_label();

void generate();

void expand_instructions();

void init_instructions();

void print_instructions();

void print_const_arrays();



vmarg* make_operand(expr *e);

// vmarg make_operand_returnval(vmarg *a);

void init_const_arrays();

//gia ta add sta const arrays gia paragori target code
int consts_add_numconst(int val);

int consts_add_stringconst(char *str);

int consts_add_namedLibFuncs(char *funcName);

int newUserFunction(int address, int localsize, char *name);

int consts_add_userFunc(userFunc *func);
void emit_instruction(instr i);

char* get_string_vmopcode(vmop op);

//
// avm_memcell stack[AVM_STACKSIZE];

// avm_table *avm_tablenew(void);

// void avm_tabledestroy(avm_table* t); //8elei ilopoish

// avm_memcell* avm_tablegetelem(avm_memcell* key);//8elei ftia3imo

// void avm_tablesetelem(avm_memcell* key, avm_memcell* value); //8elei ftia3imo

// static void avm_initstack(void);

// void avm_tableincrefcounter(avm_table *t);

// void avm_tabledecrefcounter(avm_table *t);

// void avm_tablebucketsinit(avm_table_bucket **p);

// void avm_memcellclear(avm_memcell* m);//8elei ilopoihsh

// void avm_tablebucketsdestroy(avm_table_bucket **p);

// void avm_tabledestroy(avm_table *t);