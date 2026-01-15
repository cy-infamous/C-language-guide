# Command Line Arguments in C

## Table of Contents
1. [Introduction](#introduction)
2. [argc and argv](#argc-and-argv)
3. [Parsing Arguments](#parsing-arguments)
4. [Advanced Argument Handling](#advanced-argument-handling)
5. [Real-World Applications](#real-world-applications)
6. [Best Practices](#best-practices)
7. [Practice Exercises](#practice-exercises)

---

## Introduction

Command line arguments allow users to pass information to a program when it starts, making programs flexible and scriptable without recompilation.

### Why Command Line Arguments?

- **Flexibility**: Change behavior without modifying code
- **Automation**: Enable scripting and batch processing
- **User Control**: Let users specify files, options, parameters
- **Unix Philosophy**: Build composable, reusable tools

### Common Examples

```bash
# File operations
cp source.txt dest.txt
ls -la /home/user
cat file1.txt file2.txt

# Compilation
gcc -o program program.c -Wall -O2

# Utilities
grep "pattern" file.txt
curl -X POST https://api.example.com -d "data"
```

---

## argc and argv

### The main() Function with Arguments

```c
int main(int argc, char *argv[]) {
    // argc: Argument Count (number of arguments)
    // argv: Argument Vector (array of strings)
    return 0;
}
```

Alternative (equivalent) declarations:
```c
int main(int argc, char **argv)  // argv is pointer to pointer
int main(int argc, char *argv[]) // argv is array of pointers (preferred)
```

### Understanding argc and argv

**Example Command:**
```bash
./program arg1 arg2 arg3
```

**In Memory:**
```
argc = 4

argv[0] → "./program"  (program name)
argv[1] → "arg1"       (first argument)
argv[2] → "arg2"       (second argument)
argv[3] → "arg3"       (third argument)
argv[4] → NULL         (null terminator)
```

**Memory Diagram:**
```
argv → [ptr0][ptr1][ptr2][ptr3][NULL]
        ↓     ↓     ↓     ↓
      "./program" "arg1" "arg2" "arg3"
```

### 1. Basic Example

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Total arguments: %d\n\n", argc);

    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    return 0;
}
```

**Compile and Run:**
```bash
gcc basic.c -o basic
./basic hello world 123
```

**Output:**
```
Total arguments: 4

argv[0] = ./basic
argv[1] = hello
argv[2] = world
argv[3] = 123
```

### 2. Important Characteristics

**Always Have at Least One Argument:**
```c
int main(int argc, char *argv[]) {
    // argc is always >= 1
    // argv[0] always contains program name
    printf("Program name: %s\n", argv[0]);
    return 0;
}
```

**Arguments are Always Strings:**
```c
// Command: ./program 42 3.14
// argv[1] is "42" (string), not integer 42
// argv[2] is "3.14" (string), not float 3.14

int num = atoi(argv[1]);      // Convert to int
float val = atof(argv[2]);    // Convert to float
```

**Whitespace Separates Arguments:**
```bash
./program hello world        # 3 args: ./program, hello, world
./program "hello world"      # 2 args: ./program, "hello world"
./program hello\ world       # 2 args: ./program, "hello world"
```

---

## Parsing Arguments

### 1. Simple Argument Processing

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <name>\n", argv[0]);
        return 1;
    }

    printf("Hello, %s!\n", argv[1]);
    return 0;
}
```

### 2. Multiple Arguments

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <num1> <operator> <num2>\n", argv[0]);
        printf("Operators: +, -, *, /\n");
        return 1;
    }

    double num1 = atof(argv[1]);
    char op = argv[2][0];  // First character of operator string
    double num2 = atof(argv[3]);
    double result;

    switch (op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                printf("Error: Division by zero\n");
                return 1;
            }
            break;
        default:
            printf("Error: Unknown operator '%c'\n", op);
            return 1;
    }

    printf("%.2f %c %.2f = %.2f\n", num1, op, num2, result);
    return 0;
}
```

**Usage:**
```bash
$ ./calculator 10 + 5
10.00 + 5.00 = 15.00

$ ./calculator 20 / 4
20.00 / 4.00 = 5.00
```

### 3. Flags and Options

```c
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    bool verbose = false;
    bool help = false;
    char *input_file = NULL;
    char *output_file = NULL;

    // Parse arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            verbose = true;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            help = true;
        } else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            input_file = argv[++i];  // Next argument is the file
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            output_file = argv[++i];
        } else {
            printf("Unknown option: %s\n", argv[i]);
            return 1;
        }
    }

    if (help) {
        printf("Usage: %s [options]\n", argv[0]);
        printf("Options:\n");
        printf("  -v, --verbose    Enable verbose output\n");
        printf("  -h, --help       Show this help message\n");
        printf("  -i <file>        Input file\n");
        printf("  -o <file>        Output file\n");
        return 0;
    }

    printf("Verbose: %s\n", verbose ? "enabled" : "disabled");
    printf("Input file: %s\n", input_file ? input_file : "none");
    printf("Output file: %s\n", output_file ? output_file : "none");

    return 0;
}
```

**Usage:**
```bash
$ ./program -v -i input.txt -o output.txt
Verbose: enabled
Input file: input.txt
Output file: output.txt

$ ./program --help
Usage: ./program [options]
Options:
  -v, --verbose    Enable verbose output
  -h, --help       Show this help message
  -i <file>        Input file
  -o <file>        Output file
```

### 4. Using getopt() (POSIX Standard)

```c
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    int opt;
    bool verbose = false;
    char *input_file = NULL;
    char *output_file = NULL;

    // Parse options: -v -i <file> -o <file>
    // "vi:o:" means:
    //   v: no argument
    //   i: requires argument (indicated by :)
    //   o: requires argument
    while ((opt = getopt(argc, argv, "vi:o:h")) != -1) {
        switch (opt) {
            case 'v':
                verbose = true;
                break;
            case 'i':
                input_file = optarg;  // optarg contains the argument
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'h':
                printf("Usage: %s [-v] [-i input] [-o output]\n", argv[0]);
                return 0;
            case '?':  // Unknown option or missing argument
                return 1;
        }
    }

    // Remaining non-option arguments
    for (int i = optind; i < argc; i++) {
        printf("Extra argument: %s\n", argv[i]);
    }

    printf("Verbose: %s\n", verbose ? "yes" : "no");
    printf("Input: %s\n", input_file ? input_file : "stdin");
    printf("Output: %s\n", output_file ? output_file : "stdout");

    return 0;
}
```

### 5. Conversion Functions

```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

// Safe integer conversion
int parse_int(const char *str, int *result) {
    char *endptr;
    errno = 0;

    long val = strtol(str, &endptr, 10);

    // Check for errors
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        return 0;  // Overflow
    }

    if (endptr == str || *endptr != '\0') {
        return 0;  // No digits or extra characters
    }

    *result = (int)val;
    return 1;  // Success
}

// Safe float conversion
int parse_float(const char *str, float *result) {
    char *endptr;
    errno = 0;

    float val = strtof(str, &endptr);

    if (errno == ERANGE) {
        return 0;  // Overflow
    }

    if (endptr == str || *endptr != '\0') {
        return 0;  // No digits or extra characters
    }

    *result = val;
    return 1;  // Success
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <integer> <float>\n", argv[0]);
        return 1;
    }

    int num;
    float val;

    if (!parse_int(argv[1], &num)) {
        printf("Error: '%s' is not a valid integer\n", argv[1]);
        return 1;
    }

    if (!parse_float(argv[2], &val)) {
        printf("Error: '%s' is not a valid float\n", argv[2]);
        return 1;
    }

    printf("Integer: %d\n", num);
    printf("Float: %.2f\n", val);

    return 0;
}
```

---

## Advanced Argument Handling

### 1. Subcommands (Git-style)

```c
#include <stdio.h>
#include <string.h>

void cmd_add(int argc, char *argv[]) {
    printf("Add command\n");
    for (int i = 0; i < argc; i++) {
        printf("  %s\n", argv[i]);
    }
}

void cmd_commit(int argc, char *argv[]) {
    printf("Commit command\n");
    char *message = NULL;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
            message = argv[++i];
        }
    }

    printf("Message: %s\n", message ? message : "(none)");
}

void cmd_push(int argc, char *argv[]) {
    printf("Push command\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <command> [options]\n", argv[0]);
        printf("Commands: add, commit, push\n");
        return 1;
    }

    char *command = argv[1];

    // Pass remaining arguments to subcommand
    int sub_argc = argc - 2;
    char **sub_argv = &argv[2];

    if (strcmp(command, "add") == 0) {
        cmd_add(sub_argc, sub_argv);
    } else if (strcmp(command, "commit") == 0) {
        cmd_commit(sub_argc, sub_argv);
    } else if (strcmp(command, "push") == 0) {
        cmd_push(sub_argc, sub_argv);
    } else {
        printf("Unknown command: %s\n", command);
        return 1;
    }

    return 0;
}
```

**Usage:**
```bash
$ ./git add file1.c file2.c
Add command
  file1.c
  file2.c

$ ./git commit -m "Initial commit"
Commit command
Message: Initial commit
```

### 2. Long Options (getopt_long)

```c
#include <stdio.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
    static struct option long_options[] = {
        {"verbose", no_argument,       0, 'v'},
        {"input",   required_argument, 0, 'i'},
        {"output",  required_argument, 0, 'o'},
        {"help",    no_argument,       0, 'h'},
        {"version", no_argument,       0, 'V'},
        {0, 0, 0, 0}  // Terminator
    };

    int opt;
    int option_index = 0;

    while ((opt = getopt_long(argc, argv, "vi:o:hV", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'v':
                printf("Verbose mode enabled\n");
                break;
            case 'i':
                printf("Input file: %s\n", optarg);
                break;
            case 'o':
                printf("Output file: %s\n", optarg);
                break;
            case 'h':
                printf("Help message\n");
                break;
            case 'V':
                printf("Version 1.0\n");
                break;
            case '?':
                return 1;
        }
    }

    return 0;
}
```

**Usage:**
```bash
$ ./program --verbose --input=data.txt --output=result.txt
$ ./program -v -i data.txt -o result.txt
$ ./program --version
```

### 3. Argument Validation

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int file_exists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

int is_valid_mode(const char *mode) {
    const char *valid_modes[] = {"read", "write", "append", NULL};
    for (int i = 0; valid_modes[i] != NULL; i++) {
        if (strcmp(mode, valid_modes[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file> <mode>\n", argv[0]);
        fprintf(stderr, "Modes: read, write, append\n");
        return 1;
    }

    char *filename = argv[1];
    char *mode = argv[2];

    // Validate mode
    if (!is_valid_mode(mode)) {
        fprintf(stderr, "Error: Invalid mode '%s'\n", mode);
        fprintf(stderr, "Valid modes: read, write, append\n");
        return 1;
    }

    // Check file existence for read mode
    if (strcmp(mode, "read") == 0 && !file_exists(filename)) {
        fprintf(stderr, "Error: File '%s' does not exist\n", filename);
        return 1;
    }

    printf("Opening file '%s' in %s mode\n", filename, mode);

    return 0;
}
```

---

## Real-World Applications

### 1. File Concatenation (cat-like)

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void cat_file(const char *filename, bool show_line_numbers) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror(filename);
        return;
    }

    char line[1024];
    int line_num = 1;

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (show_line_numbers) {
            printf("%4d  %s", line_num++, line);
        } else {
            printf("%s", line);
        }
    }

    fclose(fp);
}

int main(int argc, char *argv[]) {
    bool show_line_numbers = false;
    int file_start = 1;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-n] <file1> [file2 ...]\n", argv[0]);
        return 1;
    }

    // Check for -n flag
    if (strcmp(argv[1], "-n") == 0) {
        show_line_numbers = true;
        file_start = 2;
    }

    if (file_start >= argc) {
        fprintf(stderr, "Error: No files specified\n");
        return 1;
    }

    // Process each file
    for (int i = file_start; i < argc; i++) {
        cat_file(argv[i], show_line_numbers);
    }

    return 0;
}
```

### 2. Word Counter (wc-like)

```c
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct {
    int lines;
    int words;
    int chars;
} FileStats;

FileStats count_file(const char *filename) {
    FileStats stats = {0, 0, 0};
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        perror(filename);
        return stats;
    }

    int ch;
    bool in_word = false;

    while ((ch = fgetc(fp)) != EOF) {
        stats.chars++;

        if (ch == '\n') {
            stats.lines++;
        }

        if (isspace(ch)) {
            in_word = false;
        } else if (!in_word) {
            in_word = true;
            stats.words++;
        }
    }

    fclose(fp);
    return stats;
}

int main(int argc, char *argv[]) {
    bool show_lines = true;
    bool show_words = true;
    bool show_chars = true;

    int file_start = 1;

    // Parse options
    for (int i = 1; i < argc && argv[i][0] == '-'; i++) {
        show_lines = show_words = show_chars = false;

        for (int j = 1; argv[i][j] != '\0'; j++) {
            if (argv[i][j] == 'l') show_lines = true;
            else if (argv[i][j] == 'w') show_words = true;
            else if (argv[i][j] == 'c') show_chars = true;
        }
        file_start++;
    }

    if (!show_lines && !show_words && !show_chars) {
        show_lines = show_words = show_chars = true;
    }

    if (file_start >= argc) {
        fprintf(stderr, "Usage: %s [-lwc] <file1> [file2 ...]\n", argv[0]);
        return 1;
    }

    FileStats total = {0, 0, 0};

    for (int i = file_start; i < argc; i++) {
        FileStats stats = count_file(argv[i]);

        if (show_lines) printf("%8d ", stats.lines);
        if (show_words) printf("%8d ", stats.words);
        if (show_chars) printf("%8d ", stats.chars);
        printf("%s\n", argv[i]);

        total.lines += stats.lines;
        total.words += stats.words;
        total.chars += stats.chars;
    }

    if (argc - file_start > 1) {
        if (show_lines) printf("%8d ", total.lines);
        if (show_words) printf("%8d ", total.words);
        if (show_chars) printf("%8d ", total.chars);
        printf("total\n");
    }

    return 0;
}
```

### 3. File Search (grep-like)

```c
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void search_file(const char *filename, const char *pattern, bool show_line_numbers) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror(filename);
        return;
    }

    char line[1024];
    int line_num = 1;

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, pattern) != NULL) {
            if (show_line_numbers) {
                printf("%s:%d:%s", filename, line_num, line);
            } else {
                printf("%s:%s", filename, line);
            }
        }
        line_num++;
    }

    fclose(fp);
}

int main(int argc, char *argv[]) {
    bool show_line_numbers = false;
    int pattern_idx = 1;
    int file_start = 2;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s [-n] <pattern> <file1> [file2 ...]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-n") == 0) {
        show_line_numbers = true;
        pattern_idx = 2;
        file_start = 3;
    }

    if (file_start >= argc) {
        fprintf(stderr, "Error: No files specified\n");
        return 1;
    }

    char *pattern = argv[pattern_idx];

    for (int i = file_start; i < argc; i++) {
        search_file(argv[i], pattern, show_line_numbers);
    }

    return 0;
}
```

---

## Best Practices

### 1. Always Validate Input

```c
if (argc < 2) {
    fprintf(stderr, "Error: Missing arguments\n");
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    return EXIT_FAILURE;
}
```

### 2. Provide Clear Usage Messages

```c
void print_usage(const char *program_name) {
    printf("Usage: %s [OPTIONS] <input_file>\n\n", program_name);
    printf("Options:\n");
    printf("  -v, --verbose       Enable verbose output\n");
    printf("  -o, --output FILE   Specify output file\n");
    printf("  -h, --help          Display this help message\n");
    printf("  -V, --version       Show version information\n");
    printf("\nExamples:\n");
    printf("  %s input.txt\n", program_name);
    printf("  %s -v -o output.txt input.txt\n", program_name);
}
```

### 3. Use stderr for Errors

```c
if (error_condition) {
    fprintf(stderr, "Error: %s\n", error_message);
    return EXIT_FAILURE;
}
```

### 4. Support Standard Input

```c
FILE *input = stdin;

if (argc > 1 && strcmp(argv[1], "-") != 0) {
    input = fopen(argv[1], "r");
    if (input == NULL) {
        perror(argv[1]);
        return 1;
    }
}

// Process input
// ...

if (input != stdin) {
    fclose(input);
}
```

### 5. Handle Edge Cases

```c
// Empty arguments
if (argc > 1 && argv[1][0] == '\0') {
    fprintf(stderr, "Error: Empty argument\n");
    return 1;
}

// Extremely long arguments
if (strlen(argv[1]) > MAX_LENGTH) {
    fprintf(stderr, "Error: Argument too long\n");
    return 1;
}

// Special characters
if (strchr(argv[1], '\0') != NULL) {
    // Handle null characters
}
```

---

## Practice Exercises

### Exercise 1: Temperature Converter (Easy)
Create a program that converts temperature between Celsius, Fahrenheit, and Kelvin:
```bash
$ ./temp 100 C F    # Convert 100°C to Fahrenheit
$ ./temp 32 F C     # Convert 32°F to Celsius
$ ./temp -t K 273   # Alternative syntax
```

---

### Exercise 2: File Backup Utility (Medium)
Create a backup utility:
```bash
$ ./backup file.txt              # Creates file.txt.bak
$ ./backup -s .backup file.txt   # Creates file.txt.backup
$ ./backup -d backups/ *.txt     # Backs up multiple files to directory
```

---

### Exercise 3: Simple Task Manager (Hard)
Create a command-line task manager:
```bash
$ ./task add "Buy groceries"
$ ./task add "Call dentist" --priority high
$ ./task list
$ ./task list --status pending
$ ./task complete 1
$ ./task delete 2
```

Store tasks in a file, support priorities, status, due dates.

---

### Exercise 4: Log Analyzer (Hard)
Create a log file analyzer:
```bash
$ ./logparse access.log --errors        # Show only errors
$ ./logparse access.log --top 10        # Top 10 IPs
$ ./logparse access.log --date 2026-01-14
$ ./logparse access.log --status 404    # Filter by status code
```

---

### Exercise 5: CSV Processor (Medium)
Create a CSV manipulation tool:
```bash
$ ./csv data.csv --column name          # Extract column
$ ./csv data.csv --filter "age>30"      # Filter rows
$ ./csv data.csv --sort age             # Sort by column
$ ./csv data.csv --stats age            # Calculate statistics
```

---

### Exercise 6: File Encryption (Advanced)
Create a file encryption/decryption tool:
```bash
$ ./crypt -e -k password input.txt output.enc   # Encrypt
$ ./crypt -d -k password input.enc output.txt   # Decrypt
$ ./crypt --encrypt --key-file key.txt file.txt # Use key file
```

Implement simple XOR or Caesar cipher.

---

### Exercise 7: System Monitor (Advanced)
Create a system monitoring tool:
```bash
$ ./monitor --cpu              # Show CPU usage
$ ./monitor --memory           # Show memory usage
$ ./monitor --disk /home       # Show disk usage
$ ./monitor --all --interval 5 # Refresh every 5 seconds
```

Read from /proc filesystem (Linux) or use system calls.

---

### Exercise 8: Build Tool (Hard)
Create a simple build automation tool:
```bash
$ ./build                      # Build default target
$ ./build clean               # Clean build artifacts
$ ./build --target release    # Build release version
$ ./build --verbose --jobs 4  # Verbose with parallel jobs
```

Read configuration from a file, execute build commands.

---

## Summary

**Key Concepts:**

1. **argc**: Number of command line arguments (including program name)
2. **argv**: Array of argument strings (null-terminated)
3. **argv[0]**: Always program name
4. **Arguments are strings**: Must convert to other types

**Common Patterns:**

- Simple flag checking: `strcmp(argv[i], "-v") == 0`
- Value extraction: `argv[++i]` after flag
- File processing: Loop through remaining args
- Subcommands: Pass subset of argv to function

**Standard Functions:**

| Function | Purpose |
|----------|---------|
| `atoi()` | String to int (unsafe) |
| `atof()` | String to float (unsafe) |
| `strtol()` | String to long (safe) |
| `strtof()` | String to float (safe) |
| `getopt()` | Parse short options |
| `getopt_long()` | Parse long options |

**Best Practices:**
1. Always validate argument count
2. Provide helpful usage messages
3. Use stderr for errors
4. Support --help and --version
5. Follow Unix conventions (-v, --verbose, etc.)
6. Handle stdin with "-" argument
7. Return EXIT_SUCCESS (0) on success, EXIT_FAILURE (1) on error

**Common Pitfalls:**
- Not checking argc before accessing argv
- Forgetting argv[0] is program name
- Not converting string arguments
- Poor error messages
- Not supporting standard conventions

Master command line arguments and you'll build professional, user-friendly tools!
