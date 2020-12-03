#include <stdio.h>

int main(void) {
    int m, n, r, p, gcd, lcm;
    scanf("%d %d", &m, &n);
    p = m * n;
    r = m % n;
    while (r != 0) {
        m = n;
        n = r;
        r = m % n;
    }
    gcd = n;
    lcm = p / gcd;
    printf("%d %d\n", gcd, lcm);
}
