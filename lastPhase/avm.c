#include "avm.h"

#define AVM_STACKSIZE 4096
#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))
#define AVM_TABLE_HASHSIZE 211

extern int *numConsts;
extern int numConstSize ;
extern char **stringConsts;
extern int stringConstSize;
extern char **namedLibFuncs;
extern int namedLibFuncsSize;
extern struct userFunc *userFuncs[CONST_ARR_SIZE];
extern int userFuncSize ;


unsigned char executionFinished = 0 ;
unsigned pc = 0;
unsigned currLine = 0;
unsigned codeSize = 0;
instruction *code = (instruction*)0;
#define AVM_ENDING_PC codeSize

unsigned totalActuals = 0;

typedef void (*library_func_t) (void);

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

typedef double(*arithmetic_func_t)(double x,double y);

typedef unsigned char(*tobool_func_t)(avm_memcell*);
typedef unsigned char(*tobool_func_t)(avm_memcell*);
unsigned char number_tobool(avm_memcell* m){return m->data.numVal !=0;}
unsigned char string_tobool(avm_memcell* m){return m->data.strVal[0] !=0;}
unsigned char bool_tobool(avm_memcell* m){return m->data.boolVal;}
unsigned char table_tobool(avm_memcell* m){return 1;}
unsigned char userfunc_tobool(avm_memcell* m){return 1;}
unsigned char libfunc_tobool(avm_memcell* m){return 1;}
unsigned char nil_tobool(avm_memcell* m){return 0;}
unsigned char undef_tobool(avm_memcell* m){assert(0); return 0;}


//mallon 8eloun arxikopoiiishhhhhhh

unsigned totalStringConsts;
char** nameLibfuncs ;
unsigned totalNameLibfuncs ;
unsigned totalUserFuncs ;



tobool_func_t toboolFuncs[]={
  number_tobool,
  string_tobool,
  bool_tobool,
  table_tobool,
  userfunc_tobool,
  libfunc_tobool,
  nil_tobool,
  undef_tobool
};

avm_memcell stack[AVM_STACKSIZE];

avm_memcell *avm_translate_operand(vmarg *arg, avm_memcell *reg)
{
    switch (arg->type)
    {
    case global_a: 
        return &stack[AVM_STACKSIZE-1-arg->val];
    case local_a:
        return &stack[topsp-arg->val];
    case formal_a: 
        return &stack[topsp+AVM_STACKENV_SIZE+1+arg->val];
    case retval_a: 
        return &retval;
    case number_a: reg->type = number_m; reg->data.numVal =consts_get_number(arg->val);return reg; 
    case bool_a: reg->type = bool_m; reg->data.numVal =arg->val;return reg; 
    case string_a:reg->type = string_m; reg->data.strVal =consts_get_string(arg->val);return reg; 
    case userFunc_a: reg->type = userfunc_m; reg->data.funcVal = arg->val;return reg;
    case libFunc_a: reg->type = libfunc_m; reg->data.libFuncVal = arg->val;return reg;
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

char* consts_get_string(int index)
{
    return stringConsts[index];
}

userFunc* consts_get_userfunction(int index)
{
    return userFuncs[index];
}

char* consts_get_libFunction(int index)
{
    return namedLibFuncs[index];
}

  void execute_cycle(void){
  if(executionFinished)
    return;
  else
   if(pc == AVM_ENDING_PC){
        executionFinished=1;
        return;
    }else {
        assert(pc<AVM_ENDING_PC);
        instruction* instr = code+ pc;
        assert(instr->opcode>=0 && instr->opcode<= AVM_MAX_INSTRUCTIONS);
        if(instr->srcLine)
            currLine=instr->srcLine;
        unsigned oldPC = pc;
        (*executeFuncs[instr->opcode])(instr);
        if(pc == oldPC)
            ++pc;
    }
  }



void avm_callsaveenvironment(void){
  avm_push_envvalue(totalActuals);
  avm_push_envvalue(pc+1);
  avm_push_envvalue(top+totalActuals+2);
  avm_push_envvalue(topsp);
}


void execute_funcexit(instruction* unused){
  unsigned oldTop= top;
  top= avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
  pc= avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
  topsp= avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
  while(oldTop++<=top)
    avm_memcellclear(&stack[oldTop]);
}




library_func_t avm_getlibraryfunc(char* id){
 //aplo hasing leei ftia3imooooooooooooooooooo
 printf("ftia3imoooooo\n");
}

void avm_calllibfunc(char* id){
  library_func_t f = avm_getlibraryfunc(id);
  if(!f){
    avm_error("unsupported lib func %s called!",id);
    executionFinished = 1;
  }else{
    topsp = top;
    totalActuals = 0;
    (*f)();
    if(!executionFinished)
      execute_funcexit((instruction*) 0);
  }
}

unsigned avm_totalactuals(void){
  return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactual(unsigned i){
  assert(i < avm_totalactuals());
  return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

void libfunc_print(void){
  unsigned n = avm_totalactuals();
  unsigned i;
  for(i = 0; i<n; ++i){
  char* s= avm_tostring(avm_getactual(i));
  puts(s);
  free(s);
  }
}


void avm_registerlibfunc(char* id,library_func_t addr){
  //kanei add ftia3imooooooooooooooooooooooo
  printf("ftia3imoooooo\n");
}


void libfunc_typeof(void){
  unsigned n = avm_totalactuals();
  if(n != 1)
    avm_error("one argument (not %d) expected in 'typeof'!",n);
  else{
    avm_memcellclear(&retval);
    retval.type=string_m;
    retval.data.strVal=strdup(typeStrings[avm_getactual(0)->type]);
  }
}

void libfunc_totalarguments(void){
  unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
  avm_memcellclear(&retval);
  
  if(!p_topsp){
    avm_error("'totalarguments'called outside a function!");
    retval.type = nil_m;
  }else{
      retval.type = number_m;
      retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
  }
}

double add_impl(double x,double y){return x + y;}

double sub_impl(double x,double y){return x - y;}

double mul_impl(double x,double y){return x * y;}

double div_impl(double x,double y){
    printf("tsekarw g error\n");
    return x/y;
}

double mod_impl(double x,double y){
    printf("tsekarw g error\n"); 
    return ((unsigned)x)%((unsigned)y);
}

arithmetic_func_t arithmeticFuncs[]={ //na balo sto header
  add_impl,
  sub_impl,
  mul_impl,
  div_impl,
  mod_impl
};

void execute_arithmetic(instruction *instr){
  avm_memcell* lv = avm_translate_operand(instr->result,(avm_memcell*) 0);
  avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
  avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);
  
  assert(lv && (&stack[0] <= lv && &stack[top] > lv || lv==&retval));
  assert(rv1 && rv2);
  
  if(rv1->type != number_m || rv2->type != number_m){
    avm_error("not a number in arithmetic!\n");
    executionFinished = 1;
  }else{
      arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
      avm_memcellclear(lv);
      lv->type = number_m;
      lv->data.numVal = (*op)(rv1->data.numVal , rv2->data.numVal);
  }
}


unsigned char avm_tobool(avm_memcell* m){
  assert(m->type>=0 && m->type < undef_m);
  return (*toboolFuncs[m->type])(m);
}

static void avm_initstack(void)
{
    unsigned i;
    for (i = 0; i < AVM_STACKSIZE; i++){
        AVM_WIPEOUT(stack[i]);
        stack[i].type = undef_m;
    }
}

void avm_tableincrefcounter(avm_table *t)
{
    ++t->refCounter;
}


void avm_tabledecrefcounter(avm_table *t){
    assert(t->refCounter > 0);
    if (!--t->refCounter)
        avm_tabledestroy(t);
}

void avm_tablebucketsinit(avm_table_bucket **p){
    unsigned i;
    for (i = 0; i < AVM_TABLE_HASHSIZE; i++)
        p[i] = (avm_table_bucket *)0;
}

avm_table *avm_tablenew(void){
  avm_table *t = (avm_table*) malloc(sizeof(avm_table));
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
        avm_table_bucket *b;
        for (*b = *p; b;) //den exw idea! TODO
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

void execute_jeq(instruction* instr){
  
  assert(instr->result->type == label_a);
  
  avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
  avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);
  
  unsigned char result =0 ;
  
  if(rv1->type == undef_m || rv2->type == undef_m){
    avm_error("'undef'involved in equality!");
  }else if (rv1->type == nil_m || rv2->type == nil_m){
    result = rv1->type == nil_m && rv2->type == nil_m;
  }else if(rv1->type == bool_m || rv2->type == bool_m){
    result = (avm_tobool(rv1)==avm_tobool(rv2));
  }else
  if(rv1->type!=rv2->type)avm_error("%s == %s is illegal!",typeStrings[rv1->type],typeStrings[rv2->type]);
  else {
    //equality check with dispacht kanwwwwwwwwwwwwwwwwwwwwwwww
    printf("8elei elenxousssssssss\n");
  }
  if(!executionFinished && result)
    pc=instr->result.val;
}

void execute_newtable(instruction* instr){
  avm_memcell* lv = avm_translate_operand(instr->result,(avm_memcell*) 0);
  
  assert(lv && (&stack[top] <= lv && &stack[top] > lv || lv==&retval));
  
  avm_memcellclear(lv);
  lv->type =table_m;
  lv->data.tableVal = avm_tablenew();
  avm_tableincrefcounter(lv->data.tableVal);
}




avm_memcell* avm_tablegetelem(avm_memcell *key){
    //den 3erw ti fasei prepei na to doume
    printf("ftia3imoooooo\n");

}

void avm_tablesetelem(avm_memcell *key,avm_memcell *value){
printf("ftia3imoooooo\n");
    //den 3erw ti fasei prepei na to doume
}

void execute_tablegetelem(instruction* instr){
  
  avm_memcell* lv = avm_translate_operand(instr->result , (avm_memcell*) 0);
  avm_memcell* t = avm_translate_operand(instr->arg1 , (avm_memcell*) 0);
  avm_memcell* i = avm_translate_operand(instr->arg2 , &ax);
  
  assert(lv && (&stack[top] <= lv && &stack[top]> lv || lv==&retval));
  assert(t && &stack[top] <= t && &stack[top] > t);
  assert(i);
  
  avm_memcellclear(lv);
  lv->type = nil_m;
  
  if(t->type != table_m){
    avm_error("illegal use of type %s as table!",typeStrings[t->type]);
  }else{
    avm_memcell* content = avm_tablegetelem(t->data.tableVal, i);
    if(content){
      avm_assign(lv,content);
    }else{
      char* ts = avm_tostring(t);
      char* is = avm_tostring(i);
      avm_warning("%s[%s] not found ! ",ts ,is);
       free(ts);
       free(is);
    }
  }
}

void execute_tablesetelem(instruction* instr){
  avm_memcell* t = avm_translate_operand(instr->result , (avm_memcell*) 0);
  avm_memcell* i = avm_translate_operand(instr->arg1 , &ax);
  avm_memcell* c = avm_translate_operand(instr->arg2 , &bx);
  
  assert(t && &stack[top]<= t && &stack[AVM_STACKSIZE]> t);
  assert(i && c);
  
  if(t->type != table_m) 
    avm_error("illegal use of type %s as table!", typeStrings[t->type]);
  else{
    avm_tablesetelem(t->data.tableVal,i,c);
  }
}



void avm_memcellclear(avm_memcell* m){
    
    //8elei ilopoihsh
    printf("ftia3imoooooo\n");

}

//diale3i paragogi telikou kwdika //////////////////


unsigned consts_newstring(char* s){
    //8elei ftia3imo
    printf("ftia3imoooooo\n");
}


unsigned consts_newnumber(double n){
    //fti3imoo
    printf("ftia3imoooooo\n");
}


unsigned libfuncs_newused(char* s){
       printf("ftia3imoooooo\n");
     //ftia3imoo
}

unsigned userfuncs_newfunc(item* sym){
    printf("ftia3imoooooo\n");
     //ftia3imoo
}

void make_operand(expr* e,vmarg* arg){
  printf("8elei ftia3imoooo\n");
  if(!e) return;
  //8elei kapoio elenxo mallon
  switch(e->type){
    case var_e : {
    break;}
    case tableitem_e:{
          break;}
    case arithexpr_e:{break;}
    case boolexpr_e: {break;}
    case newtable_e: {
        assert(e->sym);
        arg->val = e->sym->offset;
        switch (e->sym->space) {
          case programvar : arg->type = global_a; break;
          case functionlocal : arg->type = local_a; break;
          case formalarg : arg->type = formal_a; break;
          default: assert(0);
        }
        break;
    }
    //8elei k alla case edw mallon
    /*Constants*/
    case constbool_e: {
      arg->val = e->boolConst;
      arg->type = bool_a; break;
      }
    case conststring_e : {
      arg->val = consts_newstring(e->strConst);
      arg->type = string_a; break;
    }
    case constnum_e: {
      arg->val = consts_newnumber(e->numConst);
      arg->type = number_a; break;
    }
    //edw k allo case mallon
    case nil_e: arg->type = nil_a; break;
    /*Functions*/
    case programfunc_e: {
      arg->type = userfunc_a;
      arg->val = userfuncs_newfunc(e->sym);
      //8elei kati g to name mallon
      break;
    }
    case libraryfunc_e: {
      arg->type = libfunc_a;
      arg->val = libfuncs_newused(e->sym->name);
      //mallon 8elei katig name edw
      break;
    }
    default : assert(0);
  }
}


void make_numberoperand(vmarg* arg,double val){
  arg->val = consts_newnumber(val);
  arg->type = number_a;
}
void make_booloperand(vmarg* arg,unsigned val){
  arg->val = val;
  arg->type = bool_a;
}
void make_retvaloperand(vmarg* arg){
  arg->type = retval_a;
}


incomplete_jump* ij_head = (incomplete_jump*) 0;

unsigned ij_total = 0;

void add_incomplete_jump(unsigned instrNo,unsigned iaddress);

void telos_generate(vmopcode op,quad *quad){
    printf('8elei dtia3imoooo\n');
    instruction *t;
    t->opcode = op;

  make_operand(quad->arg1,t->arg1);
  make_operand(quad->arg2,t->arg2);
  make_operand(quad->result,t->result);
  quad->taddress = nextinstructionlabel();//mallon dn xreiazete
}


void generate_ADD(quad* quad){telos_generate(add,quad);}
void generate_SUB(quad* quad){telos_generate(sub,quad);}
void generate_MUL(quad* quad){telos_generate(mul,quad);}
void generate_DIV(quad* quad){telos_generate(div,quad);}
void generate_MOD(quad* quad){telos_generate(mod,quad);}
void generate_NEWTABLE(quad* quad){telos_generate(newtable,quad);}
void generate_TABLEGETELM(quad* quad){telos_generate(tablegetelem,quad);}
void generate_TABLESETELM(quad* quad){telos_generate(tablesetelem,quad);}
void generate_ASSIGN(quad* quad){telos_generate(assign,quad);}
void generate_NOP(quad* quad){telos_generate(nop,quad);}

//prepeu na einai malakiew ta parapanw na ta exeiw kanei esy sti 4a fasi