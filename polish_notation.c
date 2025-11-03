#include "polish_notation.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "check.h"
#include "list_of_tokens.h"
#include "my_stack.h"

static int Priority(char value);
static int Operations(char ch, Stack_double *S);
static int Functions(char const *str, Stack_double *S);

Token *Token_in_Polish_notation(Token *old_T) {
  Token *new_T = NULL;
  Stack *S = NULL;
  S = init_Stack();
  char expect = EVRTHNG;
  while (old_T) {
    if (NUMBER(old_T->str[0]) || old_T->str[0] == 'x') {
      expect = NOTHING;
      add_Token(old_T->str, &new_T);
    } else if (OPERATOR(old_T->str[0]) || FUNCTION(old_T->str[0])) {
      if (expect == EVRTHNG && UNARY(old_T->str[0])) {
        old_T->str[0] = '~';
      }
      while (!is_Empty(S) && !FUNCTION(S->last->str[0]) &&
             Priority(old_T->str[0]) < Priority(S->last->str[0]))
        add_Token(pop(S), &new_T);
      push_Stack(old_T->str, S);
      expect = EVRTHNG;
    } else if (old_T->str[0] == ')') {
      while (!FUNCTION(S->last->str[0])) {
        add_Token(pop(S), &new_T);
      }
      if (S->last->str[0] != '(') {
        add_Token(pop(S), &new_T);
      } else if (!is_Empty(S)) {
        pop(S);
      }
    }
    old_T = old_T->next;
  }
  while (!is_Empty(S)) add_Token(pop(S), &new_T);
  destroy(S);
  return new_T;
}

int Polish_notation_calculations(Token *T, double x, double *result) {
  int error = 0;
  Stack_double *S = NULL;
  S = init_Stack_double();
  while (S && T && !error) {
    if (NUMBER(T->str[0])) {
      push_Stack_double(atof(T->str), S);
    } else if (T->str[0] == 'x') {
      push_Stack_double(x, S);
    } else {
      error = Operations(*(T->str), S);
    }
    if (!error) error = Functions(T->str, S);
    T = T->next;
  }
  if (S) {
    *result = pop_Stack_double(S);
  }
  destroy_Stack_double(S);
  return error;
}

static int Priority(char value) {
  int result = 0;
  switch (value) {
    case '+':
    case '-':
      result = 1;
      break;
    case '*':
    case '~':
      result = 2;
      break;
    case '/':
      result = 3;
      break;
    case '^':
      result = 4;
      break;
    default:
      result = 5;
      break;
  }
  return result;
}

static int Operations(char ch, Stack_double *S) {
  int error = 0;
  double value1 = 0, value2 = 0;
  switch (ch) {
    case '~':
      push_Stack_double(-pop_Stack_double(S), S);
      break;
    case '+':
      push_Stack_double(pop_Stack_double(S) + pop_Stack_double(S), S);
      break;
    case '*':
      push_Stack_double(pop_Stack_double(S) * pop_Stack_double(S), S);
      break;
    case '-':
      value1 = pop_Stack_double(S);
      push_Stack_double(pop_Stack_double(S) - value1, S);
      break;
    case '/':
      value1 = pop_Stack_double(S);
      if (value1 == 0)
        error = 1;
      else
        push_Stack_double(pop_Stack_double(S) / value1, S);
      break;
    case '^':
      value1 = pop_Stack_double(S);
      value2 = pop_Stack_double(S);
      if ((value2 == 0 && value1 < 0) ||
          (value2 < 0 && floor(value1) != value1))
        error = 1;
      else
        push_Stack_double(pow(value2, value1), S);
      break;
    default:
      break;
  }
  return error;
}

static int Functions(char const *str, Stack_double *S) {
  int error = 0;
  if (!strcmp(str, "sin(")) {
    push_Stack_double(sin(pop_Stack_double(S)), S);
  } else if (!strcmp(str, "cos(")) {
    push_Stack_double(cos(pop_Stack_double(S)), S);
  } else if (!strcmp(str, "tan(")) {
    push_Stack_double(tan(pop_Stack_double(S)), S);
  } else if (!strcmp(str, "ctg(")) {
    double value1 = tan(pop_Stack_double(S));
    if (value1 == 0)
      error = 1;
    else
      push_Stack_double(pow(value1, -1), S);
  } else if (!strcmp(str, "ln(")) {
    double value1 = pop_Stack_double(S);
    if (value1 <= 0)
      error = 1;
    else
      push_Stack_double(log(value1), S);
  } else if (!strcmp(str, "sqrt(")) {
    double value1 = pop_Stack_double(S);
    if (value1 < 0)
      error = 1;
    else
      push_Stack_double(sqrt(value1), S);
  }
  return error;
}