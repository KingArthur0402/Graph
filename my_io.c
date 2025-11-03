#include "my_io.h"

#include <stdio.h>
#include <stdlib.h>

int input(char **str) {
  int error = 0, br = 0;
  int n = 1;
  char ch;
  *str = (char *)malloc(sizeof(char));
  if (!(*str)) error = 1;
  while (!error && !br) {
    if (scanf("%c", &ch) != 1) error = 1;
    if (!error && ch == '\n') {
      br = 1;
      (*str)[n - 1] = '\0';
    } else if (!error) {
      n++;
      char *temp = NULL;
      temp = realloc(*str, n * sizeof(char));
      if (!temp)
        error = 1;
      else {
        *str = temp;
        (*str)[n - 2] = ch;
      }
    }
  }
  return error;
}