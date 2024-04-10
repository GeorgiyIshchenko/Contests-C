#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define DBL_EPSILON 2.2204460492503131e-14

int main(void)
{
    srand(time(NULL));
    for (int i = 0; i < 10000; i++)
    {
        double a = rand() / 1000., b = rand() / 1000., c = rand() / 1000., d = rand() / 1000., buf;
        //scanf("%lf %lf %lf %lf", &a, &b, &c, &d);

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
        int r1;
        double x;
        if (a >= c && b >= d)
        {
           r1 = 2;
        }
        else
        {
            double a1 = (d * d + c * c), b1 = -1 * (2 * b * c * c), c1 = c * c * (b * b - d * d);
            x = (-b1 + sqrt(b1 * b1 - 4 * a1 * c1)) / (2 * a1);
            //printf("%lf\n", x);
            if (d > b && a >= sqrt(c * c - x * x) + sqrt(d * d - (b - x) * (b - x)))
            {
                r1 = 1;
            }
            else
            {
                r1 = 0;
            }
        }
        double t;
        int r2;
        if (b > a)
        {
            t = a;
            a = b;
            b = t;
        }

        if (d > c)
        {
            t = c;
            c = d;
            d = t;
        }

        if ((c <= a && d <= b) || (c > a &&
                                   b >= (2 * c * d * a + (c * c - d * d) * sqrt(c * c + d * d - a * a)) / (c * c + d * d))) /* John E. Wetzel - Rectangles in Rectangles
                                                                                                     Mathematics Magazine, Vol. 73, No. 3 (Jun., 2000), pp. 204-211*/
            r2 = 1;
        else
            r2 = 0;
        if ((r1 > 0) != (r2 > 0)){
            printf("a=%lf b=%lf c=%lf d=%lf r1=%d r2=%d, x=%.20lf\n", a, b, c, d, r1, r2, x);
        }
    }
}