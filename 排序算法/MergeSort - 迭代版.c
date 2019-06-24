// https://zh.wikipedia.org/wiki/归并排序
// 迭代法实现的归并排序
#include <stdio.h>
#include <stdlib.h>

static inline int min(int x, int y) { return x < y ? x : y; }

void merge_sort(int arr[], int len) // len为数组长度
{
    int *a = arr;
    int *b = (int *)malloc(len * sizeof(int));
    for (int seg = 1; seg < len; seg += seg) // 分块，每次从头处理大小为2*seg的块
    {
        for (int start = 0; start < len; start += seg + seg)
        {
            int low = start, mid = min(start + seg, len), high = min(start + seg + seg, len);
            int k = low;
            int start1 = low, end1 = mid; // 两个分别已排序好的块
            int start2 = mid, end2 = high;
            while (start1 < end1 && start2 < end2)
                b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
            while (start1 < end1)
                b[k++] = a[start1++];
            while (start2 < end2)
                b[k++] = a[start2++];
        }
        int *temp = a; // 第一轮过后b已经是每两个元素排序好的数组了，而a里的数据就不需要了，所以互换
        a = b;
        b = temp;
    }

    if (a != arr) // 即b为arr
    {
        for (int i = 0; i < len; i++)
            b[i] = a[i];
        b = a;
    }
    free(b);
}

int main(void)
{
    int array[] = {76, 32, 71, 52, 65, 69, 2, 27, 30, 67};

    merge_sort(array, 10);

    for (int i = 0; i < 10; i++)
        printf("%d\n", array[i]);

    return 0;
}
