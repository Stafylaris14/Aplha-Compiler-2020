#include "targetCode.h"

void make_operand(expr *e, vmarg *arg)
{
    expr_t expressionType = e->type;
    arg = malloc(sizeof(vmarg));
    
    switch (expressionType)
    {
        case boolexpr_:
        case assignexp_:
        case newtable_:
        case var_:
        case tableitem_:{
            arg->val = e->sym->offset;  //na to to offset
            switch (e->sym->scope_spase)
            {
                case program_variable:arg->type = global_a; break;
                case function_local : arg->type = local_a; break;
                case formal_argument: arg->type = formal_a; break;
                default:assert(0);
            }
        }
        case constnum_:
            arg->type = number_a;
            arg->val = e->numConst;
            break;
        case constbool_:
            arg->type = constbool_;
            arg->val = e->boolConst;
            break;
        case conststring_:
            arg->type = conststring_;
            arg->val = e->stringConst;
            break;
        case pfunc_:
            arg->type = userFunc_a;
            //arg->val= e->sym-> TODO thelei to taddress leei pou einai mesa sto symbol
            break;
        case lfunc_:
            arg->type = libFunc_a;
            // TODO thelei libfunctions_newused(e->sym->name)
            break;
        case nill_:
            arg->type = nill_a;
            break;
        default:
            assert(0);
            break;
    }
}

 static void avm_initstack(void){
    unsigned i;
  for( i= 0; i < AVM_STACKSIZE; i++){
    AVM_WIPEOUT(stack[i]);
    stack[i].type = undef_m;
  }
}


void avm_tableincrefcounter(avm_table *t){
    ++t->refCounter;
}


void avm_tabledecrefcounter(avm_table *t){
  assert(t->refCounter > 0);
  if(!--t->refCounter) 
    avm_tabledestroy(t);
}


void avm_tablebucketsinit(avm_table_bucket **p){
  unsigned i;
  for(i =0; i < AVM_TABLE_HASHSIZE; i++)
    p[i] = (avm_table_bucket*) 0;
}

avm_table *avm_tablenew(void) {
  avm_table *t = (avm_table*) malloc(sizeof(avm_table));
  AVM_WIPEOUT(*t);

  t->refCounter = t->total = 0;
  avm_tablebucketsinit(t->numIndexed);
  avm_tablebucketsinit(t->strIndexed);

  return t;
}

void avm_tablebucketsdestroy(avm_table_bucket **p){
    unsigned i;
    for(i =0; i < AVM_TABLE_HASHSIZE; ++i,++p){
        avm_table_bucket *b;
        for(*b = *p; b;){
            avm_table_bucket *del =b;
            b = b->next;
            avm_memcellclear(&del->key);
            avm_memcellclear(&del->value);
            free(del);
        }
        p[i] = (avm_table_bucket*) 0;
    } 

}

void avm_tabledestroy(avm_table *t){
  avm_tablebucketsdestroy(t->strIndexed);
  avm_tablebucketsdestroy(t->numIndexed);
  free(t);
}