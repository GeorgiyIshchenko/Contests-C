#include <stdio.h>

#define MIN(a, b) (a) < (b) ? (a) : (b)
#define ABS(a) (a) < (0) ? (-a) : (a)
#define SIGN(a) (a) < (0) ? (-1) : (1)

int main(void)
{
    int n;
    scanf("%d", &n);

    int arr[10000] = {0};
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int cnt = 0;
    int sign;
    int turn_on[10000] = {0};
    for (int i = 0; i < n; i++)
    {
        if (arr[i])
        {
            sign = SIGN(arr[i]);
            for (int j = sign; ABS(j) <= ABS(arr[i]); j += sign)
            {   
                if ((i + j < 0) || (i + j >= n))
                {
                    break;
                }
                if (turn_on[i + j] != 1)
                {
                    turn_on[i + j] = 1;
                    cnt++;
                }
                if (arr[i + j] != 0)
                {
                    break;
                }
                for (int m = 0; m < n; m++)
                {
                    printf("%d ", turn_on[m]);
                }
                printf("\n%d \n", arr[i]);
            }
            printf("\n");
        }
    }
    printf("%d", cnt);
    return 0;
}