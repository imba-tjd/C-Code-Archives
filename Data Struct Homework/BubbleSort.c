// 试写出一算法，完成冒泡排序算法。
// void bubble_sort(int a[], int n)
// 改进：如果在某一次排序过程中发现没有要交换的，则说明排序已经完成了。
#include <stdio.h>

void bubble_sort(int a[], int n)
{
    for (int i = 0; i < n - 1;i++)
        for (int j = i + 1; j < n;j++)
            if (a[i]>a[j]) // 从小到大排序
                a[i] ^= a[j] ^= a[i] ^= a[j];
}

int main(void)
{
    int array[10] = {4, 28, 19, 8, 22, 14, 27, 25, 7, 11};
    bubble_sort(array, 10);
    for (int i = 0; i < 10;i++)
        printf("%d ", array[i]);
    putchar('\n');
    return 0;
}
