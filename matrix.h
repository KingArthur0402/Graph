#ifndef MATRIX_H
#define MATRIX_H

#define XMAX 80
#define YMAX 25

#include "list_of_tokens.h"

int matrix_graph(int A[][YMAX], Token *T);
void reset_matrix(int A[][YMAX]);
void print_graph(int const A[][YMAX]);

#endif