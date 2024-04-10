#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

void *xmalloc(size_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL)
    {
        printf("Memory error.");
        exit(137);
    }
    return ptr;
}

void *xrealloc(void *array, int size)
{
    void *ptr = realloc(array, size);
    if (ptr == NULL)
    {
        printf("Memory Error");
        exit(137);
    }
    return ptr;
}

int ord(char x)
{
    return x - '0';
}

char chr(int x)
{
    return x + '0';
}

typedef struct solution
{
    bool has_solution;
    char x;
    char y;
    char z;
    char buf;
} SimpleSolution;

typedef struct expression
{
    char *num1;
    char *num2;
    char *result;
    int len;
} Expression;

SimpleSolution
solve_simple(SimpleSolution solution, Expression exp, int idx)
{
    if (solution.x == '?' && solution.y == '?')
    {
        if (idx != exp.len)
        {
            // Предположим разряд не переходит
            SimpleSolution potential_s = {.x = exp.num1[idx + 1], .y = exp.num2[idx + 1], .z = exp.result[idx + 1], .buf = 0, .has_solution = false};
            potential_s = solve_simple(potential_s, exp, idx + 1);
            
        }

    }
    else if (solution.z == '?')
    {
        int num = ord(solution.x) + ord(solution.y) + ord(solution.buf);
        solution.z = chr(num % 10);
        solution.buf = chr(num / 10);
    }
    else if (solution.x == '?')
    {
        int num = ord(solution.z) - ord(solution.y) - ord(solution.buf);
        if (num < 0)
        {
            solution.x = chr(10 + num);
            solution.buf = chr(1);
        }
        else
        {
            solution.x = chr(num);
            solution.buf = chr(0);
        }
    }
    else if (solution.y == '?')
    {
        int num = ord(solution.z) - ord(solution.x) - ord(solution.buf);
        if (num < 0)
        {
            solution.y = chr(10 + num);
            solution.buf = chr(1);
        }
        else
        {
            solution.y = chr(num);
            solution.buf = chr(0);
        }
    }
    else
    {
        if ((ord(solution.x) + ord(solution.y) + ord(solution.buf)) % 10 != ord(solution.z))
        {
            solution.has_solution = false;
            return solution;
        }
        if (ord(solution.x) + ord(solution.y) + ord(solution.buf) >= 10)
        {
            solution.buf = 1;
        }
    }
    solution.has_solution = true;
    return solution;
}

char *expand_string(char *str, int required_len)
{
    int len = strlen(str);
    char *result = (char *)xmalloc(required_len);
    for (int i = 0; i < required_len - len; i++)
    {
        result[i] = '0';
    }
    result[required_len - len] = '\0';
    strcat(result, str);
    return result;
}

void solve(char *num1, char *num2, char *result)
{
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int len_result = strlen(result);
    int len = MAX(len1, len2);
    num1 = expand_string(num1, len);
    num2 = expand_string(num2, len);
    result = expand_string(result, len);
    Expression expression = {.num1 = num1, .num2 = num2, .result = result, .len = len};
    int buf = '0';
    for (int i = len - 1; i >= 0; --i)
    {
        SimpleSolution solution = {.x = num1[i], .y = num2[i], .z = result[i], .buf = buf, .has_solution = false};
        solution = solve_simple(solution, expression, i);
        expression.num1[i] = solution.x;
        expression.num2[i] = solution.y;
        expression.result[i] = solution.z;
        buf = solution.buf;
    }
    for (int i = len - len1; i < len; i++)
    {
        putchar(num1[i]);
    }
    putchar('+');
    for (int i = len - len2; i < len; i++)
    {
        putchar(num2[i]);
    }
    putchar('=');
    for (int i = len - len_result; i < len; i++)
    {
        putchar(result[i]);
    }
}

char *input(void)
{
    int size = 2;
    int idx = 0;
    char *string = (char *)xmalloc(size * sizeof(char));
    char scanner;
    while ((scanner = getchar(), scanner != '\n'))
    {
        if (idx + 1 >= size)
        {
            size *= 2;
            string = (char *)xrealloc(string, size * sizeof(char));
        }
        string[idx] = scanner;
        idx++;
    }
    string[idx] = '\0';
    return string;
}

int main(void)
{
    char *s = input();

    char *num1 = strtok(s, "+=");
    char *num2 = strtok(NULL, "+=");
    char *result = strtok(NULL, "+=");

    solve(num1, num2, result);

    return 0;
}