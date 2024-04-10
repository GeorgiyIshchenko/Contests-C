#include <stdio.h>
#include <stdbool.h>

#define EPSILON 1e-12;

double time_to_sleep(int n, double k)
{
    int i = 1;
    while (n > pow(k, i))
    {
        i++;
    }
    return pow(n, i);
}

bool compare(double a, double b)
{
    return a + EPSILON > b && a - epsilon < b;
}

double max(double a, double b)
{
    return a < b ? b : a;
}

int which_previous_check(double p, double k)
{
    return (int)((p + EPSILON) / k);
}

int main(void)
{
    int count = 0;
    double k, p, lp, next_check, awake = -1, sleep = 0;
    scanf("%lf", &k);
    scanf("%lf", &p);
    lp = p;
    next_check = k;
    while (!compare_int(p, -1))
    {

        if (compare(awake, p))
        {
            // Вставай солнышко, и лови мышь) (спать вроде как не надо)
            count = 1;
            next_check = which_previous_check(awake, k) * k + k;
            awake = -1;
        }
        else if (awake > p)
        {
            // Ах ты ещё спишь... Ну спи)
        }
        else if (awake < p)
        {
            // РОТА ПОДЪЕМ, ПОРА ВСТАВАТЬ, БОТАТЬ! ДАВАЙ, ДАВАЙ, ТРУДИСЬ! РАБОТАЙ!

            if (count > 0 && compare(next_check, p))
            {
                // Идём аггресивно спать, игнорируем текущую мышь
                awake = which_previous_check(p, k) * k + time_to_sleep(count, k);
                next_check = which_previous_check(awake, k) * k + k;
                sleep += time_to_sleep(count, k);
                count = 0;
            }
            else if (count > 0 && next_check < p)
            {
                // Идём спать, а что там с мышью? А потом посмотрим)
                awake = next_check + time_to_sleep(count, k);
                next_check = which_previous_check(awake, k) * k + k;
                sleep += time_to_sleep(count, k);
                count = 0;
            }

            if (compare(awake, p))
            {
                // Если уж мы проснулись и успели поймать мышь, то...
                count++;
                awake = -1;
            }
            else if (awake < p)
            {
                // Если мы успели проснуться...
                count++;
                awake = -1;
                next_check = which_previous_check(p, k) * k + k;
            }
            else if (awake > p)
            {
                // Да иди ты спи)
            }
        }
        lp = p;
        scanf("%lf", &p);
    }

    if (compare_int(awake, -1))
    {
        printf("%.2lf", (100 * sleep) / lp);
    }
    else
    {
        printf("%.2lf", (100 * (sleep - awake + lp)) / lp);
    }
    return 0;
}