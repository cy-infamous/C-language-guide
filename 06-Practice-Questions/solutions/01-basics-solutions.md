# Solutions - Basics Exercises

This file contains detailed solutions for all 20 basic exercises.

---

## Solution 1: Hello World

### Code
```c
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
```

### Explanation
- `#include <stdio.h>`: Includes standard input/output library
- `printf()`: Function to print formatted output
- `\n`: Newline character to move cursor to next line
- `return 0`: Indicates successful program execution

### Time Complexity
O(1) - Constant time

### Space Complexity
O(1) - Constant space

---

## Solution 2: Sum of Two Numbers

### Code
```c
#include <stdio.h>

int main() {
    int num1, num2, sum;

    // Input two numbers
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    // Calculate sum
    sum = num1 + num2;

    // Display result
    printf("Sum: %d\n", sum);

    return 0;
}
```

### Explanation
- `scanf()`: Reads formatted input from user
- `%d`: Format specifier for integers
- `&`: Address-of operator to pass variable address to scanf
- Addition operator (+) performs arithmetic addition

### Time Complexity
O(1)

### Space Complexity
O(1)

---

## Solution 3: Area of a Circle

### Code
```c
#include <stdio.h>
#define PI 3.14159

int main() {
    float radius, area;

    printf("Enter radius: ");
    scanf("%f", &radius);

    // Area = π × r²
    area = PI * radius * radius;

    printf("Area: %.5f\n", area);

    return 0;
}
```

### Explanation
- `#define PI 3.14159`: Defines a constant
- `float`: Data type for decimal numbers
- `%.5f`: Prints floating-point with 5 decimal places
- Formula: Area = π × r²

### Time Complexity
O(1)

### Space Complexity
O(1)

### Alternative Approach
Using `pow()` function from math.h:
```c
#include <math.h>
area = PI * pow(radius, 2);
```

---

## Solution 4: Temperature Converter

### Code
```c
#include <stdio.h>

int main() {
    float celsius, fahrenheit;

    printf("Enter temperature in Celsius: ");
    scanf("%f", &celsius);

    // Formula: F = (C × 9/5) + 32
    fahrenheit = (celsius * 9.0 / 5.0) + 32.0;

    printf("%.2f Celsius = %.2f Fahrenheit\n", celsius, fahrenheit);

    return 0;
}
```

### Explanation
- Use floating-point division (9.0/5.0) to avoid integer division
- Formula converts Celsius to Fahrenheit
- `%.2f`: Displays 2 decimal places

### Time Complexity
O(1)

### Space Complexity
O(1)

### Common Mistakes
- Using `9/5` instead of `9.0/5.0` results in integer division (= 1)
- This would give incorrect results

---

## Solution 5: Even or Odd

### Code
```c
#include <stdio.h>

int main() {
    int number;

    printf("Enter a number: ");
    scanf("%d", &number);

    if (number % 2 == 0) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }

    return 0;
}
```

### Explanation
- Modulus operator (%) gives remainder of division
- If number % 2 equals 0, the number is divisible by 2 (even)
- Otherwise, it's odd

### Time Complexity
O(1)

### Space Complexity
O(1)

### Alternative Approach
Using bitwise AND:
```c
if ((number & 1) == 0) {
    printf("Even\n");
} else {
    printf("Odd\n");
}
```
Checking the least significant bit: if 0, even; if 1, odd.

---

## Solution 6: Largest of Three Numbers

### Code
```c
#include <stdio.h>

int main() {
    int a, b, c, largest;

    printf("Enter three numbers: ");
    scanf("%d %d %d", &a, &b, &c);

    // Method 1: Using nested if-else
    if (a >= b && a >= c) {
        largest = a;
    } else if (b >= a && b >= c) {
        largest = b;
    } else {
        largest = c;
    }

    printf("Largest: %d\n", largest);

    return 0;
}
```

### Explanation
- Compare all three numbers using logical AND (&&)
- First condition checks if a is largest
- Second condition checks if b is largest
- If both false, c must be largest

### Time Complexity
O(1)

### Space Complexity
O(1)

### Alternative Approach
Using ternary operator:
```c
largest = (a >= b) ? ((a >= c) ? a : c) : ((b >= c) ? b : c);
```

---

## Solution 7: Grade Calculator

### Code
```c
#include <stdio.h>

int main() {
    int marks;
    char grade;

    printf("Enter marks (0-100): ");
    scanf("%d", &marks);

    // Validate input
    if (marks < 0 || marks > 100) {
        printf("Invalid marks!\n");
        return 1;
    }

    // Determine grade
    if (marks >= 90) {
        grade = 'A';
    } else if (marks >= 80) {
        grade = 'B';
    } else if (marks >= 70) {
        grade = 'C';
    } else if (marks >= 60) {
        grade = 'D';
    } else {
        grade = 'F';
    }

    printf("Grade: %c\n", grade);

    return 0;
}
```

### Explanation
- If-else ladder checks ranges from highest to lowest
- Once a condition is true, subsequent conditions are skipped
- Input validation prevents invalid marks
- `char` data type stores single character

### Time Complexity
O(1)

### Space Complexity
O(1)

---

## Solution 8: Leap Year Checker

### Code
```c
#include <stdio.h>

int main() {
    int year;

    printf("Enter a year: ");
    scanf("%d", &year);

    // Leap year conditions:
    // 1. Divisible by 4 AND not divisible by 100, OR
    // 2. Divisible by 400
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        printf("Leap Year\n");
    } else {
        printf("Not a Leap Year\n");
    }

    return 0;
}
```

### Explanation
- Leap year rules:
  - Divisible by 4: potential leap year
  - But if divisible by 100: not a leap year
  - Unless also divisible by 400: then it is a leap year
- Examples:
  - 2000: Divisible by 400 → Leap year
  - 1900: Divisible by 100 but not 400 → Not leap year
  - 2024: Divisible by 4 but not 100 → Leap year

### Time Complexity
O(1)

### Space Complexity
O(1)

---

## Solution 9: Simple Calculator

### Code
```c
#include <stdio.h>

int main() {
    float num1, num2, result;
    char operator;

    printf("Enter first number: ");
    scanf("%f", &num1);

    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &operator);  // Space before %c to consume whitespace

    printf("Enter second number: ");
    scanf("%f", &num2);

    switch (operator) {
        case '+':
            result = num1 + num2;
            printf("Result: %.2f\n", result);
            break;
        case '-':
            result = num1 - num2;
            printf("Result: %.2f\n", result);
            break;
        case '*':
            result = num1 * num2;
            printf("Result: %.2f\n", result);
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
                printf("Result: %.2f\n", result);
            } else {
                printf("Error: Division by zero!\n");
            }
            break;
        default:
            printf("Error: Invalid operator!\n");
    }

    return 0;
}
```

### Explanation
- Switch statement provides clean way to handle multiple cases
- Space before `%c` in scanf consumes any whitespace/newline
- Division by zero check prevents runtime error
- Default case handles invalid operators

### Time Complexity
O(1)

### Space Complexity
O(1)

---

## Solution 10: Print Numbers 1 to N

### Code
```c
#include <stdio.h>

int main() {
    int n;

    printf("Enter N: ");
    scanf("%d", &n);

    // Method 1: Using for loop
    printf("Using for loop:\n");
    for (int i = 1; i <= n; i++) {
        printf("%d\n", i);
    }

    // Method 2: Using while loop
    printf("\nUsing while loop:\n");
    int i = 1;
    while (i <= n) {
        printf("%d\n", i);
        i++;
    }

    return 0;
}
```

### Explanation
- For loop: initialization, condition, increment in one line
- While loop: more flexible, initialization and increment separate
- Both achieve same result

### Time Complexity
O(n)

### Space Complexity
O(1)

---

## Solution 11: Sum of First N Natural Numbers

### Code
```c
#include <stdio.h>

int main() {
    int n, sum;

    printf("Enter N: ");
    scanf("%d", &n);

    // Method 1: Using loop
    sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    printf("Sum (using loop): %d\n", sum);

    // Method 2: Using formula
    sum = n * (n + 1) / 2;
    printf("Sum (using formula): %d\n", sum);

    return 0;
}
```

### Explanation
- **Method 1**: Iterate and accumulate sum
  - Time: O(n), Space: O(1)
- **Method 2**: Direct formula: sum = n × (n + 1) / 2
  - Time: O(1), Space: O(1)
  - Much more efficient for large n

### Time Complexity
- Loop method: O(n)
- Formula method: O(1)

### Space Complexity
O(1) for both

---

## Solution 12: Factorial Calculator

### Code
```c
#include <stdio.h>

// Iterative approach
unsigned long long factorialIterative(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Recursive approach
unsigned long long factorialRecursive(int n) {
    if (n == 0 || n == 1) {
        return 1;  // Base case
    }
    return n * factorialRecursive(n - 1);  // Recursive case
}

int main() {
    int n;

    printf("Enter a number: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Factorial not defined for negative numbers!\n");
        return 1;
    }

    printf("Factorial (iterative): %llu\n", factorialIterative(n));
    printf("Factorial (recursive): %llu\n", factorialRecursive(n));

    return 0;
}
```

### Explanation
- **Iterative**: Uses loop to multiply numbers from 1 to n
- **Recursive**: Function calls itself with n-1 until base case (0 or 1)
- `unsigned long long`: Large data type to hold big factorials
- Base case prevents infinite recursion

### Time Complexity
O(n) for both methods

### Space Complexity
- Iterative: O(1)
- Recursive: O(n) due to recursion stack

---

## Solution 13: Multiplication Table

### Code
```c
#include <stdio.h>

int main() {
    int n;

    printf("Enter a number: ");
    scanf("%d", &n);

    printf("Multiplication table of %d:\n", n);
    for (int i = 1; i <= 10; i++) {
        printf("%d x %d = %d\n", n, i, n * i);
    }

    return 0;
}
```

### Explanation
- Loop from 1 to 10
- Multiply n by loop counter i
- Format output for readability

### Time Complexity
O(1) - Fixed 10 iterations

### Space Complexity
O(1)

---

## Solution 14: Count Digits

### Code
```c
#include <stdio.h>

int main() {
    int number, count = 0;

    printf("Enter a number: ");
    scanf("%d", &number);

    // Handle special case of 0
    if (number == 0) {
        count = 1;
    } else {
        // Handle negative numbers
        if (number < 0) {
            number = -number;
        }

        // Count digits
        while (number > 0) {
            count++;
            number /= 10;  // Remove last digit
        }
    }

    printf("Number of digits: %d\n", count);

    return 0;
}
```

### Explanation
- Repeatedly divide by 10 to remove last digit
- Count iterations until number becomes 0
- Special handling for 0 (has 1 digit)
- Convert negative to positive before counting

### Time Complexity
O(log₁₀ n) - Proportional to number of digits

### Space Complexity
O(1)

### Alternative Approach
Using string conversion:
```c
char str[20];
sprintf(str, "%d", number);
count = strlen(str);
if (number < 0) count--;  // Don't count minus sign
```

---

## Solution 15: Reverse a Number

### Code
```c
#include <stdio.h>

int main() {
    int number, reversed = 0, remainder;

    printf("Enter a number: ");
    scanf("%d", &number);

    int original = number;  // Store original for display

    while (number != 0) {
        remainder = number % 10;      // Extract last digit
        reversed = reversed * 10 + remainder;  // Add to reversed
        number /= 10;                 // Remove last digit
    }

    printf("Original: %d\n", original);
    printf("Reversed: %d\n", reversed);

    return 0;
}
```

### Explanation
- Extract last digit using modulus (%)
- Build reversed number by multiplying by 10 and adding digit
- Remove last digit using integer division (/)
- Example: 123 → 321
  - Step 1: reversed = 0 * 10 + 3 = 3, number = 12
  - Step 2: reversed = 3 * 10 + 2 = 32, number = 1
  - Step 3: reversed = 32 * 10 + 1 = 321, number = 0

### Time Complexity
O(log₁₀ n)

### Space Complexity
O(1)

---

## Solution 16: Sum of Digits

### Code
```c
#include <stdio.h>

int main() {
    int number, sum = 0, digit;

    printf("Enter a number: ");
    scanf("%d", &number);

    // Handle negative numbers
    if (number < 0) {
        number = -number;
    }

    while (number > 0) {
        digit = number % 10;  // Extract last digit
        sum += digit;         // Add to sum
        number /= 10;         // Remove last digit
    }

    printf("Sum of digits: %d\n", sum);

    return 0;
}
```

### Explanation
- Similar to reversing, but we accumulate sum instead
- Extract each digit, add to sum, remove digit
- Example: 123 → 1 + 2 + 3 = 6

### Time Complexity
O(log₁₀ n)

### Space Complexity
O(1)

---

## Solution 17: Prime Number Checker

### Code
```c
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool isPrime(int n) {
    // Handle special cases
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    // Check odd divisors up to √n
    int limit = sqrt(n);
    for (int i = 3; i <= limit; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    int number;

    printf("Enter a number: ");
    scanf("%d", &number);

    if (isPrime(number)) {
        printf("Prime\n");
    } else {
        printf("Not Prime\n");
    }

    return 0;
}
```

### Explanation
- Numbers ≤ 1 are not prime
- 2 is the only even prime
- Only check divisibility up to √n (if n = a × b, one of a or b must be ≤ √n)
- Skip even numbers after 2 (check only odd divisors)

### Time Complexity
O(√n)

### Space Complexity
O(1)

### Optimization
For checking many numbers, use Sieve of Eratosthenes: O(n log log n)

---

## Solution 18: Fibonacci Series

### Code
```c
#include <stdio.h>

void printFibonacci(int n) {
    int first = 0, second = 1, next;

    printf("%d ", first);
    if (n > 1) {
        printf("%d ", second);
    }

    for (int i = 3; i <= n; i++) {
        next = first + second;
        printf("%d ", next);
        first = second;
        second = next;
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter N: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Please enter a positive number!\n");
        return 1;
    }

    printf("First %d Fibonacci numbers:\n", n);
    printFibonacci(n);

    return 0;
}
```

### Explanation
- Initialize first two numbers (0, 1)
- Each subsequent number is sum of previous two
- Use three variables to track current and previous values
- Sequence: 0, 1, 1, 2, 3, 5, 8, 13, 21...

### Time Complexity
O(n)

### Space Complexity
O(1)

---

## Solution 19: Armstrong Number Checker

### Code
```c
#include <stdio.h>
#include <math.h>

int countDigits(int n) {
    int count = 0;
    while (n != 0) {
        count++;
        n /= 10;
    }
    return count;
}

bool isArmstrong(int n) {
    int original = n;
    int numDigits = countDigits(n);
    int sum = 0;

    while (n > 0) {
        int digit = n % 10;
        sum += pow(digit, numDigits);
        n /= 10;
    }

    return (sum == original);
}

int main() {
    int number;

    printf("Enter a number: ");
    scanf("%d", &number);

    if (isArmstrong(number)) {
        printf("Armstrong Number\n");
    } else {
        printf("Not an Armstrong Number\n");
    }

    return 0;
}
```

### Explanation
- Armstrong number: sum of digits raised to power of digit count equals original
- Examples:
  - 153 = 1³ + 5³ + 3³ = 1 + 125 + 27 = 153 ✓
  - 9474 = 9⁴ + 4⁴ + 7⁴ + 4⁴ = 6561 + 256 + 2401 + 256 = 9474 ✓
- Steps:
  1. Count digits
  2. Extract each digit
  3. Raise to power of digit count
  4. Sum all values
  5. Compare with original

### Time Complexity
O(d) where d is number of digits

### Space Complexity
O(1)

---

## Solution 20: Pattern Printing - Right Triangle

### Code
```c
#include <stdio.h>

void printRightTriangle(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            printf("*");
        }
        printf("\n");
    }
}

int main() {
    int n;

    printf("Enter number of rows: ");
    scanf("%d", &n);

    printRightTriangle(n);

    return 0;
}
```

### Explanation
- Outer loop: controls rows (1 to n)
- Inner loop: prints stars (1 to current row number)
- Each row has as many stars as its row number
- Result:
  ```
  *
  **
  ***
  ****
  *****
  ```

### Time Complexity
O(n²) - nested loops

### Space Complexity
O(1)

### Pattern Variations

**Inverted Right Triangle:**
```c
for (int i = n; i >= 1; i--) {
    for (int j = 1; j <= i; j++) {
        printf("*");
    }
    printf("\n");
}
```

**Pyramid:**
```c
for (int i = 1; i <= n; i++) {
    // Print spaces
    for (int j = 1; j <= n - i; j++) {
        printf(" ");
    }
    // Print stars
    for (int j = 1; j <= 2 * i - 1; j++) {
        printf("*");
    }
    printf("\n");
}
```

---

## Summary

These 20 basic problems cover:
- Input/Output operations
- Data types and variables
- Arithmetic and relational operators
- Conditional statements (if-else, switch)
- Loops (for, while)
- Basic algorithms (prime check, fibonacci, armstrong)
- Pattern printing

**Key Takeaways:**
1. Always validate input
2. Handle edge cases (0, negative numbers)
3. Use appropriate data types
4. Optimize where possible (e.g., formulas instead of loops)
5. Write readable, well-commented code

**Next Steps:**
- Practice variations of these problems
- Try solving without looking at solutions
- Optimize solutions for time and space
- Move on to intermediate exercises
