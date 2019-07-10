// 这几个算法都是原地的算法；非原地的有许多不同，但本身的思路特别简单
// 这几个算法都是递归的算法；改成迭代的需要把间隔从大往小处理，底下的返回pivot的位置就好
// 因为递归调用时会传指针进去，所以不能加restrict？
// 待看：https://www.zhihu.com/question/39214230
#include <assert.h>
#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h> // memcpy

// ----------------------------------
// 严书上的算法；有一点点不同，没有空a[0]出来
void QuickSort2(int array[], size_t length)
{
    assert(array != NULL);

    int pivot = *array; // 选a[0]作为枢轴记录下来，则这个位置就可以被覆盖了；如果要选中间的，保存选好的后把a[0]赋给那个位置

    int left = 0, right = length - 1; // 闭区间
    if (left >= right)                // length为0或1
        return;

    while (left < right)
    {
        while (left < right && array[right] >= pivot) // 从右往左找一个小于枢轴的
            right--;
        array[left] = array[right]; // 赋值后right位置可以被覆盖

        while (left < right && array[left] <= pivot) // 从左往右找一个大于枢轴的
            left++;
        array[right] = array[left];
    }
    assert(left == right); // 必定left == right，因为子循环里只会走一步且完成了赋值
    array[left] = pivot;   // 枢轴的最终位置

    QuickSort2(array, left);
    QuickSort2(array + left + 1, length - (left + 1));
}

// ----------------------------------
// wiki上的C#算法，用的是闭区间
// 不把枢轴单独拿出来，而是和其他数一起排列
// 左边找一个大的，右边找一个小的，交换，但如果左边找到了，右边没找到怎么办？
// 还有不要试图交换后left++;right++，有可能交错，导致状态变得各种复杂
// 总之看不懂太原理，试图把那个单独的分号改掉，失败，过不了有重复数据的测试
void QuickSort3(int array[const], int left, int right)
{
    assert(array != NULL);

    if (left < right)
    {
        int middle = array[left + (right - left) / 2]; // 选一个中间的数作为枢轴；注意防越界
        int i = left - 1, j = right + 1;
        while (1)
        {
            while (array[++i] < middle) // 与其它的不同，先走左边
                ;

            while (array[--j] > middle)
                ;

            if (i >= j)
                break;

            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }

        QuickSort3(array, left, i - 1); // array仅为数组，不作为指针使用。
        QuickSort3(array, j + 1, right);
    }
}

// ----------------------------------
// 算法导论的算法。快慢指针从左开始，[0,slow)是小于枢轴的部分，[slow,fast)是大于枢轴的部分
// fast是当前评估的位置，如果大于枢轴就继续往右走；如果小于，则于slow交换
void QuickSort4(int array[const], size_t len)
{
    if (len <= 1)
        return;

    int pivot = array[len - 1]; // 选最后一个数为枢轴
    int slow = 0;
    for (size_t fast = 0; fast < len; fast++)
    {
        if (array[fast] <= pivot) // pivot算作左边的部分
        {
            int t = array[fast];
            array[fast] = array[slow];
            array[slow] = t;
            slow++;
        }
    }
    QuickSort4(array, slow - 1);          // 最后交换pivot后slow还++了，所以slow-1才是pivot的位置；且这个参数是len，即开区间，所以直接传pivot的位置就好
    QuickSort4(array + slow, len - slow); //slow处即pivot的位置，但
}

// ----------------------------------
// 测试
void PrintArr(const int arr[restrict], size_t len)
{
    for (size_t i = 0; i < len; i++)
        printf("%d ", arr[i]);
    putchar('\n');
}

int *GetArr(int *len)
{
    // int array[] = {76, 32, 71, 52, 65, 69, 2, 27, 30, 67};
    int array[] = {85, 75, 75, 59, 7, 30, 36, 16, 27, 80, 53, 78, 69, 85, 75};
    *len = sizeof(array) / sizeof(*array);

    int siz = *len * sizeof(int);
    int *arr = malloc(siz);
    memcpy(arr, array, siz);
    return arr;
}

void Test2()
{
    int len;
    int *arr = GetArr(&len);

    QuickSort2(arr, len);
    PrintArr(arr, len);

    free(arr);
}

void Test3()
{
    int len;
    int *arr = GetArr(&len);

    QuickSort3(arr, 0, len - 1);
    PrintArr(arr, len);

    free(arr);
}

void Test4()
{
    int len;
    int *arr = GetArr(&len);

    QuickSort4(arr, len);
    PrintArr(arr, len);

    free(arr);
}

int main(void)
{
    Test2();
    Test3();
    Test4();

    return 0;
}
