// https://zh.wikipedia.org/wiki/归并排序
#include <stdio.h>
#include <stdlib.h>

static inline int min(int x, int y) { return x < y ? x : y; }

void merge_sort(int arr[], int len) {
    int *a = arr;
    int *b = malloc(len * sizeof(int)); // 类似于arrout，储存非原地合并一次的结果

    for (int seg = 1; seg < len; seg += seg) {  // 分块，每次从头处理大小为2*seg的块
        for (int start = 0; start < len; start += seg + seg) {
            const int low = start, mid = min(start + seg, len), high = min(start + seg + seg, len);  // low,mid和mid,high表示两个已排好序的块

            int k = low;                   // arrout索引
            int start1 = low, end1 = mid;  // 遍历两个数组所用的索引
            int start2 = mid, end2 = high;
            while (start1 < end1 && start2 < end2)  // 逻辑与merge_sorted_array2相同
                b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
            while (start1 < end1)
                b[k++] = a[start1++];
            while (start2 < end2)
                b[k++] = a[start2++];
        }

        // 互换a和b，第一轮过后b已经是每两个元素排序好的数组了，而a里的数据就不需要了
        int *temp = a;
        a = b;
        b = temp;
    }

    if (a != arr) {  // 即b为arr
        for (int i = 0; i < len; i++)
            b[i] = a[i];
        b = a;
    }
    free(b);
}

int main(void) {
    int arr[10] = {76, 32, 71, 52, 65, 69, 2, 27, 30, 67};

    merge_sort(arr, 10);

    for (int i = 0; i < 10; i++)
        printf("%d ", arr[i]);
    putchar('\n');
}
