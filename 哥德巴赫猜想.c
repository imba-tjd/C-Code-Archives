//哥德巴赫猜想：
//任一大于2的偶数都可写成两个质数之和
#include <stdio.h>

int IsPrime(int n)
{
    int i;
    if (n <= 2)
        return 0;
    for (i = 2; i * i <= n; i++)
        if (n % i == 0)
            return 0;
    return 1;
}

void goldbach(int n)
{
    int i;
    for (i = 2; i <= n / 2; i++)
        if (IsPrime(i) && IsPrime(n - i))
            printf("%d=%d+%d\n", n, i, n - i);
    return;
}

int main(void)
{
    int num;
    scanf("%d", &num);
    goldbach(num);
    return 0;
}
