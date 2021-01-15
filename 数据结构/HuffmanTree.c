// 输入的一个包括权重值的数组，构建其对应的哈夫曼树，并计算WPL（带权路径长度）
// 本代码其实基于数组构建了森林，不过合并两棵树时会生成新结点，与普通的树不同
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int weight;
    int parenti, lchildi, rchildi;
} HTNode;

HTNode HTNode_create(int weight) {
    HTNode node;
    node.weight = weight;
    node.parenti = node.lchildi = node.rchildi = -1;  // 表示不存在
    return node;
}

void HTNode_make_huffman_tree(HTNode ht[], int n) {
    for (int i = n; i < 2 * n - 1; i++) {  // 在空位置上产生合并后的结点；[0,n)直到最后都是叶子结点
        int min1ndx = -1, min2ndx = -1;

        for (int j = 0; j < i; j++) {  // 存在结点的范围
            if (ht[j].parenti != -1)   // 有父结点，忽略
                continue;

            // 从左往右找两个没有父结点且值最小的结点
            if (min1ndx == -1)
                min1ndx = j;
            else if (min2ndx == -1)
                min2ndx = j;
            else if (ht[j].weight < ht[min1ndx].weight && ht[min1ndx].weight > ht[min2ndx].weight)  // 覆盖值较大的那个
                min1ndx = j;
            else if (ht[j].weight < ht[min2ndx].weight && ht[min2ndx].weight > ht[min1ndx].weight)
                min2ndx = j;
            // else 比两个都大，什么也不做；不可能比其中一个小的同时后者条件两个都不满足
        }

        // 添加到右边的空位上
        ht[i] = HTNode_create(ht[min1ndx].weight + ht[min2ndx].weight);
        ht[i].lchildi = min1ndx;
        ht[i].rchildi = min2ndx;
        // ht[i].parenti = -1; // 不用create而手动设置就要这一条
        ht[min1ndx].parenti = ht[min2ndx].parenti = i;
    }
}

int HTNode_get_level(HTNode ht[], int i) {  // 计算结点的层次，根的层次为1
    return ht[i].parenti == -1 ? 1 : HTNode_get_level(ht, ht[i].parenti) + 1;
}

int HTNode_get_WPL(HTNode ht[], int n) {
    int WPL = 0;
    for (int i = 0; i < n; i++)
        WPL += (HTNode_get_level(ht, i) - 1) * ht[i].weight;  // 根的路径长度为0
    return WPL;
}

int main(void) {
#define LEN 8
    HTNode nodes[LEN * 2 - 1]; // 需要存放合并生成的新结点
    int arr[LEN] = {5, 29, 7, 28, 14, 23, 3, 11};
    for (int i = 0; i < 8; i++)
        nodes[i] = HTNode_create(arr[i]);

    HTNode_make_huffman_tree(nodes, LEN);
    assert(HTNode_get_WPL(nodes, LEN) == 326);
}
