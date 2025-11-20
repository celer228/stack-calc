#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct
{
    double data[MAX];
    int top;
} StackNum;

typedef struct
{
    char data[MAX];
    int top;
} StackOp;

void pushNum(StackNum *stack, double value);
double popNum(StackNum *stack);
void pushOp(StackOp *stack, char value);
char popOp(StackOp *stack);
char peekOp(StackOp *stack);
int precedence(char op);
int isOperator(char ch);
int isValidChar(char ch);
void infixToPostfix(char *expression, char *output);
double evaluatePostfix(char *expression);
