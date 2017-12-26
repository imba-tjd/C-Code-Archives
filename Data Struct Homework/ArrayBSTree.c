#include <stdio.h>

int InsertTree(int tree[], int value)
{
    // 没有办法在结尾时统一乘以二，因为i++后乘以二就是2i+2了。
    // for (int i = 1; i < BUFSIZ; i *= 2)
    int i = 1;
    while (tree[i] != 0)
    {
        if (i > BUFSIZ || tree[i] == value)
            return 0;
        else if (tree[i] > value)
            i *= 2;
        else if (tree[i] < value)
            i = i * 2 + 1;
    }
    tree[i] = value;

    return 0;
}

void ShowTree(int tree[], int index)
{
    int t = tree[index];
    if (t == 0)
        return;

    ShowTree(tree, 2 * index);
    printf("%d\n", t);
    ShowTree(tree, 2 * index + 1);
}

int main(void)
{
    int tree[BUFSIZ] = {0};
    InsertTree(tree, 76);
    InsertTree(tree, 32);
    InsertTree(tree, 71);
    InsertTree(tree, 52);
    InsertTree(tree, 65);
    InsertTree(tree, 69);
    InsertTree(tree, 2);
    InsertTree(tree, 27);
    InsertTree(tree, 30);
    InsertTree(tree, 67);

    ShowTree(tree, 1);
    return 0;
}
