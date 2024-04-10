#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *xmalloc(size_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL)
    {
        printf("MEMORY ALLOCATION ERROR!");
        exit(137);
    }
    return ptr;
}


void read_string(char *str, int size)
{
    int counter = 0;
    char scanner;
    while (counter < size)
    {
        scanner = getchar();
        if (scanner != ' ' && scanner != '\n')
        {
            str[counter++] = scanner;
        }
    }
}


void print_string(char *str, int size)
{
    for(int i = 0; i < size; i++)
    {
        putchar(str[i]);
    }
}


int main(void)
{
    int n;
    scanf("%d ", &n);

    char *s1 = (char*)xmalloc(n * sizeof(char));
    read_string(s1, n);

    char *s2 = (char*)xmalloc(n * sizeof(char));
    read_string(s2, n);

    char *s3 = (char*)xmalloc(n * sizeof(char));
    read_string(s3, n);

    print_string(s3, n);
    free(s3);

    print_string(s1, n);
    free(s1);

    print_string(s2, n);
    free(s2);

    return 0;
}