#include <stdio.h>

// 这种方法本来是先从头开始找位置，然后又从后往前每个往后移，相对低效；但找位置可用二分法，稍微好一点，移动次数仍然和下一个函数一样
void BinaryInsertSort(size_t len, int arr[static restrict len])
{
    for (size_t i = 1; i < len; i++)   // a[0]认为已经排序好了，之后用DP/数学归纳的思想
        for (size_t j = 0; j < i; j++) // 寻找要插入前面数组的位置；可用BinarySearch替代
            if (arr[j] > arr[i])    // arr[j]更小时就什么也不做
            {
                int t = arr[i];
                for (size_t k = i; k > j; k--) // 往后移，可用memmove替代
                    arr[k] = arr[k - 1];
                arr[j] = t;
            }
}

// 普通的插入排序，从后往前边比较边移动
void InsertSort(size_t len, int arr[static restrict len])
{
    for (size_t i = 1; i <= len; i++)
    {
        int t = arr[i];
        int j = i;           // 直接从后往前找
        while (t < arr[--j]) // 如果比t大，就往后移
            arr[j + 1] = arr[j];
        arr[j + 1] = t;
    }
}

int main(void)
{
#define LEN 10
    int arr[10] = {76, 32, 71, 52, 65, 69, 2, 27, 30, 67};

    InsertSort(10, arr);

    for (int i = 0; i < LEN; i++)
        printf("%d ", arr[i]);
    putchar('\n');
}
