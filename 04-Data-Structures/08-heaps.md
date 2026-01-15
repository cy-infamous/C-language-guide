# Heaps - Complete Guide

## Table of Contents
1. [Introduction to Heaps](#introduction-to-heaps)
2. [Binary Heap Implementation](#binary-heap-implementation)
3. [Heap Operations](#heap-operations)
4. [Heap Sort](#heap-sort)
5. [Priority Queue with Heap](#priority-queue-with-heap)
6. [Advanced Heap Problems](#advanced-heap-problems)
7. [Practice Problems](#practice-problems)

---

## Introduction to Heaps

### What is a Heap?
A **heap** is a complete binary tree that satisfies the heap property:
- **Max Heap**: Parent ≥ Children
- **Min Heap**: Parent ≤ Children

### Visual Representation

#### Max Heap
```
        90
       /  \
     80    70
    / \    / \
   60 50 40  30

Array: [90, 80, 70, 60, 50, 40, 30]
```

#### Min Heap
```
        10
       /  \
     20    30
    / \    / \
   40 50 60  70

Array: [10, 20, 30, 40, 50, 60, 70]
```

### Heap Properties
1. **Complete Binary Tree**: All levels filled except possibly last (filled left to right)
2. **Heap Property**: Parent-child relationship maintained
3. **Array Representation**: Efficient storage without pointers

### Array Indexing
For node at index `i`:
```
Parent:      (i - 1) / 2
Left Child:  2 * i + 1
Right Child: 2 * i + 2
```

Visual:
```
Index:    0   1   2   3   4   5   6
Array: [90, 80, 70, 60, 50, 40, 30]

Tree:
        90(0)
       /      \
     80(1)    70(2)
    /   \     /   \
  60(3) 50(4) 40(5) 30(6)

Parent of 5: (5-1)/2 = 2 ✓
Left of 1: 2*1+1 = 3 ✓
Right of 1: 2*1+2 = 4 ✓
```

### Heap vs BST

| Feature | Heap | BST |
|---------|------|-----|
| Structure | Complete binary tree | Can be skewed |
| Ordering | Partial (heap property) | Total (inorder sorted) |
| Root | Max/Min element | Random |
| Search | O(n) | O(log n) average |
| Insert | O(log n) | O(log n) average |
| Delete Max/Min | O(log n) | O(log n) |
| Use Case | Priority queue | Sorted data |

---

## Binary Heap Implementation

### Max Heap Structure

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int size;
} MaxHeap;

// Initialize heap
void initMaxHeap(MaxHeap* heap) {
    heap->size = 0;
}

// Check if empty
bool isEmpty(MaxHeap* heap) {
    return heap->size == 0;
}

// Check if full
bool isFull(MaxHeap* heap) {
    return heap->size == MAX_SIZE;
}

// Get parent index
int parent(int i) {
    return (i - 1) / 2;
}

// Get left child index
int leftChild(int i) {
    return 2 * i + 1;
}

// Get right child index
int rightChild(int i) {
    return 2 * i + 2;
}

// Swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Get maximum element (root)
int getMax(MaxHeap* heap) {
    if (isEmpty(heap)) {
        printf("Heap is empty!\n");
        return -1;
    }
    return heap->data[0];
}
```

### Min Heap Structure

```c
typedef struct {
    int data[MAX_SIZE];
    int size;
} MinHeap;

void initMinHeap(MinHeap* heap) {
    heap->size = 0;
}

int getMin(MinHeap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty!\n");
        return -1;
    }
    return heap->data[0];
}
```

---

## Heap Operations

### 1. Heapify Up (Used in Insert)

```c
// Heapify up for Max Heap - O(log n)
void heapifyUp(MaxHeap* heap, int index) {
    int parentIndex = parent(index);

    // If current element larger than parent, swap
    if (index > 0 && heap->data[index] > heap->data[parentIndex]) {
        swap(&heap->data[index], &heap->data[parentIndex]);
        heapifyUp(heap, parentIndex);
    }
}

// Iterative version
void heapifyUpIterative(MaxHeap* heap, int index) {
    while (index > 0) {
        int parentIndex = parent(index);

        if (heap->data[index] > heap->data[parentIndex]) {
            swap(&heap->data[index], &heap->data[parentIndex]);
            index = parentIndex;
        } else {
            break;
        }
    }
}

// Visual:
// Insert 95 into [90, 80, 70, 60, 50]
//
// Step 1: Add at end
//         90
//        /  \
//      80    70
//     / \    /
//   60  50  95
//
// Step 2: Heapify up (95 > 70)
//         90
//        /  \
//      80    95
//     / \    /
//   60  50  70
//
// Step 3: Heapify up (95 > 90)
//         95
//        /  \
//      80    90
//     / \    /
//   60  50  70
```

### 2. Heapify Down (Used in Delete)

```c
// Heapify down for Max Heap - O(log n)
void heapifyDown(MaxHeap* heap, int index) {
    int largest = index;
    int left = leftChild(index);
    int right = rightChild(index);

    // Find largest among node and its children
    if (left < heap->size && heap->data[left] > heap->data[largest]) {
        largest = left;
    }

    if (right < heap->size && heap->data[right] > heap->data[largest]) {
        largest = right;
    }

    // If largest is not current node, swap and continue
    if (largest != index) {
        swap(&heap->data[index], &heap->data[largest]);
        heapifyDown(heap, largest);
    }
}

// Iterative version
void heapifyDownIterative(MaxHeap* heap, int index) {
    while (true) {
        int largest = index;
        int left = leftChild(index);
        int right = rightChild(index);

        if (left < heap->size && heap->data[left] > heap->data[largest]) {
            largest = left;
        }

        if (right < heap->size && heap->data[right] > heap->data[largest]) {
            largest = right;
        }

        if (largest == index) break;

        swap(&heap->data[index], &heap->data[largest]);
        index = largest;
    }
}

// Visual:
// Remove max from [90, 80, 70, 60, 50, 40, 30]
//
// Step 1: Replace root with last element
//         30
//        /  \
//      80    70
//     / \    /
//   60  50  40
//
// Step 2: Heapify down (80 > 30)
//         80
//        /  \
//      30    70
//     / \    /
//   60  50  40
//
// Step 3: Heapify down (60 > 30)
//         80
//        /  \
//      60    70
//     / \    /
//   30  50  40
```

### 3. Insert

```c
// Insert element - O(log n)
bool insert(MaxHeap* heap, int value) {
    if (isFull(heap)) {
        printf("Heap is full!\n");
        return false;
    }

    // Insert at end
    heap->data[heap->size] = value;
    heap->size++;

    // Heapify up
    heapifyUp(heap, heap->size - 1);

    return true;
}

// For Min Heap
void heapifyUpMin(MinHeap* heap, int index) {
    int parentIndex = parent(index);

    if (index > 0 && heap->data[index] < heap->data[parentIndex]) {
        swap(&heap->data[index], &heap->data[parentIndex]);
        heapifyUpMin(heap, parentIndex);
    }
}

bool insertMin(MinHeap* heap, int value) {
    if (heap->size == MAX_SIZE) {
        printf("Heap is full!\n");
        return false;
    }

    heap->data[heap->size] = value;
    heap->size++;
    heapifyUpMin(heap, heap->size - 1);

    return true;
}
```

### 4. Extract Max/Min

```c
// Extract maximum (delete root) - O(log n)
int extractMax(MaxHeap* heap) {
    if (isEmpty(heap)) {
        printf("Heap is empty!\n");
        return -1;
    }

    if (heap->size == 1) {
        heap->size--;
        return heap->data[0];
    }

    // Store max value
    int maxValue = heap->data[0];

    // Move last element to root
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    // Heapify down from root
    heapifyDown(heap, 0);

    return maxValue;
}

// Extract minimum for Min Heap
void heapifyDownMin(MinHeap* heap, int index) {
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);

    if (left < heap->size && heap->data[left] < heap->data[smallest]) {
        smallest = left;
    }

    if (right < heap->size && heap->data[right] < heap->data[smallest]) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        heapifyDownMin(heap, smallest);
    }
}

int extractMin(MinHeap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty!\n");
        return -1;
    }

    int minValue = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapifyDownMin(heap, 0);

    return minValue;
}
```

### 5. Build Heap

```c
// Build max heap from array - O(n)
void buildMaxHeap(MaxHeap* heap, int arr[], int n) {
    if (n > MAX_SIZE) {
        printf("Array too large!\n");
        return;
    }

    // Copy array to heap
    for (int i = 0; i < n; i++) {
        heap->data[i] = arr[i];
    }
    heap->size = n;

    // Heapify from last non-leaf node to root
    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapifyDown(heap, i);
    }
}

// Why start from (n/2 - 1)?
// Leaves are from n/2 to n-1, already satisfy heap property
// Only need to heapify internal nodes

// Example: [4, 10, 3, 5, 1]
// Tree:
//       4
//      / \
//    10   3
//   / \
//  5   1
//
// Start from index 1 (parent of 5,1):
// Step 1: Heapify at 1 → [4, 10, 3, 5, 1]
// Step 2: Heapify at 0 → [10, 5, 3, 4, 1] (max heap)
```

### 6. Delete Specific Element

```c
// Decrease key to -infinity and extract
bool deleteElement(MaxHeap* heap, int index) {
    if (index < 0 || index >= heap->size) {
        printf("Invalid index!\n");
        return false;
    }

    // Increase to infinity (or very large value)
    heap->data[index] = INT_MAX;
    heapifyUp(heap, index);

    // Now it's at root, extract it
    extractMax(heap);

    return true;
}
```

### Print Heap

```c
// Print heap as array
void printHeap(MaxHeap* heap) {
    printf("Heap (array): ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

// Print heap as tree
void printHeapTree(MaxHeap* heap, int index, int level) {
    if (index >= heap->size) return;

    printHeapTree(heap, rightChild(index), level + 1);

    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("%d\n", heap->data[index]);

    printHeapTree(heap, leftChild(index), level + 1);
}

void displayHeap(MaxHeap* heap) {
    printf("\nHeap Tree:\n");
    printHeapTree(heap, 0, 0);
}
```

---

## Heap Sort

### Algorithm
1. Build max heap from array
2. Repeatedly extract max and place at end

```c
// Heap sort - O(n log n)
void heapSort(int arr[], int n) {
    MaxHeap heap;
    initMaxHeap(&heap);

    // Build max heap
    buildMaxHeap(&heap, arr, n);

    // Extract elements one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(&heap.data[0], &heap.data[i]);
        heap.size--;

        // Heapify root
        heapifyDown(&heap, 0);
    }

    // Copy back to array
    for (int i = 0; i < n; i++) {
        arr[i] = heap.data[i];
    }
}

// In-place heap sort (without extra structure)
void heapSortInPlace(int arr[], int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        // Heapify without using heap structure
        int largest, left, right, index = i;

        do {
            largest = index;
            left = 2 * index + 1;
            right = 2 * index + 2;

            if (left < n && arr[left] > arr[largest]) {
                largest = left;
            }

            if (right < n && arr[right] > arr[largest]) {
                largest = right;
            }

            if (largest != index) {
                swap(&arr[index], &arr[largest]);
                index = largest;
            } else {
                break;
            }
        } while (true);
    }

    // Extract elements
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);

        // Heapify root with reduced heap size
        int index = 0;
        while (true) {
            int largest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < i && arr[left] > arr[largest]) {
                largest = left;
            }

            if (right < i && arr[right] > arr[largest]) {
                largest = right;
            }

            if (largest == index) break;

            swap(&arr[index], &arr[largest]);
            index = largest;
        }
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);

    heapSort(arr, n);

    printf("\nSorted array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
```

### Heap Sort Complexity

| Case | Time Complexity | Space |
|------|-----------------|-------|
| Best | O(n log n) | O(1) |
| Average | O(n log n) | O(1) |
| Worst | O(n log n) | O(1) |

**Advantages:**
- Guaranteed O(n log n)
- In-place sorting
- No worst case like Quick Sort

**Disadvantages:**
- Not stable
- Poor cache performance
- Slower than Quick Sort in practice

---

## Priority Queue with Heap

### Implementation Using Max Heap

```c
typedef struct {
    int data[MAX_SIZE];
    int priority[MAX_SIZE];
    int size;
} PriorityQueue;

void initPQ(PriorityQueue* pq) {
    pq->size = 0;
}

// Heapify up based on priority
void heapifyUpPQ(PriorityQueue* pq, int index) {
    int parentIndex = parent(index);

    if (index > 0 && pq->priority[index] > pq->priority[parentIndex]) {
        swap(&pq->data[index], &pq->data[parentIndex]);
        swap(&pq->priority[index], &pq->priority[parentIndex]);
        heapifyUpPQ(pq, parentIndex);
    }
}

// Enqueue with priority
void enqueue(PriorityQueue* pq, int value, int priority) {
    if (pq->size == MAX_SIZE) {
        printf("Priority queue is full!\n");
        return;
    }

    pq->data[pq->size] = value;
    pq->priority[pq->size] = priority;
    pq->size++;

    heapifyUpPQ(pq, pq->size - 1);
}

// Dequeue highest priority
int dequeue(PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Priority queue is empty!\n");
        return -1;
    }

    int value = pq->data[0];

    pq->data[0] = pq->data[pq->size - 1];
    pq->priority[0] = pq->priority[pq->size - 1];
    pq->size--;

    // Heapify down
    int index = 0;
    while (true) {
        int largest = index;
        int left = leftChild(index);
        int right = rightChild(index);

        if (left < pq->size && pq->priority[left] > pq->priority[largest]) {
            largest = left;
        }

        if (right < pq->size && pq->priority[right] > pq->priority[largest]) {
            largest = right;
        }

        if (largest == index) break;

        swap(&pq->data[index], &pq->data[largest]);
        swap(&pq->priority[index], &pq->priority[largest]);
        index = largest;
    }

    return value;
}
```

---

## Advanced Heap Problems

### 1. Kth Largest Element

```c
// Find kth largest element using min heap - O(n log k)
int findKthLargest(int arr[], int n, int k) {
    MinHeap heap;
    initMinHeap(&heap);

    // Build min heap of size k
    for (int i = 0; i < n; i++) {
        if (heap.size < k) {
            insertMin(&heap, arr[i]);
        } else if (arr[i] > getMin(&heap)) {
            extractMin(&heap);
            insertMin(&heap, arr[i]);
        }
    }

    return getMin(&heap);
}

// Example: arr = [3,2,1,5,6,4], k = 2
// Result: 5 (second largest)
```

### 2. Merge K Sorted Arrays

```c
typedef struct {
    int value;
    int arrayIndex;
    int elementIndex;
} HeapNode;

typedef struct {
    HeapNode data[MAX_SIZE];
    int size;
} MinHeapNode;

void heapifyMinNode(MinHeapNode* heap, int index) {
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);

    if (left < heap->size &&
        heap->data[left].value < heap->data[smallest].value) {
        smallest = left;
    }

    if (right < heap->size &&
        heap->data[right].value < heap->data[smallest].value) {
        smallest = right;
    }

    if (smallest != index) {
        HeapNode temp = heap->data[index];
        heap->data[index] = heap->data[smallest];
        heap->data[smallest] = temp;
        heapifyMinNode(heap, smallest);
    }
}

void mergeKSortedArrays(int** arrays, int k, int* sizes, int result[]) {
    MinHeapNode heap;
    heap.size = 0;

    // Insert first element from each array
    for (int i = 0; i < k; i++) {
        if (sizes[i] > 0) {
            heap.data[heap.size].value = arrays[i][0];
            heap.data[heap.size].arrayIndex = i;
            heap.data[heap.size].elementIndex = 0;
            heap.size++;
        }
    }

    // Build min heap
    for (int i = (heap.size / 2) - 1; i >= 0; i--) {
        heapifyMinNode(&heap, i);
    }

    int resultIndex = 0;

    // Extract min and add next element from same array
    while (heap.size > 0) {
        HeapNode min = heap.data[0];
        result[resultIndex++] = min.value;

        // Add next element from same array
        if (min.elementIndex + 1 < sizes[min.arrayIndex]) {
            heap.data[0].value = arrays[min.arrayIndex][min.elementIndex + 1];
            heap.data[0].elementIndex = min.elementIndex + 1;
            heapifyMinNode(&heap, 0);
        } else {
            // No more elements, remove from heap
            heap.data[0] = heap.data[heap.size - 1];
            heap.size--;
            heapifyMinNode(&heap, 0);
        }
    }
}
```

### 3. Median from Data Stream

```c
// Use two heaps: max heap for lower half, min heap for upper half
typedef struct {
    MaxHeap maxHeap;  // Lower half
    MinHeap minHeap;  // Upper half
} MedianFinder;

void initMedianFinder(MedianFinder* mf) {
    initMaxHeap(&mf->maxHeap);
    initMinHeap(&mf->minHeap);
}

void addNum(MedianFinder* mf, int num) {
    // Add to max heap (lower half)
    if (mf->maxHeap.size == 0 || num <= getMax(&mf->maxHeap)) {
        insert(&mf->maxHeap, num);
    } else {
        insertMin(&mf->minHeap, num);
    }

    // Balance heaps
    if (mf->maxHeap.size > mf->minHeap.size + 1) {
        int val = extractMax(&mf->maxHeap);
        insertMin(&mf->minHeap, val);
    } else if (mf->minHeap.size > mf->maxHeap.size) {
        int val = extractMin(&mf->minHeap);
        insert(&mf->maxHeap, val);
    }
}

double findMedian(MedianFinder* mf) {
    if (mf->maxHeap.size == mf->minHeap.size) {
        return (getMax(&mf->maxHeap) + getMin(&mf->minHeap)) / 2.0;
    } else {
        return getMax(&mf->maxHeap);
    }
}
```

---

## Practice Problems

### Problem 1: Check if Array is Max Heap
```c
bool isMaxHeap(int arr[], int n) {
    for (int i = 0; i <= (n - 2) / 2; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[i] < arr[left]) return false;
        if (right < n && arr[i] < arr[right]) return false;
    }
    return true;
}
```

### Problem 2: Kth Smallest Element
```c
int findKthSmallest(int arr[], int n, int k) {
    MaxHeap heap;
    initMaxHeap(&heap);

    for (int i = 0; i < n; i++) {
        if (heap.size < k) {
            insert(&heap, arr[i]);
        } else if (arr[i] < getMax(&heap)) {
            extractMax(&heap);
            insert(&heap, arr[i]);
        }
    }

    return getMax(&heap);
}
```

### Problem 3: Top K Frequent Elements
```c
typedef struct {
    int value;
    int freq;
} FreqPair;

void topKFrequent(int arr[], int n, int k) {
    // Count frequencies (hash map simulation)
    // Build min heap of size k based on frequency
    // Extract all elements from heap
}
```

---

## Summary

### Complexity Table

| Operation | Time Complexity |
|-----------|-----------------|
| Get Max/Min | O(1) |
| Insert | O(log n) |
| Extract Max/Min | O(log n) |
| Delete | O(log n) |
| Build Heap | O(n) |
| Heap Sort | O(n log n) |
| Search | O(n) |

### Key Takeaways
- Heaps provide efficient priority queue implementation
- Complete binary tree stored in array (no pointers needed)
- Max heap: parent ≥ children, Min heap: parent ≤ children
- Heap sort: guaranteed O(n log n), in-place
- Two heaps can find median in O(log n) per insertion

**Master heaps - they're crucial for priority-based algorithms and efficient sorting!**
