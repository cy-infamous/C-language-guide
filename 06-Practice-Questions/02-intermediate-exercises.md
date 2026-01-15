# C Programming - Intermediate Exercises

This file contains 20 intermediate-level problems covering loops, functions, arrays, strings, and pointers.

---

## Problem 1: Prime Numbers in Range
**Difficulty:** Medium
**Topics:** Loops, Functions, Prime Numbers

### Problem Statement
Print all prime numbers between two given numbers (inclusive).

### Input Format
Two integers: start and end of the range.

### Output Format
All prime numbers in the range, separated by spaces.

### Constraints
- 1 ≤ start ≤ end ≤ 10000

### Example Test Cases

**Test Case 1:**
```
Input: 10 30
Output: 11 13 17 19 23 29
```

**Test Case 2:**
```
Input: 1 10
Output: 2 3 5 7
```

<details>
<summary>Hint</summary>
Create a function isPrime(n) that checks if a number is prime. Use it in a loop to check all numbers in the given range.
</details>

---

## Problem 2: GCD and LCM
**Difficulty:** Medium
**Topics:** Functions, Mathematical Algorithms

### Problem Statement
Calculate the Greatest Common Divisor (GCD) and Least Common Multiple (LCM) of two numbers.

### Input Format
Two integers.

### Output Format
```
GCD: [value]
LCM: [value]
```

### Constraints
- 1 ≤ a, b ≤ 10^9

### Example Test Cases

**Test Case 1:**
```
Input: 12 18
Output:
GCD: 6
LCM: 36
```

**Test Case 2:**
```
Input: 7 13
Output:
GCD: 1
LCM: 91
```

<details>
<summary>Hint</summary>
Use Euclidean algorithm for GCD: gcd(a, b) = gcd(b, a % b) when b ≠ 0. For LCM, use the formula: LCM(a, b) = (a × b) / GCD(a, b)
</details>

---

## Problem 3: Power Function
**Difficulty:** Medium
**Topics:** Recursion, Functions

### Problem Statement
Calculate x raised to the power n (x^n) using recursion. Handle both positive and negative exponents.

### Input Format
Two numbers: base (x) and exponent (n).

### Output Format
```
Result: [value]
```

### Constraints
- -100 ≤ x ≤ 100
- -20 ≤ n ≤ 20

### Example Test Cases

**Test Case 1:**
```
Input: 2 5
Output: Result: 32.000000
```

**Test Case 2:**
```
Input: 2 -3
Output: Result: 0.125000
```

<details>
<summary>Hint</summary>
Base case: x^0 = 1. Recursive case: x^n = x × x^(n-1). For negative exponents: x^(-n) = 1 / x^n
</details>

---

## Problem 4: Array Sum and Average
**Difficulty:** Medium
**Topics:** Arrays, Loops

### Problem Statement
Given an array of integers, calculate and print the sum and average of all elements.

### Input Format
```
First line: N (number of elements)
Second line: N space-separated integers
```

### Output Format
```
Sum: [value]
Average: [value]
```

### Constraints
- 1 ≤ N ≤ 1000
- -10^6 ≤ elements ≤ 10^6

### Example Test Cases

**Test Case 1:**
```
Input:
5
10 20 30 40 50
Output:
Sum: 150
Average: 30.00
```

**Test Case 2:**
```
Input:
4
-5 10 -3 8
Output:
Sum: 10
Average: 2.50
```

<details>
<summary>Hint</summary>
Use a loop to iterate through the array and accumulate the sum. Calculate average as sum/N. Be careful with integer division.
</details>

---

## Problem 5: Find Maximum and Minimum in Array
**Difficulty:** Medium
**Topics:** Arrays, Loops

### Problem Statement
Find the maximum and minimum elements in an array along with their positions.

### Input Format
```
First line: N (number of elements)
Second line: N space-separated integers
```

### Output Format
```
Maximum: [value] at position [index]
Minimum: [value] at position [index]
```

### Constraints
- 1 ≤ N ≤ 1000
- -10^9 ≤ elements ≤ 10^9

### Example Test Cases

**Test Case 1:**
```
Input:
5
3 7 2 9 1
Output:
Maximum: 9 at position 3
Minimum: 1 at position 4
```

<details>
<summary>Hint</summary>
Initialize max and min with the first element. Traverse the array and update max/min whenever you find a larger/smaller element. Track their positions as well.
</details>

---

## Problem 6: Reverse an Array
**Difficulty:** Medium
**Topics:** Arrays, Two-Pointer Technique

### Problem Statement
Reverse an array in-place without using additional arrays.

### Input Format
```
First line: N (number of elements)
Second line: N space-separated integers
```

### Output Format
The reversed array, elements separated by spaces.

### Constraints
- 1 ≤ N ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input:
5
1 2 3 4 5
Output: 5 4 3 2 1
```

**Test Case 2:**
```
Input:
6
10 20 30 40 50 60
Output: 60 50 40 30 20 10
```

<details>
<summary>Hint</summary>
Use two pointers: one at the start and one at the end. Swap elements and move pointers toward the center until they meet.
</details>

---

## Problem 7: Linear Search
**Difficulty:** Medium
**Topics:** Arrays, Searching

### Problem Statement
Implement linear search to find if an element exists in an array. Return its position if found, otherwise return -1.

### Input Format
```
First line: N (number of elements)
Second line: N space-separated integers
Third line: X (element to search)
```

### Output Format
```
Element found at position [index]
```
or
```
Element not found
```

### Constraints
- 1 ≤ N ≤ 1000
- -10^9 ≤ elements, X ≤ 10^9

### Example Test Cases

**Test Case 1:**
```
Input:
5
10 20 30 40 50
30
Output: Element found at position 2
```

**Test Case 2:**
```
Input:
5
10 20 30 40 50
25
Output: Element not found
```

<details>
<summary>Hint</summary>
Iterate through the array and compare each element with the search key. Return the index when found.
</details>

---

## Problem 8: Binary Search
**Difficulty:** Medium
**Topics:** Arrays, Searching Algorithms

### Problem Statement
Implement binary search on a sorted array to find an element's position.

### Input Format
```
First line: N (number of elements)
Second line: N space-separated integers (sorted in ascending order)
Third line: X (element to search)
```

### Output Format
```
Element found at position [index]
```
or
```
Element not found
```

### Constraints
- 1 ≤ N ≤ 10^6
- Array is sorted in ascending order

### Example Test Cases

**Test Case 1:**
```
Input:
7
1 3 5 7 9 11 13
7
Output: Element found at position 3
```

**Test Case 2:**
```
Input:
7
1 3 5 7 9 11 13
6
Output: Element not found
```

<details>
<summary>Hint</summary>
Compare the middle element with the search key. If equal, return position. If key is smaller, search left half; if larger, search right half. Repeat until found or search space is empty.
</details>

---

## Problem 9: Bubble Sort
**Difficulty:** Medium
**Topics:** Arrays, Sorting Algorithms

### Problem Statement
Implement bubble sort to sort an array in ascending order.

### Input Format
```
First line: N (number of elements)
Second line: N space-separated integers
```

### Output Format
Sorted array, elements separated by spaces.

### Constraints
- 1 ≤ N ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input:
5
64 34 25 12 22
Output: 12 22 25 34 64
```

**Test Case 2:**
```
Input:
6
5 1 4 2 8 3
Output: 1 2 3 4 5 8
```

<details>
<summary>Hint</summary>
Use nested loops. In each pass, compare adjacent elements and swap if they're in wrong order. After each pass, the largest element "bubbles up" to its correct position.
</details>

---

## Problem 10: Selection Sort
**Difficulty:** Medium
**Topics:** Arrays, Sorting Algorithms

### Problem Statement
Implement selection sort to sort an array in ascending order.

### Input Format
```
First line: N (number of elements)
Second line: N space-separated integers
```

### Output Format
Sorted array, elements separated by spaces.

### Constraints
- 1 ≤ N ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input:
5
64 25 12 22 11
Output: 11 12 22 25 64
```

<details>
<summary>Hint</summary>
In each iteration, find the minimum element from the unsorted portion and swap it with the first unsorted element.
</details>

---

## Problem 11: String Length (without strlen)
**Difficulty:** Medium
**Topics:** Strings, Pointers

### Problem Statement
Calculate the length of a string without using the strlen() function.

### Input Format
A single line of text (string).

### Output Format
```
Length: [value]
```

### Constraints
- 0 ≤ length ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input: Hello World
Output: Length: 11
```

**Test Case 2:**
```
Input: C Programming
Output: Length: 13
```

<details>
<summary>Hint</summary>
Traverse the string character by character until you encounter the null terminator '\0'. Count the characters.
</details>

---

## Problem 12: String Copy (without strcpy)
**Difficulty:** Medium
**Topics:** Strings, Pointers

### Problem Statement
Copy one string to another without using strcpy() function.

### Input Format
A single line of text (source string).

### Output Format
The copied string.

### Constraints
- 0 ≤ length ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input: Hello
Output: Hello
```

<details>
<summary>Hint</summary>
Iterate through the source string and copy each character to the destination string. Don't forget to add the null terminator at the end.
</details>

---

## Problem 13: String Concatenation (without strcat)
**Difficulty:** Medium
**Topics:** Strings, Pointers

### Problem Statement
Concatenate two strings without using strcat() function.

### Input Format
```
First line: First string
Second line: Second string
```

### Output Format
The concatenated string.

### Constraints
- Combined length ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input:
Hello
World
Output: HelloWorld
```

**Test Case 2:**
```
Input:
C
Programming
Output: C Programming
```

<details>
<summary>Hint</summary>
First, find the end of the first string. Then copy the second string starting from that position.
</details>

---

## Problem 14: String Comparison (without strcmp)
**Difficulty:** Medium
**Topics:** Strings, Pointers

### Problem Statement
Compare two strings lexicographically without using strcmp(). Return:
- 0 if strings are equal
- Negative value if first string is smaller
- Positive value if first string is larger

### Input Format
```
First line: First string
Second line: Second string
```

### Output Format
```
Equal
```
or
```
First string is smaller
```
or
```
First string is larger
```

### Constraints
- Length ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input:
apple
apple
Output: Equal
```

**Test Case 2:**
```
Input:
apple
banana
Output: First string is smaller
```

<details>
<summary>Hint</summary>
Compare characters one by one. If characters differ, return the difference. If one string ends before the other, the shorter one is smaller.
</details>

---

## Problem 15: Palindrome String
**Difficulty:** Medium
**Topics:** Strings, Two-Pointer Technique

### Problem Statement
Check if a given string is a palindrome (reads the same forwards and backwards). Ignore spaces and case.

### Input Format
A single line of text.

### Output Format
```
Palindrome
```
or
```
Not a Palindrome
```

### Constraints
- 1 ≤ length ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input: racecar
Output: Palindrome
```

**Test Case 2:**
```
Input: A man a plan a canal Panama
Output: Palindrome
```

**Test Case 3:**
```
Input: hello
Output: Not a Palindrome
```

<details>
<summary>Hint</summary>
First, convert to lowercase and remove spaces. Then use two pointers from both ends, comparing characters as you move toward the center.
</details>

---

## Problem 16: Count Vowels and Consonants
**Difficulty:** Medium
**Topics:** Strings, Character Classification

### Problem Statement
Count the number of vowels and consonants in a string.

### Input Format
A single line of text.

### Output Format
```
Vowels: [count]
Consonants: [count]
```

### Constraints
- Only alphabetic characters are counted
- Case insensitive

### Example Test Cases

**Test Case 1:**
```
Input: Hello World
Output:
Vowels: 3
Consonants: 7
```

**Test Case 2:**
```
Input: Programming in C
Output:
Vowels: 4
Consonants: 9
```

<details>
<summary>Hint</summary>
Iterate through the string. Check if each character is alphabetic using isalpha(). Then check if it's a vowel (a, e, i, o, u) or consonant.
</details>

---

## Problem 17: Reverse Words in a String
**Difficulty:** Medium
**Topics:** Strings, Array Manipulation

### Problem Statement
Reverse the order of words in a sentence.

### Input Format
A single line of text.

### Output Format
The string with words in reverse order.

### Constraints
- 1 ≤ length ≤ 1000
- Words are separated by single spaces

### Example Test Cases

**Test Case 1:**
```
Input: Hello World
Output: World Hello
```

**Test Case 2:**
```
Input: C Programming Language
Output: Language Programming C
```

<details>
<summary>Hint</summary>
Method 1: Split the string into words, store them in an array, then print in reverse order.
Method 2: Reverse the entire string, then reverse each word individually.
</details>

---

## Problem 18: Swap Using Pointers
**Difficulty:** Medium
**Topics:** Pointers, Functions

### Problem Statement
Write a function to swap two integers using pointers.

### Input Format
Two integers.

### Output Format
```
Before swap: a = [value1], b = [value2]
After swap: a = [value2], b = [value1]
```

### Constraints
- -10^9 ≤ a, b ≤ 10^9

### Example Test Cases

**Test Case 1:**
```
Input: 5 10
Output:
Before swap: a = 5, b = 10
After swap: a = 10, b = 5
```

<details>
<summary>Hint</summary>
Create a swap function that takes two integer pointers as parameters. Use the dereference operator (*) to access and modify the values.
</details>

---

## Problem 19: Pointer Arithmetic
**Difficulty:** Medium
**Topics:** Pointers, Arrays

### Problem Statement
Traverse an array using pointer arithmetic and print all elements.

### Input Format
```
First line: N (number of elements)
Second line: N space-separated integers
```

### Output Format
Array elements separated by spaces.

### Constraints
- 1 ≤ N ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input:
5
10 20 30 40 50
Output: 10 20 30 40 50
```

<details>
<summary>Hint</summary>
Initialize a pointer to the array's first element. Use pointer increment (ptr++) to move to the next element. Access values using the dereference operator (*ptr).
</details>

---

## Problem 20: Frequency of Elements in Array
**Difficulty:** Medium
**Topics:** Arrays, Counting

### Problem Statement
Count the frequency of each distinct element in an array.

### Input Format
```
First line: N (number of elements)
Second line: N space-separated integers
```

### Output Format
Each distinct element and its frequency, one per line.

### Constraints
- 1 ≤ N ≤ 1000
- 1 ≤ elements ≤ 100

### Example Test Cases

**Test Case 1:**
```
Input:
8
1 2 2 3 1 3 3 4
Output:
1: 2
2: 2
3: 3
4: 1
```

**Test Case 2:**
```
Input:
5
5 5 5 5 5
Output:
5: 5
```

<details>
<summary>Hint</summary>
Method 1: Use a frequency array (if elements are in a known range).
Method 2: For each element, count occurrences and mark counted elements to avoid recounting.
</details>

---

## Additional Practice Tips

1. **Understand Data Structures:** Arrays and strings are fundamental. Master them before moving to advanced topics.
2. **Practice Pointer Arithmetic:** Pointers are powerful but tricky. Practice extensively.
3. **Write Functions:** Break down problems into smaller functions for better code organization.
4. **Test Edge Cases:** Always test with empty arrays, single elements, and boundary values.
5. **Optimize:** After solving, think about how to make your solution more efficient.

## Next Steps

After completing these exercises, move on to:
- **03-advanced-exercises.md** for problems on dynamic memory, file handling, and complex pointers
- Check the **solutions/** directory for detailed solutions and explanations
