#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
{
    char c;
    uint64_t res = 0;
    while ((c = getchar()) != '.')
    {
        res *= 19;
        if (c < 'A')
        {
            res = res + (c - '0');
        }
        else
        {
            res = res + c - 'A' + 10;
        }
    }
    printf("%#x", res);
    return 1;
}