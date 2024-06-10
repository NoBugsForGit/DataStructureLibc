#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// 栈结构体定义
typedef struct Stack
{
    int *data;    // 存储栈中元素的数组
    int top;      // 指向栈顶元素的索引
    int capacity; // 栈的容量
} Stack;

// 创建一个具有指定容量的栈
Stack *create_stack(int capacity)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->data = (int *)malloc(capacity * sizeof(int));
    return stack;
}

// 销毁栈，释放内存
void destroy_stack(Stack *stack)
{
    free(stack->data);
    free(stack);
}

// 检查栈是否为空
bool is_stack_empty(Stack *stack)
{
    return stack->top == -1;
}

// 检查栈是否已满
bool is_stack_full(Stack *stack)
{
    return stack->top == stack->capacity - 1;
}

// 将一个值压入栈
void push(Stack *stack, int value)
{
    if (is_stack_full(stack))
    {
        printf("Stack overflow\n");
        return;
    }
    stack->data[++stack->top] = value;
}

// 从栈中弹出一个值
int pop(Stack *stack)
{
    if (is_stack_empty(stack))
    {
        printf("Stack underflow\n");
        return -1; // 表示栈为空
    }
    return stack->data[stack->top--];
}

// 获取栈顶元素的值
int peek(Stack *stack)
{
    if (is_stack_empty(stack))
    {
        printf("Stack is empty\n");
        return -1; // 表示栈为空
    }
    return stack->data[stack->top];
}

#endif // STACK_H
