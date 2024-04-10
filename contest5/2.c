#include <stdio.h>
#include <stdlib.h>

void *allocate(size_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL)
    {
        printf("MEMORY ALLOCATION ERROR!");
        exit(137);
    }
    return ptr;
}

long long get_matrix_trace(int n, int m, int ***matrix)
{
    long long trace = 0;

    *matrix = (int **)allocate(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        (*matrix)[i] = (int *)allocate(m * sizeof(int));
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &((*matrix)[i][j]));
            if (i == j)
            {
                trace += (*matrix)[i][j];
            }
        }
    }

    return trace;
}

void free_matrix(int n, int **matrix)
{
    if (matrix != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            free(matrix[i]);
        }
        free(matrix);
    }
}

void print_matrix(int n, int m, int **matrix)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        putchar('\n');
    }
}

int main(void)
{
    int n;
    scanf("%d", &n);

    long long max_trace = 0;
    int **result = NULL;
    int rsize = 0;

    for (int i = 0; i < n; i++)
    {
        int size;
        scanf("%d", &size);
        int **matrix = NULL;

        long long trace = get_matrix_trace(size, size, &matrix);
        if (trace > max_trace)
        {
            free_matrix(rsize, result);
            max_trace = trace;
            result = matrix;
            rsize = size;
        }
        else
        {
            free_matrix(size, matrix);
        }
    }

    print_matrix(rsize, rsize, result);
    free_matrix(rsize, result);

    return 0;
}