#pragma GCC diagnostic ignored "-Wsizeof-array-argument" // 手动测试时注释掉
#pragma clang diagnostic ignored "-Wunevaluated-expression"

#include <stdio.h>

#define PRINT(a) printf("sizeof(" #a ") = %zu where " #a " = %d\n", sizeof(a), a)
#define PRINTP(a) printf("sizeof(" #a ") = %zu where " #a " = %p\n", sizeof(a), (void*)a)

int Fun1(void) {
    return 16;
}

void Fun2(int d[3]) {
    PRINTP(d); // sizeof(d) = 8
    // warning: 'sizeof' on array function parameter 'd' will return size of 'int *' instead of 'int [3]'
}

void Fun3(int (*d)[3]) {
    PRINTP(d);  // sizeof(d) = 8
    PRINTP(*d); // sizeof(*d) = 12
}

void Fun4(int (*d)[]) {
    // PRINT(*d);
    // error: invalid application of 'sizeof' to an incomplete type 'int []'
}

int main(void) {
    int a = 11;
    int *b = &a;
    int c[] = {13, 14};
    int d[3] = {15};
    void *e = NULL;

    printf("sizeof(++a) = %zu, ", sizeof(++a)); // sizeof(++a) = 4; warning: expression with side effects has no effect in an unevaluated context
    printf("a = %d\n", a);                      // a = 11

    PRINTP(b); // sizeof(b) = 8
    PRINT(*b); // sizeof(*b) = 4 where *b = 11

    PRINTP(c);   // sizeof(c) = 8
    PRINT(c[0]); // sizeof(c[0]) = 4 where c[0] = 13

    PRINTP(d);   // sizeof(d) = 12
    PRINT(d[0]); // sizeof(d[0]) = 4 where d[0] = 15

    PRINT(Fun1()); // sizeof(Fun1()) = 4 where Fun1() = 16，计算的返回值，没啥特别的
    PRINTP(&Fun1); // sizeof(&Fun1()) = 8，另有标准不允许函数转void*的警告
    PRINTP(Fun1);  // sizeof(Fun1) = 1，标准不允许sizeof计算函数

    Fun2(d);
    Fun3(&d);
    // Fun4(&d);

    PRINTP(e); // sizeof(e) = 8
}
