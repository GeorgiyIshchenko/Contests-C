#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define EPSILON 1e-12
#define NOT_SLEEPING_TIMEUP_CODE -101

#define MIN(a, b) (a) > (b) ? (b) : (a)

double time_to_sleep(double n, double k)
{
    int i = 1;
    while (n > pow(k, i))
    {
        i++;
    }
    return pow(n, i);
}

int get_previos_down(double time, double k)
{
    return (int)((time + EPSILON) / k);
}

bool compare(double a, double b)
{
    return (fabs(a - b) < EPSILON);
}

int main(void)
{
    double k;
    scanf("%lf", &k);

    double arr[10000] = {0};
    double scan = 1;
    int size = 0;

    while (1)
    {
        scanf("%lf", &scan);
        if (scan > -0.5)
        {
            arr[size++] = scan;
        }
        else
        {
            break;
        }
    }

    double time_up = 0;
    double time_down = k;
    double sum_sleep = 0;
    double tts_buf;

    int current_catched = 0;

    for (int i = 0; i < size; i++)
    {
        if (compare(time_up, arr[i]))
        {
            current_catched = 1;
            time_down = get_previos_down(time_up, k) * k + k;
        }
        else if (time_up < arr[i])
        {
            if (current_catched > 0 && compare(time_down, arr[i]))
            {
                tts_buf = time_to_sleep(current_catched, k);
                time_up = time_down + tts_buf;

                sum_sleep += fmin(arr[size - 1] - time_down, tts_buf);

                time_down = get_previos_down(time_up, k) * k + k;
                current_catched = 0;
            }
            else if (current_catched > 0 && time_down < arr[i])
            {
                tts_buf = time_to_sleep(current_catched, k);
                time_up = time_down + tts_buf;

                sum_sleep += fmin(arr[size - 1] - time_down, tts_buf);

                time_down = get_previos_down(time_up, k) * k + k;
                current_catched = 0;
            }

            if (compare(time_up, arr[i]))
            {
                current_catched++;
            }
            else if (time_up < arr[i])
            {
                current_catched++;
                time_down = get_previos_down(arr[i], k) * k + k;
            }
        }
    }
    printf("%.2lf", (sum_sleep / arr[size - 1]) * 100);
    return 0;
}