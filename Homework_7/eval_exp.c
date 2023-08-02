#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EXPR_LEN 100U
#define OPRS_COUNT 4U
#define PLUS '+'
#define MINUS '-'
#define MULT '*'
#define POW '^'
#define OPERATORS \
    (char[]) { PLUS, MINUS, MULT, POW }

int calc(int a, int b, char operator)
{
    switch (operator)
    {
    case PLUS:
        return a + b;

    case MINUS:
        return a - b;

    case MULT:
        return a * b;

    case POW:
        return (int)pow(a, b);

    default:
        exit(1);
    }
}

int evaluate(const char *const expr, unsigned int *startIdx, unsigned int len)
{
    unsigned int argIdx = 0;
    int a = 0;
    int b = 0;
    char operator= '\0';

    for (unsigned *i = startIdx; *i < len && expr[*i] != '\0'; (*i)++)
    {
        unsigned int oldArgIdx = argIdx;
        for (size_t y = 0; y < OPRS_COUNT; y++)
        {
            if (OPERATORS[y] == expr[*i])
            {
                operator= expr[*i];
                argIdx++;
                break;
            }
        }

        if (oldArgIdx != argIdx) // an operator was found
            continue;

        if (expr[*i] == '(')
        {
            (*i)++;
            int res = evaluate(expr, i, len);
            switch (argIdx)
            {
            case 0:
                a = res;
                continue;

            case 1:
                b = res;
                continue;

            default:
                exit(2);
            }
        }
        else if (expr[*i] == ')')
            return calc(a, b, operator);

        switch (argIdx)
        {
        case 0:
            a *= 10;
            a += expr[*i] - '0';
            break;

        case 1:
            b *= 10;
            b += expr[*i] - '0';
            break;

        default:
            exit(3);
        }
    }

    return argIdx == 0 ? a : calc(a, b, operator);
}

int main()
{
    char expr[EXPR_LEN];
    unsigned int startIdx = 0;

    scanf_s("%s", expr, EXPR_LEN);
    printf_s("%i", evaluate(expr, &startIdx, EXPR_LEN));

    return 0;
}