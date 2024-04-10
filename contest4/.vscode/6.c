#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#define STRING_LENGTH 2000005

char str[STRING_LENGTH];

int k;


int get_min_space_size(int str_length, int space_count)
{
    if (space_count == 0)
    {
        return k - str_length;
    }
    else
    {
        return (k - str_length) / space_count;
    }
}

int get_max_space_usage(int str_length, int space_count)
{
    int min_space_size = get_min_space_size(str_length, space_count);
    int space_length = k - str_length;
    return space_length - min_space_size * space_count;
}

int main(void)
{
    scanf("%d ", &k);

    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';

    char *word = strtok(str, " ");

    int word_cnt = 0;
    int len = 

    int mn_ss = get_min_space_size()
    while (1)
    {
        
        word = strtok(NULL, " ");
    }

    print_matrix();

    return 0;
}