#include "stdio.h"
#include "math.h"
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

int is_in_array(int arr[], int size, int target)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target)
        {
            return 1;
        }
    }
    return 0;
}

int compare(const void *x1, const void *x2)
{
    return (*(int *)x1 - *(int *)x2);
}


// a < b
void swap_min(int *a, int *b)
{
    if (*a > *b)
    {
        int buf = *a;
        *a = *b;
        *b = buf;
    }
}

int main(void)
{
    int arr[1500000];
    int n;
    scanf("%d", &n);
    int mask = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        mask ^= arr[i];
    }
    int bit = 0;
    int xor_of_two = mask;
    int first = 0;
    while ((first == 0) && (xor_of_two == mask))
    {
        xor_of_two = 0;
        first = 0;
        for (int i = 0; i < n; i++)
        {
            if ((arr[i] >> bit) % 2 == 0)
            {
                xor_of_two ^= arr[i];
            }
            else
            {
                first ^= arr[i];
            }
        }
        bit++;
        swap_min(&first, &xor_of_two);
    }
    if (is_in_array(arr, n, xor_of_two))
    {
        int buf = xor_of_two;
        xor_of_two = first;
        first = buf;
    }
    //printf("%d %d\n", first, xor_of_two);
    for (int i = 0; i < 32; i++)
    {
        if ((xor_of_two >> i) % 2 == 1)
        {
            bit = i;
            break;
        }
    }
    int second = 0;
    int third = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] != first)
        {
            if ((arr[i] >> bit) % 2 == 0)
            {
                second ^= arr[i];
            }
            else
            {
                third ^= arr[i];
            }
        }
    }
    int nums[3] = {first, second, third};
    qsort(nums, 3, sizeof(int), compare);
    printf("%d %d %d", nums[0], nums[1], nums[2]);
    return 0;
}