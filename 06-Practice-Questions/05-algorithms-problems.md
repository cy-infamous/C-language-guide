# C Programming - Algorithms Problems

This file contains 30 comprehensive problems covering searching, sorting, recursion, dynamic programming, greedy algorithms, and backtracking.

---

## Searching Algorithms (Problems 1-5)

## Problem 1: Linear Search with Statistics
**Difficulty:** Easy
**Topics:** Searching, Arrays

### Problem Statement
Implement linear search and report number of comparisons made, best/worst/average case scenarios.

### Input Format
```
N (array size)
N space-separated integers
Q (number of queries)
Q search values
```

### Output Format
For each query: position (or -1) and number of comparisons.

### Constraints
- 1 ≤ N ≤ 10000
- 1 ≤ Q ≤ 100

### Example Test Cases

**Test Case 1:**
```
Input:
5
10 20 30 40 50
3
30
60
10
Output:
30 found at index 2, comparisons: 3
60 not found, comparisons: 5
10 found at index 0, comparisons: 1
```

<details>
<summary>Hint</summary>
Count comparisons in each search. Best case: element at first position (1 comparison). Worst case: element not present or at last position (N comparisons). Average: N/2.
</details>

---

## Problem 2: Binary Search - Iterative and Recursive
**Difficulty:** Medium
**Topics:** Binary Search, Recursion

### Problem Statement
Implement both iterative and recursive versions of binary search. Compare their performance.

### Input Format
```
N (array size)
N sorted integers
Q (queries)
Q search values
```

### Output Format
```
Value: [found/not found], Position: [index], Method: [iterative/recursive]
```

### Constraints
- 1 ≤ N ≤ 10^6
- Array is sorted

### Example Test Cases

**Test Case 1:**
```
Input:
7
1 3 5 7 9 11 13
2
7
8
Output:
Iterative: 7 found at index 3
Recursive: 7 found at index 3
Iterative: 8 not found
Recursive: 8 not found
```

<details>
<summary>Hint</summary>
Iterative: Use while loop with low and high pointers.
Recursive: Base case: low > high (not found) or arr[mid] == target (found). Recursive case: search left or right half.
</details>

---

## Problem 3: Jump Search
**Difficulty:** Medium
**Topics:** Searching Algorithms

### Problem Statement
Implement jump search algorithm which works on sorted arrays by jumping ahead by fixed steps.

### Input Format
```
N (array size)
N sorted integers
Search value
```

### Output Format
```
Element found at index [pos] with [jumps] jumps
```

### Constraints
- 1 ≤ N ≤ 10^6
- Sorted array

### Example Test Cases

**Test Case 1:**
```
Input:
10
1 2 3 4 5 6 7 8 9 10
6
Output:
Element 6 found at index 5 after 2 jumps
```

<details>
<summary>Hint</summary>
Optimal jump size: √N. Jump ahead by step size, when element is greater than target, do linear search in previous block. Time complexity: O(√N).
</details>

---

## Problem 4: Interpolation Search
**Difficulty:** Medium
**Topics:** Searching Algorithms

### Problem Statement
Implement interpolation search which works better than binary search for uniformly distributed sorted data.

### Input Format
```
N (array size)
N sorted integers (uniformly distributed)
Search value
```

### Output Format
```
Element found at index [pos], comparisons: [count]
```

### Constraints
- 1 ≤ N ≤ 10^6
- Sorted array with uniform distribution

### Example Test Cases

**Test Case 1:**
```
Input:
10
10 20 30 40 50 60 70 80 90 100
70
Output:
Element 70 found at index 6, comparisons: 2
```

<details>
<summary>Hint</summary>
Instead of always checking middle, estimate position based on value:
pos = low + [(x - arr[low]) * (high - low)] / (arr[high] - arr[low])
Better than binary search for uniformly distributed data: O(log log N).
</details>

---

## Problem 5: Find Peak Element
**Difficulty:** Medium
**Topics:** Binary Search, Array

### Problem Statement
Find a peak element in an array. A peak element is greater than or equal to its neighbors.

### Input Format
```
N (array size)
N integers
```

### Output Format
```
Peak element: [value] at index [pos]
```

### Constraints
- 1 ≤ N ≤ 10^6
- Multiple peaks may exist, find any one

### Example Test Cases

**Test Case 1:**
```
Input:
7
1 3 20 4 1 0 5
Output:
Peak element: 20 at index 2
```

**Test Case 2:**
```
Input:
5
5 10 20 15 7
Output:
Peak element: 20 at index 2
```

<details>
<summary>Hint</summary>
Use binary search approach. If arr[mid] > arr[mid+1], peak lies in left half (including mid). Otherwise, peak is in right half. Time: O(log N).
</details>

---

## Sorting Algorithms (Problems 6-12)

## Problem 6: Comparison of Basic Sorting Algorithms
**Difficulty:** Medium
**Topics:** Sorting, Algorithm Analysis

### Problem Statement
Implement and compare bubble sort, selection sort, and insertion sort. Measure comparisons and swaps.

### Input Format
```
N (array size)
N integers
```

### Output Format
```
Original array: [elements]
For each algorithm:
  Sorted array: [elements]
  Comparisons: [count]
  Swaps: [count]
  Time: [milliseconds]
```

### Constraints
- 1 ≤ N ≤ 5000

### Example Test Cases

**Test Case 1:**
```
Input:
5
64 34 25 12 22
Output:
Original: 64 34 25 12 22

Bubble Sort: 12 22 25 34 64
Comparisons: 10, Swaps: 8

Selection Sort: 12 22 25 34 64
Comparisons: 10, Swaps: 4

Insertion Sort: 12 22 25 34 64
Comparisons: 8, Swaps: 8
```

<details>
<summary>Hint</summary>
Add counters for comparisons and swaps in each algorithm. Use clock() function for timing. Best for insertion sort: already sorted O(N). Worst for bubble: reverse sorted O(N²).
</details>

---

## Problem 7: Merge Sort
**Difficulty:** Medium
**Topics:** Divide and Conquer, Sorting

### Problem Statement
Implement merge sort algorithm and analyze its performance.

### Input Format
```
N (array size)
N integers
```

### Output Format
```
Original: [elements]
Sorted: [elements]
Merge operations: [count]
```

### Constraints
- 1 ≤ N ≤ 10^6

### Example Test Cases

**Test Case 1:**
```
Input:
8
38 27 43 3 9 82 10 1
Output:
Original: 38 27 43 3 9 82 10 1
Sorted: 1 3 9 10 27 38 43 82
Merge operations: 7
```

<details>
<summary>Hint</summary>
Divide array into two halves, recursively sort each half, merge sorted halves. Merge: compare elements from both halves, add smaller to result. Time: O(N log N), Space: O(N).
</details>

---

## Problem 8: Quick Sort
**Difficulty:** Medium
**Topics:** Divide and Conquer, Sorting

### Problem Statement
Implement quick sort with different pivot selection strategies (first, last, median, random).

### Input Format
```
N (array size)
N integers
Pivot strategy: FIRST/LAST/MEDIAN/RANDOM
```

### Output Format
```
Sorted array: [elements]
Partitions: [count]
Recursion depth: [depth]
```

### Constraints
- 1 ≤ N ≤ 10^6

### Example Test Cases

**Test Case 1:**
```
Input:
7
10 7 8 9 1 5 6
LAST
Output:
Sorted: 1 5 6 7 8 9 10
Partitions: 7
Max recursion depth: 4
```

<details>
<summary>Hint</summary>
Choose pivot, partition array (elements < pivot on left, > pivot on right), recursively sort left and right. Partition: use two pointers. Average: O(N log N), Worst: O(N²) if always unbalanced.
</details>

---

## Problem 9: Heap Sort
**Difficulty:** Hard
**Topics:** Heaps, Sorting

### Problem Statement
Implement heap sort using max heap. Show heap building and extraction phases.

### Input Format
```
N (array size)
N integers
```

### Output Format
```
Original: [elements]
After heapify: [heap structure]
Sorted: [elements]
```

### Constraints
- 1 ≤ N ≤ 10^6

### Example Test Cases

**Test Case 1:**
```
Input:
6
4 10 3 5 1 6
Output:
Original: 4 10 3 5 1 6
Max Heap: 10 5 6 4 1 3
Sorted: 1 3 4 5 6 10
```

<details>
<summary>Hint</summary>
Build max heap (parent ≥ children). Repeatedly extract max (root), swap with last element, reduce heap size, heapify root. Time: O(N log N), in-place: O(1) extra space.
</details>

---

## Problem 10: Counting Sort
**Difficulty:** Medium
**Topics:** Non-comparison Sorting

### Problem Statement
Implement counting sort for integers in a limited range.

### Input Format
```
N (array size)
N integers
Range: [min, max]
```

### Output Format
```
Sorted array: [elements]
```

### Constraints
- 1 ≤ N ≤ 10^6
- 0 ≤ elements ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input:
8
4 2 2 8 3 3 1 5
Output:
Sorted: 1 2 2 3 3 4 5 8
```

<details>
<summary>Hint</summary>
Count frequency of each element in count array. Modify count array to store cumulative counts. Place elements at correct positions. Time: O(N + k) where k is range, stable sort.
</details>

---

## Problem 11: Radix Sort
**Difficulty:** Hard
**Topics:** Non-comparison Sorting

### Problem Statement
Implement radix sort for integers using counting sort as subroutine.

### Input Format
```
N (array size)
N integers
```

### Output Format
```
After sorting by each digit:
[intermediate arrays]
Final sorted: [elements]
```

### Constraints
- 1 ≤ N ≤ 10^6
- Non-negative integers

### Example Test Cases

**Test Case 1:**
```
Input:
7
170 45 75 90 802 24 2
Output:
After digit 1: 170 90 802 2 24 45 75
After digit 10: 802 2 24 45 170 75 90
After digit 100: 2 24 45 75 90 170 802
Sorted: 2 24 45 75 90 170 802
```

<details>
<summary>Hint</summary>
Sort by least significant digit first, then next digit, etc. Use stable sort (counting sort) for each digit. Time: O(d × (N + k)) where d is max digits, k is digit range (0-9).
</details>

---

## Problem 12: Bucket Sort
**Difficulty:** Medium
**Topics:** Distribution Sorting

### Problem Statement
Implement bucket sort for uniformly distributed floating-point numbers in [0, 1).

### Input Format
```
N (array size)
N floating-point numbers
```

### Output Format
```
Sorted array: [elements]
Bucket distribution: [counts per bucket]
```

### Constraints
- 1 ≤ N ≤ 10^6
- 0 ≤ elements < 1

### Example Test Cases

**Test Case 1:**
```
Input:
7
0.897 0.565 0.656 0.1234 0.665 0.3434 0.897
Output:
Sorted: 0.1234 0.3434 0.565 0.656 0.665 0.897 0.897
Buckets: [1, 0, 1, 1, 0, 2, 2, 0, 0, 0]
```

<details>
<summary>Hint</summary>
Create n buckets. Distribute elements: bucket_index = floor(n × arr[i]). Sort each bucket (insertion sort). Concatenate buckets. Average time: O(N) for uniform distribution.
</details>

---

## Recursion (Problems 13-17)

## Problem 13: Tower of Hanoi
**Difficulty:** Medium
**Topics:** Recursion, Mathematical

### Problem Statement
Solve the Tower of Hanoi problem: move N disks from source to destination using auxiliary peg.

### Input Format
```
N (number of disks)
```

### Output Format
```
Move disk [n] from [source] to [destination]
Total moves: [count]
```

### Constraints
- 1 ≤ N ≤ 20

### Example Test Cases

**Test Case 1:**
```
Input: 3
Output:
Move disk 1 from A to C
Move disk 2 from A to B
Move disk 1 from C to B
Move disk 3 from A to C
Move disk 1 from B to A
Move disk 2 from B to C
Move disk 1 from A to C
Total moves: 7
```

<details>
<summary>Hint</summary>
Recursive approach:
1. Move n-1 disks from source to auxiliary (using destination)
2. Move largest disk from source to destination
3. Move n-1 disks from auxiliary to destination (using source)
Total moves: 2^n - 1
</details>

---

## Problem 14: Generate All Permutations
**Difficulty:** Hard
**Topics:** Recursion, Backtracking

### Problem Statement
Generate all permutations of a given array/string.

### Input Format
```
N (number of elements)
N elements
```

### Output Format
```
All permutations (one per line)
Total: [count]
```

### Constraints
- 1 ≤ N ≤ 8

### Example Test Cases

**Test Case 1:**
```
Input:
3
1 2 3
Output:
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
Total: 6
```

<details>
<summary>Hint</summary>
Fix first element, recursively generate permutations of remaining. Backtrack by swapping. Base case: when you've arranged all elements. Time: O(N!).
</details>

---

## Problem 15: Generate All Subsets (Power Set)
**Difficulty:** Medium
**Topics:** Recursion, Bit Manipulation

### Problem Statement
Generate all subsets (power set) of a given set.

### Input Format
```
N (number of elements)
N elements
```

### Output Format
```
All subsets
Total: [count]
```

### Constraints
- 1 ≤ N ≤ 15

### Example Test Cases

**Test Case 1:**
```
Input:
3
1 2 3
Output:
{}
{1}
{2}
{3}
{1, 2}
{1, 3}
{2, 3}
{1, 2, 3}
Total: 8
```

<details>
<summary>Hint</summary>
Method 1 (Recursive): For each element, include it or exclude it.
Method 2 (Iterative): Use bit manipulation, iterate 0 to 2^n - 1, each bit represents include/exclude.
Total subsets: 2^N
</details>

---

## Problem 16: N-Queens Problem
**Difficulty:** Hard
**Topics:** Backtracking, Recursion

### Problem Statement
Place N queens on N×N chessboard such that no two queens attack each other.

### Input Format
```
N (board size)
```

### Output Format
```
All valid configurations
Total solutions: [count]
```

### Constraints
- 4 ≤ N ≤ 12

### Example Test Cases

**Test Case 1:**
```
Input: 4
Output:
Solution 1:
. Q . .
. . . Q
Q . . .
. . Q .

Solution 2:
. . Q .
Q . . .
. . . Q
. Q . .

Total solutions: 2
```

<details>
<summary>Hint</summary>
Use backtracking. Place queen in each row, trying all columns. Check if position is safe (no queen in same column, diagonal). If not safe, backtrack. Time: O(N!).
</details>

---

## Problem 17: Sudoku Solver
**Difficulty:** Hard
**Topics:** Backtracking, Recursion

### Problem Statement
Solve a 9×9 Sudoku puzzle using backtracking.

### Input Format
```
9×9 grid (0 represents empty cell)
```

### Output Format
```
Solved sudoku or "No solution"
```

### Constraints
- Valid sudoku with unique solution

### Example Test Cases

**Test Case 1:**
```
Input:
5 3 0 0 7 0 0 0 0
6 0 0 1 9 5 0 0 0
0 9 8 0 0 0 0 6 0
8 0 0 0 6 0 0 0 3
4 0 0 8 0 3 0 0 1
7 0 0 0 2 0 0 0 6
0 6 0 0 0 0 2 8 0
0 0 0 4 1 9 0 0 5
0 0 0 0 8 0 0 7 9

Output: [Solved grid]
```

<details>
<summary>Hint</summary>
Find empty cell, try digits 1-9. Check if valid (not in row/column/3×3 box). Recursively fill remaining. If can't place any digit, backtrack. Return true when all cells filled.
</details>

---

## Dynamic Programming (Problems 18-23)

## Problem 18: Fibonacci - DP Optimization
**Difficulty:** Medium
**Topics:** Dynamic Programming, Memoization

### Problem Statement
Calculate Fibonacci number using naive recursion, memoization, and bottom-up DP. Compare performance.

### Input Format
```
N (Fibonacci index)
```

### Output Format
```
Fibonacci(N): [value]
Time for each method:
  Naive recursion: [time]
  Memoization: [time]
  Bottom-up DP: [time]
```

### Constraints
- 1 ≤ N ≤ 45

### Example Test Cases

**Test Case 1:**
```
Input: 40
Output:
Fibonacci(40): 102334155
Naive recursion: 5243 ms
Memoization: 2 ms
Bottom-up DP: 1 ms
```

<details>
<summary>Hint</summary>
Naive: Exponential O(2^N)
Memoization: Store computed values in array, O(N) time and space
Bottom-up: Iteratively compute from 0 to N, O(N) time, O(1) space possible
</details>

---

## Problem 19: Longest Common Subsequence (LCS)
**Difficulty:** Hard
**Topics:** Dynamic Programming, Strings

### Problem Statement
Find the length and actual LCS of two strings.

### Input Format
```
String 1
String 2
```

### Output Format
```
LCS length: [length]
LCS: [subsequence]
```

### Constraints
- 1 ≤ string length ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input:
ABCDGH
AEDFHR
Output:
LCS length: 3
LCS: ADH
```

**Test Case 2:**
```
Input:
AGGTAB
GXTXAYB
Output:
LCS length: 4
LCS: GTAB
```

<details>
<summary>Hint</summary>
DP table: dp[i][j] = LCS length of first i chars of s1 and first j chars of s2
If s1[i] == s2[j]: dp[i][j] = dp[i-1][j-1] + 1
Else: dp[i][j] = max(dp[i-1][j], dp[i][j-1])
Backtrack to find actual LCS
</details>

---

## Problem 20: 0/1 Knapsack Problem
**Difficulty:** Hard
**Topics:** Dynamic Programming, Optimization

### Problem Statement
Given weights and values of items, find maximum value that can be obtained with weight limit.

### Input Format
```
N (number of items)
W (weight capacity)
N weights
N values
```

### Output Format
```
Maximum value: [value]
Items selected: [indices]
```

### Constraints
- 1 ≤ N ≤ 1000
- 1 ≤ W ≤ 10000

### Example Test Cases

**Test Case 1:**
```
Input:
4
7
1 3 4 5
1 4 5 7
Output:
Maximum value: 9
Items selected: 0 1 (weights: 1+3=4, values: 1+4=5)
Actually: Items 1, 2 (weights: 3+4=7, values: 4+5=9)
```

<details>
<summary>Hint</summary>
DP table: dp[i][w] = max value using first i items with weight limit w
If weight[i] ≤ w: dp[i][w] = max(dp[i-1][w], value[i] + dp[i-1][w-weight[i]])
Else: dp[i][w] = dp[i-1][w]
Backtrack to find selected items
</details>

---

## Problem 21: Coin Change Problem
**Difficulty:** Medium
**Topics:** Dynamic Programming

### Problem Statement
Given coins of different denominations and amount, find minimum number of coins needed.

### Input Format
```
N (number of coin types)
N coin denominations
Amount
```

### Output Format
```
Minimum coins: [count]
Coins used: [denominations]
```

### Constraints
- 1 ≤ N ≤ 100
- 1 ≤ amount ≤ 10000

### Example Test Cases

**Test Case 1:**
```
Input:
3
1 2 5
11
Output:
Minimum coins: 3
Coins used: 5 5 1
```

**Test Case 2:**
```
Input:
2
2 5
3
Output:
Not possible
```

<details>
<summary>Hint</summary>
DP: dp[i] = minimum coins needed for amount i
For each amount from 1 to target, try each coin:
dp[i] = min(dp[i], dp[i-coin] + 1) if i >= coin
If dp[amount] is still infinity, not possible
</details>

---

## Problem 22: Longest Increasing Subsequence (LIS)
**Difficulty:** Medium
**Topics:** Dynamic Programming

### Problem Statement
Find the length and actual longest increasing subsequence in an array.

### Input Format
```
N (array size)
N integers
```

### Output Format
```
LIS length: [length]
LIS: [elements]
```

### Constraints
- 1 ≤ N ≤ 10000

### Example Test Cases

**Test Case 1:**
```
Input:
8
10 9 2 5 3 7 101 18
Output:
LIS length: 4
LIS: 2 3 7 18 (or 2 5 7 18)
```

<details>
<summary>Hint</summary>
Method 1: DP O(N²) - dp[i] = length of LIS ending at i
For each i, check all j < i, if arr[j] < arr[i]: dp[i] = max(dp[i], dp[j] + 1)
Method 2: Binary search O(N log N) - maintain array of smallest tail elements
</details>

---

## Problem 23: Matrix Chain Multiplication
**Difficulty:** Hard
**Topics:** Dynamic Programming, Optimization

### Problem Statement
Find minimum number of scalar multiplications needed to multiply chain of matrices.

### Input Format
```
N (number of matrices)
N+1 dimensions (dimensions[i-1] x dimensions[i] for matrix i)
```

### Output Format
```
Minimum multiplications: [count]
Optimal parenthesization: [expression]
```

### Constraints
- 2 ≤ N ≤ 100

### Example Test Cases

**Test Case 1:**
```
Input:
4
40 20 30 10 30
Output:
Minimum multiplications: 26000
Optimal: ((A1(A2A3))A4)
```

<details>
<summary>Hint</summary>
DP: dp[i][j] = minimum cost to multiply matrices from i to j
For each chain length, try all split points k:
dp[i][j] = min(dp[i][k] + dp[k+1][j] + dimensions[i-1]*dimensions[k]*dimensions[j])
Time: O(N³)
</details>

---

## Greedy Algorithms (Problems 24-27)

## Problem 24: Activity Selection Problem
**Difficulty:** Medium
**Topics:** Greedy Algorithms

### Problem Statement
Select maximum number of non-overlapping activities given start and finish times.

### Input Format
```
N (number of activities)
N start times
N finish times
```

### Output Format
```
Maximum activities: [count]
Selected activities: [indices]
```

### Constraints
- 1 ≤ N ≤ 10000

### Example Test Cases

**Test Case 1:**
```
Input:
6
1 3 0 5 8 5
2 4 6 7 9 9
Output:
Maximum activities: 4
Selected: 0 1 3 4 (times: 1-2, 3-4, 5-7, 8-9)
```

<details>
<summary>Hint</summary>
Greedy choice: Always pick activity with earliest finish time that doesn't conflict. Sort by finish time. Select first, then select next compatible activity. Optimal solution.
</details>

---

## Problem 25: Huffman Coding
**Difficulty:** Hard
**Topics:** Greedy Algorithms, Trees

### Problem Statement
Generate Huffman codes for characters based on their frequencies.

### Input Format
```
N (number of characters)
N characters
N frequencies
```

### Output Format
```
Character: Code
Average code length: [value]
```

### Constraints
- 1 ≤ N ≤ 100

### Example Test Cases

**Test Case 1:**
```
Input:
6
a b c d e f
5 9 12 13 16 45
Output:
f: 0
c: 100
d: 101
a: 1100
b: 1101
e: 111
Average code length: 2.24
```

<details>
<summary>Hint</summary>
Build min heap of frequencies. Repeatedly extract two minimum nodes, create parent with sum frequency, insert back. Build tree bottom-up. Assign 0 for left, 1 for right. Traverse from root to generate codes.
</details>

---

## Problem 26: Fractional Knapsack
**Difficulty:** Medium
**Topics:** Greedy Algorithms

### Problem Statement
Unlike 0/1 knapsack, you can take fractions of items. Maximize value.

### Input Format
```
N (number of items)
W (capacity)
N weights
N values
```

### Output Format
```
Maximum value: [value]
Items taken: [item: fraction pairs]
```

### Constraints
- 1 ≤ N ≤ 1000
- 1 ≤ W ≤ 10000

### Example Test Cases

**Test Case 1:**
```
Input:
3
50
10 20 30
60 100 120
Output:
Maximum value: 240
Items: Item 2: 1.0, Item 1: 1.0, Item 0: 0.667
```

<details>
<summary>Hint</summary>
Calculate value/weight ratio for each item. Sort by ratio in descending order. Take items greedily until capacity is full. If item doesn't fit completely, take fraction.
</details>

---

## Problem 27: Prim's Minimum Spanning Tree
**Difficulty:** Hard
**Topics:** Greedy Algorithms, Graphs

### Problem Statement
Find minimum spanning tree of a weighted undirected graph using Prim's algorithm.

### Input Format
```
V (vertices)
E (edges)
E lines: u v weight
```

### Output Format
```
MST edges:
Total weight: [sum]
```

### Constraints
- 1 ≤ V ≤ 1000
- Connected graph

### Example Test Cases

**Test Case 1:**
```
Input:
5
7
0 1 2
0 3 6
1 2 3
1 3 8
1 4 5
2 4 7
3 4 9
Output:
MST edges:
0-1: 2
1-2: 3
0-3: 6
1-4: 5
Total weight: 16
```

<details>
<summary>Hint</summary>
Start with arbitrary vertex. Maintain set of included vertices and min heap of edges. Repeatedly add minimum edge that connects included and non-included vertex. Continue until all vertices included. Time: O(E log V) with heap.
</details>

---

## Backtracking (Problems 28-30)

## Problem 28: Rat in a Maze
**Difficulty:** Medium
**Topics:** Backtracking, Matrix

### Problem Statement
Find path from (0,0) to (N-1,N-1) in a maze. 1 represents valid path, 0 represents blocked.

### Input Format
```
N (maze size)
N×N maze (0s and 1s)
```

### Output Format
```
Path exists: Yes/No
Path: [coordinates]
Path matrix (mark path with 1)
```

### Constraints
- 1 ≤ N ≤ 20

### Example Test Cases

**Test Case 1:**
```
Input:
4
1 1 0 0
1 1 1 0
0 1 1 1
0 0 1 1
Output:
Path exists: Yes
Path: (0,0)→(0,1)→(1,1)→(1,2)→(2,2)→(2,3)→(3,3)
```

<details>
<summary>Hint</summary>
Try moving in all directions (down, right, up, left). Mark current cell as visited. If destination reached, return true. If blocked or visited, backtrack. Unmark cell and try next direction.
</details>

---

## Problem 29: Word Search in Grid
**Difficulty:** Hard
**Topics:** Backtracking, Matrix, Strings

### Problem Statement
Find if a word exists in a 2D grid of characters. Word can be constructed from adjacent cells (horizontal or vertical).

### Input Format
```
Rows Columns
Grid of characters
Word to search
```

### Output Format
```
Word found: Yes/No
Starting position and path
```

### Constraints
- 1 ≤ rows, columns ≤ 20
- 1 ≤ word length ≤ 100

### Example Test Cases

**Test Case 1:**
```
Input:
3 4
A B C E
S F C S
A D E E
ABCCED
Output:
Word found: Yes
Path: (0,0)→(0,1)→(0,2)→(1,2)→(2,2)→(2,1)
```

<details>
<summary>Hint</summary>
For each cell, if it matches first character, start DFS. Try all 4 directions, check if next character matches. Mark cell as visited during DFS, unmark while backtracking. Return true if all characters matched.
</details>

---

## Problem 30: Graph Coloring Problem
**Difficulty:** Hard
**Topics:** Backtracking, Graphs

### Problem Statement
Determine if a graph can be colored with M colors such that no two adjacent vertices have the same color.

### Input Format
```
V (vertices)
E (edges)
Edge pairs
M (number of colors)
```

### Output Format
```
Coloring possible: Yes/No
Color assignment: [vertex: color pairs]
```

### Constraints
- 1 ≤ V ≤ 20
- 1 ≤ M ≤ 10

### Example Test Cases

**Test Case 1:**
```
Input:
4
5
0 1
0 2
0 3
1 2
2 3
3
Output:
Coloring possible: Yes
Colors: 0:1, 1:2, 2:3, 3:2
```

<details>
<summary>Hint</summary>
Try assigning colors 1 to M to each vertex. Check if assignment is safe (no adjacent vertex has same color). If safe, recursively color next vertex. If all vertices colored, return true. Otherwise, backtrack.
</details>

---

## Additional Practice Tips

1. **Understand Time Complexity:** Analyze each algorithm's time and space complexity
2. **Master Techniques:** Know when to use DP vs Greedy vs Backtracking
3. **Practice Optimization:** Start with brute force, then optimize
4. **Recognize Patterns:** Many problems follow similar patterns
5. **Test Edge Cases:** Empty inputs, single elements, worst cases
6. **Compare Approaches:** Implement multiple solutions and compare

## Summary of Techniques

| Technique | When to Use | Time Complexity |
|-----------|-------------|-----------------|
| Binary Search | Sorted data, monotonic function | O(log N) |
| Merge Sort | Stable sort needed, linked lists | O(N log N) |
| Quick Sort | Average case performance | O(N log N) avg |
| DP | Overlapping subproblems, optimal substructure | Varies |
| Greedy | Local optimal → global optimal | Varies |
| Backtracking | All solutions needed, constraint satisfaction | Exponential |

## Next Steps

After completing these exercises:
- **06-coding-challenges.md** for comprehensive multi-concept problems
- Check the **solutions/** directory for detailed implementations
- Practice on competitive programming platforms (Codeforces, LeetCode, HackerRank)
