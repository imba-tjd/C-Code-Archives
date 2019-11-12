// 试写出一算法，完成堆排序算法，升序排序。 void heap_sort(int a[], int n)
// 当一个节点比父节点大或者新出现时，需要从下往上处理（上浮swim）；反之如果变得比子节点更小，需要从上往下处理（下沉sink）；
// 其中初建堆用下沉可以最多比上浮少一半的处理，也就是本代码的实现；但是对建好的堆添加元素就只能用上浮了
#include <assert.h>
#include <stdio.h>

void HeapSort(int array[], int num);
void HeapAdjust(int array[], int num, int index);

void HeapSort(int array[], int num)
{
    assert(array != NULL);

    // 初建堆
    for (int i = num / 2; i > 0; i--) // 因为使用数组实现堆，num / 2 以后的都是叶子节点，直接认为排好了；num/2恰好是最后一个有孩子的节点（二叉树的性质）
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

// array[index * 2]和array[index * 2 + 1]已经是大根堆的情况下，把array[index]调整为大根堆；即下沉操作
void HeapAdjust(int array[], int num, int index)
{
    if (index > num / 2)
        return;

    int t = array[index];
    int i = array[index * 2] >= array[index * 2 + 1] || // 左右中更大的那个
                    index * 2 + 1 > num                 // 左孩子在范围内但右孩子不在（或已经堆排序排好）
                ? index * 2
                : index * 2 + 1;

    if (t < array[i]) // else比左右都大，则直接调整完毕
    {
        array[index] = array[i];
        array[i] = t;
        HeapAdjust(array, num, i); // 另一边不需要管
    }
}

// 非递归的方法
void HeapAdjust2(int array[], int len, int k)
{
    int t = array[k]; // 把待调整的元素保存到别的地方
    for (int i = 2 * k; i <= len; i *= 2)
    { // 每次评估左子树
        if (i < len && array[i] < array[i + 1])
            i++; // 右子树更大就换到右边
        if (t >= array[i])
            break; // 比左右都大，找到位置
        else
        {
            array[k] = array[i]; // 把较小的与父节点交换，并把交换后的作为新的父节点
            k = i;
        }
    }
    array[k] = t;
}

#define LENGTH 10
int main(void)
{
    // 不使用array[0]
    int array[] = {0, 76, 32, 71, 52, 65, 69, 2, 27, 30, 67};

    HeapSort(array, LENGTH);

    for (int i = 1; i <= LENGTH; i++)
        printf("%d ", array[i]);
    putchar('\n');
}
