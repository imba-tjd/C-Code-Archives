// 这几个都是原地的算法；非原地的思路特别简单，用Py非常容易实现
// 这几个都是递归的算法；迭代的把间隔从大往小处理，底下的返回pivot的位置就好
// 时间复杂度：最坏O(n^2)，平均O(nlogn)；空间复杂度：最好为log(n+1)向上取整，最坏O(n)，平均O(logn)
// 待看：https://www.zhihu.com/question/39214230
#include <stdio.h>

// ----------------------------------
// 严书算法，闭区间；不过没有空A[0]出来
int Partition(int A[], int low, int high) {
    int pivot = A[low];  // 当前段中第一个元素作为枢轴保存下来，之后low就可以被覆盖了
    while (low < high) {
        while (low < high && A[high] >= pivot)  // 从右往左找一个小于枢轴的
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
// wiki上的C#算法，闭区间
// 不把枢轴单独拿出来，而是和其他数一起排列
// 左边找一个大的，右边找一个小的，交换，但如果左边找到了，右边没找到怎么办？
// 还有不要试图交换后left++;right++，有可能交错导致状态变得超级复杂
// 总之看不懂太原理，试图把那个单独的分号改掉，失败，过不了有重复数据的测试
void QuickSort3(int array[], int left, int right) {
    if (left < right) {
        int middle = array[left + (right - left) / 2];  // 选一个中间的数作为枢轴；注意防越界
        int i = left - 1, j = right + 1;
        while (1) {
            while (array[++i] < middle)  // 与其它的不同，先走左边
                ;

            while (array[--j] > middle)
                ;

            if (i >= j)
                break;

            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }

        QuickSort3(array, left, i - 1);
        QuickSort3(array, j + 1, right);
    }
}

// ----------------------------------
// 算法导论的算法。快慢指针从左开始，[0,slow)是小于枢轴的部分，[slow,fast)是大于枢轴的部分
// fast是当前评估的位置，如果大于枢轴就继续往右走；如果小于，则于slow交换
void QuickSort4(int array[], int len) {
    if (len <= 1)
        return;

    int pivot = array[len - 1];
    int slow = 0;
    for (int fast = 0; fast < len; fast++) {
        if (array[fast] <= pivot) {  // pivot算作左边的部分
            int t = array[fast];
            array[fast] = array[slow];
            array[slow] = t;
            slow++;
        }
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
    int arr[] = {85, 75, 75, 59, 7, 30, 36, 16, 27, 80, 53, 78, 69, 85, 75};
    const int len = sizeof(arr) / sizeof(*arr);

    fun(arr, len);
    print_arr(arr, len);
}

// 模拟闭包
static void (*FUN)(int[], int, int);

void wrapper(int arr[], int len) {
    FUN(arr, 0, len - 1);
}
// 柯里化，接收一个三个参数的函数指针，返回一个两个参数的函数指针
void (*fun_wrapper(void (*fun)(int[], int, int)))(int[], int) {
    FUN = fun;
    return wrapper;
}

int main(void) {
    Test(fun_wrapper(QuickSort1));
    Test(fun_wrapper(QuickSort3));
    Test(QuickSort4);
}
