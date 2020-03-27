#include "quad.h"

#define STARTING_SIZE 1024

#define EXTEND 1024
#define NEW_SIZE (EXTEND * sizeof(quad) + total)

quad *quads;
double total;

void init_quads()
{
    quads = malloc(sizeof(quad) * STARTING_SIZE);
    total = STARTING_SIZE;
    for (int i = 0; i < STARTING_SIZE; i++)
    {
        /* quads[i].label = 0; */
        quads[i].arg1 = NULL;
        quads[i].arg2 = NULL;
        quads[i].label = -1;
        quads[i].op = NULL;
        quads[i].resault = NULL;
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

int main()
{
    init_quads();
    print_quads();
    extend_quads();
    printf("AFTER EXTENTION1---------\n");
    extend_quads();
    /* print_quads(); */
    printf("%f \n" , total);
    return 0;
}