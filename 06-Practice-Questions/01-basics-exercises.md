# C Programming - Basics Exercises

This file contains 20 beginner-level problems covering fundamental C programming concepts including syntax, variables, operators, input/output, and control structures.

---

## Problem 1: Hello World
**Difficulty:** Easy
**Topics:** Basic Syntax, Output

### Problem Statement
Write a C program that prints "Hello, World!" to the console.

### Input Format
No input required.

### Output Format
```
Hello, World!
```

### Constraints
- None

### Example Test Cases

**Test Case 1:**
```
Output: Hello, World!
```

<details>
<summary>Hint</summary>
Use the printf() function to display text on the screen.
</details>

---

## Problem 2: Sum of Two Numbers
**Difficulty:** Easy
**Topics:** Variables, Input/Output, Arithmetic Operators

### Problem Statement
Write a program that takes two integers as input and prints their sum.

### Input Format
Two integers separated by space or newline.

### Output Format
```
Sum: [result]
```

### Constraints
- -10^9 ≤ a, b ≤ 10^9

### Example Test Cases

**Test Case 1:**
```
Input: 5 3
Output: Sum: 8
```

**Test Case 2:**
```
Input: -10 25
Output: Sum: 15
```

<details>
<summary>Hint</summary>
Use scanf() to read integers and printf() to display the result. Use the %d format specifier for integers.
</details>

---

## Problem 3: Area of a Circle
**Difficulty:** Easy
**Topics:** Variables, Arithmetic Operators, Constants

### Problem Statement
Write a program to calculate the area of a circle given its radius. Use π = 3.14159.

### Input Format
A single floating-point number representing the radius.

### Output Format
```
Area: [result]
```

### Constraints
- 0 < radius ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input: 5.0
Output: Area: 78.53975
```

**Test Case 2:**
```
Input: 10.5
Output: Area: 346.36059
```

<details>
<summary>Hint</summary>
Formula: Area = π × r². Use %f format specifier for floating-point numbers. Define PI as a constant using #define.
</details>

---

## Problem 4: Temperature Converter
**Difficulty:** Easy
**Topics:** Variables, Arithmetic Operators, Type Conversion

### Problem Statement
Convert temperature from Celsius to Fahrenheit using the formula: F = (C × 9/5) + 32

### Input Format
A floating-point number representing temperature in Celsius.

### Output Format
```
[C] Celsius = [F] Fahrenheit
```

### Constraints
- -273.15 ≤ C ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input: 0
Output: 0.00 Celsius = 32.00 Fahrenheit
```

**Test Case 2:**
```
Input: 100
Output: 100.00 Celsius = 212.00 Fahrenheit
```

<details>
<summary>Hint</summary>
Be careful with integer division. Use floating-point division (9.0/5.0) to get accurate results.
</details>

---

## Problem 5: Even or Odd
**Difficulty:** Easy
**Topics:** Conditional Statements, Modulus Operator

### Problem Statement
Write a program to check whether a given number is even or odd.

### Input Format
A single integer.

### Output Format
```
Even
```
or
```
Odd
```

### Constraints
- -10^9 ≤ n ≤ 10^9

### Example Test Cases

**Test Case 1:**
```
Input: 4
Output: Even
```

**Test Case 2:**
```
Input: 7
Output: Odd
```

<details>
<summary>Hint</summary>
Use the modulus operator (%) to check if the number is divisible by 2. If n % 2 == 0, the number is even.
</details>

---

## Problem 6: Largest of Three Numbers
**Difficulty:** Easy
**Topics:** Conditional Statements, Relational Operators

### Problem Statement
Find the largest among three integers.

### Input Format
Three integers separated by spaces.

### Output Format
```
Largest: [number]
```

### Constraints
- -10^9 ≤ a, b, c ≤ 10^9

### Example Test Cases

**Test Case 1:**
```
Input: 10 25 15
Output: Largest: 25
```

**Test Case 2:**
```
Input: -5 -10 -3
Output: Largest: -3
```

<details>
<summary>Hint</summary>
Use nested if-else statements or logical operators (&&, ||) to compare the three numbers.
</details>

---

## Problem 7: Grade Calculator
**Difficulty:** Easy
**Topics:** Conditional Statements, If-Else Ladder

### Problem Statement
Write a program that assigns a letter grade based on marks:
- A: 90-100
- B: 80-89
- C: 70-79
- D: 60-69
- F: 0-59

### Input Format
An integer representing marks.

### Output Format
```
Grade: [letter]
```

### Constraints
- 0 ≤ marks ≤ 100

### Example Test Cases

**Test Case 1:**
```
Input: 85
Output: Grade: B
```

**Test Case 2:**
```
Input: 55
Output: Grade: F
```

<details>
<summary>Hint</summary>
Use an if-else ladder to check ranges. Start from the highest grade and work downward.
</details>

---

## Problem 8: Leap Year Checker
**Difficulty:** Easy
**Topics:** Conditional Statements, Logical Operators

### Problem Statement
Determine if a given year is a leap year. A year is a leap year if:
- It is divisible by 4 AND not divisible by 100, OR
- It is divisible by 400

### Input Format
A single integer representing the year.

### Output Format
```
Leap Year
```
or
```
Not a Leap Year
```

### Constraints
- 1 ≤ year ≤ 10000

### Example Test Cases

**Test Case 1:**
```
Input: 2000
Output: Leap Year
```

**Test Case 2:**
```
Input: 1900
Output: Not a Leap Year
```

**Test Case 3:**
```
Input: 2024
Output: Leap Year
```

<details>
<summary>Hint</summary>
Use logical operators to combine conditions: ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
</details>

---

## Problem 9: Simple Calculator
**Difficulty:** Easy
**Topics:** Switch Statement, Arithmetic Operators

### Problem Statement
Create a simple calculator that performs addition, subtraction, multiplication, or division based on user choice.

### Input Format
```
First number
Operator (+, -, *, /)
Second number
```

### Output Format
```
Result: [answer]
```

### Constraints
- -10^6 ≤ a, b ≤ 10^6
- For division, b ≠ 0

### Example Test Cases

**Test Case 1:**
```
Input:
10
+
5
Output: Result: 15.00
```

**Test Case 2:**
```
Input:
20
/
4
Output: Result: 5.00
```

<details>
<summary>Hint</summary>
Use a switch statement to handle different operators. Remember to check for division by zero.
</details>

---

## Problem 10: Print Numbers 1 to N
**Difficulty:** Easy
**Topics:** Loops (for loop)

### Problem Statement
Print all numbers from 1 to N, each on a new line.

### Input Format
A single integer N.

### Output Format
Numbers from 1 to N, each on a separate line.

### Constraints
- 1 ≤ N ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input: 5
Output:
1
2
3
4
5
```

<details>
<summary>Hint</summary>
Use a for loop that starts from 1 and goes up to N (inclusive).
</details>

---

## Problem 11: Sum of First N Natural Numbers
**Difficulty:** Easy
**Topics:** Loops, Accumulation

### Problem Statement
Calculate the sum of first N natural numbers.

### Input Format
A single integer N.

### Output Format
```
Sum: [result]
```

### Constraints
- 1 ≤ N ≤ 10000

### Example Test Cases

**Test Case 1:**
```
Input: 5
Output: Sum: 15
```
Explanation: 1 + 2 + 3 + 4 + 5 = 15

**Test Case 2:**
```
Input: 100
Output: Sum: 5050
```

<details>
<summary>Hint</summary>
Method 1: Use a loop to add numbers from 1 to N.
Method 2: Use the formula: Sum = N × (N + 1) / 2
</details>

---

## Problem 12: Factorial Calculator
**Difficulty:** Easy
**Topics:** Loops, Multiplication

### Problem Statement
Calculate the factorial of a given number N. Factorial of N (N!) = 1 × 2 × 3 × ... × N

### Input Format
A single integer N.

### Output Format
```
Factorial: [result]
```

### Constraints
- 0 ≤ N ≤ 20 (to avoid overflow)

### Example Test Cases

**Test Case 1:**
```
Input: 5
Output: Factorial: 120
```
Explanation: 5! = 1 × 2 × 3 × 4 × 5 = 120

**Test Case 2:**
```
Input: 0
Output: Factorial: 1
```
Explanation: 0! = 1 by definition

<details>
<summary>Hint</summary>
Initialize a variable to 1 and multiply it by numbers from 1 to N. Remember that 0! = 1.
</details>

---

## Problem 13: Multiplication Table
**Difficulty:** Easy
**Topics:** Loops, Arithmetic

### Problem Statement
Print the multiplication table of a given number up to 10.

### Input Format
A single integer N.

### Output Format
```
N x 1 = N
N x 2 = 2N
...
N x 10 = 10N
```

### Constraints
- 1 ≤ N ≤ 100

### Example Test Cases

**Test Case 1:**
```
Input: 5
Output:
5 x 1 = 5
5 x 2 = 10
5 x 3 = 15
5 x 4 = 20
5 x 5 = 25
5 x 6 = 30
5 x 7 = 35
5 x 8 = 40
5 x 9 = 45
5 x 10 = 50
```

<details>
<summary>Hint</summary>
Use a for loop from 1 to 10 and multiply N by the loop counter.
</details>

---

## Problem 14: Count Digits
**Difficulty:** Easy
**Topics:** Loops, Integer Division

### Problem Statement
Count the number of digits in a given integer.

### Input Format
A single integer.

### Output Format
```
Number of digits: [count]
```

### Constraints
- 0 ≤ N ≤ 10^9

### Example Test Cases

**Test Case 1:**
```
Input: 12345
Output: Number of digits: 5
```

**Test Case 2:**
```
Input: 0
Output: Number of digits: 1
```

<details>
<summary>Hint</summary>
Keep dividing the number by 10 and count iterations until the number becomes 0. Handle the special case of 0.
</details>

---

## Problem 15: Reverse a Number
**Difficulty:** Easy
**Topics:** Loops, Modulus Operator

### Problem Statement
Reverse the digits of a given integer.

### Input Format
A single integer.

### Output Format
```
Reversed: [result]
```

### Constraints
- 0 ≤ N ≤ 10^9

### Example Test Cases

**Test Case 1:**
```
Input: 12345
Output: Reversed: 54321
```

**Test Case 2:**
```
Input: 1000
Output: Reversed: 1
```

<details>
<summary>Hint</summary>
Extract the last digit using modulus (%), add it to the reversed number, and remove the last digit using integer division (/). Repeat until the number becomes 0.
</details>

---

## Problem 16: Sum of Digits
**Difficulty:** Easy
**Topics:** Loops, Modulus Operator

### Problem Statement
Calculate the sum of digits of a given integer.

### Input Format
A single integer.

### Output Format
```
Sum of digits: [result]
```

### Constraints
- 0 ≤ N ≤ 10^9

### Example Test Cases

**Test Case 1:**
```
Input: 12345
Output: Sum of digits: 15
```
Explanation: 1 + 2 + 3 + 4 + 5 = 15

**Test Case 2:**
```
Input: 999
Output: Sum of digits: 27
```

<details>
<summary>Hint</summary>
Extract each digit using modulus (%), add it to a sum variable, and remove the digit using integer division (/). Repeat until the number becomes 0.
</details>

---

## Problem 17: Prime Number Checker
**Difficulty:** Easy
**Topics:** Loops, Conditional Statements

### Problem Statement
Determine if a given number is prime. A prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself.

### Input Format
A single integer N.

### Output Format
```
Prime
```
or
```
Not Prime
```

### Constraints
- 1 ≤ N ≤ 10^6

### Example Test Cases

**Test Case 1:**
```
Input: 7
Output: Prime
```

**Test Case 2:**
```
Input: 10
Output: Not Prime
```

**Test Case 3:**
```
Input: 1
Output: Not Prime
```

<details>
<summary>Hint</summary>
Check if the number is divisible by any number from 2 to √N. If it is divisible by any number in this range, it's not prime. Handle special cases: 1 is not prime, 2 is prime.
</details>

---

## Problem 18: Fibonacci Series
**Difficulty:** Easy
**Topics:** Loops, Sequences

### Problem Statement
Print the first N numbers of the Fibonacci sequence. The Fibonacci sequence starts with 0 and 1, and each subsequent number is the sum of the previous two.

### Input Format
A single integer N.

### Output Format
N Fibonacci numbers separated by spaces.

### Constraints
- 1 ≤ N ≤ 30

### Example Test Cases

**Test Case 1:**
```
Input: 7
Output: 0 1 1 2 3 5 8
```

**Test Case 2:**
```
Input: 1
Output: 0
```

<details>
<summary>Hint</summary>
Initialize two variables with 0 and 1. Print them and use a loop to calculate subsequent numbers by adding the previous two. Update the variables in each iteration.
</details>

---

## Problem 19: Armstrong Number Checker
**Difficulty:** Easy
**Topics:** Loops, Power Function

### Problem Statement
Check if a number is an Armstrong number. An Armstrong number is a number that equals the sum of its own digits each raised to the power of the number of digits.

For example: 153 is an Armstrong number because 1³ + 5³ + 3³ = 1 + 125 + 27 = 153

### Input Format
A single integer.

### Output Format
```
Armstrong Number
```
or
```
Not an Armstrong Number
```

### Constraints
- 1 ≤ N ≤ 10^6

### Example Test Cases

**Test Case 1:**
```
Input: 153
Output: Armstrong Number
```

**Test Case 2:**
```
Input: 123
Output: Not an Armstrong Number
```

**Test Case 3:**
```
Input: 9474
Output: Armstrong Number
```
Explanation: 9⁴ + 4⁴ + 7⁴ + 4⁴ = 6561 + 256 + 2401 + 256 = 9474

<details>
<summary>Hint</summary>
First, count the number of digits. Then extract each digit, raise it to the power of digit count, and sum them up. Compare the sum with the original number. Use pow() function from math.h.
</details>

---

## Problem 20: Pattern Printing - Right Triangle
**Difficulty:** Easy
**Topics:** Nested Loops, Pattern Printing

### Problem Statement
Print a right-angled triangle pattern using asterisks (*).

### Input Format
A single integer N representing the number of rows.

### Output Format
A right-angled triangle pattern with N rows.

### Constraints
- 1 ≤ N ≤ 20

### Example Test Cases

**Test Case 1:**
```
Input: 5
Output:
*
**
***
****
*****
```

**Test Case 2:**
```
Input: 3
Output:
*
**
***
```

<details>
<summary>Hint</summary>
Use nested loops. The outer loop controls rows (1 to N), and the inner loop prints asterisks (1 to current row number).
</details>

---

## Additional Practice Tips

1. **Start Simple:** Begin with the first few problems and gradually move to harder ones.
2. **Test Thoroughly:** Test your solutions with the provided test cases and create your own edge cases.
3. **Understand Concepts:** Don't just copy solutions; understand why they work.
4. **Practice Debugging:** Use printf statements to debug your code when things don't work.
5. **Code Style:** Write clean, readable code with proper indentation and comments.
6. **Time Yourself:** Try to solve problems within a time limit to improve problem-solving speed.

## Next Steps

After completing these exercises, move on to:
- **02-intermediate-exercises.md** for problems on loops, functions, arrays, strings, and pointers
- Check the **solutions/** directory for detailed solutions and explanations
