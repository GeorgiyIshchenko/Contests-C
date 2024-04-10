#include "stdio.h"
#include "math.h"

/*
a b c a^b^c
0 0 0 0
0 0 1 1
0 1 0 1
0 1 1 0
1 0 0 1
1 0 1 0
1 1 0 0
1 1 1 1
*/

int main(void)
{
    int arr[15000];
    int n;
    scanf("%d", &n);
    int mask = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        mask ^= arr[i];
    }
    int bit = 0;
    int mask0 = 0;
    int mask1 = 0;
    for (int i = 0; i < 32; i++)
    {
        if ((mask >> i) % 2 == 1)
        {
            bit = i;
            break;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if ((arr[i] >> bit) % 2 == 0)
        {
            mask0 ^= arr[i];
        }
        else
        {
            mask1 ^= arr[i];
        }
    }
    mask0 > mask1 ? printf("%d %d", mask1, mask0) : printf("%d %d", mask0, mask1);
    return 0;
}