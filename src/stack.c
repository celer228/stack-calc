#include "stack.h"

void pushNum(StackNum *stack, double value)
{
    if (stack->top < MAX - 1)
    {
        stack->data[++(stack->top)] = value;
    }
    else
    {
        printf("Stack overflow\n");
        exit(EXIT_FAILURE);
    }
}

double popNum(StackNum *stack)
{
    if (stack->top >= 0)
    {
        return stack->data[(stack->top)--];
    }
    else
    {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
}

void pushOp(StackOp *stack, char value)
{
    if (stack->top < MAX - 1)
    {
        stack->data[++(stack->top)] = value;
    }
    else
    {
        printf("Stack overflow\n");
        exit(EXIT_FAILURE);
    }
}

char popOp(StackOp *stack)
{
    if (stack->top >= 0)
    {
        return stack->data[(stack->top)--];
    }
    else
    {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
}

char peekOp(StackOp *stack)
{
    if (stack->top >= 0)
    {
        return stack->data[stack->top];
    }
    else
    {
        return '\0';
    }
}

int precedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int isValidChar(char ch)
{
    return isdigit(ch) || isspace(ch) || ch == '.' || ch == '(' || ch == ')' || isOperator(ch);
}

void infixToPostfix(char *expression, char *output)
{
    StackOp operators = {.top = -1};
    int k = 0;
    int balance = 0;

    for (int i = 0; expression[i]; i++)
    {
        if (!isValidChar(expression[i]))
        {
            printf("Invalid character in expression: %c\n", expression[i]);
            exit(EXIT_FAILURE);
        }
        if (isspace(expression[i]))
            continue;
        if (isdigit(expression[i]) || expression[i] == '.')
        {
            while (isdigit(expression[i]) || expression[i] == '.')
            {
                output[k++] = expression[i++];
            }
            output[k++] = ' ';
            i--;
        }
        else if (expression[i] == '(')
        {
            pushOp(&operators, expression[i]);
            balance++;
        }
        else if (expression[i] == ')')
        {
            while (peekOp(&operators) != '(')
            {
                output[k++] = popOp(&operators);
                output[k++] = ' ';
            }
            popOp(&operators);
            balance--;
        }
        else if (isOperator(expression[i]))
        {
            while (precedence(peekOp(&operators)) >= precedence(expression[i]))
            {
                output[k++] = popOp(&operators);
                output[k++] = ' ';
            }
            pushOp(&operators, expression[i]);
        }
    }

    if (balance != 0)
    {
        printf("Unbalanced parentheses\n");
        exit(EXIT_FAILURE);
    }

    while (operators.top != -1)
    {
        output[k++] = popOp(&operators);
        output[k++] = ' ';
    }
    output[k] = '\0';
}

double evaluatePostfix(char *expression)
{
    StackNum values = {.top = -1};
    char *token = strtok(expression, " ");

    while (token != NULL)
    {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1])))
        {
            pushNum(&values, atof(token));
        }
        else if (isOperator(token[0]))
        {
            if (values.top < 1)
            {
                printf("Stack underflow during evaluation\n");
                exit(EXIT_FAILURE);
            }
            double b = popNum(&values);
            double a = popNum(&values);
            switch (token[0])
            {
            case '+':
                pushNum(&values, a + b);
                break;
            case '-':
                pushNum(&values, a - b);
                break;
            case '*':
                pushNum(&values, a * b);
                break;
            case '/':
                pushNum(&values, a / b);
                break;
            }
        }
        token = strtok(NULL, " ");
    }
    if (values.top != 0)
    {
        printf("Stack has extra elements after evaluation\n");
        exit(EXIT_FAILURE);
    }
    return popNum(&values);
}
