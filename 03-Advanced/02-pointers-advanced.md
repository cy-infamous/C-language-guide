# Advanced Pointers in C

## Table of Contents
1. [Pointer Recap](#pointer-recap)
2. [Pointer to Pointer](#pointer-to-pointer)
3. [Function Pointers](#function-pointers)
4. [Void Pointers](#void-pointers)
5. [Pointers to Structures](#pointers-to-structures)
6. [Advanced Pointer Techniques](#advanced-techniques)
7. [Practice Exercises](#practice-exercises)

---

## Pointer Recap

A pointer is a variable that stores the memory address of another variable.

```c
int x = 10;
int *ptr = &x;  // ptr holds the address of x

printf("Value of x: %d\n", x);      // 10
printf("Address of x: %p\n", &x);   // e.g., 0x7ffd5c
printf("Value of ptr: %p\n", ptr);  // Same as &x
printf("Value at ptr: %d\n", *ptr); // 10 (dereference)
```

**Memory Diagram:**
```
Memory Address    Variable    Value
0x7ffd5c         x           10
0x7ffd60         ptr         0x7ffd5c ──→ points to x
```

---

## Pointer to Pointer (Double Pointer)

A pointer to pointer stores the address of another pointer variable. Declared with double asterisks `**`.

### Syntax

```c
int x = 10;
int *ptr = &x;      // Pointer to int
int **pptr = &ptr;  // Pointer to pointer to int
```

### Memory Diagram

```
Memory          Variable    Value
0x1000         x           10
0x2000         ptr         0x1000 ──→ points to x
0x3000         pptr        0x2000 ──→ points to ptr ──→ points to x
```

### Accessing Values

```c
#include <stdio.h>

int main() {
    int x = 100;
    int *ptr = &x;
    int **pptr = &ptr;

    printf("Value of x: %d\n", x);           // 100
    printf("Value using *ptr: %d\n", *ptr);  // 100
    printf("Value using **pptr: %d\n", **pptr); // 100

    printf("\nAddress of x: %p\n", (void*)&x);
    printf("Value of ptr: %p\n", (void*)ptr);
    printf("Value of *pptr: %p\n", (void*)*pptr);

    printf("\nAddress of ptr: %p\n", (void*)&ptr);
    printf("Value of pptr: %p\n", (void*)pptr);

    // Modify through double pointer
    **pptr = 200;
    printf("\nAfter **pptr = 200:\n");
    printf("x = %d\n", x);  // 200

    return 0;
}
```

### Use Case 1: Modifying Pointer in Function

When you want a function to modify the pointer itself (not just the value it points to):

```c
#include <stdio.h>
#include <stdlib.h>

// Wrong: Cannot modify the pointer passed
void allocate_wrong(int *ptr, int value) {
    ptr = (int*) malloc(sizeof(int));  // Only local copy is modified
    *ptr = value;
}

// Correct: Can modify the pointer through double pointer
void allocate_correct(int **pptr, int value) {
    *pptr = (int*) malloc(sizeof(int));
    if (*pptr != NULL) {
        **pptr = value;
    }
}

int main() {
    int *p = NULL;

    allocate_wrong(p, 42);
    if (p == NULL) {
        printf("Wrong method: p is still NULL\n");
    }

    allocate_correct(&p, 42);
    if (p != NULL) {
        printf("Correct method: *p = %d\n", *p);
        free(p);
    }

    return 0;
}
```

**Why it works:**
```
allocate_correct(&p, 42):
    pptr points to p
    *pptr = malloc(...) modifies p itself
    **pptr = value modifies the allocated integer
```

### Use Case 2: Dynamic 2D Arrays

```c
#include <stdio.h>
#include <stdlib.h>

int** create_2d_array(int rows, int cols) {
    // Allocate array of pointers (rows)
    int **arr = (int**) malloc(rows * sizeof(int*));
    if (arr == NULL) return NULL;

    // Allocate each row
    for (int i = 0; i < rows; i++) {
        arr[i] = (int*) malloc(cols * sizeof(int));
        if (arr[i] == NULL) {
            // Clean up on failure
            for (int j = 0; j < i; j++) {
                free(arr[j]);
            }
            free(arr);
            return NULL;
        }
    }

    return arr;
}

void free_2d_array(int **arr, int rows) {
    if (arr == NULL) return;

    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);
}

int main() {
    int rows = 3, cols = 4;

    int **matrix = create_2d_array(rows, cols);
    if (matrix == NULL) {
        printf("Allocation failed\n");
        return 1;
    }

    // Initialize matrix
    int value = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = value++;
        }
    }

    // Print matrix
    printf("Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }

    free_2d_array(matrix, rows);

    return 0;
}
```

**Memory Layout:**
```
matrix → [ptr0][ptr1][ptr2]         (array of row pointers)
          ↓     ↓     ↓
       [1][2][3][4]  [5][6][7][8]  [9][10][11][12]
       Row 0          Row 1          Row 2
```

### Use Case 3: Array of Strings

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Array of string pointers
    char **names = (char**) malloc(3 * sizeof(char*));

    // Allocate and copy strings
    names[0] = (char*) malloc(20 * sizeof(char));
    names[1] = (char*) malloc(20 * sizeof(char));
    names[2] = (char*) malloc(20 * sizeof(char));

    strcpy(names[0], "Alice");
    strcpy(names[1], "Bob");
    strcpy(names[2], "Charlie");

    // Print names
    for (int i = 0; i < 3; i++) {
        printf("Name %d: %s\n", i + 1, names[i]);
    }

    // Free memory
    for (int i = 0; i < 3; i++) {
        free(names[i]);
    }
    free(names);

    return 0;
}
```

---

## Function Pointers

Function pointers store the address of a function. They enable runtime function selection, callbacks, and plugin architectures.

### Basic Syntax

```c
return_type (*pointer_name)(parameter_types);
```

### Example 1: Simple Function Pointer

```c
#include <stdio.h>

// Regular function
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int main() {
    // Declare function pointer
    int (*operation)(int, int);

    // Point to add function
    operation = add;
    printf("5 + 3 = %d\n", operation(5, 3));  // 8

    // Point to subtract function
    operation = subtract;
    printf("5 - 3 = %d\n", operation(5, 3));  // 2

    // Alternative syntax (explicit)
    operation = &add;
    printf("5 + 3 = %d\n", (*operation)(5, 3));  // 8

    return 0;
}
```

### Example 2: Calculator with Function Pointers

```c
#include <stdio.h>

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return b != 0 ? a / b : 0; }

int main() {
    // Array of function pointers
    int (*operations[4])(int, int) = {add, subtract, multiply, divide};
    char *op_names[] = {"Add", "Subtract", "Multiply", "Divide"};

    int a = 20, b = 5;

    printf("a = %d, b = %d\n\n", a, b);

    for (int i = 0; i < 4; i++) {
        printf("%s: %d\n", op_names[i], operations[i](a, b));
    }

    return 0;
}
```

**Output:**
```
a = 20, b = 5

Add: 25
Subtract: 15
Multiply: 100
Divide: 4
```

### Example 3: Callback Functions

Callback functions are passed as arguments to other functions.

```c
#include <stdio.h>

// Callback function type
typedef void (*callback_t)(int);

// Functions that can be used as callbacks
void print_square(int n) {
    printf("Square: %d\n", n * n);
}

void print_cube(int n) {
    printf("Cube: %d\n", n * n * n);
}

// Function that accepts callback
void process_array(int *arr, int size, callback_t callback) {
    for (int i = 0; i < size; i++) {
        callback(arr[i]);
    }
}

int main() {
    int numbers[] = {2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    printf("Processing with square callback:\n");
    process_array(numbers, size, print_square);

    printf("\nProcessing with cube callback:\n");
    process_array(numbers, size, print_cube);

    return 0;
}
```

### Example 4: Generic Sorting with Comparison Callback

```c
#include <stdio.h>
#include <stdlib.h>

// Comparison function type
typedef int (*compare_t)(const void*, const void*);

// Comparison functions
int compare_ascending(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int compare_descending(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

void print_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original: ");
    print_array(arr, size);

    // Sort ascending
    qsort(arr, size, sizeof(int), compare_ascending);
    printf("Ascending: ");
    print_array(arr, size);

    // Sort descending
    qsort(arr, size, sizeof(int), compare_descending);
    printf("Descending: ");
    print_array(arr, size);

    return 0;
}
```

### Example 5: State Machine Using Function Pointers

```c
#include <stdio.h>
#include <string.h>

typedef enum { IDLE, RUNNING, PAUSED, STOPPED } State;

// Forward declarations
void state_idle();
void state_running();
void state_paused();
void state_stopped();

// Function pointer array for states
void (*state_functions[])() = {
    state_idle,
    state_running,
    state_paused,
    state_stopped
};

State current_state = IDLE;

void change_state(State new_state) {
    printf("Transitioning from state %d to state %d\n", current_state, new_state);
    current_state = new_state;
}

void state_idle() {
    printf("State: IDLE - System is idle\n");
}

void state_running() {
    printf("State: RUNNING - System is running\n");
}

void state_paused() {
    printf("State: PAUSED - System is paused\n");
}

void state_stopped() {
    printf("State: STOPPED - System is stopped\n");
}

void execute_current_state() {
    state_functions[current_state]();
}

int main() {
    execute_current_state();

    change_state(RUNNING);
    execute_current_state();

    change_state(PAUSED);
    execute_current_state();

    change_state(STOPPED);
    execute_current_state();

    return 0;
}
```

---

## Void Pointers

A `void*` is a generic pointer that can point to any data type. It cannot be dereferenced directly and must be cast to the appropriate type first.

### Basic Usage

```c
#include <stdio.h>

int main() {
    int x = 10;
    float y = 3.14;
    char c = 'A';

    void *ptr;

    // Point to int
    ptr = &x;
    printf("Integer: %d\n", *(int*)ptr);

    // Point to float
    ptr = &y;
    printf("Float: %.2f\n", *(float*)ptr);

    // Point to char
    ptr = &c;
    printf("Char: %c\n", *(char*)ptr);

    return 0;
}
```

### Generic Swap Function

```c
#include <stdio.h>
#include <string.h>

void swap(void *a, void *b, size_t size) {
    // Temporary buffer
    unsigned char temp[size];

    // Swap using memcpy
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
}

int main() {
    // Swap integers
    int x = 10, y = 20;
    printf("Before: x = %d, y = %d\n", x, y);
    swap(&x, &y, sizeof(int));
    printf("After: x = %d, y = %d\n", x, y);

    // Swap floats
    float a = 1.5, b = 2.5;
    printf("\nBefore: a = %.1f, b = %.1f\n", a, b);
    swap(&a, &b, sizeof(float));
    printf("After: a = %.1f, b = %.1f\n", a, b);

    // Swap characters
    char c1 = 'A', c2 = 'Z';
    printf("\nBefore: c1 = %c, c2 = %c\n", c1, c2);
    swap(&c1, &c2, sizeof(char));
    printf("After: c1 = %c, c2 = %c\n", c1, c2);

    return 0;
}
```

### Generic Print Function

```c
#include <stdio.h>

typedef enum { TYPE_INT, TYPE_FLOAT, TYPE_CHAR, TYPE_STRING } DataType;

void print_value(void *ptr, DataType type) {
    switch (type) {
        case TYPE_INT:
            printf("Integer: %d\n", *(int*)ptr);
            break;
        case TYPE_FLOAT:
            printf("Float: %.2f\n", *(float*)ptr);
            break;
        case TYPE_CHAR:
            printf("Char: %c\n", *(char*)ptr);
            break;
        case TYPE_STRING:
            printf("String: %s\n", (char*)ptr);
            break;
        default:
            printf("Unknown type\n");
    }
}

int main() {
    int x = 42;
    float y = 3.14159;
    char c = 'X';
    char *str = "Hello, World!";

    print_value(&x, TYPE_INT);
    print_value(&y, TYPE_FLOAT);
    print_value(&c, TYPE_CHAR);
    print_value(str, TYPE_STRING);

    return 0;
}
```

### Important Notes on Void Pointers

1. **Cannot be dereferenced directly:**
   ```c
   void *ptr = &x;
   // printf("%d", *ptr);  // ERROR: cannot dereference void*
   printf("%d", *(int*)ptr);  // OK: cast first
   ```

2. **Pointer arithmetic not allowed:**
   ```c
   void *ptr = &arr[0];
   // ptr++;  // ERROR: void* has no size
   ptr = (char*)ptr + 1;  // OK: cast to specific type
   ```

3. **malloc returns void*:**
   ```c
   int *arr = malloc(10 * sizeof(int));  // Implicit cast from void*
   ```

---

## Pointers to Structures

Pointers to structures are crucial for efficient structure handling and data structure implementation.

### Basic Syntax

```c
struct Point {
    int x;
    int y;
};

struct Point p = {10, 20};
struct Point *ptr = &p;

// Two ways to access members:
printf("x = %d\n", (*ptr).x);   // Dereference first
printf("x = %d\n", ptr->x);     // Arrow operator (preferred)
```

### Complete Example

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
    float gpa;
} Student;

// Function that takes pointer to structure
void print_student(const Student *s) {
    if (s == NULL) return;

    printf("Name: %s\n", s->name);
    printf("Age: %d\n", s->age);
    printf("GPA: %.2f\n", s->gpa);
}

// Function that modifies structure through pointer
void update_gpa(Student *s, float new_gpa) {
    if (s != NULL) {
        s->gpa = new_gpa;
    }
}

// Function that allocates and returns structure
Student* create_student(const char *name, int age, float gpa) {
    Student *s = (Student*) malloc(sizeof(Student));
    if (s == NULL) return NULL;

    strncpy(s->name, name, sizeof(s->name) - 1);
    s->name[sizeof(s->name) - 1] = '\0';  // Ensure null termination
    s->age = age;
    s->gpa = gpa;

    return s;
}

int main() {
    // Stack-allocated structure
    Student s1 = {"Alice Johnson", 20, 3.8};

    printf("Original student:\n");
    print_student(&s1);

    update_gpa(&s1, 3.9);
    printf("\nAfter GPA update:\n");
    print_student(&s1);

    // Dynamically allocated structure
    Student *s2 = create_student("Bob Smith", 21, 3.5);
    if (s2 != NULL) {
        printf("\nDynamic student:\n");
        print_student(s2);
        free(s2);
    }

    return 0;
}
```

### Self-Referential Structures (Linked List Node)

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;  // Pointer to same structure type
} Node;

Node* create_node(int data) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    if (new_node == NULL) return NULL;

    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    // Create linked list: 10 -> 20 -> 30
    Node *head = create_node(10);
    head->next = create_node(20);
    head->next->next = create_node(30);

    printf("Linked List: ");
    print_list(head);

    free_list(head);

    return 0;
}
```

**Memory Diagram:**
```
head → [10][next] → [20][next] → [30][NULL]
       0x1000       0x2000        0x3000
```

---

## Advanced Pointer Techniques

### 1. Pointer to Array vs Array of Pointers

```c
#include <stdio.h>

int main() {
    int arr[3] = {10, 20, 30};

    // Pointer to array (entire array)
    int (*ptr_to_array)[3] = &arr;
    printf("First element via ptr_to_array: %d\n", (*ptr_to_array)[0]);

    // Array of pointers
    int *array_of_ptrs[3];
    for (int i = 0; i < 3; i++) {
        array_of_ptrs[i] = &arr[i];
    }
    printf("First element via array_of_ptrs: %d\n", *array_of_ptrs[0]);

    return 0;
}
```

### 2. Const Pointers

```c
#include <stdio.h>

int main() {
    int x = 10, y = 20;

    // 1. Pointer to constant (cannot change value through pointer)
    const int *ptr1 = &x;
    // *ptr1 = 15;  // ERROR
    ptr1 = &y;      // OK

    // 2. Constant pointer (cannot change pointer address)
    int *const ptr2 = &x;
    *ptr2 = 15;     // OK
    // ptr2 = &y;   // ERROR

    // 3. Constant pointer to constant (cannot change either)
    const int *const ptr3 = &x;
    // *ptr3 = 15;  // ERROR
    // ptr3 = &y;   // ERROR

    return 0;
}
```

**Memory Rule:**
- `const` before `*` → data is constant
- `const` after `*` → pointer is constant

### 3. Pointer Arithmetic

```c
#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;  // Points to first element

    printf("Array elements using pointer arithmetic:\n");
    for (int i = 0; i < 5; i++) {
        printf("ptr + %d = %p, value = %d\n", i, (void*)(ptr + i), *(ptr + i));
    }

    // Pointer subtraction
    int *ptr1 = &arr[1];
    int *ptr2 = &arr[4];
    printf("\nDifference: %ld elements\n", ptr2 - ptr1);  // 3

    return 0;
}
```

### 4. Complex Pointer Declarations

```c
int *ptr;              // Pointer to int
int **ptr;             // Pointer to pointer to int
int *ptr[10];          // Array of 10 pointers to int
int (*ptr)[10];        // Pointer to array of 10 ints
int (*ptr)(int);       // Pointer to function taking int, returning int
int *(*ptr)(int);      // Pointer to function taking int, returning pointer to int
```

**Reading Complex Declarations (Right-Left Rule):**
```c
int *(*ptr[10])(float);
```
1. Start with identifier: `ptr`
2. Move right: `[10]` → `ptr is an array of 10`
3. Move left: `*` → `pointers to`
4. Move right: `(float)` → `functions taking float`
5. Move left: `*` → `returning pointer to`
6. Move left: `int` → `int`

Result: `ptr is an array of 10 pointers to functions taking float and returning pointer to int`

---

## Practice Exercises

### Exercise 1: Triple Pointer (Hard)
Create a program using triple pointer (`int ***`) to:
- Dynamically allocate a 3D array (x × y × z dimensions)
- Initialize with values (i * 100 + j * 10 + k)
- Print the entire 3D array
- Properly free all memory

**Hint:** Three levels of allocation needed.

---

### Exercise 2: Function Pointer Menu System (Medium)
Create a menu-driven calculator with function pointers:
```c
typedef double (*math_func_t)(double, double);

typedef struct {
    char name[20];
    math_func_t func;
} Operation;
```
Support operations: add, subtract, multiply, divide, power, modulo. Use an array of Operation structures.

---

### Exercise 3: Generic Linked List with Void Pointers (Hard)
Implement a generic linked list that can store any data type:
```c
typedef struct Node {
    void *data;
    size_t data_size;
    struct Node *next;
} Node;

Node* create_node(void *data, size_t size);
void append(Node **head, void *data, size_t size);
void print_list(Node *head, void (*print_func)(void*));
void free_list(Node *head);
```
Test with different data types (int, float, struct).

---

### Exercise 4: Structure with Function Pointers (OOP-like) (Advanced)
Create a "class-like" structure for a shape:
```c
typedef struct Shape {
    void *data;  // Specific shape data
    double (*area)(void*);
    double (*perimeter)(void*);
    void (*print)(void*);
} Shape;
```
Implement for Circle and Rectangle. Demonstrate polymorphism.

---

### Exercise 5: Callback-Based Event System (Hard)
Implement a simple event system:
```c
typedef void (*event_callback_t)(void *data);

typedef struct {
    char event_name[50];
    event_callback_t callbacks[10];
    int callback_count;
} Event;

void register_callback(Event *e, event_callback_t callback);
void trigger_event(Event *e, void *data);
```
Create events like "on_click", "on_keypress" with multiple callbacks.

---

### Exercise 6: Pointer Puzzle (Medium)
Explain what each line does and predict the output:
```c
int arr[] = {1, 2, 3, 4, 5};
int *p1 = arr + 1;
int *p2 = arr + 3;

printf("%d\n", *p1);        // ?
printf("%d\n", *(p1 + 2));  // ?
printf("%d\n", p2 - p1);    // ?
printf("%d\n", *p2 - *p1);  // ?
printf("%p\n", p1 + 1);     // ?
printf("%p\n", &arr[2]);    // ?
```

---

### Exercise 7: Array of Function Pointers for Menu (Medium)
Create a complete menu system using function pointers:
```c
void add_record();
void view_records();
void edit_record();
void delete_record();
void exit_program();

void (*menu_functions[])() = {add_record, view_records, edit_record, delete_record, exit_program};
```
Display menu, get user choice, call appropriate function.

---

### Exercise 8: Deep vs Shallow Copy with Nested Structures (Hard)
```c
typedef struct {
    char *name;
    int *grades;
    int num_grades;
} Student;

typedef struct {
    char *course_name;
    Student *students;
    int num_students;
} Course;
```
Implement deep_copy and shallow_copy for Course structure. Demonstrate the difference.

---

## Summary

**Key Concepts:**

1. **Pointer to Pointer (`**`)**: Stores address of another pointer
   - Used for: modifying pointers in functions, 2D arrays, string arrays

2. **Function Pointers**: Store addresses of functions
   - Used for: callbacks, runtime function selection, state machines

3. **Void Pointers (`void*`)**: Generic pointers to any type
   - Used for: generic functions, malloc return type
   - Cannot be dereferenced directly

4. **Pointers to Structures**: Access members using `->`
   - Used for: efficient passing, dynamic structures, linked lists

5. **Advanced Techniques**: Const pointers, pointer arithmetic, complex declarations

**Best Practices:**
- Always check for NULL before dereferencing
- Use typedef for complex pointer types
- Prefer arrow operator (`->`) for structure pointers
- Cast void pointers before dereferencing
- Free dynamically allocated memory
- Set pointers to NULL after freeing

**Common Pitfalls:**
- Dereferencing NULL pointers
- Pointer arithmetic on void*
- Forgetting to cast void pointers
- Double freeing memory
- Dangling pointers after free

Master these concepts and you'll handle any pointer challenge in C!
