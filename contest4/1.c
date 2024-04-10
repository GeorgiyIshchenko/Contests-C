#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LENGTH 10002

#define MIN(a, b) ((a) > (b) ? (b) : (a))

int max_prefix(const char* s1, const char* s2)
{
    int len2 = strlen(s2);
    int min_len = MIN(strlen(s1), len2);

    int max = 0;

    bool flag;

    for(int length = 1; length <= min_len; length++)
    {
        flag = true;
        for(int i = 0; i < length; i++)
        {
            if(s1[i] != s2[len2 - length + i])
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            max = length;
        }
    }

    return max;
}   

int main(void)
{
    char s1[LENGTH];
    char s2[LENGTH];
    fgets(s1, sizeof(s1), stdin);
    s1[strlen(s1) - 1] = '\0';

    fgets(s2, sizeof(s2), stdin);
    s2[strlen(s2) - 1] = '\0';

    printf("%d %d", max_prefix(s1, s2), max_prefix(s2, s1));

    return 0;
}