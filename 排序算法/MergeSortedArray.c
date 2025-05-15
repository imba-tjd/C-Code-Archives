// 合并两个已经从小到大排好序的数组
#include <stdio.h>
#include <stdlib.h>

// 非原地
void merge_sorted_array(int len1, const int arr1[len1],
                        int len2, const int arr2[len2],
                        int arrout[len1 + len2]) {
    int i = 0, j = 0;
    while (i < len1 || j < len2)  // 两个都满了时才出循环，用的不是&&
        // if (j == len2 || (i < len1 && arr1[i] <= arr2[j])) // 当另一个满了或自己更小时赋值过去；必须判断自己是否已满(i<len1)，否则另一个没满自己满时解引会越界
        //     *arrout++ = arr1[i++];
        // else if (i == len1 || (j < len2 && arr1[i] > arr2[j])) // 这里其实可以直接一个else解决，即下面未注释的一句
        //     *arrout++ = arr2[j++];

        *arrout++ = j == len2 || (i < len1 && arr1[i] <= arr2[j]) ? arr1[i++] : arr2[j++];  // j==len2的判断不能去掉，否则另一个满了自己没满时解引另一个会越界
}

// 更不容易出错的方式
void merge_sorted_array2(int len1, const int arr1[len1],
                         int len2, const int arr2[len2],
                         int arrout[len1 + len2]) {
    int i = 0, j = 0;

    while (i < len1 && j < len2)                                // 用的是&&，不担心越界
        *arrout++ = arr1[i] < arr2[j] ? arr1[i++] : arr2[j++];  // 每次循环，i和j只会动其中一个

    // 出循环时必定一个完成一个未完成，接下来的两个循环只会发生其中一个
    while (i < len1)
        *arrout++ = arr1[i++];  // 或用memcpy
    while (j < len2)
        *arrout++ = arr2[j++];
}

void merge_sorted_array_by_pointer(const int arr1[], const int *end1,
                                   const int arr2[], const int *end2,
                                   int arrout[]) {
    while (arr1 < end1 && arr2 < end2)  // 和方法2一样
        *arrout++ = *arr1 < *arr2 ? *arr1++ : *arr2++;

    const int *rest = arr1 == end1 ? arr2 : arr1;
    const int *restend = arr1 == end1 ? end2 : end1;
    while (rest < restend)  //收尾部分能统一
        *arrout++ = *rest++;
}

// 专用于归并排序的合并
void merge_in_mergesort(int arr[], int l, int mid, int r) {
    int tmp[r-l]; // 一般在外面开辟长度等于原数组的临时数组，而不是每次新建。如果每次新建，可将后半部分复制出来，从后往前合并每次取最大的，平均省一半空间
    int i = l, j = mid, k = 0;

    while (i < mid && j < r)
        if (arr[i] < arr[j])
            tmp[k++] = arr[i++];
        else
            tmp[k++] = arr[j++];
    while (i < mid)
        tmp[k++] = arr[i++];
    while (j < r)
        tmp[k++] = arr[j++];
    for (k = 0, i = l; i < r; ++i, ++k)
        arr[i] = tmp[k];
}

// --------------------------
// 用于第一个数不有序，后面的都有序；思路来自于插入排序
void insert_once(int arr[], int *end) {
    int t = *arr++;
    while (arr < end && *arr < t)
        (arr[-1] = arr[0]), arr++;
    arr[-1] = t;  // arr的位置为越界的end或比t大的数
}

// 原地合并两个已排序好的数组，指针参数；复杂度：while循环n/2，乘以insert_once的最坏n/2
void merge_sorted_array_in_place(int arr1[], int arr2[], int *end2) {
    int *const end1 = arr2;  // 把arr2的开始位置作为arr1的结束位置
    while (arr1 < end1) {    // arr1排好时即完成
        if (*arr1 > *arr2) {
            int t = *arr1;
            *arr1 = *arr2;
            *arr2 = t;
            insert_once(arr2, end2);  // 保持交换后的arr2有序
        }
        arr1++;  // arr2已经在insert_once里动过了
    }
}

// --------------------------
// 测试代码
void bubble_sort(int arr[], int n) {
    int t;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (arr[j] > arr[j + 1])
                t = arr[j], arr[j] = arr[j + 1], arr[j + 1] = t;
}

void print_arr(const int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    putchar('\n');
}

#define LEN 10
void Test1(void (*fun)(int, const int[], int, const int[], int[])) {
    int a[LEN] = {49, 23, 33, 26, 22, 57, 7, 14, 47, 29};
    int b[LEN] = {39, 92, 61, 50, 48, 11, 47, 45, 98, 30};

    bubble_sort(a, LEN);
    bubble_sort(b, LEN);

    int c[2 * LEN];
    fun(LEN, a, LEN, b, c);

    print_arr(c, 2 * LEN);
}

void Test2() {
    int a[LEN] = {49, 23, 33, 26, 22, 57, 7, 14, 47, 29};
    int b[LEN] = {39, 92, 61, 50, 48, 11, 47, 45, 98, 30};

    bubble_sort(a, LEN);
    bubble_sort(b, LEN);

    int c[2 * LEN];
    merge_sorted_array_by_pointer(a, a + LEN, b, b + LEN, c);

    print_arr(c, 2 * LEN);
}

void Test3() {
    // 因为此方法是原地的，就不能把两个合在一起了
    int a[LEN] = {49, 23, 33, 26, 22, 57, 7, 14, 47, 29};
    int b[LEN] = {39, 92, 61, 50, 48, 11, 47, 45, 98, 30};

    bubble_sort(a, LEN / 2);
    bubble_sort(a + LEN / 2, LEN - LEN / 2);
    bubble_sort(b, LEN / 2);
    bubble_sort(b + LEN / 2, LEN - LEN / 2);

    merge_sorted_array_in_place(a, a + LEN / 2, a + LEN);
    merge_sorted_array_in_place(b, b + LEN / 2, b + LEN);

    print_arr(a, LEN);
    print_arr(b, LEN);
}
#undef LEN

#ifndef NOTEST
int main(void) {
    Test1(merge_sorted_array);
    Test1(merge_sorted_array2);
    Test2();
    Test3();
}
#endif
