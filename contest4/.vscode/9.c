#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#define MAX_VALUE 2000005
#define STRING_LENGTH 2000005

#define SPACES_BETWEEN_PAGES 4
#define LINE_BRAKES 2

typedef struct word_info
{
    ptrdiff_t begin;
    int length;
    int spaces_before;
    int spaces_after;
    int line_brakes_before;
} Word;

char str[STRING_LENGTH];

int k, c, s;
Word book[MAX_VALUE][MAX_VALUE];

void print_matrix(void)
{
    for (int i = 0; i < MAX_VALUE; i++)
    {
        for (int j = 0; j < MAX_VALUE; j++)
        {
            if (book[i][j].length != 0)
            {
                Word w = book[i][j];
                for (int _ = 0; _ < w.spaces_before; _++)
                {
                    putchar(' ');
                }
                for (int _ = 0; _ < w.line_brakes_before; _++)
                {
                    putchar('\n');
                }
                for (int c = w.begin; c < w.begin + w.length; c++)
                {
                    putchar(str[c]);
                }
                for (int _ = 0; _ < w.spaces_after; _++)
                {
                    putchar(' ');
                }
            }
        }
    }
    putchar('\n');
}

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

void append_to_array(Word array[], Word elem, int col_cnt)
{
    int i = col_cnt * k;
    while (array[i].length != 0)
    {
        i++;
    }
    array[i] = elem;
}

int main(void)
{
    scanf("%d ", &k);
    c = 1;
    s = MAX_VALUE;

    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';

    char *word = strtok(str, " ");

    int word_cnt = 0;
    int str_lentgh = 0;

    int row_cnt = 0;
    int col_cnt = 0;
    int list_cnt = 0;

    while (1)
    {
        Word w;
        w.length = (word == NULL) ? STRING_LENGTH : strlen(word);
        w.spaces_before = 0;
        w.spaces_after = 0;
        w.line_brakes_before = 0;

        if (str_lentgh + word_cnt + w.length > k)
        {
            int space_count = word_cnt - 1;
            if (space_count == 0)
            {
                book[row_cnt + list_cnt * s][col_cnt * k].spaces_after = k - str_lentgh;
            }
            else
            {
                int min_space_size = get_min_space_size(str_lentgh, space_count);
                int max_space_size = min_space_size + 1;
                int max_space_usage = get_max_space_usage(str_lentgh, space_count);

                for (int i = 1; i <= space_count; i++)
                {
                    if (book[row_cnt + list_cnt * s][col_cnt * k + i].length == 0)
                    {
                        break;
                    }
                    if (max_space_usage-- > 0)
                    {
                        book[row_cnt + list_cnt * s][col_cnt * k + i].spaces_before = max_space_size;
                    }
                    else
                    {
                        book[row_cnt + list_cnt * s][col_cnt * k + i].spaces_before = min_space_size;
                    }
                }
            }

            if (word == NULL)
            {
                break;
            }

            word_cnt = 0;
            str_lentgh = 0;
            row_cnt++;

            if (row_cnt >= s)
            {
                row_cnt = 0;
                col_cnt++;
                if (col_cnt >= c)
                {
                    col_cnt = 0;
                    list_cnt++;
                    w.line_brakes_before += LINE_BRAKES;
                }
            }

            if (col_cnt != 0)
            {
                w.spaces_before = SPACES_BETWEEN_PAGES;
            }
            else
            {
                w.line_brakes_before += 1;
            }
        }

        w.begin = word - str;
        append_to_array(book[row_cnt + list_cnt * s], w, col_cnt);

        word_cnt++;
        str_lentgh += w.length;

        word = strtok(NULL, " ");
    }

    print_matrix();

    return 0;
}