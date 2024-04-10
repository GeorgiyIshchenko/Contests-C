#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define NNN 20
int inpInd = 0;
int arr[NNN];
double k;

double epsilon = 1e-12;

#define MIN(a, b) (a) > (b) ? (b) : (a)

double time_to_sleep(int n, double k)
{
    if (n <= k)
    {
        return n;
    }
    double result = n;
    double kk = k;
    while (n > kk)
    {
        kk *= k;
        result *= n;
    }
    return result;
}

bool compare_int(double a, int b)
{
    return a + epsilon > b && a - epsilon < b;
}

bool compare(double a, double b)
{
    return a + epsilon > b && a - epsilon < b;
}

double maxx(double a, double b)
{
    return a < b ? b : a;
}

int which_previous_check(double p, double k)
{
    return (int)((p + epsilon) / k);
}

double stress_test(int size)
{
    int count = 0;
    double p, lp, next_check, awake = -1, sleep = 0;
    p = arr[0];
    lp = p;
    next_check = k;
    int i = 1;
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
        p = arr[i++];
    }

    if (compare_int(awake, -1))
    {
        return (100 * sleep) / lp;
    }
    else
    {
        return (100 * (sleep - awake + lp)) / lp;
    }
}
double get_time_down(double time_up, double k)
{
    return ((int)(time_up / k) + 1) * k;
}

bool compare(double a, double b)
{
    return ((a + epsilon > b) && (a - epsilon < b));
}

double my_solution(int size)
{

    double time_up = 0;
    double time_down = k;
    double sum_sleep = 0;
    double buf;

    int current_catched = 0;
    char is_sleeping = 0;

    for (int i = 0; i < size; i++)
    {
        if ((compare(arr[i], time_up)) || (time_up < arr[i]))
        {
            // Проснулись
            is_sleeping = 0;
        }
        // условие на проверку проснулся-заснул одновременно -> До следующего раза чиллишь
        if (compare(time_down, arr[i]) && compare(time_up, arr[i])){
            time_down += k;
            is_sleeping = 0;
        }
        else if ((time_down < arr[i]) || (compare(time_down, arr[i])))
        {
            // Пытаемся заснуть
            if (current_catched > 0)
            {
                // Мы что-то поймали, значит засыпаем
                is_sleeping = 1;
                buf = time_to_sleep(current_catched, k);
                time_up = time_down + buf;
                sum_sleep += MIN(arr[size - 1] - time_down, buf);
                time_down = get_time_down(time_up, k);
                current_catched = 0;
            }
            else
            {
                // Мы ничего не поймали, еще одна смена
                time_down += k;
                is_sleeping = 0;
            }
        }
        // Если работаем, то ловим мышей
        if (is_sleeping == 0)
        {
            current_catched++;
        }
        //printf("%d ", current_catched);
    }
    return (sum_sleep / arr[size - 1]) * 100;
}

int main(void)
{
    int n;
    //scanf("%i", &n);
    srand(time(0));
    while (1)
    {
        n = 1 + ((double)rand() / RAND_MAX) * NNN;
        for (int i = 0; i < n; i++)
        {
            arr[i] = ((double)rand() / RAND_MAX) * 10 - 5;
        }
        k = ((double)rand() / RAND_MAX) * 10 - 5;
        double r1 = stress_test(n);
        double r2 = my_solution(n);
        if (r1 != r2)
        {
            printf("%i \n", n);
            for (int i = 0; i < n; i++)
            {
                printf("%i ", arr[i]);
            }
            printf("\n");
        }
    }
    return 0;
}