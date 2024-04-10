#include <stdio.h>
#include <math.h>

#define MIN(a, b) (a) < (b) ? (a) : (b)
#define ABS(a) (a) < (0) ? (-a) : (a)

int lighten(int n)
{
    long long last_flashlight = -1;
    char is_last_lightened = 0;
    long long forward_shine = 0;
    long long counter = 0;
    long long a;
    long long buffer = 0;

    for (int i = 0; i < n; i++)
    {
        scanf("%lli", &a);

        if (forward_shine > 0)
        {
            counter++;
        }

        if (a > 0)
        {
            last_flashlight = i;
            is_last_lightened = (forward_shine > 0) ? 1 : 0;
            forward_shine = a + 1;
        }
        else if (a < 0)
        {
            a = ABS(a);
            if (forward_shine < 0)
            {
                buffer = MIN(i - last_flashlight, MIN(a, ABS(forward_shine)));
                counter += buffer;
                if (buffer == (i - last_flashlight))
                {
                    is_last_lightened = 1;
                }
            }
            if ((is_last_lightened == 0) && (a >= i - last_flashlight) && (last_flashlight != -1))
            {
                counter++;
            }
            last_flashlight = i;
            is_last_lightened = (forward_shine > 0) ? 1 : 0;
            forward_shine = 1;
        }

        forward_shine--;
    }

    return counter;
}

int main(void)
{
    int n;
    scanf("%d", &n);
    printf("%d", lighten(n));
    return 0;
}