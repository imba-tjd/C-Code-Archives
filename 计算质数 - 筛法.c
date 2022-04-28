// 计算从2到n的质数，使用筛法打表，原理和我们自己手动计算素数一样
#include <stdio.h>
#include <string.h>  // memset

int calc_primes(int primes[], int n) {
    int ndx = 0;
    int not_prime[n];                       // 临时数组
    memset(not_prime, 0, n * sizeof(int));  // VLA无法直接初始化

    for (int i = 2; i < n; i++)
        if (!not_prime[i]) {  // 如果i是素数
            primes[ndx++] = i;

            for (int j = i; j < n; j += i)  // 把i的倍数都标记为非素数
                not_prime[j] = 1;           // 另一种方式是=i，则表示j的最大质因数
        }

    return ndx;  // 返回计算出了多少个素数
}

int main(void) {
    int arr[1000 / 2];  // 储存2-1000的所有的素数，因此长度可以小于1000
    int n = calc_primes(arr, 1000);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    putchar('\n');
}
