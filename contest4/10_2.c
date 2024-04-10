#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LENGTH 100

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) < (b) ? (b) : (a))


int prefix_function(const char *s)
{
    int len = strlen(s);
    int prefixes[STRING_LENGTH];

    int j = 0;
    for (int i = 1; i < len; i++)
    {
        j = prefixes[i - 1];
        while (j > 0 && (s[i] != s[j]))
        {
            j = prefixes[j - 1];
        }
        if(s[i] == s[j])
        {
            j++;
        }
        prefixes[i] = j;
    }
    return j;
}

int main(void)
{
    char s1[STRING_LENGTH];
    char s2[STRING_LENGTH];
    scanf("%s %s", s1, s2);

    char delimiter[1];
    delimiter[0] = ' ';

    char s1s2[2 * STRING_LENGTH];
    strcat(s1s2, s1);
    strcat(s1s2, delimiter);
    strcat(s1s2, s2);

    char s2s1[2 * STRING_LENGTH];
    strcat(s2s1, s2);
    strcat(s2s1, delimiter);
    strcat(s2s1, s1); 

    int result1 = prefix_function(s1s2);
    int result2 = prefix_function(s2s1);
    printf("%d %d", result1, result2);

    return 0;
}