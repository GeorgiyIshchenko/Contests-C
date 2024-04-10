#include "stdio.h"
#include "math.h"

#define DBL_EPSILON 2.2204460492503131e-14

int main(void)
{
    double s[100], a[100];
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%lf", &s[i]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%lf", &a[i]);
    }
    float time = 0, speed = 0, d, t1, t2;
    for (int i = 0; i < n; i++)
    {
        d = 4 * speed * speed + 8 * a[i] * s[i];
        if (fabs(a[i]) < DBL_EPSILON)
        {
            t1 = s[i] / speed;
        }
        else
        {
            t1 = (-2 * speed + sqrt(d)) / (2 * a[i]);
            t2 = (-2 * speed - sqrt(d)) / (2 * a[i]);
            if (t1 < 0)
                t1 = t2;
        }
        time += t1;
        speed += a[i] * t1;
        // printf("%f %f %f\n", time, speed, d);
    }
    printf("%.4f", time);
}