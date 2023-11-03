// 本文件三种方法在存在重复值时都不会选择最左边那个
#include <assert.h>
#include <stdio.h>

// 返回索引，闭区间。教材上是这种模式，计算比较次数时注意剩一个数时也要比一次
int binary_search(const int arr[], int from, int to, int target) {
    if (to - from < 0)
        return -1;
    else if (to - from == 0)  // 剩一个数
        return arr[from] == target ? from : -1;

    int mid = from + (to - from) / 2;

    if (arr[mid] == target)
        return mid;
    else if (arr[mid] > target)
        return binary_search(arr, from, mid - 1, target);  // 可能导致to<0
    else
        return binary_search(arr, mid + 1, to, target);
}

// 返回指针。参数的数组加了const，返回的指针也必须加
const int *binary_search2(const int arr[], int len, int target) {
    if (len == 0)
        return NULL;

    int mid = len / 2;
    if (arr[mid] == target)
        return arr + mid;
    else if (arr[mid] > target)
        return binary_search2(arr, mid, target);
    else
        return binary_search2(arr + mid + 1, len - mid - 1, target);
}

// 迭代。甚至比递归更简单
int binary_search3(const int arr[], int len, int target) {
    int from = 0, to = len;
    while (to - from > 0) {
        int mid = (from + to) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] > target)
            to = mid;
        else
            from = mid + 1;
    }
    return -1;
}

// 测试用代码

int binary_search_wrapper(const int arr[], int len, int target) {
    return binary_search(arr, 0, len, target);
}

int binary_search2_wrapper(const int arr[], int len, int target) {
    const int *result = binary_search2(arr, len, target);
    return result == NULL ? -1 : result - arr;
}

void Test(int (*fun)(const int[], int, int)) {
    int arr1[] = {7, 8, 14, 35, 39, 44, 63, 77, 96, 98};
    assert(0 == fun(arr1, 10, 7));
    assert(4 == fun(arr1, 10, 39));
    assert(7 == fun(arr1, 10, 77));
    assert(9 == fun(arr1, 10, 98));
    assert(-1 == fun(arr1, 10, 50));

    int arr2[] = {3, 7};
    assert(-1 == fun(arr2, 2, 5));
    assert(1 == fun(arr2, 2, 7));
    assert(-1 == fun(arr2, 2, 9));
}

int main(void) {
    Test(binary_search3);
    Test(binary_search_wrapper);
    Test(binary_search2_wrapper);
}
