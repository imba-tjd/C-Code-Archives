// 计算一定范围内有多少素数
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void)
{
    bool IsPrime(int n);
    int n = 0, count = 0;
    printf("This program is used to count how many prime numbers are there and print them, from 2 to your input number.\n\
Just input a number:");
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
        if (IsPrime(i))
        {
            printf("%d\n", i);
            count++;
        }
    printf("total:%d\n", count);
    return 0;
}

bool IsPrime(int n)
{
    if (n < 2)
        return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}
