#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memcpy

typedef enum SortType {
    SmallToBig = 1,
    BigToSmall = -1
} SortType;

void QuickSort1(void *array, int count, size_t size, int (*Compare)(const void *a, const void *b), SortType type);
void QuickSort2(int *array, int length);
void QuickSort3(int array[], int left, int right);
void Swap(void *a, void *b, size_t size);
int Compare(const void *a, const void *b);

// 排序算法思想来自http://developer.51cto.com/art/201403/430986.htm，实现独立。
void QuickSort1(void *array, int count, size_t size, int (*Compare)(const void *a, const void *b), SortType type)
{
    assert(array != NULL);
    if (count <= 1)
        return;

    // count > 1, right > left
    int left = 0, right = count - 1; //  如果left = 1，当count == 2时，无法判断（或需要额外判断）这两项是否须要交换
    while (left != right)            // 不会出现 left > right 的情况
    {
        // 虽然sizeof(void*) == 8，但void*类型加1以后就只会加一，不会乘以8。所以不能直接指针+间隔，要用间隔乘以大小再加。
        if (Compare(array, array + right * size) * type < 0) // 从小到大排序时，若右边的大于枢轴
        {
            right--;  // 每次只走一步
            continue; // 不用交换，继续移动
        }
        if (Compare(array, array + left * size) * type > 0) // 从小到大排序时，若左边的小于枢轴
        {
            left++;
            continue;
        }

        Swap(array + left * size, array + right * size, size);
    }
    Swap(array, array + right * size, size); // left == right

    QuickSort1(array, left * size, size, Compare, type);
    QuickSort1(array + (left + 1) * size, count - (left + 1), size, Compare, type);
}

void Swap(void *a, void *b, size_t size)
{
    void *temp = malloc(size);
    temp = memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
}

int Compare(const void *a, const void *b)
{
    int *c = (int *)a;
    int *d = (int *)b;
    return *c >= *d ? *c > *d ? 1 : 0 : -1;
}

void QuickSort2(int *array, int length) // 书上的算法
{
    assert(array != NULL);

    int left = 0, right = length - 1;
    int temp = *array;

    if (left >= right)
        return;

    while (left < right)
    {
        while (left < right && array[right] >= temp)
            right--;
        array[left] = array[right];

        while (left < right && array[left] <= temp)
            left++;
        array[right] = array[left];
    }
    array[left] = temp;

    QuickSort2(array, left);
    QuickSort2(array + left + 1, length - (left + 1));
}

void QuickSort3(int array[], int left, int right) // wiki上的C#算法。为了和其他例子保持一致，right不使用非对称边界
{
    assert(array != NULL);

    if (left < right)
    {
        int middle = array[(left + right) / 2]; // 随便选一个作为枢轴
        int i = left, j = right;
        int t;
        while (1) // 不把枢轴单独拿出来，而是和其他数一起排列
        {
            while (array[i] < middle)
                i++;

            while (array[j] > middle)
                j--;

            if (i >= j)
                break;

            t = array[j];
            array[j] = array[i];
            array[i] = t;
        }

        QuickSort3(array, left, i - 1); // array仅为数组，不作为指针使用。
        QuickSort3(array, j + 1, right);
    }
}

#define LENGTH 10
#define A

int main(void)
{
    int array[LENGTH] = {76, 32, 71, 52, 65, 69, 2, 27, 30, 67};

#ifdef A
    QuickSort1(array, LENGTH, sizeof(int), &Compare, SmallToBig);
#endif

#ifdef B
    QuickSort2(array, LENGTH);
#endif

#ifdef C
    QuickSort3(array, 0, LENGTH - 1);
#endif

    for (int i = 0; i < LENGTH; i++)
        printf("%d\n", array[i]);

    return 0;
}
