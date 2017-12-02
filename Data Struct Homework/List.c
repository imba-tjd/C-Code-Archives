#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int DataType;

typedef struct List
{
    DataType data;
    struct List *next;
} * List, *Node;

List CreateList(void);
List CreateNode(DataType data);
bool Insert(List list, DataType data, int (*Compare)(DataType data1, DataType data2));

List CreateList(void)
{
    List list = calloc(1, sizeof(struct List));
    if (list == NULL)
        exit(EXIT_FAILURE);

    return list;
}

Node CreateNode(DataType data)
{
    Node node = calloc(1, sizeof(struct List));
    if (node == NULL)
        exit(EXIT_FAILURE);

    node->data = data;

    return node;
}

bool Insert(List list, DataType data, int (*Compare)(DataType data1, DataType data2))
{
    assert(list != NULL && Compare != NULL);

    Node node = CreateNode(data);

    while (list->next != NULL)
    {
        int result = Compare(list->next->data, data); // data与list的下一项进行比较

        if (result == 0) // 已经存在
            return false;

        if (result > 0) // 从小到大递增
        {
            node->next = list->next;
            list->next = node;
            return true;
        }
        list = list->next;
    }

    list->next = node; // 插入尾部

    return true;
}

// 接口函数
#define INSERT(list, data) Insert(list, data, &Compare)

int Compare(DataType data1, DataType data2)
{
    return data1 >= data2 ? data1 > data2 ? 1 : 0 : -1;
}

int main(void)
{
    List list = CreateList();
    // Insert(list, 1, &Compare);
    INSERT(list, 1);
    INSERT(list, 2);
    INSERT(list, 4);
    INSERT(list, 3);
    INSERT(list, 0);
    INSERT(list, 5);

    List p = list;
    while ((p = p->next) != NULL)
        printf("%d\n", p->data);

    // getchar();
    return 0;
}
