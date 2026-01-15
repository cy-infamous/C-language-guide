# C Language Basics - Complete Guide

Welcome to the comprehensive C Programming Basics guide! This directory contains six detailed chapters covering all fundamental concepts of C programming for absolute beginners.

## Contents

### [01-introduction.md](01-introduction.md) (12 KB)
**What You'll Learn:**
- What is C and why learn it
- Brief history of C programming
- Setting up development environment (GCC, VS Code)
- Your first "Hello, World!" program
- Understanding the compilation process
- Common beginner mistakes
- 5 practice exercises

**Key Topics:** Installation, compilation, basic program structure, development environment setup

---

### [02-syntax-and-structure.md](02-syntax-and-structure.md) (22 KB)
**What You'll Learn:**
- Complete anatomy of a C program
- Preprocessor directives (#include, #define)
- Understanding the main() function
- Commenting best practices
- The 5-step compilation process (with diagrams)
- Code structure and formatting
- Program execution flow

**Key Topics:** Program structure, comments, preprocessor, compilation stages, coding standards

---

### [03-variables-and-datatypes.md](03-variables-and-datatypes.md) (23 KB)
**What You'll Learn:**
- Variable declaration and initialization
- Basic data types: int, float, double, char
- Type modifiers: signed, unsigned, short, long
- The sizeof operator
- Constants (const vs #define)
- Type casting (implicit and explicit)
- Format specifiers reference
- ASCII table

**Key Topics:** Variables, data types, type conversion, constants, memory size

---

### [04-operators.md](04-operators.md) (27 KB)
**What You'll Learn:**
- Arithmetic operators (+, -, *, /, %)
- Relational operators (==, !=, <, >, <=, >=)
- Logical operators (&&, ||, !) with truth tables
- Assignment operators (=, +=, -=, *=, /=, %=)
- Increment/Decrement (++, --) pre and post
- Bitwise operators (&, |, ^, ~, <<, >>)
- Ternary operator (?:)
- Operator precedence and associativity

**Key Topics:** All operator types, truth tables, precedence, practical examples

---

### [05-input-output.md](05-input-and-output.md) (26 KB)
**What You'll Learn:**
- printf() for formatted output
- scanf() for user input
- Format specifiers (complete table)
- Width and precision formatting
- getchar() and putchar() for characters
- puts() for strings
- Escape sequences
- Common scanf() pitfalls and solutions
- Creating formatted tables and receipts

**Key Topics:** I/O functions, format specifiers, formatting tricks, practical examples

---

### [06-control-structures.md](06-control-structures.md) (24 KB)
**What You'll Learn:**
- if statement
- if-else statement
- if-else if-else ladder
- Nested if statements
- switch-case statement (with break)
- Ternary operator
- Flowcharts for each structure
- if-else vs switch: when to use which
- Comprehensive examples (ATM system, leap year, triangle classifier)

**Key Topics:** Decision making, conditional statements, switch-case, control flow

---

## Learning Path

**Recommended Order:**
1. Start with **01-introduction.md** to set up your environment
2. Learn **02-syntax-and-structure.md** to understand program organization
3. Master **03-variables-and-datatypes.md** for data storage
4. Practice **04-operators.md** for manipulating data
5. Understand **05-input-output.md** for user interaction
6. Apply **06-control-structures.md** for decision making

## Features of This Guide

Each chapter includes:
- ✓ Clear explanations for absolute beginners
- ✓ Multiple code examples with detailed comments
- ✓ Visual diagrams and ASCII art
- ✓ Common mistakes and solutions
- ✓ 3-5 practice exercises
- ✓ Quick reference cards
- ✓ Real-world applications

## Practice Exercises

Each chapter ends with **3-5 practice exercises** ranging from basic to intermediate difficulty. Make sure to complete them before moving to the next chapter!

## Total Content

- **6 comprehensive chapters**
- **134+ KB of detailed content**
- **100+ code examples**
- **30+ practice exercises**
- **Multiple flowcharts and diagrams**
- **Truth tables and reference tables**

## Code Examples

All code examples are:
- Complete and ready to compile
- Thoroughly commented
- Include expected output
- Follow best practices
- Formatted for readability

## Study Tips

1. **Read Sequentially**: Follow the order from 01 to 06
2. **Type Code Yourself**: Don't just read - type and run examples
3. **Do All Exercises**: Practice is crucial for mastery
4. **Experiment**: Modify examples to see what happens
5. **Take Notes**: Write down key concepts in your own words
6. **Build Projects**: After completing all chapters, build small programs

## Getting Help

If you encounter issues:
1. Read error messages carefully (they tell you what's wrong!)
2. Review the "Common Mistakes" section in each chapter
3. Check the Quick Reference Cards
4. Re-read relevant sections
5. Practice more examples

## What's Next?

After completing these basics, you'll be ready for:
- Loops (for, while, do-while)
- Arrays and strings
- Functions
- Pointers
- Structures
- File handling

## Quick Reference

### Compilation Command
```bash
gcc filename.c -o outputname
gcc -Wall filename.c -o outputname  # with warnings
```

### Basic Program Template
```c
#include <stdio.h>

int main() {
    // Your code here
    return 0;
}
```

### Essential Shortcuts
- Compile and run: `gcc file.c -o file && ./file`
- Check GCC version: `gcc --version`
- VS Code: Ctrl+Alt+N to run (with Code Runner extension)

## File Sizes

| File | Size | Topics Covered |
|------|------|----------------|
| 01-introduction.md | 12 KB | Setup, first program |
| 02-syntax-and-structure.md | 22 KB | Program structure |
| 03-variables-and-datatypes.md | 23 KB | Data types |
| 04-operators.md | 27 KB | All operators |
| 05-input-output.md | 26 KB | I/O functions |
| 06-control-structures.md | 24 KB | Decision making |
| **Total** | **134 KB** | **Complete Basics** |

---

## About This Guide

This guide is designed for:
- College CS students with zero C knowledge
- Self-learners starting their programming journey
- Anyone wanting a solid foundation in C programming

**Created:** January 2026
**Difficulty:** Beginner
**Prerequisites:** None
**Estimated Time:** 20-30 hours to complete all chapters and exercises

---

**Happy Coding!** Remember: Every expert programmer started as a beginner. The key is consistent practice and never giving up!

*"The only way to learn a new programming language is by writing programs in it."* - Dennis Ritchie (Creator of C)
