struct Stack{
    int lineNo;
    struct Stack* next;
}typedef stack;

 stack* top1;

void printStack() ;

stack * newCommentNode(int lineNo);

void push(int lineNo);

int pop();

int isEmpty();
