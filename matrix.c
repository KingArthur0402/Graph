#include "matrix.h"

#include "list_of_tokens.h"
#include "polish_notation.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>

int matrix_graph(int A[][YMAX], Token *T) {
  int error = 0;
  for (int i = 0; !error && i != XMAX; ++i) {
    double x = 4 * M_PI / XMAX * i;
    double y = 0;
    error = Polish_notation_calculations(T, x, &y);
    if (!error) {
      int j = 12 - round(y * 12);
      if (j < YMAX && j >= 0) {
        A[i][j] = 1;
      }
    }
  }
  return error;
}

void reset_matrix(int A[][YMAX]) {
  for (int i = 0; i != XMAX; ++i) {
    for (int j = 0; j != YMAX; ++j) {
      A[i][j] = 0;
    }
  }
}

void print_graph(int const A[][YMAX]) {
  for (int j = 0; j != YMAX; ++j) {
    for (int i = 0; i != XMAX; ++i) {
      printf(A[i][j] ? "*" : ".");
    }
    printf("\n");
  }
}