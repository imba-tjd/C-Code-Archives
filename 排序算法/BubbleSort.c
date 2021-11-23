// 每轮排好最后一个数字
// 如果在某一次排序过程中发现没有要交换的，则说明排序已经完成了。可在if中设置flag=true，外层每轮开始时设为false，结束本轮后仍是false就结束
// 另一种算法：双向冒泡/鸡尾酒排序。设置low和high，内层有两个循环，一个从low到high，一个从high到low。对前面已经从小到大排好但尾部没排好的效率更高
#include <stdio.h>

void bubble_sort(int arr[], int n) {
    int t;
    for (int i = 0; i < n - 1; i++) // 可理解为排序轮数
        for (int j = 0; j < n - 1 - i; j++) // 缩减排序范围
            if (arr[j] > arr[j + 1]) // 从小到大排序
                t = arr[j], arr[j] = arr[j + 1], arr[j + 1] = t;
}

int main(void) {
    int arr[10] = {4, 28, 19, 8, 22, 14, 27, 25, 7, 11};
    bubble_sort(arr, 10);
    for (int i = 0; i < 10; i++)
        printf("%d ", arr[i]);
    putchar('\n');
}
