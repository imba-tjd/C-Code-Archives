// 在数字三角形中寻找一条从顶部到底边的路径，使得路径上所经过的数字之和最大。路径上的每一步都只能往左下或右下走

#include <stdio.h>
#include <stdlib.h>

static int *Array;
// static int Array[15];
static int Rows;

inline static int GetNum(int row, int position)
{
    int index = row * (row - 1) / 2 + position - 1; // 前row-1行相加，首项1末项row-1项数row-1
    int result = Array[index];
    return result;
}

inline static int Max(int a, int b)
{
    return a > b ? a : b;
}

int MaxArray(int row, int position)
{
    int current = GetNum(row, position);
    if (row == Rows)
        return current;
    else
        return current + Max(MaxArray(row + 1, position), MaxArray(row + 1, position + 1));
}

int main(void)
{
    scanf("%d", &Rows);
    int count = (1 + Rows) * Rows / 2 - 1;
    Array = malloc(count * sizeof(int));
    for (int i = 0; i < count; i++)
        scanf("%d", &Array[i]);
    printf("%d", MaxArray(1, 1));

    return 0;
}

/* 实验数据及结果
5
7
3  8
8  1  0
2  7  4  4
4  5  2  6  5
30
*/
