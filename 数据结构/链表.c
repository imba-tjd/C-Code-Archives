// 暂时把两个版本放到一起，等以后有机会整理再说吧
#include <stdio.h>
#include <stdlib.h>

struct student
{
    char name[10];
    float score;
    struct student *next;
};

struct student *create(int n)
{
    struct student *head, *pnew, *ptail;
    int i;
    pnew = (struct student *)malloc(sizeof(struct student));
    scanf("%s%f", pnew->name, &pnew->score);
    head = ptail = pnew;
    for (i = 0; i < n; i++)
    {
        pnew = (struct student *)malloc(sizeof(struct student));
        scanf("%s%f", pnew->name, &pnew->score);
        ptail->next = pnew;
        ptail = pnew;
    }
    ptail->next = NULL;
    return head;
}

void print(struct student *head)
{
    struct student *p = head;
    while (p != NULL)
    {
        printf("%s  %.1f\n", p->name, p->score);
        p = p->next;
    }
}

struct student *insert(struct student *head)
{
    struct student *p, *pnew, *pold;
    pnew = (struct student *)malloc(sizeof(struct student));
    scanf("%s%f", pnew->name, &pnew->score);
    p = head;
    if (pnew->score > head->score)
    {
        pnew->next = head;
        head = pnew;
    }
    else
    {
        while (p != NULL && pnew->score < p->score)
        {
            pold = p;
            p = p->next;
        }
        pnew->next = p;
        pold->next = pnew;
    }
    return head;
}

struct student *pdelete(struct student *head, int grade)
{
    struct student *p, *pold;
    p = head;
    while (head != NULL && head->score >= grade)
    {
        head = head->next;
        free(p);
        p = head;
    }
    if (head == NULL)
        return head;

    p = head->next;
    pold = head;
    while (p != NULL)
    {
        if (p->score >= grade)
        {
            pold->next = p->next;
            free(p);
            p = pold->next;
        }
        else
        {
            pold = p;
            p = p->next;
        }
    }
    return head;
}

// 另一个版本

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

