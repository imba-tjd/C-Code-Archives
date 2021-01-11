// 这种把比较函数声明为强类型，调用时强转函数指针的做法是否没问题？本文件中的测试MinGW和WSL全部通过，但是网上的用法都是在函数内强转
// 如果调用时不强转函数指针，会报不兼容类型
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int a1[] = {12, 32, 42, 51, 8, 16, 51, 21, 19, 9};
static double a2[] = {32.1, 456.87, 332.67, 442.0, 98.12, 451.79, 340.12, 54.55, 99.87, 72.5};
static const char *a3[] = {"enter", "number", "size", "begin", "of", "cat", "case"};
static char a4[][7] = {"enter", "number", "size", "begin", "of", "cat", "case"};

int c1(const int *a, const int *b) {
    return *a - *b;
}

int c2(const double *a, const double *b) {
    return *a - *b;
}

int c3(const char **a, const char **b) { // 严格来说就应该这样，参数类型是数组元素再取指针
    return strcmp(*a, *b);
}

int c4(const char *a, const char *b) { // 等价于普通的strcmp
    return strcmp(a, b);
}

void PRINT(void) {

#define PR(arr, type, n)               \
    for (size_t i = 0; i < n; i++)   \
        printf(type " ", arr[i]); \
    putchar('\n');

    PR(a1, "%d", sizeof(a1) / sizeof(*a1));
    PR(a2, "%g", sizeof(a2) / sizeof(*a2));
    PR(a3, "%s", sizeof(a3) / sizeof(*a3));
    PR(a4, "%s", sizeof(a4) / sizeof(*a4));
    putchar('\n');
}

int main(void) {
    PRINT();

#define EXPAND(arr, fun) arr, sizeof(arr) / sizeof(*arr), sizeof(*arr), (int (*)(const void *, const void *))fun
    qsort(EXPAND(a1, c1));
    qsort(EXPAND(a2, c2));
    qsort(EXPAND(a3, c3));
    qsort(EXPAND(a4, c4));

    PRINT();
}
