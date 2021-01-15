#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct BST {
    int data;
    struct BST *ltree, *rtree;
} BST;

void BST_init(BST *node, int data) {
    node->data = data;
    node->ltree = node->rtree = NULL;
}

BST *BST_new(int data) {
    BST *node = malloc(sizeof(BST));
    BST_init(node, data);
    return node;
}

// 如果用BST *tree，必须从父结点赋值，且要单独处理头结点，导致变复杂，也许更适合循环实现
void BST_insert(BST **tree, BST *node) {
    if (*tree == NULL)
        *tree = node;
    else if ((*tree)->data > node->data)
        BST_insert(&(*tree)->ltree, node);
    else
        BST_insert(&(*tree)->rtree, node);
}

// 递归中序遍历输出。根据BST的性质，刚好等于排序后的结果
void BST_show(const BST *tree) {
    if (tree == NULL)
        return;
    BST_show(tree->ltree);
    printf("%d ", tree->data);
    BST_show(tree->rtree);
}

BST *BST_find(BST *tree, int data) {
    // 也可以用一个return加?:
    if (tree == NULL || tree->data == data)
        return tree;
    else if (tree->data > data)
        return BST_find(tree->ltree, data);
    else
        return BST_find(tree->rtree, data);
}

int main(void) {
    BST *tree = NULL;

    int arr[10] = {4, 28, 19, 8, 22, 14, 27, 25, 7, 11};
    for (int i = 0; i < 10; i++)
        BST_insert(&tree, BST_new(arr[i]));

    BST_show(tree);
    putchar('\n');

    assert(BST_find(tree, 22)->data == 22);
    assert(BST_find(tree, 21) == NULL);
}
