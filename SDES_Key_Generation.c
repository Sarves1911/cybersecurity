#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int main()
{
    int p[10] = {1, 0, 1, 0, 0, 0, 0, 0, 1, 0};

    // p10
    // 3 5 2 7 4 10 1 9 8 6
    int p10[10];
    p10[0] = p[2];
    p10[1] = p[4];
    p10[2] = p[1];
    p10[3] = p[6];
    p10[4] = p[3];
    p10[5] = p[9];
    p10[6] = p[0];
    p10[7] = p[8];
    p10[8] = p[7];
    p10[9] = p[5];

    for (int i = 0; i < 10; i++)
    {
        printf("%d ", p10[i]);
    }
    printf("\n");

    // dividing p10 into 2 sub arrays
    int p10_1[5];
    int p10_2[5];

    for (int i = 0; i < 5; i++)
    {
        p10_1[i] = p10[i];
        p10_2[i] = p10[i + 5];
    }

    // left shift
    int temp = p10_1[0];
    for (int i = 0; i < 4; i++)
    {
        p10_1[i] = p10_1[i + 1];
    }
    p10_1[4] = temp;

    temp = p10_2[0];
    for (int i = 0; i < 4; i++)
    {
        p10_2[i] = p10_2[i + 1];
    }
    p10_2[4] = temp;

    // combination of left shifted arrays
    int p10_new[10];

    for (int i = 0; i < 10; i++)
    {
        if (i < 5)
        {
            p10_new[i] = p10_1[i];
        }
        else
        {
            p10_new[i] = p10_2[i - 5];
        }
    }

    // p8
    // 6 3 7 4 8 5 10 9
    int p8[8];
    p8[0] = p10_new[5];
    p8[1] = p10_new[2];
    p8[2] = p10_new[6];
    p8[3] = p10_new[3];
    p8[4] = p10_new[7];
    p8[5] = p10_new[4];
    p8[6] = p10_new[9];
    p8[7] = p10_new[8];

    printf("Key 1: ");
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", p8[i]);
    }
    printf("\n");

    // left shift 2
    for (int shift = 0; shift < 2; shift++)
    {
        int temp1 = p10_1[0];
        for (int i = 0; i < 4; i++)
        {
            p10_1[i] = p10_1[i + 1];
        }
        p10_1[4] = temp1;

        temp1 = p10_2[0];
        for (int i = 0; i < 4; i++)
        {
            p10_2[i] = p10_2[i + 1];
        }
        p10_2[4] = temp1;
    }

    // combination of 2nd left shift

    int p10_new_new[10];

    for (int i = 0; i < 10; i++)
    {
        if (i < 5)
        {
            p10_new_new[i] = p10_1[i];
        }
        else
        {
            p10_new_new[i] = p10_2[i - 5];
        }
    }

    // p8
    // 6 3 7 4 8 5 10 9

    p8[0] = p10_new_new[5];
    p8[1] = p10_new_new[2];
    p8[2] = p10_new_new[6];
    p8[3] = p10_new_new[3];
    p8[4] = p10_new_new[7];
    p8[5] = p10_new_new[4];
    p8[6] = p10_new_new[9];
    p8[7] = p10_new_new[8];

    printf("Key 2: ");
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", p8[i]);
    }
    printf("\n");

    return 0;
}
