# Basic Sorting Algorithms

## Table of Contents
1. [Introduction to Sorting](#introduction)
2. [Bubble Sort](#bubble-sort)
3. [Selection Sort](#selection-sort)
4. [Insertion Sort](#insertion-sort)
5. [Comparison of Basic Sorting](#comparison)
6. [Practice Problems](#practice-problems)

---

## Introduction to Sorting

**Sorting** is the process of arranging elements in a specific order (ascending or descending).

### Why Sorting?
1. **Searching**: Binary search requires sorted data
2. **Data Organization**: Easier to find and analyze
3. **Optimization**: Many algorithms work better on sorted data
4. **Database Operations**: Efficient indexing and queries

### Classification of Sorting Algorithms

#### By Complexity
- **Simple Sorts**: O(n²) - Bubble, Selection, Insertion
- **Efficient Sorts**: O(n log n) - Merge, Quick, Heap

#### By Memory Usage
- **In-place**: O(1) extra space - Bubble, Selection, Insertion
- **Out-of-place**: O(n) extra space - Merge Sort

#### By Stability
- **Stable**: Maintains relative order of equal elements - Bubble, Insertion, Merge
- **Unstable**: May change relative order - Selection, Quick, Heap

#### By Method
- **Comparison-based**: Compare elements - All covered here
- **Non-comparison**: Counting, Radix, Bucket Sort

---

## Bubble Sort

**Bubble Sort** repeatedly steps through the list, compares adjacent elements, and swaps them if they're in the wrong order. Larger elements "bubble" to the end.

### Algorithm Explanation

**Steps**:
1. Compare adjacent elements
2. Swap if they're in wrong order
3. Repeat for all pairs
4. After each pass, largest element reaches its position
5. Repeat n-1 passes

### Pseudocode
```
BubbleSort(array, n):
    for i = 0 to n-2:
        for j = 0 to n-i-2:
            if array[j] > array[j+1]:
                swap(array[j], array[j+1])
```

### Visual Trace

**Example**: Sort [64, 34, 25, 12, 22, 11, 90]

```
Initial Array: [64, 34, 25, 12, 22, 11, 90]

Pass 1:
[64, 34, 25, 12, 22, 11, 90]  Compare 64 & 34, swap
[34, 64, 25, 12, 22, 11, 90]  Compare 64 & 25, swap
[34, 25, 64, 12, 22, 11, 90]  Compare 64 & 12, swap
[34, 25, 12, 64, 22, 11, 90]  Compare 64 & 22, swap
[34, 25, 12, 22, 64, 11, 90]  Compare 64 & 11, swap
[34, 25, 12, 22, 11, 64, 90]  Compare 64 & 90, no swap
[34, 25, 12, 22, 11, 64, 90]  Largest element (90) in position

Pass 2:
[34, 25, 12, 22, 11, 64, 90]  Compare 34 & 25, swap
[25, 34, 12, 22, 11, 64, 90]  Compare 34 & 12, swap
[25, 12, 34, 22, 11, 64, 90]  Compare 34 & 22, swap
[25, 12, 22, 34, 11, 64, 90]  Compare 34 & 11, swap
[25, 12, 22, 11, 34, 64, 90]  Compare 34 & 64, no swap
[25, 12, 22, 11, 34, 64, 90]  Second largest (64) in position

Pass 3:
[25, 12, 22, 11, 34, 64, 90]  Compare 25 & 12, swap
[12, 25, 22, 11, 34, 64, 90]  Compare 25 & 22, swap
[12, 22, 25, 11, 34, 64, 90]  Compare 25 & 11, swap
[12, 22, 11, 25, 34, 64, 90]  Compare 25 & 34, no swap

Pass 4:
[12, 22, 11, 25, 34, 64, 90]  Compare 12 & 22, no swap
[12, 22, 11, 25, 34, 64, 90]  Compare 22 & 11, swap
[12, 11, 22, 25, 34, 64, 90]  Compare 22 & 25, no swap

Pass 5:
[12, 11, 22, 25, 34, 64, 90]  Compare 12 & 11, swap
[11, 12, 22, 25, 34, 64, 90]  Compare 12 & 22, no swap

Pass 6:
[11, 12, 22, 25, 34, 64, 90]  Compare 11 & 12, no swap

Final Sorted Array: [11, 12, 22, 25, 34, 64, 90]
```

### C Implementation

```c
#include <stdio.h>
#include <stdbool.h>

// Utility function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Print array helper function
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Basic Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // Last i elements are already in place
        for (int j = 0; j < n - i - 1; j++) {
            // Swap if element is greater than next
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Optimized Bubble Sort (stops if no swaps occur)
void bubbleSortOptimized(int arr[], int n) {
    bool swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        // If no swaps occurred, array is sorted
        if (!swapped) {
            break;
        }
    }
}

// Bubble Sort with detailed trace
void bubbleSortTrace(int arr[], int n) {
    printf("Initial array: ");
    printArray(arr, n);
    printf("\n");

    for (int i = 0; i < n - 1; i++) {
        printf("Pass %d:\n", i + 1);
        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            printf("  Compare %d and %d", arr[j], arr[j + 1]);

            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                printf(" -> Swap\n");
                swapped = true;
            } else {
                printf(" -> No swap\n");
            }

            printf("    Array: ");
            printArray(arr, n);
        }

        printf("  After pass %d: ", i + 1);
        printArray(arr, n);
        printf("\n");

        if (!swapped) {
            printf("No swaps made. Array is sorted!\n");
            break;
        }
    }

    printf("Final sorted array: ");
    printArray(arr, n);
}

// Bubble Sort with comparison and swap counters
void bubbleSortWithStats(int arr[], int n) {
    int comparisons = 0;
    int swaps = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swaps++;
            }
        }
    }

    printf("Statistics:\n");
    printf("  Comparisons: %d\n", comparisons);
    printf("  Swaps: %d\n", swaps);
}

// Demonstration function
void demonstrateBubbleSort() {
    printf("=== BUBBLE SORT DEMONSTRATION ===\n\n");

    // Example 1: Basic sort
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    printf("Example 1: Basic Bubble Sort\n");
    printf("Original: ");
    printArray(arr1, n1);

    bubbleSort(arr1, n1);

    printf("Sorted:   ");
    printArray(arr1, n1);
    printf("\n");

    // Example 2: Detailed trace
    int arr2[] = {5, 1, 4, 2, 8};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    printf("Example 2: Detailed Trace\n");
    bubbleSortTrace(arr2, n2);
    printf("\n");

    // Example 3: Already sorted (best case)
    int arr3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    printf("Example 3: Already Sorted Array\n");
    printf("Original: ");
    printArray(arr3, n3);

    bubbleSortOptimized(arr3, n3);

    printf("Sorted:   ");
    printArray(arr3, n3);
    printf("\n");

    // Example 4: Statistics
    int arr4[] = {64, 34, 25, 12, 22};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);

    printf("Example 4: Sorting Statistics\n");
    printf("Array: ");
    printArray(arr4, n4);

    bubbleSortWithStats(arr4, n4);
    printf("Sorted: ");
    printArray(arr4, n4);
}

int main() {
    demonstrateBubbleSort();
    return 0;
}
```

### Complexity Analysis

#### Time Complexity
| Case | Complexity | Explanation |
|------|------------|-------------|
| Best Case | O(n) | Already sorted (with optimization) |
| Average Case | O(n²) | Random order |
| Worst Case | O(n²) | Reverse sorted |

**Derivation**:
```
Pass 1: (n-1) comparisons
Pass 2: (n-2) comparisons
Pass 3: (n-3) comparisons
...
Pass n-1: 1 comparison

Total = (n-1) + (n-2) + ... + 1
      = n(n-1)/2
      = O(n²)
```

#### Space Complexity
- **O(1)**: In-place sorting, only uses constant extra space

### Characteristics
- **Stable**: Yes (equal elements maintain order)
- **In-place**: Yes
- **Adaptive**: Yes (with optimization, O(n) for sorted data)
- **Online**: No

### Advantages
1. Simple to understand and implement
2. No extra memory required
3. Stable sorting
4. Detects sorted array quickly (optimized version)

### Disadvantages
1. Very slow for large datasets: O(n²)
2. Not practical for real-world applications
3. Many unnecessary comparisons

### When to Use
- Teaching/learning purposes
- Small datasets (n < 10)
- Nearly sorted data (with optimization)
- Simplicity is priority over efficiency

---

## Selection Sort

**Selection Sort** divides the array into sorted and unsorted regions. It repeatedly selects the minimum element from unsorted region and moves it to sorted region.

### Algorithm Explanation

**Steps**:
1. Find minimum element in unsorted portion
2. Swap with first unsorted element
3. Move boundary between sorted/unsorted
4. Repeat until array is sorted

### Pseudocode
```
SelectionSort(array, n):
    for i = 0 to n-2:
        min_index = i
        for j = i+1 to n-1:
            if array[j] < array[min_index]:
                min_index = j
        swap(array[i], array[min_index])
```

### Visual Trace

**Example**: Sort [64, 25, 12, 22, 11]

```
Initial Array: [64, 25, 12, 22, 11]
                ↑ sorted | unsorted →

Pass 1: Find minimum in [64, 25, 12, 22, 11]
        Minimum = 11 at index 4
        Swap 64 and 11
[11, 25, 12, 22, 64]
 ↑ sorted | unsorted →

Pass 2: Find minimum in [25, 12, 22, 64]
        Minimum = 12 at index 2
        Swap 25 and 12
[11, 12, 25, 22, 64]
 ↑   ↑ sorted | unsorted →

Pass 3: Find minimum in [25, 22, 64]
        Minimum = 22 at index 3
        Swap 25 and 22
[11, 12, 22, 25, 64]
 ↑   ↑   ↑ sorted | unsorted →

Pass 4: Find minimum in [25, 64]
        Minimum = 25 at index 3
        No swap needed
[11, 12, 22, 25, 64]
 ↑   ↑   ↑   ↑ sorted | unsorted →

Final Sorted Array: [11, 12, 22, 25, 64]
```

### C Implementation

```c
#include <stdio.h>

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

// Basic Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // Find minimum element in unsorted portion
        int min_index = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        // Swap minimum with first unsorted element
        if (min_index != i) {
            swap(&arr[i], &arr[min_index]);
        }
    }
}

// Selection Sort with detailed trace
void selectionSortTrace(int arr[], int n) {
    printf("Initial array: ");
    printArray(arr, n);
    printf("\n");

    for (int i = 0; i < n - 1; i++) {
        printf("Pass %d:\n", i + 1);
        int min_index = i;

        printf("  Searching minimum in unsorted portion: ");
        for (int k = i; k < n; k++) {
            printf("%d ", arr[k]);
        }
        printf("\n");

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        printf("  Minimum found: %d at index %d\n", arr[min_index], min_index);

        if (min_index != i) {
            printf("  Swap %d and %d\n", arr[i], arr[min_index]);
            swap(&arr[i], &arr[min_index]);
        } else {
            printf("  No swap needed\n");
        }

        printf("  Array after pass %d: ", i + 1);
        printArray(arr, n);

        // Show sorted/unsorted boundary
        printf("  Sorted portion: ");
        for (int k = 0; k <= i; k++) {
            printf("%d ", arr[k]);
        }
        printf("| Unsorted: ");
        for (int k = i + 1; k < n; k++) {
            printf("%d ", arr[k]);
        }
        printf("\n\n");
    }

    printf("Final sorted array: ");
    printArray(arr, n);
}

// Selection Sort with statistics
void selectionSortWithStats(int arr[], int n) {
    int comparisons = 0;
    int swaps = 0;

    for (int i = 0; i < n - 1; i++) {
        int min_index = i;

        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        if (min_index != i) {
            swap(&arr[i], &arr[min_index]);
            swaps++;
        }
    }

    printf("Statistics:\n");
    printf("  Comparisons: %d\n", comparisons);
    printf("  Swaps: %d\n", swaps);
}

// Bidirectional Selection Sort (cocktail selection sort)
void bidirectionalSelectionSort(int arr[], int n) {
    for (int i = 0; i < n / 2; i++) {
        // Find minimum in unsorted portion
        int min_index = i;
        int max_index = i;

        for (int j = i; j < n - i; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
            if (arr[j] > arr[max_index]) {
                max_index = j;
            }
        }

        // Place minimum at start
        swap(&arr[i], &arr[min_index]);

        // If max was at position i, it's now at min_index
        if (max_index == i) {
            max_index = min_index;
        }

        // Place maximum at end
        swap(&arr[n - 1 - i], &arr[max_index]);
    }
}

// Demonstration function
void demonstrateSelectionSort() {
    printf("=== SELECTION SORT DEMONSTRATION ===\n\n");

    // Example 1: Basic sort
    int arr1[] = {64, 25, 12, 22, 11};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    printf("Example 1: Basic Selection Sort\n");
    printf("Original: ");
    printArray(arr1, n1);

    selectionSort(arr1, n1);

    printf("Sorted:   ");
    printArray(arr1, n1);
    printf("\n");

    // Example 2: Detailed trace
    int arr2[] = {29, 10, 14, 37, 13};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    printf("Example 2: Detailed Trace\n");
    selectionSortTrace(arr2, n2);
    printf("\n");

    // Example 3: Statistics
    int arr3[] = {64, 25, 12, 22, 11};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    printf("Example 3: Sorting Statistics\n");
    printf("Array: ");
    printArray(arr3, n3);

    selectionSortWithStats(arr3, n3);
    printf("Sorted: ");
    printArray(arr3, n3);
    printf("\n");

    // Example 4: Bidirectional
    int arr4[] = {5, 2, 8, 1, 9, 3};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);

    printf("Example 4: Bidirectional Selection Sort\n");
    printf("Original: ");
    printArray(arr4, n4);

    bidirectionalSelectionSort(arr4, n4);

    printf("Sorted:   ");
    printArray(arr4, n4);
}

int main() {
    demonstrateSelectionSort();
    return 0;
}
```

### Complexity Analysis

#### Time Complexity
| Case | Complexity | Explanation |
|------|------------|-------------|
| Best Case | O(n²) | Same as worst (always scans all) |
| Average Case | O(n²) | Random order |
| Worst Case | O(n²) | Any order |

**Derivation**:
```
Pass 1: (n-1) comparisons
Pass 2: (n-2) comparisons
...
Pass n-1: 1 comparison

Total = (n-1) + (n-2) + ... + 1 = n(n-1)/2 = O(n²)
```

#### Space Complexity
- **O(1)**: In-place sorting

### Characteristics
- **Stable**: No (may change order of equal elements)
- **In-place**: Yes
- **Adaptive**: No (always O(n²))
- **Comparisons**: Always n(n-1)/2
- **Swaps**: At most n-1 (minimum among O(n²) algorithms)

### Advantages
1. Simple to understand
2. Performs well on small lists
3. Minimum number of swaps: O(n)
4. In-place sorting

### Disadvantages
1. O(n²) in all cases
2. Not stable
3. Not adaptive (doesn't benefit from partially sorted data)
4. Poor performance on large lists

### When to Use
- Small datasets
- When swap operation is expensive
- When minimum swaps required
- Memory is limited

---

## Insertion Sort

**Insertion Sort** builds the final sorted array one item at a time, inserting each element into its correct position in the sorted portion.

### Algorithm Explanation

**Steps**:
1. Start with second element (first is trivially sorted)
2. Compare with elements in sorted portion
3. Shift larger elements one position right
4. Insert element at correct position
5. Repeat for all elements

### Pseudocode
```
InsertionSort(array, n):
    for i = 1 to n-1:
        key = array[i]
        j = i - 1
        while j >= 0 AND array[j] > key:
            array[j+1] = array[j]
            j = j - 1
        array[j+1] = key
```

### Visual Trace

**Example**: Sort [12, 11, 13, 5, 6]

```
Initial Array: [12, 11, 13, 5, 6]
                ↑ sorted | unsorted →

Pass 1: Insert 11
[12, 11, 13, 5, 6]
 ↑   ↑
Compare 11 with 12, 11 < 12, shift 12 right
[12, 12, 13, 5, 6]
Insert 11 at position 0
[11, 12, 13, 5, 6]

Pass 2: Insert 13
[11, 12, 13, 5, 6]
 ↑   ↑   ↑
13 > 12, no shift needed
[11, 12, 13, 5, 6]

Pass 3: Insert 5
[11, 12, 13, 5, 6]
 ↑   ↑   ↑   ↑
Compare 5 with 13, shift 13
[11, 12, 13, 13, 6]
Compare 5 with 12, shift 12
[11, 12, 12, 13, 6]
Compare 5 with 11, shift 11
[11, 11, 12, 13, 6]
Insert 5 at position 0
[5, 11, 12, 13, 6]

Pass 4: Insert 6
[5, 11, 12, 13, 6]
 ↑  ↑   ↑   ↑   ↑
Compare 6 with 13, shift 13
[5, 11, 12, 13, 13]
Compare 6 with 12, shift 12
[5, 11, 12, 12, 13]
Compare 6 with 11, shift 11
[5, 11, 11, 12, 13]
Compare 6 with 5, stop
Insert 6 at position 1
[5, 6, 11, 12, 13]

Final Sorted Array: [5, 6, 11, 12, 13]
```

### C Implementation

```c
#include <stdio.h>

// Utility function
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Basic Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Move elements greater than key one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        // Insert key at correct position
        arr[j + 1] = key;
    }
}

// Insertion Sort with detailed trace
void insertionSortTrace(int arr[], int n) {
    printf("Initial array: ");
    printArray(arr, n);
    printf("\n");

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        printf("Pass %d: Insert %d\n", i, key);
        printf("  Current array: ");
        printArray(arr, n);

        int shifts = 0;
        printf("  Comparing with sorted portion:\n");

        while (j >= 0 && arr[j] > key) {
            printf("    %d > %d, shift %d right\n", arr[j], key, arr[j]);
            arr[j + 1] = arr[j];
            j--;
            shifts++;
        }

        arr[j + 1] = key;

        if (shifts == 0) {
            printf("    %d is in correct position\n", key);
        } else {
            printf("    Insert %d at position %d\n", key, j + 1);
        }

        printf("  After pass %d: ", i);
        printArray(arr, n);
        printf("\n");
    }

    printf("Final sorted array: ");
    printArray(arr, n);
}

// Insertion Sort with statistics
void insertionSortWithStats(int arr[], int n) {
    int comparisons = 0;
    int shifts = 0;

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            comparisons++;
            arr[j + 1] = arr[j];
            j--;
            shifts++;
        }

        if (j >= 0) {
            comparisons++;
        }

        arr[j + 1] = key;
    }

    printf("Statistics:\n");
    printf("  Comparisons: %d\n", comparisons);
    printf("  Shifts: %d\n", shifts);
}

// Binary Insertion Sort (optimized search)
void binaryInsertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int left = 0;
        int right = i - 1;

        // Find position to insert using binary search
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] > key) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        // Shift elements
        for (int j = i - 1; j >= left; j--) {
            arr[j + 1] = arr[j];
        }

        // Insert key
        arr[left] = key;
    }
}

// Recursive Insertion Sort
void insertionSortRecursive(int arr[], int n) {
    // Base case
    if (n <= 1) {
        return;
    }

    // Sort first n-1 elements
    insertionSortRecursive(arr, n - 1);

    // Insert nth element at correct position
    int key = arr[n - 1];
    int j = n - 2;

    while (j >= 0 && arr[j] > key) {
        arr[j + 1] = arr[j];
        j--;
    }

    arr[j + 1] = key;
}

// Demonstration function
void demonstrateInsertionSort() {
    printf("=== INSERTION SORT DEMONSTRATION ===\n\n");

    // Example 1: Basic sort
    int arr1[] = {12, 11, 13, 5, 6};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    printf("Example 1: Basic Insertion Sort\n");
    printf("Original: ");
    printArray(arr1, n1);

    insertionSort(arr1, n1);

    printf("Sorted:   ");
    printArray(arr1, n1);
    printf("\n");

    // Example 2: Detailed trace
    int arr2[] = {8, 4, 2, 9, 3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    printf("Example 2: Detailed Trace\n");
    insertionSortTrace(arr2, n2);
    printf("\n");

    // Example 3: Statistics
    int arr3[] = {5, 2, 4, 6, 1, 3};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    printf("Example 3: Sorting Statistics\n");
    printf("Array: ");
    printArray(arr3, n3);

    insertionSortWithStats(arr3, n3);
    printf("Sorted: ");
    printArray(arr3, n3);
    printf("\n");

    // Example 4: Binary insertion sort
    int arr4[] = {37, 23, 0, 17, 12, 72, 31};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);

    printf("Example 4: Binary Insertion Sort\n");
    printf("Original: ");
    printArray(arr4, n4);

    binaryInsertionSort(arr4, n4);

    printf("Sorted:   ");
    printArray(arr4, n4);
    printf("\n");

    // Example 5: Recursive
    int arr5[] = {64, 25, 12, 22, 11};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);

    printf("Example 5: Recursive Insertion Sort\n");
    printf("Original: ");
    printArray(arr5, n5);

    insertionSortRecursive(arr5, n5);

    printf("Sorted:   ");
    printArray(arr5, n5);
}

int main() {
    demonstrateInsertionSort();
    return 0;
}
```

### Complexity Analysis

#### Time Complexity
| Case | Complexity | Explanation |
|------|------------|-------------|
| Best Case | O(n) | Already sorted (no shifts) |
| Average Case | O(n²) | Random order |
| Worst Case | O(n²) | Reverse sorted |

**Derivation**:
```
Worst case (reverse sorted):
Pass 1: 1 comparison
Pass 2: 2 comparisons
...
Pass n-1: n-1 comparisons

Total = 1 + 2 + ... + (n-1) = n(n-1)/2 = O(n²)
```

#### Space Complexity
- **O(1)**: In-place sorting
- **Recursive**: O(n) stack space

### Characteristics
- **Stable**: Yes
- **In-place**: Yes
- **Adaptive**: Yes (O(n) for nearly sorted)
- **Online**: Yes (can sort stream of data)

### Advantages
1. Simple implementation
2. Efficient for small datasets
3. Adaptive: O(n) for nearly sorted
4. Stable sorting
5. In-place sorting
6. Online algorithm

### Disadvantages
1. O(n²) for large random datasets
2. Not efficient for large datasets
3. Many shifts required

### When to Use
- Small datasets (n < 50)
- Nearly sorted data
- Online sorting (streaming data)
- When stability is required
- Hybrid sorting algorithms (used in Timsort)

---

## Comparison of Basic Sorting Algorithms

### Performance Comparison

| Algorithm | Best | Average | Worst | Space | Stable | Adaptive |
|-----------|------|---------|-------|-------|--------|----------|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | Yes | Yes |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) | No | No |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | Yes | Yes |

### Characteristics Comparison

| Feature | Bubble | Selection | Insertion |
|---------|--------|-----------|-----------|
| Comparisons (worst) | n(n-1)/2 | n(n-1)/2 | n(n-1)/2 |
| Swaps (worst) | n(n-1)/2 | n-1 | n(n-1)/2 |
| For nearly sorted | Good | Poor | Excellent |
| Implementation | Easy | Easy | Easy |
| Practical use | Rare | Rare | Small/nearly sorted |

### When to Use Which?

1. **Bubble Sort**:
   - Educational purposes
   - Detecting if array is sorted
   - Very small datasets

2. **Selection Sort**:
   - When swaps are expensive
   - Small datasets
   - When memory writes are costly

3. **Insertion Sort**:
   - Small datasets (n < 50)
   - Nearly sorted data
   - Online algorithms
   - Part of hybrid sorts (Timsort, Introsort)

---

## Practice Problems

### Problem 1: Sort by Frequency
Sort array elements by frequency. If two elements have same frequency, maintain original order.

### Problem 2: Sort 0s, 1s, and 2s
Sort an array containing only 0s, 1s, and 2s in O(n) time.

### Problem 3: Bubble Sort Variation
Implement cocktail shaker sort (bidirectional bubble sort).

### Problem 4: Selection Sort Variation
Modify selection sort to sort both minimum and maximum in each pass.

### Problem 5: Insertion Sort on Linked List
Implement insertion sort for a singly linked list.

### Problem 6: Count Inversions
Count number of inversions in array using insertion sort concept.

### Problem 7: Sort Nearly Sorted Array
Given array where each element is at most k positions away from target position, sort efficiently.

### Problem 8: Stable vs Unstable
Demonstrate why selection sort is unstable with example.

### Problem 9: Adaptive Analysis
Compare number of operations for bubble sort and insertion sort on nearly sorted data.

### Problem 10: Hybrid Sort
Create hybrid algorithm that uses insertion sort for small subarrays and switches to efficient algorithm for larger ones.

---

## Summary

### Key Takeaways

1. **Bubble Sort**: Simple but inefficient, good for teaching
2. **Selection Sort**: Minimum swaps, always O(n²)
3. **Insertion Sort**: Best for small/nearly sorted data, adaptive

### Practical Usage
- Modern systems rarely use these for large datasets
- Used in hybrid algorithms (Timsort uses insertion sort)
- Good for small subarrays in divide-and-conquer algorithms
- Educational value for understanding sorting concepts

### Next Steps
Learn efficient O(n log n) sorting algorithms:
- Merge Sort
- Quick Sort
- Heap Sort

---

**Next Topic**: Advanced Sorting Algorithms
