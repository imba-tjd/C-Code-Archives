// https://zhidao.baidu.com/question/1739181270968598267.html
#include <stdio.h>
#include <stdlib.h> // srand, rand
#include <string.h> // memcpy
#include <time.h>   // time

void Swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// 产生 [0,upper) 之间的随机一个整数
static inline int RandUpper(unsigned upper)
{
    int num;
    do
    {
        num = rand();
    } while (num == RAND_MAX);
    return (double)num / RAND_MAX * upper;
}

// 洗牌算法
void FisherYatesShuffle(size_t n, size_t m, int nums[m])
{
    srand(time(NULL));

    for (size_t i = 0; i < n; i++)
        Swap(nums + i, nums + i + 1 + RandUpper(m - (i + 1)));
}

// 用于qsort
int IntCom(const void *a, const void *b)
{
    int c = *(const int *)a;
    int d = *(const int *)b;
    return c >= d ? c == d ? 0 : 1 : -1;
}

// 对数组排序
void SortIntArr(size_t n, int nums[n])
{
    qsort(nums, n, sizeof(int), IntCom);
}

// [from,to)
void ProduceRandInt(int from, int to, size_t num, int result[num])
{
    // 初始化temparr，值从from到to
    int length = to - from;
    int *temparr = malloc(sizeof(int) * length);
    for (size_t i = 0; i < length; i++)
        temparr[i] = i + from;

    FisherYatesShuffle(num, length, temparr);
    memcpy(result, temparr, sizeof(int) * num);

    SortIntArr(num, result);
}

#define Count 7

int main()
{
    int arr[Count];
    ProduceRandInt(1, 36, Count, arr);

    for (size_t i = 0; i < Count; i++)
        printf("%d ", arr[i]);
    putchar('\n');

    return 0;
}
