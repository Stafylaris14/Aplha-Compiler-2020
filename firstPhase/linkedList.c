#include "linkedList.h"

void red()
{
	fprintf(stderr,"%s", KRED);
}
void wht()
{
	fprintf(stderr,"%s\n", KWHT);
}
void grn()
{
	fprintf(stderr,"%s", KGRN);
}
void yel()
{
	fprintf(stderr,"%s", KYEL);
}
void blu()
{
	fprintf(stderr,"%s", KBLU);
}
void cyn()
{
	fprintf(stderr,"%s", KCYN);
}
void mag()
{
	fprintf(stderr,"%s", KMAG);
}
token* head = NULL , *last = NULL;



token* createNewNode(int lineNo , int token_counter , char* value , char* type , char* category)
{
    token* newNode ;
    newNode = malloc(sizeof(token));
    newNode->lineNo = lineNo;
    newNode->token_counter = token_counter;
    newNode->value = strdup(value);
    newNode->type = type;
    newNode->category = category;
    newNode->next = NULL;
    return newNode;
}


void insert(token* node)
{
    if(head == NULL){
        head = node;
        last = head;
    }else{
        last->next = node;
        last = node;
    }
    grn();
    fprintf(stderr,"added new Node with value: (%s) ..." , node->value);
    wht();
        
}





void printList()
{
    struct alpha_token_t *tmp = head;
    yel();
    fprintf(stderr,"------------- Lexical Analysis -------------\n");
    cyn();
    while(tmp->next != NULL){
        fprintf(stderr ," %d:  #%d (\"%s\") %s <-%s\n",tmp->lineNo,tmp->token_counter,tmp->value,tmp->type,tmp->category);   
        tmp = tmp->next;
    }
    fprintf(stderr,"%s", KWHT);
    
        fprintf(stderr ," %d:  #%d (\"%s\") %s <-%s\n",tmp->lineNo,tmp->token_counter,tmp->value,tmp->type,tmp->category);   
        tmp = tmp->next;
    }
    fprintf(stderr,"%s", KWHT);
    
}








