// 试写出一算法，完成堆排序算法，升序排序（大顶堆）：void heap_sort(int a[], int n)
// 当一个结点比父结点大或者新出现时，需要从下往上处理（上浮swim）；反之如果父结点比子结点更小，需要从上往下处理（下沉sink）
// 对数组初建堆可以只用下沉且比一个个添加少一半要处理的，之后堆排序也只会用到下沉

#include <stdio.h>

void heap_adjust(int array[], int len, int index);  // index为要调整的结点

void heap_sort(int array[], int len) {  // len为堆的界限且array[len]存在（不使用array[0]）
    // 初建堆
    for (int i = len / 2; i > 0; i--)  // 因为使用数组实现堆，len/2以后的都是叶子结点，直接认为排好了；len/2恰好是最后一个有孩子的结点（二叉树的性质）
        heap_adjust(array, len, i);

    // 反复把堆顶元素放到最后
    while (len != 1) {
        int t = array[1];
        array[1] = array[len];
        array[len] = t;
        heap_adjust(array, --len, 1);  // 保持堆顶最大
    }
}

// array[index * 2]和array[index * 2 + 1]已经是大顶堆的情况下，把array[index]调整为大顶堆；即下沉操作
void heap_adjust(int array[], int len, int index) {
    if (index > len / 2)  // 叶子结点已排好，且保证之后不为叶子结点
        return;

    int t = array[index];
    int i = index * 2 + 1 > len ||                            // 右孩子不存在或
            array[index * 2] >= array[index * 2 + 1]  // 左孩子更大
            ? index * 2 : index * 2 + 1;

    if (t < array[i]) {  // else比左右都大，则直接调整完毕
        array[index] = array[i];
        array[i] = t;
        heap_adjust(array, len, i);  // 另一边不需要管
    }
}

// 非递归的算法
void heap_adjust2(int array[], int len, int index) {
    int t = array[index];
    for (int i = 2 * index; i <= len; i *= 2) {
        // 每次评估左子树
        if (i < len && array[i] < array[i + 1])
            i++;  // 右子树更大就换到右边
        if (t >= array[i])
            break;  // 比左右都大，找到位置
        else
            array[index] = array[i], index = i;  // 把较小的覆盖到父结点，继续评估原较小的位置的子结点
    }
    array[index] = t;  // 只在最后赋一次原值
}

int main(void) {
// 不使用array[0]
#define LEN 10
    int array[LEN + 1] = {0, 76, 32, 71, 52, 65, 69, 2, 27, 30, 67};

    heap_sort(array, LEN);

    for (int i = 1; i <= LEN; i++)
        printf("%d ", array[i]);
    putchar('\n');
}
