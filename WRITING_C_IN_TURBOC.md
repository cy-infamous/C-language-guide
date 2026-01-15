# Writing C Programs in Turbo C++
### A Complete Guide for Beginners

Step-by-step guide to writing, compiling, and running C programs in Turbo C++ IDE.

---

## Table of Contents
- [Getting Started](#getting-started)
- [Complete Workflow](#complete-workflow)
- [Program Structure](#program-structure)
- [Common C Programs in Turbo C++](#common-c-programs-in-turbo-c)
- [Working with Different Data Types](#working-with-different-data-types)
- [Control Structures](#control-structures)
- [Functions in Turbo C++](#functions-in-turbo-c)
- [Arrays and Strings](#arrays-and-strings)
- [File Operations](#file-operations)
- [Debugging Tips](#debugging-tips)
- [Best Practices](#best-practices)

---

## Getting Started

### Opening Turbo C++

1. **Double-click** the Turbo C++ icon on desktop
2. Or navigate to `C:\TURBOC\BIN\` and run `TC.EXE`
3. The blue IDE screen will appear

### IDE Navigation

- **Mouse**: Limited support in DOS mode
- **Keyboard**: Primary navigation method
- **Menu Bar**: Press `Alt` + letter (e.g., `Alt + F` for File)
- **Function Keys**: F1-F10 for quick actions

---

## Complete Workflow

### Step-by-Step Process to Create a C Program

```
1. Launch Turbo C++
   ↓
2. Create New File (Alt+F → New)
   ↓
3. Write Code
   ↓
4. Save File (F2)
   ↓
5. Compile (Alt+F9)
   ↓
6. Fix Errors (if any)
   ↓
7. Run Program (Ctrl+F9)
   ↓
8. View Output (Alt+F5)
```

### Example: Hello World - Complete Process

**Step 1: Open Turbo C++**
- Launch TC.EXE

**Step 2: Create New File**
- Press `Alt + F`
- Select `New`

**Step 3: Type the Code**
```c
#include <stdio.h>
#include <conio.h>

void main()
{
    clrscr();
    printf("Hello, World!\n");
    getch();
}
```

**Step 4: Save the File**
- Press `F2`
- Type: `hello.c`
- Press `Enter`

**Step 5: Compile**
- Press `Alt + F9`
- Wait for "Success" message

**Step 6: Run**
- Press `Ctrl + F9`
- Program executes

**Step 7: View Output**
- Press `Alt + F5`
- See "Hello, World!" on screen

---

## Program Structure

### Basic C Program Template for Turbo C++

```c
/*************************************************
 * Program Name: [Program name]
 * Description: [What this program does]
 * Author: [Your name]
 * Date: [Date]
 *************************************************/

// Include header files
#include <stdio.h>   // Standard input/output
#include <conio.h>   // Console I/O (Turbo C++ specific)

// Function declarations (if any)
void myFunction();

// Main function
void main()
{
    clrscr();  // Clear screen

    // Your code here

    getch();   // Wait for key press
}

// Function definitions
void myFunction()
{
    // Function code
}
```

### Essential Header Files

```c
#include <stdio.h>   // printf, scanf, FILE operations
#include <conio.h>   // clrscr, getch, gotoxy
#include <string.h>  // String functions: strlen, strcpy
#include <math.h>    // Mathematical functions: sqrt, pow
#include <stdlib.h>  // malloc, free, exit, system
#include <ctype.h>   // Character functions: toupper, isdigit
```

---

## Common C Programs in Turbo C++

### 1. Print Output

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    clrscr();

    printf("Hello, World!\n");
    printf("Welcome to C Programming\n");
    printf("Turbo C++ is easy!\n");

    getch();
}
```

### 2. Taking Input from User

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    int age;
    char name[50];

    clrscr();

    printf("Enter your name: ");
    scanf("%s", name);

    printf("Enter your age: ");
    scanf("%d", &age);

    printf("\nHello %s!\n", name);
    printf("You are %d years old.\n", age);

    getch();
}
```

### 3. Simple Arithmetic Operations

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    int a, b;
    int sum, diff, prod, quot, rem;

    clrscr();

    printf("Enter first number: ");
    scanf("%d", &a);

    printf("Enter second number: ");
    scanf("%d", &b);

    sum = a + b;
    diff = a - b;
    prod = a * b;
    quot = a / b;
    rem = a % b;

    printf("\n=== RESULTS ===\n");
    printf("Sum: %d\n", sum);
    printf("Difference: %d\n", diff);
    printf("Product: %d\n", prod);
    printf("Quotient: %d\n", quot);
    printf("Remainder: %d\n", rem);

    getch();
}
```

### 4. Area and Perimeter of Circle

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    float radius, area, perimeter;
    float pi = 3.14159;

    clrscr();

    printf("Enter radius of circle: ");
    scanf("%f", &radius);

    area = pi * radius * radius;
    perimeter = 2 * pi * radius;

    printf("\nRadius: %.2f\n", radius);
    printf("Area: %.2f\n", area);
    printf("Perimeter: %.2f\n", perimeter);

    getch();
}
```

### 5. Swap Two Numbers

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    int a, b, temp;

    clrscr();

    printf("Enter first number: ");
    scanf("%d", &a);

    printf("Enter second number: ");
    scanf("%d", &b);

    printf("\nBefore swapping:\n");
    printf("a = %d, b = %d\n", a, b);

    // Swapping logic
    temp = a;
    a = b;
    b = temp;

    printf("\nAfter swapping:\n");
    printf("a = %d, b = %d\n", a, b);

    getch();
}
```

---

## Working with Different Data Types

### Integer Programs

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    int num1 = 10;
    int num2 = 20;
    int result;

    clrscr();

    result = num1 + num2;
    printf("Integer Addition: %d + %d = %d\n", num1, num2, result);

    getch();
}
```

### Float Programs

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    float price = 99.99;
    float tax = 5.5;
    float total;

    clrscr();

    total = price + (price * tax / 100);

    printf("Price: %.2f\n", price);
    printf("Tax: %.2f%%\n", tax);
    printf("Total: %.2f\n", total);

    getch();
}
```

### Character Programs

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    char ch;

    clrscr();

    printf("Enter a character: ");
    ch = getchar();

    printf("\nYou entered: %c\n", ch);
    printf("ASCII value: %d\n", ch);

    getch();
}
```

---

## Control Structures

### If-Else Statement

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    int marks;

    clrscr();

    printf("Enter marks: ");
    scanf("%d", &marks);

    if (marks >= 60)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }

    getch();
}
```

### Nested If-Else (Grade System)

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    int marks;
    char grade;

    clrscr();

    printf("Enter marks (0-100): ");
    scanf("%d", &marks);

    if (marks >= 90)
        grade = 'A';
    else if (marks >= 80)
        grade = 'B';
    else if (marks >= 70)
        grade = 'C';
    else if (marks >= 60)
        grade = 'D';
    else
        grade = 'F';

    printf("\nMarks: %d\n", marks);
    printf("Grade: %c\n", grade);

    getch();
}
```

### Switch-Case Statement

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    int choice;

    clrscr();

    printf("=== MENU ===\n");
    printf("1. Tea\n");
    printf("2. Coffee\n");
    printf("3. Juice\n");
    printf("4. Water\n");
    printf("\nEnter choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            printf("\nYou ordered Tea\n");
            break;
        case 2:
            printf("\nYou ordered Coffee\n");
            break;
        case 3:
            printf("\nYou ordered Juice\n");
            break;
        case 4:
            printf("\nYou ordered Water\n");
            break;
        default:
            printf("\nInvalid choice!\n");
    }

    getch();
}
```

### For Loop

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    int i;

    clrscr();

    printf("Numbers from 1 to 10:\n");

    for(i = 1; i <= 10; i++)
    {
        printf("%d ", i);
    }

    printf("\n");
    getch();
}
```

### While Loop

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    int i = 1;

    clrscr();

    printf("Even numbers from 2 to 20:\n");

    while(i <= 10)
    {
        printf("%d ", i * 2);
        i++;
    }

    printf("\n");
    getch();
}
```

### Do-While Loop

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    int num, sum = 0;

    clrscr();

    do
    {
        printf("Enter number (0 to exit): ");
        scanf("%d", &num);
        sum = sum + num;
    }
    while(num != 0);

    printf("\nTotal sum: %d\n", sum);

    getch();
}
```

---

## Functions in Turbo C++

### Function Without Parameters

```c
#include <stdio.h>
#include <conio.h>

void greet()
{
    printf("Hello from function!\n");
}

void main()
{
    clrscr();

    greet();  // Function call

    getch();
}
```

### Function With Parameters

```c
#include <stdio.h>
#include <conio.h>

void printSum(int a, int b)
{
    int sum = a + b;
    printf("Sum: %d\n", sum);
}

void main()
{
    clrscr();

    printSum(5, 10);
    printSum(20, 30);

    getch();
}
```

### Function With Return Value

```c
#include <stdio.h>
#include <conio.h>

int add(int x, int y)
{
    return x + y;
}

void main()
{
    int result;

    clrscr();

    result = add(15, 25);
    printf("Result: %d\n", result);

    getch();
}
```

### Factorial Using Recursion

```c
#include <stdio.h>
#include <conio.h>

int factorial(int n)
{
    if(n == 0 || n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

void main()
{
    int num, fact;

    clrscr();

    printf("Enter number: ");
    scanf("%d", &num);

    fact = factorial(num);

    printf("Factorial of %d = %d\n", num, fact);

    getch();
}
```

---

## Arrays and Strings

### Array Input and Output

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    int arr[5];
    int i;

    clrscr();

    // Input
    printf("Enter 5 numbers:\n");
    for(i = 0; i < 5; i++)
    {
        printf("Element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    // Output
    printf("\nYou entered:\n");
    for(i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }

    getch();
}
```

### Find Maximum in Array

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    int arr[10];
    int i, n, max;

    clrscr();

    printf("How many numbers? ");
    scanf("%d", &n);

    printf("Enter %d numbers:\n", n);
    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    max = arr[0];
    for(i = 1; i < n; i++)
    {
        if(arr[i] > max)
            max = arr[i];
    }

    printf("\nMaximum: %d\n", max);

    getch();
}
```

### String Operations

```c
#include <stdio.h>
#include <conio.h>
#include <string.h>

void main()
{
    char str1[50], str2[50];
    int len;

    clrscr();

    printf("Enter first string: ");
    scanf("%s", str1);

    printf("Enter second string: ");
    scanf("%s", str2);

    // Length
    len = strlen(str1);
    printf("\nLength of first string: %d\n", len);

    // Copy
    strcpy(str2, str1);
    printf("After copy, str2: %s\n", str2);

    // Compare
    if(strcmp(str1, str2) == 0)
        printf("Strings are equal\n");
    else
        printf("Strings are not equal\n");

    getch();
}
```

---

## File Operations

### Writing to File

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    FILE *fp;
    char text[100];

    clrscr();

    fp = fopen("output.txt", "w");

    if(fp == NULL)
    {
        printf("Error opening file!\n");
        getch();
        return;
    }

    printf("Enter text: ");
    gets(text);

    fprintf(fp, "%s", text);

    fclose(fp);

    printf("\nFile written successfully!\n");

    getch();
}
```

### Reading from File

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    FILE *fp;
    char ch;

    clrscr();

    fp = fopen("output.txt", "r");

    if(fp == NULL)
    {
        printf("File not found!\n");
        getch();
        return;
    }

    printf("File contents:\n");
    while((ch = fgetc(fp)) != EOF)
    {
        printf("%c", ch);
    }

    fclose(fp);

    getch();
}
```

---

## Debugging Tips

### Common Errors and Solutions

**Error 1: Undefined symbol**
```
Error: Undefined symbol 'printf'
Solution: Add #include <stdio.h>
```

**Error 2: Statement missing semicolon**
```
Error: Statement missing ; in function main
Solution: Add semicolon at end of statement
```

**Error 3: Undefined symbol _main**
```
Error: Undefined symbol _main
Solution: Make sure you have main() function
```

### Using printf for Debugging

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    int x = 10, y = 20, z;

    clrscr();

    printf("Debug: x = %d, y = %d\n", x, y);  // Debug print

    z = x + y;

    printf("Debug: z = %d\n", z);  // Debug print

    printf("Result: %d\n", z);

    getch();
}
```

---

## Best Practices

### 1. Always Use clrscr() and getch()

```c
void main()
{
    clrscr();  // Start

    // Your code

    getch();   // End
}
```

### 2. Use Meaningful Variable Names

```c
// Bad
int a, b, c;

// Good
int length, width, area;
```

### 3. Add Comments

```c
// Calculate average of three numbers
float avg;
avg = (num1 + num2 + num3) / 3.0;  // Division by 3.0 for float result
```

### 4. Format Output Properly

```c
printf("%-10s: %d\n", "Name", value);  // Left-aligned
printf("%10d\n", number);               // Right-aligned
printf("%.2f\n", price);                // 2 decimal places
```

### 5. Validate Input

```c
int age;
printf("Enter age: ");
scanf("%d", &age);

if(age < 0 || age > 150)
{
    printf("Invalid age!\n");
    getch();
    return;
}
```

### 6. Use Functions for Reusable Code

```c
int square(int n)
{
    return n * n;
}

void main()
{
    printf("Square of 5: %d\n", square(5));
    printf("Square of 10: %d\n", square(10));
}
```

---

## Quick Reference Card

### Common Turbo C++ Operations

```c
// Clear screen
clrscr();

// Print
printf("Text");
printf("%d", number);

// Input
scanf("%d", &variable);

// Wait for key
getch();

// Position cursor
gotoxy(x, y);

// String length
len = strlen(str);

// String copy
strcpy(dest, src);

// String compare
if(strcmp(s1, s2) == 0)
```

---

## Practice Programs

### Program 1: Even or Odd

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    int num;

    clrscr();

    printf("Enter number: ");
    scanf("%d", &num);

    if(num % 2 == 0)
        printf("%d is Even\n", num);
    else
        printf("%d is Odd\n", num);

    getch();
}
```

### Program 2: Prime Number Check

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    int num, i, isPrime = 1;

    clrscr();

    printf("Enter number: ");
    scanf("%d", &num);

    if(num <= 1)
        isPrime = 0;

    for(i = 2; i <= num/2; i++)
    {
        if(num % i == 0)
        {
            isPrime = 0;
            break;
        }
    }

    if(isPrime)
        printf("%d is Prime\n", num);
    else
        printf("%d is not Prime\n", num);

    getch();
}
```

### Program 3: Fibonacci Series

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    int n, i, t1 = 0, t2 = 1, next;

    clrscr();

    printf("Enter number of terms: ");
    scanf("%d", &n);

    printf("Fibonacci Series:\n");
    printf("%d %d ", t1, t2);

    for(i = 3; i <= n; i++)
    {
        next = t1 + t2;
        printf("%d ", next);
        t1 = t2;
        t2 = next;
    }

    printf("\n");
    getch();
}
```

---

<div align="center">

## You're Now Ready to Write C Programs in Turbo C++!

**Practice these programs, experiment with the code, and build your skills!**

**[Back to Turbo C++ Setup →](TURBO_C_SETUP.md)**

**[Start Learning C →](01-Basics/01-introduction.md)**

</div>

---

**Remember:**
- Type programs yourself (don't copy-paste)
- Compile frequently (Alt+F9)
- Test with different inputs
- Practice daily for best results
