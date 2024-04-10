#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void swap(int *a, int *b)
{
    int buf = *a;
    *a = *b;
    *b = buf;
}

int sum(int a[], int size){
    int sum = 0;
    for(int i = 0; i < size; i++)
    {
        sum += a[i];
    }
    return sum;
}


int bs1(int a[], int size, int target){
    int l = 0;
    int r = size;
    int m;
    while (r - l > 1)
    {
        m = (l + r) / 2;
        if (a[m] <= target)
        {
            l = m;
        }
        else
        {
            r = m;
        }
    }
    return l;
}


int bs2(int a[], int l, int r, int target){
    if (r - l <= 1) return l;
    int m = (l + r) / 2;
    if (a[m] <= target)
    {
        return bs2(a, m, r, target);
    }
    else
    {
        return bs2(a, l, m, target);
    }
}


void debug_print(s, ...)
{
    
}


int main(void)
{
    int a = 1;
    int b = 2;
    swap(&a, &b);
    printf("a=%d, &b=%d\n", a, b);
    int mas[] = {1, 7, 5, 2};
    printf("sum=%d\n", sum(mas, 4));
    int mas1[] = {1, 5, 6, 8, 90, 100, 154, 167};
    printf("%d\n", bs1(mas1, 8, 100));
    printf("%d\n", bs2(mas1, 0, 8, 8));
    return 0;
}