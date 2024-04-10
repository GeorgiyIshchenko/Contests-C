#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LENGTH 2000000

void space_strcat(char* new_string, const char *beginning, const char *ending)
{
    int len_b = strlen(beginning);
    int len_e = strlen(ending);

    int i1, i2;
    for (i1 = 0; i1 < len_b; i1++)
    {
        new_string[i1] = beginning[i1];
    }
    new_string[i1] = ' ';
    for (i2 = 0; i2 < len_e; i2++)
    {
        new_string[i1 + i2 + 1] = ending[i2];
    }
    new_string[i1 + i2 + 1] = '\0';
}

int prefix_function(const char *s)
{
    int len = strlen(s);
    int prefixes[LENGTH];
    prefixes[0] = 0;

    int j = 0;
    for (int i = 1; i < len; i++)
    {
        j = prefixes[i - 1];
        while (j > 0 && s[i] != s[j])
        {
            j = prefixes[j - 1];
        }
        if(s[i] == s[j])
        {
            j++;
        }
        prefixes[i] = j;
    }
    return prefixes[len - 1];
}

int main(void)
{
    char s1[LENGTH];
    char s2[LENGTH];

    fgets(s1, sizeof(s1), stdin);
    s1[strlen(s1) - 1] = '\0';

    fgets(s2, sizeof(s2), stdin);
    s2[strlen(s2) - 1] = '\0';

    char s1s2[2 * LENGTH];
    space_strcat(s1s2, s1, s2);

    char s2s1[2 * LENGTH];
    space_strcat(s2s1, s2, s1);

    printf("%d %d", prefix_function(s1s2), prefix_function(s2s1));

    return 0;
}