// 计算前n个质数（不是算小于n的）
#include <stdio.h>

void calc_primes(int primes[], int n) {
    int num = 2, ndx = 0;  // 分别是 当前评估的数字，primes[]待赋值的下标
    while (ndx < n) {
        int i = -1;
        while (++i < ndx)  // 遍历已计算出的
            if (num % primes[i] == 0)
                break;
        if (i == ndx)  // 没有因子，是质数，加入表中
            primes[ndx++] = num;
        num++;
    }
}

int main(void) {
    int arr[100];
    calc_primes(arr, 100);

    for (int i = 0; i < 100; i++)
        printf("%d ", arr[i]);
}
