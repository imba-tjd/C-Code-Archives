#include <stdio.h>
#include <stdlib.h>

typedef int DataType;

typedef struct Queue
{
    int tail;   // 队列的尾，在数组中处于“前面”
    int head;   // 队列的头，在数组中处于“后面”
    int length; // 允许的最大元素数量
    DataType *elem;
} * Queue; // 循环队列

Queue CreateQueue(int length);
void EnQueue(Queue queue, DataType value);
DataType DeQueue(Queue queue);

Queue CreateQueue(int length)
{
    Queue queue = calloc(1, sizeof(struct Queue));
    if (queue == NULL)
        exit(EXIT_FAILURE);

    queue->tail = queue->head = 0;
    queue->length = length;
    queue->elem = calloc(length + 1, sizeof(DataType)); // 多一个空间空着用于判满，但不必告诉用户

    return queue;
}

void EnQueue(Queue queue, int value)
{
    if ((queue->tail + 1) % (queue->length + 1) == queue->head) // 因为实际空间比length多1，所以length也要加1。如果tail和length都不加，则空出来的位置无意义，为空时直接等于head了。
        exit(EXIT_FAILURE);

    queue->elem[queue->tail++] = value; // tail标记的位置为空
    queue->tail %= queue->length + 1;
}

DataType DeQueue(Queue queue)
{
    if (queue->head == queue->tail)
        exit(EXIT_FAILURE);

    DataType data = queue->elem[queue->head++]; // head标记的位置即为要返回的元素位置
    queue->head %= queue->length + 1;
    return data;
}

int main(void)
{
    Queue queue = CreateQueue(6);
    EnQueue(queue, 1);
    EnQueue(queue, 2);
    EnQueue(queue, 4);
    EnQueue(queue, 3);
    EnQueue(queue, 0);
    EnQueue(queue, 5);

    for (int i = 0; i < queue->length; i++)
        printf("%d\n", DeQueue(queue));

    // getchar();
    return 0;
}
