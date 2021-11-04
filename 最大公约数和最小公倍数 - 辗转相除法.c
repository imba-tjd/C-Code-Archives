// 两个整数的最大公约数等于其中较小的那个数和两数相除余数的最大公约数。最小公倍数等于两数相乘再除以最大公约数
#include <stdio.h>

int main(void) {
    int m, n, r, gcd, lcm;
    scanf("%d %d", &m, &n);

    r = m % n;  // 假如m<n，下一轮会自动换过来
    while (r != 0) {
        m = n;
        n = r;
        r = m % n;
    }

    gcd = n;
    lcm = m * n / gcd;

    printf("%d %d\n", gcd, lcm);
}
