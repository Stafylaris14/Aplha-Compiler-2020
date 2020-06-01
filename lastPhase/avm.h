#include "./utilities/targetCode.h"

// executers

// typedef struct avm_memcell avm_memcell; //na ta 3anadwwwww
// typedef struct avm_table_bucket avm_table_bucket;
#define AVM_STACKENV_SIZE 4
#define AVM_STACKSIZE 4096
#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))
#define AVM_TABLE_HASHSIZE 211
#define AVM_MAX_INSTRUCTIONS 100 //den xerw!!
//top , topsp gia tin stiva
unsigned top  , topsp ;
int total_globs;

typedef void (*library_func_t) (void);

typedef struct avm_table avm_table;

// extern void execute_assign(instr *instr);
// extern void execute_add(instr *instr);
// extern void execute_sub(instr *instr);
// extern void execute_mul(instr *instr);
// extern void execute_div(instr *instr);
// extern void execute_mod(instr *instr);
// extern void execute_uminus(instr *instr);
// extern void execute_and(instr *instr);
// extern void execute_or(instr *instr);
// extern void execute_not(instr *instr);
// extern void execute_if_eq(instr *instr);
// extern void execute_if_noteq(instr *instr);
// extern void execute_if_lesseq(instr* instr);
// extern void execute_if_less(instr* instr);
// extern void execute_if_greatereq(instr* instr);
// extern void execute_if_greater(instr* instr);
// extern void execute_jump(instr* instr);
// extern void execute_call(instr* instr);
// extern void execute_param(instr* instr);
// extern void execute_return(instr* instr);
// extern void execute_getretval(instr* instr);
// extern void execute_funcstart(instr* instr);
// extern void execute_funcend(instr* instr);
// extern void execute_tablecreate(instr* instr);
// extern void execute_tablegetelem(instr* instr);
// extern void execute_tablesetelem(instr* instr);
//apothikevei times
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
  struct avm_table_bucket *next;
}avm_table_bucket;


struct avm_table
{
  unsigned refCounter;
  avm_table_bucket *strIndexed[AVM_TABLE_HASHSIZE];
  avm_table_bucket *numIndexed[AVM_TABLE_HASHSIZE];
  unsigned total;
} ;



//gia tis times kai return val
avm_memcell ax,bx,cx;
avm_memcell retval;

//einai i stiva me ta memcells
avm_memcell avm_stack[AVM_STACKSIZE];



typedef struct incomplete_jump{
    unsigned instrNo; //The jump instruction number.
    unsigned iaddress; //the i-code jump-target address.
    struct incomplete_jump* next; //A trivial linked list.
}incomplete_jump;

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

void execute_cycle(void);

void avm_callsaveenvironment(void);


library_func_t avm_getlibraryfunc(char* id);


unsigned avm_totalactuals(void);

avm_memcell* avm_getactual(unsigned i);

void libfunc_print(void);

void avm_registerlibfunc(char* id,library_func_t addr);

void libfunc_typeof(void);

void libfunc_totalarguments(void);


double add_impl(double x,double y);

double sub_impl(double x,double y);

double mul_impl(double x,double y);

double div_impl(double x,double y);

double mod_impl(double x,double y);

void execute_arithmetic(instr *instr);

unsigned char avm_tobool(avm_memcell* m);


void execute_tablecreate(instr* instr);

avm_memcell* avm_tablegetelem(avm_memcell *key , avm_memcell* i);

void avm_tablesetelem(avm_memcell *key,avm_memcell *value , avm_memcell* curr);

void execute_tablegetelem(instr* instr);

void execute_tablesetelem(instr* instr);

unsigned consts_newstring(char* s);

unsigned consts_newnumber(double n);



int *const_numbers;
userFunc **userFunctions;
// thelei me + kai to offset
char** const_strings;
char** library_functions;





// unsigned libfuncs_newused(char* s);

// unsigned userfuncs_newfunc(item* sym);

// void make_operand(expr* e,vmarg* arg);

// void make_numberoperand(vmarg* arg,double val);

// void make_booloperand(vmarg* arg,unsigned val);


// void make_retvaloperand(vmarg* arg);

// void telos_generate(vmop op,quad *quad);


// void generate_ADD(quad* q);
// void generate_SUB(quad* q);
// void generate_MUL(quad* q);
// void generate_DIV(quad* q);
// void generate_MOD(quad* q);

// void generate_NEWTABLE(quad* quad);
// void generate_TABLEGETELM(quad* quad);
// void generate_TABLESETELM(quad* quad);
// void generate_ASSIGN(quad* quad);
// void generate_NOP(quad* quad);


void memclear_string(avm_memcell* m);


void memclear_table(avm_memcell* m);

void avm_memcellclear(avm_memcell* m);

void avm_warning(char* format,...);//8elei k allew metablites mallon

void avm_assign(avm_memcell* lv, avm_memcell* rv);

void avm_error(char* format,...);

char* avm_tostring (avm_memcell* m);

void avm_calllibfunc(char* funcName);

void execute_call(instr* instr);

void avm_dec_top(void);

void avm_push_envvalue(unsigned val);

unsigned avm_get_envvalue(unsigned i);

unsigned avm_totalactuals(void);

void execute_param(instr* instr);

char* number_tostring(avm_memcell *kati);

char* string_tostring(avm_memcell *kati);

char* bool_tostring(avm_memcell *kati);

char* table_tostring(avm_memcell *kati);

char* userfunc_tostring(avm_memcell* kati);

char* libfunc_tostring(avm_memcell* kati);

char* nil_tostring(avm_memcell* kati);

char* undef_tostring(avm_memcell* kati);


void execute_assign(instr* instr);

unsigned char undef_tobool(avm_memcell* m);

void avm_initialize(void);

void execute_uminus(instr* instr);

void execute_and(instr* instr);

void execute_or(instr* instr);

void execute_not(instr* instr);

void execute_if_eq(instr* instr);

void execute_if_noteq(instr* instr);

void execute_if_lesseq(instr* instr);

void execute_if_less(instr* instr);

void execute_if_greater(instr* instr);

void execute_if_greatereq(instr* instr);

void execute_jump(instr* instr);


void execute_return(instr* instr);

void execute_getretval(instr* instr);

void execute_funcstart(instr* instr);

void execute_funcend(instr* instr);


void read_bin();

void libfunc_input();

void libfunc_objectmemberkeys();

void libfunc_objecttotalmembers();

 void libfunc_objectcopy();

 void libfunc_argument();

 void libfunc_strtonum();

 void libfunc_sqrt();

 void libfunc_cos();

 void libfunc_sin();

void print_stack();

userFunc* consts_get_userfunction_byaddress(int address);

