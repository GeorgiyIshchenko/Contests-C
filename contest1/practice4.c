#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

int main(void)
{
    int x;
    scanf("%d", &x);
    int k = 0;
    while ((int)pow(10, k) <= x) k += 1;
    k -= 1;
    int i = 0, r, l, flag = 1;
    while (i <= k)
    {
        r = x;
        l = x % 10;
        if (r != l)
        {
            flag = 0;
            break;
        }
        x = x % (int)pow(10, k);
        k -= 2;
    }
    printf("%d", flag);
    return 1;
}
