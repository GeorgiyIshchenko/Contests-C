#include "stdio.h"

int sort(int a[])
{
    int buf;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (a[i] > a[j])
            {
                buf = a[i];
                a[i] = a[j];
                a[j] = buf;
            }
        }
    }
    return a[1];
}

int median(int *a)
{
    int buf[3];
    for (int i = 0; i < 3; i++)
    {
        buf[i] = *(a + i);
    }
    return sort(buf);
}

void compressor(int arr[], int size)
{
    if (size == -1)
    {
        return;
    }
    for (int i = 0; i < size; i++)
    {
        arr[i] = median(&arr[i]);
    }
    compressor(arr, size - 2);
}

int main(void)
{
    int size;
    scanf("%d", &size);
    int arr[1001];
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
    compressor(arr, size - 2);
    printf("%d", arr[0]);
    return 0;
}