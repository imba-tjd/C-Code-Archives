// 如果使用非对称区间，s[t++]为push,s[--t]为pop（数组栈）
#include <stdio.h>
#include <stdlib.h>

typedef int DataType;

typedef struct Stack
{
    int top;
    DataType *data;
} * Stack;

Stack CreateStack(int capacity);
void Push(Stack stack, DataType data);
DataType Pop(Stack stack);

Stack CreateStack(int capacity)
{
    Stack stack = calloc(1, sizeof(struct Stack));
    if (stack == NULL)
        exit(EXIT_FAILURE);

    stack->data = calloc(capacity, sizeof(DataType));
    stack->top = -1;

    return stack;
}

void Push(Stack stack, DataType data)
{
    if (stack->top == sizeof(stack->data))
        exit(EXIT_FAILURE);

    stack->data[++stack->top] = data;
}

DataType Pop(Stack stack)
{
    if (stack->top == -1)
        exit(EXIT_FAILURE);

    return stack->data[stack->top--];
}

int main(void)
{
    Stack stack = CreateStack(10);
    Push(stack, 1);
    Push(stack, 2);
    Push(stack, 4);
    Push(stack, 3);
    Push(stack, 0);
    Push(stack, 5);

    while (stack->top != -1)
        printf("%d\n", Pop(stack));

    // getchar();
    return 0;
}
