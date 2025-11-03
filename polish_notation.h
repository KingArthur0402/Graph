#ifndef POLISH_NOTATION_H
#define POLISH_NOTATION_H

#include "list_of_tokens.h"

Token *Token_in_Polish_notation(Token *old_T);
int Polish_notation_calculations(Token *T, double x, double *result);

#endif
