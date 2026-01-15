# Arrays and Strings - Data Structures & Algorithms

## Table of Contents
1. [Arrays in DSA](#arrays-in-dsa)
2. [Array Operations](#array-operations)
3. [Common Array Algorithms](#common-array-algorithms)
4. [Two Pointer Technique](#two-pointer-technique)
5. [Sliding Window Technique](#sliding-window-technique)
6. [String Algorithms](#string-algorithms)
7. [String Manipulation](#string-manipulation)
8. [Pattern Matching](#pattern-matching)
9. [Practice Problems](#practice-problems)

---

## Arrays in DSA

### What is an Array?
An **array** is a contiguous block of memory that stores elements of the same data type. Each element is accessible via an index.

### Memory Layout
```
Array: [10, 20, 30, 40, 50]

Memory Visualization:
┌────┬────┬────┬────┬────┐
│ 10 │ 20 │ 30 │ 40 │ 50 │
└────┴────┴────┴────┴────┘
  ↑    ↑    ↑    ↑    ↑
  0    1    2    3    4    (indices)

Address: 1000, 1004, 1008, 1012, 1016  (if int = 4 bytes)
```

### Array Characteristics

| Property | Value |
|----------|-------|
| Access Time | O(1) |
| Search Time | O(n) unsorted, O(log n) sorted |
| Insert at End | O(1) if space available |
| Insert at Beginning | O(n) |
| Delete | O(n) |
| Space | O(n) |

### Advantages
- Fast access using index: O(1)
- Cache-friendly (contiguous memory)
- Simple and widely supported

### Disadvantages
- Fixed size (in static arrays)
- Expensive insertion/deletion
- Requires contiguous memory

---

## Array Operations

### 1. Traversal
Visiting every element once.

```c
#include <stdio.h>

// Forward Traversal - O(n)
void traverseArray(int arr[], int n) {
    printf("Array elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Reverse Traversal - O(n)
void reverseTraverse(int arr[], int n) {
    printf("Reverse order: ");
    for (int i = n - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);

    traverseArray(arr, n);
    reverseTraverse(arr, n);

    return 0;
}
```

### 2. Insertion

```c
#include <stdio.h>
#define MAX 100

// Insert at end - O(1)
int insertAtEnd(int arr[], int n, int element) {
    if (n >= MAX) {
        printf("Array is full!\n");
        return n;
    }
    arr[n] = element;
    return n + 1;
}

// Insert at beginning - O(n)
int insertAtBeginning(int arr[], int n, int element) {
    if (n >= MAX) {
        printf("Array is full!\n");
        return n;
    }

    // Shift all elements right
    for (int i = n; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = element;
    return n + 1;
}

// Insert at specific position - O(n)
int insertAtPosition(int arr[], int n, int element, int pos) {
    if (n >= MAX) {
        printf("Array is full!\n");
        return n;
    }
    if (pos < 0 || pos > n) {
        printf("Invalid position!\n");
        return n;
    }

    // Shift elements from pos to end
    for (int i = n; i > pos; i--) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = element;
    return n + 1;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[MAX] = {10, 20, 30, 40, 50};
    int n = 5;

    printf("Original: ");
    printArray(arr, n);

    n = insertAtEnd(arr, n, 60);
    printf("After insert at end: ");
    printArray(arr, n);

    n = insertAtBeginning(arr, n, 5);
    printf("After insert at beginning: ");
    printArray(arr, n);

    n = insertAtPosition(arr, n, 25, 3);
    printf("After insert at position 3: ");
    printArray(arr, n);

    return 0;
}
```

### 3. Deletion

```c
#include <stdio.h>

// Delete from end - O(1)
int deleteFromEnd(int arr[], int n) {
    if (n <= 0) {
        printf("Array is empty!\n");
        return 0;
    }
    return n - 1;
}

// Delete from beginning - O(n)
int deleteFromBeginning(int arr[], int n) {
    if (n <= 0) {
        printf("Array is empty!\n");
        return 0;
    }

    // Shift all elements left
    for (int i = 0; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    return n - 1;
}

// Delete from specific position - O(n)
int deleteFromPosition(int arr[], int n, int pos) {
    if (n <= 0) {
        printf("Array is empty!\n");
        return 0;
    }
    if (pos < 0 || pos >= n) {
        printf("Invalid position!\n");
        return n;
    }

    // Shift elements from pos+1 to end
    for (int i = pos; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    return n - 1;
}

// Delete by value - O(n)
int deleteByValue(int arr[], int n, int value) {
    int pos = -1;

    // Find the element
    for (int i = 0; i < n; i++) {
        if (arr[i] == value) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Element not found!\n");
        return n;
    }

    return deleteFromPosition(arr, n, pos);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int n = 5;

    printf("Original: ");
    printArray(arr, n);

    n = deleteFromEnd(arr, n);
    printf("After delete from end: ");
    printArray(arr, n);

    n = deleteFromBeginning(arr, n);
    printf("After delete from beginning: ");
    printArray(arr, n);

    n = deleteByValue(arr, n, 30);
    printf("After deleting value 30: ");
    printArray(arr, n);

    return 0;
}
```

### 4. Searching

```c
#include <stdio.h>

// Linear Search - O(n)
int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

// Binary Search - O(log n) - Array must be sorted
int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        }
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// Recursive Binary Search
int binarySearchRecursive(int arr[], int left, int right, int target) {
    if (left > right) {
        return -1;
    }

    int mid = left + (right - left) / 2;

    if (arr[mid] == target) {
        return mid;
    }
    if (arr[mid] < target) {
        return binarySearchRecursive(arr, mid + 1, right, target);
    } else {
        return binarySearchRecursive(arr, left, mid - 1, target);
    }
}

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int n = sizeof(arr) / sizeof(arr[0]);

    int target = 50;

    // Linear Search
    int result = linearSearch(arr, n, target);
    if (result != -1)
        printf("Linear Search: Element found at index %d\n", result);

    // Binary Search
    result = binarySearch(arr, n, target);
    if (result != -1)
        printf("Binary Search: Element found at index %d\n", result);

    // Recursive Binary Search
    result = binarySearchRecursive(arr, 0, n - 1, target);
    if (result != -1)
        printf("Recursive Binary Search: Element found at index %d\n", result);

    return 0;
}
```

---

## Common Array Algorithms

### 1. Reverse an Array

```c
#include <stdio.h>

// Method 1: Using extra space - O(n) time, O(n) space
void reverseWithSpace(int arr[], int n) {
    int temp[n];
    for (int i = 0; i < n; i++) {
        temp[i] = arr[n - 1 - i];
    }
    for (int i = 0; i < n; i++) {
        arr[i] = temp[i];
    }
}

// Method 2: In-place - O(n) time, O(1) space
void reverseInPlace(int arr[], int n) {
    int left = 0, right = n - 1;

    while (left < right) {
        // Swap elements
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;

        left++;
        right--;
    }
}

// Method 3: Recursive
void reverseRecursive(int arr[], int left, int right) {
    if (left >= right) {
        return;
    }

    // Swap
    int temp = arr[left];
    arr[left] = arr[right];
    arr[right] = temp;

    reverseRecursive(arr, left + 1, right - 1);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original: ");
    printArray(arr, n);

    reverseInPlace(arr, n);
    printf("Reversed: ");
    printArray(arr, n);

    return 0;
}
```

### 2. Find Maximum and Minimum

```c
#include <stdio.h>
#include <limits.h>

// Method 1: Simple Linear Scan - O(n)
void findMaxMin(int arr[], int n, int* max, int* min) {
    *max = INT_MIN;
    *min = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (arr[i] > *max) *max = arr[i];
        if (arr[i] < *min) *min = arr[i];
    }
}

// Method 2: Tournament Method (Divide and Conquer) - O(n)
typedef struct {
    int max;
    int min;
} MinMax;

MinMax findMaxMinDivideConquer(int arr[], int left, int right) {
    MinMax result, left_result, right_result;

    // Base case: only one element
    if (left == right) {
        result.max = arr[left];
        result.min = arr[left];
        return result;
    }

    // Base case: two elements
    if (right == left + 1) {
        if (arr[left] > arr[right]) {
            result.max = arr[left];
            result.min = arr[right];
        } else {
            result.max = arr[right];
            result.min = arr[left];
        }
        return result;
    }

    // Divide
    int mid = left + (right - left) / 2;
    left_result = findMaxMinDivideConquer(arr, left, mid);
    right_result = findMaxMinDivideConquer(arr, mid + 1, right);

    // Conquer
    result.max = (left_result.max > right_result.max) ?
                 left_result.max : right_result.max;
    result.min = (left_result.min < right_result.min) ?
                 left_result.min : right_result.min;

    return result;
}

int main() {
    int arr[] = {12, 3, 5, 7, 19, 26, 8, 14};
    int n = sizeof(arr) / sizeof(arr[0]);

    int max, min;
    findMaxMin(arr, n, &max, &min);
    printf("Method 1 - Max: %d, Min: %d\n", max, min);

    MinMax result = findMaxMinDivideConquer(arr, 0, n - 1);
    printf("Method 2 - Max: %d, Min: %d\n", result.max, result.min);

    return 0;
}
```

### 3. Rotate Array

```c
#include <stdio.h>

// Rotate array left by d positions
// Method 1: Using temporary array - O(n) time, O(d) space
void rotateLeftTemp(int arr[], int n, int d) {
    d = d % n;  // Handle case where d > n
    int temp[d];

    // Store first d elements
    for (int i = 0; i < d; i++) {
        temp[i] = arr[i];
    }

    // Shift remaining elements
    for (int i = d; i < n; i++) {
        arr[i - d] = arr[i];
    }

    // Copy back temp elements
    for (int i = 0; i < d; i++) {
        arr[n - d + i] = temp[i];
    }
}

// Method 2: Using reversal - O(n) time, O(1) space
void reverse(int arr[], int start, int end) {
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void rotateLeftReversal(int arr[], int n, int d) {
    d = d % n;

    // Reverse first d elements
    reverse(arr, 0, d - 1);

    // Reverse remaining n-d elements
    reverse(arr, d, n - 1);

    // Reverse entire array
    reverse(arr, 0, n - 1);
}

// Rotate right by d positions
void rotateRight(int arr[], int n, int d) {
    d = d % n;
    rotateLeftReversal(arr, n, n - d);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original: ");
    printArray(arr, n);

    rotateLeftReversal(arr, n, 2);
    printf("Rotated left by 2: ");
    printArray(arr, n);

    rotateRight(arr, n, 3);
    printf("Rotated right by 3: ");
    printArray(arr, n);

    return 0;
}
```

### 4. Find Missing Number

```c
#include <stdio.h>

// Given array of n-1 numbers from 1 to n with one missing
// Method 1: Using sum formula - O(n) time, O(1) space
int findMissingSum(int arr[], int n) {
    int total = (n + 1) * (n + 2) / 2;  // Sum of first n+1 natural numbers
    int sum = 0;

    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    return total - sum;
}

// Method 2: Using XOR - O(n) time, O(1) space
int findMissingXOR(int arr[], int n) {
    int x1 = 0, x2 = 0;

    // XOR all array elements
    for (int i = 0; i < n; i++) {
        x1 ^= arr[i];
    }

    // XOR all numbers from 1 to n+1
    for (int i = 1; i <= n + 1; i++) {
        x2 ^= i;
    }

    // Missing number is x1 XOR x2
    return x1 ^ x2;
}

int main() {
    int arr[] = {1, 2, 4, 5, 6};  // Missing: 3
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Missing number (sum method): %d\n", findMissingSum(arr, n));
    printf("Missing number (XOR method): %d\n", findMissingXOR(arr, n));

    return 0;
}
```

---

## Two Pointer Technique

The two-pointer technique uses two pointers to iterate through the array, often reducing time complexity from O(n²) to O(n).

### Pattern Visualization
```
Array: [1, 2, 3, 4, 5, 6, 7, 8]
        ↑                    ↑
       left                right

Two pointers move towards each other or in same direction
```

### 1. Two Sum Problem (Sorted Array)

```c
#include <stdio.h>
#include <stdbool.h>

// Find two numbers that sum to target - O(n)
bool twoSumSorted(int arr[], int n, int target) {
    int left = 0, right = n - 1;

    while (left < right) {
        int sum = arr[left] + arr[right];

        if (sum == target) {
            printf("Pair found: %d + %d = %d\n", arr[left], arr[right], target);
            return true;
        } else if (sum < target) {
            left++;   // Need larger sum
        } else {
            right--;  // Need smaller sum
        }
    }

    return false;
}

// Two sum for unsorted array - O(n²) brute force
bool twoSumUnsorted(int arr[], int n, int target) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] + arr[j] == target) {
                printf("Pair found: %d + %d = %d\n", arr[i], arr[j], target);
                return true;
            }
        }
    }
    return false;
}

int main() {
    int arr[] = {2, 7, 11, 15, 27};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 18;

    twoSumSorted(arr, n, target);

    return 0;
}
```

### 2. Remove Duplicates from Sorted Array

```c
#include <stdio.h>

// Remove duplicates in-place - O(n) time, O(1) space
int removeDuplicates(int arr[], int n) {
    if (n == 0 || n == 1) return n;

    int j = 0;  // Slow pointer

    for (int i = 0; i < n - 1; i++) {  // Fast pointer
        if (arr[i] != arr[i + 1]) {
            arr[j++] = arr[i];
        }
    }
    arr[j++] = arr[n - 1];

    return j;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 1, 2, 2, 2, 3, 4, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original: ");
    printArray(arr, n);

    int newLength = removeDuplicates(arr, n);
    printf("After removing duplicates: ");
    printArray(arr, newLength);

    return 0;
}
```

### 3. Container With Most Water

```c
#include <stdio.h>

// Find maximum water that can be trapped - O(n)
int maxArea(int height[], int n) {
    int left = 0, right = n - 1;
    int maxWater = 0;

    while (left < right) {
        // Calculate area
        int width = right - left;
        int h = (height[left] < height[right]) ? height[left] : height[right];
        int area = width * h;

        if (area > maxWater) {
            maxWater = area;
        }

        // Move pointer with smaller height
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }

    return maxWater;
}

int main() {
    int height[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    int n = sizeof(height) / sizeof(height[0]);

    printf("Maximum water: %d\n", maxArea(height, n));

    return 0;
}
```

---

## Sliding Window Technique

The sliding window technique is used for problems involving subarrays or substrings. It reduces time complexity from O(n²) to O(n).

### Fixed Size Window
```
Array: [1, 4, 2, 10, 23, 3, 1, 0, 20]
Window size: 4

Window 1: [1, 4, 2, 10]    sum = 17
Window 2:    [4, 2, 10, 23] sum = 39
Window 3:       [2, 10, 23, 3] sum = 38
...
```

### 1. Maximum Sum Subarray of Size K

```c
#include <stdio.h>
#include <limits.h>

// Brute force - O(n*k)
int maxSumBruteForce(int arr[], int n, int k) {
    int maxSum = INT_MIN;

    for (int i = 0; i <= n - k; i++) {
        int sum = 0;
        for (int j = 0; j < k; j++) {
            sum += arr[i + j];
        }
        if (sum > maxSum) {
            maxSum = sum;
        }
    }

    return maxSum;
}

// Sliding window - O(n)
int maxSumSlidingWindow(int arr[], int n, int k) {
    if (n < k) {
        printf("Invalid: k > n\n");
        return -1;
    }

    // Calculate sum of first window
    int windowSum = 0;
    for (int i = 0; i < k; i++) {
        windowSum += arr[i];
    }

    int maxSum = windowSum;

    // Slide the window
    for (int i = k; i < n; i++) {
        windowSum += arr[i] - arr[i - k];  // Add new, remove old
        if (windowSum > maxSum) {
            maxSum = windowSum;
        }
    }

    return maxSum;
}

int main() {
    int arr[] = {1, 4, 2, 10, 23, 3, 1, 0, 20};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 4;

    printf("Maximum sum of subarray (size %d): %d\n",
           k, maxSumSlidingWindow(arr, n, k));

    return 0;
}
```

### 2. Longest Substring Without Repeating Characters

```c
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Variable size window - O(n)
int longestUniqueSubstring(char* s) {
    int n = strlen(s);
    int maxLength = 0;
    int start = 0;
    int charIndex[256];  // Store last index of each character

    // Initialize all characters as not seen
    for (int i = 0; i < 256; i++) {
        charIndex[i] = -1;
    }

    for (int end = 0; end < n; end++) {
        // If character already seen in current window
        if (charIndex[s[end]] >= start) {
            start = charIndex[s[end]] + 1;
        }

        charIndex[s[end]] = end;
        int currentLength = end - start + 1;

        if (currentLength > maxLength) {
            maxLength = currentLength;
        }
    }

    return maxLength;
}

int main() {
    char str[] = "abcabcbb";
    printf("Longest unique substring length: %d\n",
           longestUniqueSubstring(str));

    return 0;
}
```

### 3. Minimum Window Substring

```c
#include <stdio.h>
#include <string.h>
#include <limits.h>

// Find minimum window in s that contains all characters of t
void minWindow(char* s, char* t, char* result) {
    int sLen = strlen(s);
    int tLen = strlen(t);

    if (sLen < tLen) {
        result[0] = '\0';
        return;
    }

    int targetFreq[256] = {0};
    int windowFreq[256] = {0};

    // Count frequency of characters in t
    for (int i = 0; i < tLen; i++) {
        targetFreq[t[i]]++;
    }

    int start = 0, minStart = 0, minLength = INT_MAX;
    int count = 0;  // Count of characters matched

    for (int end = 0; end < sLen; end++) {
        windowFreq[s[end]]++;

        // If current character matches target frequency
        if (targetFreq[s[end]] > 0 && windowFreq[s[end]] <= targetFreq[s[end]]) {
            count++;
        }

        // Try to minimize window
        while (count == tLen) {
            if (end - start + 1 < minLength) {
                minLength = end - start + 1;
                minStart = start;
            }

            windowFreq[s[start]]--;
            if (targetFreq[s[start]] > 0 && windowFreq[s[start]] < targetFreq[s[start]]) {
                count--;
            }
            start++;
        }
    }

    if (minLength == INT_MAX) {
        result[0] = '\0';
    } else {
        strncpy(result, s + minStart, minLength);
        result[minLength] = '\0';
    }
}

int main() {
    char s[] = "ADOBECODEBANC";
    char t[] = "ABC";
    char result[100];

    minWindow(s, t, result);
    printf("Minimum window: %s\n", result);

    return 0;
}
```

---

## String Algorithms

### 1. String Reversal

```c
#include <stdio.h>
#include <string.h>

// In-place reversal - O(n)
void reverseString(char* str) {
    int n = strlen(str);
    int left = 0, right = n - 1;

    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

// Reverse words in a string
void reverseWords(char* str) {
    int n = strlen(str);

    // Reverse entire string
    reverseString(str);

    // Reverse each word
    int start = 0;
    for (int end = 0; end <= n; end++) {
        if (str[end] == ' ' || str[end] == '\0') {
            // Reverse word
            int left = start, right = end - 1;
            while (left < right) {
                char temp = str[left];
                str[left] = str[right];
                str[right] = temp;
                left++;
                right--;
            }
            start = end + 1;
        }
    }
}

int main() {
    char str1[] = "hello";
    printf("Original: %s\n", str1);
    reverseString(str1);
    printf("Reversed: %s\n", str1);

    char str2[] = "the sky is blue";
    printf("\nOriginal: %s\n", str2);
    reverseWords(str2);
    printf("Reversed words: %s\n", str2);

    return 0;
}
```

### 2. Check Palindrome

```c
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Basic palindrome check - O(n)
bool isPalindrome(char* str) {
    int left = 0, right = strlen(str) - 1;

    while (left < right) {
        if (str[left] != str[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// Palindrome ignoring spaces and case
bool isPalindromeIgnoreSpaces(char* str) {
    int left = 0, right = strlen(str) - 1;

    while (left < right) {
        // Skip non-alphanumeric characters
        while (left < right && !isalnum(str[left])) left++;
        while (left < right && !isalnum(str[right])) right--;

        if (tolower(str[left]) != tolower(str[right])) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

int main() {
    char str1[] = "racecar";
    printf("%s is %s\n", str1, isPalindrome(str1) ? "palindrome" : "not palindrome");

    char str2[] = "A man a plan a canal Panama";
    printf("%s is %s\n", str2,
           isPalindromeIgnoreSpaces(str2) ? "palindrome" : "not palindrome");

    return 0;
}
```

### 3. Anagram Check

```c
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Method 1: Using frequency array - O(n)
bool areAnagrams(char* str1, char* str2) {
    if (strlen(str1) != strlen(str2)) {
        return false;
    }

    int freq[256] = {0};

    // Increment for str1
    for (int i = 0; str1[i]; i++) {
        freq[str1[i]]++;
    }

    // Decrement for str2
    for (int i = 0; str2[i]; i++) {
        freq[str2[i]]--;
    }

    // Check if all frequencies are zero
    for (int i = 0; i < 256; i++) {
        if (freq[i] != 0) {
            return false;
        }
    }

    return true;
}

int main() {
    char str1[] = "listen";
    char str2[] = "silent";

    printf("%s and %s are %s\n", str1, str2,
           areAnagrams(str1, str2) ? "anagrams" : "not anagrams");

    return 0;
}
```

---

## Pattern Matching

### 1. Naive Pattern Matching

```c
#include <stdio.h>
#include <string.h>

// Brute force pattern matching - O((n-m+1)*m)
void naivePatternSearch(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    for (int i = 0; i <= n - m; i++) {
        int j;

        // Check if pattern matches at position i
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }

        if (j == m) {
            printf("Pattern found at index %d\n", i);
        }
    }
}

int main() {
    char text[] = "AABAACAADAABAAABAA";
    char pattern[] = "AABA";

    printf("Text: %s\n", text);
    printf("Pattern: %s\n", pattern);
    naivePatternSearch(text, pattern);

    return 0;
}
```

### 2. KMP Algorithm (Knuth-Morris-Pratt)

```c
#include <stdio.h>
#include <string.h>

// Compute LPS (Longest Proper Prefix which is also Suffix) array
void computeLPS(char* pattern, int m, int* lps) {
    int length = 0;  // Length of previous longest prefix suffix
    lps[0] = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Pattern Matching - O(n + m)
void KMPSearch(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    int lps[m];
    computeLPS(pattern, m, lps);

    int i = 0;  // Index for text
    int j = 0;  // Index for pattern

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    char text[] = "AABAACAADAABAAABAA";
    char pattern[] = "AABA";

    printf("Text: %s\n", text);
    printf("Pattern: %s\n", pattern);
    KMPSearch(text, pattern);

    return 0;
}
```

---

## Practice Problems

### Problem 1: Find Second Largest Element (Easy)
Find the second largest element in an array.

```c
#include <stdio.h>
#include <limits.h>

int findSecondLargest(int arr[], int n) {
    if (n < 2) return -1;

    int first = INT_MIN, second = INT_MIN;

    for (int i = 0; i < n; i++) {
        if (arr[i] > first) {
            second = first;
            first = arr[i];
        } else if (arr[i] > second && arr[i] != first) {
            second = arr[i];
        }
    }

    return (second == INT_MIN) ? -1 : second;
}

int main() {
    int arr[] = {12, 35, 1, 10, 34, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Second largest: %d\n", findSecondLargest(arr, n));
    return 0;
}
```
**Time Complexity**: O(n)
**Space Complexity**: O(1)

---

### Problem 2: Move Zeros to End (Easy)
Move all zeros to the end while maintaining order of other elements.

```c
void moveZerosToEnd(int arr[], int n) {
    int nonZeroPos = 0;

    // Move non-zero elements forward
    for (int i = 0; i < n; i++) {
        if (arr[i] != 0) {
            arr[nonZeroPos++] = arr[i];
        }
    }

    // Fill remaining with zeros
    while (nonZeroPos < n) {
        arr[nonZeroPos++] = 0;
    }
}
```
**Time Complexity**: O(n)
**Space Complexity**: O(1)

---

### Problem 3: Find Majority Element (Medium)
Find element that appears more than n/2 times.

```c
// Boyer-Moore Voting Algorithm - O(n) time, O(1) space
int findMajorityElement(int arr[], int n) {
    int candidate = arr[0];
    int count = 1;

    // Find candidate
    for (int i = 1; i < n; i++) {
        if (arr[i] == candidate) {
            count++;
        } else {
            count--;
            if (count == 0) {
                candidate = arr[i];
                count = 1;
            }
        }
    }

    // Verify candidate
    count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == candidate) {
            count++;
        }
    }

    return (count > n / 2) ? candidate : -1;
}
```

---

### Problem 4: Kadane's Algorithm - Maximum Subarray Sum (Medium)
Find maximum sum of contiguous subarray.

```c
#include <limits.h>

int maxSubarraySum(int arr[], int n) {
    int maxSoFar = INT_MIN;
    int maxEndingHere = 0;

    for (int i = 0; i < n; i++) {
        maxEndingHere += arr[i];

        if (maxSoFar < maxEndingHere) {
            maxSoFar = maxEndingHere;
        }

        if (maxEndingHere < 0) {
            maxEndingHere = 0;
        }
    }

    return maxSoFar;
}
```
**Time Complexity**: O(n)
**Space Complexity**: O(1)

---

### Problem 5: Find Peak Element (Medium)
Find an element greater than its neighbors.

```c
int findPeakElement(int arr[], int n) {
    int left = 0, right = n - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] < arr[mid + 1]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left;
}
```
**Time Complexity**: O(log n)
**Space Complexity**: O(1)

---

### Problem 6: Trapping Rain Water (Hard)
Calculate water trapped between bars.

```c
int trapRainWater(int height[], int n) {
    if (n <= 2) return 0;

    int left = 0, right = n - 1;
    int leftMax = 0, rightMax = 0;
    int water = 0;

    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= leftMax) {
                leftMax = height[left];
            } else {
                water += leftMax - height[left];
            }
            left++;
        } else {
            if (height[right] >= rightMax) {
                rightMax = height[right];
            } else {
                water += rightMax - height[right];
            }
            right--;
        }
    }

    return water;
}
```
**Time Complexity**: O(n)
**Space Complexity**: O(1)

---

### Problem 7: Longest Common Prefix (Easy)
Find longest common prefix among strings.

```c
#include <string.h>

void longestCommonPrefix(char* strs[], int n, char* result) {
    if (n == 0) {
        result[0] = '\0';
        return;
    }

    int minLen = strlen(strs[0]);
    for (int i = 1; i < n; i++) {
        int len = strlen(strs[i]);
        if (len < minLen) minLen = len;
    }

    int i = 0;
    for (i = 0; i < minLen; i++) {
        char current = strs[0][i];
        for (int j = 1; j < n; j++) {
            if (strs[j][i] != current) {
                goto done;
            }
        }
    }
done:
    strncpy(result, strs[0], i);
    result[i] = '\0';
}
```

---

### Problem 8: Product of Array Except Self (Medium)
Return array where each element is product of all others.

```c
// Without division - O(n) time, O(1) extra space
void productExceptSelf(int arr[], int n, int result[]) {
    // Calculate left products
    result[0] = 1;
    for (int i = 1; i < n; i++) {
        result[i] = result[i - 1] * arr[i - 1];
    }

    // Calculate right products and multiply
    int right = 1;
    for (int i = n - 1; i >= 0; i--) {
        result[i] *= right;
        right *= arr[i];
    }
}
```

---

### Problem 9: Find All Duplicates (Medium)
Find all duplicates in array where elements are in range [1, n].

```c
void findDuplicates(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int index = abs(arr[i]) - 1;
        if (arr[index] < 0) {
            printf("%d ", abs(arr[i]));
        } else {
            arr[index] = -arr[index];
        }
    }
}
```
**Time Complexity**: O(n)
**Space Complexity**: O(1)

---

### Problem 10: Longest Increasing Subsequence (Hard)
Find length of longest increasing subsequence.

```c
// Dynamic Programming - O(n²)
int lengthOfLIS(int arr[], int n) {
    int dp[n];
    for (int i = 0; i < n; i++) dp[i] = 1;

    int maxLength = 1;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
            }
        }
        if (dp[i] > maxLength) {
            maxLength = dp[i];
        }
    }

    return maxLength;
}
```

---

## Summary

### Key Concepts
- Arrays provide O(1) access but expensive insertion/deletion
- Two-pointer technique reduces O(n²) to O(n)
- Sliding window optimizes subarray problems
- String problems often use frequency arrays
- Pattern matching: Naive O(nm), KMP O(n+m)

### Complexity Reference

| Operation | Unsorted | Sorted |
|-----------|----------|--------|
| Access | O(1) | O(1) |
| Search | O(n) | O(log n) |
| Insert | O(1) end | O(n) |
| Delete | O(n) | O(n) |

### Next Steps
- Practice on LeetCode, HackerRank
- Study linked lists next
- Learn advanced string algorithms (Rabin-Karp, Z-algorithm)

---

**Master arrays and strings - they're the foundation of DSA!**
