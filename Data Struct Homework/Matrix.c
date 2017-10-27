// 假设稀疏矩阵A与B均以三元组顺序表作为存储结构。试写出矩阵相加的算法，另设三元组C存放结果矩阵

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20

typedef struct Node
{
    int row, col, data; // 元素所在的行数、列数和值
} Node;

typedef struct Matrix
{
    int rows, cols, nums; // 矩阵的行数、列数和元素数
    Node nodes[MAXSIZE];
} *Matrix;

Node CreateNode(int row, int col, int data);
Matrix CreateMatrix(int rows, int cols);
int AddNode(Matrix m, Node node);
void SortMatrix(Matrix m);
void ShowMatrix(Matrix m);
Matrix MergeMatrix(Matrix m1, Matrix m2);

Node CreateNode(int row, int col, int data)
{
    Node node;
    node.row = row;
    node.col = col;
    node.data = data;
    return node;
}

Matrix CreateMatrix(int rows, int cols)
{
    Matrix m = (Matrix)malloc(sizeof(struct Matrix));
    m->rows = rows;
    m->cols = cols;
    m->nums = 0;
    return m;
}

int AddNode(Matrix m, Node node) // 往矩阵里添加元素
{
    for (int i = 0; i < m->nums; i++)
        if (m->nodes[i].row == node.row && m->nodes[i].col == node.col) // 如果已有，就把值相加
        {
            m->nodes[i].data += node.data;
            return 1;
        }

    if (m->nums + 1 == MAXSIZE)
        return 0;

    m->nodes[m->nums++] = node;
    SortMatrix(m);
    return 1;
}

void SortMatrix(Matrix m) // 把矩阵的元素按行数和列数从小到大排序
{
    for (int i = 0; i < m->nums; i++)
        for (int j = i; j < m->nums - 1; j++)
            if (m->nodes[i].row > m->nodes[j].row || m->nodes[i].col > m->nodes[j].col)
            {
                Node t = CreateNode(m->nodes[i].row, m->nodes[i].col, m->nodes[i].data);
                m->nodes[i] = m->nodes[j];
                m->nodes[j] = t;
            }
}

void ShowMatrix(Matrix m)
{
    printf("----------\n");
    for (int i = 0; i < m->nums; i++)
        printf("%d %d %d\n", m->nodes[i].row, m->nodes[i].col, m->nodes[i].data);
}

Matrix MergeMatrix(Matrix m1, Matrix m2)
{
    Matrix m3 = CreateMatrix(m1->rows, m1->cols);

    for (int i = 0; i < m1->nums; i++)
        AddNode(m3, m1->nodes[i]);

    for (int i = 0; i < m2->nums; i++)
        AddNode(m3, m2->nodes[i]);

    return m3;
}

int main(void)
{
    Matrix m1, m2, m3;

    //m1 = m2 = m3 = CreateMatrix(5, 5);
    m1 = CreateMatrix(5, 5);
    m2 = CreateMatrix(5, 5);
    m3 = CreateMatrix(5, 5);

    AddNode(m1, CreateNode(1, 1, 1));
    AddNode(m1, CreateNode(1, 2, 2));
    AddNode(m1, CreateNode(1, 3, 3));
    AddNode(m1, CreateNode(1, 4, 4));
    AddNode(m1, CreateNode(1, 5, 5));

    AddNode(m2, CreateNode(1, 1, 5));
    AddNode(m2, CreateNode(2, 1, 4));
    AddNode(m2, CreateNode(3, 1, 3));
    AddNode(m2, CreateNode(4, 1, 2));
    AddNode(m2, CreateNode(5, 1, 1));

    m3 = MergeMatrix(m1, m2);

    ShowMatrix(m1);
    ShowMatrix(m2);
    ShowMatrix(m3);

    return 0;
}