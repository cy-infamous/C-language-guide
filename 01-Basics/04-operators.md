# Operators in C

## What are Operators?

**Operators** are special symbols that perform operations on variables and values (called **operands**).

```
   Operand    Operator    Operand
      ↓          ↓           ↓
      5          +           3       =    8
                            ↑
                         Result
```

C provides a rich set of operators for different purposes.

## Types of Operators in C

```
┌─────────────────────────────────────────────────────┐
│                 C OPERATORS                         │
├─────────────────────────────────────────────────────┤
│                                                     │
│  1. Arithmetic Operators     (+, -, *, /, %)        │
│  2. Relational Operators     (==, !=, <, >, <=, >=) │
│  3. Logical Operators        (&&, ||, !)            │
│  4. Assignment Operators     (=, +=, -=, *=, etc.)  │
│  5. Increment/Decrement      (++, --)               │
│  6. Bitwise Operators        (&, |, ^, ~, <<, >>)   │
│  7. Conditional Operator     (?:)                   │
│  8. Special Operators        (sizeof, &, *, etc.)   │
│                                                     │
└─────────────────────────────────────────────────────┘
```

## 1. Arithmetic Operators

Used to perform mathematical calculations.

### Basic Arithmetic Operators

```c
┌──────────┬─────────────────┬──────────────────────┐
│ Operator │   Description   │      Example         │
├──────────┼─────────────────┼──────────────────────┤
│    +     │   Addition      │   5 + 3 = 8          │
│    -     │   Subtraction   │   5 - 3 = 2          │
│    *     │   Multiplication│   5 * 3 = 15         │
│    /     │   Division      │   5 / 3 = 1 (int)    │
│    %     │   Modulus       │   5 % 3 = 2          │
└──────────┴─────────────────┴──────────────────────┘
```

### Complete Example

```c
#include <stdio.h>

int main() {
    int a = 10, b = 3;
    float x = 10.0, y = 3.0;

    printf("╔═══════════════════════════════════╗\n");
    printf("║    Arithmetic Operations          ║\n");
    printf("╠═══════════════════════════════════╣\n");

    // Integer arithmetic
    printf("║ INTEGER OPERATIONS (a=10, b=3)    ║\n");
    printf("║ ─────────────────────────────────║\n");
    printf("║ Addition:       %d + %d = %d      ║\n", a, b, a + b);
    printf("║ Subtraction:    %d - %d = %d      ║\n", a, b, a - b);
    printf("║ Multiplication: %d * %d = %d     ║\n", a, b, a * b);
    printf("║ Division:       %d / %d = %d      ║\n", a, b, a / b);
    printf("║ Modulus:        %d %% %d = %d      ║\n", a, b, a % b);

    printf("╠═══════════════════════════════════╣\n");

    // Float arithmetic
    printf("║ FLOAT OPERATIONS (x=10.0, y=3.0)  ║\n");
    printf("║ ─────────────────────────────────║\n");
    printf("║ Addition:       %.1f + %.1f = %.1f  ║\n", x, y, x + y);
    printf("║ Subtraction:    %.1f - %.1f = %.1f  ║\n", x, y, x - y);
    printf("║ Multiplication: %.1f * %.1f = %.1f ║\n", x, y, x * y);
    printf("║ Division:       %.1f / %.1f = %.2f ║\n", x, y, x / y);

    printf("╚═══════════════════════════════════╝\n");

    return 0;
}
```

**Output:**
```
╔═══════════════════════════════════╗
║    Arithmetic Operations          ║
╠═══════════════════════════════════╣
║ INTEGER OPERATIONS (a=10, b=3)    ║
║ ─────────────────────────────────║
║ Addition:       10 + 3 = 13       ║
║ Subtraction:    10 - 3 = 7        ║
║ Multiplication: 10 * 3 = 30       ║
║ Division:       10 / 3 = 3        ║  ← Integer division!
║ Modulus:        10 % 3 = 1        ║
╠═══════════════════════════════════╣
║ FLOAT OPERATIONS (x=10.0, y=3.0)  ║
║ ─────────────────────────────────║
║ Addition:       10.0 + 3.0 = 13.0 ║
║ Subtraction:    10.0 - 3.0 = 7.0  ║
║ Multiplication: 10.0 * 3.0 = 30.0 ║
║ Division:       10.0 / 3.0 = 3.33 ║  ← True division!
╚═══════════════════════════════════╝
```

### Understanding Modulus (%)

The modulus operator returns the **remainder** of division.

```c
#include <stdio.h>

int main() {
    printf("Modulus Examples:\n");
    printf("10 %% 3 = %d  (10 ÷ 3 = 3 remainder 1)\n", 10 % 3);
    printf("15 %% 4 = %d  (15 ÷ 4 = 3 remainder 3)\n", 15 % 4);
    printf("20 %% 5 = %d  (20 ÷ 5 = 4 remainder 0)\n", 20 % 5);

    // Practical use: Check if even or odd
    int number = 7;
    if (number % 2 == 0) {
        printf("%d is even\n", number);
    } else {
        printf("%d is odd\n", number);
    }

    return 0;
}
```

**Use Cases for Modulus:**
- Check if number is even/odd
- Get last digit of a number: `num % 10`
- Cycle through values: `(index % size)`
- Check divisibility

## 2. Relational (Comparison) Operators

Used to compare two values. Result is always **1 (true)** or **0 (false)**.

```c
┌──────────┬──────────────────┬──────────────────────┐
│ Operator │   Description    │      Example         │
├──────────┼──────────────────┼──────────────────────┤
│   ==     │   Equal to       │   5 == 5 → 1 (true)  │
│   !=     │   Not equal to   │   5 != 3 → 1 (true)  │
│   >      │   Greater than   │   5 > 3 → 1 (true)   │
│   <      │   Less than      │   5 < 3 → 0 (false)  │
│   >=     │   Greater or =   │   5 >= 5 → 1 (true)  │
│   <=     │   Less or equal  │   5 <= 3 → 0 (false) │
└──────────┴──────────────────┴──────────────────────┘
```

### Example Program

```c
#include <stdio.h>

int main() {
    int a = 10, b = 5, c = 10;

    printf("Given: a = %d, b = %d, c = %d\n\n", a, b, c);

    printf("Relational Operations:\n");
    printf("─────────────────────────────────────\n");
    printf("a == b  : %d (a equal to b?)\n", a == b);
    printf("a == c  : %d (a equal to c?)\n", a == c);
    printf("a != b  : %d (a not equal to b?)\n", a != b);
    printf("a > b   : %d (a greater than b?)\n", a > b);
    printf("a < b   : %d (a less than b?)\n", a < b);
    printf("a >= c  : %d (a greater than or equal to c?)\n", a >= c);
    printf("b <= a  : %d (b less than or equal to a?)\n", b <= a);

    return 0;
}
```

**Output:**
```
Given: a = 10, b = 5, c = 10

Relational Operations:
─────────────────────────────────────
a == b  : 0 (a equal to b?)
a == c  : 1 (a equal to c?)
a != b  : 1 (a not equal to b?)
a > b   : 1 (a greater than b?)
a < b   : 0 (a less than b?)
a >= c  : 1 (a greater than or equal to c?)
b <= a  : 1 (b less than or equal to a?)
```

### Common Mistake: `=` vs `==`

```c
// WRONG ❌
if (x = 5) {  // Assignment, not comparison!
    printf("This will always execute!\n");
}

// CORRECT ✅
if (x == 5) {  // Comparison
    printf("x is equal to 5\n");
}
```

## 3. Logical Operators

Used to combine multiple conditions.

```c
┌──────────┬─────────────────┬────────────────────────┐
│ Operator │   Description   │        Example         │
├──────────┼─────────────────┼────────────────────────┤
│   &&     │   Logical AND   │   (5>3) && (8>5) → 1   │
│   ||     │   Logical OR    │   (5>3) || (8<5) → 1   │
│   !      │   Logical NOT   │   !(5>3) → 0           │
└──────────┴─────────────────┴────────────────────────┘
```

### Truth Tables

**AND (&&) Truth Table:**
```
┌───────┬───────┬──────────┐
│   A   │   B   │  A && B  │
├───────┼───────┼──────────┤
│   0   │   0   │    0     │
│   0   │   1   │    0     │
│   1   │   0   │    0     │
│   1   │   1   │    1     │ ← Both must be true
└───────┴───────┴──────────┘
```

**OR (||) Truth Table:**
```
┌───────┬───────┬──────────┐
│   A   │   B   │  A || B  │
├───────┼───────┼──────────┤
│   0   │   0   │    0     │
│   0   │   1   │    1     │ ← At least one true
│   1   │   0   │    1     │ ← At least one true
│   1   │   1   │    1     │ ← At least one true
└───────┴───────┴──────────┘
```

**NOT (!) Truth Table:**
```
┌───────┬────────┐
│   A   │   !A   │
├───────┼────────┤
│   0   │   1    │ ← Inverts
│   1   │   0    │ ← Inverts
└───────┴────────┘
```

### Practical Example

```c
#include <stdio.h>

int main() {
    int age = 20;
    int has_license = 1;  // 1 = true, 0 = false
    int has_car = 0;

    printf("Eligibility Checker\n");
    printf("═══════════════════\n");
    printf("Age: %d\n", age);
    printf("Has license: %s\n", has_license ? "Yes" : "No");
    printf("Has car: %s\n\n", has_car ? "Yes" : "No");

    // AND: Both conditions must be true
    if (age >= 18 && has_license) {
        printf("✓ Can drive legally\n");
    }

    // OR: At least one condition must be true
    if (age >= 18 || has_license) {
        printf("✓ Eligible for driving course\n");
    }

    // NOT: Inverts the condition
    if (!has_car) {
        printf("✗ Needs to buy/rent a car\n");
    }

    // Complex condition
    if (age >= 18 && has_license && has_car) {
        printf("✓ Can drive own car\n");
    } else {
        printf("✗ Cannot drive own car yet\n");
    }

    return 0;
}
```

**Output:**
```
Eligibility Checker
═══════════════════
Age: 20
Has license: Yes
Has car: No

✓ Can drive legally
✓ Eligible for driving course
✗ Needs to buy/rent a car
✗ Cannot drive own car yet
```

### Short-Circuit Evaluation

C uses **short-circuit evaluation** for efficiency:

```c
// AND: If first is false, second isn't evaluated
if (x != 0 && y / x > 2) {  // Safe: won't divide by zero
    printf("Condition met\n");
}

// OR: If first is true, second isn't evaluated
if (x == 0 || y / x > 2) {  // Safe: won't divide by zero
    printf("Condition met\n");
}
```

## 4. Assignment Operators

Used to assign values to variables.

```c
┌───────────┬─────────────────────┬────────────────────┐
│ Operator  │    Description      │     Example        │
├───────────┼─────────────────────┼────────────────────┤
│    =      │  Simple assign      │  x = 5             │
│    +=     │  Add and assign     │  x += 3  (x = x+3) │
│    -=     │  Subtract & assign  │  x -= 3  (x = x-3) │
│    *=     │  Multiply & assign  │  x *= 3  (x = x*3) │
│    /=     │  Divide and assign  │  x /= 3  (x = x/3) │
│    %=     │  Modulus & assign   │  x %= 3  (x = x%3) │
└───────────┴─────────────────────┴────────────────────┘
```

### Example Program

```c
#include <stdio.h>

int main() {
    int x = 10;

    printf("Initial value: x = %d\n\n", x);

    x += 5;  // x = x + 5
    printf("After x += 5:  x = %d\n", x);  // 15

    x -= 3;  // x = x - 3
    printf("After x -= 3:  x = %d\n", x);  // 12

    x *= 2;  // x = x * 2
    printf("After x *= 2:  x = %d\n", x);  // 24

    x /= 4;  // x = x / 4
    printf("After x /= 4:  x = %d\n", x);  // 6

    x %= 4;  // x = x % 4
    printf("After x %%= 4:  x = %d\n", x);  // 2

    return 0;
}
```

**Output:**
```
Initial value: x = 10

After x += 5:  x = 15
After x -= 3:  x = 12
After x *= 2:  x = 24
After x /= 4:  x = 6
After x %= 4:  x = 2
```

### Why Use Compound Assignment?

```c
// Both do the same thing, but compound is shorter
score = score + 10;    // Longer
score += 10;           // Shorter, cleaner

// More examples
count = count + 1;     vs.    count += 1;
total = total * 2;     vs.    total *= 2;
price = price - 5;     vs.    price -= 5;
```

## 5. Increment and Decrement Operators

Shorthand for adding or subtracting 1.

```c
┌───────────┬─────────────────────┬────────────────────┐
│ Operator  │    Description      │     Example        │
├───────────┼─────────────────────┼────────────────────┤
│    ++     │  Increment by 1     │  x++ or ++x        │
│    --     │  Decrement by 1     │  x-- or --x        │
└───────────┴─────────────────────┴────────────────────┘
```

### Pre-increment vs Post-increment

This is where it gets interesting!

```c
#include <stdio.h>

int main() {
    int x, y, result;

    // POST-INCREMENT (x++)
    printf("POST-INCREMENT (x++):\n");
    x = 5;
    result = x++;  // Use current value, THEN increment
    printf("x = 5, result = x++\n");
    printf("result = %d (used old value)\n", result);  // 5
    printf("x = %d (incremented after)\n\n", x);       // 6

    // PRE-INCREMENT (++x)
    printf("PRE-INCREMENT (++x):\n");
    x = 5;
    result = ++x;  // Increment FIRST, THEN use value
    printf("x = 5, result = ++x\n");
    printf("result = %d (used new value)\n", result);  // 6
    printf("x = %d (incremented before)\n\n", x);      // 6

    // POST-DECREMENT (x--)
    printf("POST-DECREMENT (x--):\n");
    x = 5;
    result = x--;
    printf("x = 5, result = x--\n");
    printf("result = %d, x = %d\n\n", result, x);      // 5, 4

    // PRE-DECREMENT (--x)
    printf("PRE-DECREMENT (--x):\n");
    x = 5;
    result = --x;
    printf("x = 5, result = --x\n");
    printf("result = %d, x = %d\n", result, x);        // 4, 4

    return 0;
}
```

**Output:**
```
POST-INCREMENT (x++):
x = 5, result = x++
result = 5 (used old value)
x = 6 (incremented after)

PRE-INCREMENT (++x):
x = 5, result = ++x
result = 6 (used new value)
x = 6 (incremented before)

POST-DECREMENT (x--):
x = 5, result = x--
result = 5, x = 4

PRE-DECREMENT (--x):
x = 5, result = --x
result = 4, x = 4
```

### Visual Representation

```
POST-INCREMENT (x++)          PRE-INCREMENT (++x)
─────────────────────        ─────────────────────
  x = 5                        x = 5
    ↓                            ↓
  Use value (5)                Increment first
    ↓                            ↓
  Then increment               x = 6
    ↓                            ↓
  x = 6                        Use value (6)
```

### When to Use Which?

```c
// If used alone, no difference
x++;    // Same result
++x;    // Same result

// In assignments or expressions, big difference!
result = x++;   // result gets old value
result = ++x;   // result gets new value

// Common use: Loops (usually no difference here)
for (int i = 0; i < 10; i++) {  // i++ is standard
    printf("%d ", i);
}
```

## 6. Bitwise Operators

Operate on bits (binary digits). Advanced topic but important!

```c
┌──────────┬─────────────────┬──────────────────────┐
│ Operator │   Description   │      Example         │
├──────────┼─────────────────┼──────────────────────┤
│    &     │   Bitwise AND   │   5 & 3 = 1          │
│    |     │   Bitwise OR    │   5 | 3 = 7          │
│    ^     │   Bitwise XOR   │   5 ^ 3 = 6          │
│    ~     │   Bitwise NOT   │   ~5 = -6            │
│    <<    │   Left shift    │   5 << 1 = 10        │
│    >>    │   Right shift   │   5 >> 1 = 2         │
└──────────┴─────────────────┴──────────────────────┘
```

### Bitwise AND (&)

```c
#include <stdio.h>

int main() {
    int a = 5;   // Binary: 0101
    int b = 3;   // Binary: 0011

    printf("Bitwise AND:\n");
    printf("a = %d (binary: 0101)\n", a);
    printf("b = %d (binary: 0011)\n", b);
    printf("a & b = %d\n\n", a & b);  // 0001 = 1

    /*
       0101  (5)
     & 0011  (3)
     ───────
       0001  (1)
    */

    return 0;
}
```

### Bitwise OR (|)

```c
int a = 5;   // Binary: 0101
int b = 3;   // Binary: 0011

printf("a | b = %d\n", a | b);  // 0111 = 7

/*
   0101  (5)
 | 0011  (3)
 ───────
   0111  (7)
*/
```

### Bitwise XOR (^)

```c
int a = 5;   // Binary: 0101
int b = 3;   // Binary: 0011

printf("a ^ b = %d\n", a ^ b);  // 0110 = 6

/*
   0101  (5)
 ^ 0011  (3)
 ───────
   0110  (6)
*/
```

### Bitwise Truth Tables

```
AND (&)         OR (|)          XOR (^)         NOT (~)
───────         ──────          ───────         ───────
0 & 0 = 0       0 | 0 = 0       0 ^ 0 = 0       ~0 = 1
0 & 1 = 0       0 | 1 = 1       0 ^ 1 = 1       ~1 = 0
1 & 0 = 0       1 | 0 = 1       1 ^ 0 = 1
1 & 1 = 1       1 | 1 = 1       1 ^ 1 = 0
```

### Bit Shift Operators

```c
#include <stdio.h>

int main() {
    int x = 5;  // Binary: 0101

    printf("Original: x = %d (binary: 0101)\n\n", x);

    // Left shift: multiply by 2
    printf("x << 1 = %d  (0101 → 1010)\n", x << 1);  // 10
    printf("x << 2 = %d  (0101 → 10100)\n", x << 2); // 20

    // Right shift: divide by 2
    printf("x >> 1 = %d  (0101 → 0010)\n", x >> 1);  // 2
    printf("x >> 2 = %d  (0101 → 0001)\n", x >> 2);  // 1

    return 0;
}
```

### Practical Uses of Bitwise Operators

```c
// 1. Check if number is even/odd
if (num & 1) {
    printf("Odd\n");  // Last bit is 1
} else {
    printf("Even\n"); // Last bit is 0
}

// 2. Multiply/divide by powers of 2 (fast!)
int result = num << 3;  // Multiply by 8 (2^3)
int result = num >> 2;  // Divide by 4 (2^2)

// 3. Swap two numbers without temp variable
a = a ^ b;
b = a ^ b;
a = a ^ b;

// 4. Set/clear/toggle specific bits (used in embedded systems)
num |= (1 << 3);   // Set bit 3
num &= ~(1 << 3);  // Clear bit 3
num ^= (1 << 3);   // Toggle bit 3
```

## 7. Conditional (Ternary) Operator

Shorthand for `if-else` statement.

**Syntax:** `condition ? value_if_true : value_if_false`

```c
#include <stdio.h>

int main() {
    int age = 20;

    // Using if-else
    if (age >= 18) {
        printf("Adult\n");
    } else {
        printf("Minor\n");
    }

    // Using ternary operator (shorter!)
    printf("%s\n", (age >= 18) ? "Adult" : "Minor");

    // Assign value based on condition
    int a = 10, b = 20;
    int max = (a > b) ? a : b;
    printf("Maximum: %d\n", max);

    // Nested ternary (use sparingly!)
    int score = 85;
    char grade = (score >= 90) ? 'A' :
                 (score >= 80) ? 'B' :
                 (score >= 70) ? 'C' : 'F';
    printf("Grade: %c\n", grade);

    return 0;
}
```

**Output:**
```
Adult
Adult
Maximum: 20
Grade: B
```

### When to Use Ternary Operator

```c
// GOOD: Simple condition
int max = (a > b) ? a : b;

// GOOD: Short assignment
printf("Status: %s\n", (active) ? "Active" : "Inactive");

// BAD: Complex logic (use if-else instead)
result = (x > 10 && y < 20) ? (z * 2) : (w + 5);  // Hard to read!
```

## Operator Precedence and Associativity

Determines the order in which operators are evaluated.

### Precedence Table (Highest to Lowest)

```
┌──────┬────────────────────────────┬──────────────────┐
│ Level│       Operators            │  Associativity   │
├──────┼────────────────────────────┼──────────────────┤
│  1   │  ()  []  ->  .             │  Left to Right   │
│  2   │  !  ~  ++  --  (cast)      │  Right to Left   │
│  3   │  *  /  %                   │  Left to Right   │
│  4   │  +  -                      │  Left to Right   │
│  5   │  <<  >>                    │  Left to Right   │
│  6   │  <  <=  >  >=              │  Left to Right   │
│  7   │  ==  !=                    │  Left to Right   │
│  8   │  &                         │  Left to Right   │
│  9   │  ^                         │  Left to Right   │
│  10  │  |                         │  Left to Right   │
│  11  │  &&                        │  Left to Right   │
│  12  │  ||                        │  Left to Right   │
│  13  │  ?:                        │  Right to Left   │
│  14  │  =  +=  -=  *=  /=  %=     │  Right to Left   │
└──────┴────────────────────────────┴──────────────────┘
```

### Examples

```c
#include <stdio.h>

int main() {
    int result;

    // Example 1: Multiplication before addition
    result = 5 + 3 * 2;
    printf("5 + 3 * 2 = %d\n", result);  // 11, not 16
    // Evaluated as: 5 + (3 * 2) = 5 + 6 = 11

    // Example 2: Use parentheses to change order
    result = (5 + 3) * 2;
    printf("(5 + 3) * 2 = %d\n", result);  // 16

    // Example 3: Division before subtraction
    result = 10 - 8 / 2;
    printf("10 - 8 / 2 = %d\n", result);  // 6, not 1

    // Example 4: Comparison before logical AND
    int x = 5, y = 10, z = 15;
    result = x < y && y < z;
    printf("x < y && y < z = %d\n", result);  // 1 (true)
    // Evaluated as: (x < y) && (y < z)

    return 0;
}
```

## Common Mistakes and How to Avoid Them

### Mistake 1: Confusing = with ==

```c
// WRONG ❌
if (x = 5) {  // Assignment, not comparison!
    printf("This always executes\n");
}

// CORRECT ✅
if (x == 5) {  // Comparison
    printf("x equals 5\n");
}
```

### Mistake 2: Integer Division Surprise

```c
// WRONG ❌ (expecting 1.5)
int result = 3 / 2;
printf("%d\n", result);  // 1, not 1.5

// CORRECT ✅
float result = 3.0 / 2.0;
printf("%.1f\n", result);  // 1.5
```

### Mistake 3: Modulus with Floats

```c
// WRONG ❌
float x = 5.5 % 2.5;  // Error! % only works with integers

// CORRECT ✅
#include <math.h>
float x = fmod(5.5, 2.5);  // Use fmod() for floats
```

### Mistake 4: Forgetting Parentheses

```c
// WRONG ❌
int result = 5 + 3 * 2;  // 11, not 16

// CORRECT ✅ (if you want 16)
int result = (5 + 3) * 2;  // 16
```

### Mistake 5: Overcomplicating with Ternary

```c
// BAD: Hard to read
result = (a > b) ? (c > d ? x : y) : (e > f ? p : q);

// GOOD: Use if-else for complex logic
if (a > b) {
    result = (c > d) ? x : y;
} else {
    result = (e > f) ? p : q;
}
```

## Practice Exercises

### Exercise 1: Calculator Program

Create a calculator that:
- Takes two numbers from user
- Performs all arithmetic operations (+, -, *, /, %)
- Displays results in a formatted table

### Exercise 2: Even/Odd Checker

Write a program that checks if a number is even or odd using:
1. Modulus operator (%)
2. Bitwise AND operator (&)

Compare both methods.

### Exercise 3: Grading System

Create a program that:
- Takes a score (0-100)
- Uses ternary operator to assign grade:
  - A: 90-100
  - B: 80-89
  - C: 70-79
  - D: 60-69
  - F: Below 60

### Exercise 4: Logical Operations

Write a program for college admission that checks:
- Age >= 17
- GPA >= 3.0
- Test score >= 1200

Display "Eligible" only if ALL conditions are true.

### Exercise 5: Bitwise Magic

Write a program that:
- Takes a number
- Displays its binary representation (hint: use bit shifting)
- Multiplies it by 8 using bit shift
- Divides it by 4 using bit shift

## Quick Reference Card

### Arithmetic
```c
+  -  *  /  %
```

### Relational
```c
==  !=  >  <  >=  <=
```

### Logical
```c
&&  ||  !
```

### Assignment
```c
=  +=  -=  *=  /=  %=
```

### Increment/Decrement
```c
++  --
```

### Bitwise
```c
&  |  ^  ~  <<  >>
```

### Conditional
```c
condition ? true_value : false_value
```

## Summary

In this chapter, you learned:

✓ Arithmetic operators (+, -, *, /, %)
✓ Relational operators for comparison
✓ Logical operators with truth tables
✓ Assignment and compound assignment operators
✓ Increment/decrement (pre and post)
✓ Bitwise operators for bit manipulation
✓ Ternary operator for concise conditionals
✓ Operator precedence and associativity
✓ Common mistakes and how to avoid them

**Next Chapter Preview:** Input/Output - Learn how to interact with users using printf() and scanf()!

---

**Pro Tip:** When in doubt about operator precedence, use parentheses! They make your code clearer and prevent bugs.
