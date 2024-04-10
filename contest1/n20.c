#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    double a, b, c, d, buf;
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
    if (b < a)
    {
        buf = a;
        a = b;
        b = buf;
    }
    if (d < c)
    {
        buf = c;
        c = d;
        d = buf;
    }
    if (a >= c && b >= d)
    {
        printf("YES");
    }
    else
    {
        double a1 = (d * d + c * c), b1 = -1 * (2 * b * c * c), c1 = c * c * (b * b - d * d);
        double x = (-b1 + sqrt(b1 * b1 - 4 * a1 * c1)) / (2 * a1);
        if (d > b && a >= sqrt(c * c - x * x) + sqrt(d * d - (b - x) * (b - x)))
        {
            printf("YES");
        }
        else
        {
            printf("NO");
        }
    }
}