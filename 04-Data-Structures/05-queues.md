# Queues - Complete Guide

## Table of Contents
1. [Introduction to Queues](#introduction-to-queues)
2. [Linear Queue Implementation](#linear-queue-implementation)
3. [Circular Queue](#circular-queue)
4. [Priority Queue](#priority-queue)
5. [Deque (Double-Ended Queue)](#deque-double-ended-queue)
6. [Queue Applications](#queue-applications)
7. [Practice Problems](#practice-problems)

---

## Introduction to Queues

### What is a Queue?
A **queue** is a linear data structure that follows the **FIFO** (First In, First Out) principle. The first element added is the first one to be removed.

### Real-World Examples
- Line at ticket counter
- Print queue
- CPU task scheduling
- Breadth-First Search (BFS)
- Message queues

### Visual Representation
```
FRONT                                    REAR
  ↓                                        ↓
┌────┬────┬────┬────┬────┐
│ 10 │ 20 │ 30 │ 40 │ 50 │
└────┴────┴────┴────┴────┘
  ↑                      ↑
First In             Last In
(First Out)
```

### Basic Operations

| Operation | Description | Time Complexity |
|-----------|-------------|-----------------|
| `enqueue(x)` | Add element to rear | O(1) |
| `dequeue()` | Remove element from front | O(1) |
| `front()`/`peek()` | View front element | O(1) |
| `rear()` | View rear element | O(1) |
| `isEmpty()` | Check if empty | O(1) |
| `isFull()` | Check if full | O(1) |
| `size()` | Get number of elements | O(1) |

### Queue Operations Visualization
```
Initial: Empty
┌──┬──┬──┬──┬──┐
│  │  │  │  │  │
└──┴──┴──┴──┴──┘

enqueue(10):
┌────┬──┬──┬──┬──┐
│ 10 │  │  │  │  │
└────┴──┴──┴──┴──┘
  ↑
FRONT/REAR

enqueue(20):
┌────┬────┬──┬──┬──┐
│ 10 │ 20 │  │  │  │
└────┴────┴──┴──┴──┘
  ↑       ↑
FRONT   REAR

enqueue(30):
┌────┬────┬────┬──┬──┐
│ 10 │ 20 │ 30 │  │  │
└────┴────┴────┴──┴──┘
  ↑            ↑
FRONT        REAR

dequeue():  (removes 10)
┌──┬────┬────┬──┬──┐
│  │ 20 │ 30 │  │  │
└──┴────┴────┴──┴──┘
      ↑     ↑
    FRONT REAR
```

---

## Linear Queue Implementation

### Array Implementation

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
} Queue;

// Initialize queue
void initQueue(Queue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

// Check if empty
bool isEmpty(Queue* queue) {
    return queue->front == -1;
}

// Check if full
bool isFull(Queue* queue) {
    return queue->rear == MAX_SIZE - 1;
}

// Get size
int size(Queue* queue) {
    if (isEmpty(queue)) return 0;
    return queue->rear - queue->front + 1;
}

// Enqueue - O(1)
bool enqueue(Queue* queue, int value) {
    if (isFull(queue)) {
        printf("Queue Overflow! Cannot enqueue %d\n", value);
        return false;
    }

    if (isEmpty(queue)) {
        queue->front = 0;
    }

    queue->items[++queue->rear] = value;
    return true;
}

// Dequeue - O(1)
int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue Underflow! Cannot dequeue\n");
        return -1;
    }

    int value = queue->items[queue->front];

    if (queue->front == queue->rear) {
        // Last element, reset queue
        queue->front = queue->rear = -1;
    } else {
        queue->front++;
    }

    return value;
}

// Get front element - O(1)
int front(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return queue->items[queue->front];
}

// Get rear element - O(1)
int rear(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return queue->items[queue->rear];
}

// Print queue
void printQueue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue (front to rear): ");
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("%d ", queue->items[i]);
    }
    printf("\n");
}

// Display queue visually
void displayQueue(Queue* queue) {
    printf("\n");
    printf("FRONT                    REAR\n");
    printf("  ↓                        ↓\n");

    if (isEmpty(queue)) {
        printf("┌──┬──┬──┬──┬──┐\n");
        printf("│  │  │  │  │  │\n");
        printf("└──┴──┴──┴──┴──┘\n");
        return;
    }

    // Show first 5 elements
    printf("┌");
    for (int i = 0; i < 5; i++) {
        printf("────┬");
    }
    printf("\b┐\n│");

    for (int i = 0; i < 5; i++) {
        if (queue->front + i <= queue->rear) {
            printf(" %2d │", queue->items[queue->front + i]);
        } else {
            printf("    │");
        }
    }

    printf("\n└");
    for (int i = 0; i < 5; i++) {
        printf("────┴");
    }
    printf("\b┘\n");
}

int main() {
    Queue queue;
    initQueue(&queue);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    enqueue(&queue, 40);

    displayQueue(&queue);

    printf("\nFront: %d\n", front(&queue));
    printf("Rear: %d\n", rear(&queue));
    printf("Size: %d\n", size(&queue));

    printf("\nDequeued: %d\n", dequeue(&queue));
    displayQueue(&queue);

    return 0;
}
```

### Linked List Implementation

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int size;
} LinkedQueue;

// Initialize queue
void initLinkedQueue(LinkedQueue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

// Check if empty
bool isEmptyLinked(LinkedQueue* queue) {
    return queue->front == NULL;
}

// Get size
int sizeLinked(LinkedQueue* queue) {
    return queue->size;
}

// Create new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Enqueue - O(1)
void enqueueLinked(LinkedQueue* queue, int value) {
    Node* newNode = createNode(value);

    if (isEmptyLinked(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }

    queue->size++;
}

// Dequeue - O(1)
int dequeueLinked(LinkedQueue* queue) {
    if (isEmptyLinked(queue)) {
        printf("Queue Underflow!\n");
        return -1;
    }

    Node* temp = queue->front;
    int value = temp->data;

    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    queue->size--;

    return value;
}

// Get front - O(1)
int frontLinked(LinkedQueue* queue) {
    if (isEmptyLinked(queue)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return queue->front->data;
}

// Get rear - O(1)
int rearLinked(LinkedQueue* queue) {
    if (isEmptyLinked(queue)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return queue->rear->data;
}

// Print queue
void printLinkedQueue(LinkedQueue* queue) {
    if (isEmptyLinked(queue)) {
        printf("Queue is empty\n");
        return;
    }

    Node* current = queue->front;
    printf("Queue: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Free queue
void freeLinkedQueue(LinkedQueue* queue) {
    while (!isEmptyLinked(queue)) {
        dequeueLinked(queue);
    }
}

int main() {
    LinkedQueue queue;
    initLinkedQueue(&queue);

    enqueueLinked(&queue, 10);
    enqueueLinked(&queue, 20);
    enqueueLinked(&queue, 30);

    printLinkedQueue(&queue);

    printf("Dequeued: %d\n", dequeueLinked(&queue));
    printLinkedQueue(&queue);

    freeLinkedQueue(&queue);

    return 0;
}
```

---

## Circular Queue

### Why Circular Queue?
In linear queue, once rear reaches end, we can't use freed space at beginning. Circular queue solves this by wrapping around.

### Visual Representation
```
Linear Queue Problem:
┌──┬──┬────┬────┬────┐
│  │  │ 30 │ 40 │ 50 │
└──┴──┴────┴────┴────┘
          ↑         ↑
        FRONT     REAR

Space at beginning wasted!

Circular Queue Solution:
     ┌────────┐
  ┌──┴──┐  ┌──┴──┐
  │ 50  │  │ 10  │
  └──┬──┘  └──┬──┘
  ┌──┴──┐  ┌──┴──┐
  │ 40  │  │ 20  │
  └──┬──┘  └──┬──┘
     └───┬───┘
      │ 30  │
      └─────┘

Wraps around to use all space!
```

### Implementation

```c
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 5

typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
    int count;
} CircularQueue;

// Initialize
void initCircularQueue(CircularQueue* cq) {
    cq->front = 0;
    cq->rear = -1;
    cq->count = 0;
}

// Check if empty
bool isEmptyCircular(CircularQueue* cq) {
    return cq->count == 0;
}

// Check if full
bool isFullCircular(CircularQueue* cq) {
    return cq->count == MAX_SIZE;
}

// Get size
int sizeCircular(CircularQueue* cq) {
    return cq->count;
}

// Enqueue - O(1)
bool enqueueCircular(CircularQueue* cq, int value) {
    if (isFullCircular(cq)) {
        printf("Circular Queue is Full!\n");
        return false;
    }

    cq->rear = (cq->rear + 1) % MAX_SIZE;
    cq->items[cq->rear] = value;
    cq->count++;

    return true;
}

// Dequeue - O(1)
int dequeueCircular(CircularQueue* cq) {
    if (isEmptyCircular(cq)) {
        printf("Circular Queue is Empty!\n");
        return -1;
    }

    int value = cq->items[cq->front];
    cq->front = (cq->front + 1) % MAX_SIZE;
    cq->count--;

    return value;
}

// Get front
int frontCircular(CircularQueue* cq) {
    if (isEmptyCircular(cq)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return cq->items[cq->front];
}

// Get rear
int rearCircular(CircularQueue* cq) {
    if (isEmptyCircular(cq)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return cq->items[cq->rear];
}

// Print circular queue
void printCircularQueue(CircularQueue* cq) {
    if (isEmptyCircular(cq)) {
        printf("Circular Queue is empty\n");
        return;
    }

    printf("Circular Queue: ");
    int i = cq->front;
    int count = 0;

    while (count < cq->count) {
        printf("%d ", cq->items[i]);
        i = (i + 1) % MAX_SIZE;
        count++;
    }
    printf("\n");
}

// Display visually
void displayCircularQueue(CircularQueue* cq) {
    printf("\nCircular Queue (size %d/%d):\n", cq->count, MAX_SIZE);
    printf("Front index: %d, Rear index: %d\n", cq->front, cq->rear);

    for (int i = 0; i < MAX_SIZE; i++) {
        printf("[%d]: ", i);
        if (cq->count == 0) {
            printf("_");
        } else {
            int pos = (cq->front + i) % MAX_SIZE;
            bool inRange = false;

            if (cq->front <= cq->rear) {
                inRange = (pos >= cq->front && pos <= cq->rear);
            } else {
                inRange = (pos >= cq->front || pos <= cq->rear);
            }

            if (inRange) {
                printf("%d", cq->items[pos]);
                if (pos == cq->front) printf(" ← FRONT");
                if (pos == cq->rear) printf(" ← REAR");
            } else {
                printf("_");
            }
        }
        printf("\n");
    }
}

int main() {
    CircularQueue cq;
    initCircularQueue(&cq);

    enqueueCircular(&cq, 10);
    enqueueCircular(&cq, 20);
    enqueueCircular(&cq, 30);

    displayCircularQueue(&cq);

    dequeueCircular(&cq);
    dequeueCircular(&cq);

    enqueueCircular(&cq, 40);
    enqueueCircular(&cq, 50);
    enqueueCircular(&cq, 60);

    displayCircularQueue(&cq);

    return 0;
}
```

---

## Priority Queue

### Concept
Elements are dequeued based on priority, not insertion order. Higher priority elements are dequeued first.

### Visual Representation
```
Priority Queue (Max Heap):
      ┌───────┐
      │ 100(5)│  ← Highest priority
      └───┬───┘
      ┌───┴───┐
   ┌──┴──┐ ┌──┴──┐
   │70(4)│ │50(3)│
   └──┬──┘ └─────┘
   ┌──┴──┐
   │30(2)│
   └─────┘

(number) = priority
```

### Simple Array Implementation

```c
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 100

typedef struct {
    int value;
    int priority;
} PQNode;

typedef struct {
    PQNode items[MAX_SIZE];
    int size;
} PriorityQueue;

// Initialize
void initPriorityQueue(PriorityQueue* pq) {
    pq->size = 0;
}

// Check if empty
bool isEmptyPQ(PriorityQueue* pq) {
    return pq->size == 0;
}

// Check if full
bool isFullPQ(PriorityQueue* pq) {
    return pq->size == MAX_SIZE;
}

// Enqueue with priority - O(n)
bool enqueuePQ(PriorityQueue* pq, int value, int priority) {
    if (isFullPQ(pq)) {
        printf("Priority Queue is full!\n");
        return false;
    }

    // Insert in sorted order (higher priority first)
    int i = pq->size - 1;

    while (i >= 0 && pq->items[i].priority < priority) {
        pq->items[i + 1] = pq->items[i];
        i--;
    }

    pq->items[i + 1].value = value;
    pq->items[i + 1].priority = priority;
    pq->size++;

    return true;
}

// Dequeue highest priority - O(1)
int dequeuePQ(PriorityQueue* pq) {
    if (isEmptyPQ(pq)) {
        printf("Priority Queue is empty!\n");
        return -1;
    }

    int value = pq->items[0].value;

    // Shift elements
    for (int i = 0; i < pq->size - 1; i++) {
        pq->items[i] = pq->items[i + 1];
    }

    pq->size--;
    return value;
}

// Peek highest priority
int peekPQ(PriorityQueue* pq) {
    if (isEmptyPQ(pq)) {
        printf("Priority Queue is empty!\n");
        return -1;
    }
    return pq->items[0].value;
}

// Print priority queue
void printPQ(PriorityQueue* pq) {
    if (isEmptyPQ(pq)) {
        printf("Priority Queue is empty\n");
        return;
    }

    printf("Priority Queue (value, priority):\n");
    for (int i = 0; i < pq->size; i++) {
        printf("  (%d, %d)\n", pq->items[i].value, pq->items[i].priority);
    }
}

int main() {
    PriorityQueue pq;
    initPriorityQueue(&pq);

    enqueuePQ(&pq, 100, 2);
    enqueuePQ(&pq, 200, 5);
    enqueuePQ(&pq, 300, 1);
    enqueuePQ(&pq, 400, 3);

    printPQ(&pq);

    printf("\nDequeued: %d\n", dequeuePQ(&pq));
    printf("Next highest: %d\n", peekPQ(&pq));

    printPQ(&pq);

    return 0;
}
```

### Heap-Based Priority Queue (Efficient)

```c
// Binary Min Heap implementation
typedef struct {
    int values[MAX_SIZE];
    int priorities[MAX_SIZE];
    int size;
} HeapPQ;

void initHeapPQ(HeapPQ* hpq) {
    hpq->size = 0;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify up - O(log n)
void heapifyUp(HeapPQ* hpq, int index) {
    if (index == 0) return;

    int parent = (index - 1) / 2;

    if (hpq->priorities[index] < hpq->priorities[parent]) {
        swap(&hpq->priorities[index], &hpq->priorities[parent]);
        swap(&hpq->values[index], &hpq->values[parent]);
        heapifyUp(hpq, parent);
    }
}

// Heapify down - O(log n)
void heapifyDown(HeapPQ* hpq, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < hpq->size &&
        hpq->priorities[left] < hpq->priorities[smallest]) {
        smallest = left;
    }

    if (right < hpq->size &&
        hpq->priorities[right] < hpq->priorities[smallest]) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&hpq->priorities[index], &hpq->priorities[smallest]);
        swap(&hpq->values[index], &hpq->values[smallest]);
        heapifyDown(hpq, smallest);
    }
}

// Insert - O(log n)
void insertHeapPQ(HeapPQ* hpq, int value, int priority) {
    if (hpq->size == MAX_SIZE) {
        printf("Heap is full!\n");
        return;
    }

    hpq->values[hpq->size] = value;
    hpq->priorities[hpq->size] = priority;
    heapifyUp(hpq, hpq->size);
    hpq->size++;
}

// Extract min - O(log n)
int extractMin(HeapPQ* hpq) {
    if (hpq->size == 0) {
        printf("Heap is empty!\n");
        return -1;
    }

    int value = hpq->values[0];

    hpq->values[0] = hpq->values[hpq->size - 1];
    hpq->priorities[0] = hpq->priorities[hpq->size - 1];
    hpq->size--;

    heapifyDown(hpq, 0);

    return value;
}
```

---

## Deque (Double-Ended Queue)

### Concept
Elements can be added or removed from both ends.

### Visual Representation
```
        ┌─────────────────────┐
        │  Insertion/Deletion │
        ↓                     ↓
      FRONT                 REAR
        ↓                     ↓
    ┌────┬────┬────┬────┬────┐
    │ 10 │ 20 │ 30 │ 40 │ 50 │
    └────┴────┴────┴────┴────┘
        ↑                     ↑
        │  Insertion/Deletion │
        └─────────────────────┘
```

### Circular Array Implementation

```c
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 10

typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
    int count;
} Deque;

// Initialize
void initDeque(Deque* dq) {
    dq->front = 0;
    dq->rear = MAX_SIZE - 1;
    dq->count = 0;
}

// Check if empty
bool isEmptyDeque(Deque* dq) {
    return dq->count == 0;
}

// Check if full
bool isFullDeque(Deque* dq) {
    return dq->count == MAX_SIZE;
}

// Insert at front - O(1)
bool insertFront(Deque* dq, int value) {
    if (isFullDeque(dq)) {
        printf("Deque is full!\n");
        return false;
    }

    dq->front = (dq->front - 1 + MAX_SIZE) % MAX_SIZE;
    dq->items[dq->front] = value;
    dq->count++;

    return true;
}

// Insert at rear - O(1)
bool insertRear(Deque* dq, int value) {
    if (isFullDeque(dq)) {
        printf("Deque is full!\n");
        return false;
    }

    dq->rear = (dq->rear + 1) % MAX_SIZE;
    dq->items[dq->rear] = value;
    dq->count++;

    return true;
}

// Delete from front - O(1)
int deleteFront(Deque* dq) {
    if (isEmptyDeque(dq)) {
        printf("Deque is empty!\n");
        return -1;
    }

    int value = dq->items[dq->front];
    dq->front = (dq->front + 1) % MAX_SIZE;
    dq->count--;

    return value;
}

// Delete from rear - O(1)
int deleteRear(Deque* dq) {
    if (isEmptyDeque(dq)) {
        printf("Deque is empty!\n");
        return -1;
    }

    int value = dq->items[dq->rear];
    dq->rear = (dq->rear - 1 + MAX_SIZE) % MAX_SIZE;
    dq->count--;

    return value;
}

// Get front
int getFront(Deque* dq) {
    if (isEmptyDeque(dq)) {
        printf("Deque is empty!\n");
        return -1;
    }
    return dq->items[dq->front];
}

// Get rear
int getRear(Deque* dq) {
    if (isEmptyDeque(dq)) {
        printf("Deque is empty!\n");
        return -1;
    }
    return dq->items[dq->rear];
}

// Print deque
void printDeque(Deque* dq) {
    if (isEmptyDeque(dq)) {
        printf("Deque is empty\n");
        return;
    }

    printf("Deque: ");
    int i = dq->front;
    int count = 0;

    while (count < dq->count) {
        printf("%d ", dq->items[i]);
        i = (i + 1) % MAX_SIZE;
        count++;
    }
    printf("\n");
}

int main() {
    Deque dq;
    initDeque(&dq);

    insertRear(&dq, 10);
    insertRear(&dq, 20);
    insertFront(&dq, 5);
    insertFront(&dq, 1);

    printDeque(&dq);  // 1 5 10 20

    deleteFront(&dq);
    deleteRear(&dq);

    printDeque(&dq);  // 5 10

    return 0;
}
```

---

## Queue Applications

### 1. BFS (Breadth-First Search)

```c
// BFS on graph (using adjacency list)
#define V 6

void BFS(int graph[][V], int start) {
    bool visited[V] = {false};
    Queue queue;
    initQueue(&queue);

    visited[start] = true;
    enqueue(&queue, start);

    printf("BFS Traversal: ");

    while (!isEmpty(&queue)) {
        int vertex = dequeue(&queue);
        printf("%d ", vertex);

        // Visit all adjacent vertices
        for (int i = 0; i < V; i++) {
            if (graph[vertex][i] && !visited[i]) {
                visited[i] = true;
                enqueue(&queue, i);
            }
        }
    }
    printf("\n");
}
```

### 2. Level Order Tree Traversal

```c
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

void levelOrder(TreeNode* root) {
    if (root == NULL) return;

    LinkedQueue queue;
    initLinkedQueue(&queue);

    enqueueLinked(&queue, (int)root);

    while (!isEmptyLinked(&queue)) {
        TreeNode* node = (TreeNode*)dequeueLinked(&queue);
        printf("%d ", node->data);

        if (node->left) enqueueLinked(&queue, (int)node->left);
        if (node->right) enqueueLinked(&queue, (int)node->right);
    }
}
```

### 3. Generate Binary Numbers

```c
// Generate binary numbers from 1 to n
void generateBinaryNumbers(int n) {
    LinkedQueue queue;
    initLinkedQueue(&queue);

    enqueueLinked(&queue, 1);  // Start with "1"

    while (n--) {
        int front = frontLinked(&queue);
        dequeueLinked(&queue);

        printf("%d ", front);

        // Generate next numbers
        enqueueLinked(&queue, front * 10);      // Append 0
        enqueueLinked(&queue, front * 10 + 1);  // Append 1
    }
}

// Output for n=5: 1 10 11 100 101
```

### 4. Sliding Window Maximum

```c
// Find maximum in each window of size k - O(n)
void slidingWindowMaximum(int arr[], int n, int k) {
    Deque dq;
    initDeque(&dq);

    printf("Sliding Window Maximums:\n");

    // Process first window
    for (int i = 0; i < k; i++) {
        // Remove smaller elements from rear
        while (!isEmptyDeque(&dq) && arr[i] >= arr[getRear(&dq)]) {
            deleteRear(&dq);
        }
        insertRear(&dq, i);
    }

    // Process remaining elements
    for (int i = k; i < n; i++) {
        printf("%d ", arr[getFront(&dq)]);

        // Remove elements outside window
        while (!isEmptyDeque(&dq) && getFront(&dq) <= i - k) {
            deleteFront(&dq);
        }

        // Remove smaller elements
        while (!isEmptyDeque(&dq) && arr[i] >= arr[getRear(&dq)]) {
            deleteRear(&dq);
        }

        insertRear(&dq, i);
    }

    printf("%d\n", arr[getFront(&dq)]);
}

// Example: arr = [1,3,-1,-3,5,3,6,7], k = 3
// Output: 3 3 5 5 6 7
```

### 5. First Non-Repeating Character in Stream

```c
#define CHAR_SIZE 256

void firstNonRepeating(char stream[]) {
    int freq[CHAR_SIZE] = {0};
    LinkedQueue queue;
    initLinkedQueue(&queue);

    printf("First non-repeating character:\n");

    for (int i = 0; stream[i] != '\0'; i++) {
        char ch = stream[i];
        freq[ch]++;
        enqueueLinked(&queue, ch);

        // Remove repeated characters from queue
        while (!isEmptyLinked(&queue) &&
               freq[frontLinked(&queue)] > 1) {
            dequeueLinked(&queue);
        }

        if (isEmptyLinked(&queue)) {
            printf("%c -> -1\n", ch);
        } else {
            printf("%c -> %c\n", ch, (char)frontLinked(&queue));
        }
    }
}

// Example: "aabcbc"
// Output:
// a -> a
// a -> -1
// b -> b
// c -> b
// b -> c
// c -> -1
```

---

## Practice Problems

### Problem 1: Implement Queue using Two Stacks (Medium)
```c
typedef struct {
    Stack s1;  // For enqueue
    Stack s2;  // For dequeue
} QueueUsingStacks;

void initQueueStacks(QueueUsingStacks* q) {
    initStack(&q->s1);
    initStack(&q->s2);
}

void enqueueStacks(QueueUsingStacks* q, int value) {
    push(&q->s1, value);
}

int dequeueStacks(QueueUsingStacks* q) {
    if (isEmpty(&q->s2)) {
        // Move all from s1 to s2
        while (!isEmpty(&q->s1)) {
            push(&q->s2, pop(&q->s1));
        }
    }

    if (isEmpty(&q->s2)) {
        printf("Queue is empty!\n");
        return -1;
    }

    return pop(&q->s2);
}
```
**Complexity**: Enqueue O(1), Dequeue amortized O(1)

---

### Problem 2: Implement Stack using Two Queues (Medium)
```c
typedef struct {
    Queue q1;
    Queue q2;
} StackUsingQueues;

void initStackQueues(StackUsingQueues* s) {
    initQueue(&s->q1);
    initQueue(&s->q2);
}

void pushQueues(StackUsingQueues* s, int value) {
    // Add to q2
    enqueue(&s->q2, value);

    // Move all from q1 to q2
    while (!isEmpty(&s->q1)) {
        enqueue(&s->q2, dequeue(&s->q1));
    }

    // Swap q1 and q2
    Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;
}

int popQueues(StackUsingQueues* s) {
    if (isEmpty(&s->q1)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return dequeue(&s->q1);
}
```

---

### Problem 3: Reverse First K Elements (Easy)
```c
void reverseFirstK(Queue* queue, int k) {
    if (k <= 0 || k > size(queue)) return;

    Stack stack;
    initStack(&stack);

    // Dequeue first k and push to stack
    for (int i = 0; i < k; i++) {
        push(&stack, dequeue(queue));
    }

    // Enqueue from stack (reversed)
    while (!isEmpty(&stack)) {
        enqueue(queue, pop(&stack));
    }

    // Move remaining (n-k) to back
    for (int i = 0; i < size(queue) - k; i++) {
        enqueue(queue, dequeue(queue));
    }
}
```

---

### Problem 4: Interleave Queue (Medium)
Interleave first half with second half.

```c
void interleaveQueue(Queue* queue) {
    int n = size(queue);
    if (n % 2 != 0) {
        printf("Queue size must be even!\n");
        return;
    }

    Stack stack;
    initStack(&stack);

    // Push first half to stack
    for (int i = 0; i < n / 2; i++) {
        push(&stack, dequeue(queue));
    }

    // Enqueue from stack
    while (!isEmpty(&stack)) {
        enqueue(queue, pop(&stack));
    }

    // Dequeue first half and enqueue back
    for (int i = 0; i < n / 2; i++) {
        enqueue(queue, dequeue(queue));
    }

    // Again push first half to stack
    for (int i = 0; i < n / 2; i++) {
        push(&stack, dequeue(queue));
    }

    // Interleave
    while (!isEmpty(&stack)) {
        enqueue(queue, pop(&stack));
        enqueue(queue, dequeue(queue));
    }
}

// Example: 1 2 3 4 5 6
// Output: 1 4 2 5 3 6
```

---

### Problem 5: LRU Cache (Hard)
Use deque and hash map.

```c
#define CACHE_SIZE 3

typedef struct {
    Deque dq;
    int hash[100];  // maps key to presence
    int keys[MAX_SIZE];
} LRUCache;

void initLRU(LRUCache* cache) {
    initDeque(&cache->dq);
    for (int i = 0; i < 100; i++) {
        cache->hash[i] = -1;
    }
}

void refer(LRUCache* cache, int key) {
    // Key not present
    if (cache->hash[key] == -1) {
        if (isFullDeque(&cache->dq)) {
            // Remove least recently used
            int lru = deleteRear(&cache->dq);
            cache->hash[lru] = -1;
        }
    } else {
        // Key present, remove from current position
        // (Implementation detail - need to remove from middle)
    }

    // Add to front (most recently used)
    insertFront(&cache->dq, key);
    cache->hash[key] = 1;
}
```

---

## Complexity Summary

| Implementation | Enqueue | Dequeue | Front/Rear | Space |
|----------------|---------|---------|------------|-------|
| Array (Linear) | O(1) | O(1) | O(1) | O(n) fixed |
| Linked List | O(1) | O(1) | O(1) | O(n) dynamic |
| Circular Array | O(1) | O(1) | O(1) | O(n) efficient |
| Priority Queue (Array) | O(n) | O(1) | O(1) | O(n) |
| Priority Queue (Heap) | O(log n) | O(log n) | O(1) | O(n) |
| Deque | O(1) | O(1) | O(1) | O(n) |

---

## Summary

### Key Takeaways
- Queue follows FIFO principle
- Circular queue efficiently uses space
- Priority queue serves highest priority first
- Deque allows operations at both ends
- Applications: BFS, scheduling, streaming

### Queue Types
1. **Simple Queue**: Basic FIFO
2. **Circular Queue**: Wraps around, no wasted space
3. **Priority Queue**: Based on priority, not order
4. **Deque**: Insert/delete from both ends

### Common Patterns
- Two stack/queue conversions
- Sliding window with deque
- Level-order traversal with queue
- Process scheduling

**Master queues - they're essential for many graph and tree algorithms!**
