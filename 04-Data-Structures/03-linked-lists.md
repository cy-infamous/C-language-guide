# Linked Lists - Complete Guide

## Table of Contents
1. [Introduction to Linked Lists](#introduction-to-linked-lists)
2. [Singly Linked List](#singly-linked-list)
3. [Doubly Linked List](#doubly-linked-list)
4. [Circular Linked List](#circular-linked-list)
5. [Advanced Operations](#advanced-operations)
6. [Common Algorithms](#common-algorithms)
7. [Practice Problems](#practice-problems)

---

## Introduction to Linked Lists

### What is a Linked List?
A **linked list** is a linear data structure where elements are stored in nodes. Each node contains:
- **Data**: The value stored
- **Pointer(s)**: Reference to next (and possibly previous) node

### Array vs Linked List

```
Array:
┌────┬────┬────┬────┬────┐
│ 10 │ 20 │ 30 │ 40 │ 50 │  (Contiguous memory)
└────┴────┴────┴────┴────┘

Linked List:
┌────┬────┐    ┌────┬────┐    ┌────┬────┐    ┌────┬────┐
│ 10 │ ●──┼───>│ 20 │ ●──┼───>│ 30 │ ●──┼───>│ 40 │ NULL│
└────┴────┘    └────┴────┘    └────┴────┘    └────┴────┘
  Node 1         Node 2         Node 3         Node 4
```

### Comparison Table

| Feature | Array | Linked List |
|---------|-------|-------------|
| Memory | Contiguous | Scattered |
| Size | Fixed | Dynamic |
| Access Time | O(1) | O(n) |
| Insert at Beginning | O(n) | O(1) |
| Insert at End | O(1) | O(n) without tail, O(1) with tail |
| Delete | O(n) | O(1) if pointer known |
| Memory Usage | Less | More (pointers) |
| Cache Performance | Better | Worse |

### When to Use Linked Lists?
- Frequent insertions/deletions
- Unknown size
- No random access needed
- Implementing stacks, queues, graphs

---

## Singly Linked List

### Structure
```
HEAD
  ↓
┌────┬────┐    ┌────┬────┐    ┌────┬────┐    ┌────┬────┐
│ 10 │ ●──┼───>│ 20 │ ●──┼───>│ 30 │ ●──┼───>│ 40 │ NULL│
└────┴────┘    └────┴────┘    └────┴────┘    └────┴────┘
```

### Basic Implementation

```c
#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Print list
void printList(Node* head) {
    Node* current = head;
    printf("List: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Count nodes
int countNodes(Node* head) {
    int count = 0;
    Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

int main() {
    // Create nodes
    Node* head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);

    printList(head);
    printf("Number of nodes: %d\n", countNodes(head));

    return 0;
}
```

### Insertion Operations

```c
// Insert at beginning - O(1)
Node* insertAtBeginning(Node* head, int data) {
    Node* newNode = createNode(data);
    newNode->next = head;
    return newNode;  // New head
}

// Insert at end - O(n)
Node* insertAtEnd(Node* head, int data) {
    Node* newNode = createNode(data);

    if (head == NULL) {
        return newNode;
    }

    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;

    return head;
}

// Insert after a given node - O(1) if node pointer known
void insertAfter(Node* prevNode, int data) {
    if (prevNode == NULL) {
        printf("Previous node cannot be NULL\n");
        return;
    }

    Node* newNode = createNode(data);
    newNode->next = prevNode->next;
    prevNode->next = newNode;
}

// Insert at position - O(n)
Node* insertAtPosition(Node* head, int data, int position) {
    if (position < 0) {
        printf("Invalid position\n");
        return head;
    }

    Node* newNode = createNode(data);

    if (position == 0) {
        newNode->next = head;
        return newNode;
    }

    Node* current = head;
    for (int i = 0; i < position - 1 && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Position out of bounds\n");
        free(newNode);
        return head;
    }

    newNode->next = current->next;
    current->next = newNode;

    return head;
}

// Visual example of insertion at beginning:
// Before: HEAD -> 20 -> 30 -> NULL
// After:  HEAD -> 10 -> 20 -> 30 -> NULL
```

### Deletion Operations

```c
// Delete first node - O(1)
Node* deleteFirst(Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }

    Node* temp = head;
    head = head->next;
    free(temp);

    return head;
}

// Delete last node - O(n)
Node* deleteLast(Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }

    if (head->next == NULL) {
        free(head);
        return NULL;
    }

    Node* current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    free(current->next);
    current->next = NULL;

    return head;
}

// Delete node with given value - O(n)
Node* deleteByValue(Node* head, int value) {
    if (head == NULL) {
        return NULL;
    }

    // If head node holds the value
    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    Node* current = head;
    while (current->next != NULL && current->next->data != value) {
        current = current->next;
    }

    if (current->next == NULL) {
        printf("Value not found\n");
        return head;
    }

    Node* temp = current->next;
    current->next = current->next->next;
    free(temp);

    return head;
}

// Delete at position - O(n)
Node* deleteAtPosition(Node* head, int position) {
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }

    if (position == 0) {
        Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    Node* current = head;
    for (int i = 0; i < position - 1 && current->next != NULL; i++) {
        current = current->next;
    }

    if (current->next == NULL) {
        printf("Position out of bounds\n");
        return head;
    }

    Node* temp = current->next;
    current->next = current->next->next;
    free(temp);

    return head;
}
```

### Search and Access

```c
// Search for value - O(n)
Node* search(Node* head, int value) {
    Node* current = head;
    while (current != NULL) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Get node at index - O(n)
Node* getNodeAt(Node* head, int index) {
    Node* current = head;
    int count = 0;

    while (current != NULL) {
        if (count == index) {
            return current;
        }
        count++;
        current = current->next;
    }

    return NULL;
}

// Get value at index
int getValueAt(Node* head, int index) {
    Node* node = getNodeAt(head, index);
    if (node == NULL) {
        printf("Index out of bounds\n");
        return -1;
    }
    return node->data;
}
```

### Complete Singly Linked List Implementation

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} LinkedList;

// Initialize list
void initList(LinkedList* list) {
    list->head = NULL;
    list->size = 0;
}

// Create node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Insert at beginning
void insertFront(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

// Insert at end
void insertBack(LinkedList* list, int data) {
    Node* newNode = createNode(data);

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

// Delete first occurrence of value
bool deleteValue(LinkedList* list, int value) {
    if (list->head == NULL) return false;

    if (list->head->data == value) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
        list->size--;
        return true;
    }

    Node* current = list->head;
    while (current->next != NULL && current->next->data != value) {
        current = current->next;
    }

    if (current->next == NULL) return false;

    Node* temp = current->next;
    current->next = current->next->next;
    free(temp);
    list->size--;
    return true;
}

// Print list
void printList(LinkedList* list) {
    Node* current = list->head;
    printf("List (%d elements): ", list->size);
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Free entire list
void freeList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->size = 0;
}

// Main function demonstrating usage
int main() {
    LinkedList list;
    initList(&list);

    insertFront(&list, 30);
    insertFront(&list, 20);
    insertFront(&list, 10);
    insertBack(&list, 40);
    insertBack(&list, 50);

    printList(&list);

    deleteValue(&list, 30);
    printList(&list);

    freeList(&list);

    return 0;
}
```

---

## Doubly Linked List

### Structure
```
        HEAD                                          TAIL
          ↓                                            ↓
┌────┬────┬────┐   ┌────┬────┬────┐   ┌────┬────┬────┐
│NULL│ 10 │ ●──┼──>│ ●──│ 20 │ ●──┼──>│ ●──│ 30 │NULL│
└────┴────┴────┘   └────┴────┴────┘   └────┴────┴────┘
       ↑   <──────────┘  ↑  <──────────┘
     prev             prev
```

### Implementation

```c
#include <stdio.h>
#include <stdlib.h>

// Doubly linked list node
typedef struct DNode {
    int data;
    struct DNode* prev;
    struct DNode* next;
} DNode;

// Create node
DNode* createDNode(int data) {
    DNode* newNode = (DNode*)malloc(sizeof(DNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Print forward
void printForward(DNode* head) {
    printf("Forward: ");
    DNode* current = head;
    while (current != NULL) {
        printf("%d <-> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Print backward
void printBackward(DNode* tail) {
    printf("Backward: ");
    DNode* current = tail;
    while (current != NULL) {
        printf("%d <-> ", current->data);
        current = current->prev;
    }
    printf("NULL\n");
}

// Insert at beginning - O(1)
DNode* insertAtBeginning(DNode* head, int data) {
    DNode* newNode = createDNode(data);

    if (head != NULL) {
        newNode->next = head;
        head->prev = newNode;
    }

    return newNode;
}

// Insert at end - O(n) without tail pointer
DNode* insertAtEnd(DNode* head, int data) {
    DNode* newNode = createDNode(data);

    if (head == NULL) {
        return newNode;
    }

    DNode* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
    newNode->prev = current;

    return head;
}

// Insert after a given node - O(1)
void insertAfter(DNode* prevNode, int data) {
    if (prevNode == NULL) {
        printf("Previous node cannot be NULL\n");
        return;
    }

    DNode* newNode = createDNode(data);
    newNode->next = prevNode->next;
    newNode->prev = prevNode;

    if (prevNode->next != NULL) {
        prevNode->next->prev = newNode;
    }

    prevNode->next = newNode;
}

// Insert before a given node - O(1)
DNode* insertBefore(DNode* head, DNode* nextNode, int data) {
    if (nextNode == NULL) {
        printf("Next node cannot be NULL\n");
        return head;
    }

    DNode* newNode = createDNode(data);
    newNode->prev = nextNode->prev;
    newNode->next = nextNode;

    if (nextNode->prev != NULL) {
        nextNode->prev->next = newNode;
    } else {
        head = newNode;  // New head
    }

    nextNode->prev = newNode;

    return head;
}

// Delete node - O(1) if pointer known
DNode* deleteNode(DNode* head, DNode* del) {
    if (head == NULL || del == NULL) {
        return head;
    }

    // If node to delete is head
    if (head == del) {
        head = del->next;
    }

    // Change next pointer
    if (del->next != NULL) {
        del->next->prev = del->prev;
    }

    // Change prev pointer
    if (del->prev != NULL) {
        del->prev->next = del->next;
    }

    free(del);
    return head;
}

// Delete by value
DNode* deleteByValue(DNode* head, int value) {
    if (head == NULL) return NULL;

    DNode* current = head;

    while (current != NULL) {
        if (current->data == value) {
            DNode* toDelete = current;
            head = deleteNode(head, toDelete);
            return head;
        }
        current = current->next;
    }

    printf("Value not found\n");
    return head;
}

// Reverse doubly linked list
DNode* reverse(DNode* head) {
    DNode* temp = NULL;
    DNode* current = head;

    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if (temp != NULL) {
        head = temp->prev;
    }

    return head;
}

int main() {
    DNode* head = NULL;

    // Build list: 10 <-> 20 <-> 30 <-> 40
    head = insertAtBeginning(head, 10);
    head = insertAtEnd(head, 20);
    head = insertAtEnd(head, 30);
    head = insertAtEnd(head, 40);

    printForward(head);

    // Find tail for backward print
    DNode* tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    printBackward(tail);

    // Delete node with value 20
    head = deleteByValue(head, 20);
    printForward(head);

    // Reverse list
    head = reverse(head);
    printf("After reversing:\n");
    printForward(head);

    return 0;
}
```

### Doubly Linked List with Head and Tail

```c
typedef struct {
    DNode* head;
    DNode* tail;
    int size;
} DoublyLinkedList;

void initDList(DoublyLinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// Insert at front - O(1)
void insertFront(DoublyLinkedList* list, int data) {
    DNode* newNode = createDNode(data);

    if (list->head == NULL) {
        list->head = list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
    list->size++;
}

// Insert at back - O(1) with tail pointer
void insertBack(DoublyLinkedList* list, int data) {
    DNode* newNode = createDNode(data);

    if (list->tail == NULL) {
        list->head = list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->size++;
}

// Delete from front - O(1)
void deleteFront(DoublyLinkedList* list) {
    if (list->head == NULL) return;

    DNode* temp = list->head;

    if (list->head == list->tail) {
        list->head = list->tail = NULL;
    } else {
        list->head = list->head->next;
        list->head->prev = NULL;
    }

    free(temp);
    list->size--;
}

// Delete from back - O(1) with tail pointer
void deleteBack(DoublyLinkedList* list) {
    if (list->tail == NULL) return;

    DNode* temp = list->tail;

    if (list->head == list->tail) {
        list->head = list->tail = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }

    free(temp);
    list->size--;
}
```

---

## Circular Linked List

### Singly Circular Linked List
```
        HEAD
          ↓
┌────┬────┐    ┌────┬────┐    ┌────┬────┐    ┌────┬────┐
│ 10 │ ●──┼───>│ 20 │ ●──┼───>│ 30 │ ●──┼───>│ 40 │ ●──┼───┐
└────┴────┘    └────┴────┘    └────┴────┘    └────┴────┘   │
    ↑                                                        │
    └────────────────────────────────────────────────────────┘
```

### Implementation

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Insert at beginning - O(n) to find last node
Node* insertAtBeginning(Node* head, int data) {
    Node* newNode = createNode(data);

    if (head == NULL) {
        newNode->next = newNode;  // Point to itself
        return newNode;
    }

    // Find last node
    Node* current = head;
    while (current->next != head) {
        current = current->next;
    }

    newNode->next = head;
    current->next = newNode;

    return newNode;  // New head
}

// Insert at end - O(n)
Node* insertAtEnd(Node* head, int data) {
    Node* newNode = createNode(data);

    if (head == NULL) {
        newNode->next = newNode;
        return newNode;
    }

    // Find last node
    Node* current = head;
    while (current->next != head) {
        current = current->next;
    }

    current->next = newNode;
    newNode->next = head;

    return head;
}

// Delete node with value - O(n)
Node* deleteNode(Node* head, int value) {
    if (head == NULL) return NULL;

    // If head node to be deleted
    if (head->data == value) {
        // Only one node
        if (head->next == head) {
            free(head);
            return NULL;
        }

        // Find last node
        Node* current = head;
        while (current->next != head) {
            current = current->next;
        }

        current->next = head->next;
        Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    // Search for node to delete
    Node* current = head;
    while (current->next != head && current->next->data != value) {
        current = current->next;
    }

    if (current->next == head) {
        printf("Value not found\n");
        return head;
    }

    Node* temp = current->next;
    current->next = current->next->next;
    free(temp);

    return head;
}

// Print circular list
void printCircular(Node* head) {
    if (head == NULL) {
        printf("Empty list\n");
        return;
    }

    Node* current = head;
    printf("Circular List: ");
    do {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != head);
    printf("(back to %d)\n", head->data);
}

// Check if list is circular
bool isCircular(Node* head) {
    if (head == NULL) return false;

    Node* current = head->next;
    while (current != NULL && current != head) {
        current = current->next;
    }

    return (current == head);
}

int main() {
    Node* head = NULL;

    head = insertAtEnd(head, 10);
    head = insertAtEnd(head, 20);
    head = insertAtEnd(head, 30);
    head = insertAtBeginning(head, 5);

    printCircular(head);

    head = deleteNode(head, 20);
    printCircular(head);

    printf("Is circular? %s\n", isCircular(head) ? "Yes" : "No");

    return 0;
}
```

### Doubly Circular Linked List

```c
typedef struct DNode {
    int data;
    struct DNode* prev;
    struct DNode* next;
} DNode;

DNode* createDNode(int data) {
    DNode* newNode = (DNode*)malloc(sizeof(DNode));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Insert at beginning
DNode* insertAtBeginning(DNode* head, int data) {
    DNode* newNode = createDNode(data);

    if (head == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        return newNode;
    }

    DNode* last = head->prev;

    newNode->next = head;
    newNode->prev = last;
    last->next = newNode;
    head->prev = newNode;

    return newNode;  // New head
}

// Insert at end
DNode* insertAtEnd(DNode* head, int data) {
    DNode* newNode = createDNode(data);

    if (head == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        return newNode;
    }

    DNode* last = head->prev;

    newNode->next = head;
    newNode->prev = last;
    last->next = newNode;
    head->prev = newNode;

    return head;
}

// Print doubly circular list
void printDoublyCircular(DNode* head) {
    if (head == NULL) {
        printf("Empty list\n");
        return;
    }

    DNode* current = head;
    printf("Forward: ");
    do {
        printf("%d <-> ", current->data);
        current = current->next;
    } while (current != head);
    printf("(back to %d)\n", head->data);
}
```

---

## Advanced Operations

### 1. Reverse a Linked List

```c
// Iterative approach - O(n) time, O(1) space
Node* reverseIterative(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;   // Store next
        current->next = prev;   // Reverse link
        prev = current;         // Move prev forward
        current = next;         // Move current forward
    }

    return prev;  // New head
}

// Recursive approach - O(n) time, O(n) space (call stack)
Node* reverseRecursive(Node* head) {
    // Base cases
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // Reverse rest of the list
    Node* rest = reverseRecursive(head->next);

    // Put first element at the end
    head->next->next = head;
    head->next = NULL;

    return rest;
}

// Visual:
// Before: 1 -> 2 -> 3 -> 4 -> NULL
// After:  4 -> 3 -> 2 -> 1 -> NULL
```

### 2. Detect Cycle (Floyd's Algorithm)

```c
#include <stdbool.h>

// Detect cycle using Floyd's Cycle Detection (Tortoise and Hare)
bool hasCycle(Node* head) {
    if (head == NULL) return false;

    Node* slow = head;
    Node* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;          // Move 1 step
        fast = fast->next->next;    // Move 2 steps

        if (slow == fast) {
            return true;  // Cycle detected
        }
    }

    return false;
}

// Find start of cycle
Node* detectCycleStart(Node* head) {
    if (head == NULL) return NULL;

    Node* slow = head;
    Node* fast = head;
    bool cycleExists = false;

    // Detect cycle
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            cycleExists = true;
            break;
        }
    }

    if (!cycleExists) return NULL;

    // Find start of cycle
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
}

// Visual:
//     ┌──────────────┐
//     ↓              │
// 1->2->3->4->5->6->7  (cycle starts at 3)
```

### 3. Find Middle of Linked List

```c
// Using slow and fast pointers - O(n)
Node* findMiddle(Node* head) {
    if (head == NULL) return NULL;

    Node* slow = head;
    Node* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;  // Middle node
}

// For even length, returns second middle
// Example: 1->2->3->4->5->6 returns 4
```

### 4. Merge Two Sorted Lists

```c
// Iterative approach - O(m + n)
Node* mergeSorted(Node* l1, Node* l2) {
    Node dummy;
    dummy.next = NULL;
    Node* tail = &dummy;

    while (l1 != NULL && l2 != NULL) {
        if (l1->data <= l2->data) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    // Attach remaining nodes
    tail->next = (l1 != NULL) ? l1 : l2;

    return dummy.next;
}

// Recursive approach
Node* mergeSortedRecursive(Node* l1, Node* l2) {
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;

    if (l1->data <= l2->data) {
        l1->next = mergeSortedRecursive(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeSortedRecursive(l1, l2->next);
        return l2;
    }
}
```

### 5. Remove Nth Node From End

```c
// Using two pointers - O(n) time, single pass
Node* removeNthFromEnd(Node* head, int n) {
    Node dummy;
    dummy.next = head;

    Node* first = &dummy;
    Node* second = &dummy;

    // Move first pointer n+1 steps ahead
    for (int i = 0; i <= n; i++) {
        if (first == NULL) return head;  // n is larger than list size
        first = first->next;
    }

    // Move both pointers until first reaches end
    while (first != NULL) {
        first = first->next;
        second = second->next;
    }

    // Remove nth node from end
    Node* temp = second->next;
    second->next = second->next->next;
    free(temp);

    return dummy.next;
}

// Example: Remove 2nd from end
// 1->2->3->4->5, n=2
// Result: 1->2->3->5
```

### 6. Check if Palindrome

```c
// Using reverse second half - O(n) time, O(1) space
bool isPalindrome(Node* head) {
    if (head == NULL || head->next == NULL) return true;

    // Find middle
    Node* slow = head;
    Node* fast = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Reverse second half
    Node* secondHalf = reverseIterative(slow->next);

    // Compare both halves
    Node* p1 = head;
    Node* p2 = secondHalf;
    bool result = true;

    while (p2 != NULL) {
        if (p1->data != p2->data) {
            result = false;
            break;
        }
        p1 = p1->next;
        p2 = p2->next;
    }

    // Restore list (optional)
    slow->next = reverseIterative(secondHalf);

    return result;
}
```

---

## Common Algorithms

### 1. Merge Sort on Linked List

```c
// Merge sort - O(n log n) time, O(log n) space
Node* getMiddle(Node* head) {
    if (head == NULL) return head;

    Node* slow = head;
    Node* fast = head->next;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

Node* sortedMerge(Node* a, Node* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;

    Node* result = NULL;

    if (a->data <= b->data) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }

    return result;
}

Node* mergeSort(Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // Get middle
    Node* middle = getMiddle(head);
    Node* nextOfMiddle = middle->next;

    // Split the list
    middle->next = NULL;

    // Recursively sort both halves
    Node* left = mergeSort(head);
    Node* right = mergeSort(nextOfMiddle);

    // Merge sorted halves
    return sortedMerge(left, right);
}
```

### 2. Remove Duplicates from Sorted List

```c
// Remove duplicates - O(n)
Node* removeDuplicates(Node* head) {
    Node* current = head;

    while (current != NULL && current->next != NULL) {
        if (current->data == current->next->data) {
            Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }

    return head;
}

// Example: 1->1->2->3->3->4 becomes 1->2->3->4
```

### 3. Intersection of Two Linked Lists

```c
// Find length of list
int getLength(Node* head) {
    int length = 0;
    while (head != NULL) {
        length++;
        head = head->next;
    }
    return length;
}

// Find intersection point
Node* getIntersection(Node* head1, Node* head2) {
    int len1 = getLength(head1);
    int len2 = getLength(head2);

    Node* ptr1 = head1;
    Node* ptr2 = head2;

    // Advance longer list
    int diff = abs(len1 - len2);
    if (len1 > len2) {
        for (int i = 0; i < diff; i++) {
            ptr1 = ptr1->next;
        }
    } else {
        for (int i = 0; i < diff; i++) {
            ptr2 = ptr2->next;
        }
    }

    // Find intersection
    while (ptr1 != NULL && ptr2 != NULL) {
        if (ptr1 == ptr2) {
            return ptr1;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    return NULL;
}
```

### 4. Clone List with Random Pointer

```c
typedef struct RandomNode {
    int data;
    struct RandomNode* next;
    struct RandomNode* random;
} RandomNode;

// Clone list with random pointers - O(n) time, O(1) space
RandomNode* cloneList(RandomNode* head) {
    if (head == NULL) return NULL;

    // Step 1: Create copy nodes interleaved with original
    RandomNode* current = head;
    while (current != NULL) {
        RandomNode* copy = (RandomNode*)malloc(sizeof(RandomNode));
        copy->data = current->data;
        copy->next = current->next;
        copy->random = NULL;
        current->next = copy;
        current = copy->next;
    }

    // Step 2: Set random pointers for copied nodes
    current = head;
    while (current != NULL) {
        if (current->random != NULL) {
            current->next->random = current->random->next;
        }
        current = current->next->next;
    }

    // Step 3: Separate original and copied lists
    current = head;
    RandomNode* copyHead = head->next;
    RandomNode* copy = copyHead;

    while (current != NULL) {
        current->next = current->next->next;
        if (copy->next != NULL) {
            copy->next = copy->next->next;
        }
        current = current->next;
        copy = copy->next;
    }

    return copyHead;
}
```

---

## Practice Problems

### Problem 1: Find Nth Node from End (Easy)
```c
Node* nthFromEnd(Node* head, int n) {
    Node* first = head;
    Node* second = head;

    // Move first n steps ahead
    for (int i = 0; i < n; i++) {
        if (first == NULL) return NULL;
        first = first->next;
    }

    // Move both until first reaches end
    while (first != NULL) {
        first = first->next;
        second = second->next;
    }

    return second;
}
```
**Time**: O(n), **Space**: O(1)

---

### Problem 2: Rotate List (Medium)
Rotate list to the right by k places.

```c
Node* rotateRight(Node* head, int k) {
    if (head == NULL || head->next == NULL || k == 0) return head;

    // Find length and last node
    Node* current = head;
    int length = 1;
    while (current->next != NULL) {
        current = current->next;
        length++;
    }

    // Make it circular
    current->next = head;

    // Find new tail
    k = k % length;
    int stepsToNewHead = length - k;
    Node* newTail = head;
    for (int i = 1; i < stepsToNewHead; i++) {
        newTail = newTail->next;
    }

    // Break the circle
    Node* newHead = newTail->next;
    newTail->next = NULL;

    return newHead;
}
```

---

### Problem 3: Add Two Numbers (Medium)
Add two numbers represented as linked lists.

```c
Node* addTwoNumbers(Node* l1, Node* l2) {
    Node dummy;
    dummy.next = NULL;
    Node* current = &dummy;
    int carry = 0;

    while (l1 != NULL || l2 != NULL || carry) {
        int sum = carry;
        if (l1 != NULL) {
            sum += l1->data;
            l1 = l1->next;
        }
        if (l2 != NULL) {
            sum += l2->data;
            l2 = l2->next;
        }

        carry = sum / 10;
        current->next = createNode(sum % 10);
        current = current->next;
    }

    return dummy.next;
}

// Example:
// Input: 2->4->3 + 5->6->4
// Output: 7->0->8 (342 + 465 = 807)
```

---

### Problem 4: Partition List (Medium)
Partition list around value x.

```c
Node* partition(Node* head, int x) {
    Node lessHead, greaterHead;
    lessHead.next = NULL;
    greaterHead.next = NULL;

    Node* less = &lessHead;
    Node* greater = &greaterHead;

    while (head != NULL) {
        if (head->data < x) {
            less->next = head;
            less = less->next;
        } else {
            greater->next = head;
            greater = greater->next;
        }
        head = head->next;
    }

    greater->next = NULL;
    less->next = greaterHead.next;

    return lessHead.next;
}

// Example: partition(1->4->3->2->5->2, 3)
// Output: 1->2->2->4->3->5
```

---

### Problem 5: Flatten Multilevel Linked List (Hard)
Flatten a multilevel doubly linked list.

```c
typedef struct MultiNode {
    int data;
    struct MultiNode* prev;
    struct MultiNode* next;
    struct MultiNode* child;
} MultiNode;

MultiNode* flatten(MultiNode* head) {
    if (head == NULL) return NULL;

    MultiNode* current = head;

    while (current != NULL) {
        if (current->child != NULL) {
            // Find tail of child list
            MultiNode* childTail = current->child;
            while (childTail->next != NULL) {
                childTail = childTail->next;
            }

            // Connect child list
            childTail->next = current->next;
            if (current->next != NULL) {
                current->next->prev = childTail;
            }

            current->next = current->child;
            current->child->prev = current;
            current->child = NULL;
        }
        current = current->next;
    }

    return head;
}
```

---

### Problem 6: Reverse in Groups (Hard)
Reverse nodes in groups of k.

```c
Node* reverseKGroup(Node* head, int k) {
    Node* current = head;
    int count = 0;

    // Check if we have k nodes
    while (current != NULL && count < k) {
        current = current->next;
        count++;
    }

    if (count < k) return head;  // Not enough nodes

    // Reverse first k nodes
    Node* prev = NULL;
    current = head;
    Node* next = NULL;

    for (int i = 0; i < k; i++) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    // Recursively reverse remaining
    if (next != NULL) {
        head->next = reverseKGroup(next, k);
    }

    return prev;
}

// Example: reverseKGroup(1->2->3->4->5, 2)
// Output: 2->1->4->3->5
```

---

### Problem 7: Copy with Random (Hard)
Already covered above in section.

---

### Problem 8: Sort List (Medium)
Sort linked list in O(n log n) time.
(Use merge sort from previous section)

---

### Problem 9: Reorder List (Medium)
Reorder L0→L1→...→Ln-1→Ln to L0→Ln→L1→Ln-1→L2→Ln-2→...

```c
void reorderList(Node* head) {
    if (head == NULL || head->next == NULL) return;

    // Find middle
    Node* slow = head;
    Node* fast = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Reverse second half
    Node* second = reverseIterative(slow->next);
    slow->next = NULL;

    // Merge two halves
    Node* first = head;
    while (second != NULL) {
        Node* temp1 = first->next;
        Node* temp2 = second->next;

        first->next = second;
        second->next = temp1;

        first = temp1;
        second = temp2;
    }
}
```

---

### Problem 10: LRU Cache (Hard)
Implement LRU cache using doubly linked list and hash map.

```c
#define HASH_SIZE 100

typedef struct CacheNode {
    int key;
    int value;
    struct CacheNode* prev;
    struct CacheNode* next;
} CacheNode;

typedef struct {
    CacheNode* head;
    CacheNode* tail;
    CacheNode* hashTable[HASH_SIZE];
    int capacity;
    int size;
} LRUCache;

LRUCache* createCache(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->head = createDNode(-1);
    cache->tail = createDNode(-1);
    cache->head->next = cache->tail;
    cache->tail->prev = cache->head;
    cache->capacity = capacity;
    cache->size = 0;

    for (int i = 0; i < HASH_SIZE; i++) {
        cache->hashTable[i] = NULL;
    }

    return cache;
}

// Full implementation would include get() and put() methods
```

---

## Complexity Summary

| Operation | Singly LL | Doubly LL | Circular LL |
|-----------|-----------|-----------|-------------|
| Access | O(n) | O(n) | O(n) |
| Search | O(n) | O(n) | O(n) |
| Insert Front | O(1) | O(1) | O(n) or O(1) with tail |
| Insert End | O(n) or O(1) with tail | O(1) with tail | O(n) or O(1) with tail |
| Delete | O(1) if pointer known | O(1) if pointer known | O(1) if pointer known |
| Space | O(n) | O(n) + extra prev | O(n) |

---

## Summary

### Key Points
- Linked lists provide dynamic size and efficient insertion/deletion
- Trade-off: No random access like arrays
- Three main types: Singly, Doubly, Circular
- Master pointer manipulation for interviews
- Two-pointer technique solves many problems

### When to Use What?
- **Singly LL**: Basic operations, stack/queue implementation
- **Doubly LL**: When backward traversal needed, LRU cache
- **Circular LL**: Round-robin scheduling, buffers

**Practice linked list problems daily to master pointer manipulation!**
