/**
 * Solutions for Data Structures Problems
 *
 * This file contains complete implementations of fundamental data structures
 * including linked lists, stacks, queues, and trees with detailed comments.
 *
 * Compile: gcc 04-data-structures-solutions.c -o datastructures
 * Run: ./datastructures
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// ============================================================================
// LINKED LIST - Solutions 1-4
// ============================================================================

// Node structure for singly linked list
typedef struct Node {
    int data;
    struct Node *next;
} Node;

/**
 * Create a new node
 * Time: O(1), Space: O(1)
 */
Node* createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/**
 * Insert at the beginning of linked list
 * Time: O(1), Space: O(1)
 */
void insertBegin(Node **head, int data) {
    Node *newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

/**
 * Insert at the end of linked list
 * Time: O(n), Space: O(1)
 */
void insertEnd(Node **head, int data) {
    Node *newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

/**
 * Delete a node by value
 * Time: O(n), Space: O(1)
 */
bool deleteByValue(Node **head, int data) {
    if (*head == NULL) {
        return false;
    }

    // If head node holds the data
    if ((*head)->data == data) {
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);
        return true;
    }

    // Search for the node to be deleted
    Node *current = *head;
    while (current->next != NULL && current->next->data != data) {
        current = current->next;
    }

    // If data was not present
    if (current->next == NULL) {
        return false;
    }

    // Delete the node
    Node *temp = current->next;
    current->next = current->next->next;
    free(temp);
    return true;
}

/**
 * Display linked list
 * Time: O(n), Space: O(1)
 */
void displayList(Node *head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    Node *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

/**
 * Search for a value in linked list
 * Time: O(n), Space: O(1)
 */
int searchList(Node *head, int data) {
    Node *temp = head;
    int position = 0;

    while (temp != NULL) {
        if (temp->data == data) {
            return position;
        }
        temp = temp->next;
        position++;
    }

    return -1;  // Not found
}

/**
 * SOLUTION 2: Reverse a Linked List (Iterative)
 * Time: O(n), Space: O(1)
 */
void reverseListIterative(Node **head) {
    Node *prev = NULL;
    Node *current = *head;
    Node *next = NULL;

    while (current != NULL) {
        next = current->next;  // Store next
        current->next = prev;  // Reverse current node's pointer
        prev = current;        // Move prev forward
        current = next;        // Move current forward
    }

    *head = prev;
}

/**
 * SOLUTION 2: Reverse a Linked List (Recursive)
 * Time: O(n), Space: O(n) due to recursion stack
 */
Node* reverseListRecursiveHelper(Node *current, Node *prev) {
    if (current == NULL) {
        return prev;
    }

    Node *next = current->next;
    current->next = prev;
    return reverseListRecursiveHelper(next, current);
}

void reverseListRecursive(Node **head) {
    *head = reverseListRecursiveHelper(*head, NULL);
}

/**
 * SOLUTION 3: Detect Cycle using Floyd's Algorithm
 * Time: O(n), Space: O(1)
 */
bool detectCycle(Node *head) {
    if (head == NULL || head->next == NULL) {
        return false;
    }

    Node *slow = head;
    Node *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;          // Move 1 step
        fast = fast->next->next;    // Move 2 steps

        if (slow == fast) {
            return true;  // Cycle detected
        }
    }

    return false;  // No cycle
}

/**
 * SOLUTION 4: Find Middle Element
 * Time: O(n), Space: O(1)
 */
int findMiddle(Node *head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return -1;
    }

    Node *slow = head;
    Node *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow->data;
}

/**
 * Free entire linked list
 */
void freeList(Node **head) {
    Node *temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

// ============================================================================
// STACK - Solutions 11-12
// ============================================================================

#define MAX_STACK_SIZE 100

// Stack using array
typedef struct Stack {
    int items[MAX_STACK_SIZE];
    int top;
} Stack;

/**
 * Initialize stack
 * Time: O(1)
 */
void initStack(Stack *s) {
    s->top = -1;
}

/**
 * Check if stack is empty
 * Time: O(1)
 */
bool isStackEmpty(Stack *s) {
    return s->top == -1;
}

/**
 * Check if stack is full
 * Time: O(1)
 */
bool isStackFull(Stack *s) {
    return s->top == MAX_STACK_SIZE - 1;
}

/**
 * Push element onto stack
 * Time: O(1), Space: O(1)
 */
bool push(Stack *s, int data) {
    if (isStackFull(s)) {
        printf("Stack Overflow!\n");
        return false;
    }

    s->items[++s->top] = data;
    return true;
}

/**
 * Pop element from stack
 * Time: O(1), Space: O(1)
 */
int pop(Stack *s) {
    if (isStackEmpty(s)) {
        printf("Stack Underflow!\n");
        return INT_MIN;
    }

    return s->items[s->top--];
}

/**
 * Peek at top element
 * Time: O(1)
 */
int peek(Stack *s) {
    if (isStackEmpty(s)) {
        printf("Stack is empty!\n");
        return INT_MIN;
    }

    return s->items[s->top];
}

/**
 * Display stack
 */
void displayStack(Stack *s) {
    if (isStackEmpty(s)) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack (top to bottom): ");
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->items[i]);
    }
    printf("\n");
}

/**
 * SOLUTION 13: Balanced Parentheses Checker
 * Time: O(n), Space: O(n)
 */
bool isMatchingPair(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '{' && closing == '}') ||
           (opening == '[' && closing == ']');
}

bool areParenthesesBalanced(const char *expr) {
    Stack s;
    initStack(&s);

    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];

        // Push opening brackets
        if (ch == '(' || ch == '{' || ch == '[') {
            push(&s, ch);
        }
        // Check closing brackets
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (isStackEmpty(&s)) {
                return false;  // Unmatched closing bracket
            }

            char top = pop(&s);
            if (!isMatchingPair(top, ch)) {
                return false;  // Mismatched pair
            }
        }
    }

    // If stack is empty, all brackets matched
    return isStackEmpty(&s);
}

// ============================================================================
// QUEUE - Solutions 16-17
// ============================================================================

#define MAX_QUEUE_SIZE 100

// Circular Queue using array
typedef struct Queue {
    int items[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int size;
} Queue;

/**
 * Initialize queue
 * Time: O(1)
 */
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

/**
 * Check if queue is empty
 * Time: O(1)
 */
bool isQueueEmpty(Queue *q) {
    return q->size == 0;
}

/**
 * Check if queue is full
 * Time: O(1)
 */
bool isQueueFull(Queue *q) {
    return q->size == MAX_QUEUE_SIZE;
}

/**
 * Enqueue (add to rear)
 * Time: O(1), Space: O(1)
 */
bool enqueue(Queue *q, int data) {
    if (isQueueFull(q)) {
        printf("Queue Overflow!\n");
        return false;
    }

    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->items[q->rear] = data;
    q->size++;
    return true;
}

/**
 * Dequeue (remove from front)
 * Time: O(1), Space: O(1)
 */
int dequeue(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Queue Underflow!\n");
        return INT_MIN;
    }

    int data = q->items[q->front];
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    q->size--;
    return data;
}

/**
 * Get front element
 * Time: O(1)
 */
int getFront(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty!\n");
        return INT_MIN;
    }

    return q->items[q->front];
}

/**
 * Display queue
 */
void displayQueue(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue (front to rear): ");
    int i = q->front;
    for (int count = 0; count < q->size; count++) {
        printf("%d ", q->items[i]);
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
    printf("\n");
}

// ============================================================================
// BINARY TREE - Solution 21
// ============================================================================

// Tree node structure
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

/**
 * Create a new tree node
 * Time: O(1)
 */
TreeNode* createTreeNode(int data) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/**
 * SOLUTION 21: Tree Traversals
 */

// Inorder: Left -> Root -> Right
void inorderTraversal(TreeNode *root) {
    if (root == NULL) return;

    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

// Preorder: Root -> Left -> Right
void preorderTraversal(TreeNode *root) {
    if (root == NULL) return;

    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// Postorder: Left -> Right -> Root
void postorderTraversal(TreeNode *root) {
    if (root == NULL) return;

    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
}

/**
 * Free entire tree
 */
void freeTree(TreeNode *root) {
    if (root == NULL) return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// ============================================================================
// DEMO FUNCTIONS
// ============================================================================

void demoLinkedList() {
    printf("\n=== Linked List Demo ===\n");

    Node *head = NULL;

    // Insert operations
    insertBegin(&head, 10);
    insertBegin(&head, 20);
    insertEnd(&head, 5);
    insertEnd(&head, 15);

    printf("List after insertions: ");
    displayList(head);

    // Search
    int searchVal = 5;
    int pos = searchList(head, searchVal);
    printf("Searching for %d: %s\n", searchVal,
           pos != -1 ? "Found" : "Not found");

    // Find middle
    printf("Middle element: %d\n", findMiddle(head));

    // Reverse
    printf("Original list: ");
    displayList(head);

    reverseListIterative(&head);
    printf("After reversing: ");
    displayList(head);

    // Delete
    deleteByValue(&head, 20);
    printf("After deleting 20: ");
    displayList(head);

    freeList(&head);
}

void demoStack() {
    printf("\n=== Stack Demo ===\n");

    Stack s;
    initStack(&s);

    // Push operations
    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    displayStack(&s);

    printf("Top element: %d\n", peek(&s));

    // Pop operation
    printf("Popped: %d\n", pop(&s));
    displayStack(&s);

    // Balanced parentheses check
    printf("\n--- Balanced Parentheses Check ---\n");
    const char *expr1 = "{[()]}";
    const char *expr2 = "{[(])}";

    printf("Expression: %s -> %s\n", expr1,
           areParenthesesBalanced(expr1) ? "Balanced" : "Not Balanced");
    printf("Expression: %s -> %s\n", expr2,
           areParenthesesBalanced(expr2) ? "Balanced" : "Not Balanced");
}

void demoQueue() {
    printf("\n=== Queue Demo ===\n");

    Queue q;
    initQueue(&q);

    // Enqueue operations
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);

    displayQueue(&q);

    printf("Front element: %d\n", getFront(&q));

    // Dequeue operations
    printf("Dequeued: %d\n", dequeue(&q));
    printf("Dequeued: %d\n", dequeue(&q));

    displayQueue(&q);
}

void demoBinaryTree() {
    printf("\n=== Binary Tree Demo ===\n");

    // Create a sample tree:
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5

    TreeNode *root = createTreeNode(1);
    root->left = createTreeNode(2);
    root->right = createTreeNode(3);
    root->left->left = createTreeNode(4);
    root->left->right = createTreeNode(5);

    printf("Inorder traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Preorder traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Postorder traversal: ");
    postorderTraversal(root);
    printf("\n");

    freeTree(root);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    printf("=========================================\n");
    printf("Data Structures Solutions Demo\n");
    printf("=========================================\n");

    demoLinkedList();
    demoStack();
    demoQueue();
    demoBinaryTree();

    printf("\n=========================================\n");
    printf("Demo completed successfully!\n");
    printf("=========================================\n");

    return 0;
}

/**
 * COMPILATION AND RUNNING:
 *
 * To compile:
 * gcc 04-data-structures-solutions.c -o datastructures -Wall
 *
 * To run:
 * ./datastructures
 *
 * KEY CONCEPTS DEMONSTRATED:
 *
 * 1. LINKED LISTS
 *    - Dynamic memory allocation
 *    - Pointer manipulation
 *    - Traversal algorithms
 *    - Floyd's cycle detection
 *    - Two-pointer technique
 *
 * 2. STACKS
 *    - LIFO principle
 *    - Array-based implementation
 *    - Applications (parentheses matching)
 *    - Overflow/underflow handling
 *
 * 3. QUEUES
 *    - FIFO principle
 *    - Circular array implementation
 *    - Efficient space utilization
 *
 * 4. BINARY TREES
 *    - Recursive tree traversals
 *    - DFS (Depth-First Search)
 *    - Memory management
 *
 * TIME COMPLEXITIES SUMMARY:
 * - Linked List insertion at begin: O(1)
 * - Linked List insertion at end: O(n)
 * - Linked List search: O(n)
 * - Stack push/pop: O(1)
 * - Queue enqueue/dequeue: O(1)
 * - Tree traversals: O(n)
 *
 * SPACE COMPLEXITIES:
 * - All iterative operations: O(1) extra space
 * - Recursive operations: O(h) where h is height/depth
 */
