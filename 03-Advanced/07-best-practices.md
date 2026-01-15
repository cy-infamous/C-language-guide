# C Programming Best Practices

## Table of Contents
1. [Code Organization](#code-organization)
2. [Naming Conventions](#naming-conventions)
3. [Memory Management](#memory-management)
4. [Error Handling](#error-handling)
5. [Code Quality and Maintainability](#code-quality)
6. [Debugging Techniques](#debugging-techniques)
7. [Performance Optimization](#performance-optimization)
8. [Practice Exercises](#practice-exercises)

---

## Code Organization

### 1. File Structure

**Single Source File Projects:**
```c
/* file: program.c */
// Includes
#include <stdio.h>
#include <stdlib.h>

// Macros and constants
#define MAX_SIZE 100

// Type definitions
typedef struct {
    int id;
    char name[50];
} Record;

// Function prototypes
void initialize(void);
void process(Record *r);
void cleanup(void);

// Main function
int main(void) {
    // Implementation
    return 0;
}

// Function implementations
void initialize(void) {
    // Implementation
}
```

**Multi-File Projects:**
```
project/
├── src/
│   ├── main.c          # Entry point
│   ├── module1.c       # Module implementations
│   ├── module2.c
│   └── utils.c
├── include/
│   ├── module1.h       # Public interfaces
│   ├── module2.h
│   └── utils.h
├── tests/
│   ├── test_module1.c
│   └── test_module2.c
├── Makefile
└── README.md
```

### 2. Header File Best Practices

**Good Header File (module.h):**
```c
#ifndef MODULE_H
#define MODULE_H

/* Include only necessary headers */
#include <stddef.h>  // For size_t

/* Forward declarations when possible */
struct InternalData;

/* Public constants */
#define MODULE_MAX_SIZE 256
#define MODULE_VERSION 1

/* Public type definitions */
typedef struct {
    int id;
    char name[50];
} PublicData;

/* Function declarations with documentation */
/**
 * Initializes the module.
 * @return 0 on success, -1 on error
 */
int module_init(void);

/**
 * Processes data.
 * @param data Pointer to data structure
 * @return Number of items processed
 */
int module_process(PublicData *data);

/**
 * Cleans up module resources.
 */
void module_cleanup(void);

#endif /* MODULE_H */
```

**Implementation File (module.c):**
```c
#include "module.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Internal structures (not in header) */
struct InternalData {
    int internal_value;
    char *buffer;
};

/* Static (private) functions */
static int internal_helper(int value) {
    return value * 2;
}

/* Static (private) variables */
static int initialized = 0;

/* Public function implementations */
int module_init(void) {
    if (initialized) {
        return 0;  // Already initialized
    }

    // Initialization code
    initialized = 1;
    return 0;
}

int module_process(PublicData *data) {
    if (!initialized || data == NULL) {
        return -1;
    }

    // Processing code
    return 0;
}

void module_cleanup(void) {
    // Cleanup code
    initialized = 0;
}
```

### 3. Separation of Concerns

**Bad: Everything in one function**
```c
void do_everything() {
    // Parse input
    // Validate data
    // Process data
    // Format output
    // Write to file
    // All in one giant function - hard to test and maintain!
}
```

**Good: Modular approach**
```c
typedef struct {
    int value;
    char name[50];
} Data;

Data* parse_input(const char *input) {
    // Only parsing logic
    Data *data = malloc(sizeof(Data));
    // ... parse ...
    return data;
}

int validate_data(const Data *data) {
    // Only validation logic
    if (data == NULL) return 0;
    if (data->value < 0 || data->value > 100) return 0;
    return 1;
}

Data* process_data(const Data *input) {
    // Only processing logic
    Data *result = malloc(sizeof(Data));
    // ... process ...
    return result;
}

char* format_output(const Data *data) {
    // Only formatting logic
    char *output = malloc(256);
    sprintf(output, "Value: %d, Name: %s", data->value, data->name);
    return output;
}

int write_to_file(const char *filename, const char *content) {
    // Only file I/O logic
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) return -1;
    fprintf(fp, "%s", content);
    fclose(fp);
    return 0;
}

// Main orchestration
int main() {
    Data *input = parse_input("10:example");
    if (!validate_data(input)) {
        fprintf(stderr, "Invalid data\n");
        free(input);
        return 1;
    }

    Data *result = process_data(input);
    char *output = format_output(result);
    write_to_file("output.txt", output);

    // Cleanup
    free(input);
    free(result);
    free(output);

    return 0;
}
```

---

## Naming Conventions

### 1. Consistent Naming Scheme

**Snake_case (Common in C):**
```c
int user_count;
void calculate_total_price(void);
struct student_record;
```

**CamelCase (Less common, but acceptable if consistent):**
```c
int userCount;
void calculateTotalPrice(void);
struct StudentRecord;
```

**Choose one style and stick with it throughout the project.**

### 2. Descriptive Names

**Bad:**
```c
int n;                  // What does n represent?
void proc(int x);       // What does proc do?
char *p;                // Pointer to what?
int tmp, tmp2, tmp3;    // Multiple temps, unclear purpose
```

**Good:**
```c
int student_count;
void process_payment(int amount);
char *username;
int calculated_total, max_retry_count, buffer_size;
```

### 3. Naming Conventions by Type

**Variables:**
```c
// Use descriptive lowercase names
int student_age;
float temperature_celsius;
char *error_message;

// Boolean variables: use is_, has_, can_ prefix
int is_valid;
int has_permission;
int can_write;

// Constants: UPPERCASE with underscores
#define MAX_BUFFER_SIZE 1024
#define PI 3.14159265359
const int RETRY_COUNT = 3;
```

**Functions:**
```c
// Use verb phrases
void calculate_average(void);
int find_maximum(int *array, int size);
void print_report(void);

// Getter/setter prefixes
int get_age(void);
void set_age(int age);

// Boolean functions: use is_, has_, can_ prefix
int is_prime(int n);
int has_children(Node *node);
int can_access(User *user);
```

**Types:**
```c
// Structs: Use descriptive nouns
struct student_record { /* ... */ };
typedef struct { /* ... */ } Point;

// Enums: Uppercase, with common prefix
typedef enum {
    STATUS_SUCCESS,
    STATUS_ERROR,
    STATUS_PENDING
} Status;

// Type aliases: End with _t
typedef unsigned int uint_t;
typedef struct node* node_ptr_t;
```

**Macros:**
```c
// UPPERCASE for constants
#define MAX_SIZE 100

// UPPERCASE for function-like macros
#define SQUARE(x) ((x) * (x))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
```

### 4. Avoid Ambiguous Names

**Avoid:**
```c
int data;        // Too generic
void process();  // Process what?
int flag;        // What flag?
```

**Prefer:**
```c
int student_grades[MAX_STUDENTS];
void process_user_input();
int is_file_open;
```

### 5. Prefix for Namespacing

Prevent naming conflicts in large projects:

```c
// Module: database
int db_connect(const char *host);
void db_disconnect(void);
int db_query(const char *sql);

// Module: network
int net_connect(const char *host);
void net_disconnect(void);
int net_send(const char *data);

// Module: logger
void log_init(void);
void log_message(const char *msg);
void log_error(const char *msg);
```

---

## Memory Management

### 1. Always Check Allocation

**Bad:**
```c
int *arr = malloc(n * sizeof(int));
arr[0] = 10;  // Crash if malloc failed!
```

**Good:**
```c
int *arr = malloc(n * sizeof(int));
if (arr == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return NULL;
}
arr[0] = 10;
```

### 2. Always Free What You Allocate

**Bad:**
```c
void process_data() {
    int *data = malloc(100 * sizeof(int));
    // ... use data ...
    // Oops! No free() - memory leak
}
```

**Good:**
```c
void process_data() {
    int *data = malloc(100 * sizeof(int));
    if (data == NULL) return;

    // ... use data ...

    free(data);
    data = NULL;  // Good practice
}
```

### 3. Ownership Pattern

**Clear ownership of allocated memory:**
```c
// Function allocates and caller owns (must free)
char* create_string(const char *text) {
    char *str = malloc(strlen(text) + 1);
    if (str != NULL) {
        strcpy(str, text);
    }
    return str;  // Caller must free
}

// Function takes ownership (will free)
void process_and_free(char *data) {
    // ... process data ...
    free(data);  // Function frees it
}

// Usage
char *str = create_string("Hello");
process_and_free(str);  // Don't use str after this
str = NULL;
```

### 4. Resource Acquisition Is Initialization (RAII Pattern)

```c
typedef struct {
    FILE *file;
    char *buffer;
    int *data;
} Resource;

Resource* resource_create(const char *filename) {
    Resource *r = malloc(sizeof(Resource));
    if (r == NULL) return NULL;

    r->file = NULL;
    r->buffer = NULL;
    r->data = NULL;

    // Acquire resources
    r->file = fopen(filename, "r");
    if (r->file == NULL) {
        resource_destroy(r);
        return NULL;
    }

    r->buffer = malloc(1024);
    if (r->buffer == NULL) {
        resource_destroy(r);
        return NULL;
    }

    r->data = malloc(100 * sizeof(int));
    if (r->data == NULL) {
        resource_destroy(r);
        return NULL;
    }

    return r;
}

void resource_destroy(Resource *r) {
    if (r == NULL) return;

    // Release resources (safe even if NULL)
    if (r->file != NULL) fclose(r->file);
    free(r->buffer);
    free(r->data);
    free(r);
}

// Usage
Resource *r = resource_create("data.txt");
if (r != NULL) {
    // Use resource
    resource_destroy(r);
}
```

### 5. Avoid Memory Leaks in Error Paths

**Bad:**
```c
int process() {
    char *buffer1 = malloc(100);
    char *buffer2 = malloc(200);
    char *buffer3 = malloc(300);

    if (error_condition) {
        return -1;  // Leak: All three buffers leaked!
    }

    // ... process ...

    free(buffer1);
    free(buffer2);
    free(buffer3);
    return 0;
}
```

**Good:**
```c
int process() {
    char *buffer1 = NULL;
    char *buffer2 = NULL;
    char *buffer3 = NULL;
    int result = -1;

    buffer1 = malloc(100);
    if (buffer1 == NULL) goto cleanup;

    buffer2 = malloc(200);
    if (buffer2 == NULL) goto cleanup;

    buffer3 = malloc(300);
    if (buffer3 == NULL) goto cleanup;

    // ... process ...

    result = 0;  // Success

cleanup:
    free(buffer1);
    free(buffer2);
    free(buffer3);
    return result;
}
```

---

## Error Handling

### 1. Return Error Codes

**Consistent error reporting:**
```c
// Use 0 for success, negative for errors
#define SUCCESS 0
#define ERR_NULL_POINTER -1
#define ERR_OUT_OF_MEMORY -2
#define ERR_INVALID_INPUT -3
#define ERR_FILE_NOT_FOUND -4

int read_file(const char *filename, char **content) {
    if (filename == NULL || content == NULL) {
        return ERR_NULL_POINTER;
    }

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return ERR_FILE_NOT_FOUND;
    }

    // Determine file size
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    *content = malloc(size + 1);
    if (*content == NULL) {
        fclose(fp);
        return ERR_OUT_OF_MEMORY;
    }

    fread(*content, 1, size, fp);
    (*content)[size] = '\0';

    fclose(fp);
    return SUCCESS;
}

// Usage with error handling
int main() {
    char *content;
    int result = read_file("data.txt", &content);

    if (result != SUCCESS) {
        switch (result) {
            case ERR_NULL_POINTER:
                fprintf(stderr, "Error: Null pointer\n");
                break;
            case ERR_FILE_NOT_FOUND:
                fprintf(stderr, "Error: File not found\n");
                break;
            case ERR_OUT_OF_MEMORY:
                fprintf(stderr, "Error: Out of memory\n");
                break;
            default:
                fprintf(stderr, "Error: Unknown error\n");
        }
        return 1;
    }

    printf("Content: %s\n", content);
    free(content);
    return 0;
}
```

### 2. Use errno for System Errors

```c
#include <errno.h>
#include <string.h>

int open_file(const char *filename, FILE **fp) {
    *fp = fopen(filename, "r");
    if (*fp == NULL) {
        // errno is set by fopen on failure
        fprintf(stderr, "Error opening '%s': %s\n",
                filename, strerror(errno));
        return -1;
    }
    return 0;
}
```

### 3. Fail Fast

**Validate inputs early:**
```c
void process_array(int *arr, int size) {
    // Validate inputs immediately
    if (arr == NULL) {
        fprintf(stderr, "Error: Null array pointer\n");
        return;
    }

    if (size <= 0) {
        fprintf(stderr, "Error: Invalid array size: %d\n", size);
        return;
    }

    // Now safe to process
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;
    }
}
```

### 4. Defensive Programming

```c
typedef struct {
    int *data;
    int size;
    int capacity;
} DynamicArray;

int array_append(DynamicArray *arr, int value) {
    // Check all preconditions
    if (arr == NULL) {
        fprintf(stderr, "Error: Null array pointer\n");
        return -1;
    }

    if (arr->data == NULL) {
        fprintf(stderr, "Error: Uninitialized array\n");
        return -1;
    }

    if (arr->size < 0 || arr->capacity < 0) {
        fprintf(stderr, "Error: Invalid array state\n");
        return -1;
    }

    if (arr->size >= arr->capacity) {
        fprintf(stderr, "Error: Array is full\n");
        return -1;
    }

    // Preconditions satisfied, perform operation
    arr->data[arr->size++] = value;
    return 0;
}
```

### 5. Assert for Debugging

```c
#include <assert.h>

void process_data(int *data, int size) {
    // Assertions only in debug builds
    assert(data != NULL);
    assert(size > 0);
    assert(size <= MAX_SIZE);

    // Process data
    for (int i = 0; i < size; i++) {
        assert(data[i] >= 0);  // Verify assumption
        data[i] *= 2;
    }
}

// Compile without assertions for release:
// gcc -DNDEBUG program.c
```

---

## Code Quality and Maintainability

### 1. Comments

**Good comments explain WHY, not WHAT:**
```c
// BAD: Obvious comments
int count = 0;  // Initialize count to 0
count++;        // Increment count

// GOOD: Explain reasoning
// Use binary search since array is sorted (verified in load_data)
int index = binary_search(arr, size, target);

// GOOD: Explain complex algorithm
// Knuth-Morris-Pratt algorithm for efficient string matching
// Preprocesses pattern to avoid redundant comparisons
// Time complexity: O(n + m) where n = text length, m = pattern length
int kmp_search(const char *text, const char *pattern);

// GOOD: Warning about gotchas
// WARNING: This function modifies the input string in-place
// Make a copy if you need to preserve the original
void tokenize(char *str, char delimiter);
```

**Document complex functions:**
```c
/**
 * Performs a binary search on a sorted array.
 *
 * @param arr Sorted array of integers (ascending order)
 * @param size Number of elements in the array
 * @param target Value to search for
 * @return Index of target if found, -1 otherwise
 *
 * @note Array must be sorted in ascending order
 * @note Time complexity: O(log n)
 */
int binary_search(const int *arr, int size, int target);
```

### 2. Magic Numbers

**Bad:**
```c
if (status == 1) {  // What does 1 mean?
    // ...
}

int buffer[256];  // Why 256?
```

**Good:**
```c
#define STATUS_SUCCESS 1
#define STATUS_ERROR 0
#define MAX_BUFFER_SIZE 256

if (status == STATUS_SUCCESS) {
    // Clear intent
}

int buffer[MAX_BUFFER_SIZE];
```

### 3. Function Size

**Keep functions small and focused:**
```c
// BAD: One giant function doing everything
void process_everything() {
    // 500 lines of code...
}

// GOOD: Decomposed into smaller functions
void load_data(void);
void validate_data(void);
void transform_data(void);
void save_results(void);

void process_pipeline() {
    load_data();
    if (!validate_data()) return;
    transform_data();
    save_results();
}
```

**Rule of thumb: If a function doesn't fit on one screen, it's probably too long.**

### 4. DRY Principle (Don't Repeat Yourself)

**Bad:**
```c
void save_user(User *u) {
    FILE *fp = fopen("users.txt", "a");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    fprintf(fp, "%d,%s,%d\n", u->id, u->name, u->age);
    fclose(fp);
}

void save_product(Product *p) {
    FILE *fp = fopen("products.txt", "a");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    fprintf(fp, "%d,%s,%.2f\n", p->id, p->name, p->price);
    fclose(fp);
}
```

**Good:**
```c
typedef int (*formatter_t)(FILE*, void*);

int write_to_file(const char *filename, void *data, formatter_t format) {
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        perror("Error opening file");
        return -1;
    }

    int result = format(fp, data);
    fclose(fp);
    return result;
}

int format_user(FILE *fp, void *data) {
    User *u = (User*)data;
    return fprintf(fp, "%d,%s,%d\n", u->id, u->name, u->age);
}

int format_product(FILE *fp, void *data) {
    Product *p = (Product*)data;
    return fprintf(fp, "%d,%s,%.2f\n", p->id, p->name, p->price);
}

// Usage
write_to_file("users.txt", &user, format_user);
write_to_file("products.txt", &product, format_product);
```

### 5. Const Correctness

```c
// Use const for read-only pointers
void print_string(const char *str) {
    // Cannot modify str content
    printf("%s\n", str);
}

// Use const for parameters that won't change
int calculate_sum(const int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];  // Can read
        // arr[i] = 0;  // Error: Cannot modify
    }
    return sum;
}

// Use const for returned pointers to prevent modification
const char* get_error_message(int code) {
    static const char *messages[] = {
        "Success",
        "Error",
        "Warning"
    };
    return messages[code];
}
```

---

## Debugging Techniques

### 1. Printf Debugging

```c
#ifdef DEBUG
    #define DEBUG_PRINT(fmt, ...) \
        fprintf(stderr, "[DEBUG] %s:%d:%s(): " fmt "\n", \
                __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...) do {} while(0)
#endif

int process_data(int *data, int size) {
    DEBUG_PRINT("Processing %d elements", size);

    for (int i = 0; i < size; i++) {
        DEBUG_PRINT("data[%d] = %d", i, data[i]);
        data[i] *= 2;
    }

    DEBUG_PRINT("Processing complete");
    return 0;
}
```

### 2. Assertions

```c
#include <assert.h>

void array_set(int *arr, int index, int size, int value) {
    assert(arr != NULL);           // Catch null pointer
    assert(index >= 0);            // Catch negative index
    assert(index < size);          // Catch out of bounds
    assert(size > 0);              // Catch invalid size

    arr[index] = value;
}
```

### 3. Memory Debugging with Valgrind

```bash
# Compile with debug symbols
gcc -g -O0 program.c -o program

# Run with Valgrind
valgrind --leak-check=full --show-leak-kinds=all ./program

# Check for memory errors
valgrind --tool=memcheck ./program
```

### 4. GDB Debugging

```bash
# Compile with debug symbols
gcc -g program.c -o program

# Run GDB
gdb ./program

# Common GDB commands:
(gdb) break main          # Set breakpoint at main
(gdb) run arg1 arg2       # Run with arguments
(gdb) next                # Next line
(gdb) step                # Step into function
(gdb) print var           # Print variable
(gdb) backtrace           # Show call stack
(gdb) continue            # Continue execution
```

### 5. Logging System

```c
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} LogLevel;

static LogLevel current_log_level = LOG_INFO;
static FILE *log_file = NULL;

void log_init(const char *filename, LogLevel level) {
    log_file = fopen(filename, "a");
    current_log_level = level;
}

void log_message(LogLevel level, const char *fmt, ...) {
    if (level < current_log_level) return;

    const char *level_strings[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

    time_t now = time(NULL);
    char *timestamp = ctime(&now);
    timestamp[strlen(timestamp) - 1] = '\0';  // Remove newline

    FILE *output = log_file ? log_file : stderr;

    fprintf(output, "[%s] [%s] ", timestamp, level_strings[level]);

    va_list args;
    va_start(args, fmt);
    vfprintf(output, fmt, args);
    va_end(args);

    fprintf(output, "\n");
    fflush(output);
}

void log_cleanup() {
    if (log_file) {
        fclose(log_file);
        log_file = NULL;
    }
}

// Usage
int main() {
    log_init("app.log", LOG_DEBUG);

    log_message(LOG_INFO, "Application started");
    log_message(LOG_DEBUG, "Debug value: %d", 42);
    log_message(LOG_WARNING, "Low memory: %d MB", 100);
    log_message(LOG_ERROR, "Failed to open file: %s", "data.txt");

    log_cleanup();
    return 0;
}
```

---

## Performance Optimization

### 1. Profile Before Optimizing

**Don't guess - measure!**

```bash
# Use gprof for profiling
gcc -pg program.c -o program
./program
gprof program gmon.out > analysis.txt
```

### 2. Algorithmic Optimization

**Most important: Choose the right algorithm**

```c
// BAD: O(n^2) for searching
int linear_search(int *arr, int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

// GOOD: O(log n) if array is sorted
int binary_search(int *arr, int size, int target) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }

    return -1;
}
```

### 3. Minimize Memory Allocations

```c
// BAD: Allocate in loop
for (int i = 0; i < 1000; i++) {
    char *buffer = malloc(100);
    // ... use buffer ...
    free(buffer);
}

// GOOD: Allocate once
char *buffer = malloc(100);
for (int i = 0; i < 1000; i++) {
    // ... reuse buffer ...
}
free(buffer);
```

### 4. Cache-Friendly Code

```c
// BAD: Cache-unfriendly (column-major access)
for (int j = 0; j < cols; j++) {
    for (int i = 0; i < rows; i++) {
        matrix[i][j] = 0;  // Jumps in memory
    }
}

// GOOD: Cache-friendly (row-major access)
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        matrix[i][j] = 0;  // Sequential access
    }
}
```

### 5. Compiler Optimizations

```bash
# No optimization (for debugging)
gcc -O0 program.c -o program

# Basic optimization
gcc -O1 program.c -o program

# Recommended optimization
gcc -O2 program.c -o program

# Aggressive optimization
gcc -O3 program.c -o program

# Size optimization
gcc -Os program.c -o program
```

---

## Practice Exercises

### Exercise 1: Code Review (Medium)
Review and fix this code:
```c
#include <stdio.h>
#include <stdlib.h>

void f(int *a, int n) {
    for (int i = 0; i <= n; i++) {
        a[i] = i * 2;
    }
}

int main() {
    int *arr = malloc(10);
    f(arr, 10);
    for (int i = 0; i < 10; i++) {
        printf("%d\n", arr[i]);
    }
}
```
Find and fix all issues.

---

### Exercise 2: Refactoring (Hard)
Refactor this monolithic function into well-organized modules:
```c
void process_file(char *filename) {
    FILE *fp = fopen(filename, "r");
    char line[1000];
    int count = 0;
    int total = 0;
    while (fgets(line, 1000, fp)) {
        int val = atoi(line);
        if (val > 0 && val < 100) {
            total += val;
            count++;
        }
    }
    float avg = (float)total / count;
    printf("Average: %.2f\n", avg);
    fclose(fp);
}
```

---

### Exercise 3: Error Handling System (Hard)
Design a comprehensive error handling system with:
- Error codes enum
- Error message lookup
- Error stack trace
- Error logging
- Recovery mechanisms

---

### Exercise 4: Memory Pool Implementation (Advanced)
Implement a memory pool allocator:
```c
typedef struct MemoryPool MemoryPool;

MemoryPool* pool_create(size_t block_size, size_t block_count);
void* pool_alloc(MemoryPool *pool);
void pool_free(MemoryPool *pool, void *ptr);
void pool_destroy(MemoryPool *pool);
```

---

### Exercise 5: Testing Framework (Advanced)
Create a simple unit testing framework:
```c
#define TEST(name) void test_##name()
#define ASSERT_EQ(a, b) // Assert equal
#define ASSERT_NE(a, b) // Assert not equal
#define ASSERT_TRUE(cond)
#define ASSERT_FALSE(cond)
#define RUN_TEST(name)
```

---

### Exercise 6: Performance Comparison (Medium)
Compare performance of different sorting algorithms on arrays of varying sizes. Implement:
- Bubble sort
- Selection sort
- Insertion sort
- Quick sort
- Merge sort

Measure and graph execution time.

---

### Exercise 7: Documentation Generator (Hard)
Write a program that parses C header files and generates documentation from specially formatted comments.

---

### Exercise 8: Static Analyzer (Advanced)
Create a simple static analyzer that detects:
- Potential buffer overflows
- Memory leaks
- Uninitialized variables
- Dead code

---

## Summary

**Code Organization:**
- Separate interface (.h) from implementation (.c)
- Use header guards
- One module per file
- Clear directory structure

**Naming:**
- snake_case for variables and functions
- UPPERCASE for macros and constants
- Descriptive names
- Consistent prefixes for modules

**Memory Management:**
- Always check malloc/calloc
- Free everything you allocate
- Set pointers to NULL after free
- Use goto for cleanup in error paths

**Error Handling:**
- Return error codes consistently
- Fail fast with early validation
- Use errno for system errors
- Log errors appropriately

**Code Quality:**
- Write self-documenting code
- Comment WHY, not WHAT
- Keep functions small
- Avoid magic numbers
- Use const correctness

**Debugging:**
- Use assertions liberally
- Implement logging system
- Profile before optimizing
- Use Valgrind for memory issues
- Master GDB for debugging

**Performance:**
- Choose right algorithm first
- Minimize allocations
- Write cache-friendly code
- Profile to find bottlenecks
- Use compiler optimizations

**Golden Rule:** Write code as if the person maintaining it is a violent psychopath who knows where you live!

Master these practices and you'll write professional-quality C code!
