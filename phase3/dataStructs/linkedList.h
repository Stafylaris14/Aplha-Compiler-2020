#define KWHT "\x1B[37m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



struct alpha_token_t
{
    int lineNo;
    int token_counter;
    char* value;
    char* type;
    char* category;
    char* sub_category;
    struct alpha_token_t *next;
}typedef token;


void insert( token* newNode);

token* createNewNode(int lineNo , int token_counter , char* value , char* type ,char* sub_category, char* category);

void printList();


void red();
void wht();
void grn();
void yel();
void blu();
void cyn();
void mag();
