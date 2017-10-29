#include <stdio.h>
#include <stdlib.h>

#define M 100 //队列长度
typedef struct
{
    int elem[M]; //存储空间基址
    int rear;    //尾指针，若队列不空，指向队尾元素
    int front;   //当前队列的长度，即元素个数
} SqQueue;

SqQueue *InitQueue(void);
int EnQueue(SqQueue *const queue, int value);
int DeQueue(SqQueue *const queue);

// 返回循环队列指针
SqQueue *InitQueue(void)
{
    SqQueue *queue = (SqQueue *)malloc(sizeof(SqQueue));
    queue->rear = queue->front = 0;
    return queue;
}

// 入队
int EnQueue(SqQueue *const queue, int value)
{
    if ((queue->rear + 1) % M == queue->front)
        return 1;
    queue->elem[(queue->rear++) % M] = value; // rear标记的位置为空
    return 0;
}

// 出队
int DeQueue(SqQueue *const queue)
{
    if (queue->front == queue->rear)
        exit(0xff);
    return queue->elem[(queue->front++) % M];
}

int main(void)
{
    SqQueue *queue = InitQueue();
    EnQueue(queue, 1);
    EnQueue(queue, 2);
    EnQueue(queue, 4);
    EnQueue(queue, 3);
    EnQueue(queue, 0);
    EnQueue(queue, 5);

    while (queue->front != queue->rear)
        printf("%d\n", DeQueue(queue));

    getchar();
    return 0;
}
