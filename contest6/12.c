#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define M 26

void *xmalloc(size_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL)
    {
        printf("Memory error.");
        exit(137);
    }
    return ptr;
}

void *xrealloc(void *array, int size)
{
    void *ptr = realloc(array, size);
    if (ptr == NULL)
    {
        printf("Memory Error");
        exit(137);
    }
    return ptr;
}

typedef enum
{
    ident,
    node
} tag;

typedef struct vertex
{
    struct vertex **children;
    tag t;
} Vertex;

void addString(Vertex *root, char *s, int *counter)
{
    Vertex *v = root;
    int len = strlen(s);
    for(int i = 0; i < len; i++)
    {
        char symbol = s[i] - 'a';
        if (v->children == NULL)
        {
            v->children = (Vertex**)xmalloc(sizeof(Vertex*) * SIZE);
        }
        if (v->children[symbol] == NULL)
        {
            v->children[symbol] = (Vertex*)xmalloc(sizeof(Vertex));
            (*counter)++;
        }
        v = v->children[symbol];
    }
}

int main(void)
{
    char *s = (char*)xmalloc(sizeof(char) * 2001);
    scanf("%s", s);

    int len = strlen(s);
    s = (char*)xrealloc(s, sizeof(char) * len);


    int cnt = 0;
    Vertex *root = (Vertex*)xmalloc(sizeof(Vertex));
    root->t = ident;
    root->children = (Vertex**)xmalloc(sizeof(Vertex*) * SIZE);
    for(int i = 0; i < len; i++)
    {
        addString(root, s + i, &cnt);
    }
    printf("%d", cnt);

    return 0;
}