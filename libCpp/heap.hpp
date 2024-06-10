#ifndef HEAP_AND_PRIORITY_QUEUE_H
#define HEAP_AND_PRIORITY_QUEUE_H

#include <iostream>
#include <vector>
#include <stdexcept>

// 最小堆类
template <typename T>
class MinHeap
{
public:
    std::vector<T> heap;

    // 构造函数
    MinHeap() {}

    // 上推操作
    void pushUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (heap[index] >= heap[parent])
                break;
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    // 下推操作
    void pushDown(int index)
    {
        int size = heap.size();
        while (2 * index + 1 < size)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = left;
            if (right < size && heap[right] < heap[left])
            {
                smallest = right;
            }
            if (heap[index] <= heap[smallest])
                break;
            std::swap(heap[index], heap[smallest]);
            index = smallest;
        }
    }

    // 插入元素
    void insert(const T &value)
    {
        heap.push_back(value);
        pushUp(heap.size() - 1);
    }

    // 删除最小元素
    T extractMin()
    {
        if (heap.empty())
        {
            throw std::runtime_error("Heap is empty");
        }
        T minValue = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty())
        {
            pushDown(0);
        }
        return minValue;
    }

    // 获取最小元素
    T getMin() const
    {
        if (heap.empty())
        {
            throw std::runtime_error("Heap is empty");
        }
        return heap[0];
    }
};

// 最大堆类
template <typename T>
class MaxHeap
{
public:
    std::vector<T> heap;

    // 构造函数
    MaxHeap() {}

    // 上推操作
    void pushUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (heap[index] <= heap[parent])
                break;
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    // 下推操作
    void pushDown(int index)
    {
        int size = heap.size();
        while (2 * index + 1 < size)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = left;
            if (right < size && heap[right] > heap[left])
            {
                largest = right;
            }
            if (heap[index] >= heap[largest])
                break;
            std::swap(heap[index], heap[largest]);
            index = largest;
        }
    }

    // 插入元素
    void insert(const T &value)
    {
        heap.push_back(value);
        pushUp(heap.size() - 1);
    }

    // 删除最大元素
    T extractMax()
    {
        if (heap.empty())
        {
            throw std::runtime_error("Heap is empty");
        }
        T maxValue = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty())
        {
            pushDown(0);
        }
        return maxValue;
    }

    // 获取最大元素
    T getMax() const
    {
        if (heap.empty())
        {
            throw std::runtime_error("Heap is empty");
        }
        return heap[0];
    }
};

// 优先权队列类（基于最小堆）
template <typename T>
class PriorityQueue
{
public:
    MinHeap<T> minHeap;

    // 构造函数
    PriorityQueue() {}

    // 入队列
    void enqueue(const T &value)
    {
        minHeap.insert(value);
    }

    // 出队列
    T dequeue()
    {
        return minHeap.extractMin();
    }

    // 获取队列中的最小元素
    T peek() const
    {
        return minHeap.getMin();
    }

    // 检查队列是否为空
    bool isEmpty() const
    {
        return minHeap.heap.empty();
    }
};

#endif // HEAP_AND_PRIORITY_QUEUE_H
