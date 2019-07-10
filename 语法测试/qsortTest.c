// 这种把比较函数声明为强类型，调用时强转的做法是否没问题？根据这些测试是没问题的
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int a1[] = {12, 32, 42, 51, 8, 16, 51, 21, 19, 9};
static double a2[] = {32.1, 456.87, 332.67, 442.0, 98.12, 451.79, 340.12, 54.55, 99.87, 72.5};
static const char *a3[] = {"enter", "number", "size", "begin", "of", "cat", "case"};
static char a4[][7] = {"enter", "number", "size", "begin", "of", "cat", "case"};

int c1(int *a, int *b)
{
    return *a >= *b ? *a > *b ? 1 : 0 : -1;
}

int c2(double *a, double *b)
{
    return *a >= *b ? *a > *b ? 1 : 0 : -1;
}

int c3(const char **a, const char **b)
{
    return strcmp(*a, *b);
}

int c4(const char *a, const char *b) // 其实就是原版strcmp
{
    return strcmp(a, b);
}

void PRINT(void)
{

#define PR(a, b, n)               \
    for (size_t i = 0; i < n; i++)   \
        printf("%" #b " ", a[i]); \
    putchar('\n');

    PR(a1, d, sizeof(a1) / sizeof(*a1));
    PR(a2, g, sizeof(a2) / sizeof(*a2));
    PR(a3, s, sizeof(a3) / sizeof(*a3));
    PR(a4, s, sizeof(a4) / sizeof(*a4));
    putchar('\n');
}

int main(void)
{
    PRINT();

#define EXPAND(arr, fun) arr, sizeof(arr) / sizeof(*arr), sizeof(*arr), (int (*)(const void *, const void *))fun
    qsort(EXPAND(a1, c1));
    qsort(EXPAND(a2, c2));
    qsort(EXPAND(a3, c3));
    qsort(EXPAND(a4, c4));

    PRINT();
    return 0;
}
