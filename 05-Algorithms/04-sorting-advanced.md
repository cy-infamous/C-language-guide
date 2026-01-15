# Advanced Sorting Algorithms

## Table of Contents
1. [Introduction](#introduction)
2. [Merge Sort](#merge-sort)
3. [Quick Sort](#quick-sort)
4. [Heap Sort](#heap-sort)
5. [Comparison of Advanced Sorting](#comparison)
6. [Practice Problems](#practice-problems)

---

## Introduction

Advanced sorting algorithms achieve **O(n log n)** time complexity, making them efficient for large datasets.

### Why O(n log n)?
- **Comparison-based sorting** has a lower bound of Ω(n log n)
- Based on decision tree model
- Any comparison-based sort cannot do better than O(n log n) in worst case

### Categories
1. **Divide and Conquer**: Merge Sort, Quick Sort
2. **Heap-based**: Heap Sort
3. **Hybrid**: Timsort, Introsort

---

## Merge Sort

**Merge Sort** is a divide-and-conquer algorithm that divides the array into two halves, recursively sorts them, and then merges the sorted halves.

### Algorithm Explanation

**Divide and Conquer Strategy**:
1. **Divide**: Split array into two halves
2. **Conquer**: Recursively sort both halves
3. **Combine**: Merge two sorted halves

### Pseudocode
```
MergeSort(array, left, right):
    if left < right:
        mid = (left + right) / 2
        MergeSort(array, left, mid)
        MergeSort(array, mid+1, right)
        Merge(array, left, mid, right)

Merge(array, left, mid, right):
    // Create temp arrays
    L[] = array[left...mid]
    R[] = array[mid+1...right]

    // Merge back into array
    i = 0, j = 0, k = left
    while i < len(L) AND j < len(R):
        if L[i] <= R[j]:
            array[k++] = L[i++]
        else:
            array[k++] = R[j++]

    // Copy remaining elements
    Copy remaining elements from L or R
```

### Visual Trace

**Example**: Sort [38, 27, 43, 3, 9, 82, 10]

```
DIVIDE PHASE (Top-Down):

                    [38, 27, 43, 3, 9, 82, 10]
                              ↓
                    ┌─────────┴──────────┐
                    ↓                    ↓
            [38, 27, 43, 3]        [9, 82, 10]
                    ↓                    ↓
            ┌───────┴────────┐      ┌────┴─────┐
            ↓                ↓      ↓          ↓
      [38, 27]          [43, 3]  [9, 82]    [10]
            ↓                ↓      ↓
      ┌─────┴─────┐    ┌────┴─┐   ┌┴─┐
      ↓           ↓    ↓      ↓   ↓  ↓
    [38]        [27] [43]   [3] [9][82]


MERGE PHASE (Bottom-Up):

    [38]  [27]    [43]  [3]    [9]  [82]   [10]
      ↓     ↓      ↓     ↓      ↓     ↓      ↓
      Merge pairs             Merge pairs
      ↓                        ↓
    [27, 38]               [3, 43]      [9, 82]   [10]
      ↓                        ↓             ↓
      ─────────Merge──────────              ↓
              ↓                              ↓
        [3, 27, 38, 43]                [9, 10, 82]
              ↓                              ↓
              ──────────Merge────────────────
                          ↓
              [3, 9, 10, 27, 38, 43, 82]


DETAILED MERGE STEPS:

Step 1: Merge [38] and [27]
Compare 38 and 27 → 27 < 38
Result: [27, 38]

Step 2: Merge [43] and [3]
Compare 43 and 3 → 3 < 43
Result: [3, 43]

Step 3: Merge [9] and [82]
Compare 9 and 82 → 9 < 82
Result: [9, 82]

Step 4: Merge [27, 38] and [3, 43]
Compare 27 and 3 → 3 < 27, add 3
Compare 27 and 43 → 27 < 43, add 27
Compare 38 and 43 → 38 < 43, add 38
Add remaining 43
Result: [3, 27, 38, 43]

Step 5: Merge [9, 82] and [10]
Compare 9 and 10 → 9 < 10, add 9
Compare 82 and 10 → 10 < 82, add 10
Add remaining 82
Result: [9, 10, 82]

Step 6: Merge [3, 27, 38, 43] and [9, 10, 82]
Compare 3 and 9 → 3 < 9, add 3
Compare 27 and 9 → 9 < 27, add 9
Compare 27 and 10 → 10 < 27, add 10
Compare 27 and 82 → 27 < 82, add 27
Compare 38 and 82 → 38 < 82, add 38
Compare 43 and 82 → 43 < 82, add 43
Add remaining 82
Result: [3, 9, 10, 27, 38, 43, 82]
```

### C Implementation

```c
#include <stdio.h>
#include <stdlib.h>

// Utility function
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Merge two sorted subarrays
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;  // Size of left subarray
    int n2 = right - mid;      // Size of right subarray

    // Create temporary arrays
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    // Merge the temporary arrays back
    int i = 0;      // Initial index of left subarray
    int j = 0;      // Initial index of right subarray
    int k = left;   // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Free temporary arrays
    free(L);
    free(R);
}

// Merge Sort function
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Calculate middle point
        int mid = left + (right - left) / 2;

        // Sort first half
        mergeSort(arr, left, mid);

        // Sort second half
        mergeSort(arr, mid + 1, right);

        // Merge sorted halves
        merge(arr, left, mid, right);
    }
}

// Merge Sort with detailed trace
void mergeSortTrace(int arr[], int left, int right, int level) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Print divide step
        printf("%*sDivide [%d:%d] into [%d:%d] and [%d:%d]\n",
               level * 2, "", left, right, left, mid, mid + 1, right);

        // Print current range
        printf("%*s  Range: ", level * 2, "");
        for (int i = left; i <= right; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        // Recursively sort subarrays
        mergeSortTrace(arr, left, mid, level + 1);
        mergeSortTrace(arr, mid + 1, right, level + 1);

        // Merge
        merge(arr, left, mid, right);

        // Print merge result
        printf("%*sMerge [%d:%d] + [%d:%d] → [%d:%d]\n",
               level * 2, "", left, mid, mid + 1, right, left, right);
        printf("%*s  Result: ", level * 2, "");
        for (int i = left; i <= right; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
}

// Iterative Merge Sort (bottom-up)
void mergeSortIterative(int arr[], int n) {
    // Start with merge subarrays of size 1
    for (int currSize = 1; currSize < n; currSize = 2 * currSize) {
        // Pick starting index of left subarray
        for (int leftStart = 0; leftStart < n - 1; leftStart += 2 * currSize) {
            // Find ending point of left subarray
            int mid = leftStart + currSize - 1;

            // Find ending point of right subarray
            int rightEnd = (leftStart + 2 * currSize - 1 < n - 1) ?
                          (leftStart + 2 * currSize - 1) : (n - 1);

            // Merge subarrays
            if (mid < rightEnd) {
                merge(arr, leftStart, mid, rightEnd);
            }
        }
    }
}

// Count inversions using merge sort
int mergeAndCount(int arr[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    int invCount = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            invCount += (mid - i + 1);  // Count inversions
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return invCount;
}

int mergeSortAndCount(int arr[], int temp[], int left, int right) {
    int invCount = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;

        invCount += mergeSortAndCount(arr, temp, left, mid);
        invCount += mergeSortAndCount(arr, temp, mid + 1, right);
        invCount += mergeAndCount(arr, temp, left, mid, right);
    }
    return invCount;
}

// Demonstration function
void demonstrateMergeSort() {
    printf("=== MERGE SORT DEMONSTRATION ===\n\n");

    // Example 1: Basic merge sort
    int arr1[] = {38, 27, 43, 3, 9, 82, 10};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    printf("Example 1: Basic Merge Sort\n");
    printf("Original: ");
    printArray(arr1, n1);

    mergeSort(arr1, 0, n1 - 1);

    printf("Sorted:   ");
    printArray(arr1, n1);
    printf("\n");

    // Example 2: Detailed trace
    int arr2[] = {12, 11, 13, 5, 6};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    printf("Example 2: Detailed Trace\n");
    printf("Original: ");
    printArray(arr2, n2);
    printf("\n");

    mergeSortTrace(arr2, 0, n2 - 1, 0);

    printf("\nFinal sorted: ");
    printArray(arr2, n2);
    printf("\n");

    // Example 3: Iterative merge sort
    int arr3[] = {5, 2, 4, 7, 1, 3, 2, 6};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    printf("Example 3: Iterative Merge Sort\n");
    printf("Original: ");
    printArray(arr3, n3);

    mergeSortIterative(arr3, n3);

    printf("Sorted:   ");
    printArray(arr3, n3);
    printf("\n");

    // Example 4: Count inversions
    int arr4[] = {8, 4, 2, 1};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    int* temp = (int*)malloc(n4 * sizeof(int));

    printf("Example 4: Count Inversions\n");
    printf("Array: ");
    printArray(arr4, n4);

    int inversions = mergeSortAndCount(arr4, temp, 0, n4 - 1);

    printf("Number of inversions: %d\n", inversions);
    printf("Sorted array: ");
    printArray(arr4, n4);

    free(temp);
}

int main() {
    demonstrateMergeSort();
    return 0;
}
```

### Complexity Analysis

#### Time Complexity
| Case | Complexity | Explanation |
|------|------------|-------------|
| Best Case | O(n log n) | Always divides and merges |
| Average Case | O(n log n) | Same as worst |
| Worst Case | O(n log n) | Consistent performance |

**Derivation**:
```
Recurrence: T(n) = 2T(n/2) + O(n)

Using Master Theorem:
T(n) = 2T(n/2) + cn
     = 2(2T(n/4) + cn/2) + cn
     = 4T(n/4) + 2cn
     = 8T(n/8) + 3cn
     = ...
     = 2^k × T(n/2^k) + k × cn

When n/2^k = 1: k = log₂(n)

T(n) = n × T(1) + cn × log₂(n)
     = O(n log n)
```

#### Space Complexity
- **O(n)**: Requires temporary arrays for merging
- **O(log n)**: Recursion stack depth

### Characteristics
- **Stable**: Yes (preserves order of equal elements)
- **In-place**: No (requires O(n) extra space)
- **Adaptive**: No (always O(n log n))
- **Parallelizable**: Yes (independent subproblems)

### Advantages
1. Guaranteed O(n log n) performance
2. Stable sorting
3. Good for linked lists
4. Parallelizable
5. Predictable performance

### Disadvantages
1. O(n) extra space required
2. Not in-place
3. Slower for small arrays (overhead)
4. Not adaptive

### When to Use
- Large datasets
- Stability required
- Linked lists
- External sorting (disk-based)
- Parallel processing
- Guaranteed performance needed

---

## Quick Sort

**Quick Sort** is a divide-and-conquer algorithm that selects a 'pivot' element and partitions the array around it.

### Algorithm Explanation

**Steps**:
1. Choose pivot element
2. Partition array: elements smaller than pivot on left, larger on right
3. Recursively sort left and right partitions

### Partitioning Schemes

#### 1. Lomuto Partition Scheme
```c
Partition(arr, low, high):
    pivot = arr[high]
    i = low - 1
    for j = low to high-1:
        if arr[j] <= pivot:
            i++
            swap(arr[i], arr[j])
    swap(arr[i+1], arr[high])
    return i + 1
```

#### 2. Hoare Partition Scheme
```c
Partition(arr, low, high):
    pivot = arr[low]
    i = low - 1
    j = high + 1
    while true:
        do i++ while arr[i] < pivot
        do j-- while arr[j] > pivot
        if i >= j:
            return j
        swap(arr[i], arr[j])
```

### Visual Trace (Lomuto Partition)

**Example**: Sort [10, 7, 8, 9, 1, 5]

```
Initial Array: [10, 7, 8, 9, 1, 5]
Pivot = 5 (last element)

PARTITION PHASE:
i = -1 (start before array)
j scans from left to right

j=0: arr[0]=10, 10 > 5, no swap
[10, 7, 8, 9, 1, 5]
 i=-1  j

j=1: arr[1]=7, 7 > 5, no swap
[10, 7, 8, 9, 1, 5]
 i=-1     j

j=2: arr[2]=8, 8 > 5, no swap
[10, 7, 8, 9, 1, 5]
 i=-1        j

j=3: arr[3]=9, 9 > 5, no swap
[10, 7, 8, 9, 1, 5]
 i=-1           j

j=4: arr[4]=1, 1 ≤ 5, i++, swap arr[0] and arr[4]
[1, 7, 8, 9, 10, 5]
 i=0            j

After loop, swap pivot with arr[i+1]
[1, 5, 8, 9, 10, 7]
    ↑
  pivot in correct position

RECURSIVE CALLS:
Left partition: [1]  (already sorted)
Right partition: [8, 9, 10, 7]

Partition [8, 9, 10, 7], pivot = 7:
[7, 9, 10, 8]  → [7] | [9, 10, 8]
                     ↑

Partition [9, 10, 8], pivot = 8:
[8, 10, 9]  → [8] | [10, 9]
                  ↑

Partition [10, 9], pivot = 9:
[9, 10]  → [9] | [10]
               ↑

Final: [1, 5, 7, 8, 9, 10]
```

### C Implementation

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Utility functions
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Lomuto Partition Scheme
int partitionLomuto(int arr[], int low, int high) {
    int pivot = arr[high];  // Choose last element as pivot
    int i = low - 1;         // Index of smaller element

    for (int j = low; j < high; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Quick Sort using Lomuto partition
void quickSortLomuto(int arr[], int low, int high) {
    if (low < high) {
        // Partition array and get pivot index
        int pi = partitionLomuto(arr, low, high);

        // Recursively sort elements before and after partition
        quickSortLomuto(arr, low, pi - 1);
        quickSortLomuto(arr, pi + 1, high);
    }
}

// Hoare Partition Scheme
int partitionHoare(int arr[], int low, int high) {
    int pivot = arr[low];  // Choose first element as pivot
    int i = low - 1;
    int j = high + 1;

    while (1) {
        // Find leftmost element >= pivot
        do {
            i++;
        } while (arr[i] < pivot);

        // Find rightmost element <= pivot
        do {
            j--;
        } while (arr[j] > pivot);

        // If two pointers met
        if (i >= j) {
            return j;
        }

        swap(&arr[i], &arr[j]);
    }
}

// Quick Sort using Hoare partition
void quickSortHoare(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionHoare(arr, low, high);

        quickSortHoare(arr, low, pi);
        quickSortHoare(arr, pi + 1, high);
    }
}

// Quick Sort with detailed trace
void quickSortTrace(int arr[], int low, int high, int level) {
    if (low < high) {
        printf("%*sQuickSort [%d:%d]: ", level * 2, "", low, high);
        for (int i = low; i <= high; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        int pi = partitionLomuto(arr, low, high);

        printf("%*sAfter partition (pivot=%d at index %d): ",
               level * 2, "", arr[pi], pi);
        for (int i = low; i <= high; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n\n");

        quickSortTrace(arr, low, pi - 1, level + 1);
        quickSortTrace(arr, pi + 1, high, level + 1);
    }
}

// Randomized Quick Sort (better average case)
int partitionRandomized(int arr[], int low, int high) {
    // Generate random index between low and high
    int random = low + rand() % (high - low + 1);

    // Swap random element with last element
    swap(&arr[random], &arr[high]);

    // Use standard partition
    return partitionLomuto(arr, low, high);
}

void quickSortRandomized(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionRandomized(arr, low, high);

        quickSortRandomized(arr, low, pi - 1);
        quickSortRandomized(arr, pi + 1, high);
    }
}

// Three-Way Quick Sort (for arrays with many duplicates)
void quickSort3Way(int arr[], int low, int high) {
    if (low >= high) {
        return;
    }

    int pivot = arr[low];
    int lt = low;      // arr[low..lt-1] < pivot
    int gt = high;     // arr[gt+1..high] > pivot
    int i = low;       // arr[lt..i-1] == pivot

    while (i <= gt) {
        if (arr[i] < pivot) {
            swap(&arr[lt], &arr[i]);
            lt++;
            i++;
        } else if (arr[i] > pivot) {
            swap(&arr[i], &arr[gt]);
            gt--;
        } else {
            i++;
        }
    }

    quickSort3Way(arr, low, lt - 1);
    quickSort3Way(arr, gt + 1, high);
}

// Iterative Quick Sort
void quickSortIterative(int arr[], int low, int high) {
    // Create auxiliary stack
    int* stack = (int*)malloc((high - low + 1) * sizeof(int));
    int top = -1;

    // Push initial values
    stack[++top] = low;
    stack[++top] = high;

    while (top >= 0) {
        // Pop high and low
        high = stack[top--];
        low = stack[top--];

        // Set pivot element at correct position
        int pi = partitionLomuto(arr, low, high);

        // If there are elements on left of pivot, push left side
        if (pi - 1 > low) {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }

        // If there are elements on right of pivot, push right side
        if (pi + 1 < high) {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }
    }

    free(stack);
}

// Tail Call Optimization
void quickSortOptimized(int arr[], int low, int high) {
    while (low < high) {
        int pi = partitionLomuto(arr, low, high);

        // Recur for smaller partition
        if (pi - low < high - pi) {
            quickSortOptimized(arr, low, pi - 1);
            low = pi + 1;
        } else {
            quickSortOptimized(arr, pi + 1, high);
            high = pi - 1;
        }
    }
}

// Demonstration function
void demonstrateQuickSort() {
    printf("=== QUICK SORT DEMONSTRATION ===\n\n");
    srand(time(NULL));

    // Example 1: Basic quick sort (Lomuto)
    int arr1[] = {10, 7, 8, 9, 1, 5};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    printf("Example 1: Quick Sort (Lomuto Partition)\n");
    printf("Original: ");
    printArray(arr1, n1);

    quickSortLomuto(arr1, 0, n1 - 1);

    printf("Sorted:   ");
    printArray(arr1, n1);
    printf("\n");

    // Example 2: Hoare partition
    int arr2[] = {10, 7, 8, 9, 1, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    printf("Example 2: Quick Sort (Hoare Partition)\n");
    printf("Original: ");
    printArray(arr2, n2);

    quickSortHoare(arr2, 0, n2 - 1);

    printf("Sorted:   ");
    printArray(arr2, n2);
    printf("\n");

    // Example 3: Detailed trace
    int arr3[] = {5, 2, 9, 1, 7, 6};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    printf("Example 3: Detailed Trace\n");
    printf("Original: ");
    printArray(arr3, n3);
    printf("\n");

    quickSortTrace(arr3, 0, n3 - 1, 0);

    printf("Final sorted: ");
    printArray(arr3, n3);
    printf("\n");

    // Example 4: Randomized quick sort
    int arr4[] = {5, 2, 9, 1, 7, 6, 3};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);

    printf("Example 4: Randomized Quick Sort\n");
    printf("Original: ");
    printArray(arr4, n4);

    quickSortRandomized(arr4, 0, n4 - 1);

    printf("Sorted:   ");
    printArray(arr4, n4);
    printf("\n");

    // Example 5: Three-way quick sort (many duplicates)
    int arr5[] = {4, 9, 4, 4, 1, 9, 4, 4, 9, 4, 4, 1, 4};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);

    printf("Example 5: Three-Way Quick Sort (duplicates)\n");
    printf("Original: ");
    printArray(arr5, n5);

    quickSort3Way(arr5, 0, n5 - 1);

    printf("Sorted:   ");
    printArray(arr5, n5);
    printf("\n");

    // Example 6: Iterative quick sort
    int arr6[] = {64, 34, 25, 12, 22, 11, 90};
    int n6 = sizeof(arr6) / sizeof(arr6[0]);

    printf("Example 6: Iterative Quick Sort\n");
    printf("Original: ");
    printArray(arr6, n6);

    quickSortIterative(arr6, 0, n6 - 1);

    printf("Sorted:   ");
    printArray(arr6, n6);
}

int main() {
    demonstrateQuickSort();
    return 0;
}
```

### Complexity Analysis

#### Time Complexity
| Case | Complexity | Explanation |
|------|------------|-------------|
| Best Case | O(n log n) | Pivot divides array evenly |
| Average Case | O(n log n) | Expected case |
| Worst Case | O(n²) | Already sorted, bad pivot choice |

**Worst Case**:
```
T(n) = T(n-1) + O(n)
     = T(n-2) + O(n-1) + O(n)
     = O(1) + O(2) + ... + O(n)
     = O(n²)
```

**Average Case**:
```
T(n) = 2T(n/2) + O(n) = O(n log n)
```

#### Space Complexity
- **Average**: O(log n) - recursion stack
- **Worst**: O(n) - unbalanced partitions

### Characteristics
- **Stable**: No (may change order of equal elements)
- **In-place**: Yes (with O(log n) stack space)
- **Adaptive**: No
- **Cache-friendly**: Yes (good locality of reference)

### Advantages
1. Fast average case: O(n log n)
2. In-place sorting
3. Cache-friendly
4. Good for large datasets
5. Tail recursion optimizable

### Disadvantages
1. O(n²) worst case
2. Not stable
3. Requires good pivot selection
4. Recursion overhead

### When to Use
- Large datasets
- Average case performance important
- In-place sorting needed
- Cache performance matters
- Stability not required

---

## Heap Sort

**Heap Sort** uses a binary heap data structure to sort elements. It builds a max heap and repeatedly extracts the maximum.

### Algorithm Explanation

**Steps**:
1. Build a max heap from input array
2. Swap root (maximum) with last element
3. Reduce heap size by 1
4. Heapify root
5. Repeat steps 2-4 until heap size is 1

### Binary Heap Properties
```
Max Heap: Parent ≥ Children
Min Heap: Parent ≤ Children

Array representation:
Parent of i: (i-1)/2
Left child of i: 2i + 1
Right child of i: 2i + 2
```

### Visual Trace

**Example**: Sort [4, 10, 3, 5, 1]

```
STEP 1: BUILD MAX HEAP

Initial Array: [4, 10, 3, 5, 1]

Array as tree:
        4
       / \
      10  3
     / \
    5   1

Heapify from (n/2 - 1) to 0:

Heapify index 1 (element 10):
        4
       / \
     [10] 3
     / \
    5   1
10 > max(5, 1), no change

Heapify index 0 (element 4):
       [4]
       / \
      10  3
     / \
    5   1
10 > 4, swap
       10
       / \
     [4]  3
     / \
    5   1
5 > 4, swap
       10
       / \
      5   3
     / \
   [4]  1

Max Heap: [10, 5, 3, 4, 1]
          10
         / \
        5   3
       / \
      4   1


STEP 2: EXTRACT MAX AND HEAPIFY

Iteration 1:
Swap root with last element
[1, 5, 3, 4, | 10]
Heapify root:
       [1]
       / \
      5   3
     /
    4
5 > 1, swap
        5
       / \
     [1]  3
     /
    4
4 > 1, swap
        5
       / \
      4   3
     /
   [1]
Result: [5, 4, 3, 1, | 10]

Iteration 2:
[1, 4, 3, | 5, 10]
Heapify:
        4
       / \
      1   3
Result: [4, 1, 3, | 5, 10]

Iteration 3:
[3, 1, | 4, 5, 10]
Heapify:
        3
       /
      1
Result: [3, 1, | 4, 5, 10]

Iteration 4:
[1, | 3, 4, 5, 10]
No heapify needed

Final Sorted Array: [1, 3, 4, 5, 10]
```

### C Implementation

```c
#include <stdio.h>

// Utility function
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Heapify a subtree rooted at index i
// n is size of heap
void heapify(int arr[], int n, int i) {
    int largest = i;           // Initialize largest as root
    int left = 2 * i + 1;      // Left child
    int right = 2 * i + 2;     // Right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If largest is not root
    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        // Recursively heapify the affected subtree
        heapify(arr, n, largest);
    }
}

// Build max heap
void buildMaxHeap(int arr[], int n) {
    // Start from last non-leaf node and heapify
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// Heap Sort
void heapSort(int arr[], int n) {
    // Build max heap
    buildMaxHeap(arr, n);

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(&arr[0], &arr[i]);

        // Heapify the reduced heap
        heapify(arr, i, 0);
    }
}

// Heap Sort with detailed trace
void heapSortTrace(int arr[], int n) {
    printf("Initial array: ");
    printArray(arr, n);
    printf("\n");

    // Build max heap
    printf("BUILDING MAX HEAP:\n");
    for (int i = n / 2 - 1; i >= 0; i--) {
        printf("  Heapify index %d (value %d)\n", i, arr[i]);
        heapify(arr, n, i);
        printf("  Array: ");
        printArray(arr, n);
    }

    printf("\nMax Heap built: ");
    printArray(arr, n);
    printf("\n");

    // Extract elements
    printf("EXTRACTING ELEMENTS:\n");
    for (int i = n - 1; i > 0; i--) {
        printf("  Iteration %d:\n", n - i);
        printf("    Swap root %d with last element %d\n", arr[0], arr[i]);

        swap(&arr[0], &arr[i]);

        printf("    Array: ");
        for (int j = 0; j < n; j++) {
            if (j == i) printf("| ");
            printf("%d ", arr[j]);
        }
        printf("\n");

        printf("    Heapify root\n");
        heapify(arr, i, 0);

        printf("    Array: ");
        for (int j = 0; j < n; j++) {
            if (j == i) printf("| ");
            printf("%d ", arr[j]);
        }
        printf("\n\n");
    }

    printf("Final sorted array: ");
    printArray(arr, n);
}

// Iterative heapify
void heapifyIterative(int arr[], int n, int i) {
    while (1) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest == i) {
            break;
        }

        swap(&arr[i], &arr[largest]);
        i = largest;
    }
}

// Heap Sort (iterative heapify)
void heapSortIterative(int arr[], int n) {
    // Build heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyIterative(arr, n, i);
    }

    // Extract elements
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapifyIterative(arr, i, 0);
    }
}

// Print heap as tree (limited to small heaps)
void printHeapTree(int arr[], int n, int i, int level) {
    if (i < n) {
        printHeapTree(arr, n, 2 * i + 2, level + 1);

        for (int j = 0; j < level; j++) {
            printf("    ");
        }
        printf("%d\n", arr[i]);

        printHeapTree(arr, n, 2 * i + 1, level + 1);
    }
}

// Demonstration function
void demonstrateHeapSort() {
    printf("=== HEAP SORT DEMONSTRATION ===\n\n");

    // Example 1: Basic heap sort
    int arr1[] = {4, 10, 3, 5, 1};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    printf("Example 1: Basic Heap Sort\n");
    printf("Original: ");
    printArray(arr1, n1);

    heapSort(arr1, n1);

    printf("Sorted:   ");
    printArray(arr1, n1);
    printf("\n");

    // Example 2: Detailed trace
    int arr2[] = {12, 11, 13, 5, 6, 7};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    printf("Example 2: Detailed Trace\n");
    heapSortTrace(arr2, n2);
    printf("\n");

    // Example 3: Visualize heap
    int arr3[] = {9, 5, 6, 2, 3};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    printf("Example 3: Heap Visualization\n");
    printf("Array: ");
    printArray(arr3, n3);

    buildMaxHeap(arr3, n3);

    printf("\nMax Heap:\n");
    printHeapTree(arr3, n3, 0, 0);

    printf("\nSorting...\n");
    heapSort(arr3, n3);

    printf("Sorted: ");
    printArray(arr3, n3);
    printf("\n");

    // Example 4: Large array
    int arr4[] = {64, 34, 25, 12, 22, 11, 90, 88, 45, 50};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);

    printf("Example 4: Larger Array\n");
    printf("Original: ");
    printArray(arr4, n4);

    heapSortIterative(arr4, n4);

    printf("Sorted:   ");
    printArray(arr4, n4);
}

int main() {
    demonstrateHeapSort();
    return 0;
}
```

### Complexity Analysis

#### Time Complexity
| Case | Complexity | Explanation |
|------|------------|-------------|
| Best Case | O(n log n) | Build heap + extract |
| Average Case | O(n log n) | Same as worst |
| Worst Case | O(n log n) | Guaranteed performance |

**Derivation**:
```
Build Heap: O(n)
Extract Max (n times): n × O(log n) = O(n log n)
Total: O(n) + O(n log n) = O(n log n)
```

#### Space Complexity
- **O(1)**: In-place sorting (no extra array needed)

### Characteristics
- **Stable**: No
- **In-place**: Yes
- **Adaptive**: No
- **Cache-friendly**: No (random memory access)

### Advantages
1. Guaranteed O(n log n)
2. In-place sorting
3. No worst case like quick sort
4. Simple to implement
5. No stack overflow (iterative)

### Disadvantages
1. Not stable
2. Poor cache performance
3. Slower than quick sort in practice
4. Not adaptive

### When to Use
- Guaranteed O(n log n) required
- Limited memory
- Real-time systems
- Embedded systems
- When stability not required

---

## Comparison of Advanced Sorting Algorithms

### Performance Comparison

| Algorithm | Best | Average | Worst | Space | Stable | In-place | Cache |
|-----------|------|---------|-------|-------|--------|----------|-------|
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes | No | Good |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | No | Yes | Excellent |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) | No | Yes | Poor |

### Detailed Comparison

| Feature | Merge Sort | Quick Sort | Heap Sort |
|---------|------------|------------|-----------|
| Worst case | Always O(n log n) | O(n²) (rare) | Always O(n log n) |
| Extra space | O(n) | O(log n) | O(1) |
| Stability | Stable | Unstable | Unstable |
| Parallelizable | Yes | Yes | No |
| Practical speed | Moderate | Fastest | Moderate |
| Linked lists | Excellent | Poor | Poor |

### Choosing the Right Algorithm

1. **Use Merge Sort when**:
   - Stability required
   - Linked lists
   - External sorting
   - Guaranteed performance
   - Parallel processing

2. **Use Quick Sort when**:
   - Speed is critical
   - Average case performance matters
   - In-place sorting needed
   - Cache performance important
   - Arrays (not linked lists)

3. **Use Heap Sort when**:
   - Limited memory
   - Guaranteed O(n log n) required
   - No recursion allowed
   - Real-time systems
   - Partial sorting needed (top-k elements)

---

## Practice Problems

### Problem 1: Inversion Count
Count number of inversions in array using merge sort.

### Problem 2: K Closest Points
Find k closest points to origin using modified heap sort.

### Problem 3: Quick Select
Implement quick select algorithm to find kth smallest element.

### Problem 4: External Sorting
Design algorithm to sort file larger than RAM using merge sort.

### Problem 5: Hybrid Sort
Implement Introsort (quick sort + heap sort + insertion sort).

### Problem 6: Median of Two Sorted Arrays
Find median of two sorted arrays in O(log n).

### Problem 7: Nuts and Bolts Problem
Match nuts and bolts using modified quick sort.

### Problem 8: Sort Nearly Sorted Array
Sort array where each element is at most k positions away using heap.

### Problem 9: Merge K Sorted Arrays
Merge k sorted arrays using heap efficiently.

### Problem 10: Pancake Sorting
Sort array using only flip operation (variation of selection sort).

---

## Summary

### Key Characteristics

| Algorithm | When to Use |
|-----------|-------------|
| **Merge Sort** | Stability, linked lists, external sorting |
| **Quick Sort** | Speed, in-place, cache performance |
| **Heap Sort** | Guaranteed O(n log n), limited memory |

### Real-World Usage
- **Java**: Merge Sort (for objects - stability)
- **C++ STL**: Introsort (quick + heap + insertion)
- **Python**: Timsort (merge + insertion)
- **Linux Kernel**: Heap Sort (limited stack)

### Performance Tips
1. Use insertion sort for small subarrays (n < 10-50)
2. Use randomized pivot for quick sort
3. Use three-way partitioning for duplicates
4. Consider cache locality
5. Profile before optimizing

---

**Next Topic**: Recursion and Divide-and-Conquer
