#include "avm.h"


  extern int *numConsts;
  extern int numConstSize ;
  extern char **stringConsts;
  extern int stringConstSize;
  extern char **namedLibFuncs;
  extern int namedLibFuncsSize;
  extern struct userFunc *userFuncs[CONST_ARR_SIZE];
  extern int userFuncSize ;




avm_memcell *avm_translate_operand(vmarg *arg, avm_memcell *reg)
{
    switch (arg->type)
    {
    case global_a: //TODO
        break;
    case local_a: //TODO
    case formal_a: //TODO
    case retval_a: //TODO
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

// yo black P kai pali tha sas parw to kefali vre arxidia
//pinw oli mera fouda exw varethei ta idia kai ta idia











// static void avm_initstack(void)
// {
//     unsigned i;
//     for (i = 0; i < AVM_STACKSIZE; i++)
//     {
//         AVM_WIPEOUT(stack[i]);
//         stack[i].type = undef_m;
//     }
// }

// void avm_tableincrefcounter(avm_table *t)
// {
//     ++t->refCounter;
// }

// void avm_tabledecrefcounter(avm_table *t)
// {
//     assert(t->refCounter > 0);
//     if (!--t->refCounter)
//         avm_tabledestroy(t);
// }

// void avm_tablebucketsinit(avm_table_bucket **p)
// {
//     unsigned i;
//     for (i = 0; i < AVM_TABLE_HASHSIZE; i++)
//         p[i] = (avm_table_bucket *)0;
// }

// avm_table *avm_tablenew(void)
// {
//     avm_table *t = (avm_table *)malloc(sizeof(avm_table));
//     AVM_WIPEOUT(*t);

//     t->refCounter = t->total = 0;
//     avm_tablebucketsinit(t->numIndexed);
//     avm_tablebucketsinit(t->strIndexed);

//     return t;
// }

// void avm_tablebucketsdestroy(avm_table_bucket **p)
// {
//     unsigned i;
//     for (i = 0; i < AVM_TABLE_HASHSIZE; ++i, ++p)
//     {
//         avm_table_bucket *b;
//         for (*b = *p; b;) //den exw idea! TODO
//         {
//             avm_table_bucket *del = b;
//             b = b->next;
//             avm_memcellclear(&del->key);
//             avm_memcellclear(&del->value);
//             free(del);
//         }
//         p[i] = (avm_table_bucket *)0;
//     }
// }

// void avm_tabledestroy(avm_table *t)
// {
//     avm_tablebucketsdestroy(t->strIndexed);
//     avm_tablebucketsdestroy(t->numIndexed);
//     free(t);
// }