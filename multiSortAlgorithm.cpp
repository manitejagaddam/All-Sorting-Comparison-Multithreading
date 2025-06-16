#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#define TIME_SORT(name, sortFunc, nums)                                 \
{                                                                       \
    auto start = std::chrono::high_resolution_clock::now();            \
    sortFunc(nums);                                                    \
    auto end = std::chrono::high_resolution_clock::now();              \
    std::chrono::duration<double, std::milli> duration = end - start;  \
    std::cout << name << " took " << duration.count() << " ms\n";      \
}

void bubbleSort(std::vector<int> nums) {
    int noe = nums.size();
    for (int i = 0; i < noe - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < noe - i - 1; ++j) {
            if (nums[j] > nums[j + 1]) {
                std::swap(nums[j], nums[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void selectionSort(std::vector<int> nums) {
    int noe = nums.size();
    for (int i = 0; i < noe - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < noe; ++j) {
            if (nums[j] < nums[min_idx]) {
                min_idx = j;
            }
        }
        std::swap(nums[i], nums[min_idx]);
    }
}

void insertionSort(std::vector<int> nums) {
    int noe = nums.size();
    for (int i = 1; i < noe; ++i) {
        int key = nums[i];
        int j = i - 1;
        while (j >= 0 && nums[j] > key) {
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = key;
    }
}

void merge(std::vector<int>& nums, int left, int mid, int right) {
    std::vector<int> leftPart(nums.begin() + left, nums.begin() + mid + 1);
    std::vector<int> rightPart(nums.begin() + mid + 1, nums.begin() + right + 1);
    int i = 0, j = 0, k = left;

    while (i < leftPart.size() && j < rightPart.size()) {
        if (leftPart[i] <= rightPart[j]) {
            nums[k++] = leftPart[i++];
        } else {
            nums[k++] = rightPart[j++];
        }
    }

    while (i < leftPart.size()) nums[k++] = leftPart[i++];
    while (j < rightPart.size()) nums[k++] = rightPart[j++];
}

void mergeSortHelper(std::vector<int>& nums, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSortHelper(nums, left, mid);
    mergeSortHelper(nums, mid + 1, right);
    merge(nums, left, mid, right);
}

void mergeSort(std::vector<int> nums) {
    mergeSortHelper(nums, 0, nums.size() - 1);
}

int partition(std::vector<int>& nums, int low, int high) {
    int pivot = nums[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (nums[j] < pivot) {
            std::swap(nums[++i], nums[j]);
        }
    }
    std::swap(nums[i + 1], nums[high]);
    return i + 1;
}

void quickSortHelper(std::vector<int>& nums, int low, int high) {
    if (low < high) {
        int pi = partition(nums, low, high);
        quickSortHelper(nums, low, pi - 1);
        quickSortHelper(nums, pi + 1, high);
    }
}

void quickSort(std::vector<int> nums) {
    quickSortHelper(nums, 0, nums.size() - 1);
}

int main() {
    int noe;
    std::cin >> noe;
    std::vector<int> nums;
    for (int i = 0; i < noe; ++i) {
        nums.push_back(rand() % 1001);
    }

    std::thread bubble([&]() { TIME_SORT("Bubble Sort", bubbleSort, nums); });
    std::thread selection([&]() { TIME_SORT("Selection Sort", selectionSort, nums); });
    std::thread insertion([&]() { TIME_SORT("Insertion Sort", insertionSort, nums); });
    std::thread merge([&]() { TIME_SORT("Merge Sort", mergeSort, nums); });
    std::thread quick([&]() { TIME_SORT("Quick Sort", quickSort, nums); });

    bubble.join();
    selection.join();
    insertion.join();
    merge.join();
    quick.join();

    return 0;
}
