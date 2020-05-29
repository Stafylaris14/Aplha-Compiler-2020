#include "commentStack.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>





void printStack()
{
    // printf("prepei na kanw pring\n" );
    stack* tmp = top1;
    while(tmp != NULL){
      //  fprintf(stderr , "tmp->line  %d\n" , tmp->lineNo);
        tmp = tmp->next;
    }
}
stack* newCommentNode( int lineNo)
{
    stack* tmp = malloc(sizeof(stack));
    tmp->lineNo = lineNo;
    tmp->next = NULL;

    return tmp;
}

void push(int lineNo)
{
    if(top1 == NULL){
        top1 = newCommentNode(lineNo);
    }else{
        stack* tmp = newCommentNode(lineNo);
        tmp->next = top1;
        top1 =  tmp;
    }

    // fprintf(stderr , "pushed synartisi to %d\n",lineNo);

}


int isEmpty()
{
    if(top1 == NULL){return 1;
    //   fprintf(stderr , "ADEIA LISTA\n" );
    }
    else return 0;
}

int pop()
{
    if(isEmpty())return -1;
    stack* toPop = top1;

    top1 = top1->next;

    int line = toPop->lineNo;
    free(toPop);

    // fprintf(stderr , "Poped synartis %d\n",line);
    return line;

}
