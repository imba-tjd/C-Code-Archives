// 理论最差空间复杂度为2^n
#include <assert.h>
#include <stdio.h>

// 迭代实现插入
void insert(int tree[], int len, int value) {
    // 不能改成for在结尾时统一乘以二，因为i++后乘以二就是2i+2了。
    int i = 1;
    while (tree[i] != 0) {  // 把0看作无数据
        if (i >= len)
            assert(0);
        else if (tree[i] == value)
            return;
        else if (tree[i] > value)
            i *= 2;
        else
            i = i * 2 + 1;
    }
    tree[i] = value;
}

// 递归中序遍历输出
void show(const int tree[], int len, int index) {
    if (index >= len || tree[index] == 0)
        return;

    show(tree, len, 2 * index);
    printf("%d ", tree[index]);
    show(tree, len, 2 * index + 1);
}

// 与insert的逻辑一致，不过是递归
int find(const int tree[], int len, int index, int value) {
    if (index >= len || tree[index] == 0)
        return -1;
    else if (tree[index] == value)
        return index;
    else if (tree[index] > value)
        return find(tree, len, 2 * index, value);
    else
        return find(tree, len, 2 * index + 1, value);
}

int main(void) {
#define LEN BUFSIZ
    int tree[LEN] = {0};

    insert(tree, LEN, 32);
    insert(tree, LEN, 71);
    insert(tree, LEN, 52);
    insert(tree, LEN, 76);
    insert(tree, LEN, 65);
    insert(tree, LEN, 69);
    insert(tree, LEN, 2);
    insert(tree, LEN, 27);
    insert(tree, LEN, 30);
    insert(tree, LEN, 67);

    show(tree, LEN, 1);
    putchar('\n');

    assert(find(tree, LEN, 1, 40) == -1);
    assert(find(tree, LEN, 1, 30) == 11);
    assert(find(tree, LEN, 1, 67) == 54);
}
