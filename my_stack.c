#include "my_stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_Empty_Stack_double(Stack_double const *S);

Stack *init_Stack() {
  Stack *S = NULL;
  S = (Stack *)malloc(sizeof(Stack));
  if (S) S->last = NULL;
  return S;
}

void push_Stack(char *str, Stack *S) {
  // char *new_str = (char *)malloc((strlen(str) + 1) * sizeof(char));
  // strcpy(new_str, str);
  if (S) {
    Token *T = init_Token(str);
    if (T) {
      T->next = S->last;
      S->last = T;
    }
  }
}

char *pop(Stack *S) {
  char *str = NULL;
  if (!is_Empty(S)) {
    str = S->last->str;
    Token *T = S->last;
    S->last = S->last->next;
    free(T);
  }
  return str;
}

int is_Empty(Stack const *S) {
  int empty = 1;
  if (S->last) empty = 0;
  return empty;
}

void destroy(Stack *S) {
  if (S) free(S);
}

Stack_double *init_Stack_double() {
  Stack_double *S = NULL;
  S = (Stack_double *)malloc(sizeof(Stack_double));
  if (S) S->last = NULL;
  return S;
}

void push_Stack_double(double value, Stack_double *S) {
  if (S) {
    Token_double *T = init_Token_double(value);
    if (T) {
      T->next = S->last;
      S->last = T;
    }
  }
}

double pop_Stack_double(Stack_double *S) {
  double value = 0;
  if (!is_Empty_Stack_double(S)) {
    value = S->last->value;
    Token_double *T = S->last;
    S->last = S->last->next;
    free(T);
  }
  return value;
}

static int is_Empty_Stack_double(Stack_double const *S) {
  int empty = 1;
  if (S && S->last) empty = 0;
  return empty;
}

void destroy_Stack_double(Stack_double *S) {
  if (S) free(S);
}