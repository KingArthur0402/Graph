#include "check.h"

static int evrthng(char ch, char *expect, char *last_ch, int *bracket);
static int val_funct(char ch, char *expect, char *last_ch, int *bracket);
static int val_oper(char ch, char *expect, int *bracket);
static int oper(char ch, char *expect, int *bracket);
static int funct_SQRT(char ch, char *last_ch, char *expect_f);
static int funct(char ch, char *expect, char *last_ch, int *bracket,
                 char *expect_f);

int check_str(char const *str) {
  int error = 0;
  int bracket = 0;
  char expect = EVRTHNG;
  char last_ch = NOTHING;
  char expect_f = NOTHING;
  while (*str != '\0' && !error) {
    if (expect == EVRTHNG) {
      if (evrthng(*str, &expect, &last_ch, &bracket) == 1) error = 1;
    } else if (expect == VAL_FUNCT) {
      if (val_funct(*str, &expect, &last_ch, &bracket) == 1) error = 1;
    } else if (expect == VAL_OPER) {
      if (val_oper(*str, &expect, &bracket) == 1) error = 1;
    } else if (expect == OPER) {
      if (oper(*str, &expect, &bracket) == 1) error = 1;
    } else if (expect == FUNCT) {
      if (funct(*str, &expect, &last_ch, &bracket, &expect_f) == 1) error = 1;
    } else {
      error = 1;
    }
    if (!error) str++;
  }
  if (bracket || last_ch != NOTHING || expect_f != NOTHING) error = 1;
  return error;
}

static int evrthng(char ch, char *expect, char *last_ch, int *bracket) {
  int error = 0;
  if (ch != ' ') {
    if (UNARY(ch))
      *expect = VAL_FUNCT;
    else if (NUMBER(ch))
      *expect = VAL_OPER;
    else if (ch == '(')
      (*bracket)++;
    else if (ch == 'x')
      *expect = OPER;
    else if (FUNCTION(ch)) {
      *expect = FUNCT;
      *last_ch = ch;
    } else
      error = 1;
  }
  return error;
}

static int val_funct(char ch, char *expect, char *last_ch, int *bracket) {
  int error = 0;
  if (ch != ' ') {
    if (NUMBER(ch))
      *expect = VAL_OPER;
    else if (ch == '(') {
      (*bracket)++;
      *expect = EVRTHNG;
    } else if (ch == 'x')
      *expect = OPER;
    else if (FUNCTION(ch)) {
      *expect = FUNCT;
      *last_ch = ch;
    } else if (!UNARY(ch))
      error = 1;
  }
  return error;
}

static int val_oper(char ch, char *expect, int *bracket) {
  int error = 0;
  if (ch != ' ') {
    if (ch == ')') {
      (*bracket)--;
      *expect = OPER;
    } else if (ch == 'x')
      *expect = OPER;
    else if (OPERATOR(ch))
      *expect = VAL_FUNCT;
    else if (!NUMBER(ch))
      error = 1;
  } else
    *expect = OPER;
  return error;
}

static int oper(char ch, char *expect, int *bracket) {
  int error = 0;
  if (ch != ' ') {
    if (OPERATOR(ch))
      *expect = VAL_FUNCT;
    else if (ch == ')')
      (*bracket)--;
    else
      error = 1;
  }
  return error;
}

static int funct_SQRT(char ch, char *last_ch, char *expect_f) {
  int error = 0;
  if (ch == 'r' && *expect_f == SQRT && *last_ch == 'q') {
    *last_ch = 'r';
    *expect_f = SQRT;
  } else if (ch == 't' && *expect_f == SQRT && *last_ch == 'r') {
    *expect_f = '(';
  } else
    error = 1;
  return error;
}

static int funct(char ch, char *expect, char *last_ch, int *bracket,
                 char *expect_f) {
  int error = 0;
  if (ch != ' ') {
    if (*expect_f == SQRT) {
      if (funct_SQRT(ch, last_ch, expect_f) == 1) error = 1;
    } else if (ch == 'i' && *last_ch == 's') {
      *expect_f = SIN;
    } else if ((ch == 'n' &&
                (*expect_f == SIN || *expect_f == TAN || *last_ch == 'l')) ||
               (ch == 's' && *expect_f == COS) ||
               (ch == 'g' && *expect_f == CTG)) {
      *expect_f = '(';
    } else if (ch == 'q' && *last_ch == 's') {
      *last_ch = 'q';
      *expect_f = SQRT;
    } else if (ch == 'o' && *last_ch == 'c') {
      *expect_f = COS;
    } else if (ch == 't' && *last_ch == 'c') {
      *expect_f = CTG;
    } else if (ch == 'a' && *last_ch == 't') {
      *expect_f = TAN;
    } else if (ch == '(' && *expect_f == '(') {
      (*bracket)++;
      *expect = EVRTHNG;
      *expect_f = NOTHING;
    } else
      error = 1;
    if (*expect_f == SIN || *expect_f == TAN || *expect_f == COS ||
        *expect_f == CTG || *expect_f == '(')
      *last_ch = NOTHING;
  } else
    error = 1;
  return error;
}