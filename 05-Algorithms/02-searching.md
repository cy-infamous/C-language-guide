# Searching Algorithms

## Table of Contents
1. [Introduction to Searching](#introduction)
2. [Linear Search](#linear-search)
3. [Binary Search](#binary-search)
4. [Interpolation Search](#interpolation-search)
5. [Jump Search](#jump-search)
6. [Exponential Search](#exponential-search)
7. [Comparison of Search Algorithms](#comparison)
8. [Practice Problems](#practice-problems)

---

## Introduction to Searching

Searching is the process of finding a particular element in a collection of elements.

### Types of Searching
1. **Sequential Searching**: Linear Search
2. **Interval Searching**: Binary Search, Interpolation Search, Jump Search
3. **Hash-based Searching**: Hash Tables (covered in Data Structures)

### Key Considerations
- Is the data sorted?
- How large is the dataset?
- How frequent are searches?
- Memory constraints?

---

## Linear Search

**Linear Search** (Sequential Search) checks every element sequentially until the target is found or all elements are checked.

### Algorithm Explanation

**Steps**:
1. Start from the first element
2. Compare current element with target
3. If match found, return index
4. Move to next element
5. Repeat until found or end of array

### Pseudocode
```
LinearSearch(array, n, key):
    for i = 0 to n-1:
        if array[i] == key:
            return i
    return -1
```

### Visual Trace

**Example**: Search for 7 in array [3, 1, 7, 9, 2]

```
Step 1: Compare with 3
[3, 1, 7, 9, 2]
 ↑
 Not match, continue

Step 2: Compare with 1
[3, 1, 7, 9, 2]
    ↑
    Not match, continue

Step 3: Compare with 7
[3, 1, 7, 9, 2]
       ↑
       Match found! Return index 2
```

### C Implementation

```c
#include <stdio.h>

// Linear Search Implementation
int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        // Compare each element with key
        if (arr[i] == key) {
            return i;  // Element found at index i
        }
    }
    return -1;  // Element not found
}

// Linear Search with comparison counter
int linearSearchWithCount(int arr[], int n, int key, int *comparisons) {
    *comparisons = 0;
    for (int i = 0; i < n; i++) {
        (*comparisons)++;
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}

// Optimized: Sentinel Linear Search
// Reduces number of conditions in loop
int sentinelLinearSearch(int arr[], int n, int key) {
    // Save last element
    int last = arr[n - 1];

    // Place key at end (sentinel)
    arr[n - 1] = key;

    int i = 0;
    // No need to check i < n in loop
    while (arr[i] != key) {
        i++;
    }

    // Restore last element
    arr[n - 1] = last;

    // Check if element was found or sentinel was hit
    if (i < n - 1 || arr[n - 1] == key) {
        return i;
    }
    return -1;
}

// Search all occurrences
void linearSearchAll(int arr[], int n, int key) {
    int found = 0;
    printf("Element %d found at indices: ", key);

    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            printf("%d ", i);
            found = 1;
        }
    }

    if (!found) {
        printf("Not found");
    }
    printf("\n");
}

// Demonstration function
void demonstrateLinearSearch() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 12};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 22;

    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Basic linear search
    int result = linearSearch(arr, n, key);
    if (result != -1) {
        printf("Element %d found at index %d\n", key, result);
    } else {
        printf("Element %d not found\n", key);
    }

    // With comparison count
    int comparisons;
    result = linearSearchWithCount(arr, n, key, &comparisons);
    printf("Number of comparisons: %d\n", comparisons);

    // Search all occurrences
    linearSearchAll(arr, n, 12);
}

int main() {
    demonstrateLinearSearch();
    return 0;
}
```

### Complexity Analysis

#### Time Complexity
| Case | Complexity | Explanation |
|------|------------|-------------|
| Best Case | O(1) | Element at first position |
| Average Case | O(n) | Element in middle |
| Worst Case | O(n) | Element at last position or not present |

**Detailed Analysis**:
- Best Case: 1 comparison
- Average Case: n/2 comparisons
- Worst Case: n comparisons

#### Space Complexity
- **O(1)**: Uses only a few extra variables

### Advantages
1. Simple to implement
2. Works on unsorted data
3. No preprocessing required
4. Works well for small datasets
5. Can search all occurrences easily

### Disadvantages
1. Slow for large datasets
2. Time complexity O(n)
3. Not efficient for repeated searches

### When to Use
- Small datasets (n < 100)
- Unsorted data
- Single search operation
- Simple implementation needed

---

## Binary Search

**Binary Search** is an efficient algorithm for searching in a **sorted** array by repeatedly dividing the search interval in half.

### Algorithm Explanation

**Prerequisites**: Array must be sorted

**Steps**:
1. Compare key with middle element
2. If key equals middle, return index
3. If key is less than middle, search left half
4. If key is greater than middle, search right half
5. Repeat until found or interval is empty

### Pseudocode
```
BinarySearch(array, n, key):
    left = 0
    right = n - 1

    while left <= right:
        mid = left + (right - left) / 2

        if array[mid] == key:
            return mid
        else if array[mid] < key:
            left = mid + 1
        else:
            right = mid - 1

    return -1
```

### Visual Trace

**Example**: Search for 23 in sorted array [2, 5, 8, 12, 16, 23, 38, 56, 72, 91]

```
Initial Array:
Index:  0   1   2   3   4   5   6   7   8   9
Value: [2,  5,  8, 12, 16, 23, 38, 56, 72, 91]
        ↑                                   ↑
       left                               right

Step 1: mid = (0 + 9) / 2 = 4
       [2,  5,  8, 12, 16, 23, 38, 56, 72, 91]
                        ↑
                       mid (16)
       16 < 23, search right half

Step 2: left = 5, right = 9, mid = (5 + 9) / 2 = 7
       [2,  5,  8, 12, 16, 23, 38, 56, 72, 91]
                            ↑           ↑
                          left         mid (56)
       56 > 23, search left half

Step 3: left = 5, right = 6, mid = (5 + 6) / 2 = 5
       [2,  5,  8, 12, 16, 23, 38, 56, 72, 91]
                            ↑
                          mid (23)
       23 == 23, Found at index 5!
```

### C Implementation

```c
#include <stdio.h>

// Iterative Binary Search
int binarySearch(int arr[], int n, int key) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        // Calculate middle index
        // Using left + (right - left) / 2 to avoid overflow
        int mid = left + (right - left) / 2;

        // Check if key is at mid
        if (arr[mid] == key) {
            return mid;
        }

        // If key is greater, ignore left half
        if (arr[mid] < key) {
            left = mid + 1;
        }
        // If key is smaller, ignore right half
        else {
            right = mid - 1;
        }
    }

    // Element not found
    return -1;
}

// Recursive Binary Search
int binarySearchRecursive(int arr[], int left, int right, int key) {
    // Base case: element not found
    if (left > right) {
        return -1;
    }

    int mid = left + (right - left) / 2;

    // Element found
    if (arr[mid] == key) {
        return mid;
    }

    // Search in left half
    if (arr[mid] > key) {
        return binarySearchRecursive(arr, left, mid - 1, key);
    }

    // Search in right half
    return binarySearchRecursive(arr, mid + 1, right, key);
}

// Binary Search with detailed trace
int binarySearchTrace(int arr[], int n, int key) {
    int left = 0;
    int right = n - 1;
    int step = 1;

    printf("\nBinary Search Trace for key %d:\n", key);
    printf("Initial array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    while (left <= right) {
        int mid = left + (right - left) / 2;

        printf("Step %d: left=%d, right=%d, mid=%d, arr[mid]=%d\n",
               step++, left, right, mid, arr[mid]);

        if (arr[mid] == key) {
            printf("Found at index %d!\n", mid);
            return mid;
        }

        if (arr[mid] < key) {
            printf("Key > arr[mid], search right half\n\n");
            left = mid + 1;
        } else {
            printf("Key < arr[mid], search left half\n\n");
            right = mid - 1;
        }
    }

    printf("Element not found\n");
    return -1;
}

// Find first occurrence in array with duplicates
int binarySearchFirst(int arr[], int n, int key) {
    int left = 0;
    int right = n - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key) {
            result = mid;
            // Continue searching in left half for first occurrence
            right = mid - 1;
        } else if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

// Find last occurrence in array with duplicates
int binarySearchLast(int arr[], int n, int key) {
    int left = 0;
    int right = n - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key) {
            result = mid;
            // Continue searching in right half for last occurrence
            left = mid + 1;
        } else if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

// Count occurrences of element
int countOccurrences(int arr[], int n, int key) {
    int first = binarySearchFirst(arr, n, key);
    if (first == -1) {
        return 0;
    }
    int last = binarySearchLast(arr, n, key);
    return last - first + 1;
}

// Demonstration function
void demonstrateBinarySearch() {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Sorted Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Iterative search
    int key = 23;
    int result = binarySearch(arr, n, key);
    printf("\nIterative Binary Search:\n");
    if (result != -1) {
        printf("Element %d found at index %d\n", key, result);
    } else {
        printf("Element %d not found\n", key);
    }

    // Recursive search
    result = binarySearchRecursive(arr, 0, n - 1, key);
    printf("\nRecursive Binary Search:\n");
    if (result != -1) {
        printf("Element %d found at index %d\n", key, result);
    }

    // Trace
    binarySearchTrace(arr, n, 72);

    // Test with duplicates
    int arr2[] = {1, 2, 2, 2, 3, 4, 5, 5, 5, 6};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    printf("\n\nArray with duplicates: ");
    for (int i = 0; i < n2; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");

    key = 5;
    int first = binarySearchFirst(arr2, n2, key);
    int last = binarySearchLast(arr2, n2, key);
    int count = countOccurrences(arr2, n2, key);

    printf("Element %d:\n", key);
    printf("  First occurrence: index %d\n", first);
    printf("  Last occurrence: index %d\n", last);
    printf("  Total count: %d\n", count);
}

int main() {
    demonstrateBinarySearch();
    return 0;
}
```

### Complexity Analysis

#### Time Complexity
| Case | Complexity | Explanation |
|------|------------|-------------|
| Best Case | O(1) | Element at middle position |
| Average Case | O(log n) | Halves search space each iteration |
| Worst Case | O(log n) | Element at end or not present |

**Derivation**:
```
After 1 iteration: n/2 elements remain
After 2 iterations: n/4 elements remain
After 3 iterations: n/8 elements remain
...
After k iterations: n/(2^k) elements remain

When n/(2^k) = 1:
n = 2^k
k = log₂(n)

Therefore: O(log n)
```

#### Space Complexity
- **Iterative**: O(1) - constant space
- **Recursive**: O(log n) - recursion stack depth

### Recurrence Relation
```
T(n) = T(n/2) + O(1)

Solving:
T(n) = T(n/2) + c
     = T(n/4) + c + c
     = T(n/8) + c + c + c
     = T(1) + c × log₂(n)
     = O(log n)
```

### Advantages
1. Very efficient: O(log n)
2. Fast for large datasets
3. Predictable performance

### Disadvantages
1. Requires sorted array
2. Random access required (arrays, not linked lists)
3. Preprocessing (sorting) required

### When to Use
- Large sorted datasets
- Multiple search operations
- Random access available

---

## Interpolation Search

**Interpolation Search** is an improved variant of binary search for **uniformly distributed sorted** data. It estimates the position of the target based on the value.

### Algorithm Explanation

**Key Idea**: Instead of always checking the middle, estimate the likely position based on value.

**Formula**:
```
pos = left + ((key - arr[left]) × (right - left)) / (arr[right] - arr[left])
```

### Pseudocode
```
InterpolationSearch(array, n, key):
    left = 0
    right = n - 1

    while left <= right AND key >= array[left] AND key <= array[right]:
        if left == right:
            if array[left] == key:
                return left
            return -1

        pos = left + ((key - array[left]) × (right - left)) /
                     (array[right] - array[left])

        if array[pos] == key:
            return pos
        if array[pos] < key:
            left = pos + 1
        else:
            right = pos - 1

    return -1
```

### Visual Trace

**Example**: Search for 44 in [10, 12, 13, 16, 18, 23, 24, 33, 44, 59, 88]

```
Step 1: Calculate position
left = 0, right = 10
pos = 0 + ((44 - 10) × (10 - 0)) / (88 - 10)
    = 0 + (34 × 10) / 78
    = 0 + 4.35 ≈ 4

[10, 12, 13, 16, 18, 23, 24, 33, 44, 59, 88]
                    ↑
                   pos=4, value=18
18 < 44, search right

Step 2:
left = 5, right = 10
pos = 5 + ((44 - 23) × (10 - 5)) / (88 - 23)
    = 5 + (21 × 5) / 65
    = 5 + 1.61 ≈ 6

[10, 12, 13, 16, 18, 23, 24, 33, 44, 59, 88]
                        ↑
                       pos=6, value=24
24 < 44, search right

Step 3:
left = 7, right = 10
pos = 7 + ((44 - 33) × (10 - 7)) / (88 - 33)
    = 7 + (11 × 3) / 55
    = 7 + 0.6 ≈ 8

[10, 12, 13, 16, 18, 23, 24, 33, 44, 59, 88]
                                ↑
                               pos=8, value=44
Found at index 8!
```

### C Implementation

```c
#include <stdio.h>

// Interpolation Search Implementation
int interpolationSearch(int arr[], int n, int key) {
    int left = 0;
    int right = n - 1;

    while (left <= right && key >= arr[left] && key <= arr[right]) {
        // If only one element left
        if (left == right) {
            if (arr[left] == key) {
                return left;
            }
            return -1;
        }

        // Calculate probe position using interpolation formula
        int pos = left + ((double)(key - arr[left]) * (right - left)) /
                        (arr[right] - arr[left]);

        // Element found
        if (arr[pos] == key) {
            return pos;
        }

        // If key is larger, search right portion
        if (arr[pos] < key) {
            left = pos + 1;
        }
        // If key is smaller, search left portion
        else {
            right = pos - 1;
        }
    }

    return -1;
}

// Interpolation Search with trace
int interpolationSearchTrace(int arr[], int n, int key) {
    int left = 0;
    int right = n - 1;
    int step = 1;

    printf("\nInterpolation Search Trace for key %d:\n", key);

    while (left <= right && key >= arr[left] && key <= arr[right]) {
        if (left == right) {
            if (arr[left] == key) {
                printf("Step %d: Found at index %d\n", step, left);
                return left;
            }
            break;
        }

        int pos = left + ((double)(key - arr[left]) * (right - left)) /
                        (arr[right] - arr[left]);

        printf("Step %d: left=%d, right=%d, pos=%d, arr[pos]=%d\n",
               step++, left, right, pos, arr[pos]);

        if (arr[pos] == key) {
            printf("Found at index %d!\n", pos);
            return pos;
        }

        if (arr[pos] < key) {
            printf("Key > arr[pos], search right\n\n");
            left = pos + 1;
        } else {
            printf("Key < arr[pos], search left\n\n");
            right = pos - 1;
        }
    }

    printf("Element not found\n");
    return -1;
}

// Demonstration function
void demonstrateInterpolationSearch() {
    // Uniformly distributed array (best case)
    int arr[] = {10, 12, 13, 16, 18, 23, 24, 33, 44, 59, 88};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Uniformly distributed array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int key = 44;
    interpolationSearchTrace(arr, n, key);

    // Compare with binary search
    printf("\n--- Comparison ---\n");
    printf("For uniformly distributed data:\n");
    printf("Interpolation Search: Fewer probes (better position estimation)\n");
    printf("Binary Search: More probes (always middle)\n");
}

int main() {
    demonstrateInterpolationSearch();
    return 0;
}
```

### Complexity Analysis

#### Time Complexity
| Distribution | Complexity |
|--------------|------------|
| Uniform | O(log log n) |
| Non-uniform | O(n) |

#### Space Complexity
- O(1) - constant space

### Advantages
1. Very fast for uniformly distributed data: O(log log n)
2. Adapts to data distribution
3. Outperforms binary search for uniform data

### Disadvantages
1. Requires sorted array
2. Poor performance for non-uniform data
3. More complex calculation
4. May access out-of-bounds if not careful

### When to Use
- Large uniformly distributed sorted data
- Data like phone directories, dictionaries
- Known data distribution

---

## Jump Search

**Jump Search** searches a sorted array by jumping ahead by fixed steps and then performing linear search in the block.

### Algorithm Explanation

**Steps**:
1. Jump ahead by √n steps
2. When arr[i] > key, perform linear search in previous block
3. Optimal jump size is √n

### C Implementation

```c
#include <stdio.h>
#include <math.h>

// Jump Search Implementation
int jumpSearch(int arr[], int n, int key) {
    // Calculate jump size
    int step = sqrt(n);
    int prev = 0;

    // Jump until arr[step] >= key
    while (arr[step] < key) {
        prev = step;
        step += sqrt(n);

        // If we've reached end
        if (prev >= n) {
            return -1;
        }
    }

    // Linear search in block
    while (arr[prev] < key) {
        prev++;

        // If reached next block or end
        if (prev == step || prev == n) {
            return -1;
        }
    }

    // Element found
    if (arr[prev] == key) {
        return prev;
    }

    return -1;
}

// Demonstration function
void demonstrateJumpSearch() {
    int arr[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int key = 55;
    int result = jumpSearch(arr, n, key);

    if (result != -1) {
        printf("Element %d found at index %d\n", key, result);
    } else {
        printf("Element not found\n");
    }
}

int main() {
    demonstrateJumpSearch();
    return 0;
}
```

### Complexity Analysis

#### Time Complexity
- **O(√n)**: Jump and linear search phases

#### Space Complexity
- O(1)

### When to Use
- Sorted array
- When backward traversal is costly
- Systems with high jump cost

---

## Exponential Search

**Exponential Search** finds a range where element may exist by doubling the index, then performs binary search.

### C Implementation

```c
#include <stdio.h>

// Forward declaration
int binarySearch(int arr[], int left, int right, int key);

// Exponential Search Implementation
int exponentialSearch(int arr[], int n, int key) {
    // If element at first position
    if (arr[0] == key) {
        return 0;
    }

    // Find range for binary search by repeated doubling
    int i = 1;
    while (i < n && arr[i] <= key) {
        i = i * 2;
    }

    // Perform binary search in found range
    return binarySearch(arr, i / 2, (i < n) ? i : n - 1, key);
}

// Binary search helper
int binarySearch(int arr[], int left, int right, int key) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key) {
            return mid;
        }
        if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// Demonstration function
void demonstrateExponentialSearch() {
    int arr[] = {2, 3, 4, 10, 40, 50, 70, 90, 100, 120};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int key = 70;
    int result = exponentialSearch(arr, n, key);

    if (result != -1) {
        printf("Element %d found at index %d\n", key, result);
    } else {
        printf("Element not found\n");
    }
}

int main() {
    demonstrateExponentialSearch();
    return 0;
}
```

### Complexity Analysis

#### Time Complexity
- **O(log n)**: Better than binary search for unbounded arrays

#### Space Complexity
- O(1)

### When to Use
- Unbounded/infinite arrays
- Element likely near beginning

---

## Comparison of Search Algorithms

| Algorithm | Time Complexity | Space | Requires Sorted? | Best For |
|-----------|----------------|-------|------------------|----------|
| Linear Search | O(n) | O(1) | No | Small/unsorted data |
| Binary Search | O(log n) | O(1) | Yes | Large sorted data |
| Interpolation | O(log log n) avg | O(1) | Yes | Uniform distribution |
| Jump Search | O(√n) | O(1) | Yes | High jump cost |
| Exponential | O(log n) | O(1) | Yes | Unbounded arrays |

---

## Practice Problems

### Problem 1: Modified Binary Search
Implement binary search to find the first element greater than or equal to the given key.

### Problem 2: Count Inversions
Count number of elements greater than current element to its right using search.

### Problem 3: Search in Rotated Array
Search in a sorted array that has been rotated. Example: [4,5,6,7,0,1,2]

### Problem 4: Find Peak Element
An element is peak if it's greater than its neighbors. Find any peak in O(log n).

### Problem 5: Search in 2D Matrix
Search in a 2D matrix where each row and column is sorted.

### Problem 6: Find Missing Number
Find the missing number in an array of n-1 integers from 1 to n.

### Problem 7: Find Square Root
Find floor of square root using binary search.

### Problem 8: Aggressive Cows
Place k cows in n stalls to maximize minimum distance between cows.

### Problem 9: Book Allocation
Allocate books to students to minimize maximum pages allocated.

### Problem 10: Search Insert Position
Find the index where element should be inserted to maintain sorted order.

---

## Summary

- **Linear Search**: Simple, O(n), works on unsorted data
- **Binary Search**: Efficient, O(log n), requires sorted data
- **Interpolation Search**: Best for uniform distribution, O(log log n)
- **Jump Search**: Good for systems with high jump cost, O(√n)
- **Exponential Search**: Excellent for unbounded arrays, O(log n)

**Key Takeaway**: Choose algorithm based on data characteristics and constraints!

---

**Next Topic**: Sorting Algorithms
