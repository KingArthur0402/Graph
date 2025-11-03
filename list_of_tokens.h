#ifndef LIST_OF_TOKENS_H
#define LIST_OF_TOKENS_H

typedef struct Token {
  char *str;
  struct Token *next;
} Token;

Token *init_Token(char *str);
void add_Token(char *str, Token **root);
Token *string_to_Tokens(char **str);
void destroy_Tokens(Token *root);

typedef struct Token_double {
  double value;
  struct Token_double *next;
} Token_double;

Token_double *init_Token_double(double value);

#endif
