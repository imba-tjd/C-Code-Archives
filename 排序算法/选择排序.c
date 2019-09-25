#include <stdio.h>

#define N 8
int main()
{
    int a[N];
    printf("输入%d个数：\n", N);
    for (int i = 0; i < N; i++)
        scanf("%d", &a[i]);

    for (int i = 0; i < N - 1; i++)
    {
        int k = i; // 最小项的下标
        for (int j = i + 1; k < N; j++)
            if (a[j] < a[k])
                k = j;

        if (k != i)
        {
            int t = a[k];
            a[k] = a[i];
            a[i] = t;
        }
    }

    printf("从小到大排序:\n");
    for (int i = 0; i < N; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}

// 列化版的选择排序：每次都交换一下。正常版的是每次记录下标，最后才交换一次。
void selection_sort(int a[restrict], int n)
{
    int t;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j]) // 从小到大排序
                t = a[i], a[i] = a[j], a[j] = t;
}
