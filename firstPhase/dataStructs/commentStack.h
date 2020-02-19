struct Stack{
    int lineNo;
    struct Stack* next;
}typedef stack; 



stack * newCommentNode(int lineNo);

void push(int lineNo , stack* head);

int pop(stack* head);

int isEmpty(stack *head);