# Backtracking

## Table of Contents
1. [Introduction to Backtracking](#introduction)
2. [How Backtracking Works](#how-backtracking-works)
3. [Backtracking Template](#backtracking-template)
4. [Classic Backtracking Problems](#classic-problems)
5. [Optimization Techniques](#optimization-techniques)
6. [Practice Problems](#practice-problems)

---

## Introduction to Backtracking

**Backtracking** is an algorithmic technique for solving problems recursively by trying to build a solution incrementally, abandoning solutions ("backtracking") that fail to satisfy constraints.

### Core Concept
```
1. Choose: Make a choice from available options
2. Explore: Recursively explore with that choice
3. Unchoose: Backtrack if choice doesn't lead to solution
```

### Key Characteristics
- **Exhaustive search**: Tries all possibilities
- **Pruning**: Abandons invalid paths early
- **Recursive**: Uses recursion naturally
- **DFS-based**: Depth-first search approach

### When to Use Backtracking
- Find all possible solutions
- Find one solution
- Count solutions
- Optimization problems with constraints

---

## How Backtracking Works

### Decision Tree Visualization

**Example**: Generate all binary strings of length 3

```
                    ""
                   /  \
                  0    1
                 / \   / \
                00 01 10 11
               /|  |\ /| |\
              000001010011 100 101 110 111

Backtracking explores each path depth-first
```

### Pseudocode Pattern
```
function backtrack(state):
    if state is solution:
        add state to solutions
        return

    for each choice in choices:
        if choice is valid:
            make choice
            backtrack(new state)
            undo choice (backtrack)
```

---

## Backtracking Template

### General Template in C

```c
#include <stdio.h>
#include <stdbool.h>

// General backtracking template
void backtrack(int state[], int depth, int max_depth,
               bool* used, int* result, int* count) {

    // Base case: found complete solution
    if (depth == max_depth) {
        // Process solution
        printf("Solution: ");
        for (int i = 0; i < max_depth; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        (*count)++;
        return;
    }

    // Try all choices
    for (int i = 0; i < max_depth; i++) {
        // Check if choice is valid
        if (!used[i]) {
            // Make choice
            result[depth] = state[i];
            used[i] = true;

            // Recurse with choice
            backtrack(state, depth + 1, max_depth, used, result, count);

            // Undo choice (backtrack)
            used[i] = false;
        }
    }
}
```

---

## Classic Backtracking Problems

### 1. N-Queens Problem

**Problem**: Place N queens on N×N chessboard so no two queens attack each other.

```c
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 20

// Print board
void printBoard(int board[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j]) {
                printf("Q ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Check if queen can be placed at board[row][col]
bool isSafe(int board[MAX][MAX], int n, int row, int col) {
    // Check column
    for (int i = 0; i < row; i++) {
        if (board[i][col]) {
            return false;
        }
    }

    // Check upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return false;
        }
    }

    // Check upper right diagonal
    for (int i = row, j = col; i >= 0 && j < n; i--, j++) {
        if (board[i][j]) {
            return false;
        }
    }

    return true;
}

// Backtracking function to solve N-Queens
bool solveNQueensUtil(int board[MAX][MAX], int n, int row, int* count) {
    // Base case: All queens placed
    if (row >= n) {
        (*count)++;
        printf("Solution %d:\n", *count);
        printBoard(board, n);
        return true;  // Change to false to find all solutions
    }

    bool foundSolution = false;

    // Try placing queen in all columns of current row
    for (int col = 0; col < n; col++) {
        if (isSafe(board, n, row, col)) {
            // Place queen
            board[row][col] = 1;

            // Recurse to place rest of queens
            if (solveNQueensUtil(board, n, row + 1, count)) {
                foundSolution = true;
                // Remove return to find all solutions
            }

            // Backtrack: remove queen
            board[row][col] = 0;
        }
    }

    return foundSolution;
}

// Main function for N-Queens
void solveNQueens(int n) {
    int board[MAX][MAX] = {0};
    int count = 0;

    printf("=== N-QUEENS PROBLEM (N=%d) ===\n\n", n);

    if (!solveNQueensUtil(board, n, 0, &count)) {
        printf("No solution exists\n");
    }

    printf("Total solutions found: %d\n", count);
}

void demonstrateNQueens() {
    solveNQueens(4);
    printf("\n");
    solveNQueens(8);
}
```

**Visualization for 4-Queens**:
```
Solution 1:       Solution 2:
. Q . .           . . Q .
. . . Q           Q . . .
Q . . .           . . . Q
. . Q .           . Q . .
```

**Time Complexity**: O(N!)
**Space Complexity**: O(N²)

---

### 2. Sudoku Solver

**Problem**: Fill 9×9 grid so each row, column, and 3×3 box contains digits 1-9.

```c
#include <stdio.h>
#include <stdbool.h>

#define N 9

// Print Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        if (row % 3 == 0 && row != 0) {
            printf("------+-------+------\n");
        }

        for (int col = 0; col < N; col++) {
            if (col % 3 == 0 && col != 0) {
                printf("| ");
            }

            if (grid[row][col] == 0) {
                printf(". ");
            } else {
                printf("%d ", grid[row][col]);
            }
        }
        printf("\n");
    }
}

// Check if num can be placed at grid[row][col]
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check row
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num) {
            return false;
        }
    }

    // Check column
    for (int x = 0; x < N; x++) {
        if (grid[x][col] == num) {
            return false;
        }
    }

    // Check 3×3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Find empty cell
bool findEmptyLocation(int grid[N][N], int* row, int* col) {
    for (*row = 0; *row < N; (*row)++) {
        for (*col = 0; *col < N; (*col)++) {
            if (grid[*row][*col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Backtracking function to solve Sudoku
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // If no empty cell, puzzle solved
    if (!findEmptyLocation(grid, &row, &col)) {
        return true;
    }

    // Try digits 1-9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            // Make choice
            grid[row][col] = num;

            // Recurse
            if (solveSudoku(grid)) {
                return true;
            }

            // Backtrack
            grid[row][col] = 0;
        }
    }

    return false;  // Trigger backtracking
}

void demonstrateSudoku() {
    printf("=== SUDOKU SOLVER ===\n\n");

    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    printf("Unsolved Sudoku:\n");
    printGrid(grid);

    if (solveSudoku(grid)) {
        printf("\n\nSolved Sudoku:\n");
        printGrid(grid);
    } else {
        printf("\nNo solution exists\n");
    }
}
```

**Time Complexity**: O(9^(n×n)) worst case, much better with pruning
**Space Complexity**: O(n×n)

---

### 3. Rat in a Maze

**Problem**: Find path from top-left to bottom-right in maze.

```c
#include <stdio.h>
#include <stdbool.h>

#define N 4

// Print solution matrix
void printSolution(int sol[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", sol[i][j]);
        }
        printf("\n");
    }
}

// Check if x, y is valid
bool isSafe(int maze[N][N], int x, int y, int sol[N][N]) {
    return (x >= 0 && x < N && y >= 0 && y < N &&
            maze[x][y] == 1 && sol[x][y] == 0);
}

// Backtracking function to solve maze
bool solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N]) {
    // Reached destination
    if (x == N - 1 && y == N - 1 && maze[x][y] == 1) {
        sol[x][y] = 1;
        return true;
    }

    // Check if current cell is valid
    if (isSafe(maze, x, y, sol)) {
        // Mark cell as part of solution
        sol[x][y] = 1;

        // Move right
        if (solveMazeUtil(maze, x, y + 1, sol)) {
            return true;
        }

        // Move down
        if (solveMazeUtil(maze, x + 1, y, sol)) {
            return true;
        }

        // Move left
        if (solveMazeUtil(maze, x, y - 1, sol)) {
            return true;
        }

        // Move up
        if (solveMazeUtil(maze, x - 1, y, sol)) {
            return true;
        }

        // Backtrack: unmark cell
        sol[x][y] = 0;
        return false;
    }

    return false;
}

void demonstrateRatInMaze() {
    printf("=== RAT IN A MAZE ===\n\n");

    int maze[N][N] = {
        {1, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {1, 1, 1, 1}
    };

    int sol[N][N] = {0};

    printf("Maze (1=path, 0=wall):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    if (solveMazeUtil(maze, 0, 0, sol)) {
        printf("Solution (1=path taken):\n");
        printSolution(sol);
    } else {
        printf("No solution exists\n");
    }
}
```

**Visualization**:
```
Maze:           Solution:
1 1 0 0         1 1 0 0
1 1 1 0   →     0 1 1 0
0 1 0 0         0 1 0 0
1 1 1 1         0 1 1 1
```

---

### 4. Generate All Permutations

```c
#include <stdio.h>

// Swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Generate permutations using backtracking
void permute(int arr[], int left, int right, int* count) {
    if (left == right) {
        (*count)++;
        printf("Permutation %d: ", *count);
        printArray(arr, right + 1);
        return;
    }

    for (int i = left; i <= right; i++) {
        // Choose
        swap(&arr[left], &arr[i]);

        // Explore
        permute(arr, left + 1, right, count);

        // Unchoose (backtrack)
        swap(&arr[left], &arr[i]);
    }
}

void demonstratePermutations() {
    printf("=== GENERATE ALL PERMUTATIONS ===\n\n");

    int arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int count = 0;

    printf("Array: ");
    printArray(arr, n);
    printf("\nAll permutations:\n");

    permute(arr, 0, n - 1, &count);

    printf("\nTotal permutations: %d\n", count);
}
```

---

### 5. Generate All Subsets (Power Set)

```c
#include <stdio.h>
#include <stdbool.h>

// Print subset
void printSubset(int arr[], int subset[], int subsetSize) {
    printf("{ ");
    for (int i = 0; i < subsetSize; i++) {
        printf("%d ", subset[i]);
    }
    printf("}\n");
}

// Generate subsets using backtracking
void generateSubsets(int arr[], int n, int subset[], int subsetSize,
                     int index, int* count) {
    // Print current subset
    (*count)++;
    printf("Subset %d: ", *count);
    printSubset(arr, subset, subsetSize);

    // Generate subsets by including remaining elements
    for (int i = index; i < n; i++) {
        // Include arr[i]
        subset[subsetSize] = arr[i];

        // Recurse with arr[i] included
        generateSubsets(arr, n, subset, subsetSize + 1, i + 1, count);

        // Backtrack: exclude arr[i] for next iteration
        // (implicit in for loop)
    }
}

void demonstrateSubsets() {
    printf("=== GENERATE ALL SUBSETS ===\n\n");

    int arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int subset[n];
    int count = 0;

    printf("Set: { ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("}\n\nAll subsets:\n");

    generateSubsets(arr, n, subset, 0, 0, &count);

    printf("\nTotal subsets: %d (2^%d = %d)\n", count, n, 1 << n);
}
```

---

### 6. Hamiltonian Path

**Problem**: Find path visiting each vertex exactly once.

```c
#include <stdio.h>
#include <stdbool.h>

#define V 5

// Print solution path
void printSolution(int path[], int n) {
    printf("Hamiltonian path: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

// Check if vertex v can be added to path
bool isSafe(int v, bool graph[V][V], int path[], int pos) {
    // Check if vertex is adjacent to previous vertex
    if (!graph[path[pos - 1]][v]) {
        return false;
    }

    // Check if vertex already in path
    for (int i = 0; i < pos; i++) {
        if (path[i] == v) {
            return false;
        }
    }

    return true;
}

// Backtracking function for Hamiltonian path
bool hamiltonianPathUtil(bool graph[V][V], int path[], int pos) {
    // Base case: all vertices included
    if (pos == V) {
        return true;
    }

    // Try different vertices as next candidate
    for (int v = 1; v < V; v++) {
        if (isSafe(v, graph, path, pos)) {
            path[pos] = v;

            if (hamiltonianPathUtil(graph, path, pos + 1)) {
                return true;
            }

            // Backtrack
            path[pos] = -1;
        }
    }

    return false;
}

void demonstrateHamiltonianPath() {
    printf("=== HAMILTONIAN PATH ===\n\n");

    bool graph[V][V] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0}
    };

    int path[V];
    for (int i = 0; i < V; i++) {
        path[i] = -1;
    }

    // Start from vertex 0
    path[0] = 0;

    if (hamiltonianPathUtil(graph, path, 1)) {
        printSolution(path, V);
    } else {
        printf("No Hamiltonian path exists\n");
    }
}
```

---

### 7. Word Search in Grid

```c
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ROWS 3
#define COLS 4

// Check if position is valid
bool isValid(int row, int col, bool visited[ROWS][COLS]) {
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS &&
            !visited[row][col]);
}

// Backtracking function for word search
bool searchWord(char board[ROWS][COLS], char* word, int index,
                int row, int col, bool visited[ROWS][COLS]) {
    // Found complete word
    if (index == strlen(word)) {
        return true;
    }

    // Check current position
    if (!isValid(row, col, visited) || board[row][col] != word[index]) {
        return false;
    }

    // Mark as visited
    visited[row][col] = true;

    // Explore all 4 directions
    int rowDir[] = {-1, 1, 0, 0};
    int colDir[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        if (searchWord(board, word, index + 1,
                      row + rowDir[i], col + colDir[i], visited)) {
            return true;
        }
    }

    // Backtrack
    visited[row][col] = false;

    return false;
}

void demonstrateWordSearch() {
    printf("=== WORD SEARCH IN GRID ===\n\n");

    char board[ROWS][COLS] = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };

    char word[] = "ABCCED";

    printf("Board:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }

    printf("\nSearching for word: %s\n", word);

    bool visited[ROWS][COLS] = {false};
    bool found = false;

    // Try starting from each cell
    for (int i = 0; i < ROWS && !found; i++) {
        for (int j = 0; j < COLS && !found; j++) {
            if (searchWord(board, word, 0, i, j, visited)) {
                found = true;
                printf("Word found starting at (%d, %d)\n", i, j);
            }
        }
    }

    if (!found) {
        printf("Word not found\n");
    }
}
```

---

## Optimization Techniques

### 1. Constraint Propagation
- Eliminate invalid choices early
- Reduce search space

### 2. Ordering Heuristics
- **Most constrained first**: Choose variable with fewest legal values
- **Least constraining value**: Choose value that eliminates fewest options

### 3. Pruning
- Cut branches that can't lead to solution
- Alpha-beta pruning in game trees

### 4. Memoization
- Cache results of expensive computations
- Useful when subproblems repeat

---

## Practice Problems

### Problem 1: Combination Sum
Find all unique combinations that sum to target.

### Problem 2: Palindrome Partitioning
Partition string such that every substring is palindrome.

### Problem 3: Generate Parentheses
Generate all valid parentheses combinations.

### Problem 4: Letter Combinations of Phone Number
Generate all letter combinations from phone number.

### Problem 5: Restore IP Addresses
Generate all valid IP addresses from string.

### Problem 6: Subset Sum
Find all subsets with given sum.

### Problem 7: Knight's Tour
Find path for knight to visit every square on chessboard.

### Problem 8: Graph Coloring
Color graph with minimum colors.

### Problem 9: Cryptarithmetic
Solve puzzles like SEND + MORE = MONEY.

### Problem 10: Crossword Solver
Fill crossword puzzle with given words.

---

## Summary

### Key Concepts
1. **Try all possibilities**: Exhaustive search
2. **Prune invalid paths**: Early termination
3. **Backtrack**: Undo choices that don't work
4. **Recursion**: Natural implementation

### Backtracking vs Other Techniques

| Technique | Use Case | Efficiency |
|-----------|----------|------------|
| Backtracking | Find all solutions | Exponential (with pruning) |
| Dynamic Programming | Overlapping subproblems | Polynomial |
| Greedy | Local optimal → global | Linear/log |
| Branch & Bound | Optimization | Better with bounding |

### When to Use Backtracking
- All solutions needed
- Constraint satisfaction problems
- Combinatorial problems
- No better algorithm exists

### Common Patterns
1. Generate permutations/combinations
2. Constraint satisfaction (N-Queens, Sudoku)
3. Path finding (Maze, Hamiltonian)
4. Subset selection
5. Puzzle solving

---

**Next Topic**: Graph Algorithms
