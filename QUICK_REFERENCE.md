# C Programming Quick Reference Guide

A one-page cheat sheet for quick lookup of C syntax and concepts.

---

## Table of Contents
- [Basic Syntax](#basic-syntax)
- [Data Types](#data-types)
- [Operators](#operators)
- [Control Structures](#control-structures)
- [Functions](#functions)
- [Arrays & Strings](#arrays--strings)
- [Pointers](#pointers)
- [Structures](#structures)
- [Dynamic Memory](#dynamic-memory)
- [File I/O](#file-io)
- [Common Functions](#common-functions)
- [Compilation](#compilation)

---

## Basic Syntax

```c
// Single-line comment
/* Multi-line
   comment */

#include <stdio.h>      // Standard I/O
#include <stdlib.h>     // Memory, conversion
#include <string.h>     // String functions

int main() {
    printf("Hello, World!\n");
    return 0;
}
```

---

## Data Types

### Primitive Types
```c
// Integer types
char c = 'A';                    // 1 byte
short s = 100;                   // 2 bytes
int i = 1000;                    // 4 bytes
long l = 100000L;                // 4/8 bytes
long long ll = 10000000000LL;    // 8 bytes

// Floating-point
float f = 3.14f;                 // 4 bytes
double d = 3.14159;              // 8 bytes
long double ld = 3.14159L;       // 10/16 bytes

// Unsigned variants
unsigned int ui = 100;
unsigned char uc = 255;

// Boolean (C99+)
#include <stdbool.h>
bool flag = true;
```

### Type Modifiers
```c
signed int x;        // Can be negative
unsigned int y;      // Only positive
short int s;         // Smaller range
long int l;          // Larger range
const int c = 10;    // Cannot change
```

### sizeof Operator
```c
sizeof(int)          // Size in bytes
sizeof(x)            // Size of variable
```

---

## Operators

### Arithmetic
```c
+   // Addition
-   // Subtraction
*   // Multiplication
/   // Division
%   // Modulus (remainder)
++  // Increment
--  // Decrement
```

### Relational
```c
==  // Equal to
!=  // Not equal
<   // Less than
>   // Greater than
<=  // Less than or equal
>=  // Greater than or equal
```

### Logical
```c
&&  // AND
||  // OR
!   // NOT
```

### Bitwise
```c
&   // AND
|   // OR
^   // XOR
~   // NOT (complement)
<<  // Left shift
>>  // Right shift
```

### Assignment
```c
=   // Assign
+=  // Add and assign
-=  // Subtract and assign
*=  // Multiply and assign
/=  // Divide and assign
%=  // Modulus and assign
```

---

## Control Structures

### If-Else
```c
if (condition) {
    // code
} else if (condition2) {
    // code
} else {
    // code
}

// Ternary operator
result = (condition) ? value1 : value2;
```

### Switch
```c
switch (variable) {
    case value1:
        // code
        break;
    case value2:
        // code
        break;
    default:
        // code
}
```

### Loops
```c
// For loop
for (int i = 0; i < n; i++) {
    // code
}

// While loop
while (condition) {
    // code
}

// Do-while loop
do {
    // code
} while (condition);

// Loop control
break;      // Exit loop
continue;   // Skip to next iteration
```

---

## Functions

### Declaration & Definition
```c
// Declaration (prototype)
int add(int a, int b);

// Definition
int add(int a, int b) {
    return a + b;
}

// Calling
int result = add(5, 3);
```

### Function Types
```c
void noReturn() { }              // No return value
int withReturn() { return 5; }   // Returns value
void withParams(int x, int y) { } // Parameters
```

### Recursion
```c
int factorial(int n) {
    if (n <= 1) return 1;        // Base case
    return n * factorial(n - 1); // Recursive call
}
```

---

## Arrays & Strings

### Arrays
```c
// Declaration
int arr[5];                      // Uninitialized
int arr[5] = {1, 2, 3, 4, 5};   // Initialized
int arr[] = {1, 2, 3};          // Size inferred

// 2D arrays
int matrix[3][4];
int matrix[2][3] = {{1,2,3}, {4,5,6}};

// Access
arr[0] = 10;                     // First element
int x = arr[2];                  // Third element
```

### Strings
```c
// Declaration
char str[50];                    // Fixed size
char str[] = "Hello";            // Size inferred
char *str = "Hello";             // String literal (read-only)

// Common functions (string.h)
strlen(str)                      // Length
strcpy(dest, src)               // Copy
strcat(dest, src)               // Concatenate
strcmp(str1, str2)              // Compare (0 if equal)
strchr(str, 'c')                // Find character
strstr(str, "sub")              // Find substring
```

---

## Pointers

### Basics
```c
int x = 10;
int *ptr = &x;        // ptr stores address of x
int value = *ptr;     // Dereference (get value)

// Pointer types
int *p;               // Pointer to int
char *c;              // Pointer to char
void *v;              // Generic pointer
```

### Pointer Arithmetic
```c
ptr++;                // Move to next element
ptr--;                // Move to previous element
ptr + n;              // Move n elements forward
ptr - n;              // Move n elements backward
```

### Arrays and Pointers
```c
int arr[5] = {1, 2, 3, 4, 5};
int *ptr = arr;       // arr is pointer to first element
*(ptr + 2)            // Same as arr[2]
ptr[2]                // Same as arr[2]
```

### Pointers to Pointers
```c
int x = 10;
int *ptr = &x;
int **ptr2 = &ptr;    // Pointer to pointer
```

### Function Pointers
```c
int (*funcPtr)(int, int);  // Declare
funcPtr = &add;            // Assign
int result = (*funcPtr)(5, 3);  // Call
```

---

## Structures

### Basic Structure
```c
// Definition
struct Student {
    int id;
    char name[50];
    float grade;
};

// Declaration
struct Student s1;
struct Student s2 = {1, "John", 85.5};

// Access members
s1.id = 1;
strcpy(s1.name, "John");
s1.grade = 85.5;
```

### Typedef
```c
typedef struct {
    int x;
    int y;
} Point;

Point p1;             // No need for 'struct' keyword
p1.x = 10;
```

### Pointers to Structures
```c
struct Student *ptr = &s1;
ptr->id = 1;          // Arrow operator for pointers
(*ptr).id = 1;        // Equivalent
```

### Nested Structures
```c
struct Address {
    char city[50];
    int zip;
};

struct Person {
    char name[50];
    struct Address addr;
};
```

---

## Dynamic Memory

### Memory Allocation
```c
#include <stdlib.h>

// malloc - allocate memory
int *ptr = (int*)malloc(5 * sizeof(int));
if (ptr == NULL) {
    // Allocation failed
}

// calloc - allocate and initialize to zero
int *ptr = (int*)calloc(5, sizeof(int));

// realloc - resize allocated memory
ptr = (int*)realloc(ptr, 10 * sizeof(int));

// free - deallocate memory
free(ptr);
ptr = NULL;  // Good practice
```

### Example
```c
// Dynamic array
int n = 10;
int *arr = (int*)malloc(n * sizeof(int));
for (int i = 0; i < n; i++) {
    arr[i] = i * 10;
}
free(arr);

// Dynamic 2D array
int **matrix = (int**)malloc(rows * sizeof(int*));
for (int i = 0; i < rows; i++) {
    matrix[i] = (int*)malloc(cols * sizeof(int));
}
// Don't forget to free!
for (int i = 0; i < rows; i++) {
    free(matrix[i]);
}
free(matrix);
```

---

## File I/O

### File Operations
```c
#include <stdio.h>

// Open file
FILE *fp = fopen("file.txt", "r");  // Read
FILE *fp = fopen("file.txt", "w");  // Write (overwrite)
FILE *fp = fopen("file.txt", "a");  // Append
FILE *fp = fopen("file.txt", "r+"); // Read/Write

// Check if opened
if (fp == NULL) {
    perror("Error opening file");
    return 1;
}

// Close file
fclose(fp);
```

### Reading
```c
// Read character
int c = fgetc(fp);

// Read string
char str[100];
fgets(str, 100, fp);

// Read formatted
int num;
fscanf(fp, "%d", &num);

// Read binary
fread(buffer, size, count, fp);
```

### Writing
```c
// Write character
fputc('A', fp);

// Write string
fputs("Hello\n", fp);

// Write formatted
fprintf(fp, "Number: %d\n", num);

// Write binary
fwrite(buffer, size, count, fp);
```

### File Positioning
```c
fseek(fp, offset, SEEK_SET);  // From beginning
fseek(fp, offset, SEEK_CUR);  // From current position
fseek(fp, offset, SEEK_END);  // From end
long pos = ftell(fp);         // Get current position
rewind(fp);                   // Go to beginning
```

---

## Common Functions

### stdio.h
```c
printf("format", ...)     // Print to stdout
scanf("format", ...)      // Read from stdin
sprintf(str, "fmt", ...)  // Print to string
sscanf(str, "fmt", ...)   // Read from string
puts("string")            // Print string with newline
gets(str)                 // Read line (unsafe, use fgets)
getchar()                 // Read character
putchar(c)                // Write character
```

### stdlib.h
```c
malloc(size)              // Allocate memory
calloc(n, size)          // Allocate and zero
realloc(ptr, size)       // Resize memory
free(ptr)                // Deallocate memory
exit(0)                  // Exit program
atoi("123")              // String to int
atof("3.14")             // String to float
rand()                   // Random number
srand(time(NULL))        // Seed random
abs(x)                   // Absolute value
```

### string.h
```c
strlen(str)              // Length
strcpy(dest, src)        // Copy
strncpy(dest, src, n)    // Copy n chars
strcat(dest, src)        // Concatenate
strncat(dest, src, n)    // Concatenate n chars
strcmp(s1, s2)           // Compare
strncmp(s1, s2, n)       // Compare n chars
strchr(str, 'c')         // Find char
strstr(str, "sub")       // Find substring
memset(ptr, val, n)      // Set memory
memcpy(dest, src, n)     // Copy memory
```

### math.h
```c
// Compile with -lm flag
pow(x, y)                // x^y
sqrt(x)                  // Square root
abs(x)                   // Absolute (int)
fabs(x)                  // Absolute (float)
ceil(x)                  // Round up
floor(x)                 // Round down
sin(x), cos(x), tan(x)   // Trig functions
log(x), log10(x)         // Logarithms
```

### ctype.h
```c
isalpha(c)               // Is letter?
isdigit(c)               // Is digit?
isalnum(c)               // Is letter or digit?
isspace(c)               // Is whitespace?
isupper(c)               // Is uppercase?
islower(c)               // Is lowercase?
toupper(c)               // Convert to uppercase
tolower(c)               // Convert to lowercase
```

---

## Compilation

### Basic Compilation
```bash
# Compile to executable
gcc program.c -o program

# Compile and run
gcc program.c && ./program

# With warnings
gcc -Wall program.c -o program

# With debugging symbols
gcc -g program.c -o program

# Optimization
gcc -O2 program.c -o program
```

### Multiple Files
```bash
# Compile separately
gcc -c file1.c -o file1.o
gcc -c file2.c -o file2.o
gcc file1.o file2.o -o program

# Compile together
gcc file1.c file2.c -o program
```

### Common Flags
```bash
-Wall                    # All warnings
-Werror                  # Treat warnings as errors
-g                       # Debug symbols
-O0, -O1, -O2, -O3      # Optimization levels
-std=c99                 # Use C99 standard
-lm                      # Link math library
-I/path/to/includes      # Include directory
-L/path/to/libs          # Library directory
```

---

## Format Specifiers

```c
%d or %i     // int
%u           // unsigned int
%ld          // long
%lld         // long long
%f           // float/double
%lf          // double (scanf only)
%e           // Scientific notation
%c           // char
%s           // string
%p           // pointer address
%x or %X     // Hexadecimal
%o           // Octal
%%           // Literal %

// Width and precision
%5d          // Min width 5
%05d         // Pad with zeros
%.2f         // 2 decimal places
%10.2f       // Width 10, 2 decimals
%-10s        // Left-aligned, width 10
```

---

## Escape Sequences

```c
\n           // Newline
\t           // Tab
\\           // Backslash
\'           // Single quote
\"           // Double quote
\0           // Null character
\r           // Carriage return
\b           // Backspace
\a           // Alert (bell)
```

---

## Preprocessor Directives

```c
#include <stdio.h>       // Include system header
#include "myfile.h"      // Include user header

#define PI 3.14159       // Define constant
#define MAX(a,b) ((a)>(b)?(a):(b))  // Macro

#ifdef DEBUG             // Conditional compilation
    // Debug code
#endif

#ifndef HEADER_H
#define HEADER_H
    // Header contents
#endif

#undef PI                // Undefine

#pragma once             // Include guard (modern)
```

---

## Common Patterns

### Swap Variables
```c
int temp = a;
a = b;
b = temp;

// With XOR (integers only)
a = a ^ b;
b = a ^ b;
a = a ^ b;
```

### Read Until EOF
```c
while (scanf("%d", &num) == 1) {
    // process num
}

// Or
int c;
while ((c = getchar()) != EOF) {
    // process c
}
```

### Dynamic String
```c
char *str = (char*)malloc(100 * sizeof(char));
fgets(str, 100, stdin);
str[strcspn(str, "\n")] = '\0';  // Remove newline
free(str);
```

### Error Checking
```c
FILE *fp = fopen("file.txt", "r");
if (fp == NULL) {
    perror("Error");
    exit(EXIT_FAILURE);
}
```

---

## Common Mistakes to Avoid

❌ **Buffer overflow**
```c
char str[5];
strcpy(str, "Hello World");  // BAD: overflow
```

✅ **Use safe functions**
```c
strncpy(str, "Hello", 4);
str[4] = '\0';
```

❌ **Dangling pointer**
```c
int *ptr = (int*)malloc(sizeof(int));
free(ptr);
*ptr = 10;  // BAD: accessing freed memory
```

✅ **Set to NULL after free**
```c
free(ptr);
ptr = NULL;
```

❌ **Memory leak**
```c
void func() {
    int *ptr = (int*)malloc(100);
    // No free()
}
```

✅ **Always free**
```c
void func() {
    int *ptr = (int*)malloc(100);
    // Use ptr
    free(ptr);
}
```

❌ **Uninitialized variable**
```c
int x;
printf("%d", x);  // BAD: garbage value
```

✅ **Initialize**
```c
int x = 0;
printf("%d", x);
```

---

## Debugging Tips

```c
// Print debugging
printf("Debug: x = %d\n", x);

// Assert
#include <assert.h>
assert(x > 0);  // Abort if false

// GDB commands
gdb ./program
(gdb) break main
(gdb) run
(gdb) next
(gdb) print x
(gdb) quit

// Valgrind (memory leaks)
valgrind --leak-check=full ./program
```

---

<div align="center">

## Quick Reference Complete!

Keep this page bookmarked for quick lookup while coding.

**[Back to Main README →](README.md)**

</div>
