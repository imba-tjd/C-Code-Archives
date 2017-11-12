// 试写一算法，对输入的一个包括权重值的数组，构建其对应的哈夫曼树，并计算打印出WPL
// 例：5 29 7 28 14 23 3 11，则WPL == 326
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int weight;
    int parenti, lchildi, rchildi;
} HTNode, *HuffmanTree;

HuffmanTree CreateHuffmanTree(int n);
int CalculateWPL(HuffmanTree ht);
int CalculateLevel(HuffmanTree ht, int i);

HuffmanTree CreateHuffmanTree(int n)
{
    HuffmanTree ht = calloc(2 * n + 1, sizeof(HTNode));
    for (int i = 0; i < n; i++) // 读入叶子节点
    {
        scanf("%d", &ht[i].weight);
        ht[i].parenti = ht[i].lchildi = ht[i].rchildi = -1;
        getchar();
    }

    for (int i = n; i < 2 * n - 1; i++) // 产生父节点
    {
        int mini1 = -1, mini2 = -1;

        for (int j = 0; j < i; j++) // 找到两个没有父节点的节点的最小项下标
        {
            if (mini1 == -1 && ht[j].parenti == -1)
            {
                mini1 = j;
                continue;
            }
            if (mini2 == -1 && ht[j].parenti == -1)
            {
                mini2 = j;
                continue;
            }
            if (ht[j].parenti == -1 && ht[j].weight < ht[mini1].weight && ht[mini1].weight > ht[mini2].weight) // 与没有父节点的节点进行比较，指向较大的那个才更改指向
            {
                mini1 = j;
                continue;
            }
            if (ht[j].parenti == -1 && ht[j].weight < ht[mini2].weight && ht[mini2].weight > ht[mini1].weight)
            {
                mini2 = j;
                continue;
            }
        }

        ht[i].weight = ht[mini1].weight + ht[mini2].weight;
        ht[i].lchildi = mini1;
        ht[i].rchildi = mini2;
        ht[i].parenti = -1;
        ht[mini1].parenti = ht[mini2].parenti = i;
    }
    return ht;
}

int CalculateWPL(HuffmanTree ht)
{
    int n = 0;
    int WPL = 0;
    HuffmanTree p = ht;
    while (1)
    {
        if (p[n++].parenti == -1)
            break;
    }
    n = (n + 1) / 2; // 算出有多少叶子节点

    for (int i = 0; i < n; i++)
        WPL += (CalculateLevel(ht, i) - 1) * ht[i].weight; // 根的路径长度为0

    return WPL;
}

int CalculateLevel(HuffmanTree ht, int i) // 计算节点的层次（根的层次为1）
{
    if (ht[i].parenti == -1)
        return 1;
    else
        return CalculateLevel(ht, ht[i].parenti) + 1;
}

int main(void)
{
    HuffmanTree ht = CreateHuffmanTree(8);
    printf("%d", CalculateWPL(ht));
    return 0;
}
