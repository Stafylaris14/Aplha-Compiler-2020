#include "avm.h"
#include <stdio.h>
#include <math.h>
#include "./dataStructs/linkedList.h"
#include <ctype.h>

char *typeStrings[8] = {"number_m",
                        "string_m",
                        "bool_m",
                        "table_m",
                        "userfunc_m",
                        "libfunc_m",
                        "nil_m",
                        "undef_m"};

typedef void (*memclear_func_t)(avm_memcell *);

memclear_func_t memclearFuncs[] = {
    0,
    memclear_string,
    0,
    0,
    0,
    0,
    0,
    0};

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic
#define PI 3.14159265

typedef char *(*tostring_func_t)(avm_memcell *);

tostring_func_t tostringFuncs[] = {
    number_tostring,
    string_tostring,
    bool_tostring,
    table_tostring,
    userfunc_tostring,
    libfunc_tostring,
    nil_tostring,
    undef_tostring};

typedef void (*execute_func_t)(instr *);

execute_func_t executeFuncs[] = {
    execute_assign,
    execute_add,
    execute_sub,
    execute_mul,
    execute_div,
    execute_mod,
    execute_uminus,
    execute_call,
    execute_funcstart,
    execute_funcend,
    execute_and,
    execute_or,
    execute_not,
    execute_jump,
    execute_if_eq,
    execute_if_noteq,
    execute_if_greater,
    execute_if_greatereq,
    execute_if_lesseq,
    execute_tablecreate,
    execute_tablegetelem,
    execute_tablesetelem,
    execute_param,
    execute_if_less,
    execute_return,
    execute_getretval,
};

extern int *numConsts;
extern int numConstSize;
extern char **stringConsts;
extern int stringConstSize;
extern char **namedLibFuncs;
extern int namedLibFuncsSize;
extern struct userFunc *userFuncs[CONST_ARR_SIZE];
extern int userFuncSize;
extern int current_instraction;
unsigned char executionFinished = 0;
unsigned pc = 0;
unsigned currLine = 0;
unsigned codeSize = 0;
instr *code = (instr *)0;
#define AVM_ENDING_PC codeSize

unsigned totalActuals = 0;

typedef void (*library_func_t)(void);

library_func_t librarys[12] = {0};
int number_of_lib = 0;

#define AVM_NUMACTUALS_OFFSET +4
#define AVM_SAVEDPC_OFFSET +3
#define AVM_SAVEDTOP_OFFSET +2
#define AVM_SAVEDTOPSP_OFFSET +1


typedef double (*arithmetic_func_t)(double x, double y);

typedef unsigned char (*tobool_func_t)(avm_memcell *);
unsigned char number_tobool(avm_memcell *m) { return m->data.numVal != 0; } //dial 15
unsigned char string_tobool(avm_memcell *m) { return m->data.strVal[0] != 0; }//dial 15
unsigned char bool_tobool(avm_memcell *m) { return m->data.boolVal; }//dial 15
unsigned char table_tobool(avm_memcell *m) { return 1; }//dial 15
unsigned char userfunc_tobool(avm_memcell *m) { return 1; }//dial 15
unsigned char libfunc_tobool(avm_memcell *m) { return 1; }//dial 15
unsigned char nil_tobool(avm_memcell *m) { return 0; }//dial 15
unsigned char undef_tobool(avm_memcell *m) //dial 15
{
  assert(0);
  return 0;
}

typedef void (*memclear_func_t)(avm_memcell *);

typedef void (*library_func_t)(void);


unsigned totalStringConsts;
char **nameLibfuncs;
unsigned totalNameLibfuncs;
unsigned totalUserFuncs;

tobool_func_t toboolFuncs[] = { //dial 15
    number_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undef_tobool};

avm_memcell stack[AVM_STACKSIZE];

avm_memcell *avm_translate_operand(vmarg *arg, avm_memcell *reg) //dial 15
{

  switch (arg->type)
  {
  case global_a:
    return &stack[AVM_STACKSIZE - 1 - arg->val];
  case local_a:
    return &stack[topsp - arg->val];
  case formal_a:
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + arg->val];
  case retval_a:
    return &retval;
  case number_a:
    reg->type = number_m;
    reg->data.numVal = consts_get_number(arg->val);
    return reg;
  case bool_a:
    reg->type = bool_m;
    reg->data.boolVal = arg->val;
    return reg;
  case string_a:
    reg->type = string_m;
    reg->data.strVal = consts_get_string(arg->val);
    return reg;
  case userFunc_a:
    reg->type = userfunc_m;
    userFunc *t = consts_get_userfunction(arg->val);
    reg->data.funcVal = t->address;
    return reg;
  case libFunc_a:
    reg->type = libfunc_m;
    reg->data.libFuncVal = consts_get_libFunction(arg->val);
    return reg;
  case nill_a:
    reg->type = nill_m;
    break;
  default:
    assert(0);
    break;
  }
}

//GET CONSTS
int consts_get_number(int index) //dial 15
{
  return numConsts[index];
}

char *consts_get_string(int index) //dial 15
{
  return stringConsts[index];
}

userFunc *consts_get_userfunction(int index) //dial 15
{
  return userFuncs[index];
}

char *consts_get_libFunction(int index)//dial 15
{
  return namedLibFuncs[index];
}

void execute_cycle(void) //dial 15
{
  if (executionFinished){
    return;
  }
  else if (pc == AVM_ENDING_PC)
  {
    executionFinished = 1;
    return;
  }
  else
  {
    assert(pc < AVM_ENDING_PC); 
    instr *instr1 = code + pc;
    unsigned oldPC = pc;
    assert(instr1->op >= 0 && instr1->op <= AVM_MAX_INSTRUCTIONS);    
    (*executeFuncs[instr1->op])(instr1);
    if (pc == oldPC)
      ++pc;
  }
}

void avm_callsaveenvironment(void) //dial 15
{
  avm_push_envvalue(totalActuals);
  avm_push_envvalue(pc + 1);
  avm_push_envvalue(top + totalActuals + 2);
  avm_push_envvalue(topsp);
}

void execute_funcend(instr *unused) // dial 15
{
  unsigned oldTop = top;
  top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
  pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
  topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
  while (oldTop++ <= top){
    avm_memcellclear(&stack[oldTop]);
  }
}

void avm_dec_top(void) //dial 15
{
  if (!top)
  {
    avm_error("stack overflow");
    executionFinished = 1;
  }
  else
    --top;
}

void avm_push_envvalue(unsigned val) //dial 15
{
  stack[top].type = number_m;
  stack[top].data.numVal = val;
  avm_dec_top();
}

library_func_t avm_getlibraryfunc(char *id) //dial 15
{
  if (!strcmp("print", id))
    return libfunc_print;
  if (!strcmp("typeof", id))
    return libfunc_typeof;
  if (!strcmp("totalarguments", id))
    return libfunc_totalarguments;
  if (!strcmp("input", id))
    return libfunc_input;
  if (!strcmp("objectmemberkeys", id))
    return libfunc_objectmemberkeys;
  if (!strcmp("objecttotalmembers", id))
    return libfunc_objecttotalmembers;
  if (!strcmp("objectcopy", id))
    return libfunc_objectcopy;
  if (!strcmp("argument", id))
    return libfunc_argument;
  if (!strcmp("strtonum", id))
    return libfunc_strtonum;
  if (!strcmp("sqrt", id))
    return libfunc_sqrt;
  if (!strcmp("cos", id))
    return libfunc_cos;
  if (!strcmp("sin", id))
    return libfunc_sin;

  return NULL;
}

unsigned avm_totalactuals(void) //dial 15
{
  return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell *avm_getactual(unsigned i) // dial 15
{
  assert(i < avm_totalactuals());
  return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

void libfunc_print(void) // dial 15
{
  unsigned n = avm_totalactuals();
  unsigned i;
  for (i = 0; i < n; ++i)
  {
  char *s = avm_tostring(avm_getactual(i));
    grn();
    if(avm_getactual(i)->type == table_m)
      fprintf(stdout ,"(%s)", s );
    else{
      fprintf(stdout ,"%s", s );
    }
    wht();
    // free(s);
  }
}

void avm_registerlibfunc(char *id, library_func_t addr) //dial 15 
{
  librarys[number_of_lib++] = addr;
}

void libfunc_typeof(void) //dial 15
{
  unsigned n = avm_totalactuals();
  if (n != 1)
    avm_error("one argument (not %d) expected in 'typeof'!", n);
  else
  {
    avm_memcellclear(&retval);
    retval.type = string_m;
    retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
  }
}

void libfunc_totalarguments(void) //dial 15
{
  unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
  avm_memcellclear(&retval);

  if (!p_topsp)
  {
    avm_error("'totalarguments'called outside a function!");
    retval.type = nill_m;
  }
  else
  {
    retval.type = number_m;
    retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
  }
}

double add_impl(double x, double y) { return x + y; } //front

double sub_impl(double x, double y) { return x - y; } //front

double mul_impl(double x, double y) { return x * y; } //front

double div_impl(double x, double y)
{
  if(y == 0) return 0;
  return x / y;
}

double mod_impl(double x, double y) //front
{
  if (y == 0)
    return 0;
  return ((unsigned)x) % ((unsigned)y);
}

arithmetic_func_t arithmeticFuncs[] = { //na balo sto header
    add_impl,
    sub_impl,
    mul_impl,
    div_impl,
    mod_impl};

void execute_arithmetic(instr *instr) // dial 15
{
  avm_memcell *lv = avm_translate_operand(instr->res, (avm_memcell *)0);
  avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
  avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);
  assert(rv1 && rv2);
  if (rv1->type != number_m || rv2->type != number_m)
  {
    
    avm_error("not a number in arithmetic!\n");
    executionFinished = 1;
  }
  else
  {
    arithmetic_func_t op = arithmeticFuncs[instr->op - add_v];
    avm_memcellclear(lv);
    lv->type = number_m;
    lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
  }
}

unsigned char avm_tobool(avm_memcell *m) //dial 15
{
  assert(m->type >= 0 && m->type < undef_m);

  return (*toboolFuncs[m->type])(m);
}

static void avm_initstack(void)
{
  unsigned i;

  for (i = 0; i < AVM_STACKSIZE; i++)
  {
    AVM_WIPEOUT(stack[i]);
    stack[i].type = undef_m;
    stack[i].data.strVal = NULL;
  }
}

void avm_tableincrefcounter(avm_table *t) //dial 13
{
  ++t->refCounter;
}

void avm_tabledecrefcounter(avm_table *t) //dial 13
{
  assert(t->refCounter > 0);
  if (!--t->refCounter)
    avm_tabledestroy(t);
}

void avm_tablebucketsinit(avm_table_bucket **p) //dial 13
{
  unsigned i;
  for (i = 0; i < AVM_TABLE_HASHSIZE; i++)
    p[i] = (avm_table_bucket *)0;
}

avm_table *avm_tablenew(void) //dia 13
{
  avm_table *t = (avm_table*)malloc(sizeof(avm_table));
  AVM_WIPEOUT(*t);

  t->refCounter = t->total = 0;
  avm_tablebucketsinit(t->numIndexed);
  avm_tablebucketsinit(t->strIndexed);

  return t;
}

void avm_tablebucketsdestroy(avm_table_bucket **p) //dial 13
{
  unsigned i;
  for (i = 0; i < AVM_TABLE_HASHSIZE; ++i, ++p)
  {
    avm_table_bucket *b = *p;
    for (*b; b;) //den exw idea! TODO
    {
      avm_table_bucket *del = b;
      b = b->next;
      avm_memcellclear(&del->key);
      avm_memcellclear(&del->value);
      free(del);
    }
    p[i] = (avm_table_bucket *)0;
  }
}

void avm_tabledestroy(avm_table *t) //dia 13 
{
  avm_tablebucketsdestroy(t->strIndexed);
  avm_tablebucketsdestroy(t->numIndexed);
  free(t);
}

void execute_if_eq(instr *instr) //dial 15
{
  assert(instr->res->type == label_a);
  avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
  avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);

  int result = 0;

  if (rv1->type == undef_m || rv2->type == undef_m)
  {
    //avm_error("'undef'involved in equality!");
  }
  else if (rv1->type == nill_m || rv2->type == nill_m)
  {
    result = rv1->type == nill_m && rv2->type == nill_m;
  }
  else if (rv1->type == bool_m || rv2->type == bool_m)
  {
    result = (avm_tobool(rv1) == avm_tobool(rv2));
  }
  else
  {
    if (rv2->type == string_m)
      result = !strcmp(rv1->data.strVal, rv2->data.strVal);
    else if (rv2->type == number_m)
      result = rv1->data.numVal == rv2->data.numVal;
    else if (rv2->type == userfunc_m)
      result = rv1->data.funcVal == rv2->data.funcVal;
    else if (rv2->type == libfunc_m)
      result = !strcmp(rv1->data.libFuncVal, rv2->data.libFuncVal);
    else if (rv2->type == table_m)
      result = rv1->data.tableVal == rv2->data.tableVal;
  }
  
  if(result == 1){
    pc = instr->res->val;
    assert(pc < AVM_MAX_INSTRUCTIONS);
      red();
  }

}

void execute_tablecreate(instr *instr)
{
  avm_memcell *lv = avm_translate_operand(instr->arg1, (avm_memcell *)0);

 // assert(lv && (&stack[top] <= lv && &stack[top] > lv || lv == &retval));

  avm_memcellclear(lv);
  lv->type = table_m;
  lv->data.tableVal = avm_tablenew();
  avm_tableincrefcounter(lv->data.tableVal);
}


avm_memcell *avm_tablegetelem(avm_table *table ,avm_memcell *key)
{
  avm_table_bucket *pinakas = NULL;
  int index = hash_avm(key);

  if(key->type == number_m)
  {
     pinakas = table->numIndexed[index];
    if (pinakas == NULL){avm_error("Cannot access to table\n"); }
    if(pinakas->key.data.numVal == key->data.numVal){
      avm_table_bucket* tmp  = pinakas;

      while( tmp!=NULL && tmp->key.data.numVal!=key->data.numVal){
        tmp = tmp->next;
      }
      if(tmp == NULL) assert(0);
      
      return &tmp->value;
     }

    return &pinakas->value;
  }else if(key->type == string_m)
  {
    pinakas = table->strIndexed[index];
    avm_table_bucket* tmp  = pinakas;
    if(pinakas != NULL){
      while(strcmp(tmp->key.data.strVal,key->data.strVal))tmp = tmp->next;
      return &tmp->value;
    }
    return &pinakas->value;
  }else 
  {
    assert(0);
  }

}
  
 


void avm_tablesetelem(avm_table *table, avm_memcell *key, avm_memcell *val)
{

  avm_table_bucket *pinakas;
  int index = hash_avm(key);
  
  if(key->type == number_m){
    //if(key->data.numVal == 0)assert(0);
    pinakas = table->numIndexed[index];
    if(pinakas == NULL){
        pinakas = malloc(sizeof(avm_table_bucket));
        pinakas->key = *key;
       // pinakas->key.type = key->type;
        pinakas->value = *val;
        //pinakas->value.type = val->type;
        pinakas->next = NULL;
    }else{
        avm_table_bucket *Node = malloc(sizeof(avm_table_bucket));
        Node->key = *key;
        //Node->key.type = key->type;
        
        Node->value = *val;
       // Node->value.type = val->type;
        Node->next = NULL; 
       avm_table_bucket* tmp = pinakas;       
        while(tmp->next != NULL){
          tmp = tmp->next;
        }
        tmp->next = Node;

    }
    table->numIndexed[index] = pinakas;

  }else if(key->type == string_m){
    
    pinakas = table->strIndexed[index];
    if(pinakas == NULL){
        pinakas = malloc(sizeof(avm_table_bucket));
        pinakas->key = *key;
        pinakas->value = *val;
        pinakas->next = NULL;
    }else{
        avm_table_bucket *Node = malloc(sizeof(avm_table_bucket));
        Node->key = *key;
        Node->value = *val;
        Node->next = NULL;        
        avm_table_bucket *tmp = pinakas;
        while(tmp->next != NULL)
        {
          tmp = tmp->next;
        }
        tmp ->next = Node;
        
    }
    table->strIndexed[index] = pinakas;

  }
   table->total = table->total +1;
}




void execute_tablegetelem(instr *instr)
{

  avm_memcell *lv = avm_translate_operand(instr->res, (avm_memcell *)0);
  avm_memcell *t = avm_translate_operand(instr->arg1, (avm_memcell *)0);
  avm_memcell *i = avm_translate_operand(instr->arg2, &ax);

  assert(i);

  avm_memcellclear(lv);
  lv->type = nill_m;

  if (t->type != table_m)
  {
    //  avm_error("illegal use of type %d as table!", typeStrings[t->type]);
     // assert(0);
  }
  else
  {
    avm_memcell *content = avm_tablegetelem(t->data.tableVal, i);
    if (content)
    {
      avm_assign(lv, content);
    }
    else
    {
      char *ts = avm_tostring(t);
      char *is = avm_tostring(i);
      char *warn;
      sprintf(warn, "%s[%s] not found ! ", ts, is);
      avm_warning(warn);
      free(ts);
      free(is);
    }
  }
}

void execute_tablesetelem(instr *instr) //dial 15
{
  avm_memcell *t = avm_translate_operand(instr->res, (avm_memcell *)0);
  avm_memcell *i = avm_translate_operand(instr->arg1, &ax);
  avm_memcell *c = avm_translate_operand(instr->arg2, &bx);

  assert(t && &stack[top] <= t && &stack[AVM_STACKSIZE] > t);
  assert(i && c);

  if (t->type != table_m)
    avm_error("illegal use of type %s as table!", typeStrings[t->type]);
  else
  {
    avm_tablesetelem(t->data.tableVal, i, c);
  }
}

void memclear_string(avm_memcell *m) //dia 15
{
 // assert(m->data.strVal);
  // free(m->data.strVal);
}

void memclear_table(avm_memcell *m) //dia 15
{
  assert(m->data.tableVal);
  avm_tabledecrefcounter(m->data.tableVal);
}

void avm_memcellclear(avm_memcell *m) //dial 15 
{
  if (m->type != undef_m)
  {
    if(m->type!=1 && m->type!=3){
      m->type = undef_m;
      return;
    }
    memclear_func_t f = memclearFuncs[m->type];    
    if (f){
      (*f)(m);
    }
    m->type = undef_m;
  }
}

void avm_warning(char *format, ...) //dial 15
{
  cyn();
  printf("\nAVM WARNING %s\n", format);
  wht();
}

void execute_assign(instr *instr) //dial 15
{
  

  avm_memcell *lv = avm_translate_operand(instr->res, (avm_memcell *)0);
  avm_memcell *rv = avm_translate_operand(instr->arg1, &ax);
 
  
  assert(rv);

  avm_assign(lv, rv);
}

void avm_assign(avm_memcell *lv, avm_memcell *rv) //dial 15
{

  if (lv == rv)
    return;
  if (lv->type == table_m && rv->type == table_m && lv->data.tableVal == rv->data.tableVal)
    return;

  avm_memcellclear(lv);
  
  memcpy(lv, rv, sizeof(avm_memcell));
  if (lv->type == string_m){
    lv->data.strVal = strdup(rv->data.strVal);
  }
  else if (lv->type == table_m)
    avm_tableincrefcounter(lv->data.tableVal);
}

void avm_error(char *format, ...) //dial 15
{
  red();
  printf("\nAVM ERROR %s\n", format);
  wht();
}

char *avm_tostring(avm_memcell *m) //dial 15
{
   if(m->type < 0 || m->type > undef_m)m->type = 7;
  return (*tostringFuncs[m->type])(m);
}

void execute_call(instr *instr) //dial 15
{
   
  avm_memcell *func = avm_translate_operand(instr->arg1, &ax);
  assert(func);
  avm_callsaveenvironment();
  

  switch (func->type)
  {
    case userfunc_m:
    {
      pc = func->data.funcVal;
      assert(pc < AVM_ENDING_PC);
      assert(code[pc].op == enterfunc_v);
      break;
    }case number_m:
    {
      userFunc* f = consts_get_userfunction(func->data.numVal);
      if(f == NULL){
        avm_error("Function not found");
        exit(1);
      }
      pc = f->address;
      break;
    }
    case string_m:
      avm_calllibfunc(func->data.strVal);
      break;
    case libfunc_m:
      avm_calllibfunc(func->data.libFuncVal);
      break;
    default:
    {
      char *s = avm_tostring(func);
    }
  }
}

void execute_funcstart(instr *instr) //dial 15
{
  avm_memcell *func = avm_translate_operand(instr->res, &ax);

  assert(pc == func->data.funcVal);
  assert(func);

  totalActuals = 0;
  userFunc *funcInfo = consts_get_userfunction(instr->res->val);
  
  topsp = top;
  top = top - funcInfo->localsize;
}

unsigned avm_get_envvalue(unsigned i) //dial 15
{
  unsigned val = (unsigned)stack[i].data.numVal;
  if(stack[i].data.numVal != ((double)val)){
    // avm_error("Segment can't reached");
    // exit(1);
  }
  return val;
}

void avm_calllibfunc(char *funcName) //dial 15 
{

  library_func_t f = avm_getlibraryfunc(funcName);

  if (!f)
  {
    avm_error("unsupported lib func %s called ! ", funcName);
  }
  else
  {
    topsp = top;
    totalActuals = 0;
    (*f)();
    if (!executionFinished)
      execute_funcend((instr *)0);
  }
}

void execute_param(instr *instr) //dial 15
{
  avm_memcell *arg = avm_translate_operand(instr->arg1, &ax);
  wht();
  assert(arg);
  grn();
  avm_assign(&stack[top], arg);
  ++totalActuals;
  avm_dec_top();
}

char *number_tostring(avm_memcell *kati) //dial 15
{
  char *res = (char*)malloc(sizeof(char)* 50);
  sprintf(res, "%f", kati->data.numVal);
  return res;
}

char *string_tostring(avm_memcell *kati) //dial 15
{
  char *res = malloc(200);
  sprintf(res, "%s", kati->data.strVal);
  return res;
}

char *bool_tostring(avm_memcell *kati) //dial 15
{
  char *res;
  if (kati->data.boolVal == 1)
    res = "true";
  else
    res = "false";

  return res;
}

char *table_tostring(avm_memcell *kati) // dial 15
{

  avm_table * a = kati->data.tableVal;

  char* temp = malloc(100);
  char* res = malloc(500);
  int i ;
  for(i = 0; i < AVM_TABLE_HASHSIZE;i++)
  {
    if(a->numIndexed[i]!=NULL){
      sprintf(temp , "[%s] " , avm_tostring(&a->numIndexed[i]->value));
      strcat(res , temp);
      temp[0] = '\0';
    }
      if(a->strIndexed[i]!=NULL){
      sprintf(temp , "[%s] " , avm_tostring(&a->strIndexed[i]->value));
      strcat(res , temp);
      temp[0] = '\0';
    }
  }
  
 
  //char *s = "table:";
  return res;
}

char *userfunc_tostring(avm_memcell *kati) // dial 15
{
  char* s = malloc(sizeof(500));
  userFunc* function = consts_get_userfunction_byaddress(kati->data.funcVal);

  sprintf(s , "user function (%s) " , function->id);

  return s;
}

char *libfunc_tostring(avm_memcell *kati) //dial 15
{
  char* s = malloc(100);


  sprintf(s , "Library Function (%s)" , kati->data.libFuncVal); // dial 15

  return s;


}

char *nil_tostring(avm_memcell *kati) { //dial 15
  char*s = "Nill";
  return s;
}

char *undef_tostring(avm_memcell *kati) { //dial 15

  char* s="Undefined";
  return s;

}

void avm_initialize(void) // dial 15
{
  //krataw xwro gia tis global

  top = AVM_STACKSIZE - total_globs;
  topsp = AVM_STACKSIZE - total_globs;
  avm_initstack();
  avm_registerlibfunc("print", libfunc_print);
  avm_registerlibfunc("input", libfunc_input);
  avm_registerlibfunc("objectmemberkeys", libfunc_objectmemberkeys);
  avm_registerlibfunc("objecttotalmembers", libfunc_objecttotalmembers);
  avm_registerlibfunc("objectcopy", libfunc_objectcopy);
  avm_registerlibfunc("totalarguments", libfunc_totalarguments);
  avm_registerlibfunc("argument", libfunc_argument);
  avm_registerlibfunc("typeof", libfunc_typeof);
  avm_registerlibfunc("strtonum", libfunc_strtonum);
  avm_registerlibfunc("sqrt", libfunc_sqrt);
  avm_registerlibfunc("cos", libfunc_cos);
  avm_registerlibfunc("sin", libfunc_sin);
}

void execute_uminus(instr *instr)
{
  printf("uminus den benw pote\n");
}

void execute_and(instr *instr)
{
  printf("and den benw pote\n");
}

void execute_or(instr *instr)
{
  printf("or den benw pote\n");
}

void execute_not(instr *instr)
{
  printf("not den benw pote\n");
}

void execute_if_noteq(instr *instr)
{
  assert(instr->res->type == label_a);

  avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
  avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);

  unsigned char result = 0;

  if (rv1->type == undef_m || rv2->type == undef_m)
  {
    avm_error("'undef'involved in equality!");
  }
  else if (rv1->type == nill_m || rv2->type == nill_m)
  {
    result = rv1->type == nill_m && rv2->type == nill_m;
  }
  else if (rv1->type == bool_m || rv2->type == bool_m)
  {
    result = (avm_tobool(rv1) == avm_tobool(rv2));
  }
  else if (rv1->type != rv2->type){
    unsigned char t1 = avm_tobool(rv1);
    unsigned char t2 = avm_tobool(rv2);
    if(t1 == t2)result = 1;
    else result = 0;
  }else
  {
    if (rv1->type == string_m)
      result = strcmp(rv1->data.strVal, rv2->data.strVal);
    else if (rv1->type == number_m)
      result = rv1->data.numVal != rv2->data.numVal;
    else if (rv1->type == userfunc_m)
      result = rv1->data.funcVal != rv2->data.funcVal;
    else if (rv1->type == libfunc_m)
      result = strcmp(rv1->data.libFuncVal, rv2->data.libFuncVal);
    else if (rv1->type == table_m)
      result = rv1->data.tableVal != rv2->data.tableVal;
  }
  if (!executionFinished && result)
    pc = instr->res->val;
}

void execute_if_lesseq(instr *instr)
{
  assert(instr->res->type == label_a);

  avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
  avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);

  unsigned char result = 0;

  if (rv1->type == undef_m || rv2->type == undef_m)
  {
    //avm_error("'undef'involved in equality!");
  }
  else if (rv1->type == nill_m || rv2->type == nill_m)
  {
    result = rv1->type == nill_m && rv2->type == nill_m;
  }
  else if (rv1->type == bool_m || rv2->type == bool_m)
  {
    result = (avm_tobool(rv1) == avm_tobool(rv2));
  }
  else if (rv1->type != rv2->type)
    avm_error("%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
  else
  {
    if (rv1->type == string_m)
      result = strcmp(rv1->data.strVal, rv2->data.strVal) <= 0;
    else if (rv1->type == number_m)
      result = rv1->data.numVal <= rv2->data.numVal;
    else if (rv1->type == userfunc_m)
      result = rv1->data.funcVal <= rv2->data.funcVal;
    else if (rv1->type == libfunc_m)
      result = strcmp(rv1->data.libFuncVal, rv2->data.libFuncVal) <= 0;
    else if (rv1->type == table_m)
      result = rv1->data.tableVal <= rv2->data.tableVal;
  }
  if (!executionFinished && result)
    pc = instr->res->val;
}

void execute_if_less(instr *instr)
{
  assert(instr->res->type == label_a);

  avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
  avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);

  unsigned char result = 0;

  if (rv1->type == undef_m || rv2->type == undef_m)
  {
    //avm_error("'undef'involved in equality!");
  }
  else if (rv1->type == nill_m || rv2->type == nill_m)
  {
    result = rv1->type == nill_m && rv2->type == nill_m;
  }
  else if (rv1->type == bool_m || rv2->type == bool_m)
  {
    result = (avm_tobool(rv1) == avm_tobool(rv2));
  }
  else if (rv1->type != rv2->type)
    avm_error("%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
  else
  {
    if (rv1->type == string_m)
      result = strcmp(rv1->data.strVal, rv2->data.strVal) < 0;
    else if (rv1->type == number_m)
      result = rv1->data.numVal < rv2->data.numVal;
    else if (rv1->type == userfunc_m)
      result = rv1->data.funcVal < rv2->data.funcVal;
    else if (rv1->type == libfunc_m)
      result = strcmp(rv1->data.libFuncVal, rv2->data.libFuncVal) < 0;
    else if (rv1->type == table_m)
      result = rv1->data.tableVal < rv2->data.tableVal;
  }
  if (!executionFinished && result)
    pc = instr->res->val;
}

void execute_if_greater(instr *instr)
{
  assert(instr->res->type == label_a);

  avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
  avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);

  unsigned char result = 0;

  if (rv1->type == undef_m || rv2->type == undef_m)
  {
    //avm_error("'undef'involved in equality!");
  }
  else if (rv1->type == nill_m || rv2->type == nill_m)
  {
    result = rv1->type == nill_m && rv2->type == nill_m;
  }
  else if (rv1->type == bool_m || rv2->type == bool_m)
  {
    result = (avm_tobool(rv1) == avm_tobool(rv2));
  }
  else
  {
    if (rv1->type == string_m)
      result = strcmp(rv1->data.strVal, rv2->data.strVal) > 0;
    else if (rv1->type == number_m){
      result = rv1->data.numVal > rv2->data.numVal;
   
    }
    else if (rv1->type == userfunc_m)
      result = rv1->data.funcVal > rv2->data.funcVal;
    else if (rv1->type == libfunc_m)
      result = strcmp(rv1->data.libFuncVal, rv2->data.libFuncVal) > 0;
    else if (rv1->type == table_m)
      result = rv1->data.tableVal > rv2->data.tableVal;
  }
    
  
  if (!executionFinished && result)
  {
    pc = instr->res->val;
  }
}

void execute_if_greatereq(instr *instr)
{
  assert(instr->res->type == label_a);

  avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
  avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);
  unsigned char result = 0;

  if (rv1->type == undef_m || rv2->type == undef_m)
  {
    //avm_error("'undef'involved in equality!");
  }
  else if (rv1->type == nill_m || rv2->type == nill_m)
  {
    result = rv1->type == nill_m && rv2->type == nill_m;
  }
  else if (rv1->type == bool_m || rv2->type == bool_m)
  {
    result = (avm_tobool(rv1) == avm_tobool(rv2));
  }
  else if (rv1->type != rv2->type)
    avm_error("%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
  else
  {
    if (rv1->type == string_m)
      result = strcmp(rv1->data.strVal, rv2->data.strVal) >= 0;
    else if (rv1->type == number_m)
      result = rv1->data.numVal >= rv2->data.numVal;
    else if (rv1->type == userfunc_m)
      result = rv1->data.funcVal >= rv2->data.funcVal;
    else if (rv1->type == libfunc_m)
      result = strcmp(rv1->data.libFuncVal, rv2->data.libFuncVal) >= 0;
    else if (rv1->type == table_m)
      result = rv1->data.tableVal >= rv2->data.tableVal;
  }
  if (!executionFinished && result)
    pc = instr->res->val;
}

void execute_jump(instr *instr)
{
  if (!executionFinished){
    // grn();
    //exit(-1);
  }
    
    pc = instr->res->val;
}

void execute_return(instr *instr)
{
  printf("return den benw pote\n");
}

void execute_getretval(instr *instr)
{
  printf("getretval den benw pote\n");
}

void read_bin()
{
  size_t size;

  FILE *fp = fopen("instructions", "rb");
  fread(&total_globs , sizeof(int) , 1 , fp);
  fread(&codeSize, sizeof(int), 1, fp);
  char buffer[10];
  code = malloc(sizeof(instr) * codeSize);
  //code
  int i;
  red();
  for (i = 0; i < codeSize; i++)
  {
    fread(&code[i], sizeof(instr), 1, fp);

  }
  //sizes
    //string
    const_strings = malloc(sizeof(char *) * stringConstSize);
    //nums
    const_numbers = malloc(sizeof(numConstSize) * sizeof(double));
    //libfuncs
    library_functions = malloc(sizeof(char *) * namedLibFuncsSize);
    //userfunctions
    userFunctions = malloc(sizeof(userFunc) * sizeof(userFuncSize));
  
  // consts
  for (i = 0; i < numConstSize; i++)
  {
    fread(&const_numbers[i], sizeof(double), 1, fp);
  }

  //strings
  for ( i = 0; i < stringConstSize; i++)
  {
    fread(&const_strings[i], sizeof(char *), 1, fp);
  }

  //lib functions
  for (i = 0; i < namedLibFuncsSize; i++)
  {
    fread(&library_functions, sizeof(char *), 1, fp);
  }

  //userfuncs
  for (i = 0; i < userFuncSize; i++){
    fread(&userFunctions, sizeof(userFunc), 1, fp);
  }

  fclose(fp);
}


void libfunc_input(void)
{
      char s[200];
      printf("Input:");
      scanf("%s" , s);
      if(!strcmp(s , "true")){
        retval.type = bool_m;
        retval.data.boolVal = 1;
        return;
      }else if(!strcmp(s , "false")){
        retval.type = bool_m;
        retval.data.boolVal = 0;
        return;
      }else if(isdigit(s[0])){
        retval.type = number_m;
        retval.data.numVal = atoi(s);
        return;
      }
    
}

void libfunc_objectmemberkeys(void)
{
  avm_memcell* t = avm_getactual(0);
  avm_table* p = t->data.tableVal;
  retval.type = table_m;
  retval.data.tableVal = avm_tablenew();
  int i;
  char*s = malloc(200);
  for(i =0; i < AVM_TABLE_HASHSIZE; i++)
  {
    
    if(p->numIndexed[i]!=NULL)
    {
      s = strdup(avm_tostring(&p->numIndexed[i]->key));
      // s[sizeof(avm_tostring(&p->numIndexed[i]->key))] = '\0';
      avm_memcell* temp = malloc(sizeof(avm_memcell));
      temp->data.strVal = strdup(s);
      temp->type = string_m;
      avm_tablesetelem(retval.data.tableVal , temp ,temp);
      s[0] = '\0';
    }
     if(p->strIndexed[i]!=NULL)
    {
      s = strdup(avm_tostring(&p->strIndexed[i]->key));
      // s[sizeof(avm_tostring(&p->strIndexed[i]->key))] = '\0';
      avm_memcell* temp = malloc(sizeof(avm_memcell));
      temp->data.strVal = strdup(s);
      temp->type = string_m;
      avm_tablesetelem(retval.data.tableVal , temp ,temp);
      s[0] = '\0';
    }
  }

}

void libfunc_objecttotalmembers(void)
{
  avm_memcell *tmp = avm_getactual(0);
  retval.data.numVal = (double)tmp->data.tableVal->total;
  retval.type = number_m;
}

void libfunc_objectcopy(void)
{
  retval = *avm_getactual(0);

}

void libfunc_argument(void)
{

  unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
  avm_memcellclear(&retval);
  red();
   p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

  if (!p_topsp)
  {
    avm_error("'totalarguments'called outside a function!");
    retval.type = nill_m;
  }
  else
  {
        if(stack[(int)(p_topsp + AVM_NUMACTUALS_OFFSET + avm_getactual(0)->data.numVal + 1)].type == 0 ){
          retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET + avm_getactual(0)->data.numVal + 1);
          retval.type = number_m;
        }else if(stack[(int)(p_topsp + AVM_NUMACTUALS_OFFSET + avm_getactual(0)->data.numVal + 1)].type == 1){
          retval.data.strVal = stack[(int)(p_topsp + AVM_NUMACTUALS_OFFSET + avm_getactual(0)->data.numVal + 1)].data.strVal;
          retval.type = string_m;
      }
  }
}

void libfunc_strtonum(void)
{
  unsigned n = avm_totalactuals();
  if (n != 1)
    avm_error("one argument (not %d) expected in 'cos'!", n);
  else
  {
    avm_memcellclear(&retval);
    avm_memcell *a = avm_getactual(0);
    retval.type = number_m;
    retval.data.numVal = atoi(a->data.strVal);
    printf("eimai edw stin str %f---------------------------------\n" , retval.data.numVal);
    // if(retval.data.numVal == 0){

    // }
  }
  
}

void libfunc_sqrt(void)
{
    unsigned n = avm_totalactuals();
  if (n != 1)
    avm_error("one argument (not %d) expected in 'sqrt'!", n);
  else
  {
    avm_memcellclear(&retval);
    avm_memcell *a = avm_getactual(0);
    if(a->data.numVal <= 0) 
    {
      retval.type = nill_m;
    }else{
      retval.type = number_m;
      retval.data.numVal = sqrt(a->data.numVal);
    }
  }
}

void libfunc_cos(void)
{
  unsigned n = avm_totalactuals();
  if (n != 1)
    avm_error("one argument (not %d) expected in 'cos'!", n);
  else
  {
    avm_memcellclear(&retval);
    avm_memcell *a = avm_getactual(0);
    retval.type = number_m;
    retval.data.numVal = cos(a->data.numVal *(PI/180));
  }
}

void libfunc_sin()
{
    unsigned n = avm_totalactuals();
  if (n != 1)
    avm_error("one argument (not %d) expected in 'sin'!", n);
  else
  {
    avm_memcellclear(&retval);
    avm_memcell *a = avm_getactual(0);
    retval.type = number_m;
    retval.data.numVal = sin(a->data.numVal *(PI/180));
  }
}


userFunc* consts_get_userfunction_byaddress(int address)
{
  int index = code[address].res->val;
  return consts_get_userfunction(index);
}

int hash_avm(avm_memcell *key)
{
  if(key->type == number_m) 
    return ((int)key->data.numVal%AVM_TABLE_HASHSIZE);
  else if(key->type == string_m){
    int i , index = 0;
    for(i =0 ; i < strlen(key->data.strVal); i++){
      index += (int)key->data.strVal[i];
    }
    return index%AVM_TABLE_HASHSIZE;
  }
   
  else if (key->type == table_m){
    return key->data.tableVal->total%AVM_TABLE_HASHSIZE;
  }else{

    assert(0);
  }
}