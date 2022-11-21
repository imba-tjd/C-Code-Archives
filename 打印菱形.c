#include <stdio.h>
#define N 4 // 4行，假定编号从1开始

int main(void) {
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < N - i; j++) // 第1行3份空格，第4行0份空格
            printf("  ");
        for (int j = 0; j < 2 * i - 1; j++) // 第1行1个星，第2行3个星
            printf("* ");
        putchar('\n');
    }

    for (int i = N - 1; i > 0; i--) { // 下半部分，i从大到小N-1行，里面的逻辑和上半部分完全一样
        for (int j = 0; j < N - i; j++)
            printf("  ");
        for (int j = 0; j < 2 * i - 1; j++)
            printf("* ");
        putchar('\n');
    }

    // 另一种生成下半部分的逻辑，若i仍然从小到大
    // for (int i = 1; i <= N - 1; i++) {
    //     for (int j = 0; j < i; j++)
    //         printf("  ");
    //     for (int j = 0; j < 2 * (N - i) - 1; j++) // 第1行5个星
    //         printf("* ");
    //     putchar('\n');
    // }
}

/* 输出：
      *
    * * *
  * * * * *
* * * * * * *
  * * * * *
    * * *
      *
均减少一个空格后的输出：
   *
  ***
 *****
*******
 *****
  ***
   *
*/
