#include "stdio.h"

#define COMBINATIONS_NUM 16384

int sum_by_mask(int arr[], int mask)
{
    int sum = 0;
    for (int i = 0; i < 16; i++)
    {
        if ((mask >> i) % 2 == 1)
        {
            sum += arr[i];
        }
    }
    return sum;
}

void print_arr(short a[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(void)
{
    int max = 0;
    int sums[COMBINATIONS_NUM];

    int size;
    scanf("%d", &size);

    int arr[14];
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
    for (int i = 1; i < COMBINATIONS_NUM; i++)
    {
        sums[i] = sum_by_mask(arr, i);
    }
    for (int i = 1; i < COMBINATIONS_NUM; i++)
    {
        for (int j = 1; j < COMBINATIONS_NUM; j++)
        {
            if (((i & j) == 0) && sums[i] == sums[j] && sums[i] > max)
            {
                max = sums[i];
            }
        }
    }
    printf("%d", max);
    return 0;
}