# Greedy Algorithms

## Table of Contents
1. [Introduction to Greedy Algorithms](#introduction)
2. [Greedy Choice Property](#greedy-choice-property)
3. [Classic Greedy Problems](#classic-problems)
4. [When Greedy Works](#when-greedy-works)
5. [Greedy vs Dynamic Programming](#greedy-vs-dp)
6. [Practice Problems](#practice-problems)

---

## Introduction to Greedy Algorithms

**Greedy Algorithm** makes locally optimal choices at each step, hoping to find a global optimum.

### Key Principle
```
At each step:
1. Make the choice that looks best right now
2. Never reconsider past choices
3. Hope this leads to global optimum
```

### Characteristics
- **Simple**: Easy to understand and implement
- **Fast**: Usually O(n) or O(n log n)
- **No backtracking**: Once a choice is made, it's final
- **Not always optimal**: Works only for certain problems

### Example
**Coin Change (for certain denominations)**:
```
Make change for 63 cents using [25, 10, 5, 1]

Greedy approach:
- Take 2 × 25¢ = 50¢ (largest)
- Take 1 × 10¢ = 10¢ (largest remaining)
- Take 0 × 5¢
- Take 3 × 1¢ = 3¢
Total: 6 coins (optimal for this denomination system)

For some denominations, greedy fails:
Make change for 6 cents using [4, 3, 1]
Greedy: 4¢ + 1¢ + 1¢ = 3 coins
Optimal: 3¢ + 3¢ = 2 coins
```

---

## Greedy Choice Property

For greedy to work, problem must have:

### 1. Greedy Choice Property
- Local optimal choice leads to global optimal solution
- Making the best choice at each step yields best overall result

### 2. Optimal Substructure
- Optimal solution contains optimal solutions to subproblems
- Similar to dynamic programming

### Difference from DP
- **Greedy**: Make choice before solving subproblems (top-down)
- **DP**: Solve subproblems first, then make choice (bottom-up)

---

## Classic Greedy Problems

### 1. Activity Selection Problem

**Problem**: Select maximum number of non-overlapping activities.

**Input**: Activities with start and finish times
**Output**: Maximum number of activities that can be performed

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int finish;
    int index;
} Activity;

// Compare activities by finish time
int compareByFinish(const void* a, const void* b) {
    Activity* act1 = (Activity*)a;
    Activity* act2 = (Activity*)b;
    return act1->finish - act2->finish;
}

// Activity Selection using Greedy
void activitySelection(Activity activities[], int n) {
    // Sort by finish time
    qsort(activities, n, sizeof(Activity), compareByFinish);

    printf("Selected activities:\n");

    // First activity is always selected
    int lastSelected = 0;
    printf("Activity %d: [%d, %d]\n",
           activities[0].index,
           activities[0].start,
           activities[0].finish);

    int count = 1;

    // Consider rest of activities
    for (int i = 1; i < n; i++) {
        // If start time >= finish time of last selected
        if (activities[i].start >= activities[lastSelected].finish) {
            printf("Activity %d: [%d, %d]\n",
                   activities[i].index,
                   activities[i].start,
                   activities[i].finish);
            lastSelected = i;
            count++;
        }
    }

    printf("\nTotal activities selected: %d\n", count);
}

void demonstrateActivitySelection() {
    printf("=== ACTIVITY SELECTION PROBLEM ===\n\n");

    Activity activities[] = {
        {1, 4, 1},
        {3, 5, 2},
        {0, 6, 3},
        {5, 7, 4},
        {3, 9, 5},
        {5, 9, 6},
        {6, 10, 7},
        {8, 11, 8},
        {8, 12, 9},
        {2, 14, 10},
        {12, 16, 11}
    };

    int n = sizeof(activities) / sizeof(activities[0]);

    printf("All activities:\n");
    for (int i = 0; i < n; i++) {
        printf("Activity %d: [%d, %d]\n",
               activities[i].index,
               activities[i].start,
               activities[i].finish);
    }
    printf("\n");

    activitySelection(activities, n);
}
```

**Greedy Strategy**: Always pick activity that finishes first

**Why it works**:
- Leaves most room for remaining activities
- Optimal substructure: If activity k is in optimal solution, then activities compatible with k form optimal solution for remaining activities

**Time Complexity**: O(n log n) for sorting, O(n) for selection

---

### 2. Fractional Knapsack Problem

**Problem**: Maximize value in knapsack by taking fractions of items.

**Difference from 0/1 Knapsack**:
- Fractional: Can take fraction of item (greedy works)
- 0/1: Must take entire item or nothing (need DP)

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int weight;
    int value;
    float ratio;  // value per unit weight
} Item;

// Compare by value/weight ratio (descending)
int compareByRatio(const void* a, const void* b) {
    Item* item1 = (Item*)a;
    Item* item2 = (Item*)b;

    if (item1->ratio < item2->ratio) return 1;
    if (item1->ratio > item2->ratio) return -1;
    return 0;
}

// Fractional Knapsack using Greedy
float fractionalKnapsack(Item items[], int n, int capacity) {
    // Calculate value/weight ratio for each item
    for (int i = 0; i < n; i++) {
        items[i].ratio = (float)items[i].value / items[i].weight;
    }

    // Sort by ratio (descending)
    qsort(items, n, sizeof(Item), compareByRatio);

    float totalValue = 0.0;
    int remainingCapacity = capacity;

    printf("Knapsack filling process:\n");
    printf("Capacity: %d\n\n", capacity);

    for (int i = 0; i < n; i++) {
        printf("Item %d: weight=%d, value=%d, ratio=%.2f\n",
               i + 1, items[i].weight, items[i].value, items[i].ratio);

        if (items[i].weight <= remainingCapacity) {
            // Take whole item
            totalValue += items[i].value;
            remainingCapacity -= items[i].weight;
            printf("  → Take entire item (value: %d)\n", items[i].value);
        } else {
            // Take fraction
            float fraction = (float)remainingCapacity / items[i].weight;
            totalValue += items[i].value * fraction;
            printf("  → Take %.2f fraction (value: %.2f)\n",
                   fraction, items[i].value * fraction);
            remainingCapacity = 0;
            break;
        }
    }

    return totalValue;
}

void demonstrateFractionalKnapsack() {
    printf("=== FRACTIONAL KNAPSACK PROBLEM ===\n\n");

    Item items[] = {
        {10, 60, 0},
        {20, 100, 0},
        {30, 120, 0}
    };

    int n = sizeof(items) / sizeof(items[0]);
    int capacity = 50;

    float maxValue = fractionalKnapsack(items, n, capacity);

    printf("\nMaximum value in knapsack: %.2f\n", maxValue);
}
```

**Greedy Strategy**: Pick items with highest value/weight ratio first

**Time Complexity**: O(n log n)

---

### 3. Huffman Coding

**Problem**: Compress data by assigning variable-length codes to characters based on frequency.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100

// Huffman tree node
typedef struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
} MinHeapNode;

// Min heap
typedef struct MinHeap {
    unsigned size;
    unsigned capacity;
    MinHeapNode** array;
} MinHeap;

// Create new node
MinHeapNode* newNode(char data, unsigned freq) {
    MinHeapNode* temp = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// Create min heap
MinHeap* createMinHeap(unsigned capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(minHeap->capacity * sizeof(MinHeapNode*));
    return minHeap;
}

// Swap two nodes
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Heapify
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Check if size is one
int isSizeOne(MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// Extract minimum
MinHeapNode* extractMin(MinHeap* minHeap) {
    MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// Insert node
void insertMinHeap(MinHeap* minHeap, MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

// Build min heap
void buildMinHeap(MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// Check if node is leaf
int isLeaf(MinHeapNode* root) {
    return !(root->left) && !(root->right);
}

// Create and build min heap
MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

// Build Huffman tree
MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    MinHeapNode *left, *right, *top;

    // Create min heap
    MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    // Build Huffman tree
    while (!isSizeOne(minHeap)) {
        // Extract two minimum frequency nodes
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // Create new internal node with frequency = sum of two nodes
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

// Print Huffman codes
void printCodes(MinHeapNode* root, int arr[], int top) {
    // Assign 0 to left edge
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    // Assign 1 to right edge
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    // If leaf node, print character and its code
    if (isLeaf(root)) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; i++) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

// Main function for Huffman coding
void huffmanCoding(char data[], int freq[], int size) {
    // Build Huffman tree
    MinHeapNode* root = buildHuffmanTree(data, freq, size);

    // Print Huffman codes
    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top);
}

void demonstrateHuffmanCoding() {
    printf("=== HUFFMAN CODING ===\n\n");

    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Character frequencies:\n");
    for (int i = 0; i < size; i++) {
        printf("%c: %d\n", arr[i], freq[i]);
    }

    printf("\nHuffman codes:\n");
    huffmanCoding(arr, freq, size);

    printf("\nExplanation:\n");
    printf("- More frequent characters get shorter codes\n");
    printf("- No code is prefix of another (prefix-free)\n");
    printf("- Optimal compression for given frequencies\n");
}
```

**Greedy Strategy**: Always combine two least frequent nodes

**Time Complexity**: O(n log n)

**Applications**: File compression (ZIP, JPEG), data transmission

---

### 4. Job Sequencing with Deadlines

**Problem**: Schedule jobs to maximize profit, each job has deadline and profit.

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char id;
    int deadline;
    int profit;
} Job;

// Compare by profit (descending)
int compareByProfit(const void* a, const void* b) {
    Job* job1 = (Job*)a;
    Job* job2 = (Job*)b;
    return job2->profit - job1->profit;
}

// Job Sequencing
void jobSequencing(Job jobs[], int n) {
    // Sort by profit (descending)
    qsort(jobs, n, sizeof(Job), compareByProfit);

    // Find maximum deadline
    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline) {
            maxDeadline = jobs[i].deadline;
        }
    }

    // Create result array and slot availability
    char* result = (char*)malloc(maxDeadline * sizeof(char));
    bool* slot = (bool*)malloc(maxDeadline * sizeof(bool));

    for (int i = 0; i < maxDeadline; i++) {
        result[i] = '\0';
        slot[i] = false;
    }

    int totalProfit = 0;
    int jobCount = 0;

    // Schedule jobs
    for (int i = 0; i < n; i++) {
        // Find a free slot for this job
        // (starting from last possible slot)
        for (int j = jobs[i].deadline - 1; j >= 0; j--) {
            if (!slot[j]) {
                result[j] = jobs[i].id;
                slot[j] = true;
                totalProfit += jobs[i].profit;
                jobCount++;
                break;
            }
        }
    }

    printf("Job sequence: ");
    for (int i = 0; i < maxDeadline; i++) {
        if (result[i] != '\0') {
            printf("%c ", result[i]);
        }
    }
    printf("\n");

    printf("Number of jobs: %d\n", jobCount);
    printf("Total profit: %d\n", totalProfit);

    free(result);
    free(slot);
}

void demonstrateJobSequencing() {
    printf("=== JOB SEQUENCING WITH DEADLINES ===\n\n");

    Job jobs[] = {
        {'a', 2, 100},
        {'b', 1, 19},
        {'c', 2, 27},
        {'d', 1, 25},
        {'e', 3, 15}
    };

    int n = sizeof(jobs) / sizeof(jobs[0]);

    printf("Jobs (id, deadline, profit):\n");
    for (int i = 0; i < n; i++) {
        printf("%c: deadline=%d, profit=%d\n",
               jobs[i].id, jobs[i].deadline, jobs[i].profit);
    }
    printf("\n");

    jobSequencing(jobs, n);
}
```

**Greedy Strategy**: Schedule jobs with highest profit first

**Time Complexity**: O(n²) or O(n log n) with better implementation

---

### 5. Minimum Coins (for certain denominations)

```c
#include <stdio.h>

// Greedy coin change (works for standard denominations)
void coinChange(int coins[], int n, int amount) {
    printf("Making change for %d:\n", amount);

    int remaining = amount;
    int totalCoins = 0;

    for (int i = 0; i < n; i++) {
        if (remaining == 0) break;

        int count = remaining / coins[i];
        if (count > 0) {
            printf("%d × %d¢ = %d¢\n", count, coins[i], count * coins[i]);
            remaining -= count * coins[i];
            totalCoins += count;
        }
    }

    printf("Total coins: %d\n", totalCoins);
}

void demonstrateCoinChange() {
    printf("=== COIN CHANGE (GREEDY) ===\n\n");

    int coins[] = {25, 10, 5, 1};  // US denominations
    int n = sizeof(coins) / sizeof(coins[0]);

    coinChange(coins, n, 63);
    printf("\n");
    coinChange(coins, n, 93);

    printf("\nNote: Greedy works for standard denominations\n");
    printf("For arbitrary denominations, use Dynamic Programming\n");
}
```

---

### 6. Minimum Number of Platforms

**Problem**: Find minimum number of platforms required for a railway station.

```c
#include <stdio.h>
#include <stdlib.h>

// Compare function for qsort
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Find minimum platforms needed
int findMinimumPlatforms(int arr[], int dep[], int n) {
    // Sort arrival and departure times
    qsort(arr, n, sizeof(int), compare);
    qsort(dep, n, sizeof(int), compare);

    int platformsNeeded = 1;
    int maxPlatforms = 1;
    int i = 1, j = 0;

    printf("Time\tEvent\t\tPlatforms\n");
    printf("----\t-----\t\t---------\n");
    printf("%d\tTrain 0 arrives\t%d\n", arr[0], platformsNeeded);

    // Process all events
    while (i < n && j < n) {
        // If next event is arrival
        if (arr[i] <= dep[j]) {
            platformsNeeded++;
            printf("%d\tTrain %d arrives\t%d\n", arr[i], i, platformsNeeded);

            if (platformsNeeded > maxPlatforms) {
                maxPlatforms = platformsNeeded;
            }

            i++;
        }
        // If next event is departure
        else {
            platformsNeeded--;
            printf("%d\tTrain departs\t%d\n", dep[j], platformsNeeded);
            j++;
        }
    }

    return maxPlatforms;
}

void demonstrateMinimumPlatforms() {
    printf("=== MINIMUM PLATFORMS REQUIRED ===\n\n");

    int arr[] = {900, 940, 950, 1100, 1500, 1800};
    int dep[] = {910, 1200, 1120, 1130, 1900, 2000};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Train schedules:\n");
    for (int i = 0; i < n; i++) {
        printf("Train %d: %d - %d\n", i, arr[i], dep[i]);
    }
    printf("\n");

    int minPlatforms = findMinimumPlatforms(arr, dep, n);

    printf("\nMinimum platforms required: %d\n", minPlatforms);
}
```

**Greedy Strategy**: Sort events, track platforms at each time

**Time Complexity**: O(n log n)

---

## When Greedy Works

### Problems Where Greedy Works
1. **Activity Selection**: Earliest finish time
2. **Fractional Knapsack**: Highest value/weight ratio
3. **Huffman Coding**: Least frequent first
4. **Minimum Spanning Tree**: Prim's, Kruskal's
5. **Shortest Path**: Dijkstra's algorithm
6. **Job Sequencing**: Highest profit first

### Problems Where Greedy Fails
1. **0/1 Knapsack**: Need dynamic programming
2. **Coin Change (arbitrary)**: Greedy gives suboptimal
3. **Longest Path**: NP-hard, no greedy solution
4. **Graph Coloring**: Greedy is heuristic, not optimal

### How to Verify Greedy Works
1. **Greedy Choice Property**: Prove local optimal → global optimal
2. **Optimal Substructure**: Problem has optimal substructure
3. **Exchange Argument**: Prove swapping choices doesn't improve
4. **Counterexample**: Try to find case where greedy fails

---

## Greedy vs Dynamic Programming

| Aspect | Greedy | Dynamic Programming |
|--------|--------|---------------------|
| Strategy | Make best choice now | Solve all subproblems |
| Backtracking | No | Yes (implicit) |
| Optimality | Not always optimal | Always optimal |
| Speed | Usually faster | Usually slower |
| Memory | Less | More (memoization) |
| Examples | Activity selection | 0/1 Knapsack |

### Example: Coin Change

```c
// Greedy (works for [25, 10, 5, 1])
int greedyCoinChange(int coins[], int n, int amount) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        count += amount / coins[i];
        amount %= coins[i];
    }
    return count;
}

// Dynamic Programming (works for any denominations)
int dpCoinChange(int coins[], int n, int amount) {
    int* dp = (int*)malloc((amount + 1) * sizeof(int));

    dp[0] = 0;
    for (int i = 1; i <= amount; i++) {
        dp[i] = INT_MAX;
    }

    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX) {
                dp[i] = (dp[i] < dp[i - coins[j]] + 1) ?
                        dp[i] : dp[i - coins[j]] + 1;
            }
        }
    }

    int result = dp[amount];
    free(dp);
    return result;
}
```

---

## Practice Problems

### Problem 1: Minimize Maximum Difference
Minimize the maximum difference between heights after modifications.

### Problem 2: Assign Cookies
Assign cookies to children to maximize number of content children.

### Problem 3: Meeting Rooms
Find if person can attend all meetings.

### Problem 4: Jump Game
Determine if you can reach last index in array.

### Problem 5: Gas Station
Find starting gas station to complete circular route.

### Problem 6: Partition Labels
Partition string into maximum parts where each letter appears in at most one part.

### Problem 7: Remove K Digits
Remove k digits from number to get smallest possible number.

### Problem 8: Queue Reconstruction
Reconstruct queue based on height and number of people in front.

### Problem 9: Candy Distribution
Distribute candies to children with ratings such that higher rated child gets more candy.

### Problem 10: Minimum Arrows
Find minimum arrows needed to burst all balloons.

---

## Summary

### Key Concepts
1. **Local optimal → Global optimal**: Core principle
2. **Never reconsider**: No backtracking
3. **Fast**: Usually O(n) or O(n log n)
4. **Not always optimal**: Works for specific problems

### Common Greedy Strategies
- Always pick largest/smallest
- Always pick earliest/latest
- Always pick highest ratio
- Sort and process in order

### When to Use Greedy
1. Problem has greedy choice property
2. Problem has optimal substructure
3. Can prove local optimal → global optimal
4. Need fast solution

### When NOT to Use Greedy
1. Greedy doesn't work (try examples)
2. Need guaranteed optimal (use DP)
3. Problem has overlapping subproblems
4. Backtracking needed

---

**Next Topic**: Dynamic Programming
