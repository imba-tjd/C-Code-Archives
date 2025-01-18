// 这几个都是原地的、递归的算法。反复把间隔从大往小处理，底下的返回pivot的位置就好
// 时间复杂度：最坏O(n^2)，平均O(nlogn)；空间复杂度：最好为log(n+1)向上取整，最坏O(n)，平均O(logn)
// 枢轴若取第一项或最后一项，当数组已有序时，划分会极不平衡
// 可考虑三数取中：第一项、最后一项、中位数（low + (high - low) / 2 防止越界）
// 待看：https://www.zhihu.com/question/39214230

#include <stdio.h>

static inline void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// ----------------------------------
// 严书算法（不过没有空A[0]出来），闭区间。本质是Lomuto分区的变形，用后半部分保存大于枢轴的
int Partition(int A[], int low, int high) {
    int pivot = A[low];  // 当前段中第一个元素作为枢轴保存下来，之后low就可以被覆盖了。若选最后一个，则先从左往右找
    while (low < high) {
        while (low < high && A[high] >= pivot)  // 从右往左找一个小于枢轴的。如果没找到(low==high)，下一行复制无问题
            high--;
        A[low] = A[high];  // 之后high就可以被覆盖了
        while (low < high && A[low] <= pivot)
            low++;
        A[high] = A[low];
    }
    A[low] = pivot;  // 枢轴的最终位置
    return low;
}

void QuickSort1(int A[], int low, int high) {
    // 也可用栈或队列保存low和high，在此处循环栈不为空，下面两句直接入栈即可
    if (low < high) {
        int pivotpos = Partition(A, low, high);
        QuickSort1(A, low, pivotpos - 1);
        QuickSort1(A, pivotpos + 1, high);
    }
}

// ----------------------------------
// Hoare’s partition scheme，闭区间
// 没有把枢轴单独拿出来，而是和其他数一起排列。一轮排序后不保证枢轴排到了最终位置，事实上可以处于任何位置。难以理解原理
// break时，只能保证[low,i)之间的值<=枢轴，(j,high]之间>=枢轴，j可能比i小但最多是j+1==i
// 优点：如果选中位数作为枢轴，对于已排序数组，不会有不必要的交换；对于全相等数组，虽然会不必要地交换几次，但划分仍会均衡，而Lomuto划分就不行
void QuickSort3(int array[], int low, int high) {
    if (low >= high)
        return;

    int pivot = array[low]; // 用high还需把j和j+1改成i-1和i，否则会无限递归
    int i = low - 1, j = high + 1;
    while (1) {
        while (array[++i] < pivot) // 另一种写法：把++改到上下
            ;

        do { // 另一种写法，大括号可省
            --j;
        } while (array[j] > pivot);

        if (i >= j)
            break; // 若partition独立，则return j；此处不独立，可写成if <时swap，再把while条件也改成<

        swap(&array[i], &array[j]);
    }

    QuickSort3(array, low, j);
    QuickSort3(array, j + 1, high); // 没有空出元素，j不是已排好的
}

// ----------------------------------
// 算法导论的算法，Lomuto's partition scheme
// 快慢指针从左开始，[0,slow)是小于等于枢轴的部分，[slow,fast)是大于枢轴的部分
// fast是当前评估的位置，如果大于枢轴就继续往右走；如果小于，则于slow交换
// 除了通用缺点以外的缺点：当数组已基本有序时，若枢轴选中位数，则会导致大量交换（如假设0是大于枢轴的）
void QuickSort4(int array[], int len) {
    if (len <= 1)
        return;

    int pivot = array[len - 1];
    int slow = 0;
    for (int fast = 0; fast < len; fast++)
        if (array[fast] <= pivot) {
            swap(&array[fast], &array[slow]);
            slow++;
        }

    QuickSort4(array, slow - 1);           // 最后交换pivot后slow还++了，所以slow-1才是pivot的位置；此参数是开区间，所以直接传pivot的位置就好
    QuickSort4(array + slow, len - slow);  // slow-1处排好了，slow处没排好
}

// ----------------------------------
// 测试
void print_arr(const int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    putchar('\n');
}

void Test(void (*fun)(int arr[], int len)) {
    int arr[] = {5, 4, 1, 2, 3, 7, 6, 9, 8, 5};
    //int arr[] = {85, 75, 75, 59, 7, 30, 36, 16, 27, 80, 53, 78, 69, 85, 75};
    const int len = sizeof(arr) / sizeof(*arr);

    fun(arr, len);
    print_arr(arr, len);
}

// 模拟py的装饰器，也可理解为适配器模式
static void (*FUN)(int[], int, int);
typedef void (*qs1funptr)(int[], int, int);
typedef void (*qs4funptr)(int[], int);

void wrapper(int arr[], int len) {
    FUN(arr, 0, len - 1);
}

// 接收一个三个参数的函数指针，返回一个两个参数的函数指针
// void (*fun_wrapper(void (*fun)(int[], int, int)))(int[], int)
qs4funptr fun_wrapper(qs1funptr fun){
    FUN = fun;
    return wrapper;
}

int main(void) {
    Test(fun_wrapper(QuickSort1));
    Test(fun_wrapper(QuickSort3));
    Test(QuickSort4);
}
