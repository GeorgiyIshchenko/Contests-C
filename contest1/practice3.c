#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
{
    int32_t n;
    scanf("%d", &n);
    for (int i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            printf("%d\n", i);
            if (i * i != n)
            {
                printf("%d\n", n / i);
            }
        }
    }
    return 1;
}