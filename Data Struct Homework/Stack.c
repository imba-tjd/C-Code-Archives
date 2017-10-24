#include <stdio.h>
#include <stdlib.h>

#define M 100 //栈的空间
typedef struct
{
    int data[M];
    int top;
} SqStack;

SqStack *InitStack(void);
int Push(SqStack *const stack, int value);
int Pop(SqStack *const stack);

// 返回栈指针
SqStack *InitStack(void)
{
    SqStack *stack = (SqStack *)malloc(sizeof(SqStack));
    stack->top = -1;
    return stack;
}

// 略
int Push(SqStack *const stack, int value)
{
    if (stack->top == M - 1)
        return 1;
    stack->data[++stack->top] = value;
    return 0;
}

// 略
int Pop(SqStack *const stack)
{
    if (stack->top == -1)
        exit(0xff);
    return stack->data[stack->top--];
}

int main(void)
{
    SqStack *stack = InitStack();
    Push(stack, 1);
    Push(stack, 2);
    Push(stack, 4);
    Push(stack, 3);
    Push(stack, 0);
    Push(stack, 5);

    while (stack->top != -1)
        printf("%d\n", Pop(stack));

    getchar();
    return 0;
}
