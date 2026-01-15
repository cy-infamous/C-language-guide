# Control Structures

## What are Control Structures?

**Control structures** determine the **flow of execution** in a program. Without them, programs would execute line by line from top to bottom. Control structures allow you to:

- Make decisions (if-else)
- Choose from multiple options (switch)
- Repeat actions (loops - covered in next chapter)

```
┌─────────────────────────────────────────────┐
│         Program Flow                        │
├─────────────────────────────────────────────┤
│                                             │
│  SEQUENTIAL (Default)                       │
│  Statement 1  →  Statement 2  →  Statement 3│
│                                             │
│  CONDITIONAL (Decision Making)              │
│  Condition? → True path OR False path       │
│                                             │
│  SELECTION (Multiple Choices)               │
│  Menu? → Option 1, 2, 3, or default         │
└─────────────────────────────────────────────┘
```

## Types of Control Structures

```
┌───────────────────────────────────────────────┐
│        CONTROL STRUCTURES IN C                │
├───────────────────────────────────────────────┤
│                                               │
│  1. CONDITIONAL STATEMENTS                    │
│     ├── if statement                          │
│     ├── if-else statement                     │
│     ├── if-else if-else ladder                │
│     └── Nested if                             │
│                                               │
│  2. SWITCH STATEMENT                          │
│     └── Multi-way selection                   │
│                                               │
│  3. CONDITIONAL OPERATOR                      │
│     └── Ternary operator (?:)                 │
│                                               │
└───────────────────────────────────────────────┘
```

## 1. The `if` Statement

Executes a block of code **only if** a condition is true.

### Syntax

```c
if (condition) {
    // Code to execute if condition is true
}
```

### Flowchart

```
        START
          │
          ↓
    ┌──────────┐
    │Condition?│
    └──────────┘
       │    │
    True│    │False
       │    │
       ↓    ↓
    ┌────┐  Skip
    │Code│
    └────┘
       │
       ↓
      END
```

### Example

```c
#include <stdio.h>

int main() {
    int age;

    printf("Enter your age: ");
    scanf("%d", &age);

    if (age >= 18) {
        printf("You are eligible to vote!\n");
    }

    printf("Thank you!\n");

    return 0;
}
```

**Sample Runs:**

**Run 1:**
```
Enter your age: 20
You are eligible to vote!
Thank you!
```

**Run 2:**
```
Enter your age: 15
Thank you!
```

## 2. The `if-else` Statement

Provides **two paths**: one for true, one for false.

### Syntax

```c
if (condition) {
    // Code if true
} else {
    // Code if false
}
```

### Flowchart

```
        START
          │
          ↓
    ┌──────────┐
    │Condition?│
    └──────────┘
       │    │
    True│    │False
       │    │
       ↓    ↓
    ┌────┐ ┌────┐
    │True│ │False│
    │Code│ │Code│
    └────┘ └────┘
       │    │
       └────┘
          │
          ↓
         END
```

### Example

```c
#include <stdio.h>

int main() {
    int number;

    printf("Enter a number: ");
    scanf("%d", &number);

    if (number % 2 == 0) {
        printf("%d is EVEN\n", number);
    } else {
        printf("%d is ODD\n", number);
    }

    return 0;
}
```

**Sample Runs:**
```
Enter a number: 10
10 is EVEN

Enter a number: 7
7 is ODD
```

## 3. The `if-else if-else` Ladder

Used when you have **multiple conditions** to check.

### Syntax

```c
if (condition1) {
    // Code if condition1 is true
} else if (condition2) {
    // Code if condition2 is true
} else if (condition3) {
    // Code if condition3 is true
} else {
    // Code if all conditions are false
}
```

### Flowchart

```
        START
          │
          ↓
    ┌──────────┐
    │Condition1?│
    └──────────┘
       │    │
    True│    │False
       │    ↓
       │  ┌──────────┐
       │  │Condition2?│
       │  └──────────┘
       │     │    │
       │  True│   │False
       │     │    ↓
       │     │  ┌──────────┐
       │     │  │Condition3?│
       │     │  └──────────┘
       │     │     │    │
       │     │  True│   │False
       │     │     │    ↓
       ↓     ↓     ↓  ┌────┐
    ┌────┐┌────┐┌────┐│Else│
    │Code││Code││Code││Code│
    └────┘└────┘└────┘└────┘
       │     │     │    │
       └─────┴─────┴────┘
              │
              ↓
             END
```

### Example: Grading System

```c
#include <stdio.h>

int main() {
    int score;
    char grade;

    printf("╔═══════════════════════════════╗\n");
    printf("║    Grading System             ║\n");
    printf("╚═══════════════════════════════╝\n\n");

    printf("Enter your score (0-100): ");
    scanf("%d", &score);

    if (score >= 90) {
        grade = 'A';
        printf("Grade: %c (Excellent!)\n", grade);
    } else if (score >= 80) {
        grade = 'B';
        printf("Grade: %c (Very Good!)\n", grade);
    } else if (score >= 70) {
        grade = 'C';
        printf("Grade: %c (Good)\n", grade);
    } else if (score >= 60) {
        grade = 'D';
        printf("Grade: %c (Pass)\n", grade);
    } else if (score >= 0) {
        grade = 'F';
        printf("Grade: %c (Fail)\n", grade);
    } else {
        printf("Invalid score!\n");
    }

    return 0;
}
```

**Sample Runs:**
```
╔═══════════════════════════════╗
║    Grading System             ║
╚═══════════════════════════════╝

Enter your score (0-100): 85
Grade: B (Very Good!)

Enter your score (0-100): 55
Grade: F (Fail)
```

## 4. Nested `if` Statements

An `if` statement **inside another** `if` statement.

### Syntax

```c
if (condition1) {
    if (condition2) {
        // Code if both conditions are true
    }
}
```

### Example: Eligibility Checker

```c
#include <stdio.h>

int main() {
    int age;
    char has_license;

    printf("Enter your age: ");
    scanf("%d", &age);

    printf("Do you have a driving license? (Y/N): ");
    scanf(" %c", &has_license);

    if (age >= 18) {
        printf("✓ You are old enough to drive.\n");

        if (has_license == 'Y' || has_license == 'y') {
            printf("✓ You have a license.\n");
            printf("✓ You can drive legally!\n");
        } else {
            printf("✗ You need to get a license first.\n");
        }
    } else {
        printf("✗ You are too young to drive.\n");
    }

    return 0;
}
```

**Sample Runs:**

**Run 1:**
```
Enter your age: 20
Do you have a driving license? (Y/N): Y
✓ You are old enough to drive.
✓ You have a license.
✓ You can drive legally!
```

**Run 2:**
```
Enter your age: 20
Do you have a driving license? (Y/N): N
✓ You are old enough to drive.
✗ You need to get a license first.
```

**Run 3:**
```
Enter your age: 16
Do you have a driving license? (Y/N): Y
✗ You are too young to drive.
```

## 5. The `switch` Statement

Used for **multi-way selection** when you have many conditions to check against a single variable.

### Syntax

```c
switch (expression) {
    case constant1:
        // Code for case 1
        break;
    case constant2:
        // Code for case 2
        break;
    case constant3:
        // Code for case 3
        break;
    default:
        // Code if no case matches
}
```

### Flowchart

```
        START
          │
          ↓
    ┌──────────┐
    │Expression│
    └──────────┘
       │
       ├─────┬─────┬─────┬────────┐
       ↓     ↓     ↓     ↓        ↓
    ┌────┐┌────┐┌────┐┌────┐  ┌───────┐
    │Case││Case││Case││Case│  │Default│
    │ 1  ││ 2  ││ 3  ││ 4  │  │       │
    └────┘└────┘└────┘└────┘  └───────┘
       │     │     │     │        │
       └─────┴─────┴─────┴────────┘
              │
              ↓
             END
```

### Example: Simple Calculator

```c
#include <stdio.h>

int main() {
    float num1, num2, result;
    char operator;

    printf("╔════════════════════════════════╗\n");
    printf("║      Calculator v1.0           ║\n");
    printf("╚════════════════════════════════╝\n\n");

    printf("Enter first number: ");
    scanf("%f", &num1);

    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &operator);

    printf("Enter second number: ");
    scanf("%f", &num2);

    switch(operator) {
        case '+':
            result = num1 + num2;
            printf("%.2f + %.2f = %.2f\n", num1, num2, result);
            break;

        case '-':
            result = num1 - num2;
            printf("%.2f - %.2f = %.2f\n", num1, num2, result);
            break;

        case '*':
            result = num1 * num2;
            printf("%.2f × %.2f = %.2f\n", num1, num2, result);
            break;

        case '/':
            if (num2 != 0) {
                result = num1 / num2;
                printf("%.2f ÷ %.2f = %.2f\n", num1, num2, result);
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

### Important: The `break` Statement

The `break` statement **exits the switch**. Without it, execution **falls through** to the next case!

```c
#include <stdio.h>

int main() {
    int day = 2;

    printf("WITHOUT break:\n");
    switch(day) {
        case 1:
            printf("Monday\n");
        case 2:
            printf("Tuesday\n");    // Starts here
        case 3:
            printf("Wednesday\n");  // Falls through!
        case 4:
            printf("Thursday\n");   // Falls through!
        default:
            printf("Invalid day\n"); // Falls through!
    }

    printf("\nWITH break:\n");
    switch(day) {
        case 1:
            printf("Monday\n");
            break;
        case 2:
            printf("Tuesday\n");    // Executes this
            break;                  // Then exits
        case 3:
            printf("Wednesday\n");
            break;
        case 4:
            printf("Thursday\n");
            break;
        default:
            printf("Invalid day\n");
    }

    return 0;
}
```

**Output:**
```
WITHOUT break:
Tuesday
Wednesday
Thursday
Invalid day

WITH break:
Tuesday
```

### When to Use Fall-Through (Intentionally)

Sometimes fall-through is useful:

```c
#include <stdio.h>

int main() {
    char grade;

    printf("Enter your grade: ");
    scanf(" %c", &grade);

    switch(grade) {
        case 'A':
        case 'a':
            printf("Excellent! (90-100)\n");
            break;

        case 'B':
        case 'b':
            printf("Very Good! (80-89)\n");
            break;

        case 'C':
        case 'c':
            printf("Good (70-79)\n");
            break;

        case 'D':
        case 'd':
            printf("Pass (60-69)\n");
            break;

        case 'F':
        case 'f':
            printf("Fail (Below 60)\n");
            break;

        default:
            printf("Invalid grade!\n");
    }

    return 0;
}
```

## 6. The Ternary Operator `?:`

A shorthand for simple `if-else` statements.

### Syntax

```c
variable = (condition) ? value_if_true : value_if_false;
```

### Examples

```c
#include <stdio.h>

int main() {
    int a = 10, b = 20, max;

    // Using if-else
    if (a > b) {
        max = a;
    } else {
        max = b;
    }
    printf("Using if-else: max = %d\n", max);

    // Using ternary operator (shorter!)
    max = (a > b) ? a : b;
    printf("Using ternary: max = %d\n", max);

    // More examples
    int age = 20;
    printf("You are %s\n", (age >= 18) ? "an adult" : "a minor");

    int number = 7;
    printf("%d is %s\n", number, (number % 2 == 0) ? "even" : "odd");

    return 0;
}
```

**Output:**
```
Using if-else: max = 20
Using ternary: max = 20
You are an adult
7 is odd
```

### Nested Ternary (Use Sparingly!)

```c
#include <stdio.h>

int main() {
    int score = 85;
    char grade;

    // Nested ternary - works but hard to read
    grade = (score >= 90) ? 'A' :
            (score >= 80) ? 'B' :
            (score >= 70) ? 'C' :
            (score >= 60) ? 'D' : 'F';

    printf("Grade: %c\n", grade);

    return 0;
}
```

## `if-else` vs `switch`: When to Use Which?

```c
┌─────────────────────┬───────────────────────────────┐
│     Use if-else     │         Use switch            │
├─────────────────────┼───────────────────────────────┤
│ Range conditions    │ Discrete values               │
│ (score >= 90)       │ (day == 1, day == 2)          │
│                     │                               │
│ Complex conditions  │ Simple equality checks        │
│ (x > 5 && y < 10)   │ (choice == 1)                 │
│                     │                               │
│ Float comparisons   │ Integer/char comparisons      │
│ (temp > 98.6)       │ (grade == 'A')                │
│                     │                               │
│ Relational operators│ Constant values only          │
│ (<, >, <=, >=, !=)  │ (cannot use variables)        │
└─────────────────────┴───────────────────────────────┘
```

### Example: Same Program Both Ways

```c
#include <stdio.h>

int main() {
    int choice = 2;

    // Using if-else
    printf("Using if-else:\n");
    if (choice == 1) {
        printf("Option 1 selected\n");
    } else if (choice == 2) {
        printf("Option 2 selected\n");
    } else if (choice == 3) {
        printf("Option 3 selected\n");
    } else {
        printf("Invalid option\n");
    }

    // Using switch (cleaner for this case)
    printf("\nUsing switch:\n");
    switch(choice) {
        case 1:
            printf("Option 1 selected\n");
            break;
        case 2:
            printf("Option 2 selected\n");
            break;
        case 3:
            printf("Option 3 selected\n");
            break;
        default:
            printf("Invalid option\n");
    }

    return 0;
}
```

## Comprehensive Examples

### Example 1: ATM Menu System

```c
#include <stdio.h>

int main() {
    int choice;
    float balance = 1000.0;
    float amount;

    printf("╔════════════════════════════════╗\n");
    printf("║         ATM SYSTEM             ║\n");
    printf("╠════════════════════════════════╣\n");
    printf("║ 1. Check Balance               ║\n");
    printf("║ 2. Deposit Money               ║\n");
    printf("║ 3. Withdraw Money              ║\n");
    printf("║ 4. Exit                        ║\n");
    printf("╚════════════════════════════════╝\n\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            printf("\nYour balance: $%.2f\n", balance);
            break;

        case 2:
            printf("\nEnter amount to deposit: $");
            scanf("%f", &amount);
            if (amount > 0) {
                balance += amount;
                printf("Deposit successful!\n");
                printf("New balance: $%.2f\n", balance);
            } else {
                printf("Invalid amount!\n");
            }
            break;

        case 3:
            printf("\nEnter amount to withdraw: $");
            scanf("%f", &amount);
            if (amount > 0 && amount <= balance) {
                balance -= amount;
                printf("Withdrawal successful!\n");
                printf("New balance: $%.2f\n", balance);
            } else if (amount > balance) {
                printf("Insufficient funds!\n");
            } else {
                printf("Invalid amount!\n");
            }
            break;

        case 4:
            printf("\nThank you for using ATM!\n");
            break;

        default:
            printf("\nInvalid choice!\n");
    }

    return 0;
}
```

### Example 2: Leap Year Checker

```c
#include <stdio.h>

int main() {
    int year;

    printf("Enter a year: ");
    scanf("%d", &year);

    /*
     * Leap year conditions:
     * 1. Divisible by 4 AND
     * 2. Either NOT divisible by 100 OR divisible by 400
     */

    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                printf("%d is a leap year.\n", year);
            } else {
                printf("%d is not a leap year.\n", year);
            }
        } else {
            printf("%d is a leap year.\n", year);
        }
    } else {
        printf("%d is not a leap year.\n", year);
    }

    // Cleaner version using logical operators
    printf("\nUsing logical operators:\n");
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        printf("%d is a leap year.\n", year);
    } else {
        printf("%d is not a leap year.\n", year);
    }

    return 0;
}
```

### Example 3: Triangle Type Classifier

```c
#include <stdio.h>

int main() {
    float side1, side2, side3;

    printf("Enter three sides of triangle: ");
    scanf("%f %f %f", &side1, &side2, &side3);

    // Check if valid triangle
    if (side1 + side2 > side3 && side2 + side3 > side1 && side1 + side3 > side2) {
        printf("Valid triangle!\n\n");

        // Classify by sides
        if (side1 == side2 && side2 == side3) {
            printf("Type: Equilateral Triangle\n");
            printf("All sides are equal\n");
        } else if (side1 == side2 || side2 == side3 || side1 == side3) {
            printf("Type: Isosceles Triangle\n");
            printf("Two sides are equal\n");
        } else {
            printf("Type: Scalene Triangle\n");
            printf("All sides are different\n");
        }
    } else {
        printf("Invalid triangle!\n");
        printf("Sum of any two sides must be greater than the third side.\n");
    }

    return 0;
}
```

## Common Mistakes and How to Avoid Them

### Mistake 1: Using = Instead of ==

```c
// WRONG ❌
if (x = 5) {  // Assignment, not comparison!
    printf("This always executes\n");
}

// CORRECT ✅
if (x == 5) {
    printf("x equals 5\n");
}
```

### Mistake 2: Semicolon After if

```c
// WRONG ❌
if (x > 0);  // Semicolon ends the if!
{
    printf("This always executes\n");  // Not part of if!
}

// CORRECT ✅
if (x > 0) {
    printf("x is positive\n");
}
```

### Mistake 3: Forgetting break in switch

```c
// WRONG ❌
switch(choice) {
    case 1:
        printf("One\n");  // Falls through!
    case 2:
        printf("Two\n");  // Will also print if choice is 1!
}

// CORRECT ✅
switch(choice) {
    case 1:
        printf("One\n");
        break;
    case 2:
        printf("Two\n");
        break;
}
```

### Mistake 4: Comparing Floats with ==

```c
// WRONG ❌
float x = 0.1 + 0.2;
if (x == 0.3) {  // May not work due to precision!
    printf("Equal\n");
}

// CORRECT ✅
#include <math.h>
float x = 0.1 + 0.2;
if (fabs(x - 0.3) < 0.00001) {  // Use epsilon comparison
    printf("Equal\n");
}
```

### Mistake 5: Logical Operator Confusion

```c
// WRONG ❌
if (x > 0 && < 10) {  // Incomplete condition!

// CORRECT ✅
if (x > 0 && x < 10) {
    printf("x is between 0 and 10\n");
}
```

## Practice Exercises

### Exercise 1: Simple Login System

Create a program that:
- Asks for username and password
- Correct: username = "admin", password = "1234"
- Displays "Login successful" or "Invalid credentials"
- Use if-else statements

### Exercise 2: BMI Calculator with Categories

Write a program that:
- Calculates BMI from weight and height
- Categorizes into:
  - Underweight: BMI < 18.5
  - Normal: 18.5 <= BMI < 25
  - Overweight: 25 <= BMI < 30
  - Obese: BMI >= 30
- Use if-else ladder

### Exercise 3: Day of Week

Create a program that:
- Takes a number (1-7)
- Displays day name (1=Monday, 7=Sunday)
- Use switch statement
- Handle invalid input

### Exercise 4: Largest of Three Numbers

Write a program that:
- Takes three numbers
- Finds and displays the largest
- Use nested if or if-else ladder

### Exercise 5: Electricity Bill Calculator

Create a program that calculates electricity bill:
- First 100 units: $0.50/unit
- Next 100 units: $0.75/unit
- Next 100 units: $1.20/unit
- Above 300 units: $1.50/unit
- Add $50 service charge if bill > $250

Use appropriate control structures.

## Quick Reference Card

### if Statement
```c
if (condition) {
    // code
}
```

### if-else Statement
```c
if (condition) {
    // true code
} else {
    // false code
}
```

### if-else if-else Ladder
```c
if (condition1) {
    // code
} else if (condition2) {
    // code
} else {
    // code
}
```

### switch Statement
```c
switch(expression) {
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

### Ternary Operator
```c
result = (condition) ? true_value : false_value;
```

## Summary

In this chapter, you learned:

✓ What control structures are and why they're important
✓ if, if-else, and if-else if-else statements
✓ Nested if statements
✓ switch-case for multi-way selection
✓ The importance of break in switch
✓ Ternary operator for concise conditionals
✓ When to use if-else vs switch
✓ Common mistakes and how to avoid them
✓ Practical applications with flowcharts

**Next Topic Preview:** Loops - Learn how to repeat code efficiently with for, while, and do-while loops!

---

**Pro Tip:** Always use curly braces `{}` even for single-line if statements. It prevents bugs when you add more code later!

```c
// Good practice
if (condition) {
    statement;
}

// Avoid (error-prone)
if (condition)
    statement;
```

**Congratulations!** You've completed the basics of C programming. You now understand variables, operators, I/O, and control flow - the foundation of programming!
