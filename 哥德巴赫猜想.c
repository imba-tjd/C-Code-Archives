//哥德巴赫猜想：
//任一大于2的偶数都可写成两个质数之和
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

bool IsPrime(int n)
{
    if (n <= 2)
        return 0;
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return false;
    return true;
}

void goldbach(int n)
{
    for (int i = 2; i <= n / 2; i++)
        if (IsPrime(i) && IsPrime(n - i))
            printf("%d=%d+%d\n", n, i, n - i);
}

int main(void)
{
    int num;
    scanf("%d", &num);
    goldbach(num);
    return 0;
}
