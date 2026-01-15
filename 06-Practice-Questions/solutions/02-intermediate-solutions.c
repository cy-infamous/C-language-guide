/**
 * Solutions for Intermediate Exercises
 *
 * This file contains complete, runnable solutions for selected
 * intermediate problems. Each solution includes detailed comments
 * explaining the approach and implementation.
 *
 * Compile: gcc 02-intermediate-solutions.c -o intermediate -lm
 * Run: ./intermediate
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

// ============================================================================
// SOLUTION 1: Prime Numbers in Range
// ============================================================================

/**
 * Check if a number is prime
 * Time Complexity: O(√n)
 * Space Complexity: O(1)
 */
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    int limit = sqrt(n);
    for (int i = 3; i <= limit; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

/**
 * Print all prime numbers in a given range
 * Time Complexity: O((end-start) × √n)
 */
void solution1_primeInRange() {
    int start, end;

    printf("\n=== Solution 1: Prime Numbers in Range ===\n");
    printf("Enter start of range: ");
    scanf("%d", &start);
    printf("Enter end of range: ");
    scanf("%d", &end);

    printf("Prime numbers between %d and %d:\n", start, end);

    int count = 0;
    for (int i = start; i <= end; i++) {
        if (isPrime(i)) {
            printf("%d ", i);
            count++;
        }
    }

    printf("\nTotal primes found: %d\n", count);
}

// ============================================================================
// SOLUTION 2: GCD and LCM
// ============================================================================

/**
 * Calculate GCD using Euclidean Algorithm
 * Time Complexity: O(log(min(a, b)))
 * Space Complexity: O(1)
 */
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/**
 * Calculate LCM using the formula: LCM(a,b) = (a × b) / GCD(a,b)
 */
long long lcm(int a, int b) {
    return ((long long)a * b) / gcd(a, b);
}

void solution2_gcdLcm() {
    int a, b;

    printf("\n=== Solution 2: GCD and LCM ===\n");
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    int g = gcd(a, b);
    long long l = lcm(a, b);

    printf("GCD: %d\n", g);
    printf("LCM: %lld\n", l);
}

// ============================================================================
// SOLUTION 8: Binary Search
// ============================================================================

/**
 * Binary Search - Iterative Implementation
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */
int binarySearchIterative(int arr[], int n, int target) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;  // Prevents overflow

        if (arr[mid] == target) {
            return mid;  // Found
        } else if (arr[mid] < target) {
            left = mid + 1;  // Search right half
        } else {
            right = mid - 1;  // Search left half
        }
    }

    return -1;  // Not found
}

/**
 * Binary Search - Recursive Implementation
 * Time Complexity: O(log n)
 * Space Complexity: O(log n) due to recursion stack
 */
int binarySearchRecursive(int arr[], int left, int right, int target) {
    if (left > right) {
        return -1;  // Base case: not found
    }

    int mid = left + (right - left) / 2;

    if (arr[mid] == target) {
        return mid;  // Base case: found
    } else if (arr[mid] < target) {
        return binarySearchRecursive(arr, mid + 1, right, target);  // Search right
    } else {
        return binarySearchRecursive(arr, left, mid - 1, target);  // Search left
    }
}

void solution8_binarySearch() {
    int n, target;

    printf("\n=== Solution 8: Binary Search ===\n");
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    printf("Enter %d sorted integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter number to search: ");
    scanf("%d", &target);

    // Iterative search
    int resultIter = binarySearchIterative(arr, n, target);
    printf("Iterative search: ");
    if (resultIter != -1) {
        printf("Found at index %d\n", resultIter);
    } else {
        printf("Not found\n");
    }

    // Recursive search
    int resultRec = binarySearchRecursive(arr, 0, n - 1, target);
    printf("Recursive search: ");
    if (resultRec != -1) {
        printf("Found at index %d\n", resultRec);
    } else {
        printf("Not found\n");
    }

    free(arr);
}

// ============================================================================
// SOLUTION 9: Bubble Sort
// ============================================================================

/**
 * Bubble Sort Implementation with Optimization
 * Time Complexity: O(n²) worst case, O(n) best case (already sorted)
 * Space Complexity: O(1)
 */
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;

        // Last i elements are already in place
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }

        // If no swapping happened, array is already sorted
        if (!swapped) {
            break;
        }
    }
}

void solution9_bubbleSort() {
    int n;

    printf("\n=== Solution 9: Bubble Sort ===\n");
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    bubbleSort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
}

// ============================================================================
// SOLUTION 15: Palindrome String
// ============================================================================

/**
 * Check if a string is a palindrome (ignoring spaces and case)
 * Time Complexity: O(n)
 * Space Complexity: O(n) for cleaned string
 */
bool isPalindrome(const char *str) {
    int len = strlen(str);

    // Create a cleaned version (no spaces, lowercase)
    char *cleaned = (char *)malloc((len + 1) * sizeof(char));
    int k = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] != ' ') {
            cleaned[k++] = tolower(str[i]);
        }
    }
    cleaned[k] = '\0';

    // Check palindrome using two pointers
    int left = 0;
    int right = k - 1;
    bool result = true;

    while (left < right) {
        if (cleaned[left] != cleaned[right]) {
            result = false;
            break;
        }
        left++;
        right--;
    }

    free(cleaned);
    return result;
}

void solution15_palindrome() {
    char str[1000];

    printf("\n=== Solution 15: Palindrome String ===\n");
    printf("Enter a string: ");
    getchar();  // Consume newline from previous input
    fgets(str, sizeof(str), stdin);

    // Remove trailing newline if present
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    if (isPalindrome(str)) {
        printf("'%s' is a Palindrome\n", str);
    } else {
        printf("'%s' is Not a Palindrome\n", str);
    }
}

// ============================================================================
// SOLUTION 18: Swap Using Pointers
// ============================================================================

/**
 * Swap two integers using pointers
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void solution18_swapPointers() {
    int a, b;

    printf("\n=== Solution 18: Swap Using Pointers ===\n");
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    printf("Before swap: a = %d, b = %d\n", a, b);

    swap(&a, &b);

    printf("After swap: a = %d, b = %d\n", a, b);
}

// ============================================================================
// SOLUTION 20: Frequency of Elements
// ============================================================================

/**
 * Count frequency of each element in array
 * Time Complexity: O(n²) for this simple approach
 * Space Complexity: O(1) extra space
 */
void solution20_frequency() {
    int n;

    printf("\n=== Solution 20: Frequency of Elements ===\n");
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    bool *counted = (bool *)calloc(n, sizeof(bool));

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("\nElement Frequency:\n");

    for (int i = 0; i < n; i++) {
        if (counted[i]) {
            continue;  // Already counted this element
        }

        int count = 1;
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
                counted[j] = true;  // Mark as counted
            }
        }

        printf("%d: %d\n", arr[i], count);
    }

    free(arr);
    free(counted);
}

// ============================================================================
// MAIN FUNCTION - Menu Driven
// ============================================================================

void displayMenu() {
    printf("\n========================================\n");
    printf("Intermediate Problems - Solution Demo\n");
    printf("========================================\n");
    printf("1.  Prime Numbers in Range\n");
    printf("2.  GCD and LCM\n");
    printf("8.  Binary Search\n");
    printf("9.  Bubble Sort\n");
    printf("15. Palindrome String\n");
    printf("18. Swap Using Pointers\n");
    printf("20. Frequency of Elements\n");
    printf("0.  Exit\n");
    printf("========================================\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;

    printf("Intermediate C Programming Solutions\n");
    printf("Demonstrating various problem solutions\n");

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                solution1_primeInRange();
                break;
            case 2:
                solution2_gcdLcm();
                break;
            case 8:
                solution8_binarySearch();
                break;
            case 9:
                solution9_bubbleSort();
                break;
            case 15:
                solution15_palindrome();
                break;
            case 18:
                solution18_swapPointers();
                break;
            case 20:
                solution20_frequency();
                break;
            case 0:
                printf("\nThank you for using the solution demo!\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }

        if (choice != 0) {
            printf("\nPress Enter to continue...");
            getchar();
            getchar();  // Wait for user
        }

    } while (choice != 0);

    return 0;
}

/**
 * COMPILATION AND RUNNING:
 *
 * To compile:
 * gcc 02-intermediate-solutions.c -o intermediate -lm -Wall
 *
 * To run:
 * ./intermediate (Linux/Mac)
 * intermediate.exe (Windows)
 *
 * NOTES:
 * - The -lm flag links the math library for sqrt() function
 * - All solutions use dynamic memory where appropriate
 * - Error handling is included for invalid inputs
 * - Memory is properly freed to prevent leaks
 *
 * LEARNING POINTS:
 * 1. Function decomposition for clean code
 * 2. Proper use of pointers and dynamic memory
 * 3. Algorithm optimization techniques
 * 4. Input validation and error handling
 * 5. Time and space complexity considerations
 */
