#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define CITY_MAX_LENGTH 25
#define CITY_MAX_COUNT 10
#define NULL_SYMBOL '\0'


static int cities_size;
static char cities[CITY_MAX_COUNT][CITY_MAX_LENGTH];

static int max_chain_length = 0;
static int results[CITY_MAX_COUNT];

bool is_used(int used, int position)
{
    return (used >> position) % 2;
}

int make_used(int used, int position)
{
    return (used | (1 << position));
}

int get_length(int used)
{
    int length = 0;
    for(int i = 0; i < 32; i++)
    {
        length += (used >> i) % 2;
    }
    return length;
}

void word_recursion(const char* previous_city, const int first_city_index, int used)
{
    bool has_chain_continuation = false;
    int pc_len = strlen(previous_city);

    for(int city = 0; city < cities_size; city++)
    {
        if (!is_used(used, city))
        {
            if(pc_len)
            {
                if(cities[city][0] == previous_city[pc_len - 1])
                {
                    has_chain_continuation = true;
                    word_recursion(cities[city], first_city_index, make_used(used, city));
                }
            }
            else
            {
                // Initial cycle
                has_chain_continuation = true;
                word_recursion(cities[city], city, make_used(used, city));
            }
        }
    }

    if(!has_chain_continuation)
    {
        int len = get_length(used);
        max_chain_length = max_chain_length < len ? len : max_chain_length;
        results[first_city_index] = results[first_city_index] < len ? len : results[first_city_index];
        return;
    }
}

int main(void)
{
    scanf("%d ", &cities_size);
    
    char *s;
    for (int i = 0; i < cities_size; i++)
    {
        s = cities[i];
        fgets(s, CITY_MAX_LENGTH, stdin);
        s[strlen(s) - 1] = '\0';
    }

    char *initial_emptiness = "";
    word_recursion(initial_emptiness, -1, 0);

    printf("%d\n", max_chain_length);
    for(int i = 0; i < cities_size; i++)
    {
        if (results[i] == max_chain_length)
        {
            printf("%s\n", cities[i]);
        }
    }
    return 0;
}
