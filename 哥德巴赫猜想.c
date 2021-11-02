// 哥德巴赫猜想：任一大于2的偶数都可写成两个质数之和
#include <math.h>
#include <stdio.h>

int is_prime(int n) {
    if (n < 2)
        return 0;
    for (int i = 2, sqrtn = sqrt(n); i <= sqrtn; i++)
        if (n % i == 0)
            return 0;
    return 1;
}

int main(void) {
    int num;
    scanf("%d", &num);

    for (int i = 2; i <= num / 2; i++)
        if (is_prime(i) && is_prime(num - i))  // 关键点：不要先搜出两个素数再判断是否相加等于num
            printf("%d=%d+%d\n", num, i, num - i);
}
