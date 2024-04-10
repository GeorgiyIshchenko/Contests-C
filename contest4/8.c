#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LENGTH 105

int main(void)
{
    char s[LENGTH];
    fgets(s, sizeof(s), stdin);
    s[strlen(s) - 1] = '\0';
    
    int str_len = strlen(s);

    int cnt = 0;
    int hundreds, tens, units;

    int h_ind, t_ind, u_ind;
    for (int i = 100; i < 1000; i++)
    {
        hundreds = i / 100;
        tens = (i / 10) % 10;
        units = i % 10;
        t_ind = -1;
        u_ind = -1;
        for (h_ind = 0; h_ind < str_len; h_ind++)
        {
            if (((int)(s[h_ind]) - 48) == hundreds)
            {
                t_ind = h_ind + 1;
                break;
            }
        }
        if (t_ind != -1)
        {
            for (; t_ind < str_len; t_ind++)
            {
                if (((int)(s[t_ind]) - 48) == tens)
                {
                    u_ind = t_ind + 1;
                    break;
                }
            }
            if (u_ind != -1)
            {
                for (; u_ind < str_len; u_ind++)
                {
                    if (((int)(s[u_ind]) - 48) == units)
                    {
                        cnt++;
                        break;
                    }
                }
            }
        }
    }

    printf("%d", cnt);

    return 0;
}