#include <stdio.h>
#include <stdlib.h>  // srand, rand
#include <string.h>  // memcpy
#include <time.h>    // time

static inline void Swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// 均匀地在 [0,upper) 产生一个随机整数，需要先srand；简化版就rand()%upper
int RandUpper(int upper) {
    int num;
    do {
        num = rand();
    } while (num == RAND_MAX);
    return (double)num / RAND_MAX * upper;
}

// 洗牌算法，遍历数组，每项与后面随机一项交换
void FisherYatesShuffle(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        Swap(arr + i, arr + i + 1 + RandUpper(n - (i + 1)));
}

// 在 [from,to) 产生num个随机数
void GenRandIntArr(int from, int to, int result[], int num) {
    // 产生值从from开始的临时数组
    int length = to - from;
    int temparr[length];
    for (int i = 0; i < length; i++)
        temparr[i] = i + from;

    FisherYatesShuffle(temparr, length);
    memcpy(result, temparr, sizeof(int) * num);
}

// 用于qsort
int IntCmp(const void *a, const void *b) {
    return *(const int *)a - *(const int *)b;
}

// 数组排序
void SortIntArr(int arr[], int n) {
    qsort(arr, n, sizeof(int), IntCmp);
}

#define Count 7

int main(void) {
    srand(time(NULL));

    int arr[Count];
    GenRandIntArr(1, 36, arr, Count);

    // SortIntArr(arr, Count);
    for (int i = 0; i < Count; i++)
        printf("%d ", arr[i]);
    putchar('\n');
}
