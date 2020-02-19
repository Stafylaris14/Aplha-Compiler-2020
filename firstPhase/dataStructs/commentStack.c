#include "commentStack.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void printStack(stack* top)
{
    stack* tmp = top;
    while(tmp != NULL){
        fprintf(stderr , "tmp->line = %d\n" , tmp->lineNo);
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

void push(int lineNo , stack* top)
{
    
    if(top == NULL){
        top = newCommentNode(lineNo);
    }else{
        stack* tmp = newCommentNode(lineNo);
        tmp->next = top;
        top =  tmp;
    }
    
    fprintf(stderr , "pushed\n");
    
}


int isEmpty(stack* top)
{
    if(top == NULL)return 1;
    else return 0;
}

int pop(stack* top)
{
    if(isEmpty(top))return -1;
    stack* toPop = top;
    
    top = top->next;
    
    int line = toPop->lineNo;
    free(toPop);
    
    fprintf(stderr , "Poped\n" );
    return line;

}


