# Dynamic Programming

## Table of Contents
1. [Introduction to Dynamic Programming](#introduction)
2. [Key Concepts](#key-concepts)
3. [Memoization vs Tabulation](#memoization-vs-tabulation)
4. [Classic DP Problems](#classic-problems)
5. [DP Patterns](#dp-patterns)
6. [Practice Problems](#practice-problems)

---

## Introduction to Dynamic Programming

**Dynamic Programming (DP)** is an optimization technique that solves complex problems by breaking them down into simpler subproblems and storing their solutions to avoid redundant calculations.

### Core Idea
```
Instead of recomputing same subproblems:
1. Solve each subproblem once
2. Store the solution
3. Reuse when needed
```

### When to Use DP
A problem has:
1. **Optimal Substructure**: Optimal solution contains optimal solutions to subproblems
2. **Overlapping Subproblems**: Same subproblems solved multiple times

### DP vs Divide & Conquer
| Aspect | Divide & Conquer | Dynamic Programming |
|--------|------------------|---------------------|
| Subproblems | Independent | Overlapping |
| Recomputation | Yes | No (memoized) |
| Examples | Merge Sort | Fibonacci (DP) |

---

## Key Concepts

### 1. Overlapping Subproblems

**Example**: Fibonacci
```
fib(5) calls fib(4) and fib(3)
fib(4) calls fib(3) and fib(2)
fib(3) is computed twice!

Recursion tree:
                    fib(5)
                   /      \
              fib(4)       fib(3)
             /     \       /     \
        fib(3)   fib(2)  fib(2) fib(1)
        /   \     /   \
    fib(2) fib(1) ...
```

### 2. Optimal Substructure

If optimal solution to problem contains optimal solutions to subproblems.

**Example**: Shortest path
- Shortest path from A to C through B = shortest(A→B) + shortest(B→C)

---

## Memoization vs Tabulation

### Memoization (Top-Down)

Start with original problem, recursively solve and cache results.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Memoization: Top-down approach
int fibMemo(int n, int* memo) {
    // Base cases
    if (n <= 1) {
        return n;
    }

    // Check if already computed
    if (memo[n] != -1) {
        return memo[n];
    }

    // Compute and store
    memo[n] = fibMemo(n - 1, memo) + fibMemo(n - 2, memo);
    return memo[n];
}

int fibonacciMemoization(int n) {
    int* memo = (int*)malloc((n + 1) * sizeof(int));

    // Initialize with -1 (not computed)
    for (int i = 0; i <= n; i++) {
        memo[i] = -1;
    }

    int result = fibMemo(n, memo);
    free(memo);
    return result;
}
```

### Tabulation (Bottom-Up)

Start with smallest subproblems, build up to original problem.

```c
// Tabulation: Bottom-up approach
int fibonacciTabulation(int n) {
    if (n <= 1) return n;

    int* dp = (int*)malloc((n + 1) * sizeof(int));

    // Base cases
    dp[0] = 0;
    dp[1] = 1;

    // Build up from bottom
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    int result = dp[n];
    free(dp);
    return result;
}

// Space optimized: O(1) space
int fibonacciOptimized(int n) {
    if (n <= 1) return n;

    int prev2 = 0, prev1 = 1;

    for (int i = 2; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}
```

### Comparison

| Aspect | Memoization | Tabulation |
|--------|-------------|------------|
| Approach | Top-down | Bottom-up |
| Implementation | Recursive | Iterative |
| Space | Recursion stack + memo | Only table |
| Computation | Only needed subproblems | All subproblems |
| Easier for | Recursive problems | Iterative thinking |

---

## Classic DP Problems

### 1. 0/1 Knapsack Problem

**Problem**: Maximize value in knapsack without exceeding capacity.

```c
#include <stdio.h>
#include <stdlib.h>

// Recursive approach (exponential)
int knapsackRecursive(int W, int wt[], int val[], int n) {
    // Base case
    if (n == 0 || W == 0) {
        return 0;
    }

    // If weight exceeds capacity
    if (wt[n - 1] > W) {
        return knapsackRecursive(W, wt, val, n - 1);
    }

    // Return max of including or excluding item
    int include = val[n - 1] + knapsackRecursive(W - wt[n - 1], wt, val, n - 1);
    int exclude = knapsackRecursive(W, wt, val, n - 1);

    return (include > exclude) ? include : exclude;
}

// Memoization approach
int knapsackMemo(int W, int wt[], int val[], int n, int** memo) {
    if (n == 0 || W == 0) {
        return 0;
    }

    // Check memo
    if (memo[n][W] != -1) {
        return memo[n][W];
    }

    if (wt[n - 1] > W) {
        memo[n][W] = knapsackMemo(W, wt, val, n - 1, memo);
    } else {
        int include = val[n - 1] + knapsackMemo(W - wt[n - 1], wt, val, n - 1, memo);
        int exclude = knapsackMemo(W, wt, val, n - 1, memo);
        memo[n][W] = (include > exclude) ? include : exclude;
    }

    return memo[n][W];
}

// Tabulation approach
int knapsackDP(int W, int wt[], int val[], int n) {
    // Create DP table
    int** dp = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)malloc((W + 1) * sizeof(int));
    }

    // Build table bottom-up
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (wt[i - 1] <= w) {
                int include = val[i - 1] + dp[i - 1][w - wt[i - 1]];
                int exclude = dp[i - 1][w];
                dp[i][w] = (include > exclude) ? include : exclude;
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int result = dp[n][W];

    // Print DP table
    printf("\nDP Table:\n");
    printf("     ");
    for (int w = 0; w <= W; w++) {
        printf("%3d ", w);
    }
    printf("\n");

    for (int i = 0; i <= n; i++) {
        printf("i=%d: ", i);
        for (int w = 0; w <= W; w++) {
            printf("%3d ", dp[i][w]);
        }
        printf("\n");
    }

    // Free memory
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

void demonstrateKnapsack() {
    printf("=== 0/1 KNAPSACK PROBLEM ===\n\n");

    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int W = 50;
    int n = sizeof(val) / sizeof(val[0]);

    printf("Items (value, weight):\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d: value=%d, weight=%d\n", i + 1, val[i], wt[i]);
    }
    printf("Knapsack capacity: %d\n", W);

    int maxValue = knapsackDP(W, wt, val, n);
    printf("\nMaximum value: %d\n", maxValue);
}
```

**Time Complexity**: O(n × W)
**Space Complexity**: O(n × W)

---

### 2. Longest Common Subsequence (LCS)

**Problem**: Find length of longest subsequence common to two strings.

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Recursive LCS (exponential)
int lcsRecursive(char* X, char* Y, int m, int n) {
    if (m == 0 || n == 0) {
        return 0;
    }

    if (X[m - 1] == Y[n - 1]) {
        return 1 + lcsRecursive(X, Y, m - 1, n - 1);
    } else {
        int left = lcsRecursive(X, Y, m, n - 1);
        int right = lcsRecursive(X, Y, m - 1, n);
        return (left > right) ? left : right;
    }
}

// DP LCS with table
int lcsDP(char* X, char* Y, int m, int n) {
    // Create DP table
    int** dp = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int*)malloc((n + 1) * sizeof(int));
    }

    // Build LCS table
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ?
                           dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    // Print DP table
    printf("\nLCS Table:\n");
    printf("    ");
    for (int j = 0; j <= n; j++) {
        if (j == 0) {
            printf("ε ");
        } else {
            printf("%c ", Y[j - 1]);
        }
    }
    printf("\n");

    for (int i = 0; i <= m; i++) {
        if (i == 0) {
            printf("ε   ");
        } else {
            printf("%c   ", X[i - 1]);
        }

        for (int j = 0; j <= n; j++) {
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }

    int result = dp[m][n];

    // Reconstruct LCS
    printf("\nReconstructing LCS:\n");
    int index = result;
    char* lcs = (char*)malloc((index + 1) * sizeof(char));
    lcs[index] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("LCS: %s\n", lcs);

    // Free memory
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);
    free(lcs);

    return result;
}

void demonstrateLCS() {
    printf("=== LONGEST COMMON SUBSEQUENCE ===\n\n");

    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";

    printf("String X: %s\n", X);
    printf("String Y: %s\n", Y);

    int m = strlen(X);
    int n = strlen(Y);

    int length = lcsDP(X, Y, m, n);
    printf("\nLength of LCS: %d\n", length);
}
```

**Time Complexity**: O(m × n)
**Space Complexity**: O(m × n)

---

### 3. Longest Increasing Subsequence (LIS)

```c
#include <stdio.h>
#include <stdlib.h>

// DP approach for LIS
int lisDP(int arr[], int n) {
    // dp[i] = length of LIS ending at index i
    int* dp = (int*)malloc(n * sizeof(int));

    // Initialize all dp values as 1
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    // Compute LIS values
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
            }
        }
    }

    // Find maximum value in dp array
    int maxLength = 0;
    int maxIndex = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] > maxLength) {
            maxLength = dp[i];
            maxIndex = i;
        }
    }

    // Print DP array
    printf("DP array (LIS length ending at each index):\n");
    for (int i = 0; i < n; i++) {
        printf("arr[%d]=%d: LIS length=%d\n", i, arr[i], dp[i]);
    }

    // Reconstruct LIS
    printf("\nOne possible LIS:\n");
    int* lis = (int*)malloc(maxLength * sizeof(int));
    int k = maxLength - 1;
    int currLength = maxLength;
    int currValue = arr[maxIndex];

    lis[k--] = arr[maxIndex];
    currLength--;

    for (int i = maxIndex - 1; i >= 0 && currLength > 0; i--) {
        if (dp[i] == currLength && arr[i] < currValue) {
            lis[k--] = arr[i];
            currValue = arr[i];
            currLength--;
        }
    }

    for (int i = 0; i < maxLength; i++) {
        printf("%d ", lis[i]);
    }
    printf("\n");

    free(dp);
    free(lis);

    return maxLength;
}

void demonstrateLIS() {
    printf("=== LONGEST INCREASING SUBSEQUENCE ===\n\n");

    int arr[] = {10, 9, 2, 5, 3, 7, 101, 18};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    int length = lisDP(arr, n);
    printf("\nLength of LIS: %d\n", length);
}
```

**Time Complexity**: O(n²)
**Space Complexity**: O(n)

---

### 4. Edit Distance (Levenshtein Distance)

**Problem**: Minimum operations (insert, delete, replace) to convert one string to another.

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

// Edit Distance DP
int editDistanceDP(char* str1, char* str2, int m, int n) {
    // Create DP table
    int** dp = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int*)malloc((n + 1) * sizeof(int));
    }

    // Fill table
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            // Empty string
            if (i == 0) {
                dp[i][j] = j;  // Insert j characters
            } else if (j == 0) {
                dp[i][j] = i;  // Delete i characters
            }
            // Last characters match
            else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            // Last characters don't match
            else {
                dp[i][j] = 1 + min(
                    dp[i][j - 1],      // Insert
                    dp[i - 1][j],      // Delete
                    dp[i - 1][j - 1]   // Replace
                );
            }
        }
    }

    int result = dp[m][n];

    // Free memory
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

void demonstrateEditDistance() {
    printf("=== EDIT DISTANCE ===\n\n");

    char str1[] = "sunday";
    char str2[] = "saturday";

    printf("String 1: %s\n", str1);
    printf("String 2: %s\n", str2);

    int m = strlen(str1);
    int n = strlen(str2);

    int distance = editDistanceDP(str1, str2, m, n);

    printf("\nMinimum edit distance: %d\n", distance);
    printf("Operations: Insert, Delete, Replace\n");
}
```

**Time Complexity**: O(m × n)
**Space Complexity**: O(m × n)

---

### 5. Coin Change Problem

```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Minimum coins needed
int coinChangeDP(int coins[], int n, int amount) {
    int* dp = (int*)malloc((amount + 1) * sizeof(int));

    // Initialize
    dp[0] = 0;
    for (int i = 1; i <= amount; i++) {
        dp[i] = INT_MAX;
    }

    // Fill DP table
    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX) {
                if (dp[i] > dp[i - coins[j]] + 1) {
                    dp[i] = dp[i - coins[j]] + 1;
                }
            }
        }
    }

    int result = (dp[amount] == INT_MAX) ? -1 : dp[amount];
    free(dp);
    return result;
}

// Number of ways to make change
int coinChangeWays(int coins[], int n, int amount) {
    int* dp = (int*)malloc((amount + 1) * sizeof(int));

    // Initialize
    dp[0] = 1;  // One way to make 0: use no coins
    for (int i = 1; i <= amount; i++) {
        dp[i] = 0;
    }

    // For each coin
    for (int i = 0; i < n; i++) {
        // Update all amounts >= coin value
        for (int j = coins[i]; j <= amount; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }

    int result = dp[amount];
    free(dp);
    return result;
}

void demonstrateCoinChange() {
    printf("=== COIN CHANGE PROBLEM ===\n\n");

    int coins[] = {1, 2, 5};
    int n = sizeof(coins) / sizeof(coins[0]);
    int amount = 11;

    printf("Coins: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", coins[i]);
    }
    printf("\nAmount: %d\n", amount);

    int minCoins = coinChangeDP(coins, n, amount);
    printf("\nMinimum coins needed: %d\n", minCoins);

    int ways = coinChangeWays(coins, n, amount);
    printf("Number of ways: %d\n", ways);
}
```

---

### 6. Matrix Chain Multiplication

**Problem**: Find optimal order to multiply matrices to minimize operations.

```c
#include <stdio.h>
#include <limits.h>

// Print optimal parenthesization
void printOptimalParens(int s[][10], int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimalParens(s, i, s[i][j]);
        printOptimalParens(s, s[i][j] + 1, j);
        printf(")");
    }
}

// Matrix Chain Multiplication DP
int matrixChainDP(int p[], int n) {
    // n = number of matrices
    // p[] = dimensions array (matrix i has dimensions p[i-1] × p[i])

    int m[10][10];  // m[i][j] = minimum operations for matrices i to j
    int s[10][10];  // s[i][j] = split point for optimal solution

    // Cost is 0 for single matrix
    for (int i = 1; i < n; i++) {
        m[i][i] = 0;
    }

    // L = chain length
    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;

            // Try all possible split points
            for (int k = i; k < j; k++) {
                int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];

                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("Optimal parenthesization: ");
    printOptimalParens(s, 1, n - 1);
    printf("\n");

    return m[1][n - 1];
}

void demonstrateMatrixChain() {
    printf("=== MATRIX CHAIN MULTIPLICATION ===\n\n");

    int arr[] = {40, 20, 30, 10, 30};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Matrix dimensions:\n");
    for (int i = 1; i < n; i++) {
        printf("A%d: %d × %d\n", i, arr[i - 1], arr[i]);
    }

    int minOps = matrixChainDP(arr, n);
    printf("\nMinimum operations: %d\n", minOps);
}
```

---

## DP Patterns

### 1. Linear DP
- One-dimensional state
- Examples: Fibonacci, climbing stairs, house robber

### 2. Grid DP
- Two-dimensional state
- Examples: Unique paths, minimum path sum

### 3. Subsequence DP
- LCS, LIS, edit distance

### 4. Knapsack DP
- 0/1 knapsack, unbounded knapsack, subset sum

### 5. Interval DP
- Matrix chain multiplication, palindrome partitioning

### 6. Tree DP
- DP on trees, diameter of tree

---

## Practice Problems

### Problem 1: Climbing Stairs
Count ways to reach top of stairs (1 or 2 steps at a time).

### Problem 2: House Robber
Maximum money from houses without robbing adjacent ones.

### Problem 3: Maximum Subarray Sum (Kadane's)
Find contiguous subarray with maximum sum.

### Problem 4: Unique Paths
Count unique paths in grid from top-left to bottom-right.

### Problem 5: Partition Equal Subset Sum
Partition array into two subsets with equal sum.

### Problem 6: Longest Palindromic Subsequence
Find length of longest palindromic subsequence.

### Problem 7: Word Break
Determine if string can be segmented into dictionary words.

### Problem 8: Egg Drop Problem
Minimum trials needed to find critical floor.

### Problem 9: Palindrome Partitioning
Minimum cuts needed to partition string into palindromes.

### Problem 10: Best Time to Buy and Sell Stock
Maximum profit from stock transactions with constraints.

---

## Summary

### Key Takeaways
1. **Identify overlapping subproblems**
2. **Choose memoization or tabulation**
3. **Define state and transitions**
4. **Optimize space when possible**

### DP Checklist
- [ ] Identify optimal substructure
- [ ] Find overlapping subproblems
- [ ] Define state representation
- [ ] Write recurrence relation
- [ ] Decide top-down or bottom-up
- [ ] Implement and optimize

### Common Pitfalls
- Not initializing base cases correctly
- Wrong state transitions
- Off-by-one errors in indices
- Forgetting to free allocated memory

---

**Next Topic**: Backtracking
