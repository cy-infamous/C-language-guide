# Divide and Conquer Algorithms

## Table of Contents
1. [Introduction to Divide and Conquer](#introduction)
2. [The Paradigm](#the-paradigm)
3. [Master Theorem](#master-theorem)
4. [Classic Divide and Conquer Algorithms](#classic-algorithms)
5. [Applications](#applications)
6. [Practice Problems](#practice-problems)

---

## Introduction to Divide and Conquer

**Divide and Conquer** is an algorithmic paradigm that solves problems by breaking them into smaller subproblems, solving subproblems recursively, and combining solutions.

### Core Principle
```
1. DIVIDE: Break problem into smaller subproblems
2. CONQUER: Solve subproblems recursively
3. COMBINE: Merge solutions of subproblems
```

### Examples in Real Life
- **Binary Search**: Divide array in half repeatedly
- **Merge Sort**: Divide array, sort halves, merge
- **Quick Sort**: Partition around pivot, sort partitions
- **Strassen's Matrix Multiplication**
- **Closest Pair of Points**

---

## The Paradigm

### General Structure

```c
ResultType divideAndConquer(Problem P) {
    // Base case: problem small enough to solve directly
    if (P is small enough) {
        return solve P directly;
    }

    // DIVIDE: Break into subproblems
    Problem P1, P2, ..., Pk = divide(P);

    // CONQUER: Solve subproblems recursively
    ResultType R1 = divideAndConquer(P1);
    ResultType R2 = divideAndConquer(P2);
    ...
    ResultType Rk = divideAndConquer(Pk);

    // COMBINE: Merge solutions
    ResultType R = combine(R1, R2, ..., Rk);

    return R;
}
```

### Recurrence Relations

Most divide-and-conquer algorithms follow this pattern:
```
T(n) = a × T(n/b) + f(n)

where:
  a = number of subproblems
  n/b = size of each subproblem
  f(n) = work to divide and combine
```

**Examples**:
- Binary Search: T(n) = T(n/2) + O(1)
- Merge Sort: T(n) = 2T(n/2) + O(n)
- Strassen's: T(n) = 7T(n/2) + O(n²)

---

## Master Theorem

The **Master Theorem** provides a cookbook method for solving recurrences.

### Statement

For recurrence: **T(n) = aT(n/b) + f(n)** where a ≥ 1, b > 1

Compare f(n) with n^(log_b a):

**Case 1**: If f(n) = O(n^c) where c < log_b a
```
T(n) = Θ(n^(log_b a))
```

**Case 2**: If f(n) = Θ(n^c × log^k n) where c = log_b a
```
T(n) = Θ(n^c × log^(k+1) n)
```

**Case 3**: If f(n) = Ω(n^c) where c > log_b a, and regularity condition holds
```
T(n) = Θ(f(n))
```

### Examples

#### Example 1: Binary Search
```
T(n) = T(n/2) + O(1)

a = 1, b = 2, f(n) = O(1)
log_b a = log_2 1 = 0
n^(log_b a) = n^0 = 1

f(n) = O(1) = Θ(n^0)
Case 2: c = log_b a = 0, k = 0
T(n) = Θ(n^0 × log^1 n) = Θ(log n)
```

#### Example 2: Merge Sort
```
T(n) = 2T(n/2) + O(n)

a = 2, b = 2, f(n) = O(n)
log_b a = log_2 2 = 1
n^(log_b a) = n^1 = n

f(n) = O(n) = Θ(n^1)
Case 2: c = log_b a = 1, k = 0
T(n) = Θ(n × log n)
```

#### Example 3: Karatsuba Multiplication
```
T(n) = 3T(n/2) + O(n)

a = 3, b = 2, f(n) = O(n)
log_b a = log_2 3 ≈ 1.585
n^(log_b a) ≈ n^1.585

f(n) = O(n) = O(n^1)
c = 1 < 1.585 = log_b a
Case 1: T(n) = Θ(n^1.585)
```

---

## Classic Divide and Conquer Algorithms

### 1. Binary Search

Already covered in detail in searching algorithms. Here's the divide-and-conquer perspective:

```c
#include <stdio.h>

// Divide and Conquer: Binary Search
int binarySearch(int arr[], int left, int right, int key) {
    // Base case
    if (left > right) {
        return -1;
    }

    // DIVIDE: Find middle
    int mid = left + (right - left) / 2;

    // Base case: Found
    if (arr[mid] == key) {
        return mid;
    }

    // CONQUER: Recursively search one half
    if (arr[mid] > key) {
        return binarySearch(arr, left, mid - 1, key);
    } else {
        return binarySearch(arr, mid + 1, right, key);
    }

    // COMBINE: Not needed (searching returns index directly)
}
```

**Analysis**:
- Divide: O(1) - calculate middle
- Conquer: T(n/2) - search one half
- Combine: O(1) - no work needed
- Total: T(n) = T(n/2) + O(1) = O(log n)

---

### 2. Merge Sort

```c
#include <stdio.h>
#include <stdlib.h>

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// COMBINE: Merge two sorted subarrays
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp arrays
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // Copy data
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge back
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

// Divide and Conquer: Merge Sort
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // DIVIDE: Find middle point
        int mid = left + (right - left) / 2;

        // CONQUER: Recursively sort both halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // COMBINE: Merge sorted halves
        merge(arr, left, mid, right);
    }
}

void demonstrateMergeSort() {
    printf("=== MERGE SORT (Divide and Conquer) ===\n\n");

    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    mergeSort(arr, 0, n - 1);

    printf("Sorted array: ");
    printArray(arr, n);
}
```

**Analysis**:
- Divide: O(1) - calculate middle
- Conquer: 2T(n/2) - sort both halves
- Combine: O(n) - merge arrays
- Total: T(n) = 2T(n/2) + O(n) = O(n log n)

---

### 3. Quick Sort

```c
#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// DIVIDE: Partition array around pivot
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Divide and Conquer: Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // DIVIDE: Partition array and get pivot position
        int pi = partition(arr, low, high);

        // CONQUER: Recursively sort partitions
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);

        // COMBINE: Not needed (in-place sorting)
    }
}

void demonstrateQuickSort() {
    printf("=== QUICK SORT (Divide and Conquer) ===\n\n");

    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    quickSort(arr, 0, n - 1);

    printf("Sorted array: ");
    printArray(arr, n);
}
```

**Analysis**:
- Divide: O(n) - partition array
- Conquer: 2T(n/2) - average case
- Combine: O(1) - no work needed
- Total: T(n) = 2T(n/2) + O(n) = O(n log n) average
- Worst: T(n) = T(n-1) + O(n) = O(n²)

---

### 4. Maximum Subarray Problem

**Problem**: Find contiguous subarray with maximum sum.

**Example**: [-2, 1, -3, 4, -1, 2, 1, -5, 4] → [4, -1, 2, 1] = 6

```c
#include <stdio.h>
#include <limits.h>

// Find maximum of three numbers
int max(int a, int b, int c) {
    int max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    return max;
}

// COMBINE: Find max crossing subarray
int maxCrossingSum(int arr[], int left, int mid, int right) {
    // Left side of mid
    int sum = 0;
    int leftSum = INT_MIN;

    for (int i = mid; i >= left; i--) {
        sum += arr[i];
        if (sum > leftSum) {
            leftSum = sum;
        }
    }

    // Right side of mid
    sum = 0;
    int rightSum = INT_MIN;

    for (int i = mid + 1; i <= right; i++) {
        sum += arr[i];
        if (sum > rightSum) {
            rightSum = sum;
        }
    }

    return leftSum + rightSum;
}

// Divide and Conquer: Maximum Subarray
int maxSubarraySum(int arr[], int left, int right) {
    // Base case: only one element
    if (left == right) {
        return arr[left];
    }

    // DIVIDE: Find middle
    int mid = left + (right - left) / 2;

    // CONQUER: Recursively find max in three cases
    int leftMax = maxSubarraySum(arr, left, mid);
    int rightMax = maxSubarraySum(arr, mid + 1, right);

    // COMBINE: Find max crossing middle
    int crossMax = maxCrossingSum(arr, left, mid, right);

    // Return maximum of three
    return max(leftMax, rightMax, crossMax);
}

void demonstrateMaxSubarray() {
    printf("=== MAXIMUM SUBARRAY (Divide and Conquer) ===\n\n");

    int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array: ");
    printArray(arr, n);

    int maxSum = maxSubarraySum(arr, 0, n - 1);
    printf("Maximum subarray sum: %d\n", maxSum);
}
```

**Analysis**:
- Divide: O(1)
- Conquer: 2T(n/2)
- Combine: O(n) - find crossing sum
- Total: T(n) = 2T(n/2) + O(n) = O(n log n)

**Note**: Kadane's algorithm solves this in O(n) using dynamic programming!

---

### 5. Matrix Multiplication (Strassen's Algorithm)

**Standard matrix multiplication**: O(n³)
**Strassen's algorithm**: O(n^2.807)

```c
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Add two matrices
void addMatrix(int A[][MAX], int B[][MAX], int C[][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Subtract two matrices
void subtractMatrix(int A[][MAX], int B[][MAX], int C[][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Standard matrix multiplication
void multiplyMatrix(int A[][MAX], int B[][MAX], int C[][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Strassen's Matrix Multiplication (simplified for n = power of 2)
// For production: needs dynamic allocation and base case optimization
void strassenMultiply(int A[][MAX], int B[][MAX], int C[][MAX], int n) {
    // Base case: use standard multiplication for small matrices
    if (n <= 32) {  // Threshold for efficiency
        multiplyMatrix(A, B, C, n);
        return;
    }

    int newSize = n / 2;

    // Allocate submatrices (simplified - should use dynamic allocation)
    // A11, A12, A21, A22, B11, B12, B21, B22, etc.

    // Strassen's formula uses 7 multiplications instead of 8
    // M1 = (A11 + A22)(B11 + B22)
    // M2 = (A21 + A22)B11
    // M3 = A11(B12 - B22)
    // M4 = A22(B21 - B11)
    // M5 = (A11 + A12)B22
    // M6 = (A21 - A11)(B11 + B12)
    // M7 = (A12 - A22)(B21 + B22)

    // C11 = M1 + M4 - M5 + M7
    // C12 = M3 + M5
    // C21 = M2 + M4
    // C22 = M1 - M2 + M3 + M6

    // Implementation details omitted for brevity
    // This is conceptual - full implementation is complex
}

void demonstrateMatrixMultiplication() {
    printf("=== MATRIX MULTIPLICATION ===\n\n");

    int n = 2;
    int A[MAX][MAX] = {{1, 2}, {3, 4}};
    int B[MAX][MAX] = {{5, 6}, {7, 8}};
    int C[MAX][MAX];

    printf("Matrix A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

    multiplyMatrix(A, B, C, n);

    printf("\nResult C = A × B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
}
```

**Analysis**:
- Standard: O(n³)
- Strassen's: T(n) = 7T(n/2) + O(n²) = O(n^2.807)

---

### 6. Closest Pair of Points

**Problem**: Given n points in 2D plane, find pair with minimum distance.

```c
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

// Calculate distance between two points
float distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                (p1.y - p2.y) * (p1.y - p2.y));
}

// Brute force for small arrays
float bruteForce(Point points[], int n) {
    float minDist = FLT_MAX;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            float dist = distance(points[i], points[j]);
            if (dist < minDist) {
                minDist = dist;
            }
        }
    }

    return minDist;
}

// Compare function for qsort (by x-coordinate)
int compareX(const void* a, const void* b) {
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    return (p1->x - p2->x);
}

// Compare function for qsort (by y-coordinate)
int compareY(const void* a, const void* b) {
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    return (p1->y - p2->y);
}

// Find minimum of two floats
float min(float a, float b) {
    return (a < b) ? a : b;
}

// Find minimum distance in strip
float stripClosest(Point strip[], int size, float d) {
    float minDist = d;

    // Sort strip by y-coordinate
    qsort(strip, size, sizeof(Point), compareY);

    // Check each point with next 7 points
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < minDist; j++) {
            float dist = distance(strip[i], strip[j]);
            if (dist < minDist) {
                minDist = dist;
            }
        }
    }

    return minDist;
}

// Divide and Conquer: Closest Pair
float closestUtil(Point pointsX[], Point pointsY[], int n) {
    // Base case: use brute force for small arrays
    if (n <= 3) {
        return bruteForce(pointsX, n);
    }

    // DIVIDE: Find middle point
    int mid = n / 2;
    Point midPoint = pointsX[mid];

    // Divide points by vertical line through midPoint
    Point* pointsYLeft = (Point*)malloc(mid * sizeof(Point));
    Point* pointsYRight = (Point*)malloc((n - mid) * sizeof(Point));

    int leftIdx = 0, rightIdx = 0;
    for (int i = 0; i < n; i++) {
        if (pointsY[i].x <= midPoint.x && leftIdx < mid) {
            pointsYLeft[leftIdx++] = pointsY[i];
        } else {
            pointsYRight[rightIdx++] = pointsY[i];
        }
    }

    // CONQUER: Find minimum distance in left and right halves
    float distLeft = closestUtil(pointsX, pointsYLeft, mid);
    float distRight = closestUtil(pointsX + mid, pointsYRight, n - mid);

    float d = min(distLeft, distRight);

    // COMBINE: Find points in strip
    Point* strip = (Point*)malloc(n * sizeof(Point));
    int stripSize = 0;

    for (int i = 0; i < n; i++) {
        if (abs(pointsY[i].x - midPoint.x) < d) {
            strip[stripSize++] = pointsY[i];
        }
    }

    // Find minimum distance in strip
    float stripMin = stripClosest(strip, stripSize, d);

    // Cleanup
    free(pointsYLeft);
    free(pointsYRight);
    free(strip);

    return min(d, stripMin);
}

// Main function to find closest pair
float closestPair(Point points[], int n) {
    // Sort by x-coordinate
    Point* pointsX = (Point*)malloc(n * sizeof(Point));
    Point* pointsY = (Point*)malloc(n * sizeof(Point));

    for (int i = 0; i < n; i++) {
        pointsX[i] = pointsY[i] = points[i];
    }

    qsort(pointsX, n, sizeof(Point), compareX);
    qsort(pointsY, n, sizeof(Point), compareY);

    float result = closestUtil(pointsX, pointsY, n);

    free(pointsX);
    free(pointsY);

    return result;
}

void demonstrateClosestPair() {
    printf("=== CLOSEST PAIR OF POINTS ===\n\n");

    Point points[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    int n = sizeof(points) / sizeof(points[0]);

    printf("Points:\n");
    for (int i = 0; i < n; i++) {
        printf("(%d, %d) ", points[i].x, points[i].y);
    }
    printf("\n");

    float minDist = closestPair(points, n);
    printf("\nMinimum distance: %.2f\n", minDist);
}
```

**Analysis**:
- Divide: O(n) - divide points by line
- Conquer: 2T(n/2) - solve for both halves
- Combine: O(n) - check strip
- Total: T(n) = 2T(n/2) + O(n) = O(n log n)

---

### 7. Count Inversions

**Problem**: Count pairs (i, j) where i < j but arr[i] > arr[j]

```c
#include <stdio.h>
#include <stdlib.h>

// Merge and count inversions
long long mergeAndCount(int arr[], int temp[], int left, int mid, int right) {
    int i = left;    // Starting index of left subarray
    int j = mid + 1; // Starting index of right subarray
    int k = left;    // Starting index of merged array
    long long invCount = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            // All remaining elements in left subarray (arr[i...mid])
            // are greater than arr[j]
            invCount += (mid - i + 1);
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // Copy sorted subarray back to original array
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return invCount;
}

// Divide and Conquer: Count Inversions
long long mergeSortAndCount(int arr[], int temp[], int left, int right) {
    long long invCount = 0;

    if (left < right) {
        // DIVIDE
        int mid = left + (right - left) / 2;

        // CONQUER: Count inversions in left and right halves
        invCount += mergeSortAndCount(arr, temp, left, mid);
        invCount += mergeSortAndCount(arr, temp, mid + 1, right);

        // COMBINE: Count split inversions
        invCount += mergeAndCount(arr, temp, left, mid, right);
    }

    return invCount;
}

long long countInversions(int arr[], int n) {
    int* temp = (int*)malloc(n * sizeof(int));
    long long result = mergeSortAndCount(arr, temp, 0, n - 1);
    free(temp);
    return result;
}

void demonstrateCountInversions() {
    printf("=== COUNT INVERSIONS ===\n\n");

    int arr[] = {8, 4, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array: ");
    printArray(arr, n);

    long long inversions = countInversions(arr, n);
    printf("Number of inversions: %lld\n", inversions);

    printf("\nExplanation:\n");
    printf("(8,4), (8,2), (8,1), (4,2), (4,1), (2,1) = 6 inversions\n");
}
```

**Analysis**: O(n log n) - same as merge sort

---

## Applications

### 1. Fast Fourier Transform (FFT)
- Signal processing
- Polynomial multiplication
- Time complexity: O(n log n)

### 2. Karatsuba Multiplication
- Fast integer multiplication
- Time complexity: O(n^1.585)

### 3. Computational Geometry
- Closest pair of points
- Convex hull
- Line segment intersection

### 4. Sorting and Searching
- Merge sort, quick sort
- Binary search
- Selection algorithms

### 5. Dynamic Programming Optimization
- Some DP problems can be solved using divide and conquer
- Optimal binary search tree

---

## Practice Problems

### Problem 1: Median of Two Sorted Arrays
Find median of two sorted arrays in O(log(min(n,m))).

### Problem 2: Power of a Number
Calculate x^n in O(log n) time using divide and conquer.

### Problem 3: Majority Element
Find element appearing more than n/2 times using divide and conquer.

### Problem 4: Peak Element
Find peak element in array in O(log n) time.

### Problem 5: Kth Smallest Element
Find kth smallest element using QuickSelect (average O(n)).

### Problem 6: Merge K Sorted Arrays
Merge k sorted arrays using divide and conquer approach.

### Problem 7: Skyline Problem
Given buildings, find skyline using divide and conquer.

### Problem 8: Count Smaller Numbers After Self
For each element, count how many elements to its right are smaller.

### Problem 9: Binary Tree Maximum Path Sum
Find maximum path sum in binary tree.

### Problem 10: Longest Common Prefix
Find longest common prefix among strings using divide and conquer.

---

## Comparison with Other Paradigms

| Paradigm | Approach | Subproblem Overlap | Example |
|----------|----------|-------------------|---------|
| Divide & Conquer | Break into independent subproblems | No | Merge Sort |
| Dynamic Programming | Break into overlapping subproblems | Yes | Fibonacci (DP) |
| Greedy | Make locally optimal choice | No | Dijkstra's |
| Backtracking | Try all possibilities | No | N-Queens |

---

## Summary

### Key Concepts
1. **Three steps**: Divide, Conquer, Combine
2. **Recurrence relations**: T(n) = aT(n/b) + f(n)
3. **Master Theorem**: Cookbook for solving recurrences
4. **Efficiency**: Often achieves O(n log n) or better

### Common Patterns
- **Binary division**: Binary search, merge sort
- **Partition-based**: Quick sort, quickselect
- **Geometric**: Closest pair, convex hull

### When to Use
1. Problem can be broken into similar subproblems
2. Subproblems are independent
3. Solutions can be combined efficiently
4. Recursive solution is natural

### Advantages
- Often very efficient (O(n log n))
- Parallelizable
- Elegant and intuitive

### Disadvantages
- Recursion overhead
- May use more space
- Not always optimal (DP might be better)

---

**Next Topic**: Greedy Algorithms
