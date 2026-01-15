# Arrays in C

## Table of Contents
1. [Introduction to Arrays](#introduction-to-arrays)
2. [One-Dimensional Arrays](#one-dimensional-arrays)
3. [Two-Dimensional Arrays](#two-dimensional-arrays)
4. [Multidimensional Arrays](#multidimensional-arrays)
5. [Array Manipulation](#array-manipulation)
6. [Arrays and Functions](#arrays-and-functions)
7. [Real-World Applications](#real-world-applications)
8. [Practice Exercises](#practice-exercises)

---

## Introduction to Arrays

An array is a collection of elements of the same data type stored in contiguous memory locations. Arrays allow you to:
- Store multiple values under a single variable name
- Access elements efficiently using indices
- Process large amounts of data systematically
- Implement complex data structures

### Why Use Arrays?

**Without Arrays:**
```c
int student1_score = 85;
int student2_score = 92;
int student3_score = 78;
int student4_score = 90;
int student5_score = 88;
// Difficult to manage and process
```

**With Arrays:**
```c
int scores[5] = {85, 92, 78, 90, 88};
// Easy to manage and process in loops
```

### Array Characteristics

1. **Fixed size** - Size must be determined at declaration
2. **Homogeneous** - All elements must be of the same type
3. **Contiguous memory** - Elements are stored consecutively
4. **Zero-indexed** - First element is at index 0
5. **Random access** - Direct access to any element using index

---

## One-Dimensional Arrays

A 1D array is a linear collection of elements.

### Declaration and Initialization

**Syntax:**
```c
data_type array_name[size];
```

**Different Ways to Initialize:**

```c
#include <stdio.h>

int main() {
    // Method 1: Declare then assign
    int arr1[5];
    arr1[0] = 10;
    arr1[1] = 20;
    arr1[2] = 30;
    arr1[3] = 40;
    arr1[4] = 50;

    // Method 2: Declare and initialize together
    int arr2[5] = {10, 20, 30, 40, 50};

    // Method 3: Partial initialization (rest filled with 0)
    int arr3[5] = {10, 20};  // arr3 = {10, 20, 0, 0, 0}

    // Method 4: Size inferred from initializer
    int arr4[] = {10, 20, 30, 40, 50};  // Size automatically 5

    // Method 5: Initialize all elements to 0
    int arr5[5] = {0};  // All elements = 0

    return 0;
}
```

### Memory Layout

**Example: int arr[5] = {10, 20, 30, 40, 50};**

```
Memory Representation:

Logical View:
Index:     0    1    2    3    4
         +----+----+----+----+----+
arr      | 10 | 20 | 30 | 40 | 50 |
         +----+----+----+----+----+

Physical Memory:
Assuming int = 4 bytes, starting at address 1000:

Address:  1000  1004  1008  1012  1016
         +----+----+----+----+----+
Value:   | 10 | 20 | 30 | 40 | 50 |
         +----+----+----+----+----+
         arr[0] arr[1] arr[2] arr[3] arr[4]

Address of arr[i] = Base Address + (i × sizeof(element))
Address of arr[3] = 1000 + (3 × 4) = 1012
```

### Accessing Array Elements

```c
#include <stdio.h>

int main() {
    int numbers[5] = {10, 20, 30, 40, 50};

    // Accessing individual elements
    printf("First element: %d\n", numbers[0]);
    printf("Third element: %d\n", numbers[2]);
    printf("Last element: %d\n", numbers[4]);

    // Modifying elements
    numbers[1] = 25;
    printf("Modified second element: %d\n", numbers[1]);

    // Accessing using loop
    printf("All elements: ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}
/* Output:
First element: 10
Third element: 30
Last element: 50
Modified second element: 25
All elements: 10 25 30 40 50
*/
```

### Array Operations

#### 1. Finding Sum and Average
```c
#include <stdio.h>

int main() {
    int marks[5] = {85, 92, 78, 90, 88};
    int sum = 0;
    float average;

    // Calculate sum
    for(int i = 0; i < 5; i++) {
        sum += marks[i];
    }

    average = (float)sum / 5;

    printf("Marks: ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", marks[i]);
    }
    printf("\nSum: %d\n", sum);
    printf("Average: %.2f\n", average);

    return 0;
}
/* Output:
Marks: 85 92 78 90 88
Sum: 433
Average: 86.60
*/
```

#### 2. Finding Maximum and Minimum
```c
#include <stdio.h>

int main() {
    int arr[] = {45, 23, 67, 12, 89, 34};
    int size = 6;
    int max = arr[0], min = arr[0];
    int maxIndex = 0, minIndex = 0;

    for(int i = 1; i < size; i++) {
        if(arr[i] > max) {
            max = arr[i];
            maxIndex = i;
        }
        if(arr[i] < min) {
            min = arr[i];
            minIndex = i;
        }
    }

    printf("Array: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nMaximum: %d at index %d\n", max, maxIndex);
    printf("Minimum: %d at index %d\n", min, minIndex);

    return 0;
}
/* Output:
Array: 45 23 67 12 89 34
Maximum: 89 at index 4
Minimum: 12 at index 3
*/
```

#### 3. Reversing an Array
```c
#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    int temp;

    printf("Original array: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    // Reverse using two pointers
    for(int i = 0; i < size/2; i++) {
        temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }

    printf("\nReversed array: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
/* Output:
Original array: 1 2 3 4 5
Reversed array: 5 4 3 2 1
*/
```

**Reversal Process Visualization:**
```
Step-by-step reversal:
Initial:  [1, 2, 3, 4, 5]
           ^           ^
           i=0        i=4
Swap:     [5, 2, 3, 4, 1]

Step 2:   [5, 2, 3, 4, 1]
              ^     ^
              i=1  i=3
Swap:     [5, 4, 3, 2, 1]

Step 3:   [5, 4, 3, 2, 1]
                 ^
              i=2 (middle, stop)

Final:    [5, 4, 3, 2, 1]
```

#### 4. Linear Search
```c
#include <stdio.h>

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int size = 7;
    int target = 22;
    int found = -1;

    for(int i = 0; i < size; i++) {
        if(arr[i] == target) {
            found = i;
            break;
        }
    }

    if(found != -1) {
        printf("Element %d found at index %d\n", target, found);
    } else {
        printf("Element %d not found\n", target);
    }

    return 0;
}
// Output: Element 22 found at index 4
```

#### 5. Bubble Sort
```c
#include <stdio.h>

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int size = 7;
    int temp;

    printf("Original array: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    // Bubble Sort
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                // Swap
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("\nSorted array: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
/* Output:
Original array: 64 34 25 12 22 11 90
Sorted array: 11 12 22 25 34 64 90
*/
```

**Bubble Sort Visualization:**
```
Pass 1: [64, 34, 25, 12, 22, 11, 90]
        [34, 64, 25, 12, 22, 11, 90]  (swap 64, 34)
        [34, 25, 64, 12, 22, 11, 90]  (swap 64, 25)
        [34, 25, 12, 64, 22, 11, 90]  (swap 64, 12)
        [34, 25, 12, 22, 64, 11, 90]  (swap 64, 22)
        [34, 25, 12, 22, 11, 64, 90]  (swap 64, 11)
        [34, 25, 12, 22, 11, 64, 90]  (90 already in place)

Pass 2: [25, 34, 12, 22, 11, 64, 90]
        ... (continues until sorted)

Final:  [11, 12, 22, 25, 34, 64, 90]
```

---

## Two-Dimensional Arrays

A 2D array is an array of arrays, often visualized as a table with rows and columns.

### Declaration and Initialization

**Syntax:**
```c
data_type array_name[rows][columns];
```

**Different Ways to Initialize:**

```c
#include <stdio.h>

int main() {
    // Method 1: Complete initialization
    int matrix1[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Method 2: Linear initialization (filled row-wise)
    int matrix2[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Method 3: Partial initialization
    int matrix3[3][3] = {
        {1, 2},
        {4},
        {7, 8}
    };  // Remaining elements = 0

    // Method 4: All zeros
    int matrix4[3][3] = {0};

    return 0;
}
```

### Memory Layout

**Example: int matrix[3][4];**

```
Logical View (3 rows × 4 columns):

        Column 0  Column 1  Column 2  Column 3
Row 0   [  1  ]   [  2  ]   [  3  ]   [  4  ]
Row 1   [  5  ]   [  6  ]   [  7  ]   [  8  ]
Row 2   [  9  ]   [ 10  ]   [ 11  ]   [ 12  ]

Physical Memory (Row-major order):
Starting address: 1000, int = 4 bytes

Address: 1000 1004 1008 1012 1016 1020 1024 1028 1032 1036 1040 1044
Value:   [1]  [2]  [3]  [4]  [5]  [6]  [7]  [8]  [9]  [10] [11] [12]
Index:   [0,0][0,1][0,2][0,3][1,0][1,1][1,2][1,3][2,0][2,1][2,2][2,3]

Address of matrix[i][j] = Base + ((i × columns) + j) × sizeof(element)
Address of matrix[1][2] = 1000 + ((1 × 4) + 2) × 4 = 1000 + 24 = 1024
```

### Accessing 2D Array Elements

```c
#include <stdio.h>

int main() {
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Accessing individual elements
    printf("Element at [0][0]: %d\n", matrix[0][0]);
    printf("Element at [1][2]: %d\n", matrix[1][2]);
    printf("Element at [2][1]: %d\n", matrix[2][1]);

    // Accessing using nested loops
    printf("\nMatrix:\n");
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
/* Output:
Element at [0][0]: 1
Element at [1][2]: 6
Element at [2][1]: 8

Matrix:
1 2 3
4 5 6
7 8 9
*/
```

### 2D Array Operations

#### 1. Matrix Addition
```c
#include <stdio.h>

int main() {
    int A[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int B[2][3] = {{7, 8, 9}, {10, 11, 12}};
    int C[2][3];

    printf("Matrix A:\n");
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

    // Addition
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    printf("\nMatrix C (A + B):\n");
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
/* Output:
Matrix A:
1 2 3
4 5 6

Matrix B:
7 8 9
10 11 12

Matrix C (A + B):
8 10 12
14 16 18
*/
```

#### 2. Matrix Multiplication
```c
#include <stdio.h>

int main() {
    int A[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int B[3][2] = {{7, 8}, {9, 10}, {11, 12}};
    int C[2][2] = {0};

    // Matrix multiplication: C[i][j] = sum of A[i][k] * B[k][j]
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 3; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printf("Matrix A (2×3):\n");
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B (3×2):\n");
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 2; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix C (A × B) (2×2):\n");
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
/* Output:
Matrix A (2×3):
1 2 3
4 5 6

Matrix B (3×2):
7 8
9 10
11 12

Matrix C (A × B) (2×2):
58 64
139 154
*/
```

**Multiplication Visualization:**
```
C[0][0] = A[0][0]×B[0][0] + A[0][1]×B[1][0] + A[0][2]×B[2][0]
        = 1×7 + 2×9 + 3×11
        = 7 + 18 + 33 = 58

       B
     [7  8]
A    [9 10]
[1 2 3]  [11 12]
[4 5 6]

C[0][0]:  1×7 + 2×9 + 3×11 = 58
C[0][1]:  1×8 + 2×10 + 3×12 = 64
C[1][0]:  4×7 + 5×9 + 6×11 = 139
C[1][1]:  4×8 + 5×10 + 6×12 = 154
```

#### 3. Matrix Transpose
```c
#include <stdio.h>

int main() {
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int transpose[3][3];

    printf("Original Matrix:\n");
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Transpose: rows become columns
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            transpose[j][i] = matrix[i][j];
        }
    }

    printf("\nTranspose Matrix:\n");
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d ", transpose[i][j]);
        }
        printf("\n");
    }

    return 0;
}
/* Output:
Original Matrix:
1 2 3
4 5 6
7 8 9

Transpose Matrix:
1 4 7
2 5 8
3 6 9
*/
```

---

## Multidimensional Arrays

C supports arrays with more than two dimensions.

### 3D Array Example
```c
#include <stdio.h>

int main() {
    // 3D array: [layers][rows][columns]
    int arr3D[2][3][4] = {
        {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12}
        },
        {
            {13, 14, 15, 16},
            {17, 18, 19, 20},
            {21, 22, 23, 24}
        }
    };

    printf("3D Array:\n");
    for(int i = 0; i < 2; i++) {
        printf("Layer %d:\n", i);
        for(int j = 0; j < 3; j++) {
            for(int k = 0; k < 4; k++) {
                printf("%3d ", arr3D[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}
/* Output:
3D Array:
Layer 0:
  1   2   3   4
  5   6   7   8
  9  10  11  12

Layer 1:
 13  14  15  16
 17  18  19  20
 21  22  23  24
*/
```

**3D Array Visualization:**
```
Conceptual view: arr3D[2][3][4]

Layer 0:              Layer 1:
[1  2  3  4]          [13 14 15 16]
[5  6  7  8]          [17 18 19 20]
[9  10 11 12]         [21 22 23 24]

Think of it as a book:
- Layers = Pages
- Rows = Lines on a page
- Columns = Words in a line
```

---

## Array Manipulation

### Copying Arrays
```c
#include <stdio.h>

int main() {
    int source[5] = {1, 2, 3, 4, 5};
    int destination[5];

    // Manual copy
    for(int i = 0; i < 5; i++) {
        destination[i] = source[i];
    }

    printf("Source: ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", source[i]);
    }

    printf("\nDestination: ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", destination[i]);
    }
    printf("\n");

    return 0;
}
/* Output:
Source: 1 2 3 4 5
Destination: 1 2 3 4 5
*/
```

### Merging Arrays
```c
#include <stdio.h>

int main() {
    int arr1[3] = {1, 2, 3};
    int arr2[3] = {4, 5, 6};
    int merged[6];

    // Copy first array
    for(int i = 0; i < 3; i++) {
        merged[i] = arr1[i];
    }

    // Copy second array
    for(int i = 0; i < 3; i++) {
        merged[3 + i] = arr2[i];
    }

    printf("Array 1: ");
    for(int i = 0; i < 3; i++) printf("%d ", arr1[i]);

    printf("\nArray 2: ");
    for(int i = 0; i < 3; i++) printf("%d ", arr2[i]);

    printf("\nMerged: ");
    for(int i = 0; i < 6; i++) printf("%d ", merged[i]);
    printf("\n");

    return 0;
}
/* Output:
Array 1: 1 2 3
Array 2: 4 5 6
Merged: 1 2 3 4 5 6
*/
```

### Rotating Arrays
```c
#include <stdio.h>

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int size = 5;
    int temp, rotations = 2;

    printf("Original: ");
    for(int i = 0; i < size; i++) printf("%d ", arr[i]);

    // Rotate left by 2 positions
    for(int r = 0; r < rotations; r++) {
        temp = arr[0];
        for(int i = 0; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        arr[size - 1] = temp;
    }

    printf("\nRotated left by 2: ");
    for(int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
/* Output:
Original: 1 2 3 4 5
Rotated left by 2: 3 4 5 1 2
*/
```

---

## Arrays and Functions

Arrays are passed to functions by reference (address), not by value.

### Passing 1D Arrays
```c
#include <stdio.h>

void printArray(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int findSum(int arr[], int size) {
    int sum = 0;
    for(int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

void modifyArray(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        arr[i] *= 2;  // Double each element
    }
}

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int size = 5;

    printf("Original: ");
    printArray(numbers, size);

    printf("Sum: %d\n", findSum(numbers, size));

    modifyArray(numbers, size);
    printf("Modified: ");
    printArray(numbers, size);

    return 0;
}
/* Output:
Original: 10 20 30 40 50
Sum: 150
Modified: 20 40 60 80 100
*/
```

**Memory Diagram for Array Passing:**
```
main() memory:
+----------------------+
| numbers[]: [10,20,30]|
| Address: 1000        |
+----------------------+
        |
        | Pass address
        v
printArray() memory:
+----------------------+
| arr (pointer): 1000  |------> Points to same memory location
+----------------------+

Changes in function affect original array
because both reference the same memory!
```

### Passing 2D Arrays
```c
#include <stdio.h>

void printMatrix(int mat[][3], int rows) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int sumMatrix(int mat[][3], int rows) {
    int sum = 0;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < 3; j++) {
            sum += mat[i][j];
        }
    }
    return sum;
}

int main() {
    int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};

    printf("Matrix:\n");
    printMatrix(matrix, 2);

    printf("Sum of all elements: %d\n", sumMatrix(matrix, 2));

    return 0;
}
/* Output:
Matrix:
1 2 3
4 5 6
Sum of all elements: 21
*/
```

### Returning Arrays from Functions

Arrays cannot be returned directly, but you can:
1. Pass array to modify it
2. Return a pointer to array (advanced)
3. Use static arrays (limited use)

```c
#include <stdio.h>

void generateSquares(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        arr[i] = (i + 1) * (i + 1);
    }
}

int main() {
    int squares[5];

    generateSquares(squares, 5);

    printf("Squares: ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", squares[i]);
    }
    printf("\n");

    return 0;
}
// Output: Squares: 1 4 9 16 25
```

---

## Real-World Applications

### 1. Student Grade Management System
```c
#include <stdio.h>

int main() {
    int students = 5;
    int subjects = 3;
    int marks[5][3] = {
        {85, 90, 78},
        {92, 88, 95},
        {76, 82, 80},
        {88, 85, 90},
        {95, 92, 89}
    };
    char names[5][20] = {"Alice", "Bob", "Charlie", "Diana", "Eve"};

    printf("Student Report Card:\n");
    printf("%-10s %8s %8s %8s %10s %10s\n",
           "Name", "Math", "Science", "English", "Total", "Average");
    printf("------------------------------------------------------------\n");

    for(int i = 0; i < students; i++) {
        int total = 0;
        for(int j = 0; j < subjects; j++) {
            total += marks[i][j];
        }
        float average = (float)total / subjects;

        printf("%-10s %8d %8d %8d %10d %10.2f\n",
               names[i], marks[i][0], marks[i][1], marks[i][2],
               total, average);
    }

    return 0;
}
/* Output:
Student Report Card:
Name           Math  Science  English      Total    Average
------------------------------------------------------------
Alice            85       90       78        253      84.33
Bob              92       88       95        275      91.67
Charlie          76       82       80        238      79.33
Diana            88       85       90        263      87.67
Eve              95       92       89        276      92.00
*/
```

### 2. Tic-Tac-Toe Game Board
```c
#include <stdio.h>

void printBoard(char board[3][3]) {
    printf("\n");
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if(j < 2) printf("|");
        }
        printf("\n");
        if(i < 2) printf("---|---|---\n");
    }
    printf("\n");
}

int main() {
    char board[3][3] = {
        {'X', 'O', 'X'},
        {'O', 'X', 'O'},
        {'O', 'X', 'X'}
    };

    printf("Tic-Tac-Toe Board:");
    printBoard(board);

    return 0;
}
/* Output:
Tic-Tac-Toe Board:

 X | O | X
---|---|---
 O | X | O
---|---|---
 O | X | X
*/
```

### 3. Temperature Data Analysis
```c
#include <stdio.h>

int main() {
    float temperatures[7] = {23.5, 25.0, 22.8, 24.3, 26.1, 23.9, 24.7};
    char days[7][10] = {"Monday", "Tuesday", "Wednesday",
                        "Thursday", "Friday", "Saturday", "Sunday"};
    float sum = 0, max, min;

    max = min = temperatures[0];

    printf("Weekly Temperature Report:\n");
    printf("%-12s %12s\n", "Day", "Temperature");
    printf("----------------------------\n");

    for(int i = 0; i < 7; i++) {
        printf("%-12s %10.1f°C\n", days[i], temperatures[i]);
        sum += temperatures[i];

        if(temperatures[i] > max) max = temperatures[i];
        if(temperatures[i] < min) min = temperatures[i];
    }

    printf("\nStatistics:\n");
    printf("Average: %.1f°C\n", sum / 7);
    printf("Maximum: %.1f°C\n", max);
    printf("Minimum: %.1f°C\n", min);

    return 0;
}
/* Output:
Weekly Temperature Report:
Day          Temperature
----------------------------
Monday            23.5°C
Tuesday           25.0°C
Wednesday         22.8°C
Thursday          24.3°C
Friday            26.1°C
Saturday          23.9°C
Sunday            24.7°C

Statistics:
Average: 24.3°C
Maximum: 26.1°C
Minimum: 22.8°C
*/
```

### 4. Sales Data by Product and Month
```c
#include <stdio.h>

int main() {
    int sales[3][4] = {  // 3 products, 4 months
        {120, 135, 150, 145},
        {200, 195, 210, 225},
        {80, 95, 105, 110}
    };
    char products[3][15] = {"Product A", "Product B", "Product C"};
    char months[4][10] = {"Jan", "Feb", "Mar", "Apr"};

    printf("Sales Report:\n");
    printf("%-12s", "Product");
    for(int j = 0; j < 4; j++) {
        printf("%8s", months[j]);
    }
    printf("%10s\n", "Total");
    printf("--------------------------------------------------\n");

    int grandTotal = 0;

    for(int i = 0; i < 3; i++) {
        printf("%-12s", products[i]);
        int productTotal = 0;

        for(int j = 0; j < 4; j++) {
            printf("%8d", sales[i][j]);
            productTotal += sales[i][j];
        }

        printf("%10d\n", productTotal);
        grandTotal += productTotal;
    }

    printf("--------------------------------------------------\n");
    printf("Grand Total: %d units\n", grandTotal);

    return 0;
}
/* Output:
Sales Report:
Product         Jan     Feb     Mar     Apr     Total
--------------------------------------------------
Product A       120     135     150     145       550
Product B       200     195     210     225       830
Product C        80      95     105     110       390
--------------------------------------------------
Grand Total: 1770 units
*/
```

---

## Practice Exercises

### Basic Level

**Exercise 1:** Write a program to find the second largest element in an array.

**Exercise 2:** Create a program that counts the frequency of each element in an array. For example, in {1, 2, 2, 3, 3, 3}, frequency of 3 is 3.

**Exercise 3:** Write a program to check if an array is sorted in ascending order.

### Intermediate Level

**Exercise 4:** Implement a program to remove duplicate elements from an array and display the unique elements.

**Exercise 5:** Create a program that checks if a given matrix is an identity matrix (diagonal elements are 1, all others are 0).

**Exercise 6:** Write a program to find the sum of diagonal elements of a square matrix.

### Advanced Level

**Exercise 7:** Implement a program that performs binary search on a sorted array. Compare its efficiency with linear search by counting the number of comparisons.

**Hints:**
- Exercise 1: Find max, then find max excluding the first max
- Exercise 2: Use nested loops - for each element, count occurrences
- Exercise 3: Compare each element with the next one
- Exercise 4: Copy only first occurrence of each element to new array
- Exercise 5: Check if matrix[i][i] == 1 and matrix[i][j] == 0 for i != j
- Exercise 6: Sum elements where row index equals column index
- Exercise 7: Keep dividing array in half; return when element found or array exhausted

---

## Key Takeaways

1. **Arrays** store multiple elements of the same type in contiguous memory
2. **Index** starts from 0 and goes up to size-1
3. **1D arrays** are linear; **2D arrays** are like tables
4. **Arrays are passed by reference** to functions (modifications affect original)
5. **Always pass size** when passing arrays to functions
6. **Boundary checking** is crucial - accessing out-of-bounds causes errors
7. **Memory layout** is row-major order (rows stored sequentially)

---

## Best Practices

1. **Initialize arrays** to avoid garbage values
2. **Use constants** for array sizes: `#define SIZE 10`
3. **Check bounds** before accessing elements
4. **Use meaningful names**: `scores[]` instead of `arr[]`
5. **Pass size parameter** with arrays to functions
6. **Comment array dimensions** for multidimensional arrays
7. **Consider memory** - large arrays may cause stack overflow

---

**Next Topic:** [Strings](04-strings.md) - Master character arrays and string manipulation!
