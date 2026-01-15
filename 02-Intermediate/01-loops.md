# Loops in C

## Table of Contents
1. [Introduction to Loops](#introduction-to-loops)
2. [Types of Loops](#types-of-loops)
3. [Loop Control Statements](#loop-control-statements)
4. [Nested Loops](#nested-loops)
5. [Real-World Applications](#real-world-applications)
6. [Practice Exercises](#practice-exercises)

---

## Introduction to Loops

Loops are control structures that allow you to execute a block of code repeatedly based on a condition. They are essential for:
- Processing collections of data
- Performing repetitive tasks
- Iterating through arrays
- Implementing algorithms

### Why Use Loops?

Without loops, you would need to write the same code multiple times:
```c
printf("Count: 1\n");
printf("Count: 2\n");
printf("Count: 3\n");
// ... and so on
```

With loops, you can achieve this efficiently:
```c
for(int i = 1; i <= 3; i++) {
    printf("Count: %d\n", i);
}
```

---

## Types of Loops

### 1. For Loop

The `for` loop is used when you know exactly how many times you want to execute a block of code.

**Syntax:**
```c
for(initialization; condition; increment/decrement) {
    // code to be executed
}
```

**Flowchart:**
```
    START
      |
      v
[Initialization]
      |
      v
   <Condition> ----NO----> EXIT
      |YES
      v
 [Loop Body]
      |
      v
[Increment/Decrement]
      |
      v
   (Back to Condition)
```

**Example 1: Basic For Loop**
```c
#include <stdio.h>

int main() {
    // Print numbers 1 to 5
    for(int i = 1; i <= 5; i++) {
        printf("%d ", i);
    }
    printf("\n");

    return 0;
}
// Output: 1 2 3 4 5
```

**Example 2: For Loop with Step**
```c
#include <stdio.h>

int main() {
    // Print even numbers from 0 to 10
    for(int i = 0; i <= 10; i += 2) {
        printf("%d ", i);
    }
    printf("\n");

    return 0;
}
// Output: 0 2 4 6 8 10
```

**Example 3: Reverse For Loop**
```c
#include <stdio.h>

int main() {
    // Countdown from 5 to 1
    for(int i = 5; i >= 1; i--) {
        printf("%d ", i);
    }
    printf("\nBlastoff!\n");

    return 0;
}
// Output: 5 4 3 2 1
//         Blastoff!
```

### 2. While Loop

The `while` loop is used when you don't know in advance how many times the loop will execute. It checks the condition before executing the loop body.

**Syntax:**
```c
while(condition) {
    // code to be executed
}
```

**Flowchart:**
```
    START
      |
      v
   <Condition> ----NO----> EXIT
      |YES
      v
 [Loop Body]
      |
      v
   (Back to Condition)
```

**Example 1: Basic While Loop**
```c
#include <stdio.h>

int main() {
    int count = 1;

    while(count <= 5) {
        printf("%d ", count);
        count++;
    }
    printf("\n");

    return 0;
}
// Output: 1 2 3 4 5
```

**Example 2: User Input Validation**
```c
#include <stdio.h>

int main() {
    int num;

    printf("Enter a positive number: ");
    scanf("%d", &num);

    // Keep asking until user enters a positive number
    while(num <= 0) {
        printf("Invalid! Enter a positive number: ");
        scanf("%d", &num);
    }

    printf("You entered: %d\n", num);
    return 0;
}
```

**Example 3: Sum of Numbers**
```c
#include <stdio.h>

int main() {
    int n = 1, sum = 0;

    while(n <= 10) {
        sum += n;
        n++;
    }

    printf("Sum of numbers 1 to 10: %d\n", sum);
    return 0;
}
// Output: Sum of numbers 1 to 10: 55
```

### 3. Do-While Loop

The `do-while` loop is similar to the while loop, but it checks the condition after executing the loop body. This guarantees that the loop executes at least once.

**Syntax:**
```c
do {
    // code to be executed
} while(condition);
```

**Flowchart:**
```
    START
      |
      v
 [Loop Body]
      |
      v
   <Condition> ----YES----> (Back to Loop Body)
      |NO
      v
    EXIT
```

**Example 1: Basic Do-While Loop**
```c
#include <stdio.h>

int main() {
    int count = 1;

    do {
        printf("%d ", count);
        count++;
    } while(count <= 5);

    printf("\n");
    return 0;
}
// Output: 1 2 3 4 5
```

**Example 2: Menu-Driven Program**
```c
#include <stdio.h>

int main() {
    int choice;

    do {
        printf("\n=== MENU ===\n");
        printf("1. Option 1\n");
        printf("2. Option 2\n");
        printf("3. Option 3\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("You selected Option 1\n");
                break;
            case 2:
                printf("You selected Option 2\n");
                break;
            case 3:
                printf("You selected Option 3\n");
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 4);

    return 0;
}
```

**Example 3: Number Guessing Game**
```c
#include <stdio.h>

int main() {
    int secret = 42, guess;

    do {
        printf("Guess the number: ");
        scanf("%d", &guess);

        if(guess < secret)
            printf("Too low! Try again.\n");
        else if(guess > secret)
            printf("Too high! Try again.\n");
        else
            printf("Congratulations! You guessed it!\n");

    } while(guess != secret);

    return 0;
}
```

### Comparison: For vs While vs Do-While

| Feature | For Loop | While Loop | Do-While Loop |
|---------|----------|------------|---------------|
| When to use | Known iterations | Unknown iterations | At least one execution needed |
| Condition check | Before execution | Before execution | After execution |
| Initialization | In loop header | Before loop | Before loop |
| Use case | Counting, iterating | Validation, events | Menus, prompts |

---

## Loop Control Statements

### 1. Break Statement

The `break` statement terminates the loop immediately and transfers control to the statement following the loop.

**Example 1: Finding First Even Number**
```c
#include <stdio.h>

int main() {
    int numbers[] = {1, 3, 5, 8, 9, 11};
    int size = 6;

    for(int i = 0; i < size; i++) {
        if(numbers[i] % 2 == 0) {
            printf("First even number found: %d\n", numbers[i]);
            break;  // Exit loop immediately
        }
    }

    return 0;
}
// Output: First even number found: 8
```

**Example 2: Search with Break**
```c
#include <stdio.h>

int main() {
    int target = 25;
    int arr[] = {10, 20, 25, 30, 40};
    int size = 5;
    int found = 0;

    for(int i = 0; i < size; i++) {
        if(arr[i] == target) {
            printf("Target %d found at index %d\n", target, i);
            found = 1;
            break;
        }
    }

    if(!found) {
        printf("Target not found\n");
    }

    return 0;
}
// Output: Target 25 found at index 2
```

### 2. Continue Statement

The `continue` statement skips the remaining code in the current iteration and moves to the next iteration of the loop.

**Example 1: Skip Even Numbers**
```c
#include <stdio.h>

int main() {
    printf("Odd numbers from 1 to 10: ");

    for(int i = 1; i <= 10; i++) {
        if(i % 2 == 0) {
            continue;  // Skip even numbers
        }
        printf("%d ", i);
    }
    printf("\n");

    return 0;
}
// Output: Odd numbers from 1 to 10: 1 3 5 7 9
```

**Example 2: Skip Negative Numbers**
```c
#include <stdio.h>

int main() {
    int numbers[] = {10, -5, 20, -3, 30, 15, -7};
    int size = 7;
    int sum = 0;

    printf("Processing only positive numbers: ");
    for(int i = 0; i < size; i++) {
        if(numbers[i] < 0) {
            continue;  // Skip negative numbers
        }
        printf("%d ", numbers[i]);
        sum += numbers[i];
    }

    printf("\nSum of positive numbers: %d\n", sum);
    return 0;
}
// Output: Processing only positive numbers: 10 20 30 15
//         Sum of positive numbers: 75
```

**Break vs Continue Flowchart:**
```
FOR BREAK:
   Loop Iteration
         |
         v
    <Condition>
      /     \
    YES      NO
     |        |
  BREAK   Continue
     |     Loop Body
     v
  EXIT

FOR CONTINUE:
   Loop Iteration
         |
         v
    <Condition>
      /     \
    YES      NO
     |        |
 CONTINUE  Continue
     |     Loop Body
     v        |
   SKIP      |
     |        |
     +--------+
     |
  Next Iteration
```

---

## Nested Loops

Nested loops are loops inside other loops. The inner loop completes all its iterations for each iteration of the outer loop.

**Execution Flow:**
```
Outer Loop (i=1)
    Inner Loop (j=1,2,3)
Outer Loop (i=2)
    Inner Loop (j=1,2,3)
Outer Loop (i=3)
    Inner Loop (j=1,2,3)
```

### Example 1: Multiplication Table
```c
#include <stdio.h>

int main() {
    printf("Multiplication Table (1-5):\n\n");
    printf("    ");

    // Print column headers
    for(int i = 1; i <= 5; i++) {
        printf("%4d", i);
    }
    printf("\n    --------------------\n");

    // Print table
    for(int i = 1; i <= 5; i++) {
        printf("%2d |", i);
        for(int j = 1; j <= 5; j++) {
            printf("%4d", i * j);
        }
        printf("\n");
    }

    return 0;
}
/* Output:
        1   2   3   4   5
    --------------------
 1 |   1   2   3   4   5
 2 |   2   4   6   8  10
 3 |   3   6   9  12  15
 4 |   4   8  12  16  20
 5 |   5  10  15  20  25
*/
```

### Example 2: Pattern Printing

**Right Triangle Pattern:**
```c
#include <stdio.h>

int main() {
    int rows = 5;

    for(int i = 1; i <= rows; i++) {
        for(int j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }

    return 0;
}
/* Output:
*
* *
* * *
* * * *
* * * * *
*/
```

**Pyramid Pattern:**
```c
#include <stdio.h>

int main() {
    int rows = 5;

    for(int i = 1; i <= rows; i++) {
        // Print spaces
        for(int j = 1; j <= rows - i; j++) {
            printf(" ");
        }
        // Print stars
        for(int k = 1; k <= 2*i - 1; k++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
/* Output:
    *
   ***
  *****
 *******
*********
*/
```

**Number Pattern:**
```c
#include <stdio.h>

int main() {
    int rows = 5;

    for(int i = 1; i <= rows; i++) {
        for(int j = 1; j <= i; j++) {
            printf("%d ", j);
        }
        printf("\n");
    }

    return 0;
}
/* Output:
1
1 2
1 2 3
1 2 3 4
1 2 3 4 5
*/
```

### Example 3: Matrix Operations
```c
#include <stdio.h>

int main() {
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int sum = 0;

    printf("Matrix:\n");
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
            sum += matrix[i][j];
        }
        printf("\n");
    }

    printf("\nSum of all elements: %d\n", sum);
    return 0;
}
/* Output:
Matrix:
1 2 3
4 5 6
7 8 9

Sum of all elements: 45
*/
```

---

## Real-World Applications

### 1. Factorial Calculation
```c
#include <stdio.h>

int main() {
    int n = 5;
    unsigned long long factorial = 1;

    printf("Calculating %d! = ", n);

    for(int i = 1; i <= n; i++) {
        factorial *= i;
    }

    printf("%llu\n", factorial);
    return 0;
}
// Output: Calculating 5! = 120
```

### 2. Prime Number Checker
```c
#include <stdio.h>

int main() {
    int num = 29;
    int isPrime = 1;

    if(num <= 1) {
        isPrime = 0;
    } else {
        for(int i = 2; i * i <= num; i++) {
            if(num % i == 0) {
                isPrime = 0;
                break;
            }
        }
    }

    if(isPrime)
        printf("%d is a prime number\n", num);
    else
        printf("%d is not a prime number\n", num);

    return 0;
}
// Output: 29 is a prime number
```

### 3. Fibonacci Series
```c
#include <stdio.h>

int main() {
    int n = 10;
    int first = 0, second = 1, next;

    printf("Fibonacci Series (first %d terms):\n", n);
    printf("%d %d ", first, second);

    for(int i = 3; i <= n; i++) {
        next = first + second;
        printf("%d ", next);
        first = second;
        second = next;
    }
    printf("\n");

    return 0;
}
// Output: Fibonacci Series (first 10 terms):
//         0 1 1 2 3 5 8 13 21 34
```

### 4. Array Average Calculator
```c
#include <stdio.h>

int main() {
    int scores[] = {85, 92, 78, 90, 88};
    int size = 5;
    int sum = 0;
    float average;

    for(int i = 0; i < size; i++) {
        sum += scores[i];
    }

    average = (float)sum / size;

    printf("Scores: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", scores[i]);
    }
    printf("\nAverage: %.2f\n", average);

    return 0;
}
// Output: Scores: 85 92 78 90 88
//         Average: 86.60
```

### 5. ATM Withdrawal Simulation
```c
#include <stdio.h>

int main() {
    int balance = 1000;
    int choice, amount;

    do {
        printf("\n=== ATM MENU ===\n");
        printf("1. Check Balance\n");
        printf("2. Withdraw\n");
        printf("3. Deposit\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Your balance: $%d\n", balance);
                break;
            case 2:
                printf("Enter amount to withdraw: $");
                scanf("%d", &amount);
                if(amount > balance) {
                    printf("Insufficient balance!\n");
                } else {
                    balance -= amount;
                    printf("Withdrawal successful. New balance: $%d\n", balance);
                }
                break;
            case 3:
                printf("Enter amount to deposit: $");
                scanf("%d", &amount);
                balance += amount;
                printf("Deposit successful. New balance: $%d\n", balance);
                break;
            case 4:
                printf("Thank you for using ATM!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 4);

    return 0;
}
```

---

## Practice Exercises

### Basic Level

**Exercise 1:** Write a program to print all even numbers between 1 and 50 using a for loop.

**Exercise 2:** Create a program that takes a number as input and prints its multiplication table from 1 to 10.

**Exercise 3:** Write a program using a while loop to calculate the sum of all numbers entered by the user until they enter 0.

### Intermediate Level

**Exercise 4:** Create a program that prints the following pattern:
```
1
2 2
3 3 3
4 4 4 4
5 5 5 5 5
```

**Exercise 5:** Write a program to find all prime numbers between 1 and 100 using nested loops.

**Exercise 6:** Create a program that reverses a number using loops. For example, input: 1234, output: 4321.

### Advanced Level

**Exercise 7:** Write a program to print the following diamond pattern:
```
    *
   ***
  *****
 *******
*********
 *******
  *****
   ***
    *
```

**Hints:**
- Exercise 1: Use for loop with condition i % 2 == 0
- Exercise 2: Use nested loop or single loop with multiplication
- Exercise 3: Use while loop with condition num != 0
- Exercise 4: Use nested loops where inner loop runs i times
- Exercise 5: Use outer loop for numbers and inner loop to check divisibility
- Exercise 6: Use modulo operator (%) to extract digits
- Exercise 7: Combine two patterns - increasing pyramid and decreasing pyramid

---

## Key Takeaways

1. **For loops** are best when you know the number of iterations in advance
2. **While loops** are ideal for condition-based repetition
3. **Do-while loops** guarantee at least one execution
4. **Break** exits the loop immediately
5. **Continue** skips to the next iteration
6. **Nested loops** are powerful for multi-dimensional operations
7. Choose the right loop type based on your problem requirements

---

## Additional Tips

- Always initialize loop variables properly
- Ensure loop conditions will eventually become false to avoid infinite loops
- Use meaningful variable names (i, j, k are acceptable for simple counters)
- Be careful with nested loops - they can significantly increase execution time
- Test loop boundaries (first iteration, last iteration, edge cases)

---

**Next Topic:** [Functions](02-functions.md) - Learn how to organize your code into reusable blocks!
