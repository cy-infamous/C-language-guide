# Functions in C

## Table of Contents
1. [Introduction to Functions](#introduction-to-functions)
2. [Function Declaration and Definition](#function-declaration-and-definition)
3. [Function Parameters](#function-parameters)
4. [Return Values](#return-values)
5. [Recursion](#recursion)
6. [Scope and Storage Classes](#scope-and-storage-classes)
7. [Real-World Applications](#real-world-applications)
8. [Practice Exercises](#practice-exercises)

---

## Introduction to Functions

A function is a self-contained block of code that performs a specific task. Functions help you:
- **Organize code** into logical units
- **Reuse code** without repetition
- **Maintain code** more easily
- **Debug** more efficiently
- **Collaborate** better with team members

### Why Use Functions?

**Without Functions:**
```c
// Calculating area of three rectangles
int area1 = 5 * 10;
int area2 = 8 * 12;
int area3 = 6 * 9;
printf("Areas: %d, %d, %d\n", area1, area2, area3);
```

**With Functions:**
```c
int calculateArea(int length, int width) {
    return length * width;
}

int area1 = calculateArea(5, 10);
int area2 = calculateArea(8, 12);
int area3 = calculateArea(6, 9);
printf("Areas: %d, %d, %d\n", area1, area2, area3);
```

### Function Anatomy

```c
return_type function_name(parameter_list) {
    // Function body
    // Statements
    return value;  // Optional, depends on return_type
}
```

**Components:**
- **return_type**: Data type of value returned (int, float, void, etc.)
- **function_name**: Identifier for the function
- **parameter_list**: Input values (can be empty)
- **function body**: Code to be executed
- **return statement**: Sends value back to caller

---

## Function Declaration and Definition

### Function Declaration (Prototype)

A function declaration tells the compiler about the function's name, return type, and parameters. It's typically placed at the top of the program or in header files.

**Syntax:**
```c
return_type function_name(parameter_types);
```

### Function Definition

The actual implementation of the function with its complete body.

**Example: Complete Function Structure**
```c
#include <stdio.h>

// Function Declaration (Prototype)
int add(int a, int b);

int main() {
    int result = add(5, 3);
    printf("Sum: %d\n", result);
    return 0;
}

// Function Definition
int add(int a, int b) {
    int sum = a + b;
    return sum;
}
// Output: Sum: 8
```

### Why Declare Functions?

1. **Forward Reference**: Call functions before they're defined
2. **Code Organization**: Declarations in headers, definitions in source files
3. **Compiler Optimization**: Helps compiler check types and arguments

**Example: Function Call Flow**
```
Program Memory Layout:

+------------------+
|   main()         |
|   calls add()    |
+------------------+
        |
        v
+------------------+
|   add()          |
|   executes       |
|   returns result |
+------------------+
        |
        v
+------------------+
|   main()         |
|   receives value |
+------------------+
```

---

## Function Parameters

Parameters are values passed to functions. They allow functions to work with different data.

### Types of Parameters

#### 1. No Parameters
```c
#include <stdio.h>

void greet() {
    printf("Hello, World!\n");
}

int main() {
    greet();
    greet();
    return 0;
}
// Output: Hello, World!
//         Hello, World!
```

#### 2. Single Parameter
```c
#include <stdio.h>

void greetUser(char name[]) {
    printf("Hello, %s!\n", name);
}

int main() {
    greetUser("Alice");
    greetUser("Bob");
    return 0;
}
// Output: Hello, Alice!
//         Hello, Bob!
```

#### 3. Multiple Parameters
```c
#include <stdio.h>

int calculateVolume(int length, int width, int height) {
    return length * width * height;
}

int main() {
    int volume = calculateVolume(5, 4, 3);
    printf("Volume: %d cubic units\n", volume);
    return 0;
}
// Output: Volume: 60 cubic units
```

### Pass by Value

In C, arguments are passed by value by default, meaning a copy of the value is passed to the function.

**Example:**
```c
#include <stdio.h>

void modifyValue(int x) {
    x = x + 10;
    printf("Inside function: x = %d\n", x);
}

int main() {
    int num = 5;
    printf("Before function: num = %d\n", num);
    modifyValue(num);
    printf("After function: num = %d\n", num);
    return 0;
}
/* Output:
Before function: num = 5
Inside function: x = 15
After function: num = 5
*/
```

**Memory Diagram:**
```
main() memory:           modifyValue() memory:
+-------------+          +-------------+
| num = 5     |   -->    | x = 5       |
+-------------+          | (copy)      |
                         | x = 15      |
                         +-------------+

After function returns, x is destroyed.
num in main() remains unchanged.
```

### Pass by Reference (Using Pointers)

To modify original values, pass pointers to the function.

**Example:**
```c
#include <stdio.h>

void modifyValue(int *x) {
    *x = *x + 10;
    printf("Inside function: *x = %d\n", *x);
}

int main() {
    int num = 5;
    printf("Before function: num = %d\n", num);
    modifyValue(&num);  // Pass address
    printf("After function: num = %d\n", num);
    return 0;
}
/* Output:
Before function: num = 5
Inside function: *x = 15
After function: num = 15
*/
```

**Memory Diagram:**
```
main() memory:           modifyValue() memory:
+-------------+          +-------------+
| num = 5     |<---------|  x (pointer)|
| Address:100 |          |  value: 100 |
+-------------+          +-------------+
                               |
                         Modifies value at
                         address 100
                               |
                               v
+-------------+
| num = 15    |
| Address:100 |
+-------------+
```

---

## Return Values

Functions can return values to the caller using the `return` statement.

### Void Functions (No Return)
```c
#include <stdio.h>

void printDivider() {
    printf("========================\n");
}

int main() {
    printf("Section 1\n");
    printDivider();
    printf("Section 2\n");
    return 0;
}
/* Output:
Section 1
========================
Section 2
*/
```

### Functions Returning Values
```c
#include <stdio.h>

int square(int n) {
    return n * n;
}

float average(int a, int b) {
    return (a + b) / 2.0;
}

int main() {
    int result1 = square(5);
    float result2 = average(10, 20);

    printf("Square of 5: %d\n", result1);
    printf("Average of 10 and 20: %.2f\n", result2);

    return 0;
}
/* Output:
Square of 5: 25
Average of 10 and 20: 15.00
*/
```

### Multiple Return Points
```c
#include <stdio.h>

int findMax(int a, int b, int c) {
    if(a >= b && a >= c) {
        return a;
    }
    if(b >= a && b >= c) {
        return b;
    }
    return c;
}

int main() {
    int max = findMax(15, 23, 19);
    printf("Maximum value: %d\n", max);
    return 0;
}
// Output: Maximum value: 23
```

### Returning Multiple Values (Using Pointers)
```c
#include <stdio.h>

void findMinMax(int arr[], int size, int *min, int *max) {
    *min = arr[0];
    *max = arr[0];

    for(int i = 1; i < size; i++) {
        if(arr[i] < *min) {
            *min = arr[i];
        }
        if(arr[i] > *max) {
            *max = arr[i];
        }
    }
}

int main() {
    int numbers[] = {34, 12, 56, 23, 89, 45};
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

---

## Recursion

Recursion is a technique where a function calls itself to solve a problem by breaking it into smaller subproblems.

### Recursive Function Structure

**Basic Pattern:**
```c
return_type recursiveFunction(parameters) {
    // Base case - stops recursion
    if(base_condition) {
        return base_value;
    }

    // Recursive case - calls itself
    return recursiveFunction(modified_parameters);
}
```

### Call Stack Visualization

**Example: Factorial Calculation**
```c
#include <stdio.h>

int factorial(int n) {
    // Base case
    if(n == 0 || n == 1) {
        return 1;
    }
    // Recursive case
    return n * factorial(n - 1);
}

int main() {
    int num = 5;
    int result = factorial(num);
    printf("%d! = %d\n", num, result);
    return 0;
}
// Output: 5! = 120
```

**Call Stack Diagram:**
```
factorial(5) call stack:

Step 1: factorial(5)
    |
    v
   return 5 * factorial(4)

Step 2: factorial(4)
    |
    v
   return 4 * factorial(3)

Step 3: factorial(3)
    |
    v
   return 3 * factorial(2)

Step 4: factorial(2)
    |
    v
   return 2 * factorial(1)

Step 5: factorial(1)
    |
    v
   return 1  [BASE CASE]

Unwinding the stack:
factorial(1) = 1
factorial(2) = 2 * 1 = 2
factorial(3) = 3 * 2 = 6
factorial(4) = 4 * 6 = 24
factorial(5) = 5 * 24 = 120

Memory visualization:

Call Stack (grows downward):
+------------------+
| factorial(5)     |  Waiting for factorial(4)
+------------------+
| factorial(4)     |  Waiting for factorial(3)
+------------------+
| factorial(3)     |  Waiting for factorial(2)
+------------------+
| factorial(2)     |  Waiting for factorial(1)
+------------------+
| factorial(1)     |  Returns 1 (Base case)
+------------------+

Then stack unwinds as each function returns.
```

### Recursion Examples

#### 1. Fibonacci Series
```c
#include <stdio.h>

int fibonacci(int n) {
    // Base cases
    if(n == 0) return 0;
    if(n == 1) return 1;

    // Recursive case
    return fibonacci(n-1) + fibonacci(n-2);
}

int main() {
    int terms = 10;

    printf("Fibonacci series: ");
    for(int i = 0; i < terms; i++) {
        printf("%d ", fibonacci(i));
    }
    printf("\n");

    return 0;
}
// Output: Fibonacci series: 0 1 1 2 3 5 8 13 21 34
```

**Recursion Tree for fibonacci(4):**
```
                    fib(4)
                   /      \
                fib(3)    fib(2)
               /     \    /     \
           fib(2)  fib(1) fib(1) fib(0)
          /     \
      fib(1)  fib(0)

Result: 3
```

#### 2. Sum of Natural Numbers
```c
#include <stdio.h>

int sumN(int n) {
    if(n == 0) {
        return 0;
    }
    return n + sumN(n - 1);
}

int main() {
    int num = 10;
    printf("Sum of numbers 1 to %d: %d\n", num, sumN(num));
    return 0;
}
// Output: Sum of numbers 1 to 10: 55
```

#### 3. Power Function
```c
#include <stdio.h>

int power(int base, int exp) {
    // Base case
    if(exp == 0) {
        return 1;
    }
    // Recursive case
    return base * power(base, exp - 1);
}

int main() {
    int base = 2, exponent = 5;
    printf("%d^%d = %d\n", base, exponent, power(base, exponent));
    return 0;
}
// Output: 2^5 = 32
```

#### 4. Reverse a String
```c
#include <stdio.h>
#include <string.h>

void reverseString(char str[], int start, int end) {
    if(start >= end) {
        return;  // Base case
    }

    // Swap characters
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;

    // Recursive call
    reverseString(str, start + 1, end - 1);
}

int main() {
    char str[] = "Hello";
    int len = strlen(str);

    printf("Original: %s\n", str);
    reverseString(str, 0, len - 1);
    printf("Reversed: %s\n", str);

    return 0;
}
/* Output:
Original: Hello
Reversed: olleH
*/
```

### Recursion vs Iteration

| Aspect | Recursion | Iteration |
|--------|-----------|-----------|
| Approach | Function calls itself | Uses loops |
| Memory | Uses call stack | Uses less memory |
| Speed | Generally slower | Generally faster |
| Code | Often cleaner | Can be complex |
| Use case | Tree traversal, divide-and-conquer | Simple repetition |

---

## Scope and Storage Classes

### Variable Scope

#### 1. Local Variables
```c
#include <stdio.h>

void function1() {
    int x = 10;  // Local to function1
    printf("function1: x = %d\n", x);
}

void function2() {
    int x = 20;  // Different x, local to function2
    printf("function2: x = %d\n", x);
}

int main() {
    int x = 30;  // Local to main
    printf("main: x = %d\n", x);
    function1();
    function2();
    printf("main: x = %d\n", x);  // Still 30
    return 0;
}
/* Output:
main: x = 30
function1: x = 10
function2: x = 20
main: x = 30
*/
```

#### 2. Global Variables
```c
#include <stdio.h>

int globalVar = 100;  // Global variable

void modifyGlobal() {
    globalVar += 10;
    printf("Inside function: globalVar = %d\n", globalVar);
}

int main() {
    printf("Before: globalVar = %d\n", globalVar);
    modifyGlobal();
    printf("After: globalVar = %d\n", globalVar);
    return 0;
}
/* Output:
Before: globalVar = 100
Inside function: globalVar = 110
After: globalVar = 110
*/
```

#### 3. Static Variables
```c
#include <stdio.h>

void counter() {
    static int count = 0;  // Initialized only once
    count++;
    printf("Function called %d times\n", count);
}

int main() {
    counter();
    counter();
    counter();
    return 0;
}
/* Output:
Function called 1 times
Function called 2 times
Function called 3 times
*/
```

**Memory Diagram:**
```
Without static:               With static:
Call 1:                       Call 1:
+----------+                  +----------+
| count=0  |                  | count=0  |
| count=1  |                  | count=1  |
+----------+                  +----------+
(destroyed)                   (preserved)

Call 2:                       Call 2:
+----------+                  +----------+
| count=0  |                  | count=1  |
| count=1  |                  | count=2  |
+----------+                  +----------+
(destroyed)                   (preserved)
```

---

## Real-World Applications

### 1. Temperature Converter
```c
#include <stdio.h>

float celsiusToFahrenheit(float celsius) {
    return (celsius * 9.0 / 5.0) + 32;
}

float fahrenheitToCelsius(float fahrenheit) {
    return (fahrenheit - 32) * 5.0 / 9.0;
}

int main() {
    float temp;
    int choice;

    printf("Temperature Converter\n");
    printf("1. Celsius to Fahrenheit\n");
    printf("2. Fahrenheit to Celsius\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    printf("Enter temperature: ");
    scanf("%f", &temp);

    if(choice == 1) {
        printf("%.2f°C = %.2f°F\n", temp, celsiusToFahrenheit(temp));
    } else if(choice == 2) {
        printf("%.2f°F = %.2f°C\n", temp, fahrenheitToCelsius(temp));
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}
```

### 2. Prime Number Checker (Modular)
```c
#include <stdio.h>

int isPrime(int n) {
    if(n <= 1) return 0;
    if(n == 2) return 1;
    if(n % 2 == 0) return 0;

    for(int i = 3; i * i <= n; i += 2) {
        if(n % i == 0) {
            return 0;
        }
    }
    return 1;
}

void printPrimes(int start, int end) {
    printf("Prime numbers between %d and %d:\n", start, end);
    for(int i = start; i <= end; i++) {
        if(isPrime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int start = 10, end = 50;
    printPrimes(start, end);
    return 0;
}
// Output: Prime numbers between 10 and 50:
//         11 13 17 19 23 29 31 37 41 43 47
```

### 3. Array Utility Functions
```c
#include <stdio.h>

void printArray(int arr[], int size) {
    printf("[");
    for(int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if(i < size - 1) printf(", ");
    }
    printf("]\n");
}

int findSum(int arr[], int size) {
    int sum = 0;
    for(int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

float findAverage(int arr[], int size) {
    return (float)findSum(arr, size) / size;
}

void sortArray(int arr[], int size) {
    // Bubble sort
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int numbers[] = {64, 34, 25, 12, 22, 11, 90};
    int size = 7;

    printf("Original array: ");
    printArray(numbers, size);

    printf("Sum: %d\n", findSum(numbers, size));
    printf("Average: %.2f\n", findAverage(numbers, size));

    sortArray(numbers, size);
    printf("Sorted array: ");
    printArray(numbers, size);

    return 0;
}
/* Output:
Original array: [64, 34, 25, 12, 22, 11, 90]
Sum: 258
Average: 36.86
Sorted array: [11, 12, 22, 25, 34, 64, 90]
*/
```

### 4. Calculator with Functions
```c
#include <stdio.h>

float add(float a, float b) { return a + b; }
float subtract(float a, float b) { return a - b; }
float multiply(float a, float b) { return a * b; }
float divide(float a, float b) {
    if(b != 0) {
        return a / b;
    } else {
        printf("Error: Division by zero!\n");
        return 0;
    }
}

void displayMenu() {
    printf("\n=== CALCULATOR ===\n");
    printf("1. Add\n");
    printf("2. Subtract\n");
    printf("3. Multiply\n");
    printf("4. Divide\n");
    printf("5. Exit\n");
}

int main() {
    int choice;
    float num1, num2, result;

    do {
        displayMenu();
        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice >= 1 && choice <= 4) {
            printf("Enter first number: ");
            scanf("%f", &num1);
            printf("Enter second number: ");
            scanf("%f", &num2);

            switch(choice) {
                case 1:
                    result = add(num1, num2);
                    printf("%.2f + %.2f = %.2f\n", num1, num2, result);
                    break;
                case 2:
                    result = subtract(num1, num2);
                    printf("%.2f - %.2f = %.2f\n", num1, num2, result);
                    break;
                case 3:
                    result = multiply(num1, num2);
                    printf("%.2f * %.2f = %.2f\n", num1, num2, result);
                    break;
                case 4:
                    result = divide(num1, num2);
                    if(num2 != 0)
                        printf("%.2f / %.2f = %.2f\n", num1, num2, result);
                    break;
            }
        } else if(choice == 5) {
            printf("Thank you for using the calculator!\n");
        } else {
            printf("Invalid choice!\n");
        }
    } while(choice != 5);

    return 0;
}
```

### 5. GCD Using Recursion (Euclidean Algorithm)
```c
#include <stdio.h>

int gcd(int a, int b) {
    if(b == 0) {
        return a;  // Base case
    }
    return gcd(b, a % b);  // Recursive case
}

int main() {
    int num1 = 48, num2 = 18;
    printf("GCD of %d and %d: %d\n", num1, num2, gcd(num1, num2));
    return 0;
}
// Output: GCD of 48 and 18: 6
```

**Call Stack for gcd(48, 18):**
```
gcd(48, 18)  ->  gcd(18, 48%18)  ->  gcd(18, 12)
gcd(18, 12)  ->  gcd(12, 18%12)  ->  gcd(12, 6)
gcd(12, 6)   ->  gcd(6, 12%6)    ->  gcd(6, 0)
gcd(6, 0)    ->  return 6 (base case)
```

---

## Practice Exercises

### Basic Level

**Exercise 1:** Write a function `isEven(int n)` that returns 1 if the number is even and 0 if odd. Test it with multiple numbers.

**Exercise 2:** Create a function `circleArea(float radius)` that calculates and returns the area of a circle. Use the formula: Area = π × r².

**Exercise 3:** Write a function `printTable(int n)` that prints the multiplication table of n from 1 to 10.

### Intermediate Level

**Exercise 4:** Create a function `reverseArray(int arr[], int size)` that reverses the elements of an array in place (without creating a new array).

**Exercise 5:** Write a recursive function `sumOfDigits(int n)` that returns the sum of digits of a number. For example, sumOfDigits(123) should return 6.

**Exercise 6:** Implement a function `isPalindrome(int n)` that checks if a number is a palindrome (reads the same forwards and backwards). Example: 121 is a palindrome.

### Advanced Level

**Exercise 7:** Create a function `binarySearch(int arr[], int size, int target)` that implements binary search recursively. The function should return the index of the target element or -1 if not found.

**Hints:**
- Exercise 1: Use modulo operator (n % 2)
- Exercise 2: Use 3.14159 for π or include math.h for M_PI
- Exercise 3: Use a loop inside the function
- Exercise 4: Swap elements from both ends moving towards center
- Exercise 5: Base case: if n < 10, return n; Recursive: return (n%10) + sumOfDigits(n/10)
- Exercise 6: Reverse the number and compare with original
- Exercise 7: Find middle element, compare with target, recursively search left or right half

---

## Key Takeaways

1. **Functions** make code modular, reusable, and maintainable
2. **Declaration** (prototype) tells compiler about function before definition
3. **Parameters** can be passed by value (copy) or by reference (pointer)
4. **Return values** send results back to the caller
5. **Recursion** is powerful for divide-and-conquer problems but uses more memory
6. **Scope** determines where variables are accessible
7. **Static variables** retain their values between function calls

---

## Best Practices

1. **Use meaningful function names** that describe what they do
2. **Keep functions short** - one function, one task
3. **Minimize global variables** - prefer parameters
4. **Document functions** with comments explaining purpose and parameters
5. **Check for edge cases** - handle invalid inputs
6. **Avoid deep recursion** - can cause stack overflow
7. **Return early** when conditions are met to improve readability

---

**Next Topic:** [Arrays](03-arrays.md) - Master data collections and array operations!
