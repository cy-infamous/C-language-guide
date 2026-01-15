# Introduction to Data Structures and Algorithms

## Table of Contents
1. [What is Data Structures and Algorithms?](#what-is-dsa)
2. [Why DSA Matters](#why-dsa-matters)
3. [Time Complexity](#time-complexity)
4. [Space Complexity](#space-complexity)
5. [Big O Notation](#big-o-notation)
6. [Common Complexity Classes](#common-complexity-classes)
7. [How to Analyze Algorithms](#how-to-analyze-algorithms)
8. [Practice Problems](#practice-problems)

---

## What is Data Structures and Algorithms?

### Data Structures
A **data structure** is a way of organizing and storing data in a computer so that it can be accessed and modified efficiently. It defines the relationship between the data and the operations that can be performed on the data.

### Algorithms
An **algorithm** is a step-by-step procedure or formula for solving a problem. It takes input, processes it through a series of steps, and produces output.

### Why Study Them Together?
- Data structures provide the foundation for storing data
- Algorithms provide methods to manipulate that data
- The choice of data structure affects algorithm efficiency
- Together, they solve computational problems efficiently

---

## Why DSA Matters

### 1. Problem Solving Skills
- Develops logical thinking
- Improves analytical abilities
- Teaches systematic approach to problems

### 2. Performance Optimization
- Makes programs faster
- Reduces memory usage
- Improves scalability

### 3. Technical Interviews
- Core topic in coding interviews
- Tests fundamental programming knowledge
- Required for top tech companies

### 4. Real-World Applications
- Database systems
- Operating systems
- Network routing
- Artificial intelligence
- Game development

---

## Time Complexity

### Definition
**Time complexity** measures the amount of time an algorithm takes to complete as a function of the input size (n).

### Why It Matters
- Predicts how algorithm performance scales
- Helps compare different algorithms
- Identifies bottlenecks in code

### Example: Finding Maximum Element

```c
// Algorithm 1: Linear Search
int findMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}
// Time Complexity: O(n) - visits each element once
```

### Counting Operations

```c
void example1(int n) {
    int sum = 0;           // 1 operation
    for (int i = 0; i < n; i++) {  // n iterations
        sum += i;          // n operations
    }
    // Total: 1 + n + n = 2n + 1 operations
    // Time Complexity: O(n)
}

void example2(int n) {
    int sum = 0;           // 1 operation
    for (int i = 0; i < n; i++) {      // n iterations
        for (int j = 0; j < n; j++) {  // n iterations
            sum += i * j;              // n² operations
        }
    }
    // Total: 1 + n² operations
    // Time Complexity: O(n²)
}
```

---

## Space Complexity

### Definition
**Space complexity** measures the amount of memory an algorithm uses as a function of the input size (n).

### Components of Space Complexity
1. **Fixed Part**: Space required for constants, variables
2. **Variable Part**: Space required based on input size

### Example: Space Analysis

```c
// Example 1: O(1) Space
int sum(int arr[], int n) {
    int total = 0;  // Fixed space
    for (int i = 0; i < n; i++) {
        total += arr[i];
    }
    return total;
}
// Space: O(1) - only uses 'total' variable

// Example 2: O(n) Space
int* createCopy(int arr[], int n) {
    int* copy = (int*)malloc(n * sizeof(int));  // Space proportional to n
    for (int i = 0; i < n; i++) {
        copy[i] = arr[i];
    }
    return copy;
}
// Space: O(n) - creates array of size n

// Example 3: O(n²) Space
int** create2DArray(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    return matrix;
}
// Space: O(n²) - creates n×n matrix
```

---

## Big O Notation

### Definition
**Big O notation** describes the upper bound of the growth rate of an algorithm. It represents the worst-case scenario.

### Formal Definition
f(n) = O(g(n)) if there exist positive constants c and n₀ such that:
```
0 ≤ f(n) ≤ c × g(n) for all n ≥ n₀
```

### Why "Big O"?
- Focuses on growth rate, not exact operations
- Ignores constants and lower-order terms
- Simplifies comparison between algorithms

### Examples of Simplification

```
f(n) = 3n² + 5n + 10
     = O(n²)          // Drop constants and lower terms

f(n) = 100n + 50
     = O(n)           // Drop constants

f(n) = 2ⁿ + n³
     = O(2ⁿ)          // Exponential dominates polynomial
```

### Visual Representation of Growth Rates

```
Time
 |
 |                                                    O(2ⁿ)
 |                                                  /
 |                                                /
 |                                              /
 |                                    O(n²)   /
 |                                   /      /
 |                          O(n log n)   /
 |                         /           /
 |                O(n)   /          /
 |               /     /         /
 |      O(log n)/   /        /
 |            / / /       /
 |   O(1)___/_/_/_____/___________
 |_____|___|___|___|___|___|___|______ Input Size (n)
     1   10  100 1K  10K 100K 1M
```

---

## Common Complexity Classes

### 1. O(1) - Constant Time
**Definition**: Algorithm takes the same time regardless of input size.

**Examples**:
- Accessing array element by index
- Inserting at the beginning of a linked list
- Arithmetic operations

```c
// O(1) Example
int getFirstElement(int arr[], int n) {
    return arr[0];  // Always 1 operation
}

int add(int a, int b) {
    return a + b;   // Always 1 operation
}
```

### 2. O(log n) - Logarithmic Time
**Definition**: Algorithm reduces problem size by a constant factor each step.

**Examples**:
- Binary search
- Finding element in balanced BST
- Certain divide-and-conquer algorithms

```c
// O(log n) Example: Binary Search
int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// Iterations: log₂(n)
// Example: n=1000 → ~10 iterations
//          n=1,000,000 → ~20 iterations
```

### 3. O(n) - Linear Time
**Definition**: Algorithm processes each element once.

**Examples**:
- Linear search
- Finding min/max
- Traversing a list

```c
// O(n) Example: Linear Search
int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

// Iterations: n
// Must potentially check every element
```

### 4. O(n log n) - Linearithmic Time
**Definition**: Combination of linear and logarithmic operations.

**Examples**:
- Efficient sorting algorithms (Merge Sort, Quick Sort, Heap Sort)
- Building a balanced BST

```c
// O(n log n) Example: Merge Sort (simplified)
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);      // Divide: log n levels
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);   // Merge: O(n) at each level
    }
}

// Total: n × log n
// Best comparison-based sorting algorithms achieve this
```

### 5. O(n²) - Quadratic Time
**Definition**: Algorithm with nested operations over input.

**Examples**:
- Bubble sort, Selection sort, Insertion sort
- Comparing all pairs

```c
// O(n²) Example: Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {           // n iterations
        for (int j = 0; j < n - i - 1; j++) {   // n iterations
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Total comparisons: n × n = n²
```

### 6. O(n³) - Cubic Time
**Definition**: Three nested loops over input.

**Examples**:
- Matrix multiplication (naive approach)
- Three-way nested loops

```c
// O(n³) Example: Matrix Multiplication
void matrixMultiply(int A[][100], int B[][100], int C[][100], int n) {
    for (int i = 0; i < n; i++) {           // n iterations
        for (int j = 0; j < n; j++) {       // n iterations
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {   // n iterations
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Total: n × n × n = n³
```

### 7. O(2ⁿ) - Exponential Time
**Definition**: Algorithm's growth doubles with each input addition.

**Examples**:
- Recursive Fibonacci (naive)
- Generating all subsets
- Tower of Hanoi

```c
// O(2ⁿ) Example: Naive Fibonacci
int fibonacci(int n) {
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Call tree for fib(5):
//                 fib(5)
//              /          \
//          fib(4)          fib(3)
//         /     \          /     \
//     fib(3)   fib(2)   fib(2)   fib(1)
//     /   \     /   \    /   \
// fib(2) fib(1) ...  ...  ...  ...
//
// Total calls: 2⁰ + 2¹ + 2² + ... + 2ⁿ ≈ 2ⁿ⁺¹ - 1 = O(2ⁿ)
```

### 8. O(n!) - Factorial Time
**Definition**: Generates all permutations.

**Examples**:
- Generating all permutations
- Brute-force traveling salesman problem

```c
// O(n!) Example: Generating Permutations
void generatePermutations(int arr[], int start, int end) {
    if (start == end) {
        printArray(arr, end + 1);
        return;
    }

    for (int i = start; i <= end; i++) {
        swap(&arr[start], &arr[i]);
        generatePermutations(arr, start + 1, end);
        swap(&arr[start], &arr[i]);  // backtrack
    }
}

// For n elements: n! permutations
// n=5: 120 permutations
// n=10: 3,628,800 permutations
```

### Complexity Comparison Table

| Complexity | n=10 | n=100 | n=1,000 | n=10,000 | Growth Rate |
|-----------|------|-------|---------|----------|-------------|
| O(1) | 1 | 1 | 1 | 1 | Constant |
| O(log n) | 3 | 7 | 10 | 13 | Very Slow |
| O(n) | 10 | 100 | 1,000 | 10,000 | Linear |
| O(n log n) | 30 | 700 | 10,000 | 130,000 | Moderate |
| O(n²) | 100 | 10,000 | 1,000,000 | 100,000,000 | Fast |
| O(2ⁿ) | 1,024 | 1.27×10³⁰ | - | - | Very Fast |
| O(n!) | 3,628,800 | - | - | - | Extremely Fast |

---

## How to Analyze Algorithms

### Step-by-Step Process

#### 1. Identify Basic Operations
Find the most time-consuming operation in the algorithm.

#### 2. Count Operations
Count how many times basic operations execute relative to input size.

#### 3. Express as Function
Write the count as a function of n.

#### 4. Simplify Using Big O
Apply Big O rules to simplify.

### Example Analysis

```c
void exampleFunction(int arr[], int n) {
    int sum = 0;                        // O(1)

    for (int i = 0; i < n; i++) {       // Loop 1: n times
        sum += arr[i];                  // O(1) × n = O(n)
    }

    for (int i = 0; i < n; i++) {       // Loop 2: n times
        for (int j = 0; j < n; j++) {   // Inner: n times
            printf("%d ", arr[i] + arr[j]);  // O(1) × n × n = O(n²)
        }
    }

    // Total: O(1) + O(n) + O(n²) = O(n²)
    // Dominant term is n²
}
```

### Rules for Big O Simplification

1. **Drop Constants**
   - O(2n) → O(n)
   - O(5n²) → O(n²)

2. **Drop Non-Dominant Terms**
   - O(n² + n) → O(n²)
   - O(n³ + n² + n) → O(n³)

3. **Different Inputs Use Different Variables**
   ```c
   void process(int arr1[], int m, int arr2[], int n) {
       for (int i = 0; i < m; i++) { }  // O(m)
       for (int i = 0; i < n; i++) { }  // O(n)
   }
   // Time Complexity: O(m + n), NOT O(n)
   ```

4. **Multiply for Nested Loops**
   ```c
   for (int i = 0; i < n; i++) {
       for (int j = 0; j < n; j++) { }
   }
   // O(n) × O(n) = O(n²)
   ```

5. **Add for Sequential Loops**
   ```c
   for (int i = 0; i < n; i++) { }  // O(n)
   for (int i = 0; i < n; i++) { }  // O(n)
   // O(n) + O(n) = O(2n) = O(n)
   ```

### Complete Analysis Example

```c
#include <stdio.h>
#include <stdlib.h>

// Function to analyze
void complexFunction(int arr[], int n) {
    // Step 1: O(1) operations
    int max = arr[0];                    // 1 operation
    int min = arr[0];                    // 1 operation

    // Step 2: O(n) loop
    for (int i = 1; i < n; i++) {        // n-1 iterations
        if (arr[i] > max)                // n-1 comparisons
            max = arr[i];                // worst case: n-1 assignments
        if (arr[i] < min)
            min = arr[i];
    }

    // Step 3: O(n log n) operation
    // Assume this is merge sort or similar
    // sortArray(arr, n);                // O(n log n)

    // Step 4: O(n²) nested loop
    for (int i = 0; i < n; i++) {        // n iterations
        for (int j = i + 1; j < n; j++) { // n/2 avg iterations
            if (arr[i] + arr[j] == 0) {  // n² comparisons
                printf("Pair: %d, %d\n", arr[i], arr[j]);
            }
        }
    }
}

// Analysis:
// T(n) = O(1) + O(n) + O(n log n) + O(n²)
// T(n) = O(n²) (dominant term)
//
// Space Complexity: O(1) (only uses fixed variables)
```

---

## Best, Average, and Worst Case

### Definitions

- **Best Case**: Minimum time algorithm takes (optimistic scenario)
- **Average Case**: Expected time for typical input (realistic scenario)
- **Worst Case**: Maximum time algorithm takes (pessimistic scenario)

### Example: Linear Search

```c
int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

// Best Case: O(1) - element at first position
// Average Case: O(n/2) = O(n) - element in middle
// Worst Case: O(n) - element at end or not present
```

### Example: Quick Sort

```c
// Quick Sort Complexity Analysis
// Best Case: O(n log n) - pivot divides array evenly
// Average Case: O(n log n) - typical random input
// Worst Case: O(n²) - already sorted array with poor pivot choice
```

---

## Complete Complexity Analysis Program

```c
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// O(1) - Constant Time
void constantTime(int arr[], int n) {
    printf("First element: %d\n", arr[0]);
}

// O(log n) - Logarithmic Time
int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// O(n) - Linear Time
int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

// O(n²) - Quadratic Time
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Timing function
void measureTime(void (*func)(int[], int), int arr[], int n, const char* name) {
    clock_t start = clock();
    func(arr, n);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    printf("%s: %.4f ms\n", name, time_taken);
}

int main() {
    int sizes[] = {100, 1000, 10000};

    printf("=== Time Complexity Demonstration ===\n\n");

    for (int s = 0; s < 3; s++) {
        int n = sizes[s];
        int* arr = (int*)malloc(n * sizeof(int));

        // Fill array
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 1000;
        }

        printf("Array size: %d\n", n);

        // Test O(1)
        clock_t start = clock();
        constantTime(arr, n);
        clock_t end = clock();
        printf("O(1) Constant: %.4f ms\n",
               ((double)(end - start)) / CLOCKS_PER_SEC * 1000);

        // Test O(n)
        start = clock();
        linearSearch(arr, n, -1);
        end = clock();
        printf("O(n) Linear: %.4f ms\n",
               ((double)(end - start)) / CLOCKS_PER_SEC * 1000);

        // Test O(n²) - only for smaller sizes
        if (n <= 1000) {
            int* arr_copy = (int*)malloc(n * sizeof(int));
            for (int i = 0; i < n; i++) arr_copy[i] = arr[i];

            start = clock();
            bubbleSort(arr_copy, n);
            end = clock();
            printf("O(n²) Quadratic: %.4f ms\n",
                   ((double)(end - start)) / CLOCKS_PER_SEC * 1000);
            free(arr_copy);
        }

        printf("\n");
        free(arr);
    }

    return 0;
}
```

---

## Practice Problems

### Problem 1: Analyze Time Complexity (Easy)
What is the time complexity of the following code?
```c
void mystery1(int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 100; j++) {
            sum += i + j;
        }
    }
}
```
**Answer**: O(n) - Inner loop runs constant (100) times

### Problem 2: Nested Loop Analysis (Easy)
```c
void mystery2(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            printf("%d ", i + j);
        }
    }
}
```
**Answer**: O(n²) - Inner loop runs (n + (n-1) + ... + 1) = n(n+1)/2 times

### Problem 3: Logarithmic Pattern (Medium)
```c
void mystery3(int n) {
    int i = 1;
    while (i < n) {
        printf("%d ", i);
        i = i * 2;
    }
}
```
**Answer**: O(log n) - i doubles each iteration

### Problem 4: Multiple Loops (Medium)
```c
void mystery4(int arr1[], int m, int arr2[], int n) {
    for (int i = 0; i < m; i++) {
        printf("%d ", arr1[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", arr2[i] + arr2[j]);
        }
    }
}
```
**Answer**: O(m + n²) - Cannot simplify further

### Problem 5: Recursive Analysis (Medium)
```c
void mystery5(int n) {
    if (n <= 0) return;
    for (int i = 0; i < n; i++) {
        printf("%d ", i);
    }
    mystery5(n / 2);
}
```
**Answer**: O(n) - Forms geometric series: n + n/2 + n/4 + ... = 2n

### Problem 6: Find Complexity (Hard)
```c
void mystery6(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i * i; j++) {
            for (int k = 1; k <= n / 2; k++) {
                printf("*");
            }
        }
    }
}
```
**Answer**: O(n⁴) - Outer: n, Middle: i² (avg: n²/2), Inner: n/2

### Problem 7: Space Complexity (Medium)
What is the space complexity of this function?
```c
int* createArray(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = i * i;
    }
    return arr;
}
```
**Answer**: O(n) - Allocates array of size n

### Problem 8: Optimize Algorithm (Hard)
Improve the time complexity of finding duplicates:
```c
// Original: O(n²)
bool hasDuplicates(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j])
                return true;
        }
    }
    return false;
}
```
**Solution**: Use hash set - O(n) time, O(n) space

### Problem 9: Amortized Analysis (Hard)
Analyze the time complexity of n push operations on a dynamic array that doubles when full.
**Answer**: O(1) amortized - Total work is O(n), divided by n operations

### Problem 10: Compare Algorithms (Hard)
Algorithm A: O(100n)
Algorithm B: O(n²)
For what values of n is Algorithm A faster?
**Answer**: When n < 100 (solve 100n < n²)

---

## Summary

### Key Takeaways

1. **Big O** focuses on growth rate, not exact operations
2. **Drop constants** and non-dominant terms
3. **Worst case** is typically what we analyze
4. **Space-time tradeoff** often exists
5. **Choose appropriate complexity** for your problem size

### Complexity Hierarchy (Best to Worst)

```
O(1) < O(log n) < O(n) < O(n log n) < O(n²) < O(n³) < O(2ⁿ) < O(n!)
```

### Next Steps

- Study specific data structures (arrays, linked lists, trees, etc.)
- Learn sorting and searching algorithms
- Practice analyzing real-world problems
- Solve complexity-related coding problems

### Further Reading

- "Introduction to Algorithms" by Cormen et al. (CLRS)
- "The Algorithm Design Manual" by Skiena
- "Cracking the Coding Interview" by McDowell

---

**Happy Learning!** Practice analyzing complexity daily to build intuition.
