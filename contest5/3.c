#include <stdio.h>
#include <stdlib.h>

typedef struct vector
{
    int *array;
    int size;
    int idx;
} Vector;

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

void *xrealloc(void *array, int size)
{
    void *ptr = realloc(array, sizeof(int) * size);
    if (ptr == NULL)
    {
        printf("Memory Error");
        exit(137);
    }
    return ptr;
}

void append(Vector *v, int elem)
{
    if ((*v).idx + 1 >= (*v).size)
    {
        (*v).array = xrealloc(v->array, v->size * 2);
        (*v).size *= 2;
    }
    (*v).array[v->idx++] = elem;
}

void print_vector(Vector v)
{
    for (int i = 0; i < v.idx; i += 2)
    {
        printf("%d ", v.array[i]);
    }
    for (int i = 1; i < v.idx; i += 2)
    {
        printf("%d ", v.array[i]);
    }
}

int main(void)
{
    Vector v;
    v.array = (int *)calloc(1, sizeof(int));
    v.size = 1;
    v.idx = 0;

    int c;
    scanf("%d", &c);
    while (c != 0)
    {
        append(&v, c);
        scanf("%d", &c);
    }
    print_vector(v);
    free(v.array);

    return 0;
}