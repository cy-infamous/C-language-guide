# Advanced Trees - AVL, Red-Black, and B-Trees

## Table of Contents
1. [Introduction to Advanced Trees](#introduction-to-advanced-trees)
2. [AVL Trees](#avl-trees)
3. [Red-Black Trees](#red-black-trees)
4. [B-Trees](#b-trees)
5. [Comparison and Use Cases](#comparison-and-use-cases)
6. [Practice Problems](#practice-problems)

---

## Introduction to Advanced Trees

### Why Self-Balancing Trees?

**Problem with Basic BST:**
```
Worst case (skewed):     Best case (balanced):
    1                         4
     \                       / \
      2                     2   6
       \                   / \ / \
        3                 1  3 5  7
         \
          4            Height: O(log n)
           \
            5          Operations: O(log n)

Height: O(n)
Operations: O(n)
```

**Solution:** Self-balancing trees maintain height of O(log n), guaranteeing efficient operations.

### Types of Self-Balancing Trees

| Tree Type | Balance Criterion | Rotations | Complexity | Use Case |
|-----------|------------------|-----------|------------|----------|
| **AVL** | Strict (height diff ≤ 1) | More rotations | Search: Faster | Read-heavy |
| **Red-Black** | Relaxed (color rules) | Fewer rotations | Insert/Delete: Faster | Write-heavy |
| **B-Tree** | Multiple keys per node | N/A | Disk-friendly | Databases |

---

## AVL Trees

### Definition
An **AVL tree** (Adelson-Velsky and Landis) is a self-balancing BST where the height difference between left and right subtrees is at most 1 for every node.

### Balance Factor
```
Balance Factor = Height(Left Subtree) - Height(Right Subtree)

Valid BF: -1, 0, or 1
```

### AVL Tree Example
```
Valid AVL Tree:
        30 (BF=0)
       /  \
  20(0)    40(0)
  /  \       \
10(0) 25(0)  50(0)

Invalid AVL Tree:
        30 (BF=-2)  ← Violated!
          \
           40 (BF=-1)
             \
              50 (BF=0)
```

### Node Structure

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

// Create new AVL node
AVLNode* createAVLNode(int data) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // New node at leaf level
    return node;
}

// Get height of node
int height(AVLNode* node) {
    return (node == NULL) ? 0 : node->height;
}

// Get balance factor
int getBalance(AVLNode* node) {
    return (node == NULL) ? 0 : height(node->left) - height(node->right);
}

// Update height of node
void updateHeight(AVLNode* node) {
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}
```

### Rotations

#### 1. Right Rotation (LL Case)
```
Before:              After:
    z                  y
   /                  / \
  y         →        x   z
 /
x

Code: Right rotate at z
```

```c
AVLNode* rightRotate(AVLNode* z) {
    AVLNode* y = z->left;
    AVLNode* T3 = y->right;

    // Perform rotation
    y->right = z;
    z->left = T3;

    // Update heights
    updateHeight(z);
    updateHeight(y);

    return y;  // New root
}
```

#### 2. Left Rotation (RR Case)
```
Before:              After:
  z                    y
   \                  / \
    y        →       z   x
     \
      x

Code: Left rotate at z
```

```c
AVLNode* leftRotate(AVLNode* z) {
    AVLNode* y = z->right;
    AVLNode* T2 = y->left;

    // Perform rotation
    y->left = z;
    z->right = T2;

    // Update heights
    updateHeight(z);
    updateHeight(y);

    return y;  // New root
}
```

### AVL Insertion

```c
AVLNode* insertAVL(AVLNode* root, int data) {
    // 1. Perform normal BST insertion
    if (root == NULL) {
        return createAVLNode(data);
    }

    if (data < root->data) {
        root->left = insertAVL(root->left, data);
    } else if (data > root->data) {
        root->right = insertAVL(root->right, data);
    } else {
        return root;  // Duplicate keys not allowed
    }

    // 2. Update height of this ancestor node
    updateHeight(root);

    // 3. Get balance factor
    int balance = getBalance(root);

    // 4. If unbalanced, handle 4 cases

    // Left-Left Case
    if (balance > 1 && data < root->left->data) {
        return rightRotate(root);
    }

    // Right-Right Case
    if (balance < -1 && data > root->right->data) {
        return leftRotate(root);
    }

    // Left-Right Case
    if (balance > 1 && data > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right-Left Case
    if (balance < -1 && data < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
```

---

## Red-Black Trees

### Definition
A **Red-Black Tree** is a self-balancing BST with these properties:
1. Every node is either RED or BLACK
2. Root is always BLACK
3. All leaves (NULL) are BLACK
4. RED node cannot have RED children (no two consecutive reds)
5. All paths from root to leaves have same number of BLACK nodes

### Visual Example
```
Valid Red-Black Tree:
      B:30
     /    \
  R:20    R:40
  /  \      \
B:10 B:25  B:50

B = Black, R = Red
All paths have 2 black nodes (including NULL leaves)
```

### Node Structure

```c
typedef enum { RED, BLACK } Color;

typedef struct RBNode {
    int data;
    Color color;
    struct RBNode* left;
    struct RBNode* right;
    struct RBNode* parent;
} RBNode;

// Create new Red-Black node
RBNode* createRBNode(int data) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->data = data;
    node->color = RED;  // New nodes are always red
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}
```

---

## B-Trees

### Definition
A **B-Tree** of order m is a self-balancing search tree designed for disk-based storage with these properties:
1. Every node has at most m children
2. Every non-leaf node (except root) has at least ⌈m/2⌉ children
3. Root has at least 2 children (unless it's a leaf)
4. All leaves are at the same level
5. A non-leaf node with k children contains k-1 keys

### B-Tree Visual (Order 3)
```
              [40]
            /      \
      [20,30]      [50,60]
      /  |  \      /  |  \
   [10] [25] [35] [45] [55] [70]

Properties:
- Min children: 2
- Max children: 3
- Min keys: 1, Max keys: 2
```

### Node Structure

```c
#define MAX_KEYS 3
#define MAX_CHILDREN 4

typedef struct BTreeNode {
    int keys[MAX_KEYS];
    struct BTreeNode* children[MAX_CHILDREN];
    int numKeys;
    int isLeaf;
} BTreeNode;

BTreeNode* createBTreeNode(int isLeaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->isLeaf = isLeaf;
    node->numKeys = 0;
    for (int i = 0; i < MAX_CHILDREN; i++) {
        node->children[i] = NULL;
    }
    return node;
}
```

---

## Comparison and Use Cases

### Performance Comparison

| Operation | AVL Tree | Red-Black Tree | B-Tree |
|-----------|----------|----------------|--------|
| Search | O(log n) | O(log n) | O(log n) |
| Insert | O(log n) | O(log n) | O(log n) |
| Delete | O(log n) | O(log n) | O(log n) |
| Rotations | More | Fewer | N/A |

### When to Use Each?

#### AVL Trees
- Search-intensive applications
- In-memory databases
- Symbol tables

#### Red-Black Trees
- C++ STL map/set
- Java TreeMap
- Frequent insertions/deletions

#### B-Trees
- Database indexes
- File systems
- Large-scale storage

---

## Practice Problems

### Problem 1: Check if Binary Tree is AVL
```c
int isAVLUtil(AVLNode* root, int* height) {
    if (root == NULL) {
        *height = 0;
        return 1;
    }

    int leftHeight = 0, rightHeight = 0;
    int leftAVL = isAVLUtil(root->left, &leftHeight);
    int rightAVL = isAVLUtil(root->right, &rightHeight);

    *height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);

    if (abs(leftHeight - rightHeight) > 1) return 0;

    return leftAVL && rightAVL;
}
```

---

## Summary

### Key Takeaways
- **AVL Trees**: Strictest balancing, best for read-heavy workloads
- **Red-Black Trees**: Relaxed balancing, best for write-heavy workloads
- **B-Trees**: Optimized for disk access, best for databases

All guarantee O(log n) operations with different constants and practical performance.

**Choose the right tree for your use case - performance depends on access patterns!**
