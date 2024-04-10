#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VALUE 50
#define STRING_LENGTH 300


struct str_word
{
    int begin;
    int length;
    int spaces_after;
};

char str[STRING_LENGTH];

int k, c, s;
struct str_word book[MAX_VALUE][MAX_VALUE];
int row_num = 0;
int col_num = 0;
int list_num = 0;

void print_matrix(void)
{
    int row_cnt = list_num * s;
    row_cnt += row_num > 0 ? row_num + 2 : 0;
    for (int i = 0; i <= row_cnt; i++)
    {
        for (int j = 0; j < c * (k + 4) - 4; j++)
        {
            if (book[i][j].length != 0)
            {
                for (int w = book[i][j].begin; w < book[i][j].begin + book[i][j].length; w++)
                {
                    printf("%c", str[w]);
                }
                for (int w = 0; w < book[i][j].spaces_after; w++)
                {
                    printf(" ");
                }
                j += book[i][j].length - 1;
            }
        }
        printf("\n");
    }
}


void add_word_to_row(int row_num, struct str_word word)
{
    for (int i = 0; i < MAX_VALUE; i++)
    {
        if (book[row_num][i].length == 0)
        {
            book[row_num][i] = word;
        }
    }
}


int get_average_decomposion(int sum, int max_num, int n)
{
    for (int i = 0; i < n; i++)
    {
        if ((max_num * i + (max_num - 1) * (n - i)) == sum)
        {
            return i;
        }
    }
}

int main(void)
{
    scanf("%d %d %d ", &k, &c, &s);

    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';

    char *word = strtok(str, " ");

    int current_length = 0;
    int current_word_cnt = 0;
    int len;

    while (word != NULL)
    {
        len = strlen(word);

        if (current_length + len > k)
        {
            int space_count = current_word_cnt - 1;
            int max_space_size;
            if (space_count != 0)
            {
                max_space_size = ((k - current_length + current_word_cnt) / space_count) + 1;
            }
            else
            {
                max_space_size = k - current_length;
            }
            int max_space_use = get_average_decomposion(k - current_length, max_space_size, space_count);
            for(int i = 0; i < k; i++)
            {
                if(book[row_num + (list_num * (s + 2))][col_num * (k + 4) + i].length != 0)
                {
                    if(max_space_use-- > 0)
                    {
                        book[row_num + (list_num * (s + 2))][col_num * (k + 4) + i].spaces_after = max_space_size;
                    }
                    else
                    {
                        book[row_num + (list_num * (s + 2))][col_num * (k + 4) + i].spaces_after = max_space_size - 1;
                    }
                }
            }

            current_word_cnt = 0;
            current_length = 0;
            row_num++;
            if (row_num > s - 1)
            {
                row_num = 0;
                col_num++;
                if (col_num > c - 1)
                {
                    col_num = 0;
                    list_num++;
                }
            }
        }
        current_word_cnt++;

        struct str_word ws;
        ws.length = len;
        ws.begin = word - str;
        book[row_num + (list_num * (s + 2))][(current_length) + (col_num * (k + 4))] = ws;
        current_length += len;
        if (current_length < k)
        {
            current_length++;
        }
        word = strtok(NULL, " ");
    }

    print_matrix();

    return 0;
}