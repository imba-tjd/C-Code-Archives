// 试写出一算法，完成直接插入排序算法。
// void insert_sort(int a[], int n)
// 此代码为老师的代码

#include <stdio.h>

void insert_sort(int a[], int n)
{
    for (int i = 2; i <= n; i++)
    {
        a[0] = a[i];
        int j = i - 1;
        while (a[0] < a[j])
        {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = a[0];
    }
}

int main(void)
{
    int array[11] = {0, 4, 28, 19, 8, 22, 14, 27, 25, 7, 11};
    insert_sort(array, 10);
    for (int i = 1; i <= 10; i++)
        printf("%d ", array[i]);
    putchar('\n');
    return 0;
}
