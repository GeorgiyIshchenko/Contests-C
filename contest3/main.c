#include "stdio.h"

static int size;
static int target;
static int global_flag;


void print_arr(int a[], int size){
    for (int i = 0; i < size; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}


void recursion(int arr[], int sum, int step, int  num_used)
{
    //print_arr(arr, size);
    //printf("%d %d\n", sum, target);
    if (sum >= target)
    {
        if (sum == target)
        {
            if (step == 2)
            {
                global_flag = 1;
            }
            else
            {
                recursion(arr, 0, 2, 0);
            }
        }
        return;
    }
    int buf;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] != -100)
        {
            buf = arr[i];
            arr[i] = -100;
            recursion(arr, sum + buf, step, num_used + 1);
            arr[i] = buf;
        }
    }
}

int main(void)
{
    int arr[14];
    scanf("%d", &size);
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }
    int high_limit = sum / 2;
    for (int t = high_limit; t >= 0; t--)
    {
        target = t;
        global_flag = 0;
        recursion(arr, 0, 1, 0);
        if (target == 0)
        {
            printf("0");
        }
        else if (global_flag == 1)
        {
            printf("%d\n", target);
            break;
        }
    }
    return 0;
}