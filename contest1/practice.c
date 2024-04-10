#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
{
    double c = 1, sum = 0;
    while (c != 0)
    {
        scanf("%lf", &c);
        sum += c;
    }
    printf("%lf", sum);
    return 1;
}