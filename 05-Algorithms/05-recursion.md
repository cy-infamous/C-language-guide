# Recursion

## Table of Contents
1. [Introduction to Recursion](#introduction)
2. [How Recursion Works](#how-recursion-works)
3. [Base Cases and Recursive Cases](#base-and-recursive-cases)
4. [Classic Recursion Problems](#classic-problems)
5. [Types of Recursion](#types-of-recursion)
6. [Recursion vs Iteration](#recursion-vs-iteration)
7. [Advanced Recursion Techniques](#advanced-techniques)
8. [Practice Problems](#practice-problems)

---

## Introduction to Recursion

**Recursion** is a programming technique where a function calls itself to solve a problem by breaking it down into smaller, similar subproblems.

### Key Concept
```
A recursive function must have:
1. Base case(s): Terminating condition
2. Recursive case(s): Function calling itself with modified parameters
3. Progress toward base case: Each call must move closer to termination
```

### Simple Example
```c
// Countdown example
void countdown(int n) {
    // Base case
    if (n <= 0) {
        printf("Blast off!\n");
        return;
    }

    // Recursive case
    printf("%d\n", n);
    countdown(n - 1);  // Recursive call with smaller problem
}
```

---

## How Recursion Works

### Call Stack Mechanism

When a function calls itself, each call gets its own space on the **call stack**.

**Example**: `factorial(3)`

```
Call Stack Visualization:

Step 1: factorial(3) is called
┌─────────────────┐
│  factorial(3)   │  n = 3, waiting for factorial(2)
└─────────────────┘

Step 2: factorial(3) calls factorial(2)
┌─────────────────┐
│  factorial(2)   │  n = 2, waiting for factorial(1)
├─────────────────┤
│  factorial(3)   │  n = 3, waiting for factorial(2)
└─────────────────┘

Step 3: factorial(2) calls factorial(1)
┌─────────────────┐
│  factorial(1)   │  n = 1, waiting for factorial(0)
├─────────────────┤
│  factorial(2)   │  n = 2, waiting for factorial(1)
├─────────────────┤
│  factorial(3)   │  n = 3, waiting for factorial(2)
└─────────────────┘

Step 4: factorial(1) calls factorial(0)
┌─────────────────┐
│  factorial(0)   │  n = 0, base case! returns 1
├─────────────────┤
│  factorial(1)   │  n = 1, waiting for factorial(0)
├─────────────────┤
│  factorial(2)   │  n = 2, waiting for factorial(1)
├─────────────────┤
│  factorial(3)   │  n = 3, waiting for factorial(2)
└─────────────────┘

Unwinding Phase:

Step 5: factorial(0) returns 1
┌─────────────────┐
│  factorial(1)   │  returns 1 * 1 = 1
├─────────────────┤
│  factorial(2)   │  waiting...
├─────────────────┤
│  factorial(3)   │  waiting...
└─────────────────┘

Step 6: factorial(1) returns 1
┌─────────────────┐
│  factorial(2)   │  returns 2 * 1 = 2
├─────────────────┤
│  factorial(3)   │  waiting...
└─────────────────┘

Step 7: factorial(2) returns 2
┌─────────────────┐
│  factorial(3)   │  returns 3 * 2 = 6
└─────────────────┘

Step 8: factorial(3) returns 6
Stack is empty, result = 6
```

---

## Base Cases and Recursive Cases

### Base Case

The **base case** is the terminating condition that stops recursion.

```c
// Example: Sum of n natural numbers
int sum(int n) {
    // Base case
    if (n == 0) {
        return 0;
    }

    // Recursive case
    return n + sum(n - 1);
}
```

**Common Mistakes**:
```c
// WRONG: No base case → infinite recursion
int sum(int n) {
    return n + sum(n - 1);  // Stack overflow!
}

// WRONG: Base case never reached
int sum(int n) {
    if (n == -1) {        // What if n is positive?
        return 0;
    }
    return n + sum(n - 1);
}
```

### Multiple Base Cases

Some problems require multiple base cases:

```c
// Fibonacci: two base cases
int fibonacci(int n) {
    // Base case 1
    if (n == 0) return 0;

    // Base case 2
    if (n == 1) return 1;

    // Recursive case
    return fibonacci(n - 1) + fibonacci(n - 2);
}
```

---

## Classic Recursion Problems

### 1. Factorial

**Problem**: Calculate n! = n × (n-1) × (n-2) × ... × 1

```c
#include <stdio.h>

// Recursive factorial
int factorial(int n) {
    // Base case
    if (n <= 1) {
        return 1;
    }

    // Recursive case: n! = n × (n-1)!
    return n * factorial(n - 1);
}

// Factorial with trace
int factorialTrace(int n, int depth) {
    // Indentation for visualization
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("factorial(%d) called\n", n);

    if (n <= 1) {
        for (int i = 0; i < depth; i++) {
            printf("  ");
        }
        printf("factorial(%d) returns 1\n", n);
        return 1;
    }

    int result = n * factorialTrace(n - 1, depth + 1);

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("factorial(%d) returns %d\n", n, result);

    return result;
}

// Tail recursive factorial
int factorialTail(int n, int accumulator) {
    if (n <= 1) {
        return accumulator;
    }
    return factorialTail(n - 1, n * accumulator);
}

void demonstrateFactorial() {
    printf("=== FACTORIAL ===\n\n");

    printf("Example 1: Basic Factorial\n");
    for (int i = 0; i <= 5; i++) {
        printf("%d! = %d\n", i, factorial(i));
    }

    printf("\nExample 2: Factorial Trace\n");
    factorialTrace(4, 0);

    printf("\nExample 3: Tail Recursive Factorial\n");
    printf("5! = %d\n", factorialTail(5, 1));
}
```

**Visual Trace for factorial(4)**:
```
factorial(4) called
  factorial(3) called
    factorial(2) called
      factorial(1) called
      factorial(1) returns 1
    factorial(2) returns 2 (2 × 1)
  factorial(3) returns 6 (3 × 2)
factorial(4) returns 24 (4 × 6)
```

**Complexity**:
- Time: O(n)
- Space: O(n) - recursion stack depth

---

### 2. Fibonacci Numbers

**Problem**: Calculate nth Fibonacci number: F(n) = F(n-1) + F(n-2)

```c
#include <stdio.h>
#include <stdlib.h>

// Basic recursive Fibonacci (inefficient)
int fibonacci(int n) {
    // Base cases
    if (n == 0) return 0;
    if (n == 1) return 1;

    // Recursive case
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Fibonacci with call counter
int fibCalls = 0;

int fibonacciCount(int n) {
    fibCalls++;

    if (n == 0) return 0;
    if (n == 1) return 1;

    return fibonacciCount(n - 1) + fibonacciCount(n - 2);
}

// Optimized: Fibonacci with memoization
int fibonacciMemo(int n, int* memo) {
    // Check if already computed
    if (memo[n] != -1) {
        return memo[n];
    }

    // Base cases
    if (n == 0) {
        memo[n] = 0;
        return 0;
    }
    if (n == 1) {
        memo[n] = 1;
        return 1;
    }

    // Compute and store
    memo[n] = fibonacciMemo(n - 1, memo) + fibonacciMemo(n - 2, memo);
    return memo[n];
}

// Visualize Fibonacci recursion tree
void printFibTree(int n, int depth) {
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("fib(%d)\n", n);

    if (n > 1) {
        printFibTree(n - 1, depth + 1);
        printFibTree(n - 2, depth + 1);
    }
}

void demonstrateFibonacci() {
    printf("=== FIBONACCI NUMBERS ===\n\n");

    printf("Example 1: Basic Fibonacci\n");
    printf("First 10 Fibonacci numbers:\n");
    for (int i = 0; i < 10; i++) {
        printf("F(%d) = %d\n", i, fibonacci(i));
    }

    printf("\nExample 2: Recursion Tree (fib(4))\n");
    printFibTree(4, 0);

    printf("\nExample 3: Call Count Comparison\n");
    fibCalls = 0;
    int result1 = fibonacciCount(10);
    printf("fib(10) = %d, calls = %d\n", result1, fibCalls);

    int* memo = (int*)malloc(11 * sizeof(int));
    for (int i = 0; i <= 10; i++) {
        memo[i] = -1;
    }
    fibCalls = 0;
    int result2 = fibonacciMemo(10, memo);
    printf("fib(10) with memoization = %d, much fewer calls!\n", result2);
    free(memo);
}
```

**Recursion Tree for fib(5)**:
```
                    fib(5)
                   /      \
              fib(4)        fib(3)
             /     \        /     \
        fib(3)   fib(2)  fib(2)  fib(1)
        /   \     /   \   /   \
    fib(2) fib(1) f(1) f(0) f(1) f(0)
    /   \
  f(1) f(0)

Notice: fib(3) computed twice, fib(2) computed 3 times!
Total calls: 15 for fib(5)
```

**Complexity**:
- Basic Recursion: O(2ⁿ) time, O(n) space
- With Memoization: O(n) time, O(n) space

---

### 3. Tower of Hanoi

**Problem**: Move n disks from source peg to destination peg using auxiliary peg.

**Rules**:
1. Only one disk can be moved at a time
2. A disk can only be placed on a larger disk
3. Only the top disk of a stack can be moved

```c
#include <stdio.h>

// Tower of Hanoi solution
void towerOfHanoi(int n, char source, char destination, char auxiliary) {
    // Base case: only one disk
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", source, destination);
        return;
    }

    // Step 1: Move n-1 disks from source to auxiliary (using destination)
    towerOfHanoi(n - 1, source, auxiliary, destination);

    // Step 2: Move nth disk from source to destination
    printf("Move disk %d from %c to %c\n", n, source, destination);

    // Step 3: Move n-1 disks from auxiliary to destination (using source)
    towerOfHanoi(n - 1, auxiliary, destination, source);
}

// Tower of Hanoi with move counter
int moveCount = 0;

void towerOfHanoiCount(int n, char source, char destination, char auxiliary) {
    if (n == 1) {
        moveCount++;
        return;
    }

    towerOfHanoiCount(n - 1, source, auxiliary, destination);
    moveCount++;
    towerOfHanoiCount(n - 1, auxiliary, destination, source);
}

void demonstrateTowerOfHanoi() {
    printf("=== TOWER OF HANOI ===\n\n");

    printf("Example 1: Solution for 3 disks\n");
    towerOfHanoi(3, 'A', 'C', 'B');

    printf("\nExample 2: Move count for different disk numbers\n");
    for (int i = 1; i <= 5; i++) {
        moveCount = 0;
        towerOfHanoiCount(i, 'A', 'C', 'B');
        printf("%d disks: %d moves (2^%d - 1 = %d)\n",
               i, moveCount, i, (1 << i) - 1);
    }
}
```

**Visual Trace for 3 Disks**:
```
Initial State:
A: [3, 2, 1]    B: []           C: []

Steps:
1. Move disk 1 from A to C
   A: [3, 2]    B: []           C: [1]

2. Move disk 2 from A to B
   A: [3]       B: [2]          C: [1]

3. Move disk 1 from C to B
   A: [3]       B: [2, 1]       C: []

4. Move disk 3 from A to C
   A: []        B: [2, 1]       C: [3]

5. Move disk 1 from B to A
   A: [1]       B: [2]          C: [3]

6. Move disk 2 from B to C
   A: [1]       B: []           C: [3, 2]

7. Move disk 1 from A to C
   A: []        B: []           C: [3, 2, 1]

Final State: All disks on peg C
```

**Complexity**:
- Time: O(2ⁿ) - exactly 2ⁿ - 1 moves
- Space: O(n) - recursion depth

---

### 4. Sum of Array Elements

```c
#include <stdio.h>

// Recursive sum
int sumArray(int arr[], int n) {
    // Base case
    if (n == 0) {
        return 0;
    }

    // Recursive case
    return arr[n - 1] + sumArray(arr, n - 1);
}

// Alternative: using index
int sumArrayIndex(int arr[], int n, int index) {
    if (index >= n) {
        return 0;
    }

    return arr[index] + sumArrayIndex(arr, n, index + 1);
}

void demonstrateSumArray() {
    printf("=== SUM OF ARRAY ===\n\n");

    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Sum: %d\n", sumArray(arr, n));
    printf("Sum (index version): %d\n", sumArrayIndex(arr, n, 0));
}
```

---

### 5. Power Function

```c
#include <stdio.h>

// Basic recursive power
int power(int base, int exp) {
    // Base case
    if (exp == 0) {
        return 1;
    }

    // Recursive case
    return base * power(base, exp - 1);
}

// Optimized: Fast exponentiation
// Uses: a^n = (a^(n/2))^2 if n is even
//       a^n = a × a^(n-1) if n is odd
int powerFast(int base, int exp) {
    if (exp == 0) {
        return 1;
    }

    int half = powerFast(base, exp / 2);

    if (exp % 2 == 0) {
        return half * half;
    } else {
        return base * half * half;
    }
}

void demonstratePower() {
    printf("=== POWER FUNCTION ===\n\n");

    printf("Basic power:\n");
    printf("2^5 = %d\n", power(2, 5));
    printf("3^4 = %d\n", power(3, 4));

    printf("\nFast exponentiation:\n");
    printf("2^10 = %d\n", powerFast(2, 10));
    printf("5^6 = %d\n", powerFast(5, 6));
}
```

**Complexity**:
- Basic: O(n) time, O(n) space
- Fast: O(log n) time, O(log n) space

---

### 6. GCD (Greatest Common Divisor)

```c
#include <stdio.h>

// Euclidean algorithm
int gcd(int a, int b) {
    // Base case
    if (b == 0) {
        return a;
    }

    // Recursive case: GCD(a, b) = GCD(b, a % b)
    return gcd(b, a % b);
}

// GCD with trace
int gcdTrace(int a, int b) {
    printf("gcd(%d, %d)\n", a, b);

    if (b == 0) {
        printf("  Base case reached, return %d\n", a);
        return a;
    }

    return gcdTrace(b, a % b);
}

void demonstrateGCD() {
    printf("=== GCD (EUCLIDEAN ALGORITHM) ===\n\n");

    printf("Example 1: GCD(48, 18)\n");
    printf("Result: %d\n\n", gcd(48, 18));

    printf("Example 2: GCD with trace\n");
    gcdTrace(48, 18);
}
```

---

### 7. String Reversal

```c
#include <stdio.h>
#include <string.h>

// Recursive string reversal
void reverseString(char str[], int start, int end) {
    // Base case
    if (start >= end) {
        return;
    }

    // Swap characters
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;

    // Recursive case
    reverseString(str, start + 1, end - 1);
}

// Check if palindrome
int isPalindrome(char str[], int start, int end) {
    // Base case
    if (start >= end) {
        return 1;
    }

    // If characters don't match
    if (str[start] != str[end]) {
        return 0;
    }

    // Recursive case
    return isPalindrome(str, start + 1, end - 1);
}

void demonstrateStringRecursion() {
    printf("=== STRING RECURSION ===\n\n");

    char str1[] = "hello";
    printf("Original: %s\n", str1);
    reverseString(str1, 0, strlen(str1) - 1);
    printf("Reversed: %s\n\n", str1);

    char str2[] = "racecar";
    printf("Is '%s' a palindrome? %s\n",
           str2, isPalindrome(str2, 0, strlen(str2) - 1) ? "Yes" : "No");

    char str3[] = "hello";
    printf("Is '%s' a palindrome? %s\n",
           str3, isPalindrome(str3, 0, strlen(str3) - 1) ? "Yes" : "No");
}
```

---

### 8. Binary Search (Recursive)

```c
#include <stdio.h>

// Recursive binary search
int binarySearch(int arr[], int left, int right, int key) {
    // Base case: element not found
    if (left > right) {
        return -1;
    }

    int mid = left + (right - left) / 2;

    // Base case: element found
    if (arr[mid] == key) {
        return mid;
    }

    // Recursive cases
    if (arr[mid] > key) {
        return binarySearch(arr, left, mid - 1, key);
    } else {
        return binarySearch(arr, mid + 1, right, key);
    }
}

void demonstrateBinarySearch() {
    printf("=== RECURSIVE BINARY SEARCH ===\n\n");

    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int key = 23;
    int result = binarySearch(arr, 0, n - 1, key);

    if (result != -1) {
        printf("Element %d found at index %d\n", key, result);
    } else {
        printf("Element %d not found\n", key);
    }
}
```

---

## Types of Recursion

### 1. Direct Recursion

Function calls itself directly.

```c
void directRecursion(int n) {
    if (n > 0) {
        printf("%d ", n);
        directRecursion(n - 1);  // Direct call to itself
    }
}
```

### 2. Indirect Recursion

Function A calls function B, which calls function A.

```c
void functionB(int n);  // Forward declaration

void functionA(int n) {
    if (n > 0) {
        printf("%d ", n);
        functionB(n - 1);  // Calls B
    }
}

void functionB(int n) {
    if (n > 1) {
        printf("%d ", n);
        functionA(n / 2);  // Calls A
    }
}
```

### 3. Tail Recursion

Recursive call is the last operation in the function.

```c
// Tail recursive (can be optimized by compiler)
int factorialTail(int n, int acc) {
    if (n == 0) return acc;
    return factorialTail(n - 1, n * acc);  // Last operation
}

// Non-tail recursive
int factorialNonTail(int n) {
    if (n == 0) return 1;
    return n * factorialNonTail(n - 1);  // Multiplication after return
}
```

### 4. Head Recursion

Recursive call is the first operation.

```c
void headRecursion(int n) {
    if (n > 0) {
        headRecursion(n - 1);  // Recursive call first
        printf("%d ", n);       // Then operation
    }
}
// Output for headRecursion(5): 1 2 3 4 5
```

### 5. Tree Recursion

Function makes multiple recursive calls.

```c
void treeRecursion(int n) {
    if (n > 0) {
        printf("%d ", n);
        treeRecursion(n - 1);  // First recursive call
        treeRecursion(n - 1);  // Second recursive call
    }
}
```

### 6. Nested Recursion

Recursive call uses another recursive call as parameter.

```c
int nestedRecursion(int n) {
    if (n > 100) {
        return n - 10;
    }
    return nestedRecursion(nestedRecursion(n + 11));
}
```

---

## Recursion vs Iteration

### Comparison

| Aspect | Recursion | Iteration |
|--------|-----------|-----------|
| Definition | Function calls itself | Loop repeats code |
| Termination | Base case | Loop condition |
| Memory | Stack space (O(n)) | Constant space (O(1)) |
| Speed | Slower (function call overhead) | Faster |
| Code | Often shorter, cleaner | Sometimes longer |
| Use Case | Tree/graph traversal, divide-and-conquer | Simple loops, counters |

### Same Problem, Both Approaches

```c
#include <stdio.h>

// Recursive factorial
int factorialRecursive(int n) {
    if (n <= 1) return 1;
    return n * factorialRecursive(n - 1);
}

// Iterative factorial
int factorialIterative(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Recursive Fibonacci
int fibRecursive(int n) {
    if (n <= 1) return n;
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

// Iterative Fibonacci
int fibIterative(int n) {
    if (n <= 1) return n;

    int a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        int temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}
```

### When to Use Recursion

**Use Recursion When**:
1. Problem naturally recursive (tree traversal, graph DFS)
2. Divide and conquer algorithms
3. Code clarity is priority
4. Stack space is available

**Use Iteration When**:
1. Simple counting/looping
2. Memory is limited
3. Performance is critical
4. Tail recursion not optimized by compiler

---

## Advanced Recursion Techniques

### 1. Memoization (Top-Down DP)

Store results of expensive function calls.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fibonacci with memoization
int fibMemo(int n, int* memo) {
    if (memo[n] != -1) {
        return memo[n];
    }

    if (n <= 1) {
        memo[n] = n;
        return n;
    }

    memo[n] = fibMemo(n - 1, memo) + fibMemo(n - 2, memo);
    return memo[n];
}

int fibonacci(int n) {
    int* memo = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
        memo[i] = -1;
    }

    int result = fibMemo(n, memo);
    free(memo);
    return result;
}
```

### 2. Tail Call Optimization

Convert to tail recursion for compiler optimization.

```c
// Non-tail recursive
int sumNonTail(int n) {
    if (n == 0) return 0;
    return n + sumNonTail(n - 1);  // Addition after recursive call
}

// Tail recursive
int sumTail(int n, int acc) {
    if (n == 0) return acc;
    return sumTail(n - 1, acc + n);  // Recursive call is last operation
}
```

### 3. Backtracking Template

General template for backtracking problems.

```c
void backtrack(/* parameters */) {
    // Base case: solution found
    if (/* base condition */) {
        // Process solution
        return;
    }

    // Try all choices
    for (/* each choice */) {
        // Make choice
        // ...

        // Recurse with choice
        backtrack(/* modified parameters */);

        // Undo choice (backtrack)
        // ...
    }
}
```

---

## Practice Problems

### Problem 1: Sum of Digits
Write recursive function to find sum of digits of a number.
Example: sumDigits(1234) = 1 + 2 + 3 + 4 = 10

### Problem 2: Print N to 1
Print numbers from n to 1 using recursion.

### Problem 3: Print 1 to N
Print numbers from 1 to n using recursion.

### Problem 4: Decimal to Binary
Convert decimal number to binary using recursion.

### Problem 5: Count Zeros
Count number of zeros in a number using recursion.
Example: countZeros(10204) = 2

### Problem 6: First Uppercase
Find index of first uppercase letter in string using recursion.

### Problem 7: Array Maximum
Find maximum element in array using recursion.

### Problem 8: Linear Search
Implement linear search using recursion.

### Problem 9: Sort Array
Sort array using recursion (any algorithm).

### Problem 10: Generate Subsets
Generate all subsets of a set using recursion.

---

## Common Recursion Mistakes

### Mistake 1: No Base Case
```c
// WRONG: Infinite recursion
int factorial(int n) {
    return n * factorial(n - 1);  // No base case!
}
```

### Mistake 2: Wrong Progress
```c
// WRONG: Never reaches base case
int countdown(int n) {
    if (n == 0) return;
    printf("%d\n", n);
    countdown(n + 1);  // Going wrong direction!
}
```

### Mistake 3: Multiple Returns Not Handled
```c
// WRONG: Doesn't combine results
int fibonacci(int n) {
    if (n <= 1) return n;
    fibonacci(n - 1);
    fibonacci(n - 2);  // Results not combined!
}

// CORRECT:
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
```

---

## Summary

### Key Points
1. **Base case** is essential to stop recursion
2. Each recursive call must progress toward base case
3. Recursion uses **call stack** - limited by stack size
4. Consider **memoization** for overlapping subproblems
5. Convert to **iteration** if performance critical

### Complexity Patterns
- **Linear recursion**: O(n) time, O(n) space
- **Binary recursion**: O(2ⁿ) time, O(n) space
- **Divide and conquer**: O(n log n) time, O(log n) space

### Best Practices
1. Always define clear base case(s)
2. Ensure progress toward base case
3. Consider iterative alternative
4. Use memoization for repeated calculations
5. Watch for stack overflow with deep recursion

---

**Next Topic**: Divide and Conquer Algorithms
