#ifndef MY_STACK_H
#define MY_STACK_H

#include "list_of_tokens.h"

typedef struct my_Stack {
  Token *last;
} Stack;

Stack *init_Stack();

void push_Stack(char *str, Stack *S);
char *pop(Stack *S);
int is_Empty(Stack const *S);
void destroy(Stack *S);

typedef struct my_Stack_double {
  Token_double *last;
} Stack_double;

Stack_double *init_Stack_double();

void push_Stack_double(double value, Stack_double *S);
double pop_Stack_double(Stack_double *S);
void destroy_Stack_double(Stack_double *S);

#endif
