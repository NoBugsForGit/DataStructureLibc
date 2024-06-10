#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

// 冒泡排序
void bubbleSortInPlace(int *arr, int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - 1 - i; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int *bubbleSort(const int *arr, int n)
{
    int *result = (int *)malloc(n * sizeof(int));
    memcpy(result, arr, n * sizeof(int));
    bubbleSortInPlace(result, n);
    return result;
}

// 选择排序
void selectionSortInPlace(int *arr, int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        int temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
    }
}

int *selectionSort(const int *arr, int n)
{
    int *result = (int *)malloc(n * sizeof(int));
    memcpy(result, arr, n * sizeof(int));
    selectionSortInPlace(result, n);
    return result;
}

// 插入排序
void insertionSortInPlace(int *arr, int n)
{
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int *insertionSort(const int *arr, int n)
{
    int *result = (int *)malloc(n * sizeof(int));
    memcpy(result, arr, n * sizeof(int));
    insertionSortInPlace(result, n);
    return result;
}

// 希尔排序
void shellSortInPlace(int *arr, int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; ++i)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

int *shellSort(const int *arr, int n)
{
    int *result = (int *)malloc(n * sizeof(int));
    memcpy(result, arr, n * sizeof(int));
    shellSortInPlace(result, n);
    return result;
}

// 归并排序
void merge(int *arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSortInPlace(int *arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSortInPlace(arr, l, m);
        mergeSortInPlace(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int *mergeSort(const int *arr, int n)
{
    int *result = (int *)malloc(n * sizeof(int));
    memcpy(result, arr, n * sizeof(int));
    mergeSortInPlace(result, 0, n - 1);
    return result;
}

// 快速排序
int partition(int *arr, int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSortInPlace(int *arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSortInPlace(arr, low, pi - 1);
        quickSortInPlace(arr, pi + 1, high);
    }
}

int *quickSort(const int *arr, int n)
{
    int *result = (int *)malloc(n * sizeof(int));
    memcpy(result, arr, n * sizeof(int));
    quickSortInPlace(result, 0, n - 1);
    return result;
}

// 堆排序
void heapify(int *arr, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSortInPlace(int *arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

int *heapSort(const int *arr, int n)
{
    int *result = (int *)malloc(n * sizeof(int));
    memcpy(result, arr, n * sizeof(int));
    heapSortInPlace(result, n);
    return result;
}

// 计数排序
int *countingSort(const int *arr, int n)
{
    int max = arr[0];
    int min = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
        if (arr[i] < min)
            min = arr[i];
    }

    int range = max - min + 1;
    int *count = (int *)calloc(range, sizeof(int));
    int *output = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        count[arr[i] - min]++;

    for (int i = 1; i < range; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--)
    {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }

    free(count);
    return output;
}

// 桶排序
int *bucketSort(const int *arr, int n)
{
    int max = arr[0];
    int min = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
        if (arr[i] < min)
            min = arr[i];
    }

    int bucketCount = (max - min) / 10 + 1;
    int **buckets = (int **)malloc(bucketCount * sizeof(int *));
    int *bucketSizes = (int *)malloc(bucketCount * sizeof(int));
    for (int i = 0; i < bucketCount; i++)
    {
        buckets[i] = (int *)malloc(n * sizeof(int));
        bucketSizes[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        int index = (arr[i] - min) / 10;
        buckets[index][bucketSizes[index]++] = arr[i];
    }

    for (int i = 0; i < bucketCount; i++)
    {
        insertionSortInPlace(buckets[i], bucketSizes[i]);
    }

    int *output = (int *)malloc(n * sizeof(int));
    int k = 0;
    for (int i = 0; i < bucketCount; i++)
    {
        for (int j = 0; j < bucketSizes[i]; j++)
        {
            output[k++] = buckets[i][j];
        }
        free(buckets[i]);
    }

    free(buckets);
    free(bucketSizes);
    return output;
}

// 基数排序
int getMax(const int *arr, int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

void countSortRadix(int *arr, int n, int exp)
{
    int *output = (int *)malloc(n * sizeof(int));
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    free(output);
}

int *radixSort(const int *arr, int n)
{
    int *result = (int *)malloc(n * sizeof(int));
    memcpy(result, arr, n * sizeof(int));
    int m = getMax(result, n);

    for (int exp = 1; m / exp > 0; exp *= 10)
        countSortRadix(result, n, exp);

    return result;
}

#endif // SORT_H
