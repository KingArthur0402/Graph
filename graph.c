#include <stdio.h>
#include <stdlib.h>

#include "check.h"
#include "list_of_tokens.h"
#include "matrix.h"
#include "my_io.h"
#include "my_stack.h"
#include "polish_notation.h"
#include "spaces.h"

int main() {
  int error = 0;
  char *str = NULL;
  if (input(&str)) error = 1;
  if (!error && check_str(str)) error = 1;
  if (!error) {
    Token *T = string_to_Tokens(&str);
    Token *T2 = Token_in_Polish_notation(T);
    int A[XMAX][YMAX];
    reset_matrix(A);
    error = matrix_graph(A, T2);
    if (!error) print_graph(A);
    if (T) destroy_Tokens(T);
    if (T2) destroy_Tokens(T2);
  }
  if (str) free(str);
  if (error) printf("ERROR\n");
  return 0;
}
