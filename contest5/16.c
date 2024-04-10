/*
Апельсин
Трек – СЕРЕГА ПИРАТ
Текст песни
Ммм
Yeah c'mon
Давай с тобою вместе споём
Давай с тобою вместе споём
Давай с тобою вместе вдвоём
Кислый, кислый
Кислый тип, от меня все жмурятся
Gangsta shit, да, живу на улице
Не пизди, что тебе не нравится
Подойди, я останусь на лице
Самый крутой, из меня течёт сок
Сука, самый крутой, с меня течёт су-ка
Для тебя я - не друг
Для тебя я так крут
Я тот ещё фрукт
У-у, е-е-е
Я всего-лишь апельсин (что блять?)
Ведь я всего-лишь апельсин
Вас миллион, а я один
Ведь я всего-лишь апельсин
Вас миллион, а я один
SHEEEESH
SWAAAAG (оу, е-е-е-е-е)
Апельсин
Тут со мной капуста (sheesh)
Твоя жизнь просто мусор (sheesh)
Сын белого арбуза (sheesh)
Сука, в тебе так пусто (sheesh)
Я не понимаю, почему ты ещё тут?
Я наваливаю рэп, в котором я тебя ебу
Нам по кайфу витать
Мне по кайфу ебать
Тех лохов, что хотят
Моих братьев сожрать
У-у, е-е-е
Я всего-лишь апельсин (не, это надо поменять)
Ведь я всего-лишь апельсин
Вас миллион, а я один
Ведь я всего-лишь апельсин
Вас миллион, а я один (skrrr)
Тут со мной капуста (sheesh)
Твоя жизнь просто мусор (swa-a-ag)
Сын гнилого арбуза (оу, е-е-е)
Сука, в тебе так пусто
Я не понимаю, почему ты ещё тут?
Я наваливаю рэп, в котором я тебя ебу
Нам по кайфу витать
Мне по кайфу ебать
Тех лохов, что хотят
Моих братьев сожрать
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef struct matrix
{
    int width;
    int height;
    int **value;
} Matrix;

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

void free_matrix(Matrix m)
{
    for (int i = 0; i < m.height; i++)
    {
        free(m.value[i]);
    }
    free(m.value);
}

void print_matrix(Matrix m)
{
    for (int i = 0; i < m.height; i++)
    {
        for (int j = 0; j < m.width; j++)
        {
            printf("%d ", m.value[i][j]);
        }
        putchar('\n');
    }
}

Matrix matrix_multiplication(Matrix m1, Matrix m2, int p)
{
    Matrix result;
    result.height = m1.height;
    result.width = m2.width;
    result.value = (int **)xmalloc(sizeof(int *) * result.height);
    for (int i = 0; i < result.height; i++)
    {
        result.value[i] = (int *)xmalloc(sizeof(int) * result.height);
        for (int j = 0; j < result.width; j++)
        {
            result.value[i][j] = 0;
            for (int _ = 0; _ < m1.width; _++)
            {
                long long new_value = result.value[i][j] + m1.value[i][_] * (long long)m2.value[_][j];
                result.value[i][j] = new_value % p;
            }
        }
    }
    return result;
}

Matrix init_e(int size)
{
    Matrix m;
    m.height = size;
    m.width = size;
    m.value = (int **)xmalloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        m.value[i] = (int *)xmalloc(size * sizeof(int));
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {
                m.value[i][j] = 1;
            }
            else
            {
                m.value[i][j] = 0;
            }
        }
    }
    return m;
}

Matrix pow_matrix(Matrix m, int pow, int p)
{
    Matrix result = init_e(m.width);
    while (pow > 0)
    {
        if (pow % 2 == 1)
        {
            Matrix *old_res = &result;
            result = matrix_multiplication(result, m, p);
            if (old_res != &result)
                free_matrix(result);
        }
        m = matrix_multiplication(m, m, p);
        pow /= 2;
    }
    free_matrix(m);
    return result;
}

int main(void)
{
    int k, N, p;
    scanf("%d %d %d", &k, &N, &p);
    int **f_array = (int **)xmalloc(k * sizeof(int *));
    for (int i = 0; i < k; i++)
    {
        f_array[k - i - 1] = (int *)xmalloc(sizeof(int));
        scanf("%d", &f_array[k - i - 1][0]);
    }
    int **matrix = (int **)xmalloc(k * sizeof(int *));
    matrix[0] = (int *)xmalloc(k * sizeof(int));
    for (int i = 0; i < k; i++)
    {
        scanf("%d", &matrix[0][i]);
    }
    for (int i = 1; i < k; i++)
    {
        matrix[i] = (int *)xmalloc(k * sizeof(int));
        for(int j = 0; j < k; j++)
        {
            matrix[i][j] = 0;
        }
        matrix[i][i - 1] = 1;
    }
    Matrix m = {.height = k, .width = k, .value = matrix};
    Matrix f = {.height = k, .width = 1, .value = f_array};
    Matrix result = pow_matrix(m, N - 1, p);
    result = matrix_multiplication(result, f, p);
    printf("%d", result.value[k - 1][0]);
    free_matrix(m);
    free_matrix(f);
    free_matrix(result);
    return 0;
}