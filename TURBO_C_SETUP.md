# Turbo C++ Installation and Setup Guide

Complete guide to installing and configuring Turbo C++ for C programming on Windows.

---

## Table of Contents
- [What is Turbo C++?](#what-is-turbo-c)
- [Download Turbo C++](#download-turbo-c)
- [Installation Steps](#installation-steps)
- [First Run Configuration](#first-run-configuration)
- [Using Turbo C++ IDE](#using-turbo-c-ide)
- [Writing Your First C Program](#writing-your-first-c-program)
- [Keyboard Shortcuts](#keyboard-shortcuts)
- [Common Issues and Solutions](#common-issues-and-solutions)
- [Tips for Students](#tips-for-students)

---

## What is Turbo C++?

**Turbo C++** is a classic integrated development environment (IDE) and compiler for C and C++ programming. Developed by Borland, it has been widely used in educational institutions, especially in India, for teaching C programming.

### Features
- Simple, lightweight IDE (< 5 MB)
- Built-in text editor with syntax highlighting
- Fast compilation
- DOS-based interface (runs in DOSBox on modern Windows)
- Suitable for learning C basics
- No complex setup required

### Why Turbo C++ for Learning?
- Popular in Indian colleges and universities
- Simple interface for beginners
- Minimal system requirements
- Easy to use for basic C programs
- Good for understanding C fundamentals

---

## Download Turbo C++

### Option 1: Download from TurboC++ Official Site

Visit: **https://turboc.codeplex.com/** (archive) or search "Turbo C++ 4.5 download" online

**Recommended Version**: Turbo C++ 4.5 (most stable and compatible)

### Option 2: Download Full Setup with DOSBox

Many websites provide Turbo C++ bundled with DOSBox for Windows 10/11 compatibility.

Search for: **"Turbo C++ for Windows 10"** or **"Turbo C++ 4.5 with DOSBox"**

**File Size**: Approximately 3-5 MB

---

## Installation Steps

### Step 1: Download the Setup File

1. Download **Turbo C++ 4.5** setup file (usually named `TC45.zip` or `TurboC++.exe`)
2. Save it to your Downloads folder

### Step 2: Extract the Files (if ZIP)

```
Right-click on TC45.zip → Extract All
Choose location: C:\TurboC++
```

### Step 3: Run the Installer

If you have an `.exe` installer:

1. **Run the installer** (right-click → Run as Administrator)
2. Choose installation directory: `C:\TurboC++` (recommended)
3. Click **Install** or **Next**
4. Wait for installation to complete

### Step 4: Alternative - Manual Setup

If you have a portable version:

1. **Create a folder**: `C:\TurboC++`
2. **Extract all files** to this folder
3. The folder structure should look like:
   ```
   C:\TurboC++\
   ├── BIN\      (contains TC.EXE)
   ├── INCLUDE\  (header files)
   ├── LIB\      (library files)
   └── DOSBox\   (if bundled)
   ```

---

## First Run Configuration

### Method 1: Using Shortcut

1. Double-click the **Turbo C++** shortcut on your desktop
2. The IDE will open in a DOSBox window (if bundled) or directly

### Method 2: Manual Launch

1. Navigate to `C:\TurboC++\BIN\`
2. Double-click **TC.EXE**
3. The Turbo C++ IDE will open

### First-Time Configuration

When you run Turbo C++ for the first time:

1. **Accept the default settings** (press Enter)
2. The IDE will open with a blue background
3. You'll see the main menu bar at the top

### Configure Directories

**Important**: Set correct directories for smooth operation

1. Press **Alt + O** (Options menu)
2. Select **Directories**
3. Verify these paths:
   ```
   Include Directories: C:\TURBOC\INCLUDE
   Library Directories: C:\TURBOC\LIB
   Output Directory:    C:\TURBOC\OUTPUT
   ```
4. Press **Enter** to save

---

## Using Turbo C++ IDE

### IDE Layout

```
┌─────────────────────────────────────────────────────────────┐
│ File  Edit  Search  Run  Compile  Debug  Project  Options  │ ← Menu Bar
├─────────────────────────────────────────────────────────────┤
│                                                             │
│                                                             │
│                    EDITOR AREA                              │ ← Code Editor
│                 (Type your code here)                       │
│                                                             │
│                                                             │
├─────────────────────────────────────────────────────────────┤
│ F1-Help  F2-Save  F3-Open  F9-Compile  F10-Menu           │ ← Status Bar
└─────────────────────────────────────────────────────────────┘
```

### Main Menu Options

| Menu | Purpose |
|------|---------|
| **File** | New, Open, Save, Exit |
| **Edit** | Cut, Copy, Paste, Undo |
| **Search** | Find, Replace, Go to line |
| **Run** | Run program (Ctrl+F9) |
| **Compile** | Compile only (Alt+F9) |
| **Debug** | Debugging options |
| **Project** | Manage multiple files |
| **Options** | IDE settings, directories |

---

## Writing Your First C Program

### Step 1: Create a New File

1. Press **Alt + F** (File menu)
2. Select **New** (or press **F3**)
3. A blank editor window opens

### Step 2: Write Your Code

Type the following program:

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    clrscr();  // Clear screen (Turbo C++ specific)

    printf("Hello, World!\n");
    printf("Welcome to Turbo C++\n");

    getch();   // Wait for key press (Turbo C++ specific)
}
```

**Note**: `clrscr()` and `getch()` are Turbo C++ specific functions from `conio.h`

### Step 3: Save Your File

1. Press **F2** (Save)
2. Enter filename: `hello.c` (must have .c extension)
3. Choose save location (default: `C:\TURBOC\BIN`)
4. Press **Enter**

### Step 4: Compile the Program

1. Press **Alt + F9** (Compile)
2. Wait for compilation
3. Check for errors in the message window
4. If errors, fix them and compile again

### Step 5: Run the Program

1. Press **Ctrl + F9** (Run)
2. The program executes in a DOS window
3. You'll see the output
4. Press any key to return to IDE

### Step 6: View Output (if screen closes quickly)

1. Press **Alt + F5** (View output screen)
2. See your program output
3. Press any key to return to IDE

---

## Keyboard Shortcuts

### Essential Shortcuts

| Shortcut | Action |
|----------|--------|
| **F1** | Help |
| **F2** | Save file |
| **F3** | Open file |
| **F4** | Run to cursor |
| **F5** | Zoom window |
| **F6** | Switch windows |
| **F7** | Trace into (debug) |
| **F8** | Step over (debug) |
| **F9** | Make (compile project) |
| **F10** | Activate menu bar |

### Menu Access Shortcuts

| Shortcut | Menu |
|----------|------|
| **Alt + F** | File menu |
| **Alt + E** | Edit menu |
| **Alt + S** | Search menu |
| **Alt + R** | Run menu |
| **Alt + C** | Compile menu |
| **Alt + O** | Options menu |
| **Alt + X** | Exit Turbo C++ |

### Compilation & Execution

| Shortcut | Action |
|----------|--------|
| **Alt + F9** | Compile current file |
| **Ctrl + F9** | Compile and Run |
| **Alt + F5** | View output window |
| **F9** | Make (compile all) |

### Editing Shortcuts

| Shortcut | Action |
|----------|--------|
| **Ctrl + Y** | Delete line |
| **Ctrl + K + B** | Mark block begin |
| **Ctrl + K + K** | Mark block end |
| **Ctrl + K + C** | Copy block |
| **Ctrl + K + V** | Move block |
| **Ctrl + K + Y** | Delete block |
| **Ctrl + K + R** | Read block from file |
| **Ctrl + K + W** | Write block to file |

---

## Common Issues and Solutions

### Issue 1: "Unable to open INCLUDE file"

**Error Message**: `Unable to open include file 'STDIO.H'`

**Solution**:
```
1. Press Alt + O (Options)
2. Select "Directories"
3. Set Include: C:\TURBOC\INCLUDE
4. Set Library: C:\TURBOC\LIB
5. Save and restart Turbo C++
```

### Issue 2: Program Output Disappears Quickly

**Problem**: Output window closes immediately after running

**Solution**:
```c
#include <conio.h>

void main() {
    // Your code here

    getch();  // Add this at the end
}
```

Or press **Alt + F5** to view output screen.

### Issue 3: "Linker Error: Undefined symbol"

**Error Message**: `Linker Error: Undefined symbol _main`

**Solution**:
- Make sure you have `main()` function
- Check spelling: it should be `main`, not `Main` or `MAIN`
- Ensure proper syntax:
  ```c
  void main() {
      // code
  }
  ```

### Issue 4: Full Screen Issues on Windows 10/11

**Problem**: Turbo C++ runs in a small window

**Solution**:
- Use Turbo C++ version bundled with DOSBox
- Or run in compatibility mode:
  ```
  Right-click TC.EXE → Properties
  → Compatibility → Check "Run in 640x480 screen resolution"
  ```

### Issue 5: "Floating Point Formats Not Linked"

**Error**: When using `scanf("%f", &variable)`

**Solution**:
```c
// Add a dummy floating point operation before scanf
void main() {
    float dummy = 0.0;
    float x;
    dummy = dummy;  // Dummy operation
    scanf("%f", &x);
}
```

### Issue 6: Graphics Programs Don't Work

**Error**: `BGI Error: Graphics not initialized`

**Solution**:
```c
#include <graphics.h>

void main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC\\BGI");
    // graphics code
    closegraph();
}
```

---

## Complete Program Example

Here's a complete program that demonstrates proper Turbo C++ syntax:

```c
/*
   Program: Simple Calculator
   Compiler: Turbo C++
   Author: Your Name
*/

#include <stdio.h>
#include <conio.h>

void main()
{
    int choice;
    float num1, num2, result;

    clrscr();  // Clear screen

    printf("=============================\n");
    printf("   SIMPLE CALCULATOR\n");
    printf("=============================\n\n");

    printf("Enter first number: ");
    scanf("%f", &num1);

    printf("Enter second number: ");
    scanf("%f", &num2);

    printf("\nSelect Operation:\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("\nEnter choice (1-4): ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            result = num1 + num2;
            printf("\n%.2f + %.2f = %.2f\n", num1, num2, result);
            break;
        case 2:
            result = num1 - num2;
            printf("\n%.2f - %.2f = %.2f\n", num1, num2, result);
            break;
        case 3:
            result = num1 * num2;
            printf("\n%.2f * %.2f = %.2f\n", num1, num2, result);
            break;
        case 4:
            if(num2 != 0) {
                result = num1 / num2;
                printf("\n%.2f / %.2f = %.2f\n", num1, num2, result);
            } else {
                printf("\nError: Division by zero!\n");
            }
            break;
        default:
            printf("\nInvalid choice!\n");
    }

    printf("\nPress any key to exit...");
    getch();  // Wait for key press
}
```

---

## Tips for Students

### 1. Always Include `conio.h` for Turbo C++
```c
#include <conio.h>  // For clrscr() and getch()
```

### 2. Use `clrscr()` at the Beginning
```c
void main() {
    clrscr();  // Clears previous output
    // your code
}
```

### 3. Use `getch()` at the End
```c
void main() {
    // your code
    getch();  // Waits for key press before closing
}
```

### 4. Save Files Regularly
- Press **F2** frequently while coding
- Save in a dedicated folder like `C:\MyPrograms\`

### 5. Use Meaningful Filenames
```
Good: calculator.c, student_grade.c, array_sum.c
Bad: prog1.c, test.c, abc.c
```

### 6. Compile Before Running
- Always compile first (**Alt + F9**)
- Check for errors
- Then run (**Ctrl + F9**)

### 7. Read Error Messages Carefully
- Note the line number where error occurred
- Read the error description
- Common errors: missing semicolon, undefined variables

### 8. Keep Backup of Your Programs
- Copy your `.c` files to another folder
- Use a USB drive or cloud storage

### 9. Practice Daily
- Type programs manually (don't copy-paste)
- Experiment with modifications
- Try different input values

### 10. Use Comments
```c
// Single line comment
/* Multi-line
   comment */
```

---

## Turbo C++ Specific Functions

### Console Functions (conio.h)

```c
clrscr();              // Clear screen
getch();               // Get character without echo
getche();              // Get character with echo
putch(ch);             // Print character
kbhit();               // Check if key pressed
clreol();              // Clear to end of line
delline();             // Delete line
gotoxy(x, y);          // Move cursor to position
wherex();              // Get cursor X position
wherey();              // Get cursor Y position
textcolor(color);      // Set text color
textbackground(color); // Set background color
```

### Example with Color

```c
#include <stdio.h>
#include <conio.h>

void main()
{
    clrscr();

    textcolor(YELLOW);
    textbackground(BLUE);
    cprintf("Colored Text in Turbo C++");

    getch();
}
```

---

## Differences: Turbo C++ vs Modern C

| Feature | Turbo C++ | Modern C (GCC) |
|---------|-----------|----------------|
| Header for I/O | `conio.h` available | No `conio.h` |
| Main function | `void main()` works | `int main()` required |
| Clear screen | `clrscr()` | System-dependent |
| Wait for key | `getch()` | Use `getchar()` |
| Standard | Old C (C89/C90) | C99, C11, C17, C23 |
| Platform | DOS/Windows | Cross-platform |

### Modern Equivalent of Turbo C++ Code

**Turbo C++:**
```c
#include <stdio.h>
#include <conio.h>

void main() {
    clrscr();
    printf("Hello\n");
    getch();
}
```

**Modern C (GCC):**
```c
#include <stdio.h>

int main() {
    // No clrscr() needed
    printf("Hello\n");
    return 0;  // Must return int
}
```

---

## Practice Exercises in Turbo C++

### Exercise 1: Basic Output
```c
#include <stdio.h>
#include <conio.h>

void main() {
    clrscr();
    printf("My name is: [Your Name]\n");
    printf("College: [Your College]\n");
    printf("Course: Computer Science\n");
    getch();
}
```

### Exercise 2: Input and Output
```c
#include <stdio.h>
#include <conio.h>

void main() {
    char name[50];
    int age;

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

### Exercise 3: Simple Calculation
```c
#include <stdio.h>
#include <conio.h>

void main() {
    int num1, num2, sum;

    clrscr();
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    sum = num1 + num2;

    printf("Sum = %d\n", sum);
    getch();
}
```

---

## Resources for Turbo C++

### Official Documentation
- Turbo C++ Help (Press F1 in IDE)
- Built-in examples in `EXAMPLES\` folder

### Online Resources
- Search "Turbo C++ programming tutorial"
- YouTube: "Turbo C++ basics"
- Programming forums for Turbo C++

### Practice Problems
- Solve exercises from this guide's practice sections
- Modify example programs
- Create your own mini-projects

---

## Summary

### Installation Checklist
- [ ] Downloaded Turbo C++ 4.5
- [ ] Installed to `C:\TurboC++`
- [ ] Configured directories (Include, Library)
- [ ] Created first program
- [ ] Successfully compiled and ran program

### Key Points to Remember
1. Always use `#include <conio.h>` for Turbo C++
2. Start programs with `clrscr()`
3. End programs with `getch()`
4. Save files with `.c` extension
5. Compile with **Alt + F9**, Run with **Ctrl + F9**
6. View output with **Alt + F5**

---

<div align="center">

## You're Ready to Start Programming in Turbo C++!

**[Start with Chapter 1: Introduction to C →](01-Basics/01-introduction.md)**

Practice the examples, experiment with the code, and happy coding!

</div>

---

**Note**: While Turbo C++ is great for learning basics, consider learning modern C compilers (like GCC) for real-world development after mastering the fundamentals.
