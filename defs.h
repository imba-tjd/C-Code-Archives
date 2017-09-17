// 《C语言解惑》
#include <stdio.h>

#define PR (fmt, val) printf(#val " = %" #fmt "\t", (val))
#define NL putchar('\n')

#define PRINT1 (f, x1) PR(f, x1), NL // 如果为分号，则扩展后是多条语句，易出错
#define PRINT2 (f, x1, x2) PR(f, mx1), PRINT1(f, x2)
#define PRINT3 (F, x1, x2, x3) PR(f, x1), PRINT2(f, x2, x3)
