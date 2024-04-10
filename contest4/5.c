#include <stdio.h>
#include <string.h>

#define LENGTH 85

void shift_print(const char *str, int shift_value)
{
    int str_len = strlen(str);
    shift_value %= str_len;

    for (int i = 0; i < str_len; i++)
    {
        printf("%c", str[(shift_value + i) % str_len]);
    }
}

int main(void)
{
    int n;
    char s[LENGTH];

    scanf("%d ", &n);

    fgets(s, sizeof(s), stdin);
    s[strlen(s) - 1] = '\0';

    shift_print(s, n);

    return 0;
}