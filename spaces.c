#include "spaces.h"

#include <stdlib.h>

#include "check.h"

static char *remove_spaces(char *str);

char *add_spaces(char *str) {
  if (str) str = remove_spaces(str);
  int n = 1;
  char *new_str = NULL;
  char *ch = str;
  char const *last_ch = str;
  if (str) new_str = (char *)malloc(sizeof(char));
  while (new_str && *ch != '\0') {
    int b = 0, x = 0;
    if (*ch == 'x' && NUMBER(*last_ch)) {
      n += 2;
      x = 1;
    }
    if ((b = (DIFFERENCE(*ch, *last_ch) || *last_ch == '('))) n++;
    n++;
    char *temp = NULL;
    temp = realloc(new_str, n * sizeof(char));
    if (temp) {
      new_str = temp;
      if (x) {
        new_str[n - 5] = ' ';
        new_str[n - 4] = '*';
      }
      if (b) new_str[n - 3] = ' ';
      new_str[n - 2] = *ch;
      last_ch = ch;
    } else {
      free(new_str);
      new_str = NULL;
    }
    ch++;
  }
  if (new_str) {
    free(str);
    new_str[n - 1] = '\0';
  }
  return new_str;
}

static char *remove_spaces(char *str) {
  int n = 1;
  char *new_str = NULL;
  char const *ch = str;
  if (str) new_str = (char *)malloc(sizeof(char));
  while (new_str && *ch != '\0') {
    if (*ch != ' ') {
      n++;
      char *temp = realloc(new_str, n * sizeof(char));
      if (temp) {
        new_str = temp;
        new_str[n - 2] = *ch;
      } else {
        free(new_str);
        new_str = NULL;
      }
    }
    ch++;
  }
  if (new_str) {
    free(str);
    new_str[n - 1] = '\0';
  }
  return new_str;
}