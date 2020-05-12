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