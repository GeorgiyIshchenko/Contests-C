#include "stdio.h"
#include "stdlib.h"

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

int compare(const void *x1, const void *x2)
{
    return (*(int *)x1 - *(int *)x2);
}

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
    for (int i = 0; i < 32; i++)
    {
        if ((mask >> i) % 2 == 1)
        {
            bit = i;
            break;
        }
    }
    int mask0 = 0;
    int mask1 = 0;
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
    for (int i = 0; i < n; i++)
    {
        if (mask1 == arr[i])
        {
            int buf = mask0;
            mask0 = mask1;
            mask1 = buf;
            break;
        }
    }
    int bit2 = 0;
    for (int i = 0; i < 32; i++)
    {
        if ((mask1 >> i) % 2 == 1)
        {
            bit2 = i;
            break;
        }
    }
    int mask2 = 0;
    int mask3 = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] != mask0)
        {
            if ((arr[i] >> bit2) % 2 == 0)
            {
                mask2 ^= arr[i];
            }
            else
            {
                mask3 ^= arr[i];
            }
        }
    }
    int masks[] = {mask0, mask2, mask3};
    qsort(masks, 3, sizeof(int), compare);
    printf("%d %d %d", masks[0], masks[1], masks[2]);
    return 0;
}