#include "list_of_tokens.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "spaces.h"

Token *init_Token(char *str) {
  Token *root = NULL;
  if (str) {
    root = (Token *)malloc(sizeof(Token));
    if (root) {
      root->str = str;
      root->next = NULL;
    }
  }
  return root;
}

void add_Token(char *str, Token **root) {
  if (*root) {
    Token *ptr = *root;
    while (ptr->next) ptr = ptr->next;
    ptr->next = init_Token(str);
  } else
    *root = init_Token(str);
}

Token *string_to_Tokens(char **str) {
  Token *root = NULL;
  if (str) {
    *str = add_spaces(*str);
    char *str2 = *str;
    char *ch = strtok(str2, " ");
    while (ch != NULL) {
      add_Token(ch, &root);
      ch = strtok(NULL, " ");
    }
  }
  return root;
}

void destroy_Tokens(Token *root) {
  if (root) {
    destroy_Tokens(root->next);
    free(root);
  }
}

Token_double *init_Token_double(double value) {
  Token_double *root = NULL;
  root = (Token_double *)malloc(sizeof(Token));
  if (root) {
    root->value = value;
    root->next = NULL;
  }
  return root;
}