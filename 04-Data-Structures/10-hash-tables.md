# Hash Tables - Complete Guide

## Table of Contents
1. [Introduction to Hash Tables](#introduction-to-hash-tables)
2. [Hash Functions](#hash-functions)
3. [Collision Resolution](#collision-resolution)
4. [Hash Table Implementation](#hash-table-implementation)
5. [Advanced Techniques](#advanced-techniques)
6. [Applications](#applications)
7. [Practice Problems](#practice-problems)

---

## Introduction to Hash Tables

### What is a Hash Table?
A **hash table** (hash map) is a data structure that maps keys to values using a hash function. It provides average O(1) time for insert, search, and delete operations.

### Visual Representation
```
Hash Table:
Key     Hash(Key)   Index   Value
"apple"    →  3   →  [3]  → "fruit"
"cat"      →  7   →  [7]  → "animal"
"car"      →  1   →  [1]  → "vehicle"

Hash Table Array:
┌───────────┐
│ 0:  NULL  │
├───────────┤
│ 1: "car"  │
├───────────┤
│ 2:  NULL  │
├───────────┤
│ 3: "apple"│
├───────────┤
│ 4:  NULL  │
├───────────┤
│ 5:  NULL  │
├───────────┤
│ 6:  NULL  │
├───────────┤
│ 7: "cat"  │
└───────────┘
```

### Key Concepts

| Term | Definition |
|------|------------|
| **Hash Function** | Converts key to array index |
| **Collision** | Two keys hash to same index |
| **Load Factor** | n/m (items/capacity) |
| **Rehashing** | Resize and rebuild table |
| **Bucket** | Slot in hash table |

### Advantages
- **Fast operations**: O(1) average case
- **Flexible keys**: Can use any data type
- **Dynamic sizing**: Can grow/shrink

### Disadvantages
- **No ordering**: Elements not sorted
- **Space overhead**: Need extra space
- **Collisions**: Need resolution strategy

---

## Hash Functions

### Properties of Good Hash Function
1. **Deterministic**: Same key → same hash
2. **Uniform distribution**: Minimize collisions
3. **Efficient**: Fast to compute
4. **Avalanche effect**: Small change in key → large change in hash

### Common Hash Functions

#### 1. Division Method
```c
// h(k) = k mod m
int hashDivision(int key, int tableSize) {
    return key % tableSize;
}

// Best: tableSize is prime
// Example: key=123, tableSize=11
// hash = 123 % 11 = 2
```

#### 2. Multiplication Method
```c
#define A 0.6180339887  // (√5 - 1) / 2 (golden ratio)

int hashMultiplication(int key, int tableSize) {
    double fractional = key * A - (int)(key * A);
    return (int)(tableSize * fractional);
}

// h(k) = floor(m * (kA mod 1))
// Example: key=123, tableSize=10
// hash ≈ floor(10 * (123 * 0.618...)) = 6
```

#### 3. String Hashing

```c
// Simple string hash
unsigned int hashString(char* str, int tableSize) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31 + *str) % tableSize;
        str++;
    }
    return hash;
}

// Polynomial rolling hash
unsigned int polynomialHash(char* str, int tableSize) {
    unsigned int hash = 0;
    int p = 31;  // Prime number
    unsigned long long pPow = 1;

    for (int i = 0; str[i]; i++) {
        hash = (hash + (str[i] - 'a' + 1) * pPow) % tableSize;
        pPow = (pPow * p) % tableSize;
    }

    return hash;
}

// djb2 hash (Dan Bernstein)
unsigned long hashDJB2(char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }

    return hash;
}
```

#### 4. Universal Hashing
```c
#include <stdlib.h>
#include <time.h>

typedef struct {
    int a;
    int b;
    int p;
    int m;
} UniversalHash;

void initUniversalHash(UniversalHash* uh, int tableSize) {
    uh->p = 2147483647;  // Large prime
    uh->m = tableSize;
    srand(time(NULL));
    uh->a = rand() % (uh->p - 1) + 1;
    uh->b = rand() % uh->p;
}

int universalHash(UniversalHash* uh, int key) {
    return ((uh->a * key + uh->b) % uh->p) % uh->m;
}

// h(k) = ((ak + b) mod p) mod m
// a, b chosen randomly
```

---

## Collision Resolution

### 1. Chaining (Separate Chaining)

**Each bucket** contains a linked list of all elements that hash to same index.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 10

typedef struct Node {
    char* key;
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node* buckets[TABLE_SIZE];
    int size;
} HashTableChaining;

// Initialize hash table
void initHashTable(HashTableChaining* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->buckets[i] = NULL;
    }
    ht->size = 0;
}

// Hash function
unsigned int hash(char* key) {
    unsigned int hashValue = 0;
    while (*key) {
        hashValue = (hashValue * 31 + *key) % TABLE_SIZE;
        key++;
    }
    return hashValue;
}

// Create new node
Node* createNode(char* key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Insert - O(1) average
void insert(HashTableChaining* ht, char* key, int value) {
    unsigned int index = hash(key);

    // Check if key already exists
    Node* current = ht->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;  // Update existing
            return;
        }
        current = current->next;
    }

    // Insert at beginning of chain
    Node* newNode = createNode(key, value);
    newNode->next = ht->buckets[index];
    ht->buckets[index] = newNode;
    ht->size++;
}

// Search - O(1) average
int search(HashTableChaining* ht, char* key, bool* found) {
    unsigned int index = hash(key);

    Node* current = ht->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            *found = true;
            return current->value;
        }
        current = current->next;
    }

    *found = false;
    return -1;
}

// Delete - O(1) average
bool deleteKey(HashTableChaining* ht, char* key) {
    unsigned int index = hash(key);

    Node* current = ht->buckets[index];
    Node* prev = NULL;

    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                ht->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->key);
            free(current);
            ht->size--;
            return true;
        }
        prev = current;
        current = current->next;
    }

    return false;
}

// Print hash table
void printHashTable(HashTableChaining* ht) {
    printf("\nHash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);
        Node* current = ht->buckets[i];
        while (current) {
            printf("(%s, %d) -> ", current->key, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Free hash table
void freeHashTable(HashTableChaining* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = ht->buckets[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
}
```

**Visual:**
```
Chaining:
[0]: NULL
[1]: (car, 4) -> (cat, 3) -> NULL
[2]: NULL
[3]: (apple, 1) -> (apricot, 5) -> NULL
[4]: (dog, 2) -> NULL
...
```

**Advantages:**
- Simple implementation
- No clustering
- Table never fills up

**Disadvantages:**
- Extra memory for pointers
- Cache unfriendly
- Variable performance

### 2. Open Addressing

**All elements stored in table itself.** When collision occurs, probe for next empty slot.

#### Linear Probing
```c
#define TABLE_SIZE 10
#define DELETED -2  // Marker for deleted entries

typedef struct {
    char* keys[TABLE_SIZE];
    int values[TABLE_SIZE];
    int size;
} HashTableLinear;

void initHashTableLinear(HashTableLinear* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->keys[i] = NULL;
        ht->values[i] = 0;
    }
    ht->size = 0;
}

// Linear probing: h(k, i) = (h(k) + i) mod m
void insertLinear(HashTableLinear* ht, char* key, int value) {
    if (ht->size == TABLE_SIZE) {
        printf("Hash table is full!\n");
        return;
    }

    unsigned int index = hash(key);
    int i = 0;

    while (ht->keys[(index + i) % TABLE_SIZE] != NULL &&
           ht->keys[(index + i) % TABLE_SIZE] != (char*)DELETED) {
        // Update if key exists
        if (strcmp(ht->keys[(index + i) % TABLE_SIZE], key) == 0) {
            ht->values[(index + i) % TABLE_SIZE] = value;
            return;
        }
        i++;
    }

    // Insert at empty slot
    int finalIndex = (index + i) % TABLE_SIZE;
    ht->keys[finalIndex] = strdup(key);
    ht->values[finalIndex] = value;
    ht->size++;
}

int searchLinear(HashTableLinear* ht, char* key, bool* found) {
    unsigned int index = hash(key);
    int i = 0;

    while (ht->keys[(index + i) % TABLE_SIZE] != NULL) {
        int currentIndex = (index + i) % TABLE_SIZE;

        if (ht->keys[currentIndex] != (char*)DELETED &&
            strcmp(ht->keys[currentIndex], key) == 0) {
            *found = true;
            return ht->values[currentIndex];
        }

        i++;
        if (i >= TABLE_SIZE) break;
    }

    *found = false;
    return -1;
}

bool deleteLinear(HashTableLinear* ht, char* key) {
    unsigned int index = hash(key);
    int i = 0;

    while (ht->keys[(index + i) % TABLE_SIZE] != NULL) {
        int currentIndex = (index + i) % TABLE_SIZE;

        if (ht->keys[currentIndex] != (char*)DELETED &&
            strcmp(ht->keys[currentIndex], key) == 0) {
            free(ht->keys[currentIndex]);
            ht->keys[currentIndex] = (char*)DELETED;
            ht->size--;
            return true;
        }

        i++;
        if (i >= TABLE_SIZE) break;
    }

    return false;
}
```

**Visual:**
```
Linear Probing:
Insert: apple(3), apricot(3) [collision!]

[0]: NULL
[1]: NULL
[2]: NULL
[3]: apple
[4]: apricot  ← Probed to next slot
[5]: NULL
...
```

**Primary Clustering:** Long runs of occupied slots form.

#### Quadratic Probing
```c
// Quadratic probing: h(k, i) = (h(k) + c1*i + c2*i²) mod m
void insertQuadratic(HashTableLinear* ht, char* key, int value) {
    unsigned int index = hash(key);
    int i = 0;

    while (i < TABLE_SIZE) {
        int probeIndex = (index + i * i) % TABLE_SIZE;

        if (ht->keys[probeIndex] == NULL ||
            ht->keys[probeIndex] == (char*)DELETED) {
            ht->keys[probeIndex] = strdup(key);
            ht->values[probeIndex] = value;
            ht->size++;
            return;
        }

        if (strcmp(ht->keys[probeIndex], key) == 0) {
            ht->values[probeIndex] = value;
            return;
        }

        i++;
    }

    printf("Hash table is full!\n");
}
```

**Visual:**
```
Quadratic Probing:
Probe sequence: 0, 1, 4, 9, 16, ...

[0]: NULL
[1]: NULL
[2]: NULL
[3]: apple
[4]: NULL
[7]: apricot  ← Probed with i²
...
```

**Reduces primary clustering** but may have secondary clustering.

#### Double Hashing
```c
// Second hash function
unsigned int hash2(char* key) {
    unsigned int h = 0;
    while (*key) {
        h = (h * 37 + *key) % (TABLE_SIZE - 1);
        key++;
    }
    return h + 1;  // Ensure non-zero
}

// Double hashing: h(k, i) = (h1(k) + i*h2(k)) mod m
void insertDoubleHash(HashTableLinear* ht, char* key, int value) {
    unsigned int index = hash(key);
    unsigned int step = hash2(key);
    int i = 0;

    while (i < TABLE_SIZE) {
        int probeIndex = (index + i * step) % TABLE_SIZE;

        if (ht->keys[probeIndex] == NULL ||
            ht->keys[probeIndex] == (char*)DELETED) {
            ht->keys[probeIndex] = strdup(key);
            ht->values[probeIndex] = value;
            ht->size++;
            return;
        }

        if (strcmp(ht->keys[probeIndex], key) == 0) {
            ht->values[probeIndex] = value;
            return;
        }

        i++;
    }

    printf("Hash table is full!\n");
}
```

**Best open addressing method** - minimizes clustering.

---

## Hash Table Implementation

### Complete Hash Table with Resizing

```c
#define INITIAL_SIZE 8
#define LOAD_FACTOR_THRESHOLD 0.75

typedef struct {
    Node** buckets;
    int size;
    int capacity;
} DynamicHashTable;

DynamicHashTable* createDynamicHashTable(int capacity) {
    DynamicHashTable* ht = (DynamicHashTable*)malloc(sizeof(DynamicHashTable));
    ht->capacity = capacity;
    ht->size = 0;
    ht->buckets = (Node**)calloc(capacity, sizeof(Node*));
    return ht;
}

unsigned int hashDynamic(char* key, int capacity) {
    unsigned int hashValue = 0;
    while (*key) {
        hashValue = (hashValue * 31 + *key) % capacity;
        key++;
    }
    return hashValue;
}

void resize(DynamicHashTable* ht) {
    int oldCapacity = ht->capacity;
    Node** oldBuckets = ht->buckets;

    // Double capacity
    ht->capacity *= 2;
    ht->buckets = (Node**)calloc(ht->capacity, sizeof(Node*));
    ht->size = 0;

    // Rehash all elements
    for (int i = 0; i < oldCapacity; i++) {
        Node* current = oldBuckets[i];
        while (current) {
            unsigned int newIndex = hashDynamic(current->key, ht->capacity);

            Node* newNode = createNode(current->key, current->value);
            newNode->next = ht->buckets[newIndex];
            ht->buckets[newIndex] = newNode;
            ht->size++;

            Node* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }

    free(oldBuckets);
    printf("Resized hash table to capacity %d\n", ht->capacity);
}

void insertDynamic(DynamicHashTable* ht, char* key, int value) {
    // Check load factor
    double loadFactor = (double)ht->size / ht->capacity;
    if (loadFactor > LOAD_FACTOR_THRESHOLD) {
        resize(ht);
    }

    unsigned int index = hashDynamic(key, ht->capacity);

    // Check if key exists
    Node* current = ht->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return;
        }
        current = current->next;
    }

    // Insert new node
    Node* newNode = createNode(key, value);
    newNode->next = ht->buckets[index];
    ht->buckets[index] = newNode;
    ht->size++;
}

void freeDynamicHashTable(DynamicHashTable* ht) {
    for (int i = 0; i < ht->capacity; i++) {
        Node* current = ht->buckets[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(ht->buckets);
    free(ht);
}
```

---

## Advanced Techniques

### 1. Robin Hood Hashing

Minimizes variance in probe sequence length.

```c
// Each entry stores probe count
typedef struct {
    char* key;
    int value;
    int probeCount;
} RobinHoodEntry;

// When inserting, if existing entry has lower probe count, swap
```

### 2. Cuckoo Hashing

Uses two hash functions and two tables.

```c
#define TABLE1_SIZE 10
#define TABLE2_SIZE 10

typedef struct {
    char* keys1[TABLE1_SIZE];
    int values1[TABLE1_SIZE];
    char* keys2[TABLE2_SIZE];
    int values2[TABLE2_SIZE];
} CuckooHashTable;

// Insert: Try table1, if occupied, move to table2, recurse
```

### 3. Bloom Filters

Probabilistic set membership test.

```c
#define BLOOM_SIZE 1000

typedef struct {
    bool bits[BLOOM_SIZE];
} BloomFilter;

void bloomAdd(BloomFilter* bf, char* key) {
    bf->bits[hash(key) % BLOOM_SIZE] = true;
    bf->bits[hash2(key) % BLOOM_SIZE] = true;
    bf->bits[hash3(key) % BLOOM_SIZE] = true;
}

bool bloomMightContain(BloomFilter* bf, char* key) {
    return bf->bits[hash(key) % BLOOM_SIZE] &&
           bf->bits[hash2(key) % BLOOM_SIZE] &&
           bf->bits[hash3(key) % BLOOM_SIZE];
}

// False positives possible, false negatives impossible
```

---

## Applications

### 1. Frequency Counter

```c
void countFrequency(char* words[], int n) {
    HashTableChaining ht;
    initHashTable(&ht);

    for (int i = 0; i < n; i++) {
        bool found;
        int count = search(&ht, words[i], &found);

        if (found) {
            insert(&ht, words[i], count + 1);
        } else {
            insert(&ht, words[i], 1);
        }
    }

    printHashTable(&ht);
}
```

### 2. Two Sum Problem

```c
bool twoSum(int arr[], int n, int target) {
    HashTableChaining ht;
    initHashTable(&ht);

    for (int i = 0; i < n; i++) {
        int complement = target - arr[i];
        char key[20];
        sprintf(key, "%d", complement);

        bool found;
        search(&ht, key, &found);

        if (found) {
            return true;
        }

        sprintf(key, "%d", arr[i]);
        insert(&ht, key, i);
    }

    return false;
}
```

### 3. LRU Cache

```c
// Combine hash table with doubly linked list
typedef struct {
    HashTableChaining hashTable;
    // Doubly linked list for LRU order
} LRUCache;

// O(1) get and put operations
```

---

## Practice Problems

### Problem 1: First Non-Repeating Character
```c
char firstNonRepeating(char* str) {
    int freq[256] = {0};

    for (int i = 0; str[i]; i++) {
        freq[str[i]]++;
    }

    for (int i = 0; str[i]; i++) {
        if (freq[str[i]] == 1) {
            return str[i];
        }
    }

    return '\0';
}
```

### Problem 2: Group Anagrams
```c
// Use sorted string as key
void groupAnagrams(char* strs[], int n) {
    HashTableChaining ht;
    initHashTable(&ht);

    for (int i = 0; i < n; i++) {
        char sorted[100];
        strcpy(sorted, strs[i]);
        // Sort sorted string
        // Use sorted as key, add index to value list
    }
}
```

### Problem 3: Longest Substring Without Repeating Characters
```c
int lengthOfLongestSubstring(char* s) {
    int lastSeen[256];
    for (int i = 0; i < 256; i++) {
        lastSeen[i] = -1;
    }

    int maxLen = 0, start = 0;

    for (int i = 0; s[i]; i++) {
        if (lastSeen[s[i]] >= start) {
            start = lastSeen[s[i]] + 1;
        }

        lastSeen[s[i]] = i;
        int currentLen = i - start + 1;

        if (currentLen > maxLen) {
            maxLen = currentLen;
        }
    }

    return maxLen;
}
```

---

## Summary

### Complexity Table

| Operation | Average | Worst Case |
|-----------|---------|------------|
| Search | O(1) | O(n) |
| Insert | O(1) | O(n) |
| Delete | O(1) | O(n) |
| Space | O(n) | O(n) |

### Collision Resolution Comparison

| Method | Pros | Cons |
|--------|------|------|
| **Chaining** | Simple, no clustering | Extra memory, cache-unfriendly |
| **Linear Probing** | Cache-friendly | Primary clustering |
| **Quadratic Probing** | Reduces clustering | May not find slot |
| **Double Hashing** | Best distribution | Two hash functions |

### Key Takeaways
- Hash tables provide O(1) average operations
- Good hash function crucial for performance
- Collision resolution affects efficiency
- Load factor determines when to resize
- Perfect for fast lookup and counting

**Master hash tables - they're essential for efficient data retrieval and solving many algorithmic problems!**
