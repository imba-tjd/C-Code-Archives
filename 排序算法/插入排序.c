#include <stdio.h>

void InsertSort(size_t len, int arr[static restrict len])
{
    for (int i = 1; i < len; i++)   // a[0]认为已经排序好了，之后用DP/数学归纳的思想
        for (int j = 0; j < i; j++) // 每次取arr[i]插入前面的数组
            if (arr[j] > arr[i])
            {
                int t = arr[i];
                for (int k = i; k > j; k--) // 往后移，可用memmove替代
                    arr[k] = arr[k - 1];
                arr[j] = t;
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
