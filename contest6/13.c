#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_LINE_SIZE (20 * 101 + 1)
#define MAX_FIELD_AMOUNT 20
#define INPUT "input.txt"
#define OUTPUT "output.txt"

int ROW;

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

void *xrealloc(void *array, int size)
{
    void *ptr = realloc(array, size);
    if (ptr == NULL)
    {
        printf("Memory;Error");
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

typedef enum
{
    STRING,
    NUM
} field_type;

typedef union
{
    int num;
    char *string;
} field_data;

typedef struct f
{
    field_type type;
    field_data data;
} Field;

typedef struct o
{
    Field *fields;
} Object;

int string_to_digit(char *s, int len)
{
    int num = 0;
    int k = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        if (i == 0 && s[0] == '-')
        {
            return -num;
        }
        num += ((int)pow(10, k)) * (s[i] - '0');
        k++;
    }
    return num;
}

char *get_clear_string(char *s, int len)
{
    int idx = 0;
    int quotes_count = 0;
    char *newString = (char*)xmalloc(sizeof(char) * len);
    for(int i = 0; i < len; i++)
    {
        if (s[i] == '\"')
        {
            quotes_count++;
        }
        if (s[i] != ' ' || quotes_count == 1)
        {
            newString[idx] = s[i];
            idx++;
        }
    }
    newString = (char*)xrealloc(newString, sizeof(char) * (idx + 1));
    newString[idx] = '\0';
    return newString;
}

void freeObjects(Object *objects, int size, int field_amount)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < field_amount; j++)
        {
            if (objects[i].fields[j].type == STRING)
            {
                xfree(objects[i].fields[j].data.string);
            }
        }
    }
}

int compareObjects(const void *a, const void *b)
{
    Object objectA = *(Object *)a;
    Object objectB = *(Object *)b;
    Field fieldA = objectA.fields[ROW];
    Field fieldB = objectB.fields[ROW];
    if (objectA.fields[ROW].type == NUM)
    {
        return fieldA.data.num - fieldB.data.num;
    }
    else
    {
        return strcmp(fieldA.data.string, fieldB.data.string);
    }
}

int main(void)
{
    FILE *input = fopen(INPUT, "r");
    fscanf(input, "%d\n", &ROW);

    char *scanner = (char *)xmalloc(sizeof(char) * MAX_LINE_SIZE);
    int real_size = 0;
    int size = 2;
    int field_amount = -1;
    Object *objectArray = (Object *)xmalloc(sizeof(Object) * size);
    while (fgets(scanner, MAX_LINE_SIZE, input))
    {
        int len_string = strlen(scanner);
        if (scanner[len_string - 1] == '\n')
            scanner[len_string - 1] = '\0';

        char *word = strtok(scanner, ";");
        if (real_size >= size)
        {
            size *= 2;
            objectArray = (Object *)xrealloc(objectArray, sizeof(Object) * size);
        }
        if (field_amount == -1)
            objectArray[real_size].fields = (Field *)xmalloc(sizeof(Field) * MAX_FIELD_AMOUNT);
        else
            objectArray[real_size].fields = (Field *)xmalloc(sizeof(Field) * field_amount);
        int field_cnt = 0;
        while (word != NULL)
        {
            char *clear_string = get_clear_string(word, strlen(word));
            if (isdigit(clear_string[0]) || clear_string[0] == '-')
            {
                int digit = string_to_digit(clear_string, strlen(clear_string));
                objectArray[real_size].fields[field_cnt].type = NUM;
                objectArray[real_size].fields[field_cnt].data.num = digit;
            }
            else
            {
                int len = strlen(clear_string);
                objectArray[real_size].fields[field_cnt].type = STRING;
                objectArray[real_size].fields[field_cnt].data.string = (char *)xmalloc(sizeof(char) * (len + 1));
                strcpy(objectArray[real_size].fields[field_cnt].data.string, clear_string);
                objectArray[real_size].fields[field_cnt].data.string[len] = '\0';
            }
            xfree(clear_string);
            field_cnt++;
            word = strtok(NULL, ";");
        }
        if (field_amount == -1)
            field_amount = field_cnt;
        real_size++;
    }
    xfree(scanner);
    fclose(input);

    qsort(objectArray, real_size, sizeof(Object), compareObjects);

    FILE *output = fopen(OUTPUT, "w");
    for (int i = 0; i < real_size; i++)
    {
        for (int j = 0; j < field_amount; j++)
        {
            Field field = objectArray[i].fields[j];
            if (field.type == NUM)
            {
                fprintf(output, "%d", field.data.num);
            }
            else
            {
                fprintf(output, "%s", field.data.string);
            }
            if (j != field_amount - 1)
                fprintf(output, ";");
        }
        fprintf(output, "\n");
    }

    freeObjects(objectArray, real_size, field_amount);
    fclose(output);
    return 0;
}