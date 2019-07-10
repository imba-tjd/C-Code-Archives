#ifdef TRAVIS
#pragma GCC diagnostic ignored "-Wsizeof-array-argument"
#pragma GCC diagnostic ignored "-Wunused-value"
#endif

#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>

#define PRINT(a) printf("sizeof(" #a ") = %zu where " #a " = %d\n", sizeof(a), a)
#define PRINTP(a) printf("sizeof(" #a ") = %zu where " #a " = %p\n", sizeof(a), a)

int Fun1(void)
{
    return 16;
}

void Fun2(int d[3])
{
    PRINTP(d); // sizeof(d) = 8
    // sizeof on array function parameter will return size of 'int *' instead of 'int [3]'
}

void Fun3(int (*d)[3])
{
    PRINTP(d);  // sizeof(d) = 8
    PRINTP(*d); // sizeof(*d) = 12
}

void Fun4(int (*d)[])
{
    // PRINT(*d);
    // error: invalid application of 'sizeof' to an incomplete type 'int []'
}

int main(void)
{
    int a = 11;
    int *b = &a;
    int c[] = {13, 14};
    int d[3] = {15};
    void *e = NULL;

    printf("sizeof(++a) = %zu, ", sizeof(++a)); // sizeof(++a) = 4; expression with side effects has no effect in an unevaluated context
    printf("a = %d\n", a);                      // a = 11,

    PRINTP(b); // sizeof(b) = 8
    PRINT(*b); // sizeof(*b) = 4 where *b = 11

    PRINTP(c);   // sizeof(c) = 8
    PRINT(c[0]); // sizeof(c[0]) = 4 where c[0] = 13

    PRINTP(d);   // sizeof(d) = 12
    PRINT(d[0]); // sizeof(d[0]) = 4 where d[0] = 15

    PRINT(Fun1()); // sizeof(Fun1()) = 4 where Fun1() = 16，前者即函数的返回类型的大小
    PRINTP(&Fun1); // sizeof(&Fun1()) = 8
    PRINTP(Fun1);  // sizeof(Fun1) = 1，不会报错和警告，但是标准说sizeof不允许计算函数

    Fun2(d);
    Fun3(&d);
    // Fun4(&d);

    PRINTP(e); // sizeof(e) = 8

    return 0;
}
