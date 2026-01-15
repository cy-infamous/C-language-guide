# Strings in C

## Table of Contents
1. [Introduction to Strings](#introduction-to-strings)
2. [String Declaration and Initialization](#string-declaration-and-initialization)
3. [String Input and Output](#string-input-and-output)
4. [String Library Functions](#string-library-functions)
5. [String Manipulation](#string-manipulation)
6. [Character Arrays vs String Literals](#character-arrays-vs-string-literals)
7. [Real-World Applications](#real-world-applications)
8. [Practice Exercises](#practice-exercises)

---

## Introduction to Strings

In C, a string is an array of characters terminated by a null character `\0`. Strings allow you to:
- Store and manipulate text data
- Process user input
- Display formatted messages
- Implement text-based operations

### String Anatomy

```c
char str[] = "Hello";
```

**Memory Representation:**
```
Index:    0    1    2    3    4    5
        +----+----+----+----+----+----+
str     | H  | e  | l  | l  | o  | \0 |
        +----+----+----+----+----+----+

Note: The null character '\0' (ASCII value 0) marks the end of the string.
Length = 5, but array size = 6 (includes '\0')
```

### Why Null Terminator?

The null terminator `\0` helps C functions identify where the string ends:
- Functions can process strings without knowing the size in advance
- Enables efficient string operations
- Standard convention across C programs

**Example:**
```c
#include <stdio.h>

int main() {
    char str1[] = {'H', 'i', '\0'};  // Valid string
    char str2[] = {'H', 'i'};         // NOT a proper string

    printf("%s\n", str1);  // Output: Hi
    printf("%s\n", str2);  // Unpredictable output (no null terminator)

    return 0;
}
```

---

## String Declaration and Initialization

### Different Ways to Declare Strings

#### 1. Character Array with String Literal
```c
#include <stdio.h>

int main() {
    // Method 1: Size specified
    char str1[6] = "Hello";  // Size = 5 + 1 for '\0'

    // Method 2: Size inferred
    char str2[] = "World";   // Compiler calculates size

    // Method 3: Character by character
    char str3[] = {'H', 'e', 'l', 'l', 'o', '\0'};

    // Method 4: Partial initialization
    char str4[10] = "Hi";    // Rest filled with '\0'

    printf("%s\n", str1);  // Hello
    printf("%s\n", str2);  // World
    printf("%s\n", str3);  // Hello
    printf("%s\n", str4);  // Hi

    return 0;
}
```

#### 2. String Pointer
```c
#include <stdio.h>

int main() {
    // Pointer to string literal (stored in read-only memory)
    char *str = "Hello, World!";

    printf("%s\n", str);
    // str[0] = 'h';  // ERROR: Cannot modify string literal

    return 0;
}
```

### Memory Layout Comparison

**Character Array:**
```
Stack Memory (Modifiable):
Address: 1000 1001 1002 1003 1004 1005
        +----+----+----+----+----+----+
str[]   | H  | e  | l  | l  | o  | \0 |
        +----+----+----+----+----+----+

Can be modified: str[0] = 'h'; ✓
```

**String Literal:**
```
Read-Only Memory (Not modifiable):
Address: 2000 2001 2002 2003 2004 2005
        +----+----+----+----+----+----+
        | H  | e  | l  | l  | o  | \0 |
        +----+----+----+----+----+----+
         ^
         |
Stack:  +------+
*str -->| 2000 |  (pointer storing address)
        +------+

Cannot be modified: str[0] = 'h'; ✗ (Segmentation Fault)
```

---

## String Input and Output

### Output Functions

#### 1. printf() with %s
```c
#include <stdio.h>

int main() {
    char name[] = "Alice";

    printf("Hello, %s!\n", name);
    printf("First 3 characters: %.3s\n", name);  // Width specifier
    printf("Right-aligned: %10s\n", name);        // Right-align in 10 spaces
    printf("Left-aligned: %-10s|\n", name);       // Left-align in 10 spaces

    return 0;
}
/* Output:
Hello, Alice!
First 3 characters: Ali
Right-aligned:      Alice
Left-aligned: Alice     |
*/
```

#### 2. puts()
```c
#include <stdio.h>

int main() {
    char message[] = "Welcome to C Programming";

    puts(message);              // Automatically adds newline
    puts("Another message");

    return 0;
}
/* Output:
Welcome to C Programming
Another message
*/
```

### Input Functions

#### 1. scanf() - Reads until whitespace
```c
#include <stdio.h>

int main() {
    char name[50];

    printf("Enter your first name: ");
    scanf("%s", name);  // No & needed for arrays

    printf("Hello, %s!\n", name);

    return 0;
}
/* Input: John
   Output: Hello, John!

   Input: John Doe
   Output: Hello, John!  (Only reads "John", stops at space)
*/
```

#### 2. gets() - Reads entire line (UNSAFE - Deprecated)
```c
#include <stdio.h>

int main() {
    char line[100];

    printf("Enter a line: ");
    // gets(line);  // UNSAFE! Deprecated in C11
    // Reason: No bounds checking, can cause buffer overflow

    return 0;
}
```

#### 3. fgets() - Safe alternative to gets()
```c
#include <stdio.h>

int main() {
    char line[100];

    printf("Enter a line: ");
    fgets(line, sizeof(line), stdin);

    printf("You entered: %s", line);
    // Note: fgets() includes the newline character

    return 0;
}
/* Input: Hello World
   Output: You entered: Hello World
*/
```

#### 4. Removing Newline from fgets()
```c
#include <stdio.h>
#include <string.h>

int main() {
    char line[100];

    printf("Enter a line: ");
    fgets(line, sizeof(line), stdin);

    // Remove trailing newline
    line[strcspn(line, "\n")] = '\0';

    printf("You entered: %s\n", line);

    return 0;
}
```

---

## String Library Functions

Include `<string.h>` to use these functions.

### 1. strlen() - String Length

Returns the number of characters before `\0` (excluding `\0`).

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Hello";

    int len = strlen(str);
    printf("String: %s\n", str);
    printf("Length: %d\n", len);

    return 0;
}
// Output: String: Hello
//         Length: 5
```

**Manual Implementation:**
```c
int myStrlen(char str[]) {
    int count = 0;
    while(str[count] != '\0') {
        count++;
    }
    return count;
}
```

### 2. strcpy() - String Copy

Copies source string to destination.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char source[] = "Hello";
    char destination[20];

    strcpy(destination, source);

    printf("Source: %s\n", source);
    printf("Destination: %s\n", destination);

    return 0;
}
/* Output:
Source: Hello
Destination: Hello
*/
```

**Memory Visualization:**
```
Before strcpy:
source      [H][e][l][l][o][\0]
destination [?][?][?][?][?][?]...

After strcpy:
source      [H][e][l][l][o][\0]
destination [H][e][l][l][o][\0]...
```

**Manual Implementation:**
```c
void myStrcpy(char dest[], char src[]) {
    int i = 0;
    while(src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';  // Add null terminator
}
```

### 3. strcat() - String Concatenation

Appends source string to destination.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str1[50] = "Hello";
    char str2[] = " World";

    strcat(str1, str2);

    printf("Result: %s\n", str1);

    return 0;
}
// Output: Result: Hello World
```

**Memory Visualization:**
```
Before strcat:
str1 [H][e][l][l][o][\0][?][?][?]...
str2 [ ][W][o][r][l][d][\0]

After strcat:
str1 [H][e][l][l][o][ ][W][o][r][l][d][\0]...
str2 [ ][W][o][r][l][d][\0] (unchanged)
```

**Manual Implementation:**
```c
void myStrcat(char dest[], char src[]) {
    int i = 0, j = 0;

    // Find end of destination
    while(dest[i] != '\0') {
        i++;
    }

    // Copy source to end of destination
    while(src[j] != '\0') {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
}
```

### 4. strcmp() - String Compare

Compares two strings lexicographically.

**Return Values:**
- 0: Strings are equal
- Negative: str1 < str2
- Positive: str1 > str2

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str1[] = "apple";
    char str2[] = "banana";
    char str3[] = "apple";

    printf("strcmp(\"apple\", \"banana\"): %d\n", strcmp(str1, str2));
    printf("strcmp(\"banana\", \"apple\"): %d\n", strcmp(str2, str1));
    printf("strcmp(\"apple\", \"apple\"): %d\n", strcmp(str1, str3));

    // Practical use in conditions
    if(strcmp(str1, str3) == 0) {
        printf("str1 and str3 are equal\n");
    }

    return 0;
}
/* Output:
strcmp("apple", "banana"): -1  (or negative value)
strcmp("banana", "apple"): 1   (or positive value)
strcmp("apple", "apple"): 0
str1 and str3 are equal
*/
```

**Manual Implementation:**
```c
int myStrcmp(char str1[], char str2[]) {
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0') {
        if(str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}
```

### 5. strchr() - Find Character

Finds first occurrence of a character in string.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Hello World";
    char ch = 'o';

    char *ptr = strchr(str, ch);

    if(ptr != NULL) {
        printf("'%c' found at position: %ld\n", ch, ptr - str);
        printf("String from '%c': %s\n", ch, ptr);
    } else {
        printf("Character not found\n");
    }

    return 0;
}
/* Output:
'o' found at position: 4
String from 'o': o World
*/
```

### 6. strstr() - Find Substring

Finds first occurrence of a substring.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Hello World";
    char substr[] = "World";

    char *ptr = strstr(str, substr);

    if(ptr != NULL) {
        printf("Substring found at position: %ld\n", ptr - str);
        printf("String from substring: %s\n", ptr);
    } else {
        printf("Substring not found\n");
    }

    return 0;
}
/* Output:
Substring found at position: 6
String from substring: World
*/
```

### 7. strlwr() and strupr() - Case Conversion (Non-standard)

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str1[] = "Hello World";
    char str2[] = "Hello World";

    // Note: These functions are not standard C
    // Available in some compilers (like MSVC)

    // Manual lowercase conversion
    for(int i = 0; str1[i] != '\0'; i++) {
        if(str1[i] >= 'A' && str1[i] <= 'Z') {
            str1[i] = str1[i] + 32;  // or str1[i] += 'a' - 'A';
        }
    }

    // Manual uppercase conversion
    for(int i = 0; str2[i] != '\0'; i++) {
        if(str2[i] >= 'a' && str2[i] <= 'z') {
            str2[i] = str2[i] - 32;  // or str2[i] -= 'a' - 'A';
        }
    }

    printf("Lowercase: %s\n", str1);
    printf("Uppercase: %s\n", str2);

    return 0;
}
/* Output:
Lowercase: hello world
Uppercase: HELLO WORLD
*/
```

### 8. strrev() - Reverse String (Non-standard)

```c
#include <stdio.h>
#include <string.h>

void reverseString(char str[]) {
    int left = 0;
    int right = strlen(str) - 1;
    char temp;

    while(left < right) {
        temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

int main() {
    char str[] = "Hello";

    printf("Original: %s\n", str);
    reverseString(str);
    printf("Reversed: %s\n", str);

    return 0;
}
/* Output:
Original: Hello
Reversed: olleH
*/
```

---

## String Manipulation

### 1. Counting Vowels and Consonants
```c
#include <stdio.h>
#include <ctype.h>

int main() {
    char str[100];
    int vowels = 0, consonants = 0, digits = 0, spaces = 0;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    for(int i = 0; str[i] != '\0'; i++) {
        char ch = tolower(str[i]);

        if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            vowels++;
        } else if(ch >= 'a' && ch <= 'z') {
            consonants++;
        } else if(ch >= '0' && ch <= '9') {
            digits++;
        } else if(ch == ' ') {
            spaces++;
        }
    }

    printf("Vowels: %d\n", vowels);
    printf("Consonants: %d\n", consonants);
    printf("Digits: %d\n", digits);
    printf("Spaces: %d\n", spaces);

    return 0;
}
/* Input: Hello World 123
   Output:
   Vowels: 3
   Consonants: 7
   Digits: 3
   Spaces: 2
*/
```

### 2. Palindrome Check
```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isPalindrome(char str[]) {
    int left = 0;
    int right = strlen(str) - 1;

    while(left < right) {
        // Skip non-alphanumeric characters
        while(!isalnum(str[left]) && left < right) left++;
        while(!isalnum(str[right]) && left < right) right--;

        if(tolower(str[left]) != tolower(str[right])) {
            return 0;  // Not a palindrome
        }

        left++;
        right--;
    }

    return 1;  // Is a palindrome
}

int main() {
    char str1[] = "madam";
    char str2[] = "racecar";
    char str3[] = "hello";

    printf("\"%s\" is %s\n", str1,
           isPalindrome(str1) ? "a palindrome" : "not a palindrome");
    printf("\"%s\" is %s\n", str2,
           isPalindrome(str2) ? "a palindrome" : "not a palindrome");
    printf("\"%s\" is %s\n", str3,
           isPalindrome(str3) ? "a palindrome" : "not a palindrome");

    return 0;
}
/* Output:
"madam" is a palindrome
"racecar" is a palindrome
"hello" is not a palindrome
*/
```

### 3. Word Count
```c
#include <stdio.h>
#include <ctype.h>

int countWords(char str[]) {
    int count = 0;
    int inWord = 0;

    for(int i = 0; str[i] != '\0'; i++) {
        if(isspace(str[i])) {
            inWord = 0;
        } else if(inWord == 0) {
            inWord = 1;
            count++;
        }
    }

    return count;
}

int main() {
    char str[] = "Hello World from C Programming";

    printf("String: %s\n", str);
    printf("Word count: %d\n", countWords(str));

    return 0;
}
/* Output:
String: Hello World from C Programming
Word count: 5
*/
```

### 4. String Tokenization
```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "apple,banana,orange,grape";
    char *token;

    printf("Original string: %s\n", str);
    printf("Tokens:\n");

    token = strtok(str, ",");
    while(token != NULL) {
        printf("  %s\n", token);
        token = strtok(NULL, ",");
    }

    return 0;
}
/* Output:
Original string: apple,banana,orange,grape
Tokens:
  apple
  banana
  orange
  grape
*/
```

### 5. Remove Spaces from String
```c
#include <stdio.h>

void removeSpaces(char str[]) {
    int i = 0, j = 0;

    while(str[i] != '\0') {
        if(str[i] != ' ') {
            str[j] = str[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
}

int main() {
    char str[] = "Hello World from C";

    printf("Original: \"%s\"\n", str);
    removeSpaces(str);
    printf("After removing spaces: \"%s\"\n", str);

    return 0;
}
/* Output:
Original: "Hello World from C"
After removing spaces: "HelloWorldfromC"
*/
```

### 6. String to Integer Conversion
```c
#include <stdio.h>

int stringToInt(char str[]) {
    int result = 0;
    int sign = 1;
    int i = 0;

    // Handle negative sign
    if(str[0] == '-') {
        sign = -1;
        i = 1;
    }

    while(str[i] != '\0') {
        if(str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        } else {
            break;  // Stop at non-digit character
        }
        i++;
    }

    return result * sign;
}

int main() {
    char str1[] = "12345";
    char str2[] = "-678";
    char str3[] = "42abc";

    printf("\"%s\" -> %d\n", str1, stringToInt(str1));
    printf("\"%s\" -> %d\n", str2, stringToInt(str2));
    printf("\"%s\" -> %d\n", str3, stringToInt(str3));

    return 0;
}
/* Output:
"12345" -> 12345
"-678" -> -678
"42abc" -> 42
*/
```

---

## Character Arrays vs String Literals

### Comparison Table

| Feature | Character Array | String Literal |
|---------|----------------|----------------|
| Declaration | `char str[] = "Hello";` | `char *str = "Hello";` |
| Memory | Stack (modifiable) | Read-only section |
| Modification | Allowed | Not allowed (undefined behavior) |
| Size | Known at compile-time | Pointer size (4 or 8 bytes) |
| Lifetime | Block scope | Program lifetime |

### Examples

```c
#include <stdio.h>

int main() {
    // Character array - modifiable
    char arr[] = "Hello";
    arr[0] = 'h';  // OK
    printf("%s\n", arr);  // hello

    // String literal - not modifiable
    char *ptr = "World";
    // ptr[0] = 'w';  // ERROR: Segmentation fault
    printf("%s\n", ptr);  // World

    // Can reassign pointer (points to different string)
    ptr = "C Programming";
    printf("%s\n", ptr);  // C Programming

    return 0;
}
```

**Memory Diagram:**
```
Character Array (Stack):
arr: [H][e][l][l][o][\0]  <- Can modify
     ↑
     Directly stored

String Literal (Read-Only Memory):
Read-Only: [W][o][r][l][d][\0]  <- Cannot modify
            ↑
            |
Stack: ptr [address] <- Can change to point elsewhere
```

---

## Real-World Applications

### 1. Email Validator
```c
#include <stdio.h>
#include <string.h>

int isValidEmail(char email[]) {
    int atCount = 0, dotAfterAt = 0;
    int atPos = -1;

    // Check for @ symbol
    for(int i = 0; email[i] != '\0'; i++) {
        if(email[i] == '@') {
            atCount++;
            atPos = i;
        }
    }

    if(atCount != 1 || atPos == 0) {
        return 0;  // Must have exactly one @ and not at start
    }

    // Check for . after @
    for(int i = atPos + 1; email[i] != '\0'; i++) {
        if(email[i] == '.') {
            dotAfterAt = 1;
            break;
        }
    }

    return dotAfterAt;
}

int main() {
    char email1[] = "user@example.com";
    char email2[] = "invalid.email";
    char email3[] = "@example.com";

    printf("%s: %s\n", email1, isValidEmail(email1) ? "Valid" : "Invalid");
    printf("%s: %s\n", email2, isValidEmail(email2) ? "Valid" : "Invalid");
    printf("%s: %s\n", email3, isValidEmail(email3) ? "Valid" : "Invalid");

    return 0;
}
/* Output:
user@example.com: Valid
invalid.email: Invalid
@example.com: Invalid
*/
```

### 2. Password Strength Checker
```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void checkPasswordStrength(char password[]) {
    int len = strlen(password);
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;

    for(int i = 0; i < len; i++) {
        if(isupper(password[i])) hasUpper = 1;
        else if(islower(password[i])) hasLower = 1;
        else if(isdigit(password[i])) hasDigit = 1;
        else hasSpecial = 1;
    }

    int strength = hasUpper + hasLower + hasDigit + hasSpecial;

    printf("Password: %s\n", password);
    printf("Length: %d\n", len);
    printf("Has uppercase: %s\n", hasUpper ? "Yes" : "No");
    printf("Has lowercase: %s\n", hasLower ? "Yes" : "No");
    printf("Has digit: %s\n", hasDigit ? "Yes" : "No");
    printf("Has special char: %s\n", hasSpecial ? "Yes" : "No");

    if(len < 8) {
        printf("Strength: Weak (too short)\n");
    } else if(strength <= 2) {
        printf("Strength: Weak\n");
    } else if(strength == 3) {
        printf("Strength: Medium\n");
    } else {
        printf("Strength: Strong\n");
    }
}

int main() {
    char password[100];

    printf("Enter password: ");
    scanf("%s", password);

    checkPasswordStrength(password);

    return 0;
}
```

### 3. Text Formatter
```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void titleCase(char str[]) {
    int newWord = 1;

    for(int i = 0; str[i] != '\0'; i++) {
        if(isspace(str[i])) {
            newWord = 1;
        } else if(newWord) {
            str[i] = toupper(str[i]);
            newWord = 0;
        } else {
            str[i] = tolower(str[i]);
        }
    }
}

int main() {
    char text[] = "hello world from c programming";

    printf("Original: %s\n", text);
    titleCase(text);
    printf("Title Case: %s\n", text);

    return 0;
}
/* Output:
Original: hello world from c programming
Title Case: Hello World From C Programming
*/
```

### 4. Simple Text Encryption (Caesar Cipher)
```c
#include <stdio.h>
#include <ctype.h>

void caesarCipher(char str[], int shift) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(isalpha(str[i])) {
            char base = isupper(str[i]) ? 'A' : 'a';
            str[i] = base + (str[i] - base + shift) % 26;
        }
    }
}

int main() {
    char message[] = "Hello World";
    int shift = 3;

    printf("Original: %s\n", message);

    caesarCipher(message, shift);
    printf("Encrypted: %s\n", message);

    caesarCipher(message, 26 - shift);  // Decrypt
    printf("Decrypted: %s\n", message);

    return 0;
}
/* Output:
Original: Hello World
Encrypted: Khoor Zruog
Decrypted: Hello World
*/
```

### 5. Username Generator
```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generateUsername(char firstName[], char lastName[], char username[]) {
    int i = 0, j = 0;

    // Add first 3 letters of first name (lowercase)
    for(i = 0; i < 3 && firstName[i] != '\0'; i++) {
        username[j++] = tolower(firstName[i]);
    }

    // Add first 3 letters of last name (lowercase)
    for(i = 0; i < 3 && lastName[i] != '\0'; i++) {
        username[j++] = tolower(lastName[i]);
    }

    // Add random number (simplified - use length)
    int num = strlen(firstName) + strlen(lastName);
    sprintf(&username[j], "%d", num);
}

int main() {
    char firstName[50], lastName[50], username[50];

    printf("Enter first name: ");
    scanf("%s", firstName);
    printf("Enter last name: ");
    scanf("%s", lastName);

    generateUsername(firstName, lastName, username);

    printf("Generated username: %s\n", username);

    return 0;
}
/* Example:
   Input: John Smith
   Output: Generated username: johsmi9
*/
```

---

## Practice Exercises

### Basic Level

**Exercise 1:** Write a program that counts the number of words in a sentence entered by the user.

**Exercise 2:** Create a program that checks if a given string is a palindrome (case-insensitive).

**Exercise 3:** Write a program to find the frequency of a specific character in a string.

### Intermediate Level

**Exercise 4:** Implement a function that removes all duplicate characters from a string. For example, "hello" becomes "helo".

**Exercise 5:** Create a program that finds the longest word in a sentence.

**Exercise 6:** Write a program that checks if two strings are anagrams (contain same characters in different order). Example: "listen" and "silent" are anagrams.

### Advanced Level

**Exercise 7:** Implement a function that performs pattern matching to check if a substring exists in a string and returns all positions where it occurs. Example: In "hello hello world", "hello" occurs at positions 0 and 6.

**Hints:**
- Exercise 1: Count transitions from space to non-space characters
- Exercise 2: Compare characters from both ends moving towards center
- Exercise 3: Loop through string and count matches
- Exercise 4: For each character, check if it appeared before; if not, keep it
- Exercise 5: Tokenize string by spaces and compare lengths
- Exercise 6: Sort characters in both strings and compare, or count frequency of each character
- Exercise 7: Use nested loops or strstr() repeatedly with pointer arithmetic

---

## Key Takeaways

1. **Strings are character arrays** terminated by `\0`
2. **Always allocate space** for the null terminator
3. **Use `string.h` functions** for common operations
4. **fgets() is safer** than gets() for input
5. **Character arrays are modifiable**, string literals are not
6. **strcmp() returns 0** when strings are equal (not 1)
7. **Always check bounds** to prevent buffer overflow

---

## Best Practices

1. **Always include null terminator** in size calculations
2. **Use `sizeof()` with `fgets()`** for safety
3. **Check for NULL** when using search functions
4. **Prefer `strncpy()` over `strcpy()`** for bounded copying
5. **Validate input** before processing
6. **Use `const char*`** for read-only string parameters
7. **Be cautious** with string modification in functions

---

## Common Pitfalls

1. Forgetting null terminator in manual string creation
2. Buffer overflow from unbounded input
3. Comparing strings with `==` instead of `strcmp()`
4. Modifying string literals (causes segmentation fault)
5. Not checking return values of string functions
6. Off-by-one errors in loop conditions
7. Memory leaks with dynamically allocated strings

---

**Next Topic:** [Pointers](05-pointers.md) - Master memory addresses and pointer operations!
