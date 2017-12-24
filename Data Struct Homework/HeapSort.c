// 试写出一算法，完成堆排序算法，升序排序。 void heap_sort(int a[], int n)
#include <assert.h>
#include <stdio.h>

void HeapSort(int array[], int num);
void HeapAdjust(int array[], int num, int index);

void HeapSort(int array[], int num)
{
    assert(array != NULL);

    // 初建堆
    for (int i = num / 2; i > 0; i--) // 因为使用数组实现堆，num / 2 以后的都是叶子节点，直接认为排好了
        HeapAdjust(array, num, i);

    // 反复把堆顶元素放到最后
    while (num != 1)
    {
        int t = array[1];
        array[1] = array[num];
        array[num] = t;
        HeapAdjust(array, --num, 1); // 保持堆顶最大
    }
}

// array[index * 2]和array[index * 2 + 1]已经是大根堆的情况下，把array[index]调整为大根堆
void HeapAdjust(int array[], int num, int index)
{
    if (index > num / 2)
        return;

    int t = array[index];
    int i = array[index * 2] >= array[index * 2 + 1] ||
                    index * 2 + 1 > num // 左孩子在范围内但右孩子不在（或已经排好）
                ? index * 2
                : index * 2 + 1;

    if (t < array[i]) // 如果比左右都大，则直接调整完毕
    {
        array[index] = array[i];
        array[i] = t;
        HeapAdjust(array, num, i); // 另一边不需要管
    }
}

#define LENGTH 10
int main(void)
{
    // 不使用array[0]
    int array[] = {0, 76, 32, 71, 52, 65, 69, 2, 27, 30, 67};
    // int array[] = {0, 32, 52, 65, 69, 2, 27, 30};

    HeapSort(array, LENGTH);

    for (int i = 1; i <= LENGTH; i++)
        printf("%d\n", array[i]);
}
