#include <stdio.h>
#include <stdlib.h>

typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode;

LNode *CreateList(void);
void Insert(LNode *const head, int value);

// 返回头结点指针
LNode *CreateList(void)
{
    LNode *head = (LNode *)malloc(sizeof(LNode));
    head->next = NULL;
    return head;
}

// 插入节点
void Insert(LNode *const head, int value)
{
    LNode *p = head;
    LNode *q = (LNode *)malloc(sizeof(LNode));

    q->data = value;
    q->next = NULL;

    while (p->next != NULL)
    {
        if (p->next->data >= value) // 从小到大递增
        {
            q->next = p->next;
            p->next = q;
            return;
        }
        p = p->next;
    }
    p->next = q;
}

int main(void)
{
    LNode *const head = CreateList();
    Insert(head, 1);
    Insert(head, 2);
    Insert(head, 4);
    Insert(head, 3);
    Insert(head, 0);
    Insert(head, 5);

    LNode *p = head->next;
    while (p != NULL)
    {
        printf("%d\n", p->data);
        p = p->next;
    }

    getchar();
    return 0;
}
