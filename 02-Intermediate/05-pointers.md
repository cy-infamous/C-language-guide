# Pointers in C

## Table of Contents
1. [Introduction to Pointers](#introduction-to-pointers)
2. [Pointer Basics](#pointer-basics)
3. [Pointer Arithmetic](#pointer-arithmetic)
4. [Pointers and Arrays](#pointers-and-arrays)
5. [Pointers and Functions](#pointers-and-functions)
6. [Advanced Pointer Concepts](#advanced-pointer-concepts)
7. [Real-World Applications](#real-world-applications)
8. [Practice Exercises](#practice-exercises)

---

## Introduction to Pointers

A pointer is a variable that stores the memory address of another variable. Pointers are one of the most powerful and distinctive features of C.

### Why Use Pointers?

Pointers enable:
- **Dynamic memory allocation** - Create variables at runtime
- **Efficient array handling** - Process large data without copying
- **Pass by reference** - Modify variables in functions
- **Data structures** - Build linked lists, trees, graphs
- **System programming** - Direct memory manipulation
- **Function pointers** - Implement callbacks and flexible code

### Memory Address Concept

Every variable in C is stored at a specific memory location (address).

**Memory Visualization:**
```
Memory Layout:

Address     Variable     Value
+--------+  +--------+  +-------+
| 1000   |  | int x  |  |   42  |
+--------+  +--------+  +-------+
| 1004   |  | int y  |  |   10  |
+--------+  +--------+  +-------+
| 1008   |  | int *p |  |  1000 | <- p stores address of x
+--------+  +--------+  +-------+

p is a pointer to x
p = 1008 (p's own address)
*p = 42 (value at address stored in p)
&x = 1000 (address of x)
```

---

## Pointer Basics

### Declaration and Initialization

**Syntax:**
```c
data_type *pointer_name;
```

**Examples:**
```c
#include <stdio.h>

int main() {
    int x = 42;
    int *ptr;        // Declare pointer

    ptr = &x;        // Initialize pointer with address of x

    printf("Value of x: %d\n", x);
    printf("Address of x: %p\n", (void*)&x);
    printf("Value of ptr: %p\n", (void*)ptr);
    printf("Value pointed to by ptr: %d\n", *ptr);

    return 0;
}
/* Output:
Value of x: 42
Address of x: 0x7ffc8b9d3c1c
Value of ptr: 0x7ffc8b9d3c1c
Value pointed to by ptr: 42
*/
```

### Key Operators

1. **Address-of operator (&)** - Gets memory address of a variable
2. **Dereference operator (*)** - Accesses value at an address

**Memory Diagram:**
```
Before: int x = 42;

Memory:
Address: 1000
        +----+
x       | 42 |
        +----+


After: int *ptr = &x;

Memory:
Address: 1000              Address: 2000
        +----+                    +------+
x       | 42 | <----------------- | 1000 |  ptr
        +----+                    +------+

&x    = 1000 (address of x)
ptr   = 1000 (value stored in ptr)
*ptr  = 42   (value at address 1000)
&ptr  = 2000 (address of ptr itself)
```

### Different Types of Pointers

```c
#include <stdio.h>

int main() {
    int i = 10;
    float f = 3.14;
    char c = 'A';

    int *iptr = &i;
    float *fptr = &f;
    char *cptr = &c;

    printf("Integer: %d, Address: %p\n", *iptr, (void*)iptr);
    printf("Float: %.2f, Address: %p\n", *fptr, (void*)fptr);
    printf("Character: %c, Address: %p\n", *cptr, (void*)cptr);

    return 0;
}
```

### Pointer Size

Pointer size depends on the system architecture:
- 32-bit system: 4 bytes
- 64-bit system: 8 bytes

```c
#include <stdio.h>

int main() {
    int *p1;
    float *p2;
    char *p3;
    double *p4;

    printf("Size of int pointer: %zu bytes\n", sizeof(p1));
    printf("Size of float pointer: %zu bytes\n", sizeof(p2));
    printf("Size of char pointer: %zu bytes\n", sizeof(p3));
    printf("Size of double pointer: %zu bytes\n", sizeof(p4));

    return 0;
}
/* Output (on 64-bit system):
Size of int pointer: 8 bytes
Size of float pointer: 8 bytes
Size of char pointer: 8 bytes
Size of double pointer: 8 bytes
*/
```

### NULL Pointer

A pointer that doesn't point to any valid memory location.

```c
#include <stdio.h>

int main() {
    int *ptr = NULL;  // Good practice: initialize to NULL

    if(ptr == NULL) {
        printf("Pointer is NULL\n");
    }

    // Always check before dereferencing
    if(ptr != NULL) {
        printf("Value: %d\n", *ptr);
    } else {
        printf("Cannot dereference NULL pointer\n");
    }

    return 0;
}
/* Output:
Pointer is NULL
Cannot dereference NULL pointer
*/
```

### Pointer Assignment

```c
#include <stdio.h>

int main() {
    int x = 10, y = 20;
    int *ptr;

    ptr = &x;
    printf("ptr points to x: %d\n", *ptr);

    ptr = &y;  // Reassign pointer
    printf("ptr now points to y: %d\n", *ptr);

    *ptr = 50;  // Modify y through pointer
    printf("y is now: %d\n", y);

    return 0;
}
/* Output:
ptr points to x: 10
ptr now points to y: 20
y is now: 50
*/
```

**Memory Visualization:**
```
Step 1: ptr = &x
        +----+              +------+
x (10)  | 10 | <----------- | addr |  ptr
        +----+              +------+
        +----+
y (20)  | 20 |
        +----+

Step 2: ptr = &y
        +----+
x (10)  | 10 |
        +----+              +------+
        +----+ <----------- | addr |  ptr
y (20)  | 20 |              +------+
        +----+

Step 3: *ptr = 50
        +----+
x (10)  | 10 |
        +----+              +------+
        +----+ <----------- | addr |  ptr
y (50)  | 50 |  (modified) +------+
        +----+
```

---

## Pointer Arithmetic

Pointer arithmetic allows you to perform addition, subtraction, and comparison operations on pointers.

### Basic Operations

```c
#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;  // Points to first element

    printf("Initial pointer value (address): %p\n", (void*)ptr);
    printf("Value at ptr: %d\n", *ptr);

    ptr++;  // Move to next integer
    printf("\nAfter ptr++:\n");
    printf("Pointer value: %p\n", (void*)ptr);
    printf("Value at ptr: %d\n", *ptr);

    ptr += 2;  // Move forward by 2 integers
    printf("\nAfter ptr += 2:\n");
    printf("Pointer value: %p\n", (void*)ptr);
    printf("Value at ptr: %d\n", *ptr);

    ptr--;  // Move back by 1 integer
    printf("\nAfter ptr--:\n");
    printf("Pointer value: %p\n", (void*)ptr);
    printf("Value at ptr: %d\n", *ptr);

    return 0;
}
/* Output:
Initial pointer value (address): 0x7ffc8b9d3c00
Value at ptr: 10

After ptr++:
Pointer value: 0x7ffc8b9d3c04
Value at ptr: 20

After ptr += 2:
Pointer value: 0x7ffc8b9d3c0c
Value at ptr: 40

After ptr--:
Pointer value: 0x7ffc8b9d3c08
Value at ptr: 30
*/
```

### Pointer Arithmetic Rules

**Key Concept:** When you add/subtract from a pointer, it moves by `sizeof(data_type)` bytes.

**Memory Diagram:**
```
Array: int arr[] = {10, 20, 30, 40, 50};

Address:  1000  1004  1008  1012  1016
        +----+----+----+----+----+
arr     | 10 | 20 | 30 | 40 | 50 |
        +----+----+----+----+----+
         ^
         ptr

ptr = 1000
ptr + 1 = 1004 (not 1001!)
ptr + 2 = 1008
ptr + 3 = 1012
ptr + 4 = 1016

Formula: new_address = ptr + (n × sizeof(int))
         new_address = 1000 + (2 × 4) = 1008
```

### Pointer Arithmetic with Different Data Types

```c
#include <stdio.h>

int main() {
    int intArr[] = {1, 2, 3};
    char charArr[] = {'A', 'B', 'C'};
    double doubleArr[] = {1.1, 2.2, 3.3};

    int *iptr = intArr;
    char *cptr = charArr;
    double *dptr = doubleArr;

    printf("Initial addresses:\n");
    printf("iptr: %p\n", (void*)iptr);
    printf("cptr: %p\n", (void*)cptr);
    printf("dptr: %p\n", (void*)dptr);

    iptr++; cptr++; dptr++;

    printf("\nAfter increment:\n");
    printf("iptr: %p (moved %zu bytes)\n", (void*)iptr, sizeof(int));
    printf("cptr: %p (moved %zu bytes)\n", (void*)cptr, sizeof(char));
    printf("dptr: %p (moved %zu bytes)\n", (void*)dptr, sizeof(double));

    return 0;
}
/* Output (typical):
Initial addresses:
iptr: 0x7ffc8b9d3c00
cptr: 0x7ffc8b9d3c10
dptr: 0x7ffc8b9d3c20

After increment:
iptr: 0x7ffc8b9d3c04 (moved 4 bytes)
cptr: 0x7ffc8b9d3c11 (moved 1 bytes)
dptr: 0x7ffc8b9d3c28 (moved 8 bytes)
*/
```

### Pointer Comparison

```c
#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr1 = &arr[1];  // Points to 20
    int *ptr2 = &arr[3];  // Points to 40

    printf("ptr1 points to: %d\n", *ptr1);
    printf("ptr2 points to: %d\n", *ptr2);

    if(ptr1 < ptr2) {
        printf("ptr1 is at lower address than ptr2\n");
    }

    if(ptr1 != ptr2) {
        printf("ptr1 and ptr2 point to different locations\n");
    }

    // Pointer subtraction (gives number of elements)
    int diff = ptr2 - ptr1;
    printf("Difference: %d elements\n", diff);

    return 0;
}
/* Output:
ptr1 points to: 20
ptr2 points to: 40
ptr1 is at lower address than ptr2
ptr1 and ptr2 point to different locations
Difference: 2 elements
*/
```

---

## Pointers and Arrays

Arrays and pointers are closely related in C. An array name acts as a pointer to its first element.

### Array-Pointer Equivalence

```c
#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};

    // These are equivalent:
    printf("arr[0] = %d\n", arr[0]);
    printf("*arr = %d\n", *arr);

    printf("arr[2] = %d\n", arr[2]);
    printf("*(arr + 2) = %d\n", *(arr + 2));

    // Array name is address of first element
    printf("\n&arr[0] = %p\n", (void*)&arr[0]);
    printf("arr = %p\n", (void*)arr);

    return 0;
}
/* Output:
arr[0] = 10
*arr = 10
arr[2] = 30
*(arr + 2) = 30

&arr[0] = 0x7ffc8b9d3c00
arr = 0x7ffc8b9d3c00
*/
```

**Equivalence Rules:**
```
arr[i]  ≡  *(arr + i)
&arr[i] ≡  arr + i
```

### Traversing Arrays with Pointers

**Method 1: Array Indexing**
```c
#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = 5;

    printf("Using array indexing:\n");
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
```

**Method 2: Pointer Arithmetic**
```c
#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = 5;
    int *ptr = arr;

    printf("Using pointer arithmetic:\n");
    for(int i = 0; i < size; i++) {
        printf("%d ", *(ptr + i));
    }
    printf("\n");

    return 0;
}
```

**Method 3: Pointer Increment**
```c
#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = 5;
    int *ptr = arr;
    int *end = arr + size;

    printf("Using pointer increment:\n");
    while(ptr < end) {
        printf("%d ", *ptr);
        ptr++;
    }
    printf("\n");

    return 0;
}
```

**Memory Visualization:**
```
Array: int arr[] = {10, 20, 30, 40, 50};

Address:  1000  1004  1008  1012  1016
        +----+----+----+----+----+
arr     | 10 | 20 | 30 | 40 | 50 |
        +----+----+----+----+----+

Access methods:
arr[2]        -> value at index 2 -> 30
*(arr + 2)    -> value at (base + 2*sizeof(int)) -> 30
ptr = arr + 2 -> ptr points to address 1008
*ptr          -> value at address 1008 -> 30
```

### Pointer to Array

```c
#include <stdio.h>

int main() {
    int arr[5] = {10, 20, 30, 40, 50};

    // Pointer to entire array
    int (*ptr)[5] = &arr;

    printf("Array elements:\n");
    for(int i = 0; i < 5; i++) {
        printf("%d ", (*ptr)[i]);
    }
    printf("\n");

    return 0;
}
```

### Array of Pointers

```c
#include <stdio.h>

int main() {
    int a = 10, b = 20, c = 30;
    int *ptrArray[3];  // Array of 3 integer pointers

    ptrArray[0] = &a;
    ptrArray[1] = &b;
    ptrArray[2] = &c;

    printf("Values using array of pointers:\n");
    for(int i = 0; i < 3; i++) {
        printf("ptrArray[%d] points to: %d\n", i, *ptrArray[i]);
    }

    return 0;
}
/* Output:
Values using array of pointers:
ptrArray[0] points to: 10
ptrArray[1] points to: 20
ptrArray[2] points to: 30
*/
```

**Memory Diagram:**
```
Variables:
Address: 1000     1004     1008
        +----+   +----+   +----+
a       | 10 |   | 20 |   | 30 |
        +----+   +----+   +----+
                b        c

Array of Pointers:
Address:  2000    2008    2016
        +------+------+------+
ptrArray| 1000 | 1004 | 1008 |
        +------+------+------+
          |      |      |
          v      v      v
         10     20     30
```

---

## Pointers and Functions

Pointers enable pass-by-reference, allowing functions to modify the original variables.

### Pass by Value vs Pass by Reference

**Pass by Value (Cannot Modify Original):**
```c
#include <stdio.h>

void swap(int x, int y) {
    int temp = x;
    x = y;
    y = temp;
    printf("Inside function: x = %d, y = %d\n", x, y);
}

int main() {
    int a = 10, b = 20;

    printf("Before swap: a = %d, b = %d\n", a, b);
    swap(a, b);
    printf("After swap: a = %d, b = %d\n", a, b);

    return 0;
}
/* Output:
Before swap: a = 10, b = 20
Inside function: x = 20, y = 10
After swap: a = 10, b = 20  (unchanged!)
*/
```

**Pass by Reference (Can Modify Original):**
```c
#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
    printf("Inside function: *x = %d, *y = %d\n", *x, *y);
}

int main() {
    int a = 10, b = 20;

    printf("Before swap: a = %d, b = %d\n", a, b);
    swap(&a, &b);  // Pass addresses
    printf("After swap: a = %d, b = %d\n", a, b);

    return 0;
}
/* Output:
Before swap: a = 10, b = 20
Inside function: *x = 20, *y = 10
After swap: a = 20, b = 10  (swapped!)
*/
```

**Memory Visualization:**
```
Pass by Value:
main():         swap():
a = 10          x = 10 (copy)
b = 20          y = 20 (copy)
                Swap x and y
                (originals unchanged)

Pass by Reference:
main():                 swap():
a = 10 <--------------- *x modifies a
b = 20 <--------------- *y modifies b
Address: 1000          x = 1000
Address: 1004          y = 1004
```

### Returning Multiple Values

```c
#include <stdio.h>

void findMinMax(int arr[], int size, int *min, int *max) {
    *min = arr[0];
    *max = arr[0];

    for(int i = 1; i < size; i++) {
        if(arr[i] < *min) *min = arr[i];
        if(arr[i] > *max) *max = arr[i];
    }
}

int main() {
    int numbers[] = {45, 23, 67, 12, 89, 34};
    int size = 6;
    int minimum, maximum;

    findMinMax(numbers, size, &minimum, &maximum);

    printf("Minimum: %d\n", minimum);
    printf("Maximum: %d\n", maximum);

    return 0;
}
/* Output:
Minimum: 12
Maximum: 89
*/
```

### Passing Arrays to Functions

```c
#include <stdio.h>

// All three declarations are equivalent:
void processArray1(int arr[], int size);
void processArray2(int *arr, int size);
void processArray3(int arr[10], int size);  // Size ignored

void printArray(int *arr, int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void modifyArray(int *arr, int size) {
    for(int i = 0; i < size; i++) {
        arr[i] *= 2;
    }
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = 5;

    printf("Original: ");
    printArray(numbers, size);

    modifyArray(numbers, size);

    printf("Modified: ");
    printArray(numbers, size);

    return 0;
}
/* Output:
Original: 1 2 3 4 5
Modified: 2 4 6 8 10
*/
```

### Function Returning Pointer

```c
#include <stdio.h>

int* findMax(int *arr, int size) {
    int *maxPtr = arr;

    for(int i = 1; i < size; i++) {
        if(arr[i] > *maxPtr) {
            maxPtr = &arr[i];
        }
    }

    return maxPtr;
}

int main() {
    int numbers[] = {45, 23, 67, 12, 89, 34};
    int size = 6;

    int *max = findMax(numbers, size);

    printf("Maximum value: %d\n", *max);
    printf("At index: %ld\n", max - numbers);

    return 0;
}
/* Output:
Maximum value: 89
At index: 4
*/
```

---

## Advanced Pointer Concepts

### Pointer to Pointer (Double Pointer)

```c
#include <stdio.h>

int main() {
    int x = 42;
    int *ptr = &x;      // Pointer to int
    int **pptr = &ptr;  // Pointer to pointer

    printf("Value of x: %d\n", x);
    printf("Value using *ptr: %d\n", *ptr);
    printf("Value using **pptr: %d\n", **pptr);

    printf("\nAddress of x: %p\n", (void*)&x);
    printf("Value of ptr: %p\n", (void*)ptr);
    printf("Value of pptr: %p\n", (void*)pptr);

    // Modify through double pointer
    **pptr = 100;
    printf("\nAfter **pptr = 100:\n");
    printf("x = %d\n", x);

    return 0;
}
```

**Memory Diagram:**
```
Address:  1000        2000         3000
        +------+    +------+     +------+
x       |  42  |    | 1000 |     | 2000 |
        +------+    +------+     +------+
                    ptr          pptr

Relationships:
x     = 42       (value)
&x    = 1000     (address of x)
ptr   = 1000     (stores address of x)
*ptr  = 42       (value at address 1000)
&ptr  = 2000     (address of ptr)
pptr  = 2000     (stores address of ptr)
*pptr = 1000     (value at address 2000, which is ptr)
**pptr= 42       (value at address stored in ptr)
```

### Const Pointers

```c
#include <stdio.h>

int main() {
    int x = 10, y = 20;

    // 1. Pointer to constant (cannot change value)
    const int *ptr1 = &x;
    // *ptr1 = 15;  // ERROR
    ptr1 = &y;      // OK

    // 2. Constant pointer (cannot change address)
    int *const ptr2 = &x;
    *ptr2 = 15;     // OK
    // ptr2 = &y;   // ERROR

    // 3. Constant pointer to constant (cannot change both)
    const int *const ptr3 = &x;
    // *ptr3 = 15;  // ERROR
    // ptr3 = &y;   // ERROR

    return 0;
}
```

### Void Pointer (Generic Pointer)

```c
#include <stdio.h>

int main() {
    int i = 10;
    float f = 3.14;
    char c = 'A';

    void *ptr;  // Can point to any data type

    ptr = &i;
    printf("Integer: %d\n", *(int*)ptr);

    ptr = &f;
    printf("Float: %.2f\n", *(float*)ptr);

    ptr = &c;
    printf("Character: %c\n", *(char*)ptr);

    return 0;
}
/* Output:
Integer: 10
Float: 3.14
Character: A
*/
```

---

## Real-World Applications

### 1. Dynamic Array Resizing
```c
#include <stdio.h>

void reverseArray(int *arr, int size) {
    int *left = arr;
    int *right = arr + size - 1;
    int temp;

    while(left < right) {
        temp = *left;
        *left = *right;
        *right = temp;
        left++;
        right--;
    }
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = 10;

    printf("Original: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }

    reverseArray(numbers, size);

    printf("\nReversed: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}
/* Output:
Original: 1 2 3 4 5 6 7 8 9 10
Reversed: 10 9 8 7 6 5 4 3 2 1
*/
```

### 2. String Manipulation with Pointers
```c
#include <stdio.h>

int stringLength(char *str) {
    char *ptr = str;
    while(*ptr != '\0') {
        ptr++;
    }
    return ptr - str;
}

void stringCopy(char *dest, char *src) {
    while(*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

int main() {
    char source[] = "Hello World";
    char destination[50];

    printf("Source: %s\n", source);
    printf("Length: %d\n", stringLength(source));

    stringCopy(destination, source);
    printf("Destination: %s\n", destination);

    return 0;
}
/* Output:
Source: Hello World
Length: 11
Destination: Hello World
*/
```

### 3. Matrix Operations with Pointers
```c
#include <stdio.h>

void printMatrix(int *mat, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            printf("%3d ", *(mat + i * cols + j));
        }
        printf("\n");
    }
}

int main() {
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    printf("Matrix:\n");
    printMatrix((int*)matrix, 3, 4);

    return 0;
}
/* Output:
Matrix:
  1   2   3   4
  5   6   7   8
  9  10  11  12
*/
```

### 4. Sorting with Pointers (Bubble Sort)
```c
#include <stdio.h>

void bubbleSort(int *arr, int size) {
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(*(arr + j) > *(arr + j + 1)) {
                // Swap using pointers
                int temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }
}

int main() {
    int numbers[] = {64, 34, 25, 12, 22, 11, 90};
    int size = 7;

    printf("Original: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }

    bubbleSort(numbers, size);

    printf("\nSorted: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}
/* Output:
Original: 64 34 25 12 22 11 90
Sorted: 11 12 22 25 34 64 90
*/
```

### 5. Linked List Node (Preview)
```c
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

void printList(struct Node *head) {
    struct Node *current = head;

    printf("Linked List: ");
    while(current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    // Create nodes manually (simplified)
    struct Node node1, node2, node3;

    node1.data = 10;
    node1.next = &node2;

    node2.data = 20;
    node2.next = &node3;

    node3.data = 30;
    node3.next = NULL;

    printList(&node1);

    return 0;
}
/* Output:
Linked List: 10 -> 20 -> 30 -> NULL
*/
```

**Linked List Memory Diagram:**
```
Node 1:           Node 2:           Node 3:
+------+------+  +------+------+  +------+------+
| 10   | next |->| 20   | next |->| 30   | NULL |
+------+------+  +------+------+  +------+------+
  ^
  |
head
```

---

## Practice Exercises

### Basic Level

**Exercise 1:** Write a program that uses pointers to swap two numbers. Verify the swap in the main function.

**Exercise 2:** Create a function that takes an array and its size as parameters and returns the sum of all elements using pointer arithmetic.

**Exercise 3:** Write a program to find the address difference between consecutive elements of an integer array and a character array.

### Intermediate Level

**Exercise 4:** Implement a function that takes a string (character array) and returns the number of vowels using pointers. Do not use array indexing.

**Exercise 5:** Create a function that rotates an array to the right by n positions using pointers. For example, {1,2,3,4,5} rotated by 2 becomes {4,5,1,2,3}.

**Exercise 6:** Write a program that uses pointers to find the second largest element in an array without sorting it.

### Advanced Level

**Exercise 7:** Implement a function that takes a 2D array (matrix) using a pointer to pointer and transposes it (swap rows and columns). Display both original and transposed matrices.

**Hints:**
- Exercise 1: Pass addresses using &, use * to modify values
- Exercise 2: Use loop with *(arr + i) or increment pointer
- Exercise 3: Use sizeof() and pointer arithmetic
- Exercise 4: Increment pointer through string, check each character
- Exercise 5: Save last n elements, shift rest right, place saved elements at start
- Exercise 6: Find max first, then find max excluding the first max
- Exercise 7: Create new matrix where new[j][i] = old[i][j]

---

## Key Takeaways

1. **Pointers store memory addresses** of variables
2. **& operator** gets address, **\* operator** dereferences (gets value)
3. **Pointer arithmetic** moves by sizeof(data_type) bytes
4. **Arrays and pointers** are closely related: arr[i] ≡ *(arr + i)
5. **Pass by reference** uses pointers to modify original variables
6. **NULL pointers** should always be checked before dereferencing
7. **Pointer types matter** for arithmetic and dereferencing

---

## Best Practices

1. **Initialize pointers** to NULL or valid address
2. **Check for NULL** before dereferencing
3. **Use const** when pointer shouldn't modify data
4. **Match pointer types** with variable types
5. **Be careful with pointer arithmetic** - easy to go out of bounds
6. **Document pointer ownership** - who allocates and frees memory
7. **Avoid dangling pointers** - don't use after the pointed-to variable is destroyed

---

## Common Pitfalls

1. **Uninitialized pointers** - pointing to random memory
2. **Dereferencing NULL** - causes segmentation fault
3. **Out-of-bounds access** - pointer arithmetic beyond array
4. **Type mismatches** - using wrong pointer type
5. **Dangling pointers** - pointer to freed/destroyed memory
6. **Memory leaks** - forgetting to free dynamically allocated memory
7. **Lost pointer** - no way to access allocated memory

---

**Next Topic:** [Structures](06-structures.md) - Learn to create custom data types and organize complex data!
