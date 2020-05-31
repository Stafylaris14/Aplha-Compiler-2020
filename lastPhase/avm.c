#include "avm.h"
#include "./dataStructs/linkedList.h"

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
    memclear_table,
    0,
    0,
    0,
    0};

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

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

// extern userFunc* avm_getfuncinfo(unsigned address);

typedef double (*arithmetic_func_t)(double x, double y);

typedef unsigned char (*tobool_func_t)(avm_memcell *);
unsigned char number_tobool(avm_memcell *m) { return m->data.numVal != 0; }
unsigned char string_tobool(avm_memcell *m) { return m->data.strVal[0] != 0; }
unsigned char bool_tobool(avm_memcell *m) { return m->data.boolVal; }
unsigned char table_tobool(avm_memcell *m) { return 1; }
unsigned char userfunc_tobool(avm_memcell *m) { return 1; }
unsigned char libfunc_tobool(avm_memcell *m) { return 1; }
unsigned char nil_tobool(avm_memcell *m) { return 0; }
unsigned char undef_tobool(avm_memcell *m)
{
  assert(0);
  return 0;
}

typedef void (*memclear_func_t)(avm_memcell *);

typedef void (*library_func_t)(void);

//mallon 8eloun arxikopoiiishhhhhhh

unsigned totalStringConsts;
char **nameLibfuncs;
unsigned totalNameLibfuncs;
unsigned totalUserFuncs;

tobool_func_t toboolFuncs[] = {
    number_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undef_tobool};

avm_memcell stack[AVM_STACKSIZE];

avm_memcell *avm_translate_operand(vmarg *arg, avm_memcell *reg)
{
  //printf("translate type %d\n", arg->type);
  switch (arg->type)
  {
  case global_a:
    return &stack[AVM_STACKSIZE - 1 - arg->val];
  case local_a:
    return &stack[topsp - arg->val];
  case formal_a:
    // assert(0);
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
    yel();
    reg->type = userfunc_m;
    userFunc *t = consts_get_userfunction(arg->val);
    reg->data.funcVal = t->address;
    printf("miso %d\n" , t->address);
    return reg;
  case libFunc_a:
    reg->type = libfunc_m;
    reg->data.libFuncVal = consts_get_libFunction(arg->val);
    return reg;
  default:
    assert(0);
    break;
  }
}

//GET CONSTS
int consts_get_number(int index)
{
  return numConsts[index];
}

char *consts_get_string(int index)
{
  return stringConsts[index];
}

userFunc *consts_get_userfunction(int index)
{
  return userFuncs[index];
}

char *consts_get_libFunction(int index)
{
  return namedLibFuncs[index];
}

void execute_cycle(void)
{
    mag();
   // printf("to pc einai %d\n" , pc);
    wht();
  if (executionFinished)
    return;
  else if (pc == AVM_ENDING_PC)
  {
    executionFinished = 1;
    return;
  }
  else
  {
    // printf("to pc %d kai ending %d\n",pc,AVM_ENDING_PC);
    assert(pc < AVM_ENDING_PC); //2:	PUSHARG		01(formal)0:x    afto thelouyme!!!!
    instr *instr1 = code + pc;
    cyn();
   // printf("to opeinai %d\n" , instr1->op);
    unsigned oldPC = pc;
    assert(instr1->op >= 0 && instr1->op <= AVM_MAX_INSTRUCTIONS);
    // if (instr1->srcLine)
    //     oldPC = pc;
    printf("instruction %d - opcode %d\n", pc,instr1->op);
    
    (*executeFuncs[instr1->op])(instr1);
    if (pc == oldPC)
      ++pc;
  }
}

void avm_callsaveenvironment(void)
{
  avm_push_envvalue(totalActuals);
  avm_push_envvalue(pc + 1);
  avm_push_envvalue(top + totalActuals + 2);
  avm_push_envvalue(topsp);
}

void execute_funcend(instr *unused)
{
  printf("eimai stin funcend\n");
  unsigned oldTop = top;
  top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
  pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
  topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
  while (oldTop++ <= top)
    avm_memcellclear(&stack[oldTop]);
}

void avm_dec_top(void)
{
  if (!top)
  {
    avm_error("stack overflow");
    executionFinished = 1;
  }
  else
    --top;
}

void avm_push_envvalue(unsigned val)
{
  stack[top].type = number_m;
  stack[top].data.numVal = val;
  avm_dec_top();
}

library_func_t avm_getlibraryfunc(char *id)
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

unsigned avm_totalactuals(void)
{
  return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell *avm_getactual(unsigned i)
{
  assert(i < avm_totalactuals());
  return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

void libfunc_print(void)
{
  unsigned n = avm_totalactuals();
  unsigned i;
  //printf("kane printsss\n");
  for (i = 0; i < n; ++i)
  {
    char *s = avm_tostring(avm_getactual(i));
    printf("kane printsss %s\n", s);
    grn();
    puts(s);
    wht();
    free(s);
  }
}

void avm_registerlibfunc(char *id, library_func_t addr)
{
  librarys[number_of_lib++] = addr;
}

void libfunc_typeof(void)
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

void libfunc_totalarguments(void)
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

double add_impl(double x, double y) { return x + y; }

double sub_impl(double x, double y) { return x - y; }

double mul_impl(double x, double y) { return x * y; }

double div_impl(double x, double y)
{
  printf("tsekarw g error\n");
  return x / y;
}

double mod_impl(double x, double y)
{
  printf("tsekarw g error\n");
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

void execute_arithmetic(instr *instr)
{
  avm_memcell *lv = avm_translate_operand(instr->res, (avm_memcell *)0);
  avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
  avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);
  printf("eimai edw s lew asset\n");
  // assert(lv && (&stack[0] <= lv && &stack[top] > lv || lv == &retval));
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
    printf("se blepw %f kai %f apotelesma %f\n", rv1->data.numVal, rv2->data.numVal, lv->data.numVal);
  }
}

unsigned char avm_tobool(avm_memcell *m)
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
  }
}

void avm_tableincrefcounter(avm_table *t)
{
  ++t->refCounter;
}

void avm_tabledecrefcounter(avm_table *t)
{
  assert(t->refCounter > 0);
  if (!--t->refCounter)
    avm_tabledestroy(t);
}

void avm_tablebucketsinit(avm_table_bucket **p)
{
  unsigned i;
  for (i = 0; i < AVM_TABLE_HASHSIZE; i++)
    p[i] = (avm_table_bucket *)0;
}

avm_table *avm_tablenew(void)
{
  avm_table *t = (avm_table *)malloc(sizeof(avm_table));
  AVM_WIPEOUT(*t);

  t->refCounter = t->total = 0;
  avm_tablebucketsinit(t->numIndexed);
  avm_tablebucketsinit(t->strIndexed);

  return t;
}

void avm_tablebucketsdestroy(avm_table_bucket **p)
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

void avm_tabledestroy(avm_table *t)
{
  avm_tablebucketsdestroy(t->strIndexed);
  avm_tablebucketsdestroy(t->numIndexed);
  free(t);
}

void execute_if_eq(instr *instr)
{
  puts("eimai if eq");
  assert(instr->res->type == label_a);

  avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
  avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);

  int result = 0;

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
    printf("av1 %d kai av2 %d\n",rv1->data.boolVal,rv2->data.boolVal);
    result = (avm_tobool(rv1) == avm_tobool(rv2));
  }
  else if (rv1->type != rv2->type)
    avm_error("%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
  else
  {
    if (rv1->type == string_m)
      result = !strcmp(rv1->data.strVal, rv2->data.strVal);
    else if (rv1->type == number_m)
      result = rv1->data.numVal == rv2->data.numVal;
    else if (rv1->type == userfunc_m)
      result = rv1->data.funcVal == rv2->data.funcVal;
    else if (rv1->type == libfunc_m)
      result = !strcmp(rv1->data.libFuncVal, rv2->data.libFuncVal);
    else if (rv1->type == table_m)
      result = rv1->data.tableVal == rv2->data.tableVal;
  }
  printf("kalimeres me jumo %d kai exe exe %d\n",result,instr->res->val);
  
  if(result == 1){
    printf("allazw pc re manm \n");
    pc = instr->res->val;
  }

  // if (!executionFinished && result){
  //   red();
  //   printf("panta\n");
  //   pc = instr->res->val;
  // }
}//////////////////////////////////////////////////////////////////////////////

void execute_tablecreate(instr *instr)
{
  avm_memcell *lv = avm_translate_operand(instr->res, (avm_memcell *)0);

  assert(lv && (&stack[top] <= lv && &stack[top] > lv || lv == &retval));

  avm_memcellclear(lv);
  lv->type = table_m;
  lv->data.tableVal = avm_tablenew();
  avm_tableincrefcounter(lv->data.tableVal);
}

avm_memcell *avm_tablegetelem(avm_memcell *key, avm_memcell *i)
{
  //den 3erw ti fasei prepei na to doume
  printf("ftia3imoooooo\n");
}

void avm_tablesetelem(avm_memcell *key, avm_memcell *value, avm_memcell *cur)
{
  printf("ftia3imoooooo\n");
  //den 3erw ti fasei prepei na to doume
}

void execute_tablegetelem(instr *instr)
{

  avm_memcell *lv = avm_translate_operand(instr->res, (avm_memcell *)0);
  avm_memcell *t = avm_translate_operand(instr->arg1, (avm_memcell *)0);
  avm_memcell *i = avm_translate_operand(instr->arg2, &ax);

  assert(lv && (&stack[top] <= lv && &stack[top] > lv || lv == &retval));
  assert(t && &stack[top] <= t && &stack[top] > t);
  assert(i);

  avm_memcellclear(lv);
  lv->type = nill_m;

  if (t->type != table_m)
  {
    avm_error("illegal use of type %s as table!", typeStrings[t->type]);
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

void execute_tablesetelem(instr *instr)
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

void memclear_string(avm_memcell *m)
{
 // assert(m->data.strVal);
  free(m->data.strVal);
}

void memclear_table(avm_memcell *m)
{
  assert(m->data.tableVal);
  avm_tabledecrefcounter(m->data.tableVal);
}

void avm_memcellclear(avm_memcell *m)
{
  if (m->type != undef_m)
  {
    memclear_func_t f = memclearFuncs[m->type];
    if (f)
      (*f)(m);
    m->type = undef_m;
  }
}

void avm_warning(char *format, ...)
{
  cyn();
  printf("AVM WARNING %s\n", format);
  wht();
}

void execute_assign(instr *instr)
{
  

  avm_memcell *lv = avm_translate_operand(instr->res, (avm_memcell *)0);
  avm_memcell *rv = avm_translate_operand(instr->arg1, &ax);

  grn();
  printf("lv eeeeeeeeeeeeeeeeeeeee .type == %d , rv.type  == %d\n" ,lv->type, rv->data.boolVal );
  wht();
  //na dw ligo to assert
  //assert(lv && ((&stack[AVM_STACKENV_SIZE] >= lv && lv > &stack[top]) || lv == &retval));
  assert(rv);

  avm_assign(lv, rv);
}

void avm_assign(avm_memcell *lv, avm_memcell *rv)
{

  if (lv == rv)
    return;
  if (lv == NULL)
    printf("TO LV EINAI NULL!!!!\n");
  if (lv->type == table_m && rv->type == table_m && lv->data.tableVal == rv->data.tableVal)
    return;
  if (rv->type == undef_m)
    avm_warning("assigning from 'undef' content!");

  avm_memcellclear(lv);

  memcpy(lv, rv, sizeof(avm_memcell));
  //printf("eimai edw lv %f\n",lv->data.numVal);
  if (lv->type == string_m)
    lv->data.strVal = strdup(rv->data.strVal);
  else if (lv->type == table_m)
    avm_tableincrefcounter(lv->data.tableVal);
}

void avm_error(char *format, ...)
{
  red();
  printf("AVM ERROR %s\n", format);
  wht();
}

char *avm_tostring(avm_memcell *m)
{
  mag();
  printf("memcels se prins ------------ type %d\n", m->type);
  wht();
  assert(m->type >= 0 && m->type <= undef_m);
  return (*tostringFuncs[m->type])(m);
}

void execute_call(instr *instr)
{
  // puts("eimai stin call");
  avm_memcell *func = avm_translate_operand(instr->arg1, &ax);
  assert(func);
  avm_callsaveenvironment();
  

  switch (func->type)
  {
  case userfunc_m:
  {
    pc = func->data.funcVal;
    yel();
    printf("to func->data.funcVal einai %d\n" , func->data.funcVal);
    wht();
    assert(pc < AVM_ENDING_PC);
    yel();
    printf("%d\n" ,code[pc].op);
    assert(code[pc].op == enterfunc_v);
    break;
  }
  case string_m:
    avm_calllibfunc(func->data.strVal);
    break;
  case libfunc_m:
    printf("eimai edw!!!! %s\n", func->data.libFuncVal);
    avm_calllibfunc(func->data.libFuncVal);
    break;
  default:
  {
    char *s = avm_tostring(func);
    avm_error("call: cannot bind '%s' to function!", s);
    free(s);
    executionFinished = 1;
  }
  }
}

void execute_funcstart(instr *instr)
{
  printf("eimai stin funcstart\n");
  avm_memcell *func = avm_translate_operand(instr->arg1, &ax);

  assert(pc == func->data.funcVal);
  assert(func);

  totalActuals = 0;
  userFunc *funcInfo = consts_get_userfunction(pc);
  topsp = top;
  top = top - funcInfo->localsize;
}

unsigned avm_get_envvalue(unsigned i)
{

  //assert(stack[i].type == number_m);

  unsigned val = (unsigned)stack[i].data.numVal;

  assert(stack[i].data.numVal == ((double)val));

  return val;
}

void avm_calllibfunc(char *funcName)
{

  library_func_t f = avm_getlibraryfunc(funcName);

  if (!f)
  {
    avm_error("unsupported lib func %s called ! ", funcName);
    executionFinished = 1;
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

void execute_param(instr *instr)
{
  red();
  printf("eimai stin param kai to type tou instr einia %d\n" , instr->arg1->type);
  wht();
  avm_memcell *arg = avm_translate_operand(instr->arg1, &ax);
  red();
  printf("%f\n", arg->data.numVal);
  wht();
  assert(arg);
  grn();
  // printf("eimai mesa stin param %f \n" , arg->data.numVal );
  avm_assign(&stack[top], arg);
  ++totalActuals;
  avm_dec_top();
}

char *number_tostring(avm_memcell *kati)
{
  char *res = malloc(sizeof(char) * 200);
  sprintf(res, "%f", kati->data.numVal);
  //printf("gamienaui %s den gamiemai\n", res,strdup(kati->data.strVal));
  //printf("giati edw ??\n");
  return res;
  //8elei ftia3imo
}

char *string_tostring(avm_memcell *kati)
{
  //8elei ftia3imo alla mporei k extern
  char *res = malloc(sizeof(char) * 200);
  sprintf(res, "%s\n", kati->data.strVal);
  // printf("gamienaui %s den gamiemai\n", res);
  return res;
}

char *bool_tostring(avm_memcell *kati)
{
  char *res;
  if (kati->data.boolVal == 1)
    res = "true";
  else
    res = "false";

  return res;
  //isow 8elei exter
}

char *table_tostring(avm_memcell *kati)
{
}

char *userfunc_tostring(avm_memcell *kati)
{
}

char *libfunc_tostring(avm_memcell *kati)
{
}

char *nil_tostring(avm_memcell *kati) {}

char *undef_tostring(avm_memcell *kati) {}

void avm_initialize(void)
{
  //krataw xwro gia tis global

  top = AVM_STACKSIZE;
  topsp = AVM_STACKSIZE;
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
  else if (rv1->type != rv2->type)
    avm_error("%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
  else
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
  else if (rv1->type != rv2->type)
    avm_error("%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
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
    
  printf("eimai sto greatew kai rv1 type %d kai result (%d) kai jump %d\n",rv1->type,result,instr->res->val);
  wht();
  
  if (!executionFinished && result)
  {
       red();
      printf("pernaw edww\n");
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
    grn();
    //printf("mpika sto exec finished\n");
  }
   // printf("to pc einai prin %d\n" , pc);
    pc = instr->res->val;
    //printf("to pc einai meta %d\n" , pc);
    wht();
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

  FILE *fp = fopen("instructions", "rb");

  fread(&codeSize, sizeof(int), 1, fp);
  char buffer[10];
  code = malloc(sizeof(instr) * codeSize);
  //code
  int i;
  for (i = 0; i < codeSize; i++)
  {
    // code[i] = malloc(sizeof(instr));
    fread(&code[i], sizeof(instr), 1, fp);
    printf("--- code[%d] : %d \n", i, code[i].op);
  }
  // consts
  // num
  const_numbers = malloc(sizeof(numConstSize));
  for (i = 0; i < numConstSize; i++)
  {
    fread(&const_numbers[i], sizeof(int), 1, fp);
  }

  //strings
  const_strings = malloc(sizeof(char *) * stringConstSize);
  for ( i = 0; i < stringConstSize; i++)
  {
    fread(&const_strings[i], sizeof(char *), 1, fp);
  }

  //lib functions

  library_functions = malloc(sizeof(char *) * namedLibFuncsSize);

  for (i = 0; i < namedLibFuncsSize; i++)
  {
    fread(&library_functions, sizeof(char *), 1, fp);
  }

  //userfuncs
  userFunctions = malloc(sizeof(userFunc) * userFuncSize);
    yel();
    printf("%d\n" , userFuncSize);
  for (i = 0; i < userFuncSize; i++){
    fread(&userFunctions, sizeof(userFunc), 1, fp);
  }

  fclose(fp);
}

// stringConstss = malloc(sizeof(char*) * totalStringConstss);
// for(i =0; i < totalStringConstss; i++){
//   //fread(&len,sizeof(size_t),1,tester);
//   fread(&stringConstss[i],sizeof(char*),1,tester);
// }

void libfunc_input()
{
}

void libfunc_objectmemberkeys()
{
}

void libfunc_objecttotalmembers()
{
}

void libfunc_objectcopy()
{
}

void libfunc_argument()
{
}

void libfunc_strtonum()
{
}

void libfunc_sqrt()
{
}

void libfunc_cos()
{
}

void libfunc_sin()
{
}



void print_stack(){
  cyn();
  printf("----------type---------data\n\n");
  int i;
  for(i = AVM_STACKSIZE; i < AVM_STACKSIZE - pc; i--)
  {
    printf("|       %d      " , stack[i].type);

    switch (stack[i].type)
    {
    case number_m:
      printf("%f \n" , stack[i].data.numVal);
      break;
    case string_m:
      printf("%s\n" , stack[i].data.strVal);
      break;
    case bool_m:
      if(stack[i].data.boolVal) printf("true\n");
      else printf("false\n");
      break;
    case table_m:
      printf("table\n");
      break;
    case userfunc_m:
      printf("userFunc\n");
      break;
    case libfunc_m:
      printf("libfunc\n");
      break;
    case nill_m:
      printf("nilll\n");
      break;
    case undef_m:
      printf("undeff\n");
      break;
    default:
      break;
    }

  }
  printf("-------------------------\n");
}