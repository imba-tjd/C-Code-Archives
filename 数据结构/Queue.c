// 基于数组的循环队列实现，tail是待插入位置，head==tail时为空，tail+1==head时为满
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef int DataType;

typedef struct Queue {
    int tail;  // 队列的尾，在数组中处于“前面”
    int head;  // 队列的头，在数组中处于“后面”
    int len;   // 允许的最大元素数量再加1
    DataType data[];
} Queue;

void Queue_init(Queue* q, int len) {
    q->tail = q->head = 0;
    q->len = len + 1;
}

int Queue_calculate_size(int len) {
    return sizeof(Queue) + sizeof(DataType) * (len + 1);
}

void Queue_enqueue(Queue* q, DataType value) {
    if ((q->tail + 1) % (q->len) == q->head)
        assert(0);

    q->data[q->tail++] = value;
    q->tail %= q->len;  // 这样两句都改变了tail，可读性不如tail=(tail+1)%len
}

DataType Queue_dequeue(Queue* queue) {
    if (queue->head == queue->tail)
        assert(0);

    DataType data = queue->data[queue->head++];  // head标记的位置即为要返回的元素位置
    queue->head %= queue->len;
    return data;
}

// 如果tail比head小，加了len就为正；如果大，就相当于没加len
int Queue_count(Queue* q) {
    return (q->tail - q->head + q->len) % q->len;
}

int main(void) {
    Queue* q = malloc(Queue_calculate_size(4));
    Queue_init(q, 4);

    assert(Queue_count(q) == 0);
    Queue_enqueue(q, 1);
    Queue_enqueue(q, 2);
    Queue_enqueue(q, 3);
    Queue_enqueue(q, 4);
    assert(Queue_count(q) == 4);
    // Queue_enqueue(q, 5);
    assert(Queue_dequeue(q) == 1);
    assert(Queue_dequeue(q) == 2);
    assert(Queue_count(q) == 2);
    Queue_enqueue(q, 5);
    Queue_enqueue(q, 6);
    assert(Queue_count(q) == 4);
    assert(Queue_dequeue(q) == 3);
    assert(Queue_dequeue(q) == 4);
    assert(Queue_dequeue(q) == 5);
    assert(Queue_dequeue(q) == 6);
    assert(Queue_count(q) == 0);
    // Queue_dequeue(q);

    free(q);
}
