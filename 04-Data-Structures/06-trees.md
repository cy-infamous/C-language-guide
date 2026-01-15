# Trees - Complete Guide

## Table of Contents
1. [Introduction to Trees](#introduction-to-trees)
2. [Binary Trees](#binary-trees)
3. [Binary Search Trees (BST)](#binary-search-trees-bst)
4. [Tree Traversals](#tree-traversals)
5. [Common Tree Operations](#common-tree-operations)
6. [Advanced Problems](#advanced-problems)
7. [Practice Problems](#practice-problems)

---

## Introduction to Trees

### What is a Tree?
A **tree** is a hierarchical data structure consisting of nodes connected by edges. It has:
- One **root** node
- **Parent-child** relationships
- No cycles

### Tree Terminology
```
        1          ← Root (level 0)
       / \
      2   3        ← Siblings (level 1)
     / \   \
    4   5   6      ← Leaves (level 2)
```

| Term | Definition |
|------|------------|
| **Root** | Topmost node with no parent |
| **Parent** | Node with children |
| **Child** | Node descended from parent |
| **Siblings** | Nodes with same parent |
| **Leaf** | Node with no children |
| **Internal Node** | Node with at least one child |
| **Edge** | Connection between nodes |
| **Path** | Sequence of nodes connected by edges |
| **Height** | Longest path from node to leaf |
| **Depth** | Distance from root to node |
| **Level** | Depth + 1 |
| **Degree** | Number of children |
| **Subtree** | Tree formed by node and descendants |

### Tree Properties
- **n nodes** have **n-1 edges**
- **Height of empty tree**: -1
- **Height of single node**: 0
- **Maximum nodes at level L**: 2^L
- **Maximum nodes in tree of height H**: 2^(H+1) - 1

---

## Binary Trees

### What is a Binary Tree?
A tree where each node has **at most 2 children** (left and right).

### Types of Binary Trees

#### 1. Full Binary Tree
Every node has 0 or 2 children.
```
        1
       / \
      2   3
     / \
    4   5
```

#### 2. Complete Binary Tree
All levels filled except possibly last, which is filled left to right.
```
        1
       / \
      2   3
     / \  /
    4  5 6
```

#### 3. Perfect Binary Tree
All internal nodes have 2 children, all leaves at same level.
```
        1
       / \
      2   3
     / \ / \
    4  5 6  7
```

#### 4. Balanced Binary Tree
Height difference between left and right subtrees ≤ 1 for all nodes.
```
        1
       / \
      2   3
     /
    4
(Height difference: |2-1| = 1 ✓)
```

#### 5. Degenerate (Skewed) Tree
Each parent has only one child.
```
    1
     \
      2
       \
        3
         \
          4
```

### Node Structure

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Create new node
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Build sample tree
TreeNode* buildSampleTree() {
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    return root;
}

int main() {
    TreeNode* root = buildSampleTree();
    printf("Tree created successfully!\n");
    return 0;
}
```

---

## Binary Search Trees (BST)

### Definition
A binary tree where:
- **Left subtree** contains only nodes with values **less than** parent
- **Right subtree** contains only nodes with values **greater than** parent
- Both subtrees are also BSTs

### BST Example
```
        50
       /  \
      30   70
     / \   / \
   20  40 60  80

In-order traversal: 20, 30, 40, 50, 60, 70, 80 (sorted!)
```

### BST Implementation

```c
// Search in BST - O(h) where h is height
TreeNode* search(TreeNode* root, int key) {
    // Base cases
    if (root == NULL || root->data == key) {
        return root;
    }

    // Key smaller than root, search left
    if (key < root->data) {
        return search(root->left, key);
    }

    // Key larger than root, search right
    return search(root->right, key);
}

// Iterative search
TreeNode* searchIterative(TreeNode* root, int key) {
    while (root != NULL && root->data != key) {
        if (key < root->data) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return root;
}

// Insert in BST - O(h)
TreeNode* insert(TreeNode* root, int data) {
    // Base case: empty tree
    if (root == NULL) {
        return createNode(data);
    }

    // Recursive case
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    // Equal elements not allowed in BST

    return root;
}

// Find minimum value node - O(h)
TreeNode* findMin(TreeNode* root) {
    if (root == NULL) return NULL;

    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Find maximum value node - O(h)
TreeNode* findMax(TreeNode* root) {
    if (root == NULL) return NULL;

    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

// Delete from BST - O(h)
TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == NULL) return root;

    // Find the node to delete
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node found, handle three cases

        // Case 1: Node with no children (leaf)
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        // Case 2: Node with one child
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        // Case 3: Node with two children
        // Find inorder successor (smallest in right subtree)
        TreeNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

// Check if valid BST
bool isBSTUtil(TreeNode* root, int min, int max) {
    if (root == NULL) return true;

    if (root->data <= min || root->data >= max) {
        return false;
    }

    return isBSTUtil(root->left, min, root->data) &&
           isBSTUtil(root->right, root->data, max);
}

bool isBST(TreeNode* root) {
    return isBSTUtil(root, INT_MIN, INT_MAX);
}
```

### BST Deletion Visual
```
Delete 30 from:
        50
       /  \
      30   70
     / \
   20  40

Step 1: Find node (30)
Step 2: Node has 2 children
Step 3: Find inorder successor (40)
Step 4: Replace 30 with 40
Step 5: Delete duplicate 40

Result:
        50
       /  \
      40   70
     /
   20
```

---

## Tree Traversals

### 1. Inorder Traversal (Left → Root → Right)

```c
// Recursive - O(n)
void inorderRecursive(TreeNode* root) {
    if (root == NULL) return;

    inorderRecursive(root->left);
    printf("%d ", root->data);
    inorderRecursive(root->right);
}

// Iterative using stack
void inorderIterative(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* stack[100];
    int top = -1;
    TreeNode* current = root;

    while (current != NULL || top >= 0) {
        // Go to leftmost node
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }

        // Current is NULL, pop from stack
        current = stack[top--];
        printf("%d ", current->data);

        // Visit right subtree
        current = current->right;
    }
}

// Example Tree:
//      1
//     / \
//    2   3
//   / \
//  4   5
//
// Inorder: 4 2 5 1 3
```

### 2. Preorder Traversal (Root → Left → Right)

```c
// Recursive - O(n)
void preorderRecursive(TreeNode* root) {
    if (root == NULL) return;

    printf("%d ", root->data);
    preorderRecursive(root->left);
    preorderRecursive(root->right);
}

// Iterative using stack
void preorderIterative(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* stack[100];
    int top = -1;

    stack[++top] = root;

    while (top >= 0) {
        TreeNode* current = stack[top--];
        printf("%d ", current->data);

        // Push right first (so left is processed first)
        if (current->right) stack[++top] = current->right;
        if (current->left) stack[++top] = current->left;
    }
}

// Example Tree:
//      1
//     / \
//    2   3
//   / \
//  4   5
//
// Preorder: 1 2 4 5 3
```

### 3. Postorder Traversal (Left → Right → Root)

```c
// Recursive - O(n)
void postorderRecursive(TreeNode* root) {
    if (root == NULL) return;

    postorderRecursive(root->left);
    postorderRecursive(root->right);
    printf("%d ", root->data);
}

// Iterative using two stacks
void postorderIterative(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* stack1[100];
    TreeNode* stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;

    while (top1 >= 0) {
        TreeNode* current = stack1[top1--];
        stack2[++top2] = current;

        if (current->left) stack1[++top1] = current->left;
        if (current->right) stack1[++top1] = current->right;
    }

    while (top2 >= 0) {
        printf("%d ", stack2[top2--]->data);
    }
}

// Example Tree:
//      1
//     / \
//    2   3
//   / \
//  4   5
//
// Postorder: 4 5 2 3 1
```

### 4. Level Order Traversal (BFS)

```c
// Using queue - O(n)
void levelOrder(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        TreeNode* current = queue[front++];
        printf("%d ", current->data);

        if (current->left) queue[rear++] = current->left;
        if (current->right) queue[rear++] = current->right;
    }
}

// Level order with level indication
void levelOrderByLevel(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    int level = 0;

    while (front < rear) {
        int levelSize = rear - front;
        printf("Level %d: ", level++);

        for (int i = 0; i < levelSize; i++) {
            TreeNode* current = queue[front++];
            printf("%d ", current->data);

            if (current->left) queue[rear++] = current->left;
            if (current->right) queue[rear++] = current->right;
        }
        printf("\n");
    }
}

// Example Tree:
//      1
//     / \
//    2   3
//   / \
//  4   5
//
// Level Order: 1 2 3 4 5
// By Level:
// Level 0: 1
// Level 1: 2 3
// Level 2: 4 5
```

### Traversal Comparison Visual
```
Tree:
        1
       / \
      2   3
     / \
    4   5

Inorder:   4 2 5 1 3     (Left-Root-Right)
Preorder:  1 2 4 5 3     (Root-Left-Right)
Postorder: 4 5 2 3 1     (Left-Right-Root)
Level:     1 2 3 4 5     (Level by level)
```

---

## Common Tree Operations

### 1. Height of Tree

```c
// Height = longest path from root to leaf
int height(TreeNode* root) {
    if (root == NULL) return -1;  // or 0 depending on definition

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}
```

### 2. Count Nodes

```c
// Count total nodes - O(n)
int countNodes(TreeNode* root) {
    if (root == NULL) return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Count leaf nodes
int countLeaves(TreeNode* root) {
    if (root == NULL) return 0;

    if (root->left == NULL && root->right == NULL) {
        return 1;
    }

    return countLeaves(root->left) + countLeaves(root->right);
}
```

### 3. Diameter of Tree

```c
// Diameter = longest path between any two nodes
int diameterUtil(TreeNode* root, int* height) {
    if (root == NULL) {
        *height = 0;
        return 0;
    }

    int leftHeight = 0, rightHeight = 0;
    int leftDiameter = diameterUtil(root->left, &leftHeight);
    int rightDiameter = diameterUtil(root->right, &rightHeight);

    *height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);

    // Diameter through root
    int throughRoot = leftHeight + rightHeight;

    // Maximum of three
    int maxDiameter = leftDiameter > rightDiameter ?
                      leftDiameter : rightDiameter;
    maxDiameter = maxDiameter > throughRoot ? maxDiameter : throughRoot;

    return maxDiameter;
}

int diameter(TreeNode* root) {
    int height = 0;
    return diameterUtil(root, &height);
}
```

### 4. Check if Balanced

```c
// Balanced if height difference ≤ 1 for all nodes
int checkBalance(TreeNode* root, bool* balanced) {
    if (root == NULL) return 0;

    int leftHeight = checkBalance(root->left, balanced);
    int rightHeight = checkBalance(root->right, balanced);

    if (abs(leftHeight - rightHeight) > 1) {
        *balanced = false;
    }

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

bool isBalanced(TreeNode* root) {
    bool balanced = true;
    checkBalance(root, &balanced);
    return balanced;
}
```

### 5. Lowest Common Ancestor (LCA)

```c
// Find LCA in BST - O(h)
TreeNode* lcaBST(TreeNode* root, int n1, int n2) {
    if (root == NULL) return NULL;

    // If both smaller, LCA in left
    if (root->data > n1 && root->data > n2) {
        return lcaBST(root->left, n1, n2);
    }

    // If both larger, LCA in right
    if (root->data < n1 && root->data < n2) {
        return lcaBST(root->right, n1, n2);
    }

    // Otherwise root is LCA
    return root;
}

// Find LCA in binary tree - O(n)
TreeNode* lcaBinaryTree(TreeNode* root, int n1, int n2) {
    if (root == NULL) return NULL;

    if (root->data == n1 || root->data == n2) {
        return root;
    }

    TreeNode* leftLCA = lcaBinaryTree(root->left, n1, n2);
    TreeNode* rightLCA = lcaBinaryTree(root->right, n1, n2);

    // If both return non-NULL, root is LCA
    if (leftLCA && rightLCA) {
        return root;
    }

    // Otherwise return non-NULL value
    return (leftLCA != NULL) ? leftLCA : rightLCA;
}
```

### 6. Mirror/Invert Tree

```c
// Mirror tree - O(n)
void mirror(TreeNode* root) {
    if (root == NULL) return;

    // Swap left and right
    TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;

    // Recursively mirror subtrees
    mirror(root->left);
    mirror(root->right);
}

// Check if two trees are mirrors
bool areMirrors(TreeNode* root1, TreeNode* root2) {
    if (root1 == NULL && root2 == NULL) return true;
    if (root1 == NULL || root2 == NULL) return false;

    return (root1->data == root2->data) &&
           areMirrors(root1->left, root2->right) &&
           areMirrors(root1->right, root2->left);
}

// Check if tree is symmetric
bool isSymmetric(TreeNode* root) {
    if (root == NULL) return true;
    return areMirrors(root->left, root->right);
}
```

### 7. Print Paths from Root to Leaf

```c
void printPathsUtil(TreeNode* root, int path[], int pathLen) {
    if (root == NULL) return;

    // Add current node to path
    path[pathLen] = root->data;
    pathLen++;

    // If leaf, print path
    if (root->left == NULL && root->right == NULL) {
        printf("Path: ");
        for (int i = 0; i < pathLen; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        // Recurse for children
        printPathsUtil(root->left, path, pathLen);
        printPathsUtil(root->right, path, pathLen);
    }
}

void printPaths(TreeNode* root) {
    int path[100];
    printPathsUtil(root, path, 0);
}
```

### 8. Vertical Order Traversal

```c
// Find min and max horizontal distance
void findMinMax(TreeNode* root, int* min, int* max, int hd) {
    if (root == NULL) return;

    if (hd < *min) *min = hd;
    if (hd > *max) *max = hd;

    findMinMax(root->left, min, max, hd - 1);
    findMinMax(root->right, min, max, hd + 1);
}

// Print nodes at given horizontal distance
void printVerticalLine(TreeNode* root, int lineNo, int hd) {
    if (root == NULL) return;

    if (hd == lineNo) {
        printf("%d ", root->data);
    }

    printVerticalLine(root->left, lineNo, hd - 1);
    printVerticalLine(root->right, lineNo, hd + 1);
}

void verticalOrder(TreeNode* root) {
    int min = 0, max = 0;
    findMinMax(root, &min, &max, 0);

    for (int line = min; line <= max; line++) {
        printVerticalLine(root, line, 0);
        printf("\n");
    }
}
```

---

## Advanced Problems

### 1. Construct Tree from Traversals

```c
// Construct from Inorder and Preorder
int findIndex(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) return i;
    }
    return -1;
}

TreeNode* buildTreeUtil(int inorder[], int preorder[],
                        int inStart, int inEnd, int* preIndex) {
    if (inStart > inEnd) return NULL;

    // Pick current node from preorder
    TreeNode* node = createNode(preorder[*preIndex]);
    (*preIndex)++;

    if (inStart == inEnd) return node;

    // Find index in inorder
    int inIndex = findIndex(inorder, inStart, inEnd, node->data);

    // Recursively construct subtrees
    node->left = buildTreeUtil(inorder, preorder, inStart, inIndex - 1, preIndex);
    node->right = buildTreeUtil(inorder, preorder, inIndex + 1, inEnd, preIndex);

    return node;
}

TreeNode* buildTree(int inorder[], int preorder[], int n) {
    int preIndex = 0;
    return buildTreeUtil(inorder, preorder, 0, n - 1, &preIndex);
}

// Example:
// Inorder:  [4, 2, 5, 1, 3]
// Preorder: [1, 2, 4, 5, 3]
// Constructs:
//       1
//      / \
//     2   3
//    / \
//   4   5
```

### 2. Serialize and Deserialize Tree

```c
// Serialize tree to string
void serializeUtil(TreeNode* root, char* str) {
    if (root == NULL) {
        strcat(str, "# ");
        return;
    }

    char val[10];
    sprintf(val, "%d ", root->data);
    strcat(str, val);

    serializeUtil(root->left, str);
    serializeUtil(root->right, str);
}

// Deserialize string to tree
TreeNode* deserializeUtil(char** str) {
    char* token = strtok(*str, " ");

    if (token == NULL || strcmp(token, "#") == 0) {
        *str = NULL;
        return NULL;
    }

    TreeNode* root = createNode(atoi(token));
    *str = NULL;

    root->left = deserializeUtil(str);
    root->right = deserializeUtil(str);

    return root;
}
```

### 3. Maximum Path Sum

```c
// Find maximum path sum in binary tree
int maxPathSumUtil(TreeNode* root, int* maxSum) {
    if (root == NULL) return 0;

    // Get max sum from left and right subtrees
    int left = maxPathSumUtil(root->left, maxSum);
    int right = maxPathSumUtil(root->right, maxSum);

    // Max path through this node
    int maxSingle = (left > right ? left : right) + root->data;
    maxSingle = maxSingle > root->data ? maxSingle : root->data;

    // Max path with node as root
    int maxTop = root->data;
    if (left > 0) maxTop += left;
    if (right > 0) maxTop += right;

    // Update global max
    *maxSum = *maxSum > maxTop ? *maxSum : maxTop;

    return maxSingle;
}

int maxPathSum(TreeNode* root) {
    int maxSum = INT_MIN;
    maxPathSumUtil(root, &maxSum);
    return maxSum;
}
```

---

## Practice Problems

### Problem 1: Find Kth Smallest in BST (Medium)
```c
void kthSmallestUtil(TreeNode* root, int k, int* count, int* result) {
    if (root == NULL || *count >= k) return;

    kthSmallestUtil(root->left, k, count, result);

    (*count)++;
    if (*count == k) {
        *result = root->data;
        return;
    }

    kthSmallestUtil(root->right, k, count, result);
}

int kthSmallest(TreeNode* root, int k) {
    int count = 0, result = -1;
    kthSmallestUtil(root, k, &count, &result);
    return result;
}
```

---

### Problem 2: Convert BST to Greater Tree (Medium)
Each node's value becomes sum of all nodes greater than it.

```c
void convertToGreaterUtil(TreeNode* root, int* sum) {
    if (root == NULL) return;

    convertToGreaterUtil(root->right, sum);

    *sum += root->data;
    root->data = *sum;

    convertToGreaterUtil(root->left, sum);
}

TreeNode* convertToGreaterTree(TreeNode* root) {
    int sum = 0;
    convertToGreaterUtil(root, &sum);
    return root;
}
```

---

### Problem 3: Binary Tree Right Side View (Medium)
```c
void rightSideViewUtil(TreeNode* root, int level, int* maxLevel, int result[]) {
    if (root == NULL) return;

    if (level > *maxLevel) {
        result[level] = root->data;
        *maxLevel = level;
    }

    rightSideViewUtil(root->right, level + 1, maxLevel, result);
    rightSideViewUtil(root->left, level + 1, maxLevel, result);
}

void rightSideView(TreeNode* root) {
    int result[100];
    int maxLevel = -1;
    rightSideViewUtil(root, 0, &maxLevel, result);

    printf("Right side view: ");
    for (int i = 0; i <= maxLevel; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}
```

---

### Problem 4: Flatten Binary Tree to Linked List (Medium)
```c
TreeNode* prev = NULL;

void flatten(TreeNode* root) {
    if (root == NULL) return;

    flatten(root->right);
    flatten(root->left);

    root->right = prev;
    root->left = NULL;
    prev = root;
}
```

---

### Problem 5: Count Complete Tree Nodes (Medium)
```c
int getLeftHeight(TreeNode* root) {
    int height = 0;
    while (root) {
        height++;
        root = root->left;
    }
    return height;
}

int getRightHeight(TreeNode* root) {
    int height = 0;
    while (root) {
        height++;
        root = root->right;
    }
    return height;
}

int countCompleteNodes(TreeNode* root) {
    if (root == NULL) return 0;

    int leftH = getLeftHeight(root);
    int rightH = getRightHeight(root);

    // Perfect tree
    if (leftH == rightH) {
        return (1 << leftH) - 1;  // 2^h - 1
    }

    // Recurse
    return 1 + countCompleteNodes(root->left) +
           countCompleteNodes(root->right);
}
```

---

## Summary

### Time Complexity

| Operation | Average | Worst Case |
|-----------|---------|------------|
| Search (BST) | O(log n) | O(n) |
| Insert (BST) | O(log n) | O(n) |
| Delete (BST) | O(log n) | O(n) |
| Traversal | O(n) | O(n) |
| Height | O(n) | O(n) |

### Space Complexity
- **Recursive**: O(h) for call stack
- **Iterative**: O(h) for explicit stack/queue
- **Tree storage**: O(n)

### Key Takeaways
- Trees are hierarchical structures
- BST enables efficient search/insert/delete
- Four main traversals: inorder, preorder, postorder, level-order
- Many problems solved recursively
- Balanced trees crucial for performance

**Master tree traversals - they're the foundation for advanced tree algorithms!**
