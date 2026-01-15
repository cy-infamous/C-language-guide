# Input and Output in C

## Introduction to I/O

Input/Output (I/O) operations allow your program to **interact with users**. Without I/O, programs would be static and unable to process user data.

```
┌─────────────────────────────────────────────┐
│           Input/Output Flow                 │
├─────────────────────────────────────────────┤
│                                             │
│  User Input  →  Program Processing  →  Output │
│     (scanf)        (calculations)     (printf)│
│                                             │
│  Example:                                   │
│  Enter radius: 5  →  area = π×r²  →  78.54 │
└─────────────────────────────────────────────┘
```

## Standard I/O Functions

C provides several functions for input and output, defined in `<stdio.h>`:

```
┌────────────┬─────────────────────────────────────┐
│ Function   │         Purpose                     │
├────────────┼─────────────────────────────────────┤
│ printf()   │ Formatted output to screen          │
│ scanf()    │ Formatted input from keyboard       │
│ getchar()  │ Read single character               │
│ putchar()  │ Write single character              │
│ gets()     │ Read string (DEPRECATED - unsafe)   │
│ puts()     │ Write string with newline           │
└────────────┴─────────────────────────────────────┘
```

## 1. The `printf()` Function

Used to **display output** to the console.

### Basic Syntax

```c
printf("format string", arguments);
```

### Simple Examples

```c
#include <stdio.h>

int main() {
    // Print plain text
    printf("Hello, World!\n");

    // Print multiple lines
    printf("Line 1\n");
    printf("Line 2\n");
    printf("Line 3\n");

    // Print with variables
    int age = 20;
    printf("Age: %d\n", age);

    // Print multiple variables
    int x = 10, y = 20;
    printf("x = %d, y = %d\n", x, y);

    return 0;
}
```

**Output:**
```
Hello, World!
Line 1
Line 2
Line 3
Age: 20
x = 10, y = 20
```

## Format Specifiers

Format specifiers are placeholders that tell `printf()` what type of data to display.

### Complete Format Specifier Table

```c
┌──────────┬─────────────────────┬──────────────────────────┐
│ Specifier│     Data Type       │        Example           │
├──────────┼─────────────────────┼──────────────────────────┤
│   %d     │ int (decimal)       │ printf("%d", 42)         │
│   %i     │ int (same as %d)    │ printf("%i", 42)         │
│   %u     │ unsigned int        │ printf("%u", 42U)        │
│   %f     │ float/double        │ printf("%f", 3.14)       │
│   %lf    │ double (in scanf)   │ scanf("%lf", &d)         │
│   %c     │ char                │ printf("%c", 'A')        │
│   %s     │ string              │ printf("%s", "Hello")    │
│   %p     │ pointer             │ printf("%p", &var)       │
│   %x     │ hexadecimal (lower) │ printf("%x", 255)        │
│   %X     │ hexadecimal (upper) │ printf("%X", 255)        │
│   %o     │ octal               │ printf("%o", 8)          │
│   %e     │ scientific (lower)  │ printf("%e", 1000.0)     │
│   %E     │ scientific (upper)  │ printf("%E", 1000.0)     │
│   %%     │ print % symbol      │ printf("100%%")          │
└──────────┴─────────────────────┴──────────────────────────┘
```

### Examples of Each Format Specifier

```c
#include <stdio.h>

int main() {
    int num = 42;
    float pi = 3.14159;
    char grade = 'A';
    char name[] = "Alice";

    printf("╔═══════════════════════════════════════╗\n");
    printf("║     Format Specifier Examples         ║\n");
    printf("╠═══════════════════════════════════════╣\n");

    // Integer formats
    printf("║ Decimal:      %d                     ║\n", num);
    printf("║ Unsigned:     %u                     ║\n", num);
    printf("║ Hexadecimal:  %x                     ║\n", num);
    printf("║ Octal:        %o                     ║\n", num);

    // Float formats
    printf("║ Float:        %f              ║\n", pi);
    printf("║ Scientific:   %e              ║\n", pi);

    // Character and string
    printf("║ Character:    %c                     ║\n", grade);
    printf("║ String:       %s                   ║\n", name);

    // Special
    printf("║ Percentage:   100%%                  ║\n");

    printf("╚═══════════════════════════════════════╝\n");

    return 0;
}
```

**Output:**
```
╔═══════════════════════════════════════╗
║     Format Specifier Examples         ║
╠═══════════════════════════════════════╣
║ Decimal:      42                      ║
║ Unsigned:     42                      ║
║ Hexadecimal:  2a                      ║
║ Octal:        52                      ║
║ Float:        3.141590                ║
║ Scientific:   3.141590e+00            ║
║ Character:    A                       ║
║ String:       Alice                   ║
║ Percentage:   100%                    ║
╚═══════════════════════════════════════╝
```

## Formatting Output with Width and Precision

### Width Specification

```c
#include <stdio.h>

int main() {
    int num = 42;

    printf("No width:       '%d'\n", num);
    printf("Width 5:        '%5d'\n", num);     // Right-aligned
    printf("Width 10:       '%10d'\n", num);
    printf("Left-aligned:   '%-10d'\n", num);   // Left-aligned with -
    printf("Zero-padded:    '%05d'\n", num);    // Pad with zeros

    return 0;
}
```

**Output:**
```
No width:       '42'
Width 5:        '   42'
Width 10:       '        42'
Left-aligned:   '42        '
Zero-padded:    '00042'
```

### Precision for Floating-Point Numbers

```c
#include <stdio.h>

int main() {
    double pi = 3.14159265358979;

    printf("Default:        %f\n", pi);        // 6 decimal places
    printf("1 decimal:      %.1f\n", pi);
    printf("2 decimals:     %.2f\n", pi);
    printf("5 decimals:     %.5f\n", pi);
    printf("10 decimals:    %.10f\n", pi);

    return 0;
}
```

**Output:**
```
Default:        3.141593
1 decimal:      3.1
2 decimals:     3.14
5 decimals:     3.14159
10 decimals:    3.1415926536
```

### Combining Width and Precision

```c
#include <stdio.h>

int main() {
    double price = 19.99;

    printf("Price: $%8.2f\n", price);   // Width 8, precision 2
    printf("Price: $%-8.2f\n", price);  // Left-aligned

    // Creating a table
    printf("\n╔════════════╦═══════════╗\n");
    printf("║  Item      ║   Price   ║\n");
    printf("╠════════════╬═══════════╣\n");
    printf("║ %-10s ║ $%8.2f ║\n", "Apple", 1.50);
    printf("║ %-10s ║ $%8.2f ║\n", "Banana", 0.75);
    printf("║ %-10s ║ $%8.2f ║\n", "Orange", 2.00);
    printf("╚════════════╩═══════════╝\n");

    return 0;
}
```

**Output:**
```
Price: $   19.99
Price: $19.99

╔════════════╦═══════════╗
║  Item      ║   Price   ║
╠════════════╬═══════════╣
║ Apple      ║ $    1.50 ║
║ Banana     ║ $    0.75 ║
║ Orange     ║ $    2.00 ║
╚════════════╩═══════════╝
```

## 2. The `scanf()` Function

Used to **read input** from the user.

### Basic Syntax

```c
scanf("format string", &variable);
```

**Important:** Notice the `&` (address-of operator) before the variable!

### Simple Input Examples

```c
#include <stdio.h>

int main() {
    int age;
    float height;
    char grade;

    // Read integer
    printf("Enter your age: ");
    scanf("%d", &age);
    printf("You are %d years old.\n\n", age);

    // Read float
    printf("Enter your height (in meters): ");
    scanf("%f", &height);
    printf("Your height is %.2f meters.\n\n", height);

    // Read character
    printf("Enter your grade: ");
    scanf(" %c", &grade);  // Note the space before %c
    printf("Your grade is %c.\n", grade);

    return 0;
}
```

**Sample Run:**
```
Enter your age: 20
You are 20 years old.

Enter your height (in meters): 1.75
Your height is 1.75 meters.

Enter your grade: A
Your grade is A.
```

### Reading Multiple Values

```c
#include <stdio.h>

int main() {
    int day, month, year;

    // Method 1: Separate scanf calls
    printf("Enter day: ");
    scanf("%d", &day);
    printf("Enter month: ");
    scanf("%d", &month);
    printf("Enter year: ");
    scanf("%d", &year);

    printf("Date: %02d/%02d/%d\n\n", day, month, year);

    // Method 2: Single scanf (user enters: 15 8 2026)
    printf("Enter date (DD MM YYYY): ");
    scanf("%d %d %d", &day, &month, &year);
    printf("Date: %02d/%02d/%d\n", day, month, year);

    return 0;
}
```

### Format Specifiers for `scanf()`

```c
┌──────────┬─────────────────────┬──────────────────────────┐
│ Specifier│     Data Type       │        Example           │
├──────────┼─────────────────────┼──────────────────────────┤
│   %d     │ int                 │ scanf("%d", &num)        │
│   %f     │ float               │ scanf("%f", &price)      │
│   %lf    │ double              │ scanf("%lf", &pi)        │
│   %c     │ char                │ scanf(" %c", &ch)        │
│   %s     │ string              │ scanf("%s", str)         │
│   %x     │ hexadecimal         │ scanf("%x", &hex)        │
│   %o     │ octal               │ scanf("%o", &oct)        │
└──────────┴─────────────────────┴──────────────────────────┘
```

### Complete Input/Output Example

```c
#include <stdio.h>

int main() {
    char name[50];
    int age;
    float gpa;
    char grade;

    printf("╔════════════════════════════════════╗\n");
    printf("║     Student Information Form       ║\n");
    printf("╚════════════════════════════════════╝\n\n");

    // Get student information
    printf("Enter your name: ");
    scanf("%s", name);  // No & for strings!

    printf("Enter your age: ");
    scanf("%d", &age);

    printf("Enter your GPA: ");
    scanf("%f", &gpa);

    printf("Enter your grade: ");
    scanf(" %c", &grade);  // Space before %c to skip whitespace

    // Display the information
    printf("\n╔════════════════════════════════════╗\n");
    printf("║        Student Profile             ║\n");
    printf("╠════════════════════════════════════╣\n");
    printf("║ Name:  %-28s║\n", name);
    printf("║ Age:   %-28d║\n", age);
    printf("║ GPA:   %-28.2f║\n", gpa);
    printf("║ Grade: %-28c║\n", grade);
    printf("╚════════════════════════════════════╝\n");

    return 0;
}
```

## 3. Character I/O: `getchar()` and `putchar()`

For reading and writing **single characters**.

### `getchar()` - Read a Character

```c
#include <stdio.h>

int main() {
    char ch;

    printf("Enter a character: ");
    ch = getchar();

    printf("You entered: ");
    putchar(ch);
    printf("\n");

    return 0;
}
```

### `putchar()` - Write a Character

```c
#include <stdio.h>

int main() {
    // Print alphabet
    printf("Alphabet: ");
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        putchar(ch);
        putchar(' ');
    }
    putchar('\n');

    return 0;
}
```

**Output:**
```
Alphabet: A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
```

### Reading Multiple Characters

```c
#include <stdio.h>

int main() {
    char ch;

    printf("Enter text (Ctrl+D or Ctrl+Z to end):\n");

    // Read until EOF (End of File)
    while ((ch = getchar()) != EOF) {
        // Convert lowercase to uppercase
        if (ch >= 'a' && ch <= 'z') {
            ch = ch - 32;  // ASCII conversion
        }
        putchar(ch);
    }

    return 0;
}
```

## 4. String I/O: `puts()` and `gets()`

### `puts()` - Write String with Newline

```c
#include <stdio.h>

int main() {
    puts("Hello, World!");          // Automatically adds \n
    puts("This is easier than printf!");

    // Equivalent to:
    // printf("Hello, World!\n");

    return 0;
}
```

### `gets()` - AVOID! (Unsafe)

```c
// DON'T USE THIS! ❌
char name[50];
gets(name);  // Dangerous: Can cause buffer overflow!

// INSTEAD, USE fgets() ✅
fgets(name, sizeof(name), stdin);
```

## Common scanf() Pitfalls and Solutions

### Problem 1: Buffer Not Cleared

```c
// PROBLEM: scanf leaves \n in buffer
int num;
char ch;

printf("Enter number: ");
scanf("%d", &num);        // User enters: 42<Enter>
                          // Buffer: <Enter> remains

printf("Enter character: ");
scanf("%c", &ch);         // Gets \n, not the character!

// SOLUTION: Add space before %c
scanf(" %c", &ch);        // Space skips whitespace
```

### Problem 2: Reading Strings with Spaces

```c
// PROBLEM: scanf stops at whitespace
char name[50];
scanf("%s", name);        // Input: "John Doe" → Only gets "John"

// SOLUTION: Use fgets()
fgets(name, sizeof(name), stdin);
```

### Problem 3: Multiple scanf() Issues

```c
#include <stdio.h>

int main() {
    int age;
    char name[50];

    // This works fine
    printf("Enter age: ");
    scanf("%d", &age);

    // This has a problem!
    printf("Enter name: ");
    scanf("%s", name);  // Gets leftover \n from previous scanf

    // SOLUTION: Clear buffer
    while (getchar() != '\n');  // Clear input buffer

    // OR use space before format specifier
    scanf(" %s", name);

    return 0;
}
```

## Escape Sequences Reference

```c
┌─────────┬──────────────────────────────────────┐
│ Sequence│           Description                │
├─────────┼──────────────────────────────────────┤
│   \n    │ Newline (move to next line)          │
│   \t    │ Horizontal tab                       │
│   \b    │ Backspace                            │
│   \r    │ Carriage return                      │
│   \\    │ Backslash                            │
│   \'    │ Single quote                         │
│   \"    │ Double quote                         │
│   \0    │ Null character (string terminator)   │
│   \a    │ Alert (beep sound)                   │
│   \v    │ Vertical tab                         │
│   \f    │ Form feed                            │
└─────────┴──────────────────────────────────────┘
```

### Escape Sequences in Action

```c
#include <stdio.h>

int main() {
    // Newline
    printf("Line 1\nLine 2\n");

    // Tab
    printf("Name:\tJohn\nAge:\t20\n");

    // Quotes
    printf("She said, \"Hello!\"\n");
    printf("It\'s a nice day\n");

    // Backslash
    printf("Path: C:\\Users\\Documents\\\n");

    // Alert (may not work in all environments)
    printf("\aBeep!\n");

    return 0;
}
```

**Output:**
```
Line 1
Line 2
Name:   John
Age:    20
She said, "Hello!"
It's a nice day
Path: C:\Users\Documents\
Beep!
```

## Practical Examples

### Example 1: Simple Calculator

```c
#include <stdio.h>

int main() {
    float num1, num2, result;
    char operator;

    printf("╔════════════════════════════════╗\n");
    printf("║    Simple Calculator           ║\n");
    printf("╚════════════════════════════════╝\n\n");

    printf("Enter first number: ");
    scanf("%f", &num1);

    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &operator);  // Space before %c

    printf("Enter second number: ");
    scanf("%f", &num2);

    printf("\nCalculation: %.2f %c %.2f = ", num1, operator, num2);

    switch(operator) {
        case '+':
            result = num1 + num2;
            printf("%.2f\n", result);
            break;
        case '-':
            result = num1 - num2;
            printf("%.2f\n", result);
            break;
        case '*':
            result = num1 * num2;
            printf("%.2f\n", result);
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
                printf("%.2f\n", result);
            } else {
                printf("Error! Division by zero.\n");
            }
            break;
        default:
            printf("Invalid operator!\n");
    }

    return 0;
}
```

### Example 2: Temperature Converter

```c
#include <stdio.h>

int main() {
    float celsius, fahrenheit, kelvin;
    int choice;

    printf("╔═══════════════════════════════════╗\n");
    printf("║   Temperature Converter           ║\n");
    printf("╠═══════════════════════════════════╣\n");
    printf("║ 1. Celsius to Fahrenheit          ║\n");
    printf("║ 2. Celsius to Kelvin              ║\n");
    printf("║ 3. Fahrenheit to Celsius          ║\n");
    printf("╚═══════════════════════════════════╝\n\n");

    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            printf("Enter temperature in Celsius: ");
            scanf("%f", &celsius);
            fahrenheit = (celsius * 9.0/5.0) + 32.0;
            printf("%.2f°C = %.2f°F\n", celsius, fahrenheit);
            break;

        case 2:
            printf("Enter temperature in Celsius: ");
            scanf("%f", &celsius);
            kelvin = celsius + 273.15;
            printf("%.2f°C = %.2fK\n", celsius, kelvin);
            break;

        case 3:
            printf("Enter temperature in Fahrenheit: ");
            scanf("%f", &fahrenheit);
            celsius = (fahrenheit - 32.0) * 5.0/9.0;
            printf("%.2f°F = %.2f°C\n", fahrenheit, celsius);
            break;

        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
```

### Example 3: Formatted Receipt

```c
#include <stdio.h>

int main() {
    char item1[30], item2[30], item3[30];
    float price1, price2, price3;
    int qty1, qty2, qty3;
    float total;

    printf("Enter details for 3 items:\n\n");

    printf("Item 1 name: ");
    scanf("%s", item1);
    printf("Price: $");
    scanf("%f", &price1);
    printf("Quantity: ");
    scanf("%d", &qty1);

    printf("\nItem 2 name: ");
    scanf("%s", item2);
    printf("Price: $");
    scanf("%f", &price2);
    printf("Quantity: ");
    scanf("%d", &qty2);

    printf("\nItem 3 name: ");
    scanf("%s", item3);
    printf("Price: $");
    scanf("%f", &price3);
    printf("Quantity: ");
    scanf("%d", &qty3);

    total = (price1 * qty1) + (price2 * qty2) + (price3 * qty3);

    // Print receipt
    printf("\n\n╔════════════════════════════════════════╗\n");
    printf("║            RECEIPT                     ║\n");
    printf("╠════════════════════════════════════════╣\n");
    printf("║ Item          Qty   Price    Total    ║\n");
    printf("╠════════════════════════════════════════╣\n");
    printf("║ %-12s  %2d   $%5.2f   $%6.2f  ║\n",
           item1, qty1, price1, price1 * qty1);
    printf("║ %-12s  %2d   $%5.2f   $%6.2f  ║\n",
           item2, qty2, price2, price2 * qty2);
    printf("║ %-12s  %2d   $%5.2f   $%6.2f  ║\n",
           item3, qty3, price3, price3 * qty3);
    printf("╠════════════════════════════════════════╣\n");
    printf("║                    TOTAL: $%9.2f ║\n", total);
    printf("╚════════════════════════════════════════╝\n");

    return 0;
}
```

## Common Mistakes and How to Avoid Them

### Mistake 1: Forgetting & in scanf()

```c
// WRONG ❌
int age;
scanf("%d", age);  // Missing &

// CORRECT ✅
scanf("%d", &age);
```

### Mistake 2: Using & with Strings in scanf()

```c
// WRONG ❌
char name[50];
scanf("%s", &name);  // Don't use & for strings!

// CORRECT ✅
scanf("%s", name);   // Array name is already an address
```

### Mistake 3: Wrong Format Specifier

```c
// WRONG ❌
float price = 19.99;
scanf("%d", &price);  // %d is for int, not float!

// CORRECT ✅
scanf("%f", &price);  // Use %f for float
```

### Mistake 4: Not Clearing Buffer

```c
// WRONG ❌
int num;
char ch;
scanf("%d", &num);
scanf("%c", &ch);  // Gets \n instead of character

// CORRECT ✅
scanf("%d", &num);
scanf(" %c", &ch);  // Space before %c skips whitespace
```

### Mistake 5: Buffer Overflow with String Input

```c
// DANGEROUS ❌
char name[10];
scanf("%s", name);  // User enters 50 characters → overflow!

// SAFER ✅
char name[10];
scanf("%9s", name);  // Limit to 9 chars (1 for \0)
```

## Practice Exercises

### Exercise 1: Personal Information

Create a program that:
- Asks for name, age, height, and weight
- Displays the information in a formatted card
- Uses appropriate format specifiers
- Handles spacing properly

### Exercise 2: Electricity Bill Calculator

Write a program that:
- Reads customer name and units consumed
- Calculates bill:
  - First 100 units: $0.50/unit
  - Next 100 units: $0.75/unit
  - Above 200 units: $1.20/unit
- Displays a formatted bill with all details

### Exercise 3: BMI Calculator

Create a BMI calculator that:
- Reads weight (kg) and height (m)
- Calculates BMI = weight / (height²)
- Displays result with interpretation:
  - < 18.5: Underweight
  - 18.5-24.9: Normal
  - 25-29.9: Overweight
  - >= 30: Obese

### Exercise 4: Character Analyzer

Write a program that:
- Reads a character using getchar()
- Displays its ASCII value
- Checks if it's:
  - Uppercase letter
  - Lowercase letter
  - Digit
  - Special character

### Exercise 5: Menu-Driven Program

Create a menu-driven program with options:
1. Add two numbers
2. Subtract two numbers
3. Multiply two numbers
4. Divide two numbers
5. Exit

Use proper formatting and error handling.

## Quick Reference Card

### Output Functions
```c
printf("format", args);     // Formatted output
puts("string");             // String with newline
putchar('c');               // Single character
```

### Input Functions
```c
scanf("format", &var);      // Formatted input
getchar();                  // Single character
fgets(str, size, stdin);    // String (safe)
```

### Common Format Specifiers
```c
%d  - int
%f  - float
%c  - char
%s  - string
%lf - double (scanf only)
```

### Formatting
```c
%5d     - Width 5
%-5d    - Left-align
%05d    - Zero-pad
%.2f    - 2 decimal places
%8.2f   - Width 8, precision 2
```

## Summary

In this chapter, you learned:

✓ How to use printf() for output with format specifiers
✓ How to use scanf() for input
✓ Width and precision formatting
✓ Character I/O with getchar() and putchar()
✓ String I/O with puts()
✓ Escape sequences for special characters
✓ Common pitfalls and how to avoid them
✓ Practical applications with formatted output

**Next Chapter Preview:** Control Structures - Learn how to make decisions and control program flow with if-else and switch statements!

---

**Pro Tip:** Always add a space before %c in scanf() to avoid reading leftover whitespace: `scanf(" %c", &ch);`
