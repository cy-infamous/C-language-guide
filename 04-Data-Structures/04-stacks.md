# Stacks - Complete Guide

## Table of Contents
1. [Introduction to Stacks](#introduction-to-stacks)
2. [Array Implementation](#array-implementation)
3. [Linked List Implementation](#linked-list-implementation)
4. [Stack Applications](#stack-applications)
5. [Expression Evaluation](#expression-evaluation)
6. [Advanced Problems](#advanced-problems)
7. [Practice Problems](#practice-problems)

---

## Introduction to Stacks

### What is a Stack?
A **stack** is a linear data structure that follows the **LIFO** (Last In, First Out) principle. The last element added is the first one to be removed.

### Real-World Examples
- Stack of plates
- Browser back button
- Undo functionality in editors
- Function call stack

### Visual Representation
```
        TOP
         ↓
      ┌─────┐
      │  30 │  ← Last In, First Out
      ├─────┤
      │  20 │
      ├─────┤
      │  10 │
      └─────┘
```

### Basic Operations

| Operation | Description | Time Complexity |
|-----------|-------------|-----------------|
| `push(x)` | Add element to top | O(1) |
| `pop()` | Remove top element | O(1) |
| `peek()`/`top()` | View top element | O(1) |
| `isEmpty()` | Check if empty | O(1) |
| `isFull()` | Check if full (array) | O(1) |
| `size()` | Get number of elements | O(1) |

### Stack Operations Visualization
```
Initial:  Empty
          ┌─────┐
          │     │
          └─────┘

push(10): ┌─────┐
          │  10 │
          └─────┘

push(20): ┌─────┐
          │  20 │
          ├─────┤
          │  10 │
          └─────┘

push(30): ┌─────┐
          │  30 │ ← TOP
          ├─────┤
          │  20 │
          ├─────┤
          │  10 │
          └─────┘

pop():    ┌─────┐
          │  20 │ ← TOP (30 removed)
          ├─────┤
          │  10 │
          └─────┘
```

---

## Array Implementation

### Structure Definition

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int items[MAX_SIZE];
    int top;
} Stack;

// Initialize stack
void initStack(Stack* stack) {
    stack->top = -1;
}

// Check if empty
bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Check if full
bool isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

// Get size
int size(Stack* stack) {
    return stack->top + 1;
}

// Push operation - O(1)
bool push(Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack Overflow! Cannot push %d\n", value);
        return false;
    }

    stack->items[++stack->top] = value;
    return true;
}

// Pop operation - O(1)
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow! Cannot pop\n");
        return -1;
    }

    return stack->items[stack->top--];
}

// Peek/Top operation - O(1)
int peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return -1;
    }

    return stack->items[stack->top];
}

// Print stack
void printStack(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack (bottom to top): ");
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->items[i]);
    }
    printf("\n");
}

// Display stack vertically
void displayStack(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return;
    }

    printf("\n  TOP\n");
    printf("   ↓\n");
    for (int i = stack->top; i >= 0; i--) {
        printf("┌─────┐\n");
        printf("│ %3d │\n", stack->items[i]);
        printf("└─────┘\n");
    }
}

int main() {
    Stack stack;
    initStack(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    push(&stack, 40);

    displayStack(&stack);

    printf("\nTop element: %d\n", peek(&stack));
    printf("Popped: %d\n", pop(&stack));

    displayStack(&stack);

    return 0;
}
```

### Dynamic Array Stack

```c
typedef struct {
    int* items;
    int top;
    int capacity;
} DynamicStack;

// Initialize
DynamicStack* createStack(int capacity) {
    DynamicStack* stack = (DynamicStack*)malloc(sizeof(DynamicStack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->items = (int*)malloc(capacity * sizeof(int));
    return stack;
}

// Resize when full
void resize(DynamicStack* stack) {
    stack->capacity *= 2;
    stack->items = (int*)realloc(stack->items, stack->capacity * sizeof(int));
}

// Push with auto-resize
void pushDynamic(DynamicStack* stack, int value) {
    if (stack->top == stack->capacity - 1) {
        resize(stack);
    }
    stack->items[++stack->top] = value;
}

// Free memory
void freeStack(DynamicStack* stack) {
    free(stack->items);
    free(stack);
}
```

---

## Linked List Implementation

### Node Structure

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
    int size;
} LinkedStack;

// Initialize stack
void initLinkedStack(LinkedStack* stack) {
    stack->top = NULL;
    stack->size = 0;
}

// Check if empty
bool isEmptyLinked(LinkedStack* stack) {
    return stack->top == NULL;
}

// Get size
int sizeLinked(LinkedStack* stack) {
    return stack->size;
}

// Create new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Push operation - O(1)
void pushLinked(LinkedStack* stack, int value) {
    Node* newNode = createNode(value);
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

// Pop operation - O(1)
int popLinked(LinkedStack* stack) {
    if (isEmptyLinked(stack)) {
        printf("Stack Underflow!\n");
        return -1;
    }

    Node* temp = stack->top;
    int value = temp->data;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;

    return value;
}

// Peek operation - O(1)
int peekLinked(LinkedStack* stack) {
    if (isEmptyLinked(stack)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return stack->top->data;
}

// Print stack
void printLinkedStack(LinkedStack* stack) {
    if (isEmptyLinked(stack)) {
        printf("Stack is empty\n");
        return;
    }

    Node* current = stack->top;
    printf("Stack (top to bottom): ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Display vertically
void displayLinkedStack(LinkedStack* stack) {
    if (isEmptyLinked(stack)) {
        printf("Stack is empty\n");
        return;
    }

    printf("\n  TOP\n");
    printf("   ↓\n");

    Node* current = stack->top;
    while (current != NULL) {
        printf("┌─────┐\n");
        printf("│ %3d │\n", current->data);
        printf("└─────┘\n");
        if (current->next != NULL) {
            printf("   ↓\n");
        }
        current = current->next;
    }
}

// Free all nodes
void freeLinkedStack(LinkedStack* stack) {
    while (!isEmptyLinked(stack)) {
        popLinked(stack);
    }
}

int main() {
    LinkedStack stack;
    initLinkedStack(&stack);

    pushLinked(&stack, 10);
    pushLinked(&stack, 20);
    pushLinked(&stack, 30);
    pushLinked(&stack, 40);

    displayLinkedStack(&stack);

    printf("\nTop: %d\n", peekLinked(&stack));
    printf("Popped: %d\n", popLinked(&stack));

    displayLinkedStack(&stack);

    freeLinkedStack(&stack);

    return 0;
}
```

### Visual Comparison
```
Array Implementation:
┌─────────────────────┐
│ [10][20][30][40][_] │ Fixed size array
└─────────────────────┘
       ↑
      top = 3

Linked List Implementation:
TOP → [40|●] → [30|●] → [20|●] → [10|NULL]
      Dynamic, no size limit
```

---

## Stack Applications

### 1. Reverse a String

```c
#include <string.h>

void reverseString(char* str) {
    Stack stack;
    initStack(&stack);

    // Push all characters
    for (int i = 0; str[i] != '\0'; i++) {
        push(&stack, str[i]);
    }

    // Pop all characters
    int i = 0;
    while (!isEmpty(&stack)) {
        str[i++] = pop(&stack);
    }
}

int main() {
    char str[] = "Hello World";
    printf("Original: %s\n", str);

    reverseString(str);
    printf("Reversed: %s\n", str);

    return 0;
}

// Output:
// Original: Hello World
// Reversed: dlroW olleH
```

### 2. Check Balanced Parentheses

```c
#include <stdbool.h>
#include <string.h>

bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

bool areParenthesesBalanced(char* expr) {
    Stack stack;
    initStack(&stack);

    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];

        // Push opening brackets
        if (ch == '(' || ch == '[' || ch == '{') {
            push(&stack, ch);
        }
        // Check closing brackets
        else if (ch == ')' || ch == ']' || ch == '}') {
            if (isEmpty(&stack)) {
                return false;  // No matching opening bracket
            }

            char top = pop(&stack);
            if (!isMatchingPair(top, ch)) {
                return false;  // Mismatched pair
            }
        }
    }

    // Stack should be empty if balanced
    return isEmpty(&stack);
}

int main() {
    char expr1[] = "{[()]}";
    char expr2[] = "{[(])}";
    char expr3[] = "((())";

    printf("%s: %s\n", expr1, areParenthesesBalanced(expr1) ? "Balanced" : "Not Balanced");
    printf("%s: %s\n", expr2, areParenthesesBalanced(expr2) ? "Balanced" : "Not Balanced");
    printf("%s: %s\n", expr3, areParenthesesBalanced(expr3) ? "Balanced" : "Not Balanced");

    return 0;
}

// Output:
// {[()]}: Balanced
// {[(])}: Not Balanced
// ((()): Not Balanced
```

### 3. Next Greater Element

```c
// Find next greater element for each element - O(n)
void nextGreaterElement(int arr[], int n, int result[]) {
    Stack stack;
    initStack(&stack);

    // Process from right to left
    for (int i = n - 1; i >= 0; i--) {
        // Pop elements smaller than current
        while (!isEmpty(&stack) && peek(&stack) <= arr[i]) {
            pop(&stack);
        }

        // If stack empty, no greater element
        result[i] = isEmpty(&stack) ? -1 : peek(&stack);

        // Push current element
        push(&stack, arr[i]);
    }
}

int main() {
    int arr[] = {4, 5, 2, 10, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result[n];

    nextGreaterElement(arr, n, result);

    printf("Array:         ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\nNext Greater: ");
    for (int i = 0; i < n; i++) printf("%d ", result[i]);
    printf("\n");

    return 0;
}

// Output:
// Array:         4 5 2 10 8
// Next Greater:  5 10 10 -1 -1
```

### 4. Stock Span Problem

```c
// Calculate stock span for each day
void calculateSpan(int prices[], int n, int span[]) {
    Stack stack;
    initStack(&stack);

    // First day span is always 1
    span[0] = 1;
    push(&stack, 0);

    for (int i = 1; i < n; i++) {
        // Pop while stack not empty and top price <= current price
        while (!isEmpty(&stack) && prices[peek(&stack)] <= prices[i]) {
            pop(&stack);
        }

        // If stack empty, all previous days had lower price
        span[i] = isEmpty(&stack) ? (i + 1) : (i - peek(&stack));

        push(&stack, i);
    }
}

int main() {
    int prices[] = {100, 80, 60, 70, 60, 75, 85};
    int n = sizeof(prices) / sizeof(prices[0]);
    int span[n];

    calculateSpan(prices, n, span);

    printf("Day:   ");
    for (int i = 0; i < n; i++) printf("%d ", i + 1);
    printf("\nPrice: ");
    for (int i = 0; i < n; i++) printf("%d ", prices[i]);
    printf("\nSpan:  ");
    for (int i = 0; i < n; i++) printf("%d ", span[i]);
    printf("\n");

    return 0;
}

// Output:
// Day:   1 2 3 4 5 6 7
// Price: 100 80 60 70 60 75 85
// Span:  1 1 1 2 1 4 6
```

---

## Expression Evaluation

### 1. Infix to Postfix Conversion

```c
#include <ctype.h>

// Get operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Check if operator is right associative
bool isRightAssociative(char op) {
    return op == '^';
}

// Convert infix to postfix
void infixToPostfix(char* infix, char* postfix) {
    Stack stack;
    initStack(&stack);

    int j = 0;  // Index for postfix

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        // Skip whitespace
        if (ch == ' ') continue;

        // Operand: add to output
        if (isalnum(ch)) {
            postfix[j++] = ch;
        }
        // Left parenthesis: push to stack
        else if (ch == '(') {
            push(&stack, ch);
        }
        // Right parenthesis: pop until '('
        else if (ch == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[j++] = pop(&stack);
            }
            if (!isEmpty(&stack)) pop(&stack);  // Remove '('
        }
        // Operator
        else {
            while (!isEmpty(&stack) && peek(&stack) != '(' &&
                   (precedence(peek(&stack)) > precedence(ch) ||
                    (precedence(peek(&stack)) == precedence(ch) &&
                     !isRightAssociative(ch)))) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, ch);
        }
    }

    // Pop remaining operators
    while (!isEmpty(&stack)) {
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0';
}

int main() {
    char infix[] = "A+B*C-D/E";
    char postfix[100];

    infixToPostfix(infix, postfix);

    printf("Infix:    %s\n", infix);
    printf("Postfix:  %s\n", postfix);

    return 0;
}

// Output:
// Infix:    A+B*C-D/E
// Postfix:  ABC*+DE/-
```

### Conversion Examples
```
Infix:    A + B * C - D / E
Postfix:  A B C * + D E / -

Infix:    (A + B) * (C - D)
Postfix:  A B + C D - *

Infix:    A * B + C / D
Postfix:  A B * C D / +

Infix:    A ^ B ^ C  (right associative)
Postfix:  A B C ^ ^
```

### 2. Evaluate Postfix Expression

```c
int evaluatePostfix(char* postfix) {
    Stack stack;
    initStack(&stack);

    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        // Skip whitespace
        if (ch == ' ') continue;

        // Operand: push to stack
        if (isdigit(ch)) {
            push(&stack, ch - '0');
        }
        // Operator: pop two operands and apply
        else {
            int val2 = pop(&stack);
            int val1 = pop(&stack);

            switch (ch) {
                case '+': push(&stack, val1 + val2); break;
                case '-': push(&stack, val1 - val2); break;
                case '*': push(&stack, val1 * val2); break;
                case '/': push(&stack, val1 / val2); break;
                case '^': push(&stack, (int)pow(val1, val2)); break;
            }
        }
    }

    return pop(&stack);
}

int main() {
    char postfix[] = "231*+9-";

    printf("Postfix: %s\n", postfix);
    printf("Result: %d\n", evaluatePostfix(postfix));

    // 231*+9-
    // = 2 + (3*1) - 9
    // = 2 + 3 - 9
    // = -4

    return 0;
}
```

### 3. Infix Expression Evaluation

```c
// Evaluate infix expression directly
int evaluateInfix(char* infix) {
    Stack values;   // Stack for numbers
    Stack ops;      // Stack for operators
    initStack(&values);
    initStack(&ops);

    for (int i = 0; infix[i] != '\0'; i++) {
        if (infix[i] == ' ') continue;

        // Number: push to values stack
        if (isdigit(infix[i])) {
            int num = 0;
            while (i < strlen(infix) && isdigit(infix[i])) {
                num = num * 10 + (infix[i] - '0');
                i++;
            }
            i--;
            push(&values, num);
        }
        // Opening bracket: push to ops
        else if (infix[i] == '(') {
            push(&ops, infix[i]);
        }
        // Closing bracket: solve until '('
        else if (infix[i] == ')') {
            while (!isEmpty(&ops) && peek(&ops) != '(') {
                int val2 = pop(&values);
                int val1 = pop(&values);
                char op = pop(&ops);

                switch (op) {
                    case '+': push(&values, val1 + val2); break;
                    case '-': push(&values, val1 - val2); break;
                    case '*': push(&values, val1 * val2); break;
                    case '/': push(&values, val1 / val2); break;
                }
            }
            if (!isEmpty(&ops)) pop(&ops);  // Remove '('
        }
        // Operator
        else {
            while (!isEmpty(&ops) && precedence(peek(&ops)) >= precedence(infix[i])) {
                int val2 = pop(&values);
                int val1 = pop(&values);
                char op = pop(&ops);

                switch (op) {
                    case '+': push(&values, val1 + val2); break;
                    case '-': push(&values, val1 - val2); break;
                    case '*': push(&values, val1 * val2); break;
                    case '/': push(&values, val1 / val2); break;
                }
            }
            push(&ops, infix[i]);
        }
    }

    // Process remaining operators
    while (!isEmpty(&ops)) {
        int val2 = pop(&values);
        int val1 = pop(&values);
        char op = pop(&ops);

        switch (op) {
            case '+': push(&values, val1 + val2); break;
            case '-': push(&values, val1 - val2); break;
            case '*': push(&values, val1 * val2); break;
            case '/': push(&values, val1 / val2); break;
        }
    }

    return pop(&values);
}
```

---

## Advanced Problems

### 1. Min Stack (O(1) getMin)

```c
typedef struct {
    Stack dataStack;
    Stack minStack;
} MinStack;

void initMinStack(MinStack* ms) {
    initStack(&ms->dataStack);
    initStack(&ms->minStack);
}

void pushMin(MinStack* ms, int value) {
    push(&ms->dataStack, value);

    // Push to min stack if it's minimum
    if (isEmpty(&ms->minStack) || value <= peek(&ms->minStack)) {
        push(&ms->minStack, value);
    }
}

int popMin(MinStack* ms) {
    if (isEmpty(&ms->dataStack)) {
        printf("Stack is empty!\n");
        return -1;
    }

    int value = pop(&ms->dataStack);

    // Pop from min stack if it was minimum
    if (value == peek(&ms->minStack)) {
        pop(&ms->minStack);
    }

    return value;
}

int getMin(MinStack* ms) {
    if (isEmpty(&ms->minStack)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return peek(&ms->minStack);
}

int main() {
    MinStack ms;
    initMinStack(&ms);

    pushMin(&ms, 5);
    pushMin(&ms, 3);
    pushMin(&ms, 7);
    pushMin(&ms, 2);
    pushMin(&ms, 9);

    printf("Min: %d\n", getMin(&ms));  // 2

    popMin(&ms);  // Remove 9
    printf("Min: %d\n", getMin(&ms));  // 2

    popMin(&ms);  // Remove 2
    printf("Min: %d\n", getMin(&ms));  // 3

    return 0;
}
```

### 2. Largest Rectangle in Histogram

```c
int largestRectangleArea(int heights[], int n) {
    Stack stack;
    initStack(&stack);

    int maxArea = 0;
    int i = 0;

    while (i < n) {
        // If current bar is higher, push to stack
        if (isEmpty(&stack) || heights[i] >= heights[peek(&stack)]) {
            push(&stack, i++);
        }
        // Calculate area with top as smallest bar
        else {
            int top = pop(&stack);
            int width = isEmpty(&stack) ? i : i - peek(&stack) - 1;
            int area = heights[top] * width;

            if (area > maxArea) {
                maxArea = area;
            }
        }
    }

    // Process remaining bars
    while (!isEmpty(&stack)) {
        int top = pop(&stack);
        int width = isEmpty(&stack) ? i : i - peek(&stack) - 1;
        int area = heights[top] * width;

        if (area > maxArea) {
            maxArea = area;
        }
    }

    return maxArea;
}

// Example:
// heights = [2, 1, 5, 6, 2, 3]
// Result: 10 (bars at index 2-3 with height 5,6)
```

### 3. Valid Parentheses with Wild Cards

```c
bool isValidWithWildcard(char* s) {
    Stack leftParen;
    Stack asterisk;
    initStack(&leftParen);
    initStack(&asterisk);

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            push(&leftParen, i);
        } else if (s[i] == '*') {
            push(&asterisk, i);
        } else {  // ')'
            if (!isEmpty(&leftParen)) {
                pop(&leftParen);
            } else if (!isEmpty(&asterisk)) {
                pop(&asterisk);
            } else {
                return false;
            }
        }
    }

    // Match remaining '(' with '*'
    while (!isEmpty(&leftParen) && !isEmpty(&asterisk)) {
        if (peek(&leftParen) > peek(&asterisk)) {
            return false;
        }
        pop(&leftParen);
        pop(&asterisk);
    }

    return isEmpty(&leftParen);
}

// Example: "(*)" is valid
// '*' can represent ')', making it "()"
```

### 4. Daily Temperatures

```c
// Find next warmer day for each day
void dailyTemperatures(int temps[], int n, int result[]) {
    Stack stack;
    initStack(&stack);

    for (int i = 0; i < n; i++) {
        while (!isEmpty(&stack) && temps[i] > temps[peek(&stack)]) {
            int prevDay = pop(&stack);
            result[prevDay] = i - prevDay;
        }
        push(&stack, i);
    }

    // Days with no warmer temperature
    while (!isEmpty(&stack)) {
        result[pop(&stack)] = 0;
    }
}

int main() {
    int temps[] = {73, 74, 75, 71, 69, 72, 76, 73};
    int n = sizeof(temps) / sizeof(temps[0]);
    int result[n];

    dailyTemperatures(temps, n, result);

    printf("Temperatures: ");
    for (int i = 0; i < n; i++) printf("%d ", temps[i]);
    printf("\nDays to wait: ");
    for (int i = 0; i < n; i++) printf("%d ", result[i]);
    printf("\n");

    return 0;
}

// Output:
// Temperatures: 73 74 75 71 69 72 76 73
// Days to wait: 1 1 4 2 1 1 0 0
```

---

## Practice Problems

### Problem 1: Implement Two Stacks in One Array (Medium)
```c
typedef struct {
    int arr[MAX_SIZE];
    int top1;
    int top2;
} TwoStacks;

void initTwoStacks(TwoStacks* ts) {
    ts->top1 = -1;
    ts->top2 = MAX_SIZE;
}

void push1(TwoStacks* ts, int value) {
    if (ts->top1 < ts->top2 - 1) {
        ts->arr[++ts->top1] = value;
    } else {
        printf("Stack Overflow\n");
    }
}

void push2(TwoStacks* ts, int value) {
    if (ts->top1 < ts->top2 - 1) {
        ts->arr[--ts->top2] = value;
    } else {
        printf("Stack Overflow\n");
    }
}

int pop1(TwoStacks* ts) {
    if (ts->top1 >= 0) {
        return ts->arr[ts->top1--];
    }
    printf("Stack 1 Underflow\n");
    return -1;
}

int pop2(TwoStacks* ts) {
    if (ts->top2 < MAX_SIZE) {
        return ts->arr[ts->top2++];
    }
    printf("Stack 2 Underflow\n");
    return -1;
}
```

---

### Problem 2: Sort Stack (Medium)
```c
void insertSorted(Stack* stack, int value) {
    if (isEmpty(stack) || value > peek(stack)) {
        push(stack, value);
        return;
    }

    int temp = pop(stack);
    insertSorted(stack, value);
    push(stack, temp);
}

void sortStack(Stack* stack) {
    if (!isEmpty(stack)) {
        int temp = pop(stack);
        sortStack(stack);
        insertSorted(stack, temp);
    }
}
```

---

### Problem 3: Celebrity Problem (Medium)
Find celebrity who knows no one but everyone knows them.

```c
int findCelebrity(int matrix[][100], int n) {
    Stack stack;
    initStack(&stack);

    // Push all people
    for (int i = 0; i < n; i++) {
        push(&stack, i);
    }

    // Eliminate non-celebrities
    while (size(&stack) > 1) {
        int a = pop(&stack);
        int b = pop(&stack);

        if (matrix[a][b]) {
            // A knows B, so A is not celebrity
            push(&stack, b);
        } else {
            // A doesn't know B, so B is not celebrity
            push(&stack, a);
        }
    }

    int candidate = pop(&stack);

    // Verify candidate
    for (int i = 0; i < n; i++) {
        if (i != candidate) {
            if (matrix[candidate][i] || !matrix[i][candidate]) {
                return -1;  // No celebrity
            }
        }
    }

    return candidate;
}
```

---

### Problem 4: Decode String (Hard)
Decode "3[a2[c]]" to "accaccacc"

```c
#include <string.h>
#include <ctype.h>

void decodeString(char* s, char* result) {
    Stack numStack;
    Stack strStack;
    initStack(&numStack);
    initStack(&strStack);

    char current[1000] = "";
    int num = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (isdigit(s[i])) {
            num = num * 10 + (s[i] - '0');
        } else if (s[i] == '[') {
            push(&numStack, num);
            // Push current string (implementation detail)
            num = 0;
        } else if (s[i] == ']') {
            int repeatTimes = pop(&numStack);
            // Pop string and repeat
            // Append to current
        } else {
            // Append character to current
            int len = strlen(current);
            current[len] = s[i];
            current[len + 1] = '\0';
        }
    }

    strcpy(result, current);
}
```

---

### Problem 5: Trapping Rain Water (Hard)
```c
int trapRainWater(int height[], int n) {
    if (n <= 2) return 0;

    Stack stack;
    initStack(&stack);
    int water = 0;

    for (int i = 0; i < n; i++) {
        while (!isEmpty(&stack) && height[i] > height[peek(&stack)]) {
            int top = pop(&stack);

            if (isEmpty(&stack)) break;

            int distance = i - peek(&stack) - 1;
            int boundedHeight = (height[i] < height[peek(&stack)] ?
                                 height[i] : height[peek(&stack)]) - height[top];

            water += distance * boundedHeight;
        }
        push(&stack, i);
    }

    return water;
}
```

---

## Summary

### Complexity Comparison

| Implementation | Push | Pop | Peek | Space |
|----------------|------|-----|------|-------|
| Array | O(1) | O(1) | O(1) | O(n) fixed |
| Linked List | O(1) | O(1) | O(1) | O(n) dynamic |
| Dynamic Array | O(1)* | O(1) | O(1) | O(n) resizable |

*Amortized O(1) for dynamic array with resizing

### Key Takeaways
- Stack follows LIFO principle
- Perfect for: reversing, matching, parsing
- Two implementations: array (fixed) vs linked list (dynamic)
- Used in: function calls, expression evaluation, backtracking
- Master monotonic stack pattern for interview problems

### Common Patterns
1. **Monotonic Stack**: Next greater/smaller element
2. **Two Stacks**: Simulate queue, implement min/max stack
3. **Expression**: Infix/postfix conversion and evaluation
4. **Matching**: Parentheses, tags, palindrome

**Practice stack problems daily - they're fundamental to many algorithms!**
