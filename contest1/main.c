#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
(a11 & x) ^ (a12 & y) == b1
(a21 & x) ^ (a22 & y) == b2
*/

int main(void)
{
    unsigned int a11, a12, a21, a22, b1, b2;
    int ba11, ba12, ba21, ba22, bb1, bb2;
    int fl_has_solution = 0;
    unsigned int rx = 0, ry = 0;
    scanf("%u %u %u %u %u %u", &a11, &a12, &a21, &a22, &b1, &b2);
    for (int i = 0; i < 32; i++)
    {
        fl_has_solution = 0;
        // ba11 means byte_a11
        ba11 = a11 % 2, ba12 = a12 % 2, ba21 = a21 % 2, ba22 = a22 % 2, bb1 = b1 % 2, bb2 = b2 % 2;
        for (int x = 0; !fl_has_solution && x <=1 ; x++)
        {
            for (int y = 0; y <= 1; y++)
            {
                // printf("%d %d %d %d\n", rx, ry, x, y);
                if (((ba11 & x) ^ (ba12 & y)) == bb1 && ((ba21 & x) ^ (ba22 & y)) == bb2)
                {
                    rx += (x << i);
                    ry += (y << i);
                    fl_has_solution = 1;
                    break;
                }
            }
        }
        if (!fl_has_solution){
            break;
        }
        a11 >>= 1, a12 >>= 1, a21 >>= 1, a22 >>= 1, b1 >>= 1, b2 >>= 1;
    }
    if (fl_has_solution){
        printf("Yes\n");
        printf("%u %u", rx, ry);
    }
    else printf("No");
    return 0;
}