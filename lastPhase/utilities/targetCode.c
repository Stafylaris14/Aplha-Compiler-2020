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
    case tableitem_:
    {
        arg->val = e->sym->offset; //na to to offset
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
    }
    case constnum_:
        arg->type = number_a;
        arg->val = consts_add_numconst(e->numConst);
        break;
    case constbool_:
        arg->type = constbool_;
        arg->val = e->boolConst;
        break;
    case conststring_:
        arg->type = conststring_;
        arg->val = consts_add_stringconst(e->stringConst);
        break;
    case pfunc_:
        arg->type = userFunc_a;
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
    default:
        assert(0);
        break;
    }
}

void init_const_arrays()
{
    numConsts = malloc(sizeof(int) * CONST_ARR_SIZE);
    stringConsts = malloc(CONST_ARR_SIZE);
    namedLibFuncs = malloc(sizeof(struct userFunc) * CONST_ARR_SIZE);

    for (int i = 0; i < CONST_ARR_SIZE; i++)
    {
        // numConsts[i] = NULL;
        stringConsts[i] = NULL;
        namedLibFuncs[i] = NULL;
    }
}

int consts_add_numconst(int val)
{
    numConsts[numConstSize] = val;
    numConstSize++;
    return numConstSize - 1;
}

int consts_add_stringconst(char *str)
{
    stringConsts[stringConstSize] = strdup(str);
    stringConstSize++;
    return stringConstSize-1;
}

int consts_add_namedLibFuncs(char* funcName)
{
    namedLibFuncs[namedLibFuncsSize] = funcName;
    namedLibFuncsSize++;
    return namedLibFuncsSize-1;
}

//to address einai to quad pou 3ekinaei h sinartisi kai to localsize einai to plithos tws formal arguments
userFunc* newUserFunction(int address , int localsize , char* name)
{
    userFunc* tmp = malloc(sizeof(userFunc));
    tmp->address = address;
    tmp->localsize = localsize;

    tmp->id = strdup(name);


    return tmp;
}


int consts_add_userFunc(userFunc *func)
{
    userFuncs[userFuncSize] = func;
    userFuncSize++;
    return userFuncSize-1;
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
        avm_table_bucket *b;
        for (*b=*p; b;)         //den exw idea! TODO
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