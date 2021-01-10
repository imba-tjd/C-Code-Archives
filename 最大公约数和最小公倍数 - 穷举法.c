#include <stdio.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int gcd(int x, int y) {
    int b = max(x, y);
    int a = min(x, y);
    for (int i = a; i >= 1; i--)
        if (a % i == 0 && b % i == 0)
            return i;
    return 1;  // 实际上不会执行到，循环中到1时必返回
}

int lcm(int x, int y) {
    int b = max(x, y);
    int a = min(x, y);
    for (int i = b; i <= a * b; i++)
        if (i % b == 0 && i % a == 0)
            return i;
    return a * b;
}

int main(void) {
    int x, y;
    scanf("%d %d", &x, &y);
    printf("%d %d", gcd(x, y), lcm(x, y));
}
