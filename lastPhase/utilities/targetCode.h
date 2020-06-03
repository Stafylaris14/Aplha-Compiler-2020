#include "quad.h"
#include <assert.h>

#define CONST_ARR_SIZE 1000

//gia ton pinaka tou telikou kwdika
#define I_SIZE 1024
#define I_EXPAND 1024
#define I_CURRENT_SIZE current_instraction * sizeof(instr)
#define I_NEW_SIZE (I_SIZE * sizeof(instr) + I_CURRENT_SIZE)
#define __DEBUG instr *INSTRUCTION_DEBUG = NULL;printf("%d" , INSTRUCTION_DEBUG->res->val);


//
 extern unsigned int total;
extern quad* quads;







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
  int srcLine;
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

vmarg* make_operand_boolean(int val);

vmarg* make_operand_constNum(int val);

vmarg *make_operand_returnval();

void init_const_arrays();

//gia ta add sta const arrays gia paragori target code
int consts_add_numconst(int val);

int consts_add_stringconst(char *str);

int consts_add_namedLibFuncs(char *funcName);

int newUserFunction(int address, int localsize, char *name);

int consts_add_userFunc(expr *e);

void emit_instruction(instr i);

char* get_string_vmopcode(vmop op);

char* get_string_vmargtype(vmarg *v);

void print_quad(quad q);

void write_bin();
