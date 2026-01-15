# Dynamic Memory Management in C

## Table of Contents
1. [Introduction to Dynamic Memory](#introduction)
2. [Memory Layout](#memory-layout)
3. [Dynamic Memory Functions](#dynamic-memory-functions)
4. [Memory Leaks and Management](#memory-leaks)
5. [Best Practices](#best-practices)
6. [Practice Exercises](#practice-exercises)

---

## Introduction to Dynamic Memory

Dynamic memory allocation allows programs to request memory at runtime, enabling flexible data structures whose size isn't known at compile time. Unlike stack memory (automatic storage), heap memory persists until explicitly freed.

### Why Dynamic Memory?

- **Flexibility**: Allocate memory based on runtime conditions
- **Efficiency**: Use only the memory you need
- **Large Data**: Store data too large for the stack
- **Data Structures**: Build dynamic arrays, linked lists, trees, etc.

---

## Memory Layout

Understanding how a C program's memory is organized is crucial for effective dynamic memory management.

```
High Memory Address
+------------------+
|  Command Line    |
|  & Environment   |
+------------------+
|      STACK       | ↓ Grows downward
|  (Local vars,    |
|   function calls)|
+------------------+
|        ↓         |
|                  |
|    Free Space    |
|                  |
|        ↑         |
+------------------+
|      HEAP        | ↑ Grows upward
|  (Dynamic alloc) |
+------------------+
|   Uninitialized  |
|   Data (BSS)     |
|  (Uninit globals)|
+------------------+
|  Initialized     |
|      Data        |
|  (Init globals)  |
+------------------+
|   Text/Code      |
|  (Instructions)  |
+------------------+
Low Memory Address
```

### Memory Characteristics

| Memory Type | Allocation | Deallocation | Size | Speed | Lifetime |
|-------------|------------|--------------|------|-------|----------|
| **Stack** | Automatic | Automatic | Limited (~1-8 MB) | Fast | Function scope |
| **Heap** | Manual | Manual | Large (GB) | Slower | Until freed |
| **Static** | Compile-time | Program end | Fixed | Fast | Program lifetime |

---

## Dynamic Memory Functions

### 1. malloc() - Memory Allocation

```c
void* malloc(size_t size);
```

Allocates a block of memory of specified size (in bytes) and returns a pointer to the beginning of the block. Memory is **uninitialized** (contains garbage values).

**Example:**

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr;
    int n = 5;

    // Allocate memory for 5 integers
    ptr = (int*) malloc(n * sizeof(int));

    // Check if allocation was successful
    if (ptr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Initialize and use the memory
    for (int i = 0; i < n; i++) {
        ptr[i] = i + 1;
        printf("ptr[%d] = %d\n", i, ptr[i]);
    }

    // Free the memory
    free(ptr);
    ptr = NULL;  // Good practice

    return 0;
}
```

**Memory Diagram After malloc:**

```
Before malloc:
ptr: [????]

After malloc(5 * sizeof(int)):
ptr: [0x1000] ──→ Heap: [????][????][????][????][????]
                         0x1000 (20 bytes allocated)

After initialization:
ptr: [0x1000] ──→ Heap: [1][2][3][4][5]
```

---

### 2. calloc() - Contiguous Allocation

```c
void* calloc(size_t num, size_t size);
```

Allocates memory for an array of `num` elements, each of `size` bytes. Unlike malloc, **initializes all bytes to zero**.

**Example:**

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr;
    int n = 5;

    // Allocate and initialize to 0
    arr = (int*) calloc(n, sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Values initialized by calloc:\n");
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);  // All will be 0
    }

    free(arr);
    return 0;
}
```

**malloc vs calloc:**

| Feature | malloc | calloc |
|---------|--------|--------|
| **Parameters** | 1 (total size) | 2 (count, size) |
| **Initialization** | Uninitialized | Zero-initialized |
| **Speed** | Faster | Slightly slower |
| **Use Case** | Will initialize manually | Need zero values |

---

### 3. realloc() - Reallocation

```c
void* realloc(void *ptr, size_t new_size);
```

Changes the size of previously allocated memory block. Can expand or shrink. Returns pointer to new location (may be different from original).

**Example:**

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr;
    int n = 3;

    // Initial allocation
    arr = (int*) malloc(n * sizeof(int));
    if (arr == NULL) return 1;

    // Initialize
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Expand to 6 elements
    n = 6;
    int *temp = (int*) realloc(arr, n * sizeof(int));

    if (temp == NULL) {
        printf("Reallocation failed!\n");
        free(arr);  // Original memory still valid
        return 1;
    }

    arr = temp;  // Update pointer

    // Initialize new elements
    for (int i = 3; i < n; i++) {
        arr[i] = i + 1;
    }

    printf("Expanded array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}
```

**realloc Behavior:**

```
Case 1: Enough space at current location
Before: [1][2][3][X][X]...
After:  [1][2][3][4][5][6] (same location)

Case 2: Not enough space, must move
Before: Location A: [1][2][3][IN USE]...
After:  Location B: [1][2][3][4][5][6] (new location)
        Location A: [freed automatically]

Case 3: ptr is NULL
realloc(NULL, size) ≡ malloc(size)

Case 4: size is 0
realloc(ptr, 0) ≡ free(ptr)
```

**Important realloc Points:**

1. **Always assign to temporary pointer first** to avoid losing original pointer if realloc fails
2. **Old pointer becomes invalid** if realloc moves the memory
3. **New memory is uninitialized** (beyond original size)
4. **Existing data is preserved** up to the smaller of old/new size

---

### 4. free() - Deallocation

```c
void free(void *ptr);
```

Releases previously allocated memory back to the heap. The pointer itself is not destroyed, only the memory it points to.

**Example:**

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = (int*) malloc(sizeof(int));

    if (ptr == NULL) return 1;

    *ptr = 42;
    printf("Value: %d\n", *ptr);

    free(ptr);  // Memory released
    ptr = NULL; // Prevent dangling pointer

    // ptr is now NULL, safe to check
    if (ptr != NULL) {
        printf("Value: %d\n", *ptr);  // Won't execute
    }

    return 0;
}
```

**Critical free() Rules:**

1. **Free only dynamically allocated memory** (from malloc/calloc/realloc)
2. **Free each block exactly once** (double-free is undefined behavior)
3. **Don't use pointer after free** (dangling pointer)
4. **Set pointer to NULL after free** (defensive programming)
5. **free(NULL) is safe** (does nothing)

---

## Memory Leaks and Management

### What is a Memory Leak?

A memory leak occurs when dynamically allocated memory is not freed, making it unavailable for reuse. Repeated leaks can exhaust system memory.

### Common Causes of Memory Leaks

#### 1. Forgetting to Free

```c
// BAD: Memory leak
void bad_function() {
    int *ptr = (int*) malloc(100 * sizeof(int));
    // ... use ptr ...
    // Oops! No free() call
}

// GOOD: Properly freed
void good_function() {
    int *ptr = (int*) malloc(100 * sizeof(int));
    if (ptr == NULL) return;

    // ... use ptr ...

    free(ptr);
    ptr = NULL;
}
```

#### 2. Lost Pointer

```c
// BAD: Lost pointer to allocated memory
int *ptr = (int*) malloc(10 * sizeof(int));
ptr = (int*) malloc(20 * sizeof(int));  // First block leaked!

// GOOD: Free before reassigning
int *ptr = (int*) malloc(10 * sizeof(int));
free(ptr);
ptr = (int*) malloc(20 * sizeof(int));
```

#### 3. Early Return Without Free

```c
// BAD: Early return causes leak
int process_data(int n) {
    int *data = (int*) malloc(n * sizeof(int));
    if (data == NULL) return -1;

    if (n > 1000) {
        return -1;  // Leak! data not freed
    }

    // ... process data ...
    free(data);
    return 0;
}

// GOOD: Free before all returns
int process_data(int n) {
    int *data = (int*) malloc(n * sizeof(int));
    if (data == NULL) return -1;

    int result = 0;
    if (n > 1000) {
        result = -1;
        goto cleanup;
    }

    // ... process data ...

cleanup:
    free(data);
    return result;
}
```

### Dangling Pointers

A dangling pointer points to memory that has been freed or is no longer valid.

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr1 = (int*) malloc(sizeof(int));
    *ptr1 = 100;

    int *ptr2 = ptr1;  // Both point to same memory

    free(ptr1);
    ptr1 = NULL;  // ptr1 is safe

    // ptr2 is now a dangling pointer!
    // *ptr2 = 200;  // UNDEFINED BEHAVIOR!

    // Solution: Set all aliases to NULL
    ptr2 = NULL;

    return 0;
}
```

### Double Free Error

```c
// DANGEROUS: Double free
int *ptr = (int*) malloc(sizeof(int));
free(ptr);
free(ptr);  // UNDEFINED BEHAVIOR! Crash or corruption

// SAFE: Set to NULL after free
int *ptr = (int*) malloc(sizeof(int));
free(ptr);
ptr = NULL;
free(ptr);  // Safe: free(NULL) does nothing
```

---

## Best Practices

### 1. Check for Allocation Failure

```c
int *ptr = (int*) malloc(n * sizeof(int));
if (ptr == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return ERROR_CODE;
}
```

### 2. Initialize Allocated Memory

```c
// Option 1: Use calloc
int *arr = (int*) calloc(n, sizeof(int));

// Option 2: Use memset
int *arr = (int*) malloc(n * sizeof(int));
if (arr != NULL) {
    memset(arr, 0, n * sizeof(int));
}

// Option 3: Manual initialization
for (int i = 0; i < n; i++) {
    arr[i] = 0;
}
```

### 3. Always Free in Reverse Order of Allocation (for complex structures)

```c
struct Node {
    int data;
    struct Node *next;
};

// Allocate
struct Node *node1 = malloc(sizeof(struct Node));
struct Node *node2 = malloc(sizeof(struct Node));
node1->next = node2;

// Free in reverse order (or follow pointers)
free(node2);
free(node1);
```

### 4. Use sizeof with the Variable, Not Type

```c
// GOOD: Automatically correct if type changes
int *ptr = malloc(sizeof(*ptr));
int *arr = malloc(n * sizeof(*arr));

// LESS SAFE: Must update if type changes
int *ptr = malloc(sizeof(int));
```

### 5. Set Pointers to NULL After Free

```c
free(ptr);
ptr = NULL;  // Prevents dangling pointer bugs
```

### 6. Create Wrapper Functions

```c
#include <stdio.h>
#include <stdlib.h>

void* safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Fatal: Memory allocation of %zu bytes failed\n", size);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void safe_free(void **ptr) {
    if (ptr != NULL && *ptr != NULL) {
        free(*ptr);
        *ptr = NULL;
    }
}

int main() {
    int *arr = safe_malloc(10 * sizeof(int));
    // ... use arr ...
    safe_free((void**)&arr);  // Automatically sets to NULL
    return 0;
}
```

### 7. Complete Example: Dynamic String Array

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** create_string_array(int count, int max_length) {
    // Allocate array of char pointers
    char **arr = (char**) malloc(count * sizeof(char*));
    if (arr == NULL) return NULL;

    // Allocate each string
    for (int i = 0; i < count; i++) {
        arr[i] = (char*) malloc(max_length * sizeof(char));
        if (arr[i] == NULL) {
            // Allocation failed, free previous allocations
            for (int j = 0; j < i; j++) {
                free(arr[j]);
            }
            free(arr);
            return NULL;
        }
    }

    return arr;
}

void free_string_array(char **arr, int count) {
    if (arr == NULL) return;

    // Free each string first
    for (int i = 0; i < count; i++) {
        free(arr[i]);
    }

    // Then free the array itself
    free(arr);
}

int main() {
    int n = 5;
    char **names = create_string_array(n, 50);

    if (names == NULL) {
        printf("Failed to create string array\n");
        return 1;
    }

    // Use the array
    strcpy(names[0], "Alice");
    strcpy(names[1], "Bob");
    strcpy(names[2], "Charlie");
    strcpy(names[3], "David");
    strcpy(names[4], "Eve");

    // Print
    for (int i = 0; i < n; i++) {
        printf("%d: %s\n", i + 1, names[i]);
    }

    // Clean up
    free_string_array(names, n);

    return 0;
}
```

**Memory Diagram:**

```
names → [ptr0][ptr1][ptr2][ptr3][ptr4]
         ↓     ↓     ↓     ↓     ↓
       "Alice" "Bob" "Charlie" "David" "Eve"
       [A][l][i][c][e][\0]...
```

---

## Practice Exercises

### Exercise 1: Dynamic Matrix (Medium)
Write a program to create a dynamic 2D matrix (rows × cols) of integers. Implement functions to:
- Allocate the matrix
- Initialize with values (row*cols + col)
- Print the matrix
- Free the matrix properly

**Bonus:** Make it work for non-rectangular matrices (different column count per row).

---

### Exercise 2: Memory Leak Detector (Hard)
Implement a simple memory tracking system:
- Create wrapper functions `tracked_malloc()` and `tracked_free()`
- Keep count of allocations and deallocations
- At program end, report any memory leaks (allocated but not freed)
- Store size of each allocation

**Hint:** Use a simple array or linked list to track allocations.

---

### Exercise 3: Dynamic String Concatenation (Medium)
Write a function that takes multiple strings as input and concatenates them into a single dynamically allocated string. The function should:
```c
char* concat_strings(int count, ...);  // Variable arguments
```
Example: `concat_strings(3, "Hello", " ", "World")` returns `"Hello World"`

**Bonus:** Handle NULL inputs gracefully.

---

### Exercise 4: Resizable Array (Hard)
Implement a dynamic array that automatically grows when full:
```c
typedef struct {
    int *data;
    int size;      // Current number of elements
    int capacity;  // Total allocated space
} DynamicArray;

DynamicArray* create_array(int initial_capacity);
void append(DynamicArray *arr, int value);
void resize(DynamicArray *arr, int new_capacity);
void free_array(DynamicArray *arr);
```
When array is full, double its capacity using `realloc()`.

---

### Exercise 5: Fix the Memory Errors (Hard)
Identify and fix all memory-related errors in this code:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* create_message(int code) {
    char buffer[100];
    sprintf(buffer, "Error code: %d", code);
    return buffer;  // Error 1: ?
}

void process_data(int n) {
    int *data = malloc(n * sizeof(int));

    if (n > 100) {
        printf("Too large!\n");
        return;  // Error 2: ?
    }

    for (int i = 0; i <= n; i++) {  // Error 3: ?
        data[i] = i * i;
    }

    int *backup = data;
    free(data);

    printf("Last value: %d\n", backup[n-1]);  // Error 4: ?

    free(data);  // Error 5: ?
}

int main() {
    char *msg = create_message(404);
    printf("%s\n", msg);
    free(msg);  // Error 6: ?

    process_data(50);

    int *ptr = malloc(sizeof(int));
    *ptr = 42;
    ptr = malloc(sizeof(int));  // Error 7: ?
    *ptr = 100;
    free(ptr);

    return 0;
}
```

---

### Exercise 6: Memory Pool Allocator (Advanced)
Implement a simple memory pool for fixed-size allocations:
```c
typedef struct {
    void *pool;
    int block_size;
    int num_blocks;
    int *free_list;  // Track which blocks are free
} MemoryPool;

MemoryPool* create_pool(int block_size, int num_blocks);
void* pool_alloc(MemoryPool *pool);
void pool_free(MemoryPool *pool, void *ptr);
void destroy_pool(MemoryPool *pool);
```
This is more efficient than malloc/free for many same-size allocations.

---

### Exercise 7: Deep Copy vs Shallow Copy (Medium)
Create a structure:
```c
typedef struct {
    char *name;
    int age;
    int *scores;
    int num_scores;
} Student;
```

Implement:
- `Student* shallow_copy(Student *original)` - Copies pointers
- `Student* deep_copy(Student *original)` - Allocates new memory for all dynamic parts
- `void free_student(Student *s)` - Properly frees all memory

Demonstrate the difference with a test program.

---

### Exercise 8: Realloc Challenge (Hard)
Write a function that reads an unknown number of integers from a file and stores them in a dynamically allocated array. The array should:
- Start with capacity of 10
- Double in size when full (using realloc)
- Print statistics: total numbers read, final capacity, memory efficiency (used/allocated)

```c
int* read_numbers(const char *filename, int *count);
```

**Bonus:** After reading, shrink the array to exact size needed.

---

## Summary

**Key Takeaways:**
1. **malloc** allocates uninitialized memory
2. **calloc** allocates zero-initialized memory
3. **realloc** resizes allocated memory (may move it)
4. **free** releases memory back to the heap
5. **Always check** for allocation failures
6. **Always free** dynamically allocated memory
7. **Set pointers to NULL** after freeing
8. **Memory leaks** occur when allocated memory is never freed
9. **Dangling pointers** point to freed memory
10. **Use tools** like Valgrind to detect memory errors

**Memory Management Mantra:**
> "For every malloc/calloc/realloc, there must be exactly one free."

Happy coding!
