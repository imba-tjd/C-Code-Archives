#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *MergeSortedIntArray(int array1[], int array2[], int count1, int count2) // 合并两个已经排序好的数组
{
    int *array = calloc(count1 + count2, sizeof(int));
    int *p = array;
    int i = 0, j = 0;

    while (i < count1 || j < count2) // 两个都满了
    {
        // 从小到大排列
        if (j == count2 || (i < count1 && array1[i] <= array2[j])) // 必须判断自己是否已满，否则另一个没满自己满时会越界
            *p++ = array1[i++];
        else if (i == count1 || (j < count2 && array1[i] > array2[j])) // 当另一个满了或自己更小时赋值过去
            *p++ = array2[j++];
    }

    return array;
}

typedef enum SortType {
    SmallToBig = 1,
    BigToSmall = -1
} SortType;

void *MergeSortedArray(void *array1, int count1, void *array2, int count2, size_t size, int (*Compare)(const void *a, const void *b), SortType type)
{
    assert(array1 != NULL && array2 != NULL && Compare != NULL);

    void *array = calloc(count1 + count2, size);
    void *p = array, *p1 = array1, *p2 = array2, *flag1 = array1 + count1 * size, *flag2 = array2 + count2 * size;

    while (p1 != flag1 || p2 != flag2)
    {
        // 从小到大排列
        if (p2 == flag2 || (p1 < flag1 && Compare(p1, p2) <= 0))
        {
            memcpy(p, p1, size);
            p += size;
            p1 += size;
        }
        else if (p1 == flag1 || (p2 < flag2 && Compare(p1, p2) > 0))
        {
            memcpy(p, p2, size);
            p += size;
            p2 += size;
        }
    }

    return array;
}

int Compare(const void *a, const void *b)
{
    int *c = (int *)a;
    int *d = (int *)b;
    return *c >= *d ? *c > *d ? 1 : 0 : -1;
}

void bubble_sort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j])
                a[i] ^= a[j] ^= a[i] ^= a[j];
}

int main(void)
{
    int a[] = {49, 23, 33, 26, 22, 57, 7, 14, 47, 29};
    int b[] = {39, 92, 61, 50, 48, 11, 47, 45, 98, 30};

    bubble_sort(a, 10);
    bubble_sort(b, 10);

    // int *c = MergeSortedIntArray(a, b, 10, 10);
    int *c = MergeSortedArray(a, 10, b, 10, 4, Compare, SmallToBig);

    for (int i = 0; i < 20; i++)
        printf("%d ", c[i]);
    putchar('\n');
    return 0;
}
