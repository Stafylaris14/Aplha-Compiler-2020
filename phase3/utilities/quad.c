#include "quad.h"

#define STARTING_SIZE 1024

#define EXTEND 1024
#define CURR_SIZE (total*sizeof(quad))
#define NEW_SIZE (STARTING_SIZE*sizeof(quad) + CURR_SIZE)
/* extern int yylineno; */



quad *quads = (quad*) 0;
unsigned int total = 0 ;
unsigned int currQuad = 0;

void init_quads()
{
    currQuad = 0;
    quads = malloc(sizeof(quad) * STARTING_SIZE);
    total = STARTING_SIZE;
    for (int i = 0; i < STARTING_SIZE; i++)
    {
        /* quads[i].label = 0; */
        quads[i].arg1 = NULL;
        quads[i].arg2 = NULL;
        quads[i].label = -1;
        quads[i].op = NULL;
        quads[i].result = NULL;
    }

}

void extend_quads()
{
    quad *p = malloc(NEW_SIZE);
    if (quads)
    {
        memcpy(p, quads, total);
        free(quads);
    }
    quads = p;
    total += EXTEND;
    
}

void print_quads()
{
    int i = 0;
    for (i = 0; i < total; i++)
    {
        
        printf("%d (%d)\n", quads[i].label , i);
    }
}

void print_quads_not_empty()
{
    int i = 0;
    for (i = 0; i < total; i++)
    {
        if(quads[i].arg1 !=NULL)
            printf("%d (%d)\n", quads[i].label, i);
    }
}

quad newQuad(iopcode* op , expr* arg1 , expr* arg2 , expr* res)
{
    quad tmp;
    tmp.op = op;
    tmp.arg1 = arg1;
    tmp.arg2 = arg2;
    tmp.result = res;
    tmp.lineno = 10;
    /* kati gia to label */
    return tmp;
}


void emit(iopcode* op , expr* arg1 , expr* arg2 , expr* res)
{
    /* ean den ftanei o xwros kanei extend */
    if(currQuad >= total) extend_quads();
    /* create a new Quad */
    quad tmp = newQuad(op , arg1 , arg2 , res);
    /* add it to array */
    quads[currQuad] = tmp;
    /* increse currQuad with 1 */
    currQuad = currQuad + 1;
}

int main()
{
    init_quads();
    expr* db1 = malloc(sizeof(expr));
    db1->next = NULL;
    db1->boolConst = 1;
     
    emit(ASSIGN , db1 , db1 , db1 );
    print_quads_not_empty();
    printf("AFTER EXTENTION1---------\n");

    printf("%u \n", total);
    return 0;
}
