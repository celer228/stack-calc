#include "stack.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s \"expression\"\n", argv[0]);
        return 1;
    }

    char *expression = argv[1];
    char postfix[MAX] = {0};

    infixToPostfix(expression, postfix);
    double result = evaluatePostfix(postfix);

    printf("Result: %lf\n", result);

    return 0;
}
