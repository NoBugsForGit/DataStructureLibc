#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// 定义堆的结构
typedef struct
{
    int *data;
    int size;
    int capacity;
} Heap;

// 初始化堆
Heap *createHeap(int capacity)
{
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->data = (int *)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// 交换两个元素
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 最小堆上推操作
void minHeapPushUp(Heap *heap, int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (heap->data[index] >= heap->data[parent])
            break;
        swap(&heap->data[index], &heap->data[parent]);
        index = parent;
    }
}

// 最小堆下推操作
void minHeapPushDown(Heap *heap, int index)
{
    int size = heap->size;
    while (2 * index + 1 < size)
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = left;
        if (right < size && heap->data[right] < heap->data[left])
        {
            smallest = right;
        }
        if (heap->data[index] <= heap->data[smallest])
            break;
        swap(&heap->data[index], &heap->data[smallest]);
        index = smallest;
    }
}

// 最大堆上推操作
void maxHeapPushUp(Heap *heap, int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (heap->data[index] <= heap->data[parent])
            break;
        swap(&heap->data[index], &heap->data[parent]);
        index = parent;
    }
}

// 最大堆下推操作
void maxHeapPushDown(Heap *heap, int index)
{
    int size = heap->size;
    while (2 * index + 1 < size)
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = left;
        if (right < size && heap->data[right] > heap->data[left])
        {
            largest = right;
        }
        if (heap->data[index] >= heap->data[largest])
            break;
        swap(&heap->data[index], &heap->data[largest]);
        index = largest;
    }
}

// 插入元素到最小堆
void minHeapInsert(Heap *heap, int value)
{
    if (heap->size == heap->capacity)
    {
        heap->capacity *= 2;
        heap->data = (int *)realloc(heap->data, heap->capacity * sizeof(int));
    }
    heap->data[heap->size++] = value;
    minHeapPushUp(heap, heap->size - 1);
}

// 插入元素到最大堆
void maxHeapInsert(Heap *heap, int value)
{
    if (heap->size == heap->capacity)
    {
        heap->capacity *= 2;
        heap->data = (int *)realloc(heap->data, heap->capacity * sizeof(int));
    }
    heap->data[heap->size++] = value;
    maxHeapPushUp(heap, heap->size - 1);
}

// 删除最小堆的最小元素
int minHeapExtractMin(Heap *heap)
{
    if (heap->size == 0)
    {
        fprintf(stderr, "Heap is empty\n");
        exit(EXIT_FAILURE);
    }
    int minValue = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    minHeapPushDown(heap, 0);
    return minValue;
}

// 删除最大堆的最大元素
int maxHeapExtractMax(Heap *heap)
{
    if (heap->size == 0)
    {
        fprintf(stderr, "Heap is empty\n");
        exit(EXIT_FAILURE);
    }
    int maxValue = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    maxHeapPushDown(heap, 0);
    return maxValue;
}

// 获取最小堆的最小元素
int minHeapGetMin(const Heap *heap)
{
    if (heap->size == 0)
    {
        fprintf(stderr, "Heap is empty\n");
        exit(EXIT_FAILURE);
    }
    return heap->data[0];
}

// 获取最大堆的最大元素
int maxHeapGetMax(const Heap *heap)
{
    if (heap->size == 0)
    {
        fprintf(stderr, "Heap is empty\n");
        exit(EXIT_FAILURE);
    }
    return heap->data[0];
}

// 删除堆
void deleteHeap(Heap *heap)
{
    free(heap->data);
    free(heap);
}

// 优先权队列（基于最小堆）
typedef struct
{
    Heap *minHeap;
} PriorityQueue;

// 创建优先权队列
PriorityQueue *createPriorityQueue(int capacity)
{
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    pq->minHeap = createHeap(capacity);
    return pq;
}

// 入队列
void enqueue(PriorityQueue *pq, int value)
{
    minHeapInsert(pq->minHeap, value);
}

// 出队列
int dequeue(PriorityQueue *pq)
{
    return minHeapExtractMin(pq->minHeap);
}

// 获取队列中的最小元素
int peek(const PriorityQueue *pq)
{
    return minHeapGetMin(pq->minHeap);
}

// 检查队列是否为空
bool isEmpty(const PriorityQueue *pq)
{
    return pq->minHeap->size == 0;
}

// 删除优先权队列
void deletePriorityQueue(PriorityQueue *pq)
{
    deleteHeap(pq->minHeap);
    free(pq);
}
