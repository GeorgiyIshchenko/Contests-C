#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

void *xmalloc(size_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL)
    {
        printf("Memory\nerror.");
        exit(0);
    }
    return ptr;
}

void *xrealloc(void *array, int size)
{
    void *ptr = realloc(array, size);
    if (ptr == NULL)
    {
        printf("Memory\nError");
        exit(0);
    }
    return ptr;
}

void reverse_string(char *s)
{
    int len = strlen(s);
    for (int i = 0; i < len / 2; i++)
    {
        char buf = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = buf;
    }
}

char *expand_string(char *str, int required_len)
{
    int len = strlen(str);
    str = (char *)xrealloc(str, (required_len + 1) * sizeof(char));
    for (int i = required_len - 1; i >= required_len - len; i--)
    {
        str[i] = str[i - (required_len - len)];
    }
    for (int i = required_len - len - 1; i >= 0; i--)
    {
        str[i] = '0';
    }
    str[required_len] = '\0';
    return str;
}

char *addition(char *num1, char *num2)
{
    int len = MAX(strlen(num1), strlen(num2));

    char* old1 = num1;
    num1 = expand_string(num1, len);
    if (old1 != num1)
        free(old1);
    char* old2 = num2;
    num2 = expand_string(num2, len);
    if (old2 != num2)
        free(old2);

    int size = len + 2;
    char *result = (char *)xmalloc(size * sizeof(char));
    int result_idx = 0;

    int buf = 0;
    for (int i = 0; i < len; i++)
    {
        int num = 0;
        num = num1[len - i - 1] - '0' + num2[len - i - 1] - '0' + buf;
        result[result_idx] = num % 10 + '0';
        result_idx++;
        buf = num / 10;
    }
    if (buf == 1)
    {
        result[result_idx] = '1';
        result_idx++;
    }
    result_idx++;
    result = (char *)xrealloc(result, sizeof(char) * (result_idx));
    result[result_idx - 1] = '\0';
    reverse_string(result);

    return result;
}

bool a_bigger_b(char *a, char *b, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (a[i] < b[i])
        {
            return false;
        }
        else if (a[i] > b[i])
        {
            return true;
        }
    }
    return true;
}

bool is_equal(char *a, char *b, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (a[i] != b[i])
        {
            return false;
        }
    }
    return true;
}

char *difference(char *num1, char *num2)
{
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int len = MAX(len1, len2);

    int size = len + 3;
    char *result = (char *)xmalloc(size * sizeof(char));
    int result_idx = 0;

    if (strcmp(num2, num1) == 0)
    {
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    if (len2 > len1 || (len1 == len2 && a_bigger_b(num2, num1, len)))
    {
        char *abs_result = difference(num2, num1);
        result[0] = '-';
        result[1] = '\0';
        strcat(result, abs_result);
        return result;
    }

    char* old1 = num1;
    num1 = expand_string(num1, len);
    if (old1 != num1)
        free(old1);
    char* old2 = num2;
    num2 = expand_string(num2, len);
    if (old2 != num2)
        free(old2);

    if (is_equal(num1, num2, len))
    {
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    int buf = 0;
    for (int i = 0; i < len; i++)
    {
        int num = (num1[len - i - 1] - '0') - (num2[len - i - 1] - '0') - buf;
        buf = (num < 0) ? 1 : 0;
        if (num < 0)
        {
            num += 10;
        }
        result[result_idx] = num + '0';
        result_idx++;
    }

    // Подчистка нулей

    for (int i = result_idx - 1; i >= 0; i--)
    {
        if (result[i] == '0')
        {
            result_idx = i;
        }
        else
        {
            break;
        }
    }

    result_idx++;
    result = (char *)xrealloc(result, sizeof(char) * (result_idx));
    result[result_idx - 1] = '\0';
    reverse_string(result);
    return result;
}

char *single_multiplication(char *str_num, char multiplicator, int zeros_count)
{
    int len_num = strlen(str_num);
    int size = len_num + zeros_count + 1;
    char *result = (char *)xmalloc(size * sizeof(char));
    int result_idx = 0;

    for (int i = 0; i < zeros_count; i++)
    {
        result[result_idx] = '0';
        result_idx++;
    }
    int mult_int = multiplicator - '0';
    int buf = 0;
    for (int i = 0; i < len_num; i++)
    {
        int num = (str_num[len_num - 1 - i] - '0') * mult_int + buf;
        result[result_idx] = num % 10 + '0';
        result_idx++;
        buf = num / 10;
    }
    if (buf > 0)
    {
        result[result_idx] = buf + '0';
        result_idx++;
    }
    result_idx++;
    result = (char *)xrealloc(result, sizeof(char) * (result_idx));
    result[result_idx - 1] = '\0';
    reverse_string(result);
    return result;
}

char *multiplication(char *num1, char *num2)
{
    int len2 = strlen(num2);
    char *result = (char *)xmalloc(2 * sizeof(char));
    result[0] = '0';
    result[1] = '\0';
    if (num1[0] == '0' || num2[0] == '0')
    {
        return result;
    }
    for (int i = 0; i < len2; i++)
    {
        char *single_result = single_multiplication(num1, num2[len2 - i - 1], i);
        result = addition(result, single_result);
    }
    free(num1);
    free(num2);
    return result;
}

char *input(void)
{
    int size = 21005;
    int idx = 0;
    char *string = (char *)xmalloc(size * sizeof(char));
    char scanner;
    while ((scanner = getchar(), scanner != '\n' && scanner != EOF))
    {
        string[idx] = scanner;
        idx++;
    }
    string = (char*)xrealloc(string, sizeof(char) * (idx + 1));
    string[idx] = '\0';
    return string;
}

int main(void)
{
    char *s = input();

    char sign = 'z';
    int len = strlen(s);
    int sign_idx = 0;
    for (int i = 0; i < len; i++)
    {
        if (s[i] == '+' || s[i] == '-' || s[i] == '*')
        {
            sign = s[i];
            sign_idx = i;
            break;
        }
    }

    char *num1 = (char*)xmalloc(sizeof(char) * (sign_idx + 1));
    for(int i = 0; i < sign_idx; i++)
    {
        num1[i] = s[i];
    }
    num1[sign_idx] = '\0';
    char *num2 = (char*)xmalloc(sizeof(char) * (len - sign_idx + 1));
    for(int i = 0; i < len - sign_idx; i++)
    {
        num2[i] = s[i + sign_idx + 1];
    }
    num2[len - sign_idx] = '\0'; 
    free(s);
    char *result = NULL;
    if (sign == '+')
    {
        result = addition(num1, num2);
    }
    else if (sign == '-')
    {
        result = difference(num1, num2);
    }
    else if (sign == '*')
    {
        result = multiplication(num1, num2);
    }
    printf("%s", result);
    free(result);
    return 0;
}