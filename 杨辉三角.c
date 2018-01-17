// 《品悟C》
#include <stdio.h>
#define N 10

int main(void)
{
    int a[N] = {1};
    for (int line = 0; line < N; line++)
    {
        for (int i = line; i > 0; i--)
            a[i] += a[i - 1];
        for (int i = 0; i <= line; i++)
            printf(" %3d", a[i]);
        putchar('\n');
    }
}
