#include <stdio.h>

#define INPUT "input.txt"
#define OUTPUT "output.txt"

int main(void)
{
    FILE *input = fopen(INPUT, "r");
    long long result;
    fscanf(input, "%lld ", &result);
    long long buf;
    char sign;
    while(fscanf(input, "%c ", &sign) && fscanf(input, "%lld ", &buf) == 1)
    {
        if (sign == '+')
        {
            result += buf;
        }
        else if (sign == '-')
        {
            result -= buf;
        }
    }
    fclose(input);
    FILE *output = fopen(OUTPUT, "w");
    fprintf(output, "%lld", result);
    fclose(output);
    return 0;
}