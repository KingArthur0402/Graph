#ifndef CHECK_H
#define CHECK_H

#define NUMBER(value) (value >= '0' && value <= '9')
#define OPERATOR(value) \
  (value == '+' || value == '-' || value == '*' || value == '/' || value == '^')
#define FUNCTION(value)                                            \
  (value == 's' || value == 'i' || value == 'n' || value == 'c' || \
   value == 'o' || value == 't' || value == 'a' || value == 'g' || \
   value == 'l' || value == 'q' || value == 'r' || value == '(')
#define UNARY(value) (value == '-')
#define DIFFERENCE(value1, value2)              \
  ((!(NUMBER(value1) && NUMBER(value2)) &&      \
    !(FUNCTION(value1) && FUNCTION(value2))) || \
   (OPERATOR(value1) && OPERATOR(value2)) || (UNARY(value1) && UNARY(value2)))

#define EVRTHNG 'q'
#define VAL_FUNCT 'w'
#define VAL_OPER 'e'
#define OPER 'r'
#define FUNCT 't'
#define SIN 'y'
#define SQRT 'i'
#define COS 'o'
#define CTG 'p'
#define TAN 'a'
#define NOTHING 'N'

int check_str(char const *str);

#endif