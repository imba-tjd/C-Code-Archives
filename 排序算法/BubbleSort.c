// 试写出一算法，完成冒泡排序算法。
// void bubble_sort(int a[], int n)
// 改进：如果在某一次排序过程中发现没有要交换的，则说明排序已经完成了。
#include <stdio.h>

void bubble_sort(int a[restrict], int n)
{
    int t;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++) // 每一轮排序保证最后一个数字排好，下一次就不用排了
            if (a[j] > a[j + 1]) // 从小到大排序
                t = a[j], a[j] = a[j + 1], a[j + 1] = t;
}

int main(void)
{
    int array[10] = {4, 28, 19, 8, 22, 14, 27, 25, 7, 11};
    bubble_sort(array, 10);
    for (int i = 0; i < 10; i++)
        printf("%d ", array[i]);
    putchar('\n');
    return 0;
}
