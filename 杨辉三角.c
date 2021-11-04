// 《品悟C》
// 每次循环会改变原来的数组，从后往前扫描，自己最开始是零，新自己等于自己加左边的数
#include <stdio.h>
#define N 10

int main(void) {
    int a[N] = {1};
    for (int line = 0; line < N; line++) {
        for (int i = line; i > 0; i--)
            a[i] += a[i - 1];
        for (int i = 0; i <= line; i++)
            printf(" %3d", a[i]);
        putchar('\n');
    }
}
/* 输出：
   1
   1   1
   1   2   1
   1   3   3   1
   1   4   6   4   1
   1   5  10  10   5   1
   1   6  15  20  15   6   1
   1   7  21  35  35  21   7   1
   1   8  28  56  70  56  28   8   1
   1   9  36  84 126 126  84  36   9   1
*/
