# Variables and Data Types

## What is a Variable?

A **variable** is a named storage location in memory that holds a value. Think of it as a labeled box where you can store different types of data.

```
┌─────────────────────────────────────────┐
│  Memory Representation                  │
├─────────────────────────────────────────┤
│                                         │
│  Variable Name: age                     │
│  Memory Address: 0x7fff5fbff7ac        │
│  Value: 20                              │
│  Type: int                              │
│                                         │
│  ┌──────────┐                           │
│  │    20    │  ← The actual value       │
│  └──────────┘                           │
│      age                                │
└─────────────────────────────────────────┘
```

### Why Do We Need Variables?

```c
// Without variables (BAD)
printf("Area: %d", 5 * 10);        // What do these numbers mean?
printf("Area: %d", 7 * 14);        // Have to repeat calculation

// With variables (GOOD)
int length = 5;
int width = 10;
int area = length * width;
printf("Area: %d", area);          // Clear and reusable!
```

## Variable Declaration and Initialization

### Declaration vs. Initialization

```c
// Declaration: Creates variable but no value assigned
int age;                    // Declared but uninitialized
float salary;               // Contains garbage value!

// Initialization: Assigns a value when declaring
int age = 20;              // Declared AND initialized
float salary = 50000.50;   // Good practice!

// Declaration then assignment
int marks;                 // Declare
marks = 95;               // Assign later
```

### Multiple Variable Declaration

```c
// Declare multiple variables of same type
int x, y, z;                        // Three integers

// Declare and initialize multiple variables
int a = 1, b = 2, c = 3;

// Mixed declaration and initialization
int num1 = 10, num2, num3 = 30;    // num2 is uninitialized!

// Best practice: One per line (more readable)
int length = 10;
int width = 5;
int height = 8;
```

### Naming Rules and Conventions

**Rules (Must Follow):**

✓ Must start with a letter (a-z, A-Z) or underscore (_)
✓ Can contain letters, digits (0-9), and underscores
✓ Cannot use C keywords (int, float, if, while, etc.)
✓ Case-sensitive (age ≠ Age ≠ AGE)

```c
// VALID variable names ✅
int age;
int _count;
int student1;
int total_marks;
int firstName;
int __temp;

// INVALID variable names ❌
int 1student;          // Cannot start with digit
int first-name;        // Hyphen not allowed
int first name;        // Space not allowed
int int;              // 'int' is a keyword
int @price;           // Special character not allowed
```

**Conventions (Best Practice):**

```c
// Use descriptive names
int student_age;           // Good
int sa;                    // Bad (unclear)

// Use snake_case or camelCase
int student_count;         // snake_case (common in C)
int studentCount;          // camelCase (also acceptable)

// Constants in UPPERCASE
const int MAX_SIZE = 100;
#define PI 3.14159
```

## Basic Data Types in C

C provides several built-in data types for storing different kinds of data.

```
┌─────────────────────────────────────────────────────┐
│              C DATA TYPES                           │
├─────────────────────────────────────────────────────┤
│                                                     │
│  PRIMARY TYPES                                      │
│  ├── int          (integers)                        │
│  ├── float        (floating-point)                  │
│  ├── double       (double precision float)          │
│  └── char         (characters)                      │
│                                                     │
│  DERIVED TYPES (Advanced)                           │
│  ├── Arrays                                         │
│  ├── Pointers                                       │
│  ├── Structures                                     │
│  └── Unions                                         │
│                                                     │
│  VOID TYPE                                          │
│  └── void         (no value)                        │
└─────────────────────────────────────────────────────┘
```

## 1. Integer Data Type (`int`)

Stores **whole numbers** (no decimal points).

### Basic Integer Operations

```c
#include <stdio.h>

int main() {
    int a = 10;
    int b = 3;

    printf("a = %d, b = %d\n", a, b);
    printf("Addition: %d + %d = %d\n", a, b, a + b);
    printf("Subtraction: %d - %d = %d\n", a, b, a - b);
    printf("Multiplication: %d × %d = %d\n", a, b, a * b);
    printf("Division: %d ÷ %d = %d\n", a, b, a / b);        // Integer division!
    printf("Modulus: %d %% %d = %d\n", a, b, a % b);        // Remainder

    return 0;
}
```

**Output:**
```
a = 10, b = 3
Addition: 10 + 3 = 13
Subtraction: 10 - 3 = 7
Multiplication: 10 × 3 = 30
Division: 10 ÷ 3 = 3       ← Note: Not 3.33 (integer division)
Modulus: 10 % 3 = 1        ← Remainder
```

### Integer Range

The range of an `int` depends on your system (typically 32-bit or 64-bit).

```c
#include <stdio.h>
#include <limits.h>    // Contains INT_MIN, INT_MAX

int main() {
    printf("Size of int: %zu bytes\n", sizeof(int));
    printf("Minimum int value: %d\n", INT_MIN);
    printf("Maximum int value: %d\n", INT_MAX);

    return 0;
}
```

**Typical Output (32-bit int):**
```
Size of int: 4 bytes
Minimum int value: -2147483648
Maximum int value: 2147483647
```

## 2. Floating-Point Data Type (`float`)

Stores **decimal numbers** (real numbers).

```c
#include <stdio.h>

int main() {
    float pi = 3.14159;
    float temperature = 98.6;
    float price = 19.99;

    printf("Value of pi: %f\n", pi);
    printf("Temperature: %.1f°F\n", temperature);    // 1 decimal place
    printf("Price: $%.2f\n", price);                 // 2 decimal places

    // Arithmetic with floats
    float a = 10.5;
    float b = 3.2;

    printf("\nFloat arithmetic:\n");
    printf("%.1f + %.1f = %.1f\n", a, b, a + b);
    printf("%.1f - %.1f = %.1f\n", a, b, a - b);
    printf("%.1f × %.1f = %.2f\n", a, b, a * b);
    printf("%.1f ÷ %.1f = %.2f\n", a, b, a / b);    // True division!

    return 0;
}
```

**Output:**
```
Value of pi: 3.141590
Temperature: 98.6°F
Price: $19.99

Float arithmetic:
10.5 + 3.2 = 13.7
10.5 - 3.2 = 7.3
10.5 × 3.2 = 33.60
10.5 ÷ 3.2 = 3.28
```

### Float Precision

```c
#include <stdio.h>
#include <float.h>     // Contains FLT_MIN, FLT_MAX

int main() {
    printf("Size of float: %zu bytes\n", sizeof(float));
    printf("Float precision: %d decimal digits\n", FLT_DIG);
    printf("Minimum float: %e\n", FLT_MIN);
    printf("Maximum float: %e\n", FLT_MAX);

    return 0;
}
```

**Typical Output:**
```
Size of float: 4 bytes
Float precision: 6 decimal digits
Minimum float: 1.175494e-38
Maximum float: 3.402823e+38
```

## 3. Double Precision (`double`)

Like `float` but with **double precision** (more accurate, more memory).

```c
#include <stdio.h>

int main() {
    float f = 3.14159265358979;
    double d = 3.14159265358979;

    printf("Float:  %.15f\n", f);     // Limited precision
    printf("Double: %.15lf\n", d);    // Better precision

    printf("\nSize comparison:\n");
    printf("float:  %zu bytes\n", sizeof(float));
    printf("double: %zu bytes\n", sizeof(double));

    return 0;
}
```

**Output:**
```
Float:  3.141592741012573      ← Lost precision after 6-7 digits
Double: 3.141592653589790      ← Accurate up to 15-16 digits

Size comparison:
float:  4 bytes
double: 8 bytes
```

**When to Use What?**

- **float**: When memory is limited, precision doesn't matter much (e.g., graphics, games)
- **double**: Scientific calculations, financial applications, default for most work

## 4. Character Data Type (`char`)

Stores **single characters** (letters, digits, symbols).

```c
#include <stdio.h>

int main() {
    char grade = 'A';
    char symbol = '@';
    char digit = '5';         // Note: '5' is different from 5
    char newline = '\n';

    printf("Grade: %c\n", grade);
    printf("Symbol: %c\n", symbol);
    printf("Digit character: %c\n", digit);

    // Characters are stored as ASCII values
    printf("\nASCII values:\n");
    printf("'A' = %d\n", 'A');
    printf("'a' = %d\n", 'a');
    printf("'0' = %d\n", '0');
    printf("'@' = %d\n", '@');

    return 0;
}
```

**Output:**
```
Grade: A
Symbol: @
Digit character: 5

ASCII values:
'A' = 65
'a' = 97
'0' = 48
'@' = 64
```

### ASCII Table (Essential Characters)

```
┌──────────┬───────┬────────────────────────────┐
│ Decimal  │ Char  │ Description                │
├──────────┼───────┼────────────────────────────┤
│   32     │ space │ Space character            │
│   48-57  │ 0-9   │ Digits                     │
│   65-90  │ A-Z   │ Uppercase letters          │
│   97-122 │ a-z   │ Lowercase letters          │
│   33     │  !    │ Exclamation                │
│   63     │  ?    │ Question mark              │
│   64     │  @    │ At symbol                  │
│   10     │  \n   │ Newline                    │
│   9      │  \t   │ Tab                        │
└──────────┴───────┴────────────────────────────┘
```

### Escape Sequences

Special characters represented with backslash `\`:

```c
#include <stdio.h>

int main() {
    printf("Line 1\nLine 2\n");           // \n = newline
    printf("Column1\tColumn2\n");         // \t = tab
    printf("She said, \"Hello!\"\n");     // \" = double quote
    printf("Path: C:\\Users\\Name\n");    // \\ = backslash
    printf("Single quote: \'\n");         // \' = single quote

    return 0;
}
```

**Output:**
```
Line 1
Line 2
Column1    Column2
She said, "Hello!"
Path: C:\Users\Name
Single quote: '
```

## Type Modifiers

Modifiers change the range/behavior of data types.

```
┌────────────┬──────────────────────────────────────┐
│  Modifier  │  Effect                              │
├────────────┼──────────────────────────────────────┤
│  signed    │  Can store positive & negative (default) │
│  unsigned  │  Only positive values (0 and above)  │
│  short     │  Smaller range, less memory          │
│  long      │  Larger range, more memory           │
└────────────┴──────────────────────────────────────┘
```

### Integer Modifiers

```c
#include <stdio.h>
#include <limits.h>

int main() {
    // Different integer types
    short int si = 32767;
    int i = 2147483647;
    long int li = 2147483647L;
    long long int lli = 9223372036854775807LL;

    unsigned int ui = 4294967295U;

    printf("Type            Size     Range\n");
    printf("─────────────────────────────────────────────────\n");
    printf("short int       %zu bytes  %d to %d\n",
           sizeof(short int), SHRT_MIN, SHRT_MAX);
    printf("int             %zu bytes  %d to %d\n",
           sizeof(int), INT_MIN, INT_MAX);
    printf("long int        %zu bytes  %ld to %ld\n",
           sizeof(long int), LONG_MIN, LONG_MAX);
    printf("unsigned int    %zu bytes  0 to %u\n",
           sizeof(unsigned int), UINT_MAX);

    return 0;
}
```

**Typical Output (64-bit system):**
```
Type            Size     Range
─────────────────────────────────────────────────
short int       2 bytes  -32768 to 32767
int             4 bytes  -2147483648 to 2147483647
long int        8 bytes  -9223372036854775808 to 9223372036854775807
unsigned int    4 bytes  0 to 4294967295
```

### When to Use Modifiers

```c
// Age is always positive → use unsigned
unsigned int age = 25;

// Need to store 5 billion → use long or long long
long long population = 8000000000LL;

// Small values (e.g., day of month) → use short
short day = 15;

// Default int is usually fine for most cases
int count = 100;
```

## The `sizeof` Operator

Returns the **size in bytes** of a data type or variable.

```c
#include <stdio.h>

int main() {
    int num = 100;
    float price = 99.99;
    char grade = 'A';
    double pi = 3.14159;

    printf("╔════════════════════════════════════╗\n");
    printf("║     Size of Data Types             ║\n");
    printf("╠════════════════════════════════════╣\n");

    // Size of types
    printf("║ sizeof(char)     = %zu byte(s)      ║\n", sizeof(char));
    printf("║ sizeof(int)      = %zu byte(s)      ║\n", sizeof(int));
    printf("║ sizeof(float)    = %zu byte(s)      ║\n", sizeof(float));
    printf("║ sizeof(double)   = %zu byte(s)      ║\n", sizeof(double));

    printf("╠════════════════════════════════════╣\n");

    // Size of variables
    printf("║ sizeof(num)      = %zu byte(s)      ║\n", sizeof(num));
    printf("║ sizeof(price)    = %zu byte(s)      ║\n", sizeof(price));
    printf("║ sizeof(grade)    = %zu byte(s)      ║\n", sizeof(grade));
    printf("║ sizeof(pi)       = %zu byte(s)      ║\n", sizeof(pi));

    printf("╚════════════════════════════════════╝\n");

    // Memory calculation
    int total_memory = sizeof(num) + sizeof(price) + sizeof(grade) + sizeof(pi);
    printf("\nTotal memory used: %d bytes\n", total_memory);

    return 0;
}
```

## Constants

Values that **cannot be changed** during program execution.

### Method 1: Using `const` Keyword

```c
#include <stdio.h>

int main() {
    const float PI = 3.14159;
    const int MAX_STUDENTS = 50;

    printf("Value of PI: %f\n", PI);

    // PI = 3.14;  // ERROR! Cannot modify a constant

    // Calculate circle area
    float radius = 5.0;
    float area = PI * radius * radius;
    printf("Area: %.2f\n", area);

    return 0;
}
```

### Method 2: Using `#define` Preprocessor

```c
#include <stdio.h>

#define PI 3.14159
#define MAX_SIZE 100
#define GREETING "Welcome!"

int main() {
    printf("%s\n", GREETING);
    printf("PI = %f\n", PI);
    printf("Max size: %d\n", MAX_SIZE);

    // No memory allocated for #define constants
    // Replaced by preprocessor before compilation

    return 0;
}
```

### `const` vs `#define`

```c
┌─────────────────┬──────────────────┬─────────────────┐
│   Feature       │      const       │     #define     │
├─────────────────┼──────────────────┼─────────────────┤
│ Type checking   │   Yes            │   No            │
│ Scope           │   Block/Function │   Global        │
│ Debugging       │   Easier         │   Harder        │
│ Memory          │   Uses memory    │   No memory     │
│ Pointer use     │   Can use        │   Cannot use    │
└─────────────────┴──────────────────┴─────────────────┘
```

**Best Practice:** Use `const` for type safety, use `#define` for macros.

## Type Casting (Type Conversion)

Converting one data type to another.

### Implicit Type Casting (Automatic)

```c
#include <stdio.h>

int main() {
    int a = 10;
    float b = 5.5;
    float result;

    result = a + b;  // int 'a' automatically converted to float
    printf("Result: %.1f\n", result);  // 15.5

    // Hierarchy: int → float → double
    int x = 5;
    float y = 2.5;
    double z = 1.5;

    double final = x + y + z;  // All converted to double
    printf("Final: %.1lf\n", final);  // 9.0

    return 0;
}
```

### Explicit Type Casting (Manual)

```c
#include <stdio.h>

int main() {
    float average = 85.7;

    // Truncate float to int
    int rounded = (int)average;
    printf("Average: %.1f → Rounded: %d\n", average, rounded);

    // Division examples
    int a = 7, b = 2;

    printf("\nInteger division:\n");
    printf("%d / %d = %d\n", a, b, a / b);        // 3 (integer division)

    printf("\nWith type casting:\n");
    printf("%d / %d = %.2f\n", a, b, (float)a / b);  // 3.50 (float division)

    // Character to integer
    char ch = 'A';
    printf("\nCharacter '%c' = %d (ASCII)\n", ch, (int)ch);

    return 0;
}
```

**Output:**
```
Average: 85.7 → Rounded: 85

Integer division:
7 / 2 = 3

With type casting:
7 / 2 = 3.50

Character 'A' = 65 (ASCII)
```

## Format Specifiers Reference

```c
┌───────────┬─────────────────────┬─────────────────────┐
│ Specifier │     Data Type       │      Example        │
├───────────┼─────────────────────┼─────────────────────┤
│   %d      │   int               │   printf("%d", 42)  │
│   %u      │   unsigned int      │   printf("%u", 42U) │
│   %f      │   float/double      │   printf("%f", 3.14)│
│   %lf     │   double (scanf)    │   scanf("%lf", &d)  │
│   %c      │   char              │   printf("%c", 'A') │
│   %s      │   string            │   printf("%s", "Hi")│
│   %p      │   pointer           │   printf("%p", &var)│
│   %x      │   hexadecimal       │   printf("%x", 255) │
│   %o      │   octal             │   printf("%o", 8)   │
│   %e      │   scientific        │   printf("%e", 1000)│
│   %.2f    │   2 decimal places  │   printf("%.2f", pi)│
│   %5d     │   min 5 chars wide  │   printf("%5d", 42) │
└───────────┴─────────────────────┴─────────────────────┘
```

## Common Mistakes and How to Avoid Them

### Mistake 1: Using Uninitialized Variables

```c
// WRONG ❌
int age;
printf("Age: %d\n", age);  // Garbage value!

// CORRECT ✅
int age = 0;               // Always initialize
printf("Age: %d\n", age);
```

### Mistake 2: Integer Division Surprise

```c
// WRONG ❌ (expecting 2.5)
int result = 5 / 2;
printf("%d\n", result);    // Prints 2, not 2.5

// CORRECT ✅
float result = 5.0 / 2.0;
printf("%.1f\n", result);  // Prints 2.5
```

### Mistake 3: Wrong Format Specifier

```c
// WRONG ❌
float price = 19.99;
printf("Price: %d\n", price);  // Wrong! Use %f

// CORRECT ✅
printf("Price: %.2f\n", price);
```

### Mistake 4: Character vs. String

```c
// WRONG ❌
char letter = "A";  // Error! "A" is a string, not a character

// CORRECT ✅
char letter = 'A';  // Single quotes for characters
```

### Mistake 5: Overflow

```c
// WRONG ❌
int big_num = 5000000000;  // Too big for 32-bit int!

// CORRECT ✅
long long big_num = 5000000000LL;
```

## Practice Exercises

### Exercise 1: Variable Declaration Practice

Write a program that declares variables for a student's information:
- Name (you'll use a char for first initial, we'll learn strings later)
- Age (integer)
- GPA (floating-point)
- Grade (character)

Print all information with appropriate labels.

### Exercise 2: Area and Perimeter Calculator

Create a program that:
- Declares variables for length and width of a rectangle
- Calculates area and perimeter
- Displays results with 2 decimal places
- Uses constants where appropriate

**Expected Output:**
```
Rectangle Calculator
─────────────────────
Length: 12.50 cm
Width: 8.30 cm

Area: 103.75 cm²
Perimeter: 41.60 cm
```

### Exercise 3: Temperature Converter

Write a program that:
- Declares a Celsius temperature
- Converts to Fahrenheit using: F = (C × 9/5) + 32
- Converts to Kelvin using: K = C + 273.15
- Displays all three values

### Exercise 4: Data Type Explorer

Create a program that uses `sizeof` to display:
- Size of all basic data types (char, int, float, double)
- Size with modifiers (short, long, long long)
- Size of signed vs unsigned
- Create a table showing all results

### Exercise 5: ASCII Arithmetic

Write a program that:
- Takes a lowercase letter (e.g., 'a')
- Converts it to uppercase by manipulating ASCII value
- Hint: 'a' - 'A' = 32
- Displays both the character and its ASCII value

**Example:**
```
Enter a lowercase letter: a
Lowercase: a (ASCII: 97)
Uppercase: A (ASCII: 65)
```

## Quick Reference Card

### Variable Declaration
```c
int age = 20;
float price = 99.99;
char grade = 'A';
double pi = 3.14159;
```

### Type Modifiers
```c
unsigned int count = 100;
short int small = 32000;
long int big = 1000000;
long long int huge = 9999999999LL;
```

### Constants
```c
const float PI = 3.14159;
#define MAX_SIZE 100
```

### sizeof Operator
```c
printf("Size: %zu bytes\n", sizeof(int));
```

### Type Casting
```c
float result = (float)a / b;
int truncated = (int)3.99;
```

## Summary

In this chapter, you learned:

✓ What variables are and how to declare them
✓ The four basic data types: int, float, double, char
✓ Type modifiers: signed, unsigned, short, long
✓ How to use the sizeof operator
✓ Constants using const and #define
✓ Type casting (implicit and explicit)
✓ Common mistakes and how to avoid them

**Next Chapter Preview:** Operators - Learn how to perform arithmetic, comparisons, and logical operations!

---

**Pro Tip:** Always initialize your variables! Uninitialized variables are a common source of bugs.
