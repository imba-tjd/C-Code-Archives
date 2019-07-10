#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 非原地合并两个已经排序好的数组，从小到大
void MergeSortedArray(
    size_t len1, const int arr1[static restrict len1],
    size_t len2, const int arr2[static restrict len2],
    int arrout[static restrict len1 + len2])
{
    int i = 0, j = 0;                                      // 用索引处理
    while (i < len1 || j < len2)                           // 两个都满了时才出循环，用的不是&&
        if (j == len2 || (i < len1 && arr1[i] <= arr2[j])) // 当另一个满了或自己更小时赋值过去
            *arrout++ = arr1[i++];
        else if (i == len1 || (j < len2 && arr1[i] > arr2[j])) // 必须判断自己是否已满(j<len2)，否则另一个没满自己满时解引会越界
            *arrout++ = arr2[j++];
}

// --------------------------
// 非原地合并两个已经排序好的数组，用指针
void MergeSortedArrayByPoint(
    size_t len1, const int arr1[static restrict len1],
    size_t len2, const int arr2[static restrict len2],
    int arrout[static restrict len1 + len2])
{
    const int *end1 = arr1 + len1;
    const int *end2 = arr2 + len2;

    while (arr1 < end1 && arr2 < end2)                 // 用的是&&，不担心越界
        *arrout++ = *arr1 < *arr2 ? *arr1++ : *arr2++; // 每次循环，arr1和arr2只会动其中一个

    // 出循环时必定一个完成一个未完成，接下来的两个循环只会发生其中一个
    while (arr1 < end1)
        *arrout++ = *arr1++; // 或用memcpy
    while (arr2 < end2)
        *arrout++ = *arr2++;

    // 如果是以NULL为结尾的序列，则不需要restend，统一一下也还行；但本函数需要，和上面那种比不占优势
    // const int *rest = arr1 == end1 ? arr2 : arr1;
    // const int *restend = arr1 == end1 ? end2 : end1;
    // while (rest < restend)
    //     *arrout++ = *rest++;
}

// --------------------------
// 原地合并两个已排序好的数组
void Swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// 用于第一个数不有序，后面的都有序；思路来自于插入排序
void insertOnce(int arr[restrict], int *end)
{
    int t = *arr;
    while (arr < end && *arr < t)
        (arr[-1] = arr[0]), arr++;
    arr[-1] = t;
}

void MergeSortedArrayInPlace(
    size_t len1, int arr1[static restrict len1],
    size_t len2, int arr2[static restrict len2])
{
    int *end1 = arr1 + len1;
    int *end2 = arr2 + len2;
    while (arr1 < end1 && arr2 < end2) // 因为是原地，只要有一个结束，剩下的自然就排好了
        if (*arr1 > *arr2)             // 所以也不用越界检查
        {
            Swap(arr1++, arr2);
            insertOnce(arr2, end2); // 如果发生了交换，arr2可能不再有序
        }
        else
            arr2++;
}

// --------------------------
// 无类型非原地合并两个已排序好的数组，用主动分配内存
typedef enum SortType
{
    SmallToBig = 1,
    BigToSmall = -1
} SortType;

void *MergeSortedArrayNoType(void *arr1, int len1, void *arr2, int len2, size_t elemsiz, int (*compare)(const void *a, const void *b), SortType type)
{
    assert(arr1 != NULL && arr2 != NULL && compare != NULL);

    void *const arrout = malloc((len1 + len2) * elemsiz); // 因为最后要返回，所以不能改
    void *arroutp = arrout;
    void *end1 = arr1 + len1 * elemsiz, *end2 = arr2 + len2 * elemsiz;

    // 用的是第一种的||，但用的是指针
    while (arr1 != end1 || arr2 != end2)
    {
        if (arr2 == end2 || (arr1 < end1 && compare(arr1, arr2) <= 0))
        {
            memcpy(arroutp, arr1, elemsiz);
            arroutp += elemsiz;
            arr1 += elemsiz;
        }
        else if (arr1 == end1 || (arr2 < end2 && compare(arr1, arr2) > 0))
        {
            memcpy(arroutp, arr2, elemsiz);
            arroutp += elemsiz;
            arr2 += elemsiz;
        }
    }

    return arrout;
}

int Compare(const void *a, const void *b)
{
    int *c = (int *)a;
    int *d = (int *)b;
    return *c >= *d ? *c > *d ? 1 : 0 : -1;
}

// --------------------------
// 测试代码
void bubbleSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j]) // 从小到大排列
            {
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
}

void PrintArr(size_t len, int arr[static restrict len])
{
    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);
    putchar('\n');
}

#define LEN 10
void Test1()
{
    int a[LEN] = {49, 23, 33, 26, 22, 57, 7, 14, 47, 29};
    int b[LEN] = {39, 92, 61, 50, 48, 11, 47, 45, 98, 30};

    bubbleSort(a, LEN);
    bubbleSort(b, LEN);

    int c[2 * LEN];
    MergeSortedArray(LEN, a, LEN, b, c);

    PrintArr(2 * LEN, c);
}

void Test2()
{
    int a[LEN] = {49, 23, 33, 26, 22, 57, 7, 14, 47, 29};
    int b[LEN] = {39, 92, 61, 50, 48, 11, 47, 45, 98, 30};

    bubbleSort(a, LEN);
    bubbleSort(b, LEN);

    int c[2 * LEN];
    MergeSortedArrayByPoint(LEN, a, LEN, b, c);

    PrintArr(2 * LEN, c);
}

void Test3()
{
    int a[LEN] = {49, 23, 33, 26, 22, 57, 7, 14, 47, 29};
    int b[LEN] = {39, 92, 61, 50, 48, 11, 47, 45, 98, 30};

    bubbleSort(a, LEN / 2);
    bubbleSort(a + LEN / 2, LEN - LEN / 2);
    bubbleSort(b, LEN / 2);
    bubbleSort(b + LEN / 2, LEN - LEN / 2);

    MergeSortedArrayInPlace(LEN / 2, a, LEN - LEN / 2, a + LEN / 2);
    MergeSortedArrayInPlace(LEN / 2, b, LEN - LEN / 2, b + LEN / 2);

    PrintArr(LEN, a);
    PrintArr(LEN, b);
}

void Test4()
{
    int a[LEN] = {49, 23, 33, 26, 22, 57, 7, 14, 47, 29};
    int b[LEN] = {39, 92, 61, 50, 48, 11, 47, 45, 98, 30};

    bubbleSort(a, LEN);
    bubbleSort(b, LEN);

    int *c = MergeSortedArrayNoType(a, LEN, b, LEN, sizeof(int), Compare, SmallToBig);

    PrintArr(2 * LEN, c);
}

#ifndef NOTEST
int main(void)
{
    Test1();
    Test2();
    Test3();
    Test4();
}
#endif
