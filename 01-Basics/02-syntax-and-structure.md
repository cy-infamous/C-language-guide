# Syntax and Structure of C Programs

## Understanding Program Structure

Every C program follows a specific structure. Let's break down a complete C program and understand each component.

### Anatomy of a C Program

```c
/* 1. PREPROCESSOR DIRECTIVES */
#include <stdio.h>
#include <stdlib.h>
#define PI 3.14159

/* 2. GLOBAL DECLARATIONS */
int global_variable = 100;

/* 3. FUNCTION PROTOTYPES */
void displayMessage();
int add(int a, int b);

/* 4. MAIN FUNCTION */
int main() {
    /* 5. LOCAL DECLARATIONS */
    int local_variable = 50;

    /* 6. STATEMENTS */
    printf("This is the main function\n");
    displayMessage();

    /* 7. RETURN STATEMENT */
    return 0;
}

/* 8. FUNCTION DEFINITIONS */
void displayMessage() {
    printf("Hello from displayMessage function!\n");
}

int add(int a, int b) {
    return a + b;
}
```

### Structural Components Explained

```
┌─────────────────────────────────────────┐
│    PREPROCESSOR DIRECTIVES              │
│    #include, #define                    │
├─────────────────────────────────────────┤
│    GLOBAL DECLARATIONS                  │
│    Variables, constants                 │
├─────────────────────────────────────────┤
│    FUNCTION PROTOTYPES                  │
│    Function declarations                │
├─────────────────────────────────────────┤
│    MAIN FUNCTION                        │
│    ┌─────────────────────────────────┐ │
│    │ Local Variables                 │ │
│    │ Statements                      │ │
│    │ Function Calls                  │ │
│    │ Return Statement                │ │
│    └─────────────────────────────────┘ │
├─────────────────────────────────────────┤
│    OTHER FUNCTION DEFINITIONS           │
│    User-defined functions               │
└─────────────────────────────────────────┘
```

## 1. Preprocessor Directives

Preprocessor directives are instructions processed **before** compilation begins. They start with `#`.

### Include Directive: `#include`

```c
#include <stdio.h>     // Standard library (system path)
#include "myheader.h"  // User-defined header (current directory)
```

**Common Standard Headers:**

| Header File | Purpose | Common Functions |
|-------------|---------|------------------|
| `stdio.h` | Standard Input/Output | `printf()`, `scanf()`, `getchar()` |
| `stdlib.h` | Standard Library | `malloc()`, `free()`, `exit()` |
| `string.h` | String Operations | `strlen()`, `strcpy()`, `strcmp()` |
| `math.h` | Mathematical Functions | `sqrt()`, `pow()`, `sin()`, `cos()` |
| `ctype.h` | Character Classification | `isalpha()`, `isdigit()`, `toupper()` |
| `time.h` | Time/Date Functions | `time()`, `clock()`, `difftime()` |

### Define Directive: `#define`

Creates symbolic constants (macros).

```c
#include <stdio.h>

#define PI 3.14159
#define MAX_SIZE 100
#define GREETING "Hello, World!"
#define SQUARE(x) ((x) * (x))

int main() {
    printf("Value of PI: %f\n", PI);
    printf("Max size: %d\n", MAX_SIZE);
    printf("%s\n", GREETING);
    printf("Square of 5: %d\n", SQUARE(5));

    return 0;
}
```

**Output:**
```
Value of PI: 3.141590
Max size: 100
Hello, World!
Square of 5: 25
```

**Why use `#define`?**
- Easy to change values (change once, affects entire program)
- Better code readability
- No memory allocation (replaced during preprocessing)

## 2. The Main Function

The `main()` function is the **entry point** of every C program.

### Standard Forms of main()

```c
// Form 1: No command-line arguments
int main() {
    // code
    return 0;
}

// Form 2: With command-line arguments
int main(int argc, char *argv[]) {
    // code
    return 0;
}

// Form 3: Old style (avoid in modern code)
void main() {
    // code
}
```

**Best Practice:** Use `int main()` and always return 0 for success.

### Return Values from main()

```c
int main() {
    // return 0;     → Success (convention)
    // return 1;     → General error
    // return -1;    → Error
    // return 127;   → Command not found (UNIX)

    return 0;  // Program executed successfully
}
```

The return value is sent to the operating system. You can check it:

**Linux/macOS:**
```bash
./program
echo $?        # Prints the return value
```

**Windows (Command Prompt):**
```cmd
program.exe
echo %errorlevel%
```

## 3. Comments in C

Comments are ignored by the compiler but are crucial for code readability.

### Single-Line Comments (`//`)

```c
// This is a single-line comment
int age = 20;  // Variable to store age

// Comments can span the entire line
// or appear after code
```

### Multi-Line Comments (`/* */`)

```c
/*
 * This is a multi-line comment
 * Used for longer explanations
 * Author: Your Name
 * Date: 2026-01-14
 */

/* This can also be on a single line */

int result = /* inline comment */ 5 + 3;
```

### Good Commenting Practices

```c
#include <stdio.h>

/*
 * Program: Circle Calculator
 * Purpose: Calculate area and circumference of a circle
 * Author: CS Student
 * Date: 2026-01-14
 */

#define PI 3.14159

int main() {
    float radius, area, circumference;

    // Get radius from user
    printf("Enter radius: ");
    scanf("%f", &radius);

    // Calculate area: πr²
    area = PI * radius * radius;

    // Calculate circumference: 2πr
    circumference = 2 * PI * radius;

    // Display results
    printf("Area: %.2f\n", area);
    printf("Circumference: %.2f\n", circumference);

    return 0;  // Success
}
```

### When to Comment vs. When Not to

**DON'T Comment the Obvious:**
```c
// BAD: Obvious comments
int age = 20;  // Declare age variable and assign 20

// GOOD: Add value
int age = 20;  // Minimum voting age in the country
```

**DO Comment Complex Logic:**
```c
// Calculate compound interest: A = P(1 + r/n)^(nt)
amount = principal * pow((1 + rate/frequency), frequency * time);
```

## 4. Statements and Blocks

### Statements

A statement is a single instruction ending with a semicolon (`;`).

```c
int x = 10;              // Declaration + initialization
printf("Hello");         // Function call
x = x + 5;              // Assignment
return 0;               // Return statement
;                       // Null statement (does nothing)
```

### Blocks (Compound Statements)

Multiple statements grouped together with `{ }`.

```c
{
    int x = 10;
    int y = 20;
    int sum = x + y;
    printf("Sum = %d\n", sum);
}  // No semicolon after closing brace!
```

### Statement Types

```c
#include <stdio.h>

int main() {
    // 1. Expression Statement
    5 + 3;  // Valid but useless

    // 2. Declaration Statement
    int number = 42;

    // 3. Assignment Statement
    number = 100;

    // 4. Function Call Statement
    printf("Number: %d\n", number);

    // 5. Control Statement (covered later)
    if (number > 50) {
        printf("Large number\n");
    }

    // 6. Return Statement
    return 0;
}
```

## 5. The Compilation Process (Detailed)

Understanding how C code becomes an executable program is crucial!

```
┌──────────────────────────────────────────────────────────────┐
│                    COMPILATION PROCESS                       │
└──────────────────────────────────────────────────────────────┘

Step 1: SOURCE CODE (hello.c)
        ┌─────────────────────────────┐
        │ #include <stdio.h>          │
        │                             │
        │ int main() {                │
        │     printf("Hello");        │
        │     return 0;               │
        │ }                           │
        └─────────────────────────────┘
                    ↓
        ┌───────────────────────────┐
        │    PREPROCESSOR (cpp)     │
        │  - Handles #include       │
        │  - Handles #define        │
        │  - Removes comments       │
        └───────────────────────────┘
                    ↓
Step 2: EXPANDED SOURCE CODE (hello.i)
        ┌─────────────────────────────┐
        │ [Contents of stdio.h]       │
        │ ...                         │
        │ int main() {                │
        │     printf("Hello");        │
        │     return 0;               │
        │ }                           │
        └─────────────────────────────┘
                    ↓
        ┌───────────────────────────┐
        │      COMPILER (cc1)       │
        │  - Syntax checking        │
        │  - Semantic analysis      │
        │  - Generates assembly     │
        └───────────────────────────┘
                    ↓
Step 3: ASSEMBLY CODE (hello.s)
        ┌─────────────────────────────┐
        │ .section .text              │
        │ .global main                │
        │ main:                       │
        │     push   %rbp             │
        │     mov    %rsp,%rbp        │
        │     lea    0x0(%rip),%rdi   │
        │     call   printf           │
        │     ...                     │
        └─────────────────────────────┘
                    ↓
        ┌───────────────────────────┐
        │      ASSEMBLER (as)       │
        │  - Converts to machine    │
        │    code (binary)          │
        └───────────────────────────┘
                    ↓
Step 4: OBJECT CODE (hello.o)
        ┌─────────────────────────────┐
        │ 01010101 10001011 11101100  │
        │ 01001000 10000011 11101100  │
        │ 01001000 10001101 00111101  │
        │ ...                         │
        └─────────────────────────────┘
                    ↓
        ┌───────────────────────────┐
        │       LINKER (ld)         │
        │  - Links object files     │
        │  - Links libraries        │
        │  - Creates executable     │
        └───────────────────────────┘
                    ↓
Step 5: EXECUTABLE (hello.exe / hello)
        ┌─────────────────────────────┐
        │  Ready to run!              │
        │  $ ./hello                  │
        │  Hello                      │
        └─────────────────────────────┘
```

### Seeing Each Step in Action

You can manually execute each compilation step:

```bash
# Step 1: Preprocessing only
gcc -E hello.c -o hello.i

# Step 2: Compilation to assembly
gcc -S hello.c -o hello.s

# Step 3: Assembly to object code
gcc -c hello.c -o hello.o

# Step 4: Linking to create executable
gcc hello.o -o hello

# Or do everything in one command:
gcc hello.c -o hello
```

### Common Compilation Flags

```bash
# Enable all warnings
gcc -Wall hello.c -o hello

# Enable even more warnings
gcc -Wall -Wextra hello.c -o hello

# Optimize for speed
gcc -O2 hello.c -o hello

# Include debugging information
gcc -g hello.c -o hello

# Show all warnings and treat them as errors
gcc -Wall -Werror hello.c -o hello
```

## 6. Program Execution Flow

```
                START
                  │
                  ↓
        ┌─────────────────────┐
        │  Operating System   │
        │  loads program      │
        └─────────────────────┘
                  │
                  ↓
        ┌─────────────────────┐
        │  Preprocessor       │
        │  runs #directives   │
        └─────────────────────┘
                  │
                  ↓
        ┌─────────────────────┐
        │  Initialize global  │
        │  variables          │
        └─────────────────────┘
                  │
                  ↓
        ┌─────────────────────┐
        │  Enter main()       │◄─── ENTRY POINT
        └─────────────────────┘
                  │
                  ↓
        ┌─────────────────────┐
        │  Execute statements │
        │  line by line       │
        └─────────────────────┘
                  │
                  ↓
        ┌─────────────────────┐
        │  Reach return 0;    │
        └─────────────────────┘
                  │
                  ↓
        ┌─────────────────────┐
        │  Exit main()        │
        └─────────────────────┘
                  │
                  ↓
        ┌─────────────────────┐
        │  Return control to  │
        │  Operating System   │
        └─────────────────────┘
                  │
                  ↓
                 END
```

## 7. Code Structure Best Practices

### Example: Well-Structured Program

```c
/*
 * ============================================================================
 * Filename:    temperature_converter.c
 * Description: Converts temperature between Celsius and Fahrenheit
 * Author:      CS Student
 * Date:        2026-01-14
 * Version:     1.0
 * ============================================================================
 */

// ==================== PREPROCESSOR DIRECTIVES ====================
#include <stdio.h>
#include <stdlib.h>

// ==================== SYMBOLIC CONSTANTS ====================
#define FREEZING_POINT_C 0
#define BOILING_POINT_C 100
#define PROGRAM_SUCCESS 0
#define PROGRAM_ERROR 1

// ==================== FUNCTION PROTOTYPES ====================
void displayMenu();
float celsiusToFahrenheit(float celsius);
float fahrenheitToCelsius(float fahrenheit);

// ==================== MAIN FUNCTION ====================
int main() {
    int choice;
    float temperature, result;

    // Display program header
    printf("╔════════════════════════════════════╗\n");
    printf("║  Temperature Converter v1.0        ║\n");
    printf("╚════════════════════════════════════╝\n\n");

    // Get user choice
    displayMenu();
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    // Process based on choice
    if (choice == 1) {
        printf("Enter temperature in Celsius: ");
        scanf("%f", &temperature);
        result = celsiusToFahrenheit(temperature);
        printf("%.2f°C = %.2f°F\n", temperature, result);
    }
    else if (choice == 2) {
        printf("Enter temperature in Fahrenheit: ");
        scanf("%f", &temperature);
        result = fahrenheitToCelsius(temperature);
        printf("%.2f°F = %.2f°C\n", temperature, result);
    }
    else {
        printf("Invalid choice!\n");
        return PROGRAM_ERROR;
    }

    return PROGRAM_SUCCESS;
}

// ==================== FUNCTION DEFINITIONS ====================

/*
 * Function: displayMenu
 * Purpose:  Shows conversion options to user
 * Parameters: None
 * Returns:  void
 */
void displayMenu() {
    printf("1. Celsius to Fahrenheit\n");
    printf("2. Fahrenheit to Celsius\n");
}

/*
 * Function: celsiusToFahrenheit
 * Purpose:  Convert Celsius to Fahrenheit
 * Formula:  F = (C × 9/5) + 32
 * Parameters: celsius - temperature in Celsius
 * Returns:  temperature in Fahrenheit
 */
float celsiusToFahrenheit(float celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

/*
 * Function: fahrenheitToCelsius
 * Purpose:  Convert Fahrenheit to Celsius
 * Formula:  C = (F - 32) × 5/9
 * Parameters: fahrenheit - temperature in Fahrenheit
 * Returns:  temperature in Celsius
 */
float fahrenheitToCelsius(float fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}
```

### Naming Conventions

```c
// Variables and Functions: Use snake_case or camelCase
int student_age;        // snake_case (common in C)
int studentAge;         // camelCase (also acceptable)

// Constants and Macros: Use UPPER_CASE
#define MAX_SIZE 100
#define PI 3.14159

// Avoid:
int x;                  // Not descriptive
int a1, a2, a3;        // Unclear purpose
```

## 8. Indentation and Formatting

### K&R Style (Kernighan & Ritchie)
```c
int main() {
    if (condition) {
        statement1;
        statement2;
    } else {
        statement3;
    }
    return 0;
}
```

### Allman Style
```c
int main()
{
    if (condition)
    {
        statement1;
        statement2;
    }
    else
    {
        statement3;
    }
    return 0;
}
```

**Choose one style and be consistent!**

## Common Mistakes and How to Avoid Them

### Mistake 1: Missing Semicolons
```c
// WRONG ❌
int x = 10
printf("Value: %d", x)

// CORRECT ✅
int x = 10;
printf("Value: %d", x);
```

### Mistake 2: Mismatched Braces
```c
// WRONG ❌
int main() {
    if (x > 0) {
        printf("Positive");
    // Missing closing brace for if
    return 0;
}  // This closes main, not if!

// CORRECT ✅
int main() {
    if (x > 0) {
        printf("Positive");
    }
    return 0;
}
```

**Tip:** Use an editor with bracket matching!

### Mistake 3: Case Sensitivity
```c
// WRONG ❌
#include <STDIO.H>    // Should be lowercase
Int main() {          // Should be int
    Printf("Hi");     // Should be printf
}

// CORRECT ✅
#include <stdio.h>
int main() {
    printf("Hi");
}
```

### Mistake 4: Comments Inside Comments
```c
// WRONG ❌
/*
This is a comment
/* This is nested */ Won't work!
*/

// CORRECT ✅
/*
This is a comment
This is another line
No nesting needed
*/
```

### Mistake 5: Forgetting Return Type
```c
// WRONG ❌
main() {               // No return type
    printf("Hello");
}

// CORRECT ✅
int main() {           // int return type
    printf("Hello");
    return 0;
}
```

## Practice Exercises

### Exercise 1: Program Structure Analysis
Given this messy code, rewrite it with proper structure:

```c
#include <stdio.h>
int main(){int x=10;int y=20;printf("Sum: %d",x+y);return 0;}
```

Rewrite with:
- Proper indentation
- Comments
- Good spacing
- Clear variable names

### Exercise 2: Create a Header Comment
Write a complete header comment for a program that calculates the area of different shapes (circle, rectangle, triangle). Include author, date, description, and version.

### Exercise 3: Compilation Steps
Write down the four main steps of compilation and what happens in each step. Draw a diagram showing the flow.

### Exercise 4: Error Detective
Find and fix ALL errors in this program:

```c
#include <studio.h>

define PI 3.14

int main()
    float radius = 5.0
    float area = PI * radius * radius
    printf("Area: %f" area);
    return 0;
}
```

### Exercise 5: Build a Well-Structured Program
Create a program that:
- Has a proper header comment
- Uses at least 2 #define constants
- Has a descriptive function (not main)
- Calculates the average of three numbers
- Follows all best practices from this chapter

Example output:
```
╔═══════════════════════════════╗
║   Average Calculator v1.0     ║
╚═══════════════════════════════╝

Enter three numbers:
Number 1: 85
Number 2: 90
Number 3: 78

Average: 84.33
Grade: B
```

## Quick Reference Card

### Essential Structure
```c
#include <stdio.h>

int main() {
    // Your code
    return 0;
}
```

### Comments
```c
// Single line
/* Multi-line */
```

### Preprocessor
```c
#include <header.h>
#define CONSTANT value
```

### Compilation Command
```bash
gcc -Wall filename.c -o outputname
```

## Summary

In this chapter, you learned:

✓ The complete structure of a C program
✓ Preprocessor directives (#include, #define)
✓ The importance of the main() function
✓ How to write effective comments
✓ The 5-step compilation process
✓ Code organization and best practices
✓ Common syntax mistakes to avoid

**Next Chapter Preview:** Variables and Data Types - Learn how to store and manipulate different types of data in C!

---

**Remember:** Good code structure makes programs easier to read, maintain, and debug. Start with good habits now!
