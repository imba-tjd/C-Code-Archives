// 这代码有问题。
// insertbstree时，内部会calloc一个tree，而外层的tree不会变。
// 按ctr + z后还要按一下。
// 代码设计得有问题，应该实现add。但这样create就没用了？
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // sprintf、dtrup

typedef int KeyType;
typedef char InfoType;

typedef struct BSTree
{
    KeyType key;
    InfoType info;
    struct BSTree *lchild, *rchild;
} * BSTree;

bool InputEnd; // 用于指示用户是否输入了EOF

BSTree CreateBSTree(void);
BSTree CreateTreeNode(void);
void InsertBSTree(BSTree tree, BSTree node);

void ClearInput(void);
KeyType GetKey(void);
char *NodeToString(BSTree node);
InfoType GetInfo(void);

BSTree CreateBSTree()
{
    BSTree tree = NULL, node = NULL;

    printf("Create BSTree, input ctrl + z to end.\n");
    while ((node = CreateTreeNode()) != NULL)
    {
        putchar('\n');
        InsertBSTree(tree, node);
    }

    return tree;
}

BSTree CreateTreeNode(void)
{
    BSTree tree = calloc(1, sizeof(struct BSTree));
    if (tree == NULL)
        exit(EXIT_FAILURE);

    printf("Input key:");
    tree->key = GetKey();
    if (InputEnd == true)
    {
        free(tree);
        return NULL;
    }

    printf("Input Info:");
    tree->info = GetInfo();
    if (InputEnd == true)
    {
        free(tree);
        return NULL;
    }

    return tree;
}

void InsertBSTree(BSTree tree, BSTree node)
{
    if (tree == NULL)
        tree = node;
    else if (tree->key > node->key)
        InsertBSTree(tree->lchild, node);
    else
        InsertBSTree(tree->rchild, node);
}

void IOT(BSTree tree) // 中序遍历
{
    if (tree == NULL)
        return;

    IOT(tree->lchild);

    char *ds = NodeToString(tree);
    printf("%s\n", ds);
    free(ds);

    IOT(tree->rchild);
}

// 接口函数

void ClearInput(void)
{
    while (getchar() != '\n')
        ;
}

KeyType GetKey(void)
{
    KeyType key = (KeyType)NULL;

    if (scanf("%d", &key) == EOF)
        InputEnd = true;
    ClearInput();

    return key;
}

InfoType GetInfo(void)
{
    InfoType info = (InfoType)NULL;

    if (scanf("%c", &info) == EOF)
        InputEnd = true;
    ClearInput();

    return info;
}

char *NodeToString(BSTree node)
{
    char buffer[BUFSIZ];
    sprintf(buffer, "%d\n%c\n", node->key, node->info);
    return strdup(buffer);
}

int main(void)
{
    BSTree tree = CreateBSTree();
    IOT(tree);

    return 0;
}
