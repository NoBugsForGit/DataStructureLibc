#ifndef SORT_H
#define SORT_H

#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <iterator>

namespace sort
{

    // 冒泡排序
    template <typename T>
    void bubbleSortInPlace(std::vector<T> &vec)
    {
        for (size_t i = 0; i < vec.size(); ++i)
        {
            for (size_t j = 0; j < vec.size() - 1 - i; ++j)
            {
                if (vec[j] > vec[j + 1])
                {
                    std::swap(vec[j], vec[j + 1]);
                }
            }
        }
    }

    template <typename T>
    std::vector<T> bubbleSort(const std::vector<T> &vec)
    {
        std::vector<T> result = vec;
        bubbleSortInPlace(result);
        return result;
    }

    // 选择排序
    template <typename T>
    void selectionSortInPlace(std::vector<T> &vec)
    {
        for (size_t i = 0; i < vec.size(); ++i)
        {
            size_t minIndex = i;
            for (size_t j = i + 1; j < vec.size(); ++j)
            {
                if (vec[j] < vec[minIndex])
                {
                    minIndex = j;
                }
            }
            std::swap(vec[i], vec[minIndex]);
        }
    }

    template <typename T>
    std::vector<T> selectionSort(const std::vector<T> &vec)
    {
        std::vector<T> result = vec;
        selectionSortInPlace(result);
        return result;
    }

    // 插入排序
    template <typename T>
    void insertionSortInPlace(std::vector<T> &vec)
    {
        for (size_t i = 1; i < vec.size(); ++i)
        {
            T key = vec[i];
            int j = i - 1;
            while (j >= 0 && vec[j] > key)
            {
                vec[j + 1] = vec[j];
                j--;
            }
            vec[j + 1] = key;
        }
    }

    template <typename T>
    std::vector<T> insertionSort(const std::vector<T> &vec)
    {
        std::vector<T> result = vec;
        insertionSortInPlace(result);
        return result;
    }

    // 希尔排序
    template <typename T>
    void shellSortInPlace(std::vector<T> &vec)
    {
        for (size_t gap = vec.size() / 2; gap > 0; gap /= 2)
        {
            for (size_t i = gap; i < vec.size(); ++i)
            {
                T temp = vec[i];
                size_t j;
                for (j = i; j >= gap && vec[j - gap] > temp; j -= gap)
                {
                    vec[j] = vec[j - gap];
                }
                vec[j] = temp;
            }
        }
    }

    template <typename T>
    std::vector<T> shellSort(const std::vector<T> &vec)
    {
        std::vector<T> result = vec;
        shellSortInPlace(result);
        return result;
    }

    // 归并排序
    template <typename T>
    void merge(std::vector<T> &vec, int left, int mid, int right)
    {
        std::vector<T> leftVec(vec.begin() + left, vec.begin() + mid + 1);
        std::vector<T> rightVec(vec.begin() + mid + 1, vec.begin() + right + 1);
        size_t i = 0, j = 0, k = left;
        while (i < leftVec.size() && j < rightVec.size())
        {
            if (leftVec[i] <= rightVec[j])
            {
                vec[k++] = leftVec[i++];
            }
            else
            {
                vec[k++] = rightVec[j++];
            }
        }
        while (i < leftVec.size())
        {
            vec[k++] = leftVec[i++];
        }
        while (j < rightVec.size())
        {
            vec[k++] = rightVec[j++];
        }
    }

    template <typename T>
    void mergeSortInPlace(std::vector<T> &vec, int left, int right)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;
            mergeSortInPlace(vec, left, mid);
            mergeSortInPlace(vec, mid + 1, right);
            merge(vec, left, mid, right);
        }
    }

    template <typename T>
    std::vector<T> mergeSort(const std::vector<T> &vec)
    {
        std::vector<T> result = vec;
        mergeSortInPlace(result, 0, result.size() - 1);
        return result;
    }

    // 快速排序
    template <typename T>
    int partition(std::vector<T> &vec, int low, int high)
    {
        T pivot = vec[high];
        int i = low - 1;
        for (int j = low; j < high; ++j)
        {
            if (vec[j] < pivot)
            {
                std::swap(vec[++i], vec[j]);
            }
        }
        std::swap(vec[++i], vec[high]);
        return i;
    }

    template <typename T>
    void quickSortInPlace(std::vector<T> &vec, int low, int high)
    {
        if (low < high)
        {
            int pi = partition(vec, low, high);
            quickSortInPlace(vec, low, pi - 1);
            quickSortInPlace(vec, pi + 1, high);
        }
    }

    template <typename T>
    std::vector<T> quickSort(const std::vector<T> &vec)
    {
        std::vector<T> result = vec;
        quickSortInPlace(result, 0, result.size() - 1);
        return result;
    }

    // 堆排序
    template <typename T>
    void heapify(std::vector<T> &vec, int n, int i)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && vec[left] > vec[largest])
            largest = left;

        if (right < n && vec[right] > vec[largest])
            largest = right;

        if (largest != i)
        {
            std::swap(vec[i], vec[largest]);
            heapify(vec, n, largest);
        }
    }

    template <typename T>
    void heapSortInPlace(std::vector<T> &vec)
    {
        int n = vec.size();

        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(vec, n, i);

        for (int i = n - 1; i >= 0; i--)
        {
            std::swap(vec[0], vec[i]);
            heapify(vec, i, 0);
        }
    }

    template <typename T>
    std::vector<T> heapSort(const std::vector<T> &vec)
    {
        std::vector<T> result = vec;
        heapSortInPlace(result);
        return result;
    }

    // 计数排序
    std::vector<int> countingSort(const std::vector<int> &vec)
    {
        int maxElement = *std::max_element(vec.begin(), vec.end());
        int minElement = *std::min_element(vec.begin(), vec.end());
        int range = maxElement - minElement + 1;

        std::vector<int> count(range), output(vec.size());
        for (int i = 0; i < vec.size(); i++)
            count[vec[i] - minElement]++;

        for (int i = 1; i < count.size(); i++)
            count[i] += count[i - 1];

        for (int i = vec.size() - 1; i >= 0; i--)
        {
            output[count[vec[i] - minElement] - 1] = vec[i];
            count[vec[i] - minElement]--;
        }

        return output;
    }

    // 桶排序
    template <typename T>
    std::vector<T> bucketSort(const std::vector<T> &vec)
    {
        T maxElement = *std::max_element(vec.begin(), vec.end());
        T minElement = *std::min_element(vec.begin(), vec.end());
        T range = maxElement - minElement + 1;

        int bucketCount = vec.size();
        std::vector<std::vector<T>> buckets(bucketCount);

        for (int i = 0; i < vec.size(); i++)
        {
            int bucketIndex = (vec[i] - minElement) * bucketCount / range;
            buckets[bucketIndex].push_back(vec[i]);
        }

        for (int i = 0; i < bucketCount; i++)
        {
            std::sort(buckets[i].begin(), buckets[i].end());
        }

        std::vector<T> output;
        for (int i = 0; i < bucketCount; i++)
        {
            output.insert(output.end(), buckets[i].begin(), buckets[i].end());
        }

        return output;
    }

    // 基数排序
    int getMax(const std::vector<int> &vec)
    {
        return *std::max_element(vec.begin(), vec.end());
    }

    void countSortRadix(std::vector<int> &vec, int exp)
    {
        std::vector<int> output(vec.size());
        int count[10] = {0};

        for (int i = 0; i < vec.size(); i++)
            count[(vec[i] / exp) % 10]++;

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (int i = vec.size() - 1; i >= 0; i--)
        {
            output[count[(vec[i] / exp) % 10] - 1] = vec[i];
            count[(vec[i] / exp) % 10]--;
        }

        for (int i = 0; i < vec.size(); i++)
            vec[i] = output[i];
    }

    std::vector<int> radixSort(const std::vector<int> &vec)
    {
        std::vector<int> result = vec;
        int m = getMax(result);

        for (int exp = 1; m / exp > 0; exp *= 10)
            countSortRadix(result, exp);

        return result;
    }

} // namespace sort

#endif // SORT_H
