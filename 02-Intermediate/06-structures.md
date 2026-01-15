# Structures in C

## Table of Contents
1. [Introduction to Structures](#introduction-to-structures)
2. [Structure Basics](#structure-basics)
3. [Accessing Structure Members](#accessing-structure-members)
4. [Nested Structures](#nested-structures)
5. [Typedef with Structures](#typedef-with-structures)
6. [Structures and Functions](#structures-and-functions)
7. [Array of Structures](#array-of-structures)
8. [Real-World Applications](#real-world-applications)
9. [Practice Exercises](#practice-exercises)

---

## Introduction to Structures

A structure (struct) is a user-defined data type that groups variables of different types under a single name. Structures enable you to:
- Create complex data types
- Model real-world entities
- Organize related data together
- Build sophisticated data structures

### Why Use Structures?

**Without Structures:**
```c
// Student data scattered across multiple variables
char name1[50] = "Alice";
int rollNo1 = 101;
float gpa1 = 3.8;

char name2[50] = "Bob";
int rollNo2 = 102;
float gpa2 = 3.5;
// Difficult to manage and pass to functions
```

**With Structures:**
```c
struct Student {
    char name[50];
    int rollNo;
    float gpa;
};

struct Student student1 = {"Alice", 101, 3.8};
struct Student student2 = {"Bob", 102, 3.5};
// Easy to manage and pass as a single unit
```

---

## Structure Basics

### Structure Definition

**Syntax:**
```c
struct structure_name {
    data_type member1;
    data_type member2;
    // ... more members
};
```

### Declaring Structure Variables

**Method 1: Definition and Declaration Separate**
```c
#include <stdio.h>

// Structure definition
struct Point {
    int x;
    int y;
};

int main() {
    // Variable declaration
    struct Point p1;
    struct Point p2;

    return 0;
}
```

**Method 2: Declaration with Definition**
```c
#include <stdio.h>

struct Point {
    int x;
    int y;
} p1, p2;  // Declare variables during definition

int main() {
    return 0;
}
```

**Method 3: Anonymous Structure**
```c
#include <stdio.h>

struct {
    int x;
    int y;
} p1, p2;  // Can only declare variables here

int main() {
    // Cannot create more variables of this type
    return 0;
}
```

### Structure Initialization

```c
#include <stdio.h>

struct Student {
    char name[50];
    int rollNo;
    float gpa;
};

int main() {
    // Method 1: Initialize during declaration
    struct Student s1 = {"Alice", 101, 3.8};

    // Method 2: Initialize with designated initializers (C99)
    struct Student s2 = {
        .name = "Bob",
        .rollNo = 102,
        .gpa = 3.5
    };

    // Method 3: Partial initialization (rest = 0)
    struct Student s3 = {"Charlie"};  // rollNo=0, gpa=0.0

    // Method 4: Member-by-member assignment
    struct Student s4;
    strcpy(s4.name, "Diana");
    s4.rollNo = 104;
    s4.gpa = 3.9;

    printf("Student 1: %s, %d, %.2f\n", s1.name, s1.rollNo, s1.gpa);
    printf("Student 2: %s, %d, %.2f\n", s2.name, s2.rollNo, s2.gpa);

    return 0;
}
/* Output:
Student 1: Alice, 101, 3.80
Student 2: Bob, 102, 3.50
*/
```

### Memory Layout of Structures

**Example Structure:**
```c
struct Student {
    char name[50];   // 50 bytes
    int rollNo;      // 4 bytes
    float gpa;       // 4 bytes
};
```

**Memory Diagram:**
```
Without Padding (Theoretical):
+-------------------+----------+--------+
|   name (50 bytes) | rollNo(4)| gpa(4) |
+-------------------+----------+--------+
Total: 58 bytes

With Padding (Actual - depends on alignment):
+-------------------+----------+--------+--+
|   name (50 bytes) | padding  |rollNo(4)| gpa(4) |
+-------------------+----------+--------+--+
                      2 bytes
Total: 60 bytes (aligned to 4-byte boundary)

Address layout for struct Student s1:
&s1        = 1000
&s1.name   = 1000
&s1.rollNo = 1052 (might be padded)
&s1.gpa    = 1056
```

### Size of Structure

```c
#include <stdio.h>

struct Example {
    char c;      // 1 byte
    int i;       // 4 bytes
    float f;     // 4 bytes
};

int main() {
    struct Example e;

    printf("Size of structure: %zu bytes\n", sizeof(struct Example));
    printf("Size of char: %zu bytes\n", sizeof(e.c));
    printf("Size of int: %zu bytes\n", sizeof(e.i));
    printf("Size of float: %zu bytes\n", sizeof(e.f));

    printf("\nMember offsets:\n");
    printf("Offset of c: %zu\n", offsetof(struct Example, c));
    printf("Offset of i: %zu\n", offsetof(struct Example, i));
    printf("Offset of f: %zu\n", offsetof(struct Example, f));

    return 0;
}
/* Output (typical):
Size of structure: 12 bytes
Size of char: 1 bytes
Size of int: 4 bytes
Size of float: 4 bytes

Member offsets:
Offset of c: 0
Offset of i: 4
Offset of f: 8
*/
```

**Memory Alignment Visualization:**
```
struct Example e:

Byte:   0    1    2    3    4    5    6    7    8    9   10   11
      +----+----+----+----+----+----+----+----+----+----+----+----+
      | c  |  padding  |      i      |      f      |
      +----+----+----+----+----+----+----+----+----+----+----+----+

c occupies 1 byte, but i needs 4-byte alignment, so 3 bytes padding added
Total: 12 bytes (not 9 bytes)
```

---

## Accessing Structure Members

### Dot Operator (.)

Used to access members of structure variables.

```c
#include <stdio.h>
#include <string.h>

struct Book {
    char title[100];
    char author[50];
    int pages;
    float price;
};

int main() {
    struct Book book1;

    // Assign values
    strcpy(book1.title, "C Programming");
    strcpy(book1.author, "Dennis Ritchie");
    book1.pages = 350;
    book1.price = 29.99;

    // Access and display values
    printf("Book Information:\n");
    printf("Title: %s\n", book1.title);
    printf("Author: %s\n", book1.author);
    printf("Pages: %d\n", book1.pages);
    printf("Price: $%.2f\n", book1.price);

    return 0;
}
/* Output:
Book Information:
Title: C Programming
Author: Dennis Ritchie
Pages: 350
Price: $29.99
*/
```

### Arrow Operator (->)

Used to access members through structure pointers.

```c
#include <stdio.h>
#include <string.h>

struct Employee {
    char name[50];
    int id;
    float salary;
};

int main() {
    struct Employee emp = {"John Doe", 1001, 50000.0};
    struct Employee *ptr = &emp;

    // Both methods are equivalent:
    printf("Using dot operator:\n");
    printf("Name: %s\n", emp.name);
    printf("ID: %d\n", emp.id);

    printf("\nUsing arrow operator:\n");
    printf("Name: %s\n", ptr->name);
    printf("ID: %d\n", ptr->id);

    // ptr->member is equivalent to (*ptr).member
    printf("\nUsing (*ptr).member:\n");
    printf("Name: %s\n", (*ptr).name);
    printf("ID: %d\n", (*ptr).id);

    return 0;
}
```

**Memory Diagram:**
```
Stack Memory:
Address: 1000
        +-------------+
emp     | name: "John"|
        | id: 1001    |
        | salary:50000|
        +-------------+

Address: 2000
        +------+
ptr     | 1000 | (stores address of emp)
        +------+

Access methods:
emp.name      - Direct access
ptr->name     - Access through pointer
(*ptr).name   - Dereference pointer, then access
```

---

## Nested Structures

Structures can contain other structures as members.

### Basic Nested Structure

```c
#include <stdio.h>
#include <string.h>

struct Date {
    int day;
    int month;
    int year;
};

struct Employee {
    char name[50];
    int id;
    struct Date joinDate;  // Nested structure
    float salary;
};

int main() {
    struct Employee emp1;

    strcpy(emp1.name, "Alice Smith");
    emp1.id = 2001;
    emp1.joinDate.day = 15;
    emp1.joinDate.month = 6;
    emp1.joinDate.year = 2020;
    emp1.salary = 60000.0;

    printf("Employee Details:\n");
    printf("Name: %s\n", emp1.name);
    printf("ID: %d\n", emp1.id);
    printf("Join Date: %02d/%02d/%d\n",
           emp1.joinDate.day,
           emp1.joinDate.month,
           emp1.joinDate.year);
    printf("Salary: $%.2f\n", emp1.salary);

    return 0;
}
/* Output:
Employee Details:
Name: Alice Smith
ID: 2001
Join Date: 15/06/2020
Salary: $60000.00
*/
```

### Complex Nested Structure

```c
#include <stdio.h>
#include <string.h>

struct Address {
    char street[100];
    char city[50];
    char state[50];
    int zipCode;
};

struct Contact {
    char phone[15];
    char email[50];
};

struct Person {
    char name[50];
    int age;
    struct Address address;
    struct Contact contact;
};

int main() {
    struct Person person1 = {
        "John Doe",
        30,
        {"123 Main St", "New York", "NY", 10001},
        {"555-1234", "john@example.com"}
    };

    printf("Person Information:\n");
    printf("Name: %s\n", person1.name);
    printf("Age: %d\n", person1.age);
    printf("Address: %s, %s, %s %d\n",
           person1.address.street,
           person1.address.city,
           person1.address.state,
           person1.address.zipCode);
    printf("Phone: %s\n", person1.contact.phone);
    printf("Email: %s\n", person1.contact.email);

    return 0;
}
/* Output:
Person Information:
Name: John Doe
Age: 30
Address: 123 Main St, New York, NY 10001
Phone: 555-1234
Email: john@example.com
*/
```

**Memory Layout:**
```
struct Person person1:

+------------------+
| name[50]         |
+------------------+
| age              |
+------------------+
| address:         |
|   street[100]    |
|   city[50]       |
|   state[50]      |
|   zipCode        |
+------------------+
| contact:         |
|   phone[15]      |
|   email[50]      |
+------------------+

Access: person1.address.city
        person1.contact.email
```

---

## Typedef with Structures

`typedef` creates an alias for a data type, making code cleaner and more readable.

### Without Typedef

```c
struct Student {
    char name[50];
    int rollNo;
};

struct Student s1;  // Must use 'struct' keyword
```

### With Typedef

**Method 1: Separate typedef**
```c
struct Student {
    char name[50];
    int rollNo;
};

typedef struct Student Student;

Student s1;  // No 'struct' keyword needed
```

**Method 2: Combined typedef (Common)**
```c
typedef struct {
    char name[50];
    int rollNo;
} Student;

Student s1;  // Cleaner syntax
```

**Method 3: Named struct with typedef**
```c
typedef struct Student {
    char name[50];
    int rollNo;
} Student;

// Can use both:
struct Student s1;  // With struct keyword
Student s2;         // Without struct keyword
```

### Example with Typedef

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    char title[100];
    char author[50];
    int year;
    float price;
} Book;

void printBook(Book b) {
    printf("Title: %s\n", b.title);
    printf("Author: %s\n", b.author);
    printf("Year: %d\n", b.year);
    printf("Price: $%.2f\n", b.price);
}

int main() {
    Book book1 = {"The C Programming Language", "K&R", 1988, 45.99};
    Book book2;

    strcpy(book2.title, "C Primer Plus");
    strcpy(book2.author, "Stephen Prata");
    book2.year = 2013;
    book2.price = 39.99;

    printf("Book 1:\n");
    printBook(book1);

    printf("\nBook 2:\n");
    printBook(book2);

    return 0;
}
```

---

## Structures and Functions

Structures can be passed to functions in three ways:
1. **Pass by value** (copy entire structure)
2. **Pass by reference** (using pointers)
3. **Return structure** from function

### Pass by Value

```c
#include <stdio.h>

typedef struct {
    int x;
    int y;
} Point;

void displayPoint(Point p) {
    printf("Point: (%d, %d)\n", p.x, p.y);
}

void tryModify(Point p) {
    p.x = 100;  // Modifies copy, not original
    printf("Inside function: (%d, %d)\n", p.x, p.y);
}

int main() {
    Point p1 = {10, 20};

    displayPoint(p1);

    tryModify(p1);
    printf("After function: (%d, %d)\n", p1.x, p1.y);
    // p1 unchanged because copy was modified

    return 0;
}
/* Output:
Point: (10, 20)
Inside function: (100, 20)
After function: (10, 20)
*/
```

**Memory Diagram:**
```
main():                 tryModify():
p1 (10, 20)            p (10, 20) [copy]
Address: 1000          Address: 2000

When p.x = 100 inside function:
p1 (10, 20)            p (100, 20)
[unchanged]            [modified copy]
```

### Pass by Reference (Pointer)

```c
#include <stdio.h>

typedef struct {
    int x;
    int y;
} Point;

void displayPoint(Point *p) {
    printf("Point: (%d, %d)\n", p->x, p->y);
}

void modifyPoint(Point *p) {
    p->x = 100;  // Modifies original
    p->y = 200;
    printf("Inside function: (%d, %d)\n", p->x, p->y);
}

int main() {
    Point p1 = {10, 20};

    displayPoint(&p1);

    modifyPoint(&p1);
    printf("After function: (%d, %d)\n", p1.x, p1.y);
    // p1 modified because pointer was passed

    return 0;
}
/* Output:
Point: (10, 20)
Inside function: (100, 200)
After function: (100, 200)
*/
```

### Returning Structure

```c
#include <stdio.h>

typedef struct {
    int x;
    int y;
} Point;

Point createPoint(int x, int y) {
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

Point addPoints(Point p1, Point p2) {
    Point result;
    result.x = p1.x + p2.x;
    result.y = p1.y + p2.y;
    return result;
}

int main() {
    Point p1 = createPoint(10, 20);
    Point p2 = createPoint(30, 40);

    printf("Point 1: (%d, %d)\n", p1.x, p1.y);
    printf("Point 2: (%d, %d)\n", p2.x, p2.y);

    Point sum = addPoints(p1, p2);
    printf("Sum: (%d, %d)\n", sum.x, sum.y);

    return 0;
}
/* Output:
Point 1: (10, 20)
Point 2: (30, 40)
Sum: (40, 60)
*/
```

### Comparison: Pass by Value vs Pass by Reference

| Aspect | Pass by Value | Pass by Reference |
|--------|---------------|-------------------|
| Memory | Creates copy | Uses original |
| Speed | Slower (large structs) | Faster |
| Safety | Cannot modify original | Can modify original |
| Use when | Small structs, read-only | Large structs, need modification |

---

## Array of Structures

An array of structures stores multiple structure variables.

### Basic Array of Structures

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    char name[50];
    int rollNo;
    float marks;
} Student;

int main() {
    Student class[3];

    // Initialize students
    strcpy(class[0].name, "Alice");
    class[0].rollNo = 101;
    class[0].marks = 85.5;

    strcpy(class[1].name, "Bob");
    class[1].rollNo = 102;
    class[1].marks = 92.0;

    strcpy(class[2].name, "Charlie");
    class[2].rollNo = 103;
    class[2].marks = 78.5;

    // Display all students
    printf("Student Records:\n");
    printf("%-15s %-10s %s\n", "Name", "Roll No", "Marks");
    printf("----------------------------------------\n");

    for(int i = 0; i < 3; i++) {
        printf("%-15s %-10d %.2f\n",
               class[i].name,
               class[i].rollNo,
               class[i].marks);
    }

    return 0;
}
/* Output:
Student Records:
Name            Roll No    Marks
----------------------------------------
Alice           101        85.50
Bob             102        92.00
Charlie         103        78.50
*/
```

**Memory Layout:**
```
Array: Student class[3]

Address: 1000        1100        1200
       +----------+----------+----------+
       | class[0] | class[1] | class[2] |
       |          |          |          |
       | Alice    | Bob      | Charlie  |
       | 101      | 102      | 103      |
       | 85.5     | 92.0     | 78.5     |
       +----------+----------+----------+

Each element is approximately 60-70 bytes
(depending on padding)
```

### Initializing Array of Structures

```c
#include <stdio.h>

typedef struct {
    char name[30];
    int age;
    float salary;
} Employee;

int main() {
    Employee employees[3] = {
        {"John Doe", 30, 50000.0},
        {"Jane Smith", 28, 55000.0},
        {"Bob Johnson", 35, 60000.0}
    };

    printf("Employee List:\n");
    for(int i = 0; i < 3; i++) {
        printf("%d. %s, Age: %d, Salary: $%.2f\n",
               i + 1,
               employees[i].name,
               employees[i].age,
               employees[i].salary);
    }

    return 0;
}
/* Output:
Employee List:
1. John Doe, Age: 30, Salary: $50000.00
2. Jane Smith, Age: 28, Salary: $55000.00
3. Bob Johnson, Age: 35, Salary: $60000.00
*/
```

### Operations on Array of Structures

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    char name[50];
    int id;
    float score;
} Player;

void sortByScore(Player players[], int size) {
    Player temp;
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(players[j].score < players[j + 1].score) {
                temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
}

Player* findPlayer(Player players[], int size, int id) {
    for(int i = 0; i < size; i++) {
        if(players[i].id == id) {
            return &players[i];
        }
    }
    return NULL;
}

float calculateAverage(Player players[], int size) {
    float sum = 0;
    for(int i = 0; i < size; i++) {
        sum += players[i].score;
    }
    return sum / size;
}

int main() {
    Player players[4] = {
        {"Alice", 101, 95.5},
        {"Bob", 102, 87.0},
        {"Charlie", 103, 92.5},
        {"Diana", 104, 89.0}
    };

    printf("Original List:\n");
    for(int i = 0; i < 4; i++) {
        printf("%s: %.2f\n", players[i].name, players[i].score);
    }

    sortByScore(players, 4);

    printf("\nSorted by Score (Descending):\n");
    for(int i = 0; i < 4; i++) {
        printf("%d. %s: %.2f\n",
               i + 1, players[i].name, players[i].score);
    }

    printf("\nAverage Score: %.2f\n", calculateAverage(players, 4));

    Player *found = findPlayer(players, 4, 103);
    if(found != NULL) {
        printf("Found Player ID 103: %s, Score: %.2f\n",
               found->name, found->score);
    }

    return 0;
}
/* Output:
Original List:
Alice: 95.50
Bob: 87.00
Charlie: 92.50
Diana: 89.00

Sorted by Score (Descending):
1. Alice: 95.50
2. Charlie: 92.50
3. Diana: 89.00
4. Bob: 87.00

Average Score: 91.00
Found Player ID 103: Charlie, Score: 92.50
*/
```

---

## Real-World Applications

### 1. Student Management System

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    char name[50];
    int rollNo;
    Date dob;
    float marks[5];  // 5 subjects
    float average;
} Student;

void calculateAverage(Student *s) {
    float sum = 0;
    for(int i = 0; i < 5; i++) {
        sum += s->marks[i];
    }
    s->average = sum / 5;
}

void displayStudent(Student s) {
    printf("\n--- Student Details ---\n");
    printf("Name: %s\n", s.name);
    printf("Roll No: %d\n", s.rollNo);
    printf("DOB: %02d/%02d/%d\n", s.dob.day, s.dob.month, s.dob.year);
    printf("Marks: ");
    for(int i = 0; i < 5; i++) {
        printf("%.2f ", s.marks[i]);
    }
    printf("\nAverage: %.2f\n", s.average);
}

int main() {
    Student s1;

    strcpy(s1.name, "Alice Johnson");
    s1.rollNo = 101;
    s1.dob.day = 15;
    s1.dob.month = 8;
    s1.dob.year = 2005;

    float marks[] = {85.5, 92.0, 88.5, 90.0, 87.5};
    for(int i = 0; i < 5; i++) {
        s1.marks[i] = marks[i];
    }

    calculateAverage(&s1);
    displayStudent(s1);

    return 0;
}
/* Output:
--- Student Details ---
Name: Alice Johnson
Roll No: 101
DOB: 15/08/2005
Marks: 85.50 92.00 88.50 90.00 87.50
Average: 88.70
*/
```

### 2. Library Book Management

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    char isbn[20];
    char title[100];
    char author[50];
    int year;
    int isAvailable;  // 1 = available, 0 = borrowed
} Book;

typedef struct {
    Book books[100];
    int count;
} Library;

void addBook(Library *lib, Book b) {
    if(lib->count < 100) {
        lib->books[lib->count] = b;
        lib->count++;
        printf("Book added successfully!\n");
    } else {
        printf("Library is full!\n");
    }
}

void displayBooks(Library lib) {
    printf("\n%-20s %-40s %-30s %6s %s\n",
           "ISBN", "Title", "Author", "Year", "Status");
    printf("--------------------------------------------------"
           "----------------------------------------------\n");

    for(int i = 0; i < lib.count; i++) {
        printf("%-20s %-40s %-30s %6d %s\n",
               lib.books[i].isbn,
               lib.books[i].title,
               lib.books[i].author,
               lib.books[i].year,
               lib.books[i].isAvailable ? "Available" : "Borrowed");
    }
}

Book* searchByISBN(Library *lib, char isbn[]) {
    for(int i = 0; i < lib->count; i++) {
        if(strcmp(lib->books[i].isbn, isbn) == 0) {
            return &lib->books[i];
        }
    }
    return NULL;
}

int main() {
    Library library = {.count = 0};

    Book b1 = {"978-0-13-110362-7", "The C Programming Language",
               "K&R", 1988, 1};
    Book b2 = {"978-0-13-467747-5", "C Primer Plus",
               "Stephen Prata", 2013, 1};
    Book b3 = {"978-1-49-192214-7", "C Programming Absolute Beginner",
               "Perry & Miller", 2013, 0};

    addBook(&library, b1);
    addBook(&library, b2);
    addBook(&library, b3);

    displayBooks(library);

    printf("\nSearching for ISBN: 978-0-13-110362-7\n");
    Book *found = searchByISBN(&library, "978-0-13-110362-7");
    if(found != NULL) {
        printf("Found: %s by %s\n", found->title, found->author);
    } else {
        printf("Book not found!\n");
    }

    return 0;
}
```

### 3. Bank Account System

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    int accountNo;
    char name[50];
    char type[20];  // Savings or Checking
    float balance;
} Account;

void deposit(Account *acc, float amount) {
    if(amount > 0) {
        acc->balance += amount;
        printf("Deposited $%.2f. New balance: $%.2f\n",
               amount, acc->balance);
    } else {
        printf("Invalid amount!\n");
    }
}

void withdraw(Account *acc, float amount) {
    if(amount > 0 && amount <= acc->balance) {
        acc->balance -= amount;
        printf("Withdrew $%.2f. New balance: $%.2f\n",
               amount, acc->balance);
    } else if(amount > acc->balance) {
        printf("Insufficient funds!\n");
    } else {
        printf("Invalid amount!\n");
    }
}

void displayAccount(Account acc) {
    printf("\n=== Account Details ===\n");
    printf("Account No: %d\n", acc.accountNo);
    printf("Name: %s\n", acc.name);
    printf("Type: %s\n", acc.type);
    printf("Balance: $%.2f\n", acc.balance);
}

int main() {
    Account acc1 = {1001, "John Doe", "Savings", 5000.0};

    displayAccount(acc1);

    deposit(&acc1, 1500.0);
    withdraw(&acc1, 2000.0);
    withdraw(&acc1, 10000.0);  // Should fail

    displayAccount(acc1);

    return 0;
}
/* Output:
=== Account Details ===
Account No: 1001
Name: John Doe
Type: Savings
Balance: $5000.00
Deposited $1500.00. New balance: $6500.00
Withdrew $2000.00. New balance: $4500.00
Insufficient funds!

=== Account Details ===
Account No: 1001
Name: John Doe
Type: Savings
Balance: $4500.00
*/
```

### 4. Employee Payroll System

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    int empId;
    char name[50];
    char department[30];
    float basicSalary;
    float allowances;
    float deductions;
    float netSalary;
} Employee;

void calculateNetSalary(Employee *emp) {
    emp->netSalary = emp->basicSalary + emp->allowances - emp->deductions;
}

void generatePayslip(Employee emp) {
    printf("\n========== PAYSLIP ==========\n");
    printf("Employee ID: %d\n", emp.empId);
    printf("Name: %s\n", emp.name);
    printf("Department: %s\n", emp.department);
    printf("-----------------------------\n");
    printf("Basic Salary:    $%10.2f\n", emp.basicSalary);
    printf("Allowances:      $%10.2f\n", emp.allowances);
    printf("Deductions:      $%10.2f\n", emp.deductions);
    printf("-----------------------------\n");
    printf("Net Salary:      $%10.2f\n", emp.netSalary);
    printf("=============================\n");
}

int main() {
    Employee employees[3] = {
        {101, "Alice Johnson", "Engineering", 50000, 5000, 2000, 0},
        {102, "Bob Smith", "Marketing", 45000, 4500, 1800, 0},
        {103, "Charlie Brown", "Sales", 40000, 6000, 1500, 0}
    };

    printf("Monthly Payroll Report\n");

    for(int i = 0; i < 3; i++) {
        calculateNetSalary(&employees[i]);
        generatePayslip(employees[i]);
    }

    return 0;
}
```

### 5. Product Inventory System

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    int productId;
    char name[50];
    char category[30];
    int quantity;
    float price;
} Product;

typedef struct {
    Product products[100];
    int count;
} Inventory;

void addProduct(Inventory *inv, Product p) {
    if(inv->count < 100) {
        inv->products[inv->count] = p;
        inv->count++;
    }
}

void displayInventory(Inventory inv) {
    printf("\n%-6s %-25s %-15s %10s %10s %12s\n",
           "ID", "Name", "Category", "Quantity", "Price", "Total Value");
    printf("----------------------------------------------------------------"
           "----------------\n");

    float totalValue = 0;

    for(int i = 0; i < inv.count; i++) {
        float value = inv.products[i].quantity * inv.products[i].price;
        printf("%-6d %-25s %-15s %10d $%9.2f $%11.2f\n",
               inv.products[i].productId,
               inv.products[i].name,
               inv.products[i].category,
               inv.products[i].quantity,
               inv.products[i].price,
               value);
        totalValue += value;
    }

    printf("----------------------------------------------------------------"
           "----------------\n");
    printf("%65s $%11.2f\n", "TOTAL INVENTORY VALUE:", totalValue);
}

void updateStock(Inventory *inv, int productId, int quantity) {
    for(int i = 0; i < inv->count; i++) {
        if(inv->products[i].productId == productId) {
            inv->products[i].quantity += quantity;
            printf("Stock updated for %s. New quantity: %d\n",
                   inv->products[i].name,
                   inv->products[i].quantity);
            return;
        }
    }
    printf("Product not found!\n");
}

int main() {
    Inventory inventory = {.count = 0};

    Product p1 = {101, "Laptop", "Electronics", 25, 899.99};
    Product p2 = {102, "Mouse", "Accessories", 150, 19.99};
    Product p3 = {103, "Keyboard", "Accessories", 75, 49.99};
    Product p4 = {104, "Monitor", "Electronics", 40, 299.99};

    addProduct(&inventory, p1);
    addProduct(&inventory, p2);
    addProduct(&inventory, p3);
    addProduct(&inventory, p4);

    displayInventory(inventory);

    printf("\nUpdating stock...\n");
    updateStock(&inventory, 102, -30);  // Sold 30 mice

    displayInventory(inventory);

    return 0;
}
```

---

## Practice Exercises

### Basic Level

**Exercise 1:** Create a structure to represent a Rectangle with length and width. Write functions to calculate area and perimeter.

**Exercise 2:** Define a structure for Time (hours, minutes, seconds). Write a function to add two Time structures.

**Exercise 3:** Create a structure for a Circle with radius. Write functions to calculate area and circumference.

### Intermediate Level

**Exercise 4:** Create a structure for a Student with name, roll number, and marks in 3 subjects. Write a program to find the student with the highest average marks from an array of 5 students.

**Exercise 5:** Define a structure for a Car (make, model, year, price). Write functions to sort an array of cars by price and by year.

**Exercise 6:** Create a nested structure representing a Company with departments, where each department has multiple employees. Display all employees department-wise.

### Advanced Level

**Exercise 7:** Implement a simple contact management system using structures. Create a structure for Contact (name, phone, email, address). Implement functions to:
- Add new contact
- Search contact by name
- Display all contacts
- Delete a contact
- Update contact information
Store contacts in an array of structures.

**Hints:**
- Exercise 1: area = length × width, perimeter = 2(length + width)
- Exercise 2: Add hours, minutes, seconds separately, handle carry-over (60 seconds = 1 minute)
- Exercise 3: Use π = 3.14159; area = πr², circumference = 2πr
- Exercise 4: Calculate average for each student, track max and corresponding student
- Exercise 5: Use bubble sort or selection sort, compare by specified field
- Exercise 6: Use array of department structures, each containing array of employees
- Exercise 7: Use array of Contact structures with counter, implement CRUD operations

---

## Key Takeaways

1. **Structures group related data** of different types under one name
2. **Dot operator (.)** accesses members of structure variables
3. **Arrow operator (->)** accesses members through pointers
4. **typedef** simplifies structure declarations
5. **Nested structures** model complex real-world entities
6. **Pass by pointer** is efficient for large structures
7. **Array of structures** manages collections of related data

---

## Best Practices

1. **Use typedef** for cleaner syntax
2. **Pass structures by pointer** to functions for efficiency
3. **Initialize structures** completely to avoid garbage values
4. **Use const** when structure shouldn't be modified
5. **Group related data** logically in structures
6. **Document structure members** with comments
7. **Consider memory alignment** for performance-critical code

---

## Common Pitfalls

1. **Forgetting to use &** when passing structure to pointer parameter
2. **Using = instead of strcpy** for string members
3. **Uninitialized structures** containing garbage values
4. **Wrong operator** - using . with pointer or -> with variable
5. **Structure assignment** copies entire structure (can be slow for large structures)
6. **Padding and alignment** can make sizeof() larger than expected
7. **Comparing structures** with == (doesn't work, must compare member by member)

---

## Summary

Structures are fundamental to organizing complex data in C. They enable you to:
- Model real-world entities effectively
- Create custom data types
- Build sophisticated data structures
- Write more maintainable and organized code

Mastering structures is essential for advanced C programming, especially when working with:
- File handling
- Data structures (linked lists, trees, graphs)
- System programming
- Embedded systems
- Large-scale applications

---

**Congratulations!** You've completed the Intermediate C Programming module. You now have a solid foundation in:
- Loops and control flow
- Functions and recursion
- Arrays and data collections
- String manipulation
- Pointers and memory management
- Structures and custom data types

**Next Steps:** Practice these concepts extensively and prepare for advanced topics like:
- Dynamic memory allocation
- File handling
- Preprocessor directives
- Advanced data structures
- Multi-file projects

Keep coding and happy learning!
