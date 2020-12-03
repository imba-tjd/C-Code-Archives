#include <stdio.h>
#define N 4

int main(void) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N - i - 1; j++)
            printf("  ");
        for (int j = 0; j < 2 * i + 1; j++)
            printf("* ");
        printf("\n");
    }
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j <= i; j++)
            printf("  ");
        for (int j = 0; j < 2 * (N - 1 - i) - 1; j++)
            printf("* ");
        printf("\n");
    }
}
/* 输出：
      *
    * * *
  * * * * *
* * * * * * *
  * * * * *
    * * *
      *
把空格变成1个就是另一种风格。
*/
