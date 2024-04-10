#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EPSILON 1e-10

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

void read_matrix(double ***matrix, int n)
{
    *matrix = (double **)xmalloc(sizeof(double *) * n);
    for (int i = 0; i < n; i++)
    {
        (*matrix)[i] = (double *)xmalloc(sizeof(double) * (n + 1));
        for (int j = 0; j < n + 1; j++)
        {
            scanf("%lf", &((*matrix)[i][j]));
        }
    }
}





double *gauss(double **matrix, int size)
{
    double max;
    int k = 0;
    int max_idx;
    while (k < size)
    {
        max = matrix[k][k];
        max_idx = k;
        for (int i = k + 1; i < size; i++)
        {
            if (matrix[i][k] > max)
            {
                max = matrix[i][k];
                max_idx = i;
            }
        }
        for (int i = 0; i < size + 1; i++)
        {
            double buf = matrix[k][i];
            matrix[k][i] = matrix[max_idx][i];
            matrix[max_idx][i] = buf;
        }
        for (int i = k; i < size; i++)
        {
            double buf = matrix[i][k];
            if (-EPSILON < buf && buf < EPSILON)
            {
                continue;
            }
            for (int j = 0; j < size + 1; j++)
            {
                matrix[i][j] = matrix[i][j] / buf;
            }
            if (i != k)
            {
                for (int j = 0; j < size + 1; j++)
                {
                    matrix[i][j] = matrix[i][j] - matrix[k][j];
                }
            }
        }
        k++;
    }
    double *x = (double*)xmalloc(size * sizeof(double));
    for (int i = size - 1; i >= 0; i--)
    {
        x[i] = matrix[i][size];
        for(int j = 0; j < i; j++)
        {
            matrix[j][size] -= matrix[j][i] * x[i];
        }
    }
    return x;
}

int main(void)
{
    int n;
    scanf("%d", &n);

    double **matrix;
    read_matrix(&matrix, n);

    double *x = gauss(matrix, n);
    for(int i = 0; i < n; i++)
    {
        printf("%lld\n", (long long)round(x[i]));
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}