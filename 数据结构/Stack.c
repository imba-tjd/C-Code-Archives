// 本实现起始top为0，data[top]即为待赋值的位置
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef int DataType;

typedef struct Stack {
    int top;
    int len;
    DataType data[];
} Stack;

void Stack_init(Stack* s, int len) {
    s->top = 0;
    s->len = len;
}

int Stack_calculate_size(int len) {
    return sizeof(Stack) + sizeof(DataType) * len;
}

void Stack_push(Stack* stack, DataType data) {
    if (stack->top == stack->len)
        assert(0);

    stack->data[stack->top++] = data;
}

DataType Stack_pop(Stack* stack) {
    if (stack->top == 0)
        assert(0);

    return stack->data[--stack->top];
}

int main(void) {
    Stack* stack = malloc(Stack_calculate_size(10));
    Stack_init(stack, 10);

    Stack_push(stack, 1);
    Stack_push(stack, 2);
    Stack_push(stack, 3);
    assert(Stack_pop(stack) == 3);
    assert(Stack_pop(stack) == 2);
    Stack_push(stack, 4);
    assert(Stack_pop(stack) == 4);
    assert(Stack_pop(stack) == 1);

    free(stack);
}
