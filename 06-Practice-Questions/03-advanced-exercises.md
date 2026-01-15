# C Programming - Advanced Exercises

This file contains 20 advanced-level problems covering dynamic memory allocation, file handling, complex pointers, and advanced programming concepts.

---

## Problem 1: Dynamic Array Allocation
**Difficulty:** Hard
**Topics:** Dynamic Memory, Pointers

### Problem Statement
Create a program that dynamically allocates memory for an array, takes input, processes it, and properly frees the memory.

### Input Format
```
First line: N (number of elements)
Second line: N space-separated integers
```

### Output Format
```
Original array: [elements]
Doubled array: [elements]
```

### Constraints
- 1 ≤ N ≤ 10^6

### Example Test Cases

**Test Case 1:**
```
Input:
5
1 2 3 4 5
Output:
Original array: 1 2 3 4 5
Doubled array: 2 4 6 8 10
```

<details>
<summary>Hint</summary>
Use malloc() or calloc() to allocate memory. Remember to check if allocation succeeded (pointer != NULL). Always free() the memory before program ends.
</details>

---

## Problem 2: Dynamic 2D Array
**Difficulty:** Hard
**Topics:** Dynamic Memory, 2D Arrays

### Problem Statement
Create a 2D array dynamically with variable dimensions and perform matrix operations.

### Input Format
```
First line: rows columns
Next 'rows' lines: 'columns' space-separated integers
```

### Output Format
Print the matrix and its transpose.

### Constraints
- 1 ≤ rows, columns ≤ 100

### Example Test Cases

**Test Case 1:**
```
Input:
2 3
1 2 3
4 5 6
Output:
Original Matrix:
1 2 3
4 5 6

Transpose:
1 4
2 5
3 6
```

<details>
<summary>Hint</summary>
Allocate an array of pointers (for rows), then allocate memory for each row. For transpose, swap rows and columns. Don't forget to free all allocated memory.
</details>

---

## Problem 3: Memory Reallocation
**Difficulty:** Hard
**Topics:** Dynamic Memory, realloc()

### Problem Statement
Create a program that starts with a small array and dynamically grows it as needed using realloc().

### Input Format
```
First line: initial_size
Second line: number_of_operations
Next lines: ADD value OR PRINT
```

### Output Format
For PRINT: display all current elements.

### Constraints
- 1 ≤ initial_size ≤ 100
- Elements can grow beyond initial size

### Example Test Cases

**Test Case 1:**
```
Input:
2
5
ADD 10
ADD 20
ADD 30
PRINT
Output:
Array size: 3, Elements: 10 20 30
```

<details>
<summary>Hint</summary>
Start with malloc(). When array is full, use realloc() to increase size (typically double it). Check if realloc() succeeds. Keep track of current size and capacity.
</details>

---

## Problem 4: String Array with Dynamic Allocation
**Difficulty:** Hard
**Topics:** Dynamic Memory, Strings, 2D Character Arrays

### Problem Statement
Store N strings dynamically, sort them alphabetically, and display them.

### Input Format
```
First line: N (number of strings)
Next N lines: strings
```

### Output Format
Sorted strings, one per line.

### Constraints
- 1 ≤ N ≤ 1000
- 1 ≤ string length ≤ 100

### Example Test Cases

**Test Case 1:**
```
Input:
4
banana
apple
cherry
date
Output:
apple
banana
cherry
date
```

<details>
<summary>Hint</summary>
Allocate array of char pointers. For each string, allocate exact memory needed (strlen + 1). Use strcmp() for sorting. Free each string and then the array.
</details>

---

## Problem 5: File Writing
**Difficulty:** Medium
**Topics:** File Handling

### Problem Statement
Write a program that takes user input and writes it to a text file.

### Input Format
```
First line: filename
Second line: number of lines to write
Next lines: content to write
```

### Output Format
```
Successfully written to [filename]
```

### Constraints
- Valid filename
- 1 ≤ lines ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input:
output.txt
3
Hello World
This is a test
File handling in C
Output:
Successfully written to output.txt
```

<details>
<summary>Hint</summary>
Use fopen() with "w" mode to create/overwrite file. Check if file opened successfully. Use fprintf() or fputs() to write. Always fclose() the file.
</details>

---

## Problem 6: File Reading
**Difficulty:** Medium
**Topics:** File Handling

### Problem Statement
Read the contents of a text file and display it on the screen.

### Input Format
```
Filename
```

### Output Format
Contents of the file.

### Constraints
- File must exist

### Example Test Cases

**Test Case 1:**
```
Input: data.txt
Output: [contents of data.txt]
```

<details>
<summary>Hint</summary>
Use fopen() with "r" mode. Check if file exists. Read line by line using fgets() or character by character using fgetc(). Close file with fclose().
</details>

---

## Problem 7: File Copy
**Difficulty:** Medium
**Topics:** File Handling

### Problem Statement
Copy the contents of one file to another file.

### Input Format
```
Source filename
Destination filename
```

### Output Format
```
File copied successfully
```

### Constraints
- Source file must exist

### Example Test Cases

**Test Case 1:**
```
Input:
source.txt
dest.txt
Output:
File copied successfully
```

<details>
<summary>Hint</summary>
Open source file in read mode and destination in write mode. Read from source and write to destination character by character or line by line. Close both files.
</details>

---

## Problem 8: Count Words in File
**Difficulty:** Medium
**Topics:** File Handling, String Processing

### Problem Statement
Count the number of words, lines, and characters in a text file.

### Input Format
```
Filename
```

### Output Format
```
Lines: [count]
Words: [count]
Characters: [count]
```

### Constraints
- File must exist

### Example Test Cases

**Test Case 1:**
```
Input: sample.txt
Output:
Lines: 5
Words: 25
Characters: 120
```

<details>
<summary>Hint</summary>
Read file character by character. Count newlines for lines, spaces/tabs/newlines for word boundaries, and all characters for character count.
</details>

---

## Problem 9: Binary File Operations
**Difficulty:** Hard
**Topics:** File Handling, Binary Files, Structures

### Problem Statement
Create a student database using binary files. Store student records (name, roll number, marks) and retrieve them.

### Input Format
```
1. ADD name rollno marks
2. DISPLAY
3. SEARCH rollno
```

### Output Format
Based on operation: confirmation message or student details.

### Constraints
- Valid operations
- 1 ≤ rollno ≤ 10000
- 0 ≤ marks ≤ 100

### Example Test Cases

**Test Case 1:**
```
Input:
ADD John 101 85
ADD Alice 102 92
DISPLAY
Output:
John 101 85
Alice 102 92
```

<details>
<summary>Hint</summary>
Define a structure for student. Use fopen() with "ab" for append, "rb" for read. Use fwrite() to write structures, fread() to read them. Binary mode preserves exact data.
</details>

---

## Problem 10: Pointer to Pointer
**Difficulty:** Hard
**Topics:** Pointers, Double Pointers

### Problem Statement
Implement a function that modifies a pointer itself (not just the value it points to) using pointer to pointer.

### Input Format
```
Initial value
New value
```

### Output Format
```
Before: [address] -> [value]
After: [address] -> [value]
```

### Constraints
- Any integer values

### Example Test Cases

**Test Case 1:**
```
Input:
10
20
Output:
Before: 0x7fff5c... -> 10
After: 0x7fff5c... -> 20
```

<details>
<summary>Hint</summary>
Create a function that takes pointer to pointer (int **ptr). You can modify where the pointer points using *ptr = &new_var.
</details>

---

## Problem 11: Function Pointers
**Difficulty:** Hard
**Topics:** Function Pointers, Callbacks

### Problem Statement
Create a calculator using function pointers. Store arithmetic operations in an array of function pointers.

### Input Format
```
Number1 Operator Number2
```

### Output Format
```
Result: [value]
```

### Constraints
- Valid operators: +, -, *, /
- Division by zero not allowed

### Example Test Cases

**Test Case 1:**
```
Input: 10 + 5
Output: Result: 15
```

**Test Case 2:**
```
Input: 20 * 3
Output: Result: 60
```

<details>
<summary>Hint</summary>
Declare function pointer: int (*operation)(int, int). Create separate functions for each operation. Store them in an array and call based on operator.
</details>

---

## Problem 12: Generic Swap Using void Pointers
**Difficulty:** Hard
**Topics:** void Pointers, Generic Programming

### Problem Statement
Implement a generic swap function that can swap any data type using void pointers.

### Input Format
```
Type (int/float/char)
Value1 Value2
```

### Output Format
```
Before swap: [value1], [value2]
After swap: [value2], [value1]
```

### Constraints
- Support int, float, char types

### Example Test Cases

**Test Case 1:**
```
Input:
int
5 10
Output:
Before swap: 5, 10
After swap: 10, 5
```

<details>
<summary>Hint</summary>
void swap(void *a, void *b, size_t size). Use a temporary buffer and memcpy() to swap bytes. Cast void* to appropriate type for display.
</details>

---

## Problem 13: Linked List Simulation with Arrays
**Difficulty:** Hard
**Topics:** Arrays, Pointers, Data Structures

### Problem Statement
Simulate a linked list using arrays and indices instead of pointers.

### Input Format
```
Operations: INSERT value, DELETE value, DISPLAY
```

### Output Format
Current list state after each operation.

### Constraints
- Maximum 1000 nodes

### Example Test Cases

**Test Case 1:**
```
Input:
INSERT 10
INSERT 20
INSERT 30
DISPLAY
DELETE 20
DISPLAY
Output:
10 -> 20 -> 30
10 -> 30
```

<details>
<summary>Hint</summary>
Use two arrays: one for data, one for next indices. Maintain a head index. For free nodes, maintain a free list.
</details>

---

## Problem 14: Matrix Multiplication with Dynamic Memory
**Difficulty:** Hard
**Topics:** Dynamic Memory, 2D Arrays, Algorithms

### Problem Statement
Multiply two matrices of any compatible dimensions using dynamically allocated memory.

### Input Format
```
rows1 cols1
Matrix1 elements
rows2 cols2
Matrix2 elements
```

### Output Format
Resultant matrix or error message if incompatible.

### Constraints
- 1 ≤ dimensions ≤ 100
- cols1 must equal rows2

### Example Test Cases

**Test Case 1:**
```
Input:
2 3
1 2 3
4 5 6
3 2
7 8
9 10
11 12
Output:
58 64
139 154
```

<details>
<summary>Hint</summary>
Check if cols1 == rows2. Allocate result matrix (rows1 × cols2). Use triple nested loop for multiplication: result[i][j] = sum of matrix1[i][k] * matrix2[k][j].
</details>

---

## Problem 15: Command Line Arguments Processing
**Difficulty:** Medium
**Topics:** argc, argv, Command Line

### Problem Statement
Create a program that processes command line arguments to perform file operations.

### Input Format
```
./program operation filename [additional args]
Operations: count, copy source dest, display
```

### Output Format
Based on operation: file contents, counts, or success message.

### Constraints
- Valid command line arguments

### Example Test Cases

**Test Case 1:**
```
Command: ./program count data.txt
Output: Lines: 10, Words: 50, Characters: 250
```

<details>
<summary>Hint</summary>
int main(int argc, char *argv[]). argc is argument count, argv[] contains arguments as strings. argv[0] is program name, argv[1] is first argument, etc.
</details>

---

## Problem 16: Bitwise Operations Manager
**Difficulty:** Hard
**Topics:** Bitwise Operators, Bit Manipulation

### Problem Statement
Implement various bitwise operations: set bit, clear bit, toggle bit, check bit, count set bits.

### Input Format
```
Operation number value [position]
Operations: SET, CLEAR, TOGGLE, CHECK, COUNT
```

### Output Format
Result after operation or bit status.

### Constraints
- 0 ≤ number ≤ 10^9
- 0 ≤ position < 32

### Example Test Cases

**Test Case 1:**
```
Input: SET 5 1
Output: 7
Explanation: 5 (101) -> 7 (111)
```

**Test Case 2:**
```
Input: COUNT 15
Output: 4
Explanation: 15 (1111) has 4 set bits
```

<details>
<summary>Hint</summary>
Set: n | (1 << pos)
Clear: n & ~(1 << pos)
Toggle: n ^ (1 << pos)
Check: (n >> pos) & 1
Count: Loop and check each bit
</details>

---

## Problem 17: Structure Padding and Alignment
**Difficulty:** Hard
**Topics:** Structures, Memory Layout

### Problem Statement
Demonstrate structure padding by creating structures with different member orders and comparing sizes.

### Input Format
No input.

### Output Format
```
Structure 1 size: [size]
Structure 2 size: [size]
Padding details...
```

### Constraints
- None

### Example Test Cases

**Test Case 1:**
```
Output:
Structure 1 (char, int, char): 12 bytes
Structure 2 (char, char, int): 8 bytes
Padding saved: 4 bytes
```

<details>
<summary>Hint</summary>
Use sizeof() operator. Create same members in different orders. Use #pragma pack(1) to disable padding for comparison. Explain alignment requirements.
</details>

---

## Problem 18: Union vs Structure
**Difficulty:** Medium
**Topics:** Union, Structure, Memory

### Problem Statement
Demonstrate the difference between union and structure by creating similar data types and comparing memory usage.

### Input Format
```
Values for structure/union members
```

### Output Format
```
Structure size: [size]
Union size: [size]
Member values...
```

### Constraints
- None

### Example Test Cases

**Test Case 1:**
```
Input:
65 (integer)
65.5 (float)
A (char)
Output:
Structure: int=65, float=65.5, char=A, Size=12
Union: Last assigned value visible, Size=4
```

<details>
<summary>Hint</summary>
Structure: all members have separate memory. Union: all members share same memory (size = largest member). Assigning to one union member overwrites others.
</details>

---

## Problem 19: Preprocessor Macros
**Difficulty:** Medium
**Topics:** Macros, Preprocessor Directives

### Problem Statement
Create useful macros for common operations: MAX, MIN, SQUARE, ABS, SWAP, and demonstrate their usage.

### Input Format
```
Two or more numbers for testing macros
```

### Output Format
Results of macro operations.

### Constraints
- None

### Example Test Cases

**Test Case 1:**
```
Input: 5 10
Output:
MAX(5, 10) = 10
MIN(5, 10) = 5
SQUARE(5) = 25
ABS(-5) = 5
After SWAP: 10, 5
```

<details>
<summary>Hint</summary>
#define MAX(a,b) ((a) > (b) ? (a) : (b))
Always use parentheses around parameters and entire expression. Be careful with side effects (don't use MAX(a++, b++)).
</details>

---

## Problem 20: Memory Leak Detector
**Difficulty:** Hard
**Topics:** Dynamic Memory, Debugging

### Problem Statement
Create wrapper functions for malloc/free that track allocations and detect memory leaks.

### Input Format
```
Series of allocations and frees
```

### Output Format
```
Allocation tracking
Memory leak report
```

### Constraints
- Track up to 1000 allocations

### Example Test Cases

**Test Case 1:**
```
Operations:
Allocate 100 bytes
Allocate 200 bytes
Free first
Free second
Output:
Total allocated: 300 bytes
Total freed: 300 bytes
Memory leaks: 0 bytes
```

<details>
<summary>Hint</summary>
Create my_malloc() and my_free(). Maintain array/list of allocations with size and address. Mark as freed when free is called. At end, report unfree blocks.
</details>

---

## Additional Practice Tips

1. **Master Dynamic Memory:** Understand malloc, calloc, realloc, free thoroughly
2. **Practice File Operations:** Work with both text and binary files
3. **Understand Pointers Deeply:** Multi-level pointers, function pointers, void pointers
4. **Debug Memory Issues:** Use valgrind or similar tools to detect memory leaks
5. **Study Memory Layout:** Understand how structures, unions, and arrays are stored
6. **Read Documentation:** man pages provide excellent information about system calls

## Next Steps

After completing these exercises, move on to:
- **04-data-structures-problems.md** for comprehensive data structure implementations
- **05-algorithms-problems.md** for algorithm challenges
- Check the **solutions/** directory for detailed solutions and explanations

## Important Notes

- Always check return values of malloc, fopen, etc.
- Free all allocated memory before program exits
- Close all opened files
- Handle edge cases (NULL pointers, empty files, etc.)
- Use valgrind to detect memory leaks: `valgrind --leak-check=full ./program`
