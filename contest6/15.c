#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define INPUT "input.txt"
#define OUTPUT "output.txt"
#define M 1000033
#define ABS(a) (a >= 0) ? (a) : (-a) 

void *xmalloc(size_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL)
    {
        printf("Memory;error.");
        exit(0);
    }
    return ptr;
}

void xfree(void *ptr)
{
    if (ptr == NULL)
    {
        printf("Memory;Error");
        exit(0);
    }
    free(ptr);
}

typedef struct node
{
    char *string;
    unsigned value;
    struct node *next;
} listNode;


void pushFront(listNode **head, char* s, unsigned value)
{
    listNode *node = (listNode*)xmalloc(sizeof(listNode));
    node->string = (char*)xmalloc(sizeof(char) * 101);
    strcpy(node->string, s);
    node->value = value;
    node->next = *head;
    *head = node;
}


unsigned get_hash(char *s)
{
    int len = strlen(s);
    const unsigned p = 31;
    unsigned hash = 0;
    unsigned k = 1;
    for(int i = 0; i < len; i++)
    {
        hash = (hash + ((s[i] - 'a' + 1) * k)) % M;
        k = (k * p) % M;
    }
    return hash;
}


long long find(listNode *node, char *s)
{
    while(node != NULL)
    {
        if (strcmp(node->string, s) == 0)
        {
            return node->value;
        }
        node = node->next;
    }
    return -1;
}


int main(void)
{
    FILE *input = fopen(INPUT, "r");

    int n;
    fscanf(input, "%d\n", &n);
    listNode **list = (listNode**)xmalloc(M * sizeof(listNode*));
    char *name = (char*)xmalloc(sizeof(char) * 110);
    for (int i = 0; i < n; i++)
    {
        fscanf(input, "%s", name);
        int value;
        fscanf(input, "%u", &value);
        long long hash = get_hash(name);
        pushFront(&list[hash], name, value);
    }
    FILE *output = fopen(OUTPUT, "w");
    fscanf(input, "%d\n", &n);
    for(int i = 0; i < n; i++)
    {
        fscanf(input, "%s", name);
        long long hash = get_hash(name);
        fprintf(output, "%lld", find(list[hash], name));
        fprintf(output, "\n");
    }
    xfree(name);
    for(int i = 0; i < M; i++)
    {
        if (list[i] != NULL)
        {
            listNode *node = list[i];
            while (node != NULL)
            {
                xfree(node->string);
                node = node->next;
            }
        }
    }
    xfree(list);
    fclose(input);
    fclose(output);
    return 0;
}