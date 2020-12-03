#include <stdio.h>

// 直接插入排序，从后往前边比较边移动
void insert_sort(int arr[], int len) {
    for (int i = 1; i < len; i++) {
        int t = arr[i];
        int j = i;
        while (j > 0 && t < arr[j - 1]) // 如果比t大，就往后移
            arr[j] = arr[j - 1], j--;
        arr[j] = t;
    }
}

// 这种方法本来是先从头开始找位置，然后又从后往前每个往后移，相对低效；但找位置可用二分法，叫做折半插入排序，比较次数稍微少一点，移动次数仍然和直接一样
void insert_sort2(int arr[], int len) {
    for (int i = 1; i < len; i++)   // a[0]认为已经排序好了
        for (int j = 0; j < i; j++) // 寻找要插入前面数组的位置；可用BinarySearch替代
            if (arr[j] > arr[i]) {  // arr[j]更小时就什么也不做
                int t = arr[i];
                for (int k = i; k > j; k--) // 往后移，可用memmove替代
                    arr[k] = arr[k - 1];
                arr[j] = t;
            }
}

int main(void) {
    int arr[10] = {76, 32, 71, 52, 65, 69, 2, 27, 30, 67};
    insert_sort(arr, 10);
    for (int i = 0; i < 10; i++)
        printf("%d ", arr[i]);
    putchar('\n');
}
