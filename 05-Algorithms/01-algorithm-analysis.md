# Algorithm Analysis

## Table of Contents
1. [Introduction to Algorithm Analysis](#introduction)
2. [Why Analyze Algorithms?](#why-analyze)
3. [Time and Space Complexity](#complexity)
4. [Asymptotic Notation](#asymptotic-notation)
5. [Best, Worst, and Average Case Analysis](#case-analysis)
6. [Common Complexity Classes](#complexity-classes)
7. [Rules for Calculating Complexity](#calculation-rules)
8. [Practice Problems](#practice-problems)

---

## Introduction to Algorithm Analysis

Algorithm analysis is the process of determining the computational complexity of algorithms - the amount of time, storage, or other resources needed to execute them.

### Key Concepts
- **Algorithm**: A step-by-step procedure to solve a problem
- **Efficiency**: How well an algorithm performs in terms of time and space
- **Scalability**: How performance changes as input size increases

---

## Why Analyze Algorithms?

1. **Performance Prediction**: Estimate how long an algorithm will take
2. **Comparison**: Compare different algorithms solving the same problem
3. **Optimization**: Identify bottlenecks and improve efficiency
4. **Resource Planning**: Determine hardware/memory requirements

### Example Scenario
```
Problem: Search for element in array of size n

Algorithm 1: Linear Search - checks each element
Algorithm 2: Binary Search - divides array in half repeatedly

For n = 1,000,000:
- Linear Search: Up to 1,000,000 comparisons
- Binary Search: Up to 20 comparisons (log₂ 1,000,000 ≈ 20)
```

---

## Time and Space Complexity

### Time Complexity
Measures the amount of time an algorithm takes as a function of input size.

**Not measured in seconds** - hardware dependent
**Measured in**: Number of basic operations (comparisons, assignments, etc.)

### Space Complexity
Measures the amount of memory an algorithm uses as a function of input size.

Includes:
- **Input Space**: Memory to store input data
- **Auxiliary Space**: Extra space used by algorithm (variables, recursive stack)

---

## Asymptotic Notation

Asymptotic notation describes limiting behavior of functions as input size approaches infinity.

### 1. Big-O Notation (O) - Upper Bound

Represents **worst-case** time complexity (upper bound on growth rate).

**Definition**: f(n) = O(g(n)) if there exist positive constants c and n₀ such that:
```
f(n) ≤ c × g(n) for all n ≥ n₀
```

**Visualization**:
```
Performance
    |
    |           g(n) × c
    |          /
    |         /
    |    f(n)/
    |       /
    |      /
    |_____/_____________ Input Size (n)
         n₀
```

**Example**:
```c
// Algorithm with complexity O(n)
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {      // n iterations
        printf("%d ", arr[i]);          // O(1) operation
    }
}
// Total: n × O(1) = O(n)
```

### 2. Big-Omega Notation (Ω) - Lower Bound

Represents **best-case** time complexity (lower bound on growth rate).

**Definition**: f(n) = Ω(g(n)) if there exist positive constants c and n₀ such that:
```
f(n) ≥ c × g(n) for all n ≥ n₀
```

**Example**:
```c
// Algorithm with best-case Ω(1)
int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key)
            return i;  // Best case: found at first position
    }
    return -1;
}
// Best case: Ω(1) - element at index 0
// Worst case: O(n) - element not present
```

### 3. Big-Theta Notation (Θ) - Tight Bound

Represents complexity when upper and lower bounds are the same.

**Definition**: f(n) = Θ(g(n)) if f(n) = O(g(n)) and f(n) = Ω(g(n))

**Example**:
```c
// Algorithm with complexity Θ(n)
int sumArray(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {      // Always n iterations
        sum += arr[i];
    }
    return sum;
}
// Always performs exactly n additions: Θ(n)
```

### 4. Little-o Notation (o) - Strict Upper Bound

f(n) = o(g(n)) means f(n) grows strictly slower than g(n).

**Example**: f(n) = n is o(n²) but NOT o(n)

### 5. Little-omega Notation (ω) - Strict Lower Bound

f(n) = ω(g(n)) means f(n) grows strictly faster than g(n).

**Example**: f(n) = n² is ω(n) but NOT ω(n²)

---

## Best, Worst, and Average Case Analysis

### 1. Best Case (Ω)
The minimum time/space required for any input of size n.

**Example - Linear Search**:
```c
int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key)
            return i;
    }
    return -1;
}
// Best Case: Element at first position - Ω(1)
```

### 2. Worst Case (O)
The maximum time/space required for any input of size n.

**Example - Linear Search**:
```c
// Worst Case: Element not present or at last position - O(n)
int arr[] = {1, 2, 3, 4, 5};
linearSearch(arr, 5, 99);  // 5 comparisons
```

### 3. Average Case (Θ)
The expected time/space for a random input of size n.

**Example - Linear Search**:
```
Assume element is equally likely to be at any position:
Average comparisons = (1 + 2 + 3 + ... + n) / n
                    = (n × (n+1)) / (2 × n)
                    = (n + 1) / 2
                    = Θ(n)
```

### Comparison Table

| Algorithm       | Best Case | Average Case | Worst Case |
|----------------|-----------|--------------|------------|
| Linear Search  | Ω(1)      | Θ(n)         | O(n)       |
| Binary Search  | Ω(1)      | Θ(log n)     | O(log n)   |
| Bubble Sort    | Ω(n)      | Θ(n²)        | O(n²)      |
| Quick Sort     | Ω(n log n)| Θ(n log n)   | O(n²)      |
| Merge Sort     | Ω(n log n)| Θ(n log n)   | O(n log n) |

---

## Common Complexity Classes

Listed from fastest to slowest:

### 1. O(1) - Constant Time
Performance doesn't depend on input size.

```c
// Example 1: Array access
int getElement(int arr[], int index) {
    return arr[index];  // Single operation
}

// Example 2: Mathematical computation
int addNumbers(int a, int b) {
    return a + b;
}

// Example 3: Multiple constant operations
void swap(int* a, int* b) {
    int temp = *a;  // O(1)
    *a = *b;        // O(1)
    *b = temp;      // O(1)
}
// Total: O(1) + O(1) + O(1) = O(1)
```

**Growth**: Always takes same time regardless of n

```
Time
  |_______________
  |_______________
  |_______________
  |_______________ Input Size
```

### 2. O(log n) - Logarithmic Time
Typically involves dividing problem in half repeatedly.

```c
// Binary Search
int binarySearch(int arr[], int n, int key) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}
// Each iteration halves the search space: O(log n)
```

**Growth**: Very slow growth

```
n = 10      → ~3 operations
n = 100     → ~7 operations
n = 1,000   → ~10 operations
n = 1,000,000 → ~20 operations
```

### 3. O(n) - Linear Time
Single pass through input.

```c
// Example 1: Linear search
int findMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {  // n-1 iterations
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

// Example 2: Array sum
int arraySum(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {  // n iterations
        sum += arr[i];
    }
    return sum;
}
```

**Growth**: Linear increase

```
Time
  |           /
  |         /
  |       /
  |     /
  |___/_____________ Input Size
```

### 4. O(n log n) - Linearithmic Time
Common in efficient sorting algorithms.

```c
// Merge Sort (simplified structure)
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);      // T(n/2)
        mergeSort(arr, mid + 1, right); // T(n/2)
        merge(arr, left, mid, right);   // O(n)
    }
}
// T(n) = 2T(n/2) + O(n) = O(n log n)
```

**Growth**: Slightly worse than linear

```
n = 10      → ~33 operations
n = 100     → ~664 operations
n = 1,000   → ~9,966 operations
```

### 5. O(n²) - Quadratic Time
Nested loops over input.

```c
// Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {        // n iterations
        for (int j = 0; j < n - i - 1; j++) { // n iterations
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}
// Total: n × n = O(n²)
```

**Growth**: Rapidly increasing

```
n = 10    → 100 operations
n = 100   → 10,000 operations
n = 1,000 → 1,000,000 operations
```

### 6. O(n³) - Cubic Time
Three nested loops.

```c
// Matrix multiplication
void matrixMultiply(int A[][MAX], int B[][MAX], int C[][MAX], int n) {
    for (int i = 0; i < n; i++) {           // n iterations
        for (int j = 0; j < n; j++) {       // n iterations
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {   // n iterations
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
// Total: n × n × n = O(n³)
```

### 7. O(2ⁿ) - Exponential Time
Algorithm doubles execution time with each additional input element.

```c
// Recursive Fibonacci (inefficient)
int fibonacci(int n) {
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
// T(n) = T(n-1) + T(n-2) + O(1) = O(2ⁿ)
```

**Growth**: Extremely rapid

```
n = 10  → 1,024 operations
n = 20  → 1,048,576 operations
n = 30  → 1,073,741,824 operations
```

### 8. O(n!) - Factorial Time
All permutations of input.

```c
// Generate all permutations (simplified)
void generatePermutations(int arr[], int n) {
    // For n elements, there are n! permutations
}
```

**Growth**: Catastrophically rapid

```
n = 5  → 120 operations
n = 10 → 3,628,800 operations
n = 15 → 1,307,674,368,000 operations
```

### Complexity Comparison Graph

```
Time
  |
  |                                           O(n!)
  |                                        /
  |                                    /
  |                              O(2ⁿ)/
  |                            /    /
  |                      O(n³)/   /
  |                    /     /  /
  |              O(n²)/    /  /
  |            /     /   /  /
  |      O(n log n) / /  /
  |        /   /  / / /
  |   O(n)/  /  / / /
  |   / /  /  / / /
  | O(log n) / / /
  |O(1)____|/_/_/__________ Input Size (n)
```

---

## Rules for Calculating Complexity

### Rule 1: Constant Operations are O(1)
```c
int a = 5;           // O(1)
int b = a + 10;      // O(1)
arr[0] = 100;        // O(1)
```

### Rule 2: Drop Constants
```c
void function(int n) {
    // 3n operations, but complexity is O(n), not O(3n)
    for (int i = 0; i < n; i++) {     // n times
        printf("%d", i);               // O(1)
    }
    for (int i = 0; i < n; i++) {     // n times
        printf("%d", i);               // O(1)
    }
    for (int i = 0; i < n; i++) {     // n times
        printf("%d", i);               // O(1)
    }
}
// Total: n + n + n = 3n = O(n)
```

### Rule 3: Drop Non-Dominant Terms
```c
void function(int n) {
    for (int i = 0; i < n; i++) {              // O(n)
        printf("%d", i);
    }

    for (int i = 0; i < n; i++) {              // O(n²)
        for (int j = 0; j < n; j++) {
            printf("%d %d", i, j);
        }
    }
}
// Total: O(n) + O(n²) = O(n²)
// Drop O(n) as it's dominated by O(n²)
```

### Rule 4: Different Inputs Use Different Variables
```c
void function(int arr1[], int n, int arr2[], int m) {
    for (int i = 0; i < n; i++) {     // O(n)
        printf("%d", arr1[i]);
    }

    for (int i = 0; i < m; i++) {     // O(m)
        printf("%d", arr2[i]);
    }
}
// Total: O(n + m), NOT O(n) or O(2n)
```

### Rule 5: Nested Loops Multiply
```c
void function(int n, int m) {
    for (int i = 0; i < n; i++) {           // n times
        for (int j = 0; j < m; j++) {       // m times
            printf("%d %d", i, j);          // O(1)
        }
    }
}
// Total: n × m × O(1) = O(n × m)
```

### Rule 6: Logarithmic Complexity for Halving/Doubling
```c
// Halving
void function(int n) {
    for (int i = n; i > 0; i /= 2) {  // log₂(n) iterations
        printf("%d", i);
    }
}
// Complexity: O(log n)

// Doubling
void function2(int n) {
    for (int i = 1; i < n; i *= 2) {  // log₂(n) iterations
        printf("%d", i);
    }
}
// Complexity: O(log n)
```

### Rule 7: Recursive Complexity
Use recurrence relations or recursion tree method.

```c
// Example: Binary Search
int binarySearch(int arr[], int left, int right, int key) {
    if (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key) return mid;
        if (arr[mid] > key)
            return binarySearch(arr, left, mid - 1, key);
        return binarySearch(arr, mid + 1, right, key);
    }
    return -1;
}
// T(n) = T(n/2) + O(1) = O(log n)
```

---

## Complete Analysis Examples

### Example 1: Simple Loop
```c
void example1(int n) {
    int sum = 0;                    // O(1)
    for (int i = 0; i < n; i++) {   // n iterations
        sum += i;                   // O(1)
    }
    printf("%d", sum);              // O(1)
}
// Total: O(1) + n × O(1) + O(1) = O(n)
```

### Example 2: Nested Loops
```c
void example2(int n) {
    for (int i = 0; i < n; i++) {           // n iterations
        for (int j = 0; j < n; j++) {       // n iterations
            printf("%d %d\n", i, j);        // O(1)
        }
    }
}
// Total: n × n × O(1) = O(n²)
```

### Example 3: Loop with Halving
```c
void example3(int n) {
    for (int i = 1; i < n; i *= 2) {  // log₂(n) iterations
        printf("%d\n", i);             // O(1)
    }
}
// Total: log₂(n) × O(1) = O(log n)
```

### Example 4: Mixed Complexity
```c
void example4(int n) {
    // Part 1: O(n)
    for (int i = 0; i < n; i++) {
        printf("%d", i);
    }

    // Part 2: O(log n)
    for (int i = 1; i < n; i *= 2) {
        printf("%d", i);
    }

    // Part 3: O(n²)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d %d", i, j);
        }
    }
}
// Total: O(n) + O(log n) + O(n²) = O(n²)
// Drop non-dominant terms
```

### Example 5: Dependent Nested Loops
```c
void example5(int n) {
    for (int i = 0; i < n; i++) {         // n iterations
        for (int j = i; j < n; j++) {     // (n-i) iterations
            printf("%d %d\n", i, j);
        }
    }
}
// Iterations: n + (n-1) + (n-2) + ... + 1
//           = n(n+1)/2
//           = O(n²)
```

---

## Space Complexity Analysis

### Example 1: Constant Space
```c
int findMax(int arr[], int n) {
    int max = arr[0];  // O(1) space
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}
// Space: O(1) - only uses one extra variable
```

### Example 2: Linear Space
```c
void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];  // O(n) space for dest
    }
}
// Space: O(n) - destination array of size n
```

### Example 3: Recursive Space
```c
int factorial(int n) {
    if (n <= 1)
        return 1;
    return n * factorial(n - 1);
}
// Space: O(n) - recursion stack depth is n
```

---

## Practice Problems

### Problem 1: Determine Time Complexity
Analyze the time complexity of the following code:
```c
void mystery1(int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            count++;
        }
    }
}
```
**Answer**: O(n²)

### Problem 2: Compare Algorithms
Which is faster for large n?
```c
// Algorithm A
for (int i = 0; i < n; i++) {
    for (int j = 0; j < 1000000; j++) {
        // constant operation
    }
}

// Algorithm B
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        // constant operation
    }
}
```
**Answer**: Algorithm A is O(n), Algorithm B is O(n²). A is faster for large n.

### Problem 3: Space Complexity
What is the space complexity?
```c
int sumArray(int arr[], int n, int index) {
    if (index >= n)
        return 0;
    return arr[index] + sumArray(arr, n, index + 1);
}
```
**Answer**: O(n) - recursion stack depth

### Problem 4: Determine Complexity
```c
void function(int n) {
    for (int i = 1; i < n; i *= 2) {
        for (int j = 0; j < n; j++) {
            printf("%d %d\n", i, j);
        }
    }
}
```
**Answer**: O(n log n) - outer loop is O(log n), inner is O(n)

### Problem 5: Best/Worst Case
Analyze best and worst case:
```c
int search(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key)
            return i;
    }
    return -1;
}
```
**Answer**: Best O(1), Worst O(n)

### Problem 6: Complex Analysis
```c
void function(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i * i; j++) {
            for (int k = 0; k < n; k++) {
                printf("%d", k);
            }
        }
    }
}
```
**Answer**: O(n⁴)

### Problem 7: Logarithmic Complexity
```c
void function(int n) {
    int i = 1;
    while (i < n) {
        printf("%d\n", i);
        i = i * 3;
    }
}
```
**Answer**: O(log₃ n) = O(log n)

### Problem 8: Amortized Analysis
Consider dynamic array doubling. If we insert n elements:
- Most insertions: O(1)
- Doubling operations: O(1) + O(2) + O(4) + ... + O(n/2) + O(n)

What is the amortized cost per insertion?
**Answer**: O(1) amortized

### Problem 9: Multiple Inputs
```c
void function(int arr1[], int n, int arr2[], int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr1[i] == arr2[j])
                printf("Match\n");
        }
    }
}
```
**Answer**: O(n × m)

### Problem 10: Recursive Complexity
```c
int mystery(int n) {
    if (n <= 1)
        return 1;
    return mystery(n/2) + mystery(n/2);
}
```
**Answer**: O(n) - T(n) = 2T(n/2) + O(1)

---

## Summary

| Notation | Meaning | Use Case |
|----------|---------|----------|
| O(g(n))  | Upper bound | Worst-case analysis |
| Ω(g(n))  | Lower bound | Best-case analysis |
| Θ(g(n))  | Tight bound | Average-case analysis |

**Key Takeaways**:
1. Focus on growth rate, not exact operations
2. Drop constants and non-dominant terms
3. Consider input size approaching infinity
4. Analyze best, worst, and average cases
5. Consider both time and space complexity

**Common Complexities** (from best to worst):
O(1) < O(log n) < O(n) < O(n log n) < O(n²) < O(n³) < O(2ⁿ) < O(n!)

---

**Next Topics**: Searching Algorithms, Sorting Algorithms, Recursion
