# C Preprocessor Directives

## Table of Contents
1. [Introduction to Preprocessor](#introduction)
2. [File Inclusion](#file-inclusion)
3. [Macro Definitions](#macro-definitions)
4. [Conditional Compilation](#conditional-compilation)
5. [Predefined Macros](#predefined-macros)
6. [Advanced Macro Techniques](#advanced-macro-techniques)
7. [Best Practices](#best-practices)
8. [Practice Exercises](#practice-exercises)

---

## Introduction to Preprocessor

The C preprocessor is a text substitution tool that runs before actual compilation. It processes directives (lines starting with `#`) and produces modified source code for the compiler.

### Preprocessing Stages

```
Source Code (.c, .h)
        ↓
   Preprocessor (cpp)
        ↓
Expanded Source (temporary)
        ↓
   Compiler (cc)
        ↓
  Object Code (.o)
        ↓
   Linker (ld)
        ↓
  Executable
```

### Key Characteristics

- **Text-based**: Works on source text, not compiled code
- **No type checking**: Pure text substitution
- **Compile-time**: Happens before compilation
- **Directives start with #**: Must be first non-whitespace character on line

### Common Use Cases

1. **File inclusion**: `#include` for header files
2. **Macro definitions**: `#define` for constants and functions
3. **Conditional compilation**: `#ifdef`, `#ifndef`, `#if`
4. **Header guards**: Prevent multiple inclusion
5. **Platform-specific code**: Compile different code for different systems

---

## File Inclusion

### 1. #include Directive

Two forms:

```c
#include <stdio.h>      // System/standard headers (searches system paths)
#include "myheader.h"   // User headers (searches current directory first)
```

### Search Order

**Angle brackets `<>`:**
```
1. Standard system directories (/usr/include, /usr/local/include, etc.)
2. Compiler-specific directories
```

**Double quotes `""`:**
```
1. Current directory (where source file is)
2. Directories specified with -I compiler flag
3. Standard system directories (as fallback)
```

### Example 1: Basic Header Usage

**math_utils.h:**
```c
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

// Function declarations
int add(int a, int b);
int multiply(int a, int b);

// Macro
#define PI 3.14159

#endif
```

**math_utils.c:**
```c
#include "math_utils.h"

int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}
```

**main.c:**
```c
#include <stdio.h>
#include "math_utils.h"

int main() {
    printf("5 + 3 = %d\n", add(5, 3));
    printf("5 * 3 = %d\n", multiply(5, 3));
    printf("PI = %.5f\n", PI);
    return 0;
}
```

### 2. Header Guards

Prevent multiple inclusion of the same header file.

**Method 1: Traditional (using #ifndef)**
```c
#ifndef HEADER_NAME_H
#define HEADER_NAME_H

// Header contents here

#endif  // HEADER_NAME_H
```

**Method 2: Pragma once (modern, not standard but widely supported)**
```c
#pragma once

// Header contents here
```

### Why Header Guards Matter

**Without guards:**
```c
// config.h
struct Config {
    int value;
};

// utils.h
#include "config.h"

// main.c
#include "config.h"  // First inclusion
#include "utils.h"   // Second inclusion (includes config.h again)
// ERROR: struct Config redefined!
```

**With guards:**
```c
// config.h
#ifndef CONFIG_H
#define CONFIG_H

struct Config {
    int value;
};

#endif

// Now safe to include multiple times!
```

### 3. Nested Includes

Headers can include other headers:

```c
// types.h
#ifndef TYPES_H
#define TYPES_H

typedef struct {
    int x, y;
} Point;

#endif

// graphics.h
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "types.h"  // graphics.h depends on types.h

void draw_point(Point p);

#endif

// main.c
#include "graphics.h"  // Automatically includes types.h
```

---

## Macro Definitions

### 1. Object-like Macros (Constants)

```c
#define IDENTIFIER replacement_text
```

**Example:**
```c
#define MAX_SIZE 100
#define PI 3.14159265359
#define COMPANY_NAME "Tech Corp"
#define DEBUG

int arr[MAX_SIZE];  // Becomes: int arr[100];
float area = PI * r * r;  // Becomes: float area = 3.14159265359 * r * r;
```

### 2. Function-like Macros

```c
#define MACRO_NAME(parameters) replacement_text
```

**Example:**
```c
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define IS_EVEN(n) ((n) % 2 == 0)

int result = SQUARE(5);      // Becomes: ((5) * (5)) = 25
int max_val = MAX(10, 20);   // Becomes: ((10) > (20) ? (10) : (20)) = 20
```

### 3. Why Parentheses Matter

**Bad (without parentheses):**
```c
#define SQUARE(x) x * x

int result = SQUARE(2 + 3);
// Expands to: 2 + 3 * 2 + 3 = 2 + 6 + 3 = 11 (WRONG!)
// Expected: (2 + 3) * (2 + 3) = 25

int result2 = 100 / SQUARE(5);
// Expands to: 100 / 5 * 5 = 100 (WRONG!)
// Expected: 100 / (5 * 5) = 4
```

**Good (with parentheses):**
```c
#define SQUARE(x) ((x) * (x))

int result = SQUARE(2 + 3);
// Expands to: ((2 + 3) * (2 + 3)) = 25 (CORRECT!)

int result2 = 100 / SQUARE(5);
// Expands to: 100 / ((5) * (5)) = 4 (CORRECT!)
```

### 4. Multi-line Macros

Use backslash `\` for continuation:

```c
#define SWAP(a, b, type) \
    do { \
        type temp = (a); \
        (a) = (b); \
        (b) = temp; \
    } while(0)

// Usage
int x = 5, y = 10;
SWAP(x, y, int);
printf("x = %d, y = %d\n", x, y);  // x = 10, y = 5
```

**Why `do { ... } while(0)`?**

Makes the macro behave like a single statement:

```c
// Without do-while:
#define BAD_SWAP(a, b, type) \
    type temp = (a); \
    (a) = (b); \
    (b) = temp;

// Problem:
if (condition)
    BAD_SWAP(x, y, int);  // Only first line of macro in if!
else
    something_else();     // Syntax error!

// With do-while:
#define GOOD_SWAP(a, b, type) \
    do { \
        type temp = (a); \
        (a) = (b); \
        (b) = temp; \
    } while(0)

// Works correctly:
if (condition)
    GOOD_SWAP(x, y, int);  // Entire macro is one statement
else
    something_else();
```

### 5. Stringification (#)

Convert macro argument to string literal:

```c
#define TO_STRING(x) #x
#define PRINT_VAR(var) printf(#var " = %d\n", var)

// Examples
printf(TO_STRING(Hello));  // Prints: Hello
// Expands to: printf("Hello");

int age = 25;
PRINT_VAR(age);  // Prints: age = 25
// Expands to: printf("age" " = %d\n", age);
```

### 6. Token Pasting (##)

Concatenate tokens:

```c
#define CONCAT(a, b) a##b
#define MAKE_FUNCTION(name) void func_##name() { printf("Function: " #name "\n"); }

int CONCAT(num, 123) = 456;  // Becomes: int num123 = 456;

MAKE_FUNCTION(test)  // Creates: void func_test() { printf("Function: test\n"); }
MAKE_FUNCTION(demo)  // Creates: void func_demo() { printf("Function: demo\n"); }

int main() {
    func_test();  // Prints: Function: test
    func_demo();  // Prints: Function: demo
    return 0;
}
```

### 7. #undef - Undefine Macro

```c
#define SIZE 100
// ... use SIZE ...

#undef SIZE  // SIZE no longer defined

#define SIZE 200  // Redefine with new value
```

### 8. Useful Macro Examples

```c
// Min/Max
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Array size
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// Bit manipulation
#define SET_BIT(num, pos) ((num) |= (1 << (pos)))
#define CLEAR_BIT(num, pos) ((num) &= ~(1 << (pos)))
#define TOGGLE_BIT(num, pos) ((num) ^= (1 << (pos)))
#define CHECK_BIT(num, pos) (((num) >> (pos)) & 1)

// Debugging
#define DEBUG_PRINT(fmt, ...) \
    fprintf(stderr, "[%s:%d] " fmt, __FILE__, __LINE__, ##__VA_ARGS__)

// Safe memory
#define SAFE_FREE(ptr) \
    do { \
        if ((ptr) != NULL) { \
            free(ptr); \
            (ptr) = NULL; \
        } \
    } while(0)

// Usage examples
int arr[] = {1, 2, 3, 4, 5};
int size = ARRAY_SIZE(arr);  // 5

int flags = 0;
SET_BIT(flags, 3);    // flags = 0b1000 = 8
TOGGLE_BIT(flags, 1); // flags = 0b1010 = 10

int *ptr = malloc(100);
SAFE_FREE(ptr);  // Frees and sets to NULL
```

---

## Conditional Compilation

Compile different code based on conditions.

### 1. #ifdef / #ifndef

```c
#ifdef IDENTIFIER
    // Compiled if IDENTIFIER is defined
#endif

#ifndef IDENTIFIER
    // Compiled if IDENTIFIER is NOT defined
#endif
```

**Example:**
```c
#define DEBUG

#ifdef DEBUG
    printf("Debug mode: x = %d\n", x);
#endif

#ifndef RELEASE
    printf("Not in release mode\n");
#endif
```

### 2. #if / #elif / #else / #endif

```c
#if expression
    // Code if expression is true (non-zero)
#elif another_expression
    // Code if another_expression is true
#else
    // Code if all expressions are false
#endif
```

**Example:**
```c
#define VERSION 2

#if VERSION == 1
    printf("Version 1\n");
#elif VERSION == 2
    printf("Version 2\n");
#else
    printf("Unknown version\n");
#endif
```

### 3. defined() Operator

Check if macro is defined:

```c
#if defined(DEBUG) && defined(VERBOSE)
    printf("Debug and verbose mode\n");
#endif

// Equivalent to:
#if defined(DEBUG)
    #if defined(VERBOSE)
        printf("Debug and verbose mode\n");
    #endif
#endif
```

### 4. Platform-Specific Code

```c
#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
#elif defined(__linux__)
    #include <unistd.h>
    #define SLEEP(ms) usleep((ms) * 1000)
#elif defined(__APPLE__)
    #include <unistd.h>
    #define SLEEP(ms) usleep((ms) * 1000)
#else
    #error "Unsupported platform"
#endif

int main() {
    printf("Sleeping for 1 second...\n");
    SLEEP(1000);
    printf("Done!\n");
    return 0;
}
```

### 5. Debug vs Release Builds

```c
#ifdef DEBUG
    #define LOG(msg) printf("[DEBUG] %s\n", msg)
    #define ASSERT(cond) \
        if (!(cond)) { \
            fprintf(stderr, "Assertion failed: %s, file %s, line %d\n", \
                    #cond, __FILE__, __LINE__); \
            abort(); \
        }
#else
    #define LOG(msg)      // Empty in release
    #define ASSERT(cond)  // Empty in release
#endif

int main() {
    LOG("Program started");  // Only prints in debug builds

    int x = 5;
    ASSERT(x > 0);  // Only checks in debug builds

    LOG("Program ended");
    return 0;
}
```

**Compile:**
```bash
gcc -DDEBUG program.c -o program_debug    # Debug build
gcc program.c -o program_release          # Release build
```

### 6. Feature Flags

```c
// config.h
#define FEATURE_DATABASE
// #define FEATURE_NETWORKING  // Commented out = disabled
#define FEATURE_LOGGING

// main.c
#include "config.h"

int main() {
    #ifdef FEATURE_DATABASE
        init_database();
    #endif

    #ifdef FEATURE_NETWORKING
        init_network();
    #endif

    #ifdef FEATURE_LOGGING
        init_logger();
    #endif

    return 0;
}
```

### 7. #error and #warning

```c
#ifndef CONFIG_H_INCLUDED
    #error "You must include config.h before this file"
#endif

#if SIZE > 1000
    #warning "SIZE is very large, may cause performance issues"
#endif

#ifdef DEPRECATED_API
    #error "This API is deprecated and no longer supported"
#endif
```

---

## Predefined Macros

Standard predefined macros available in all C compilers:

### Standard Predefined Macros

```c
#include <stdio.h>

int main() {
    printf("File: %s\n", __FILE__);          // Current source file name
    printf("Line: %d\n", __LINE__);          // Current line number
    printf("Date: %s\n", __DATE__);          // Compilation date (Mmm dd yyyy)
    printf("Time: %s\n", __TIME__);          // Compilation time (hh:mm:ss)
    printf("Standard: %ld\n", __STDC_VERSION__);  // C standard version

    #ifdef __STDC__
        printf("Standard C conforming\n");
    #endif

    return 0;
}
```

**Output example:**
```
File: main.c
Line: 4
Date: Jan 14 2026
Time: 15:30:45
Standard: 201710
Standard C conforming
```

### Compiler-Specific Macros

```c
#ifdef __GNUC__
    printf("GCC version: %d.%d.%d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#endif

#ifdef _MSC_VER
    printf("Microsoft Visual C++ version: %d\n", _MSC_VER);
#endif

#ifdef __clang__
    printf("Clang compiler\n");
#endif
```

### Platform Detection Macros

```c
#ifdef _WIN32
    printf("Windows (32 or 64-bit)\n");
#endif

#ifdef _WIN64
    printf("Windows 64-bit\n");
#endif

#ifdef __linux__
    printf("Linux\n");
#endif

#ifdef __APPLE__
    printf("macOS\n");
#endif

#ifdef __unix__
    printf("Unix-like system\n");
#endif
```

### Architecture Macros

```c
#ifdef __x86_64__
    printf("64-bit x86 architecture\n");
#elif defined(__i386__)
    printf("32-bit x86 architecture\n");
#elif defined(__arm__)
    printf("ARM architecture\n");
#endif
```

---

## Advanced Macro Techniques

### 1. Variadic Macros

Macros that accept variable number of arguments:

```c
#define PRINT_ARGS(...) printf(__VA_ARGS__)
#define LOG(level, ...) printf("[%s] ", level); printf(__VA_ARGS__); printf("\n")

PRINT_ARGS("x = %d, y = %d\n", 5, 10);
LOG("INFO", "User %s logged in", "Alice");
LOG("ERROR", "Failed with code %d", 404);
```

**Output:**
```
x = 5, y = 10
[INFO] User Alice logged in
[ERROR] Failed with code 404
```

### 2. Macro Overloading (Count-based)

```c
// Count arguments helper
#define NARGS_SEQ(_1,_2,_3,_4,_5,N,...) N
#define NARGS(...) NARGS_SEQ(__VA_ARGS__, 5, 4, 3, 2, 1)

// Overloading based on argument count
#define CONCAT_(a,b) a##b
#define CONCAT(a,b) CONCAT_(a,b)

#define PRINT_1(a) printf("%d\n", a)
#define PRINT_2(a,b) printf("%d %d\n", a, b)
#define PRINT_3(a,b,c) printf("%d %d %d\n", a, b, c)

#define PRINT(...) CONCAT(PRINT_, NARGS(__VA_ARGS__))(__VA_ARGS__)

int main() {
    PRINT(5);        // Calls PRINT_1
    PRINT(5, 10);    // Calls PRINT_2
    PRINT(5, 10, 15); // Calls PRINT_3
    return 0;
}
```

### 3. X-Macros (Code Generation)

Generate related code from a single definition:

```c
// Define list of error codes
#define ERROR_CODES \
    X(SUCCESS, "Operation successful") \
    X(ERR_FILE_NOT_FOUND, "File not found") \
    X(ERR_PERMISSION_DENIED, "Permission denied") \
    X(ERR_INVALID_INPUT, "Invalid input") \
    X(ERR_OUT_OF_MEMORY, "Out of memory")

// Generate enum
#define X(name, desc) name,
typedef enum {
    ERROR_CODES
} ErrorCode;
#undef X

// Generate string descriptions
#define X(name, desc) desc,
const char *error_messages[] = {
    ERROR_CODES
};
#undef X

// Generate function
const char* get_error_message(ErrorCode code) {
    if (code >= 0 && code < sizeof(error_messages) / sizeof(error_messages[0])) {
        return error_messages[code];
    }
    return "Unknown error";
}

int main() {
    ErrorCode err = ERR_FILE_NOT_FOUND;
    printf("Error: %s\n", get_error_message(err));
    return 0;
}
```

### 4. Type-Generic Macros (_Generic)

C11 feature for compile-time type selection:

```c
#include <stdio.h>

#define print_value(x) _Generic((x), \
    int: printf("Integer: %d\n", x), \
    float: printf("Float: %.2f\n", x), \
    double: printf("Double: %.2f\n", x), \
    char*: printf("String: %s\n", x), \
    default: printf("Unknown type\n") \
)

int main() {
    print_value(42);          // Integer: 42
    print_value(3.14f);       // Float: 3.14
    print_value(2.71828);     // Double: 2.72
    print_value("Hello");     // String: Hello
    return 0;
}
```

### 5. Compile-Time Assertions

```c
#define STATIC_ASSERT(condition, message) \
    typedef char static_assertion_##message[(condition) ? 1 : -1]

// C11 alternative:
#include <assert.h>
_Static_assert(sizeof(int) == 4, "int must be 4 bytes");

// Usage
STATIC_ASSERT(sizeof(int) >= 4, int_size_check);
STATIC_ASSERT(sizeof(void*) == 8, pointer_size_check);  // For 64-bit
```

---

## Best Practices

### 1. Naming Conventions

```c
// Use UPPERCASE for macros
#define MAX_SIZE 100
#define CALCULATE_AREA(r) (3.14159 * (r) * (r))

// Use descriptive names
#define MAX_USERNAME_LENGTH 50  // Good
#define M 50                    // Bad

// Prefix project-specific macros
#define MYAPP_VERSION 1
#define MYAPP_MAX_CONNECTIONS 100
```

### 2. Prefer Enums and Const Over Macros for Constants

```c
// BAD: No type safety
#define WIDTH 100
#define HEIGHT 200

// BETTER: Type-safe, debugger-friendly
enum { WIDTH = 100, HEIGHT = 200 };

// BETTER: For single constants
const int WIDTH = 100;
const int HEIGHT = 200;
```

### 3. Prefer Inline Functions Over Function-like Macros

```c
// Macro: No type checking, debugging issues
#define SQUARE(x) ((x) * (x))

// Inline function: Type-safe, debugger-friendly
static inline int square(int x) {
    return x * x;
}
```

**When to use macros:**
- Generic code (works with any type)
- Compile-time constants
- Conditional compilation
- Code generation

**When to use inline functions:**
- Type safety matters
- Debugging needed
- Side effects must be avoided

### 4. Always Use Parentheses

```c
// BAD
#define TWICE(x) x + x
#define SQUARE(x) x * x

// GOOD
#define TWICE(x) ((x) + (x))
#define SQUARE(x) ((x) * (x))
```

### 5. Multi-statement Macros Use do-while(0)

```c
#define SWAP(a, b, type) \
    do { \
        type temp = (a); \
        (a) = (b); \
        (b) = temp; \
    } while(0)
```

### 6. Document Macros

```c
/**
 * Calculates the area of a circle.
 * @param r Radius of the circle
 * @return Area as a double
 */
#define CIRCLE_AREA(r) (3.14159265359 * (r) * (r))

/**
 * Safe pointer free: Frees memory and sets pointer to NULL.
 * Prevents use-after-free and double-free bugs.
 */
#define SAFE_FREE(ptr) \
    do { \
        if ((ptr) != NULL) { \
            free(ptr); \
            (ptr) = NULL; \
        } \
    } while(0)
```

### 7. Include Guards Standard

```c
// File: my_module.h
#ifndef MY_MODULE_H
#define MY_MODULE_H

// Header contents

#endif /* MY_MODULE_H */
```

---

## Practice Exercises

### Exercise 1: Configuration System (Medium)
Create a configuration system using preprocessor:
```c
// config.h - Define capabilities
#define ENABLE_LOGGING
#define ENABLE_CACHING
#define MAX_USERS 1000
#define VERSION_MAJOR 2
#define VERSION_MINOR 5
```

Write macros that:
- Print version string "v2.5"
- Conditionally enable/disable features
- Provide compile-time size checks

---

### Exercise 2: Debug Macro System (Hard)
Create a comprehensive debug system:
```c
#define DEBUG_LEVEL 2  // 0=off, 1=error, 2=warning, 3=info, 4=verbose

#define LOG_ERROR(...)   // Only if DEBUG_LEVEL >= 1
#define LOG_WARNING(...) // Only if DEBUG_LEVEL >= 2
#define LOG_INFO(...)    // Only if DEBUG_LEVEL >= 3
#define LOG_VERBOSE(...) // Only if DEBUG_LEVEL >= 4
```

Each should print file, line, function name, and message.

---

### Exercise 3: Unit Testing Macros (Hard)
Create simple unit testing macros:
```c
#define TEST(name) void test_##name()
#define ASSERT_EQ(a, b) // Assert equal, print on failure
#define ASSERT_NE(a, b) // Assert not equal
#define ASSERT_TRUE(cond)
#define RUN_TEST(name)  // Run test and report result
```

**Example usage:**
```c
TEST(addition) {
    ASSERT_EQ(2 + 2, 4);
    ASSERT_EQ(10 + 5, 15);
}

int main() {
    RUN_TEST(addition);
}
```

---

### Exercise 4: Generic Data Structure Macros (Advanced)
Create macros to generate type-specific vector (dynamic array) implementations:
```c
#define DEFINE_VECTOR(type) \
    /* Generate struct, functions for type */ \
    typedef struct { \
        type *data; \
        int size; \
        int capacity; \
    } vector_##type;
```

Should generate: create, push, pop, get, free functions for any type.

---

### Exercise 5: Platform Abstraction (Medium)
Create platform-independent file system macros:
```c
// Should work on Windows, Linux, macOS
#define PATH_SEPARATOR  // '\\' on Windows, '/' on Unix
#define CLEAR_SCREEN    // "cls" on Windows, "clear" on Unix
#define SLEEP(ms)       // Sleep/usleep based on platform
```

Test on your platform.

---

### Exercise 6: Bit Manipulation Library (Medium)
Create comprehensive bit manipulation macros:
```c
#define SET_BIT(num, pos)
#define CLEAR_BIT(num, pos)
#define TOGGLE_BIT(num, pos)
#define CHECK_BIT(num, pos)
#define SET_BITS(num, mask)      // Set multiple bits
#define CLEAR_BITS(num, mask)
#define CREATE_MASK(from, to)    // Create bit mask from bit 'from' to 'to'
#define EXTRACT_BITS(num, from, to)  // Extract bit range
```

---

### Exercise 7: X-Macro for State Machine (Advanced)
Use X-macros to define a state machine:
```c
#define STATES \
    X(IDLE, "System idle") \
    X(RUNNING, "System running") \
    X(PAUSED, "System paused") \
    X(ERROR, "System error")
```

Generate:
- Enum of states
- String names array
- Transition validation function
- State pretty-printer

---

### Exercise 8: Conditional Feature Implementation (Hard)
Create a program with optional features controlled by preprocessor:

Features:
- Database support (SQLITE, MYSQL, or none)
- Logging (FILE, CONSOLE, SYSLOG, or none)
- Compression (ZLIB, GZIP, or none)

Each combination should compile cleanly. Use `#if defined()` to handle all combinations.

**Bonus:** Auto-detect features if headers are available.

---

## Summary

**Key Directives:**

| Directive | Purpose |
|-----------|---------|
| `#include` | Include header files |
| `#define` | Define macros |
| `#undef` | Undefine macros |
| `#ifdef` | If defined |
| `#ifndef` | If not defined |
| `#if` | Conditional compilation |
| `#elif` | Else if |
| `#else` | Else |
| `#endif` | End conditional |
| `#error` | Generate compilation error |
| `#warning` | Generate compilation warning |
| `#pragma` | Compiler-specific directive |

**Macro Operators:**

| Operator | Purpose | Example |
|----------|---------|---------|
| `#` | Stringification | `#x` → `"x"` |
| `##` | Token pasting | `a##b` → `ab` |
| `__VA_ARGS__` | Variadic arguments | `...` |

**Best Practices:**
1. Use UPPERCASE for macros
2. Always use parentheses in macro expressions
3. Use do-while(0) for multi-statement macros
4. Prefer inline functions over macros when possible
5. Use header guards in all header files
6. Document complex macros
7. Be careful with side effects in macro arguments

**Common Pitfalls:**
- Missing parentheses causing precedence issues
- Multiple evaluation of arguments with side effects
- Macro naming conflicts
- Forgetting header guards
- Using macros when functions would be better

Master the preprocessor and you'll write more maintainable, portable C code!
