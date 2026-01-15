# File Handling in C

## Table of Contents
1. [Introduction to File Handling](#introduction)
2. [File Operations Overview](#file-operations-overview)
3. [Text File Operations](#text-file-operations)
4. [Binary File Operations](#binary-file-operations)
5. [File Positioning](#file-positioning)
6. [Error Handling](#error-handling)
7. [Advanced File Techniques](#advanced-techniques)
8. [Practice Exercises](#practice-exercises)

---

## Introduction to File Handling

Files provide persistent storage for data beyond program execution. C provides comprehensive file I/O capabilities through the Standard Library.

### Why File Handling?

- **Persistence**: Data survives after program terminates
- **Large Data**: Handle datasets too large for memory
- **Communication**: Exchange data between programs
- **Configuration**: Store settings and preferences
- **Logging**: Record program activity and errors

### File Types

1. **Text Files**: Human-readable, contains ASCII/UTF-8 characters
   - Examples: `.txt`, `.csv`, `.log`, `.c`, `.h`
   - Line endings: `\n` (Unix) or `\r\n` (Windows)

2. **Binary Files**: Machine-readable, contains raw bytes
   - Examples: `.exe`, `.dat`, `.bin`, images, videos
   - Exact memory representation, no conversion

---

## File Operations Overview

### Standard File Operations Workflow

```
1. Open file     (fopen)
2. Check success (verify FILE* != NULL)
3. Read/Write    (fread, fwrite, fprintf, fscanf, etc.)
4. Close file    (fclose)
```

### FILE Structure

```c
FILE *fp;  // File pointer (opaque structure)
```

`FILE*` is a pointer to a structure that contains:
- File descriptor
- Buffer for I/O
- Current position
- Error and EOF indicators
- Mode flags

### File Opening Modes

| Mode | Description | Creates if Missing | Truncates if Exists | Position |
|------|-------------|-------------------|-------------------|----------|
| `"r"` | Read text | No (fails) | No | Beginning |
| `"w"` | Write text | Yes | Yes | Beginning |
| `"a"` | Append text | Yes | No | End |
| `"r+"` | Read/Write text | No (fails) | No | Beginning |
| `"w+"` | Read/Write text | Yes | Yes | Beginning |
| `"a+"` | Read/Append text | Yes | No | End |
| `"rb"` | Read binary | No (fails) | No | Beginning |
| `"wb"` | Write binary | Yes | Yes | Beginning |
| `"ab"` | Append binary | Yes | No | End |
| `"rb+"` | Read/Write binary | No (fails) | No | Beginning |
| `"wb+"` | Read/Write binary | Yes | Yes | Beginning |
| `"ab+"` | Read/Append binary | Yes | No | End |

---

## Text File Operations

### 1. Opening and Closing Files

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;

    // Open file for writing
    fp = fopen("output.txt", "w");

    // Always check if opening succeeded
    if (fp == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // File operations here
    fprintf(fp, "Hello, File!\n");

    // Close file
    fclose(fp);

    return EXIT_SUCCESS;
}
```

### 2. fprintf() - Formatted Write to File

```c
int fprintf(FILE *stream, const char *format, ...);
```

Similar to `printf()`, but writes to file instead of console.

**Example:**

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("student.txt", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    char name[] = "Alice Johnson";
    int age = 20;
    float gpa = 3.85;

    // Write formatted data
    fprintf(fp, "Name: %s\n", name);
    fprintf(fp, "Age: %d\n", age);
    fprintf(fp, "GPA: %.2f\n", gpa);

    fclose(fp);
    printf("Data written successfully!\n");

    return 0;
}
```

**File Contents (student.txt):**
```
Name: Alice Johnson
Age: 20
GPA: 3.85
```

### 3. fscanf() - Formatted Read from File

```c
int fscanf(FILE *stream, const char *format, ...);
```

Similar to `scanf()`, but reads from file. Returns number of items successfully read, or EOF on failure.

**Example:**

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("student.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    char name[50];
    int age;
    float gpa;

    // Read formatted data
    fscanf(fp, "Name: %[^\n]\n", name);  // Read until newline
    fscanf(fp, "Age: %d\n", &age);
    fscanf(fp, "GPA: %f\n", &gpa);

    printf("Read from file:\n");
    printf("Name: %s\n", name);
    printf("Age: %d\n", age);
    printf("GPA: %.2f\n", gpa);

    fclose(fp);

    return 0;
}
```

### 4. fgets() - Read Line from File

```c
char* fgets(char *str, int n, FILE *stream);
```

Reads at most `n-1` characters or until newline (whichever comes first). Includes newline character in result.

**Example:**

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[256];

    printf("File contents:\n");
    printf("----------------\n");

    // Read line by line
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);  // line already contains \n
    }

    fclose(fp);

    return 0;
}
```

### 5. fputs() - Write String to File

```c
int fputs(const char *str, FILE *stream);
```

Writes string to file. Does NOT add newline automatically.

**Example:**

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("output.txt", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    fputs("Line 1\n", fp);
    fputs("Line 2\n", fp);
    fputs("Line 3\n", fp);

    fclose(fp);

    return 0;
}
```

### 6. fgetc() and fputc() - Character I/O

```c
int fgetc(FILE *stream);         // Read one character
int fputc(int c, FILE *stream);  // Write one character
```

**Example: Copy File Character by Character**

```c
#include <stdio.h>

int main() {
    FILE *source = fopen("source.txt", "r");
    FILE *dest = fopen("destination.txt", "w");

    if (source == NULL || dest == NULL) {
        perror("Error opening file");
        return 1;
    }

    int ch;
    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, dest);
    }

    printf("File copied successfully!\n");

    fclose(source);
    fclose(dest);

    return 0;
}
```

### 7. Complete Example: Student Record Management

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    float gpa;
} Student;

void add_student() {
    FILE *fp = fopen("students.txt", "a");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    Student s;
    printf("Enter ID: ");
    scanf("%d", &s.id);
    getchar();  // Consume newline

    printf("Enter Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0;  // Remove newline

    printf("Enter GPA: ");
    scanf("%f", &s.gpa);

    fprintf(fp, "%d|%s|%.2f\n", s.id, s.name, s.gpa);
    fclose(fp);

    printf("Student added successfully!\n");
}

void display_students() {
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    Student s;
    printf("\n%-5s %-30s %-5s\n", "ID", "Name", "GPA");
    printf("------------------------------------------\n");

    while (fscanf(fp, "%d|%[^|]|%f\n", &s.id, s.name, &s.gpa) == 3) {
        printf("%-5d %-30s %.2f\n", s.id, s.name, s.gpa);
    }

    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                display_students();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
```

---

## Binary File Operations

Binary files store data in the exact format as it exists in memory. More efficient and preserves exact values (no conversion).

### 1. fread() - Read Binary Data

```c
size_t fread(void *ptr, size_t size, size_t count, FILE *stream);
```

- `ptr`: Buffer to store data
- `size`: Size of each element (in bytes)
- `count`: Number of elements
- Returns: Number of elements successfully read

### 2. fwrite() - Write Binary Data

```c
size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);
```

- `ptr`: Data to write
- `size`: Size of each element
- `count`: Number of elements
- Returns: Number of elements successfully written

### 3. Example: Binary Integer Array

```c
#include <stdio.h>

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int size = 5;

    // Write binary data
    FILE *fp = fopen("numbers.dat", "wb");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    size_t written = fwrite(numbers, sizeof(int), size, fp);
    printf("Wrote %zu integers\n", written);
    fclose(fp);

    // Read binary data
    int read_numbers[5];
    fp = fopen("numbers.dat", "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    size_t read = fread(read_numbers, sizeof(int), size, fp);
    printf("Read %zu integers\n", read);

    printf("Numbers: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", read_numbers[i]);
    }
    printf("\n");

    fclose(fp);

    return 0;
}
```

### 4. Example: Binary Structure I/O

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    float salary;
} Employee;

void write_employees() {
    FILE *fp = fopen("employees.dat", "wb");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    Employee employees[] = {
        {101, "Alice Johnson", 75000.50},
        {102, "Bob Smith", 82000.75},
        {103, "Charlie Brown", 68000.00}
    };

    int count = sizeof(employees) / sizeof(employees[0]);

    fwrite(employees, sizeof(Employee), count, fp);
    printf("Wrote %d employees\n", count);

    fclose(fp);
}

void read_employees() {
    FILE *fp = fopen("employees.dat", "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    Employee emp;

    printf("\n%-5s %-30s %-10s\n", "ID", "Name", "Salary");
    printf("------------------------------------------------\n");

    while (fread(&emp, sizeof(Employee), 1, fp) == 1) {
        printf("%-5d %-30s $%.2f\n", emp.id, emp.name, emp.salary);
    }

    fclose(fp);
}

int main() {
    write_employees();
    read_employees();

    return 0;
}
```

### Text vs Binary Files Comparison

**Example: Storing Integer 1234567890**

```c
#include <stdio.h>

int main() {
    int num = 1234567890;

    // Text file
    FILE *text = fopen("text.txt", "w");
    fprintf(text, "%d", num);
    fclose(text);

    // Binary file
    FILE *binary = fopen("binary.dat", "wb");
    fwrite(&num, sizeof(int), 1, binary);
    fclose(binary);

    // Check file sizes
    // text.txt: 10 bytes (digits: "1234567890")
    // binary.dat: 4 bytes (exact integer representation)

    printf("Integer %d stored\n", num);
    printf("Text file: 10 bytes\n");
    printf("Binary file: 4 bytes\n");

    return 0;
}
```

| Aspect | Text File | Binary File |
|--------|-----------|-------------|
| **Human Readable** | Yes | No |
| **Size** | Larger (ASCII conversion) | Smaller (exact bytes) |
| **Precision** | May lose precision | Exact representation |
| **Speed** | Slower (conversion) | Faster (direct) |
| **Portability** | Better (platform-independent text) | Worse (endianness issues) |
| **Best For** | Config, logs, CSV | Images, executables, large data |

---

## File Positioning

File positioning functions allow random access to files (move to any position without reading sequentially).

### 1. ftell() - Get Current Position

```c
long ftell(FILE *stream);
```

Returns current file position (bytes from beginning), or -1L on error.

### 2. fseek() - Set File Position

```c
int fseek(FILE *stream, long offset, int whence);
```

- `offset`: Number of bytes to move
- `whence`: Starting point
  - `SEEK_SET` (0): Beginning of file
  - `SEEK_CUR` (1): Current position
  - `SEEK_END` (2): End of file

Returns 0 on success, non-zero on error.

### 3. rewind() - Reset to Beginning

```c
void rewind(FILE *stream);
```

Equivalent to `fseek(stream, 0L, SEEK_SET)` but also clears error indicators.

### 4. Example: File Positioning

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("data.txt", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Write data
    fprintf(fp, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    fclose(fp);

    // Reopen for reading
    fp = fopen("data.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Current position
    printf("Current position: %ld\n", ftell(fp));  // 0

    // Read first 5 characters
    char buffer[6];
    fgets(buffer, 6, fp);
    printf("Read: %s\n", buffer);  // ABCDE
    printf("Current position: %ld\n", ftell(fp));  // 5

    // Seek to position 10
    fseek(fp, 10, SEEK_SET);
    printf("After fseek(10, SEEK_SET): %ld\n", ftell(fp));  // 10

    // Read 5 characters
    fgets(buffer, 6, fp);
    printf("Read: %s\n", buffer);  // KLMNO

    // Seek 3 bytes forward from current
    fseek(fp, 3, SEEK_CUR);
    printf("After fseek(3, SEEK_CUR): %ld\n", ftell(fp));  // 18

    fgets(buffer, 6, fp);
    printf("Read: %s\n", buffer);  // STUVW

    // Seek to 5 bytes before end
    fseek(fp, -5, SEEK_END);
    printf("After fseek(-5, SEEK_END): %ld\n", ftell(fp));  // 21

    fgets(buffer, 6, fp);
    printf("Read: %s\n", buffer);  // VWXYZ

    // Go back to beginning
    rewind(fp);
    printf("After rewind: %ld\n", ftell(fp));  // 0

    fclose(fp);

    return 0;
}
```

### 5. Random Access in Binary Files

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char name[30];
    float grade;
} Student;

int main() {
    FILE *fp;
    Student s;

    // Write some students
    fp = fopen("students.dat", "wb");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    Student students[] = {
        {1, "Alice", 85.5},
        {2, "Bob", 90.0},
        {3, "Charlie", 78.5},
        {4, "David", 92.0},
        {5, "Eve", 88.5}
    };

    fwrite(students, sizeof(Student), 5, fp);
    fclose(fp);

    // Read specific student (e.g., 3rd student, index 2)
    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    int index = 2;  // Charlie
    fseek(fp, index * sizeof(Student), SEEK_SET);
    fread(&s, sizeof(Student), 1, fp);

    printf("Student at index %d:\n", index);
    printf("ID: %d, Name: %s, Grade: %.1f\n", s.id, s.name, s.grade);

    // Update this student's grade
    s.grade = 95.0;
    fseek(fp, index * sizeof(Student), SEEK_SET);
    fclose(fp);

    // Reopen in update mode
    fp = fopen("students.dat", "rb+");
    fseek(fp, index * sizeof(Student), SEEK_SET);
    fwrite(&s, sizeof(Student), 1, fp);

    printf("Updated Charlie's grade to %.1f\n", s.grade);

    fclose(fp);

    return 0;
}
```

---

## Error Handling

### 1. feof() - Check End of File

```c
int feof(FILE *stream);
```

Returns non-zero if EOF has been reached, 0 otherwise.

### 2. ferror() - Check for Errors

```c
int ferror(FILE *stream);
```

Returns non-zero if error indicator is set, 0 otherwise.

### 3. clearerr() - Clear Error Indicators

```c
void clearerr(FILE *stream);
```

Clears EOF and error indicators.

### 4. perror() - Print Error Message

```c
void perror(const char *str);
```

Prints error message corresponding to current value of `errno`.

### 5. Complete Error Handling Example

```c
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    FILE *fp = fopen("nonexistent.txt", "r");

    if (fp == NULL) {
        // Method 1: perror (automatically includes errno message)
        perror("Error");

        // Method 2: strerror (manual formatting)
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));

        return 1;
    }

    // File operations
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    // Check why loop ended
    if (feof(fp)) {
        printf("End of file reached\n");
    } else if (ferror(fp)) {
        perror("Error reading file");
        clearerr(fp);  // Clear error for potential retry
    }

    fclose(fp);

    return 0;
}
```

---

## Advanced File Techniques

### 1. File Size Calculation

```c
#include <stdio.h>

long get_file_size(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }

    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    fclose(fp);

    return size;
}

int main() {
    const char *filename = "data.txt";
    long size = get_file_size(filename);

    if (size >= 0) {
        printf("File size: %ld bytes\n", size);
    } else {
        printf("Error getting file size\n");
    }

    return 0;
}
```

### 2. File Copying with Progress

```c
#include <stdio.h>

int copy_file(const char *source, const char *dest) {
    FILE *src = fopen(source, "rb");
    if (src == NULL) {
        perror("Error opening source");
        return 0;
    }

    FILE *dst = fopen(dest, "wb");
    if (dst == NULL) {
        perror("Error opening destination");
        fclose(src);
        return 0;
    }

    // Get file size
    fseek(src, 0L, SEEK_END);
    long size = ftell(src);
    rewind(src);

    // Copy with progress
    char buffer[4096];
    long copied = 0;
    size_t bytes;

    printf("Copying %ld bytes...\n", size);

    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dst);
        copied += bytes;

        int progress = (int)((copied * 100) / size);
        printf("\rProgress: %d%%", progress);
        fflush(stdout);
    }

    printf("\nCopy complete!\n");

    fclose(src);
    fclose(dst);

    return 1;
}

int main() {
    copy_file("large_file.dat", "backup.dat");
    return 0;
}
```

### 3. CSV File Parsing

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
    char city[50];
    float salary;
} Person;

void read_csv(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    Person p;
    char line[256];

    // Skip header
    fgets(line, sizeof(line), fp);

    printf("%-20s %-5s %-20s %-10s\n", "Name", "Age", "City", "Salary");
    printf("-----------------------------------------------------------\n");

    // Read data lines
    while (fgets(line, sizeof(line), fp) != NULL) {
        // Parse CSV line
        if (sscanf(line, "%[^,],%d,%[^,],%f", p.name, &p.age, p.city, &p.salary) == 4) {
            printf("%-20s %-5d %-20s $%.2f\n", p.name, p.age, p.city, p.salary);
        }
    }

    fclose(fp);
}

int main() {
    // Create sample CSV
    FILE *fp = fopen("people.csv", "w");
    fprintf(fp, "Name,Age,City,Salary\n");
    fprintf(fp, "Alice Johnson,28,New York,75000.50\n");
    fprintf(fp, "Bob Smith,35,Los Angeles,82000.75\n");
    fprintf(fp, "Charlie Brown,42,Chicago,68000.00\n");
    fclose(fp);

    // Read and display
    read_csv("people.csv");

    return 0;
}
```

### 4. Buffered vs Unbuffered I/O

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("output.txt", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Default: Fully buffered
    fprintf(fp, "Line 1\n");
    // Not written to file yet, still in buffer

    // Flush buffer manually
    fflush(fp);
    // Now written to file

    // Set custom buffer
    char buffer[1024];
    setvbuf(fp, buffer, _IOFBF, sizeof(buffer));  // Full buffering

    // Other buffering modes:
    // _IOLBF: Line buffered (flush on newline)
    // _IONBF: No buffering (immediate write)

    fprintf(fp, "Line 2\n");
    fprintf(fp, "Line 3\n");

    fclose(fp);  // Automatically flushes buffer

    return 0;
}
```

---

## Practice Exercises

### Exercise 1: Text File Statistics (Medium)
Write a program that analyzes a text file and reports:
- Total number of characters
- Total number of words
- Total number of lines
- Most frequent character
- Longest word

**Hint:** Use fgetc() and track state for word boundaries.

---

### Exercise 2: Binary Student Database (Hard)
Create a complete student database using binary files:
```c
typedef struct {
    int id;
    char name[50];
    int age;
    float gpa;
} Student;
```

Implement:
- `add_student()` - Append new student
- `search_by_id(int id)` - Find and display student
- `update_gpa(int id, float new_gpa)` - Update specific field
- `delete_student(int id)` - Mark as deleted (set id to -1)
- `list_all()` - Display all non-deleted students

---

### Exercise 3: File Encryption/Decryption (Medium)
Implement simple XOR encryption:
```c
void encrypt_file(const char *input, const char *output, char key);
void decrypt_file(const char *input, const char *output, char key);
```

For each byte: `encrypted = byte ^ key`

Decryption uses same operation (XOR is reversible).

---

### Exercise 4: Merge Sorted Files (Hard)
Write a function that merges two sorted files into a third sorted file:
```c
int merge_sorted_files(const char *file1, const char *file2, const char *output);
```

Input files contain integers (one per line). Output must be sorted.

---

### Exercise 5: CSV to Binary Converter (Hard)
Create converters between CSV and binary formats:
```c
int csv_to_binary(const char *csv_file, const char *bin_file);
int binary_to_csv(const char *bin_file, const char *csv_file);
```

Handle structures with multiple fields. Preserve data exactly.

---

### Exercise 6: File Splitting and Joining (Medium)
Implement file splitting:
```c
int split_file(const char *filename, long chunk_size);
// Creates filename.001, filename.002, etc.

int join_files(const char *pattern, const char *output);
// Joins filename.001, filename.002, etc. into output
```

Useful for transferring large files.

---

### Exercise 7: Transaction Log System (Advanced)
Implement a transaction logging system:
```c
typedef struct {
    time_t timestamp;
    char type[20];     // "INSERT", "UPDATE", "DELETE"
    char description[100];
} LogEntry;

void log_transaction(const char *type, const char *description);
void display_logs(time_t start_time, time_t end_time);
void search_logs(const char *keyword);
```

Log should be append-only binary file for efficiency.

---

### Exercise 8: Random Access Record Update (Hard)
Create a system to update records in the middle of a binary file without rewriting the entire file:

```c
typedef struct {
    int id;
    char status[20];
    double balance;
    time_t last_updated;
} Account;

Account* find_account(FILE *fp, int id);
int update_account(const char *filename, int id, const Account *new_data);
```

Use `fseek()` to position correctly and update in place.

---

## Summary

**Key Functions:**

| Function | Purpose | Returns |
|----------|---------|---------|
| `fopen()` | Open file | FILE* or NULL |
| `fclose()` | Close file | 0 or EOF |
| `fprintf()` | Formatted write | Characters written |
| `fscanf()` | Formatted read | Items read or EOF |
| `fgets()` | Read line | Pointer or NULL |
| `fputs()` | Write string | Non-negative or EOF |
| `fgetc()` | Read character | Character or EOF |
| `fputc()` | Write character | Character or EOF |
| `fread()` | Binary read | Items read |
| `fwrite()` | Binary write | Items written |
| `fseek()` | Set position | 0 or non-zero |
| `ftell()` | Get position | Position or -1L |
| `rewind()` | Reset to start | void |
| `feof()` | Check EOF | Non-zero if EOF |
| `ferror()` | Check error | Non-zero if error |

**Best Practices:**
1. Always check if `fopen()` returns NULL
2. Always `fclose()` opened files
3. Use binary mode for non-text data
4. Check return values of I/O functions
5. Use `fflush()` for critical data
6. Handle errors gracefully with perror() or strerror()
7. Use buffering appropriately for performance

**Common Pitfalls:**
- Forgetting to close files (resource leak)
- Not checking for errors
- Using wrong mode (text vs binary)
- Buffer overflow in fgets()
- Not checking fread/fwrite return values
- Mixing text and binary operations

Master file handling and you can persist data efficiently!
