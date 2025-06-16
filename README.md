# 🧠 Multi-Threaded Sorting Algorithm Benchmark

![C++](https://img.shields.io/badge/language-C++17-blue)
![License](https://img.shields.io/badge/license-MIT-green)

## Overview

This project demonstrates and compares the performance of five fundamental sorting algorithms:

- Bubble Sort
- Selection Sort
- Insertion Sort
- Merge Sort
- Quick Sort

Each algorithm is executed in a separate thread, enabling concurrent benchmarking. The idea is to visualize the efficiency differences, especially as input size increases.



## Key Concepts

### Why Multiple Threads?

Sorting functions are executed in parallel threads to:

- Utilize multi-core CPUs.
- Avoid sequential bottlenecks.
- Observe time differences between algorithms without sequential delays.

> **Note:** All sorting functions receive `std::vector<int> nums` **by value**, meaning each thread works on its own copy — avoiding race conditions.

---

## Breakdown of Each Sorting Algorithm

### 1. **Bubble Sort**

- **Intuition:** Repeatedly swaps adjacent elements if they're in the wrong order.
- **Time Complexity:** Worst: O(n^2), Best: O(n) if already sorted
- **Usage:** Best for educational purposes, not used in practice.

### 2. **Selection Sort**

- **Intuition:** Repeatedly finds the minimum element and moves it to the sorted part.
- **Time Complexity:** Always O(n^2)
- **Usage:** Simple but inefficient for large datasets.

### 3. **Insertion Sort**

- **Intuition:** Builds the sorted array one item at a time by inserting elements at their correct position.
- **Time Complexity:** Worst: O(n^2), Best: O(n) when nearly sorted
- **Usage:** Efficient for small or nearly sorted datasets.

### 4. **Merge Sort**

- **Intuition:** Divide and conquer approach; splits array, sorts subarrays, merges them.
- **Time Complexity:** O(n log n)
- **Space Complexity:** O(n)
- **Usage:** Reliable for large datasets, stable sort.

### 5. **Quick Sort**

- **Intuition:** Picks a pivot, partitions array around it, recursively sorts partitions.
- **Time Complexity:** Avg: O(n log n), Worst: O(n^2)
- **Space Complexity:** O(log n)
- **Usage:** Very fast in practice but unstable. Widely used.

---

## Code With Timing Logic (Chrono)

```cpp
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

// All sorting functions: bubbleSort, selectionSort, insertionSort, mergeSort, quickSort as implemented in your code
// ... [Omitted for brevity — identical logic]

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
```

---

## Performance Comparison Table

| Elements | Bubble Sort | Selection Sort | Insertion Sort | Merge Sort | Quick Sort |
| -------- | ----------- | -------------- | -------------- | ---------- | ---------- |
| 1        | 0.0022 ms   | 0.0025 ms      | 0.0017 ms      | 0.0022 ms  | 0.0017 ms  |
| 10       | 0.011 ms    | 0.0028 ms      | 0.0023 ms      | 0.0018 ms  | 0.0017 ms  |
| 100      | 0.0541 ms   | 0.0521 ms      | 0.0862 ms      | 0.0163 ms  | 0.146  ms  |
| 1,000    | 17.6035 ms  | 11.3609 ms     | 9.4179 ms      | 4.2221 ms  | 1.8528 ms  |
| 10,000   | 838.599 ms  | 461.341 ms     | 323.572 ms     | 9.5766 ms  | 2.0979 ms  |
| 100,000  | 144618 ms   | 87839.2 ms     | 71072.4 ms     | 174.152 ms | 111.371 ms |

---

## General Observations

- **Bubble/Selection/Insertion Sorts** degrade drastically after 1,000 elements due to O(n²) complexity.
- **Merge Sort** and **Quick Sort** perform extremely well even up to 100,000 elements.
- **Quick Sort** outperforms Merge Sort for small and medium sizes due to lower overhead.

---

## Requirements

- C++17 or later
- g++ compiler with pthread support
- Windows/Linux environment

## How to Run

1. Compile:
```bash
g++ -std=c++17 -pthread -O2 multiSortAlgorithm.cpp -o multiSortAlgorithm.exe
```
2. Run:
```bash
./multiSortAlgorithm.exe
```
3. Input:
```
10000   // or any size you want to test
```

## Project Structure

```
multiSortAlgorithm.cpp    # Main source code with multi-threaded logic
README.md                 # Documentation and benchmark explanation
```

## Conclusion

This multi-threaded sort comparison helps:

- Understand strengths/weaknesses of sorting algorithms.
- Observe real-time performance scaling.
- Practice thread-safe programming in C++.

> ✅ For large data: Use **Quick Sort** or **Merge Sort**. ❌ Avoid Bubble/Selection/Insertion beyond a few thousand elements.

---

## Author
**Mani** - [GitHub Profile](https://github.com/your-github-username)

---

Feel free to contribute or raise an issue if you’d like to add features such as:
- GUI Visualizations
- STL sort comparisons
- Graph-based performance charting

---

