#include "stdio.h"
#include "math.h"

int main(void)
{
    int m[9][9];
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            m[i][j] = 101;
        }
    }
    int v[16];
    for (int i = 0; i < 16; i++)
    {
        scanf("%d", &v[i]);
    }
    int mx_stroke = -1;
    char flag = 1;
    for (int i = 0; i < 8; i++)
    {
        mx_stroke = -1;
        for (int j = 0; j < 8; j++)
        {
            if (v[i] < m[i][j])
            {
                m[i][j] = v[i];
            }
            if (v[8 + j] < m[i][j])
            {
                m[i][j] = v[8 + j];
            }
            // check sum in the stoke (smaller than value in v[i] -> error)
            mx_stroke = m[i][j] > mx_stroke ? m[i][j] : mx_stroke;
        }
        if (mx_stroke < v[i])
        {
            flag = 0;
            break;
        }
    }
    if (flag)
    {
        int mx_coll = -1;
        for (int j = 0; j < 8; j++)
        {
            mx_coll = -1;
            for (int i = 0; i < 8; i++)
            {
                mx_coll = m[i][j] > mx_coll ? m[i][j] : mx_coll;
            }
            if (mx_coll < v[8 + j])
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            int sm = 0;
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    sm += m[i][j];
                }
            }
            printf("%d", sm);
        }
        else
        {
            printf("-1");
        }
    }
    else
    {
        printf("-1");
    }
    return 0;
}