// 不开优化时，结果为11，因为分布上a[4]就是count；开了以后为3，因为count在循环内只有一种改变的可能，就是循环的次数
#include <stdio.h>

int main(void) {
    int b = 0;
    int count = 0;
    int a[3];
    while (b++ < 3) {
        a[b] = 10;
        count++;
    }
    printf("%d", count);
}
