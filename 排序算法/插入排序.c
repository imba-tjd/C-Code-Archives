#include <stdio.h>

// 其实这种方法比较低效，它先从头开始找位置，然后又从后往前每个往后移
void InsertSort(size_t len, int arr[static restrict len])
{
    for (int i = 1; i < len; i++)   // a[0]认为已经排序好了，之后用DP/数学归纳的思想
        for (int j = 0; j < i; j++) // 每次取arr[i]插入前面的数组
            if (arr[j] > arr[i])    // arr[j]更小时就什么也不做
            {
                int t = arr[i];
                for (int k = i; k > j; k--) // 往后移，可用memmove替代
                    arr[k] = arr[k - 1];
                arr[j] = t;
            }
}

// 高效的方法
void insert_sort(int a[restrict], int n)
{
    for (int i = 1; i <= n; i++)
    {
        int t = a[i];
        int j = i;         // 直接从后往前找
        while (t < a[--j]) // 如果比t大，就往后移
            a[j + 1] = a[j];
        a[j + 1] = t;
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
