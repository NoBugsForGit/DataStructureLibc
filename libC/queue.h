#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// 队列结构体定义
typedef struct Queue
{
    int *data;    // 存储队列中元素的数组
    int front;    // 指向队列头元素的索引
    int rear;     // 指向队列尾元素的索引
    int size;     // 队列中元素的数量
    int capacity; // 队列的容量
} Queue;

// 创建一个具有指定容量的队列
Queue *create_queue(int capacity)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->data = (int *)malloc(capacity * sizeof(int));
    return queue;
}

// 销毁队列，释放内存
void destroy_queue(Queue *queue)
{
    free(queue->data);
    free(queue);
}

// 检查队列是否为空
bool is_queue_empty(Queue *queue)
{
    return queue->size == 0;
}

// 检查队列是否已满
bool is_queue_full(Queue *queue)
{
    return queue->size == queue->capacity;
}

// 将一个值加入队列
void enqueue(Queue *queue, int value)
{
    if (is_queue_full(queue))
    {
        printf("Queue overflow\n");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = value;
    queue->size++;
}

// 从队列中移除一个值
int dequeue(Queue *queue)
{
    if (is_queue_empty(queue))
    {
        printf("Queue underflow\n");
        return -1; // 表示队列为空
    }
    int value = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return value;
}

// 获取队列头元素的值
int front(Queue *queue)
{
    if (is_queue_empty(queue))
    {
        printf("Queue is empty\n");
        return -1; // 表示队列为空
    }
    return queue->data[queue->front];
}

// 获取队列尾元素的值
int rear(Queue *queue)
{
    if (is_queue_empty(queue))
    {
        printf("Queue is empty\n");
        return -1; // 表示队列为空
    }
    return queue->data[queue->rear];
}

#endif // QUEUE_H
