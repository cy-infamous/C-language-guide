# C Programming - Data Structures Problems

This file contains 30 comprehensive problems covering all major data structures including linked lists, stacks, queues, trees, and graphs.

---

## Linked Lists (Problems 1-10)

## Problem 1: Singly Linked List - Basic Operations
**Difficulty:** Medium
**Topics:** Linked Lists, Dynamic Memory

### Problem Statement
Implement a singly linked list with operations: insert at beginning, insert at end, delete by value, display, and search.

### Input Format
```
Number of operations
Operations: INSERT_BEGIN value, INSERT_END value, DELETE value, DISPLAY, SEARCH value
```

### Output Format
List status after each operation or search result.

### Constraints
- 1 ≤ operations ≤ 1000
- 1 ≤ value ≤ 10^6

### Example Test Cases

**Test Case 1:**
```
Input:
6
INSERT_BEGIN 10
INSERT_END 20
INSERT_BEGIN 5
DISPLAY
DELETE 10
DISPLAY
Output:
5 -> 10 -> 20 -> NULL
5 -> 20 -> NULL
```

<details>
<summary>Hint</summary>
Define node structure with data and next pointer. Maintain head pointer. For insert at beginning, create new node and make it head. For insert at end, traverse to last node.
</details>

---

## Problem 2: Reverse a Linked List
**Difficulty:** Medium
**Topics:** Linked Lists, Pointers

### Problem Statement
Reverse a singly linked list iteratively and recursively.

### Input Format
```
N (number of elements)
N space-separated integers
```

### Output Format
```
Original: [list]
Reversed (Iterative): [list]
Reversed (Recursive): [list]
```

### Constraints
- 1 ≤ N ≤ 10000

### Example Test Cases

**Test Case 1:**
```
Input:
5
1 2 3 4 5
Output:
Original: 1 -> 2 -> 3 -> 4 -> 5 -> NULL
Reversed: 5 -> 4 -> 3 -> 2 -> 1 -> NULL
```

<details>
<summary>Hint</summary>
Iterative: Use three pointers (prev, current, next). Reverse links one by one.
Recursive: Reverse rest of list first, then fix links. Base case: single node or NULL.
</details>

---

## Problem 3: Detect Cycle in Linked List
**Difficulty:** Medium
**Topics:** Linked Lists, Floyd's Algorithm

### Problem Statement
Detect if a linked list contains a cycle using Floyd's Cycle Detection Algorithm (slow and fast pointers).

### Input Format
```
N (number of nodes)
N values
Position where cycle starts (0 for no cycle)
```

### Output Format
```
Cycle detected: Yes/No
If yes, cycle starts at position: [pos]
```

### Constraints
- 1 ≤ N ≤ 10000

### Example Test Cases

**Test Case 1:**
```
Input:
5
1 2 3 4 5
2
Output:
Cycle detected: Yes
Cycle starts at position: 2 (value: 3)
```

<details>
<summary>Hint</summary>
Use two pointers: slow (moves 1 step) and fast (moves 2 steps). If they meet, cycle exists. To find start of cycle, reset one pointer to head and move both one step at a time.
</details>

---

## Problem 4: Middle Element of Linked List
**Difficulty:** Easy
**Topics:** Linked Lists, Two-Pointer Technique

### Problem Statement
Find the middle element of a linked list in a single traversal.

### Input Format
```
N (number of elements)
N space-separated integers
```

### Output Format
```
Middle element: [value]
```

### Constraints
- 1 ≤ N ≤ 10000

### Example Test Cases

**Test Case 1:**
```
Input:
5
1 2 3 4 5
Output:
Middle element: 3
```

**Test Case 2:**
```
Input:
6
1 2 3 4 5 6
Output:
Middle element: 3
```

<details>
<summary>Hint</summary>
Use slow and fast pointer approach. Slow moves 1 step, fast moves 2 steps. When fast reaches end, slow is at middle.
</details>

---

## Problem 5: Merge Two Sorted Linked Lists
**Difficulty:** Medium
**Topics:** Linked Lists, Merging

### Problem Statement
Merge two sorted linked lists into a single sorted linked list.

### Input Format
```
N1 (elements in list 1)
N1 sorted integers
N2 (elements in list 2)
N2 sorted integers
```

### Output Format
```
Merged list: [elements]
```

### Constraints
- 0 ≤ N1, N2 ≤ 1000
- Lists are sorted in ascending order

### Example Test Cases

**Test Case 1:**
```
Input:
3
1 3 5
3
2 4 6
Output:
Merged list: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> NULL
```

<details>
<summary>Hint</summary>
Compare heads of both lists, attach smaller one to result. Move pointer forward in that list. Repeat until one list is empty, then attach remaining list.
</details>

---

## Problem 6: Remove Duplicates from Sorted Linked List
**Difficulty:** Easy
**Topics:** Linked Lists

### Problem Statement
Remove duplicate elements from a sorted linked list.

### Input Format
```
N (number of elements)
N sorted integers (may have duplicates)
```

### Output Format
```
Original: [list]
After removing duplicates: [list]
```

### Constraints
- 1 ≤ N ≤ 10000

### Example Test Cases

**Test Case 1:**
```
Input:
7
1 1 2 3 3 3 4
Output:
Original: 1 -> 1 -> 2 -> 3 -> 3 -> 3 -> 4 -> NULL
After removing duplicates: 1 -> 2 -> 3 -> 4 -> NULL
```

<details>
<summary>Hint</summary>
Traverse the list. If current node's data equals next node's data, delete next node. Continue until no more duplicates.
</details>

---

## Problem 7: Doubly Linked List Operations
**Difficulty:** Medium
**Topics:** Doubly Linked Lists

### Problem Statement
Implement a doubly linked list with insert, delete, forward traversal, and backward traversal operations.

### Input Format
```
Operations: INSERT value, DELETE value, FORWARD, BACKWARD
```

### Output Format
List in forward or backward direction as requested.

### Constraints
- 1 ≤ operations ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input:
INSERT 10
INSERT 20
INSERT 30
FORWARD
BACKWARD
Output:
Forward: 10 <-> 20 <-> 30 <-> NULL
Backward: 30 <-> 20 <-> 10 <-> NULL
```

<details>
<summary>Hint</summary>
Node structure: data, next pointer, prev pointer. Maintain head and tail pointers. Update both next and prev links when inserting/deleting.
</details>

---

## Problem 8: Circular Linked List
**Difficulty:** Medium
**Topics:** Circular Linked Lists

### Problem Statement
Implement a circular linked list where the last node points back to the first node.

### Input Format
```
Operations: INSERT value, DELETE value, DISPLAY
```

### Output Format
List elements (show circular nature).

### Constraints
- 1 ≤ operations ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input:
INSERT 10
INSERT 20
INSERT 30
DISPLAY
Output:
10 -> 20 -> 30 -> (back to 10)
```

<details>
<summary>Hint</summary>
Last node's next points to head. Be careful with traversal to avoid infinite loops. Use do-while loop or check if you've reached the starting node again.
</details>

---

## Problem 9: Nth Node from End
**Difficulty:** Medium
**Topics:** Linked Lists, Two-Pointer Technique

### Problem Statement
Find the Nth node from the end of a linked list in a single traversal.

### Input Format
```
Number of elements
Elements
N (position from end)
```

### Output Format
```
Nth node from end: [value]
```

### Constraints
- 1 ≤ N ≤ list length ≤ 10000

### Example Test Cases

**Test Case 1:**
```
Input:
5
1 2 3 4 5
2
Output:
2nd node from end: 4
```

<details>
<summary>Hint</summary>
Use two pointers. Move first pointer N steps ahead. Then move both pointers together until first reaches end. Second pointer is at Nth node from end.
</details>

---

## Problem 10: Intersection of Two Linked Lists
**Difficulty:** Hard
**Topics:** Linked Lists, Hashing

### Problem Statement
Find the intersection point of two singly linked lists (if they merge at some point).

### Input Format
```
List 1 elements
List 2 elements
Common elements (if any)
```

### Output Format
```
Intersection point: [value] or No intersection
```

### Constraints
- 1 ≤ list length ≤ 10000

### Example Test Cases

**Test Case 1:**
```
Input:
List 1: 1 -> 2 -> 3 -> 6 -> 7
List 2: 4 -> 5 -> 6 -> 7
Output:
Intersection point: 6
```

<details>
<summary>Hint</summary>
Method 1: Use hashing to store nodes of first list, traverse second to find common node.
Method 2: Calculate lengths, advance longer list's pointer by difference, then move both together.
</details>

---

## Stacks (Problems 11-15)

## Problem 11: Stack Implementation Using Array
**Difficulty:** Easy
**Topics:** Stack, Arrays

### Problem Statement
Implement a stack using arrays with operations: push, pop, peek, isEmpty, isFull.

### Input Format
```
Stack capacity
Operations: PUSH value, POP, PEEK, ISEMPTY, ISFULL
```

### Output Format
Result of each operation or error message.

### Constraints
- 1 ≤ capacity ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input:
5
PUSH 10
PUSH 20
PEEK
POP
PEEK
Output:
Pushed: 10
Pushed: 20
Top element: 20
Popped: 20
Top element: 10
```

<details>
<summary>Hint</summary>
Use an array and a top variable (initially -1). Push: increment top, add element. Pop: return element at top, decrement top. Check for overflow and underflow.
</details>

---

## Problem 12: Stack Implementation Using Linked List
**Difficulty:** Medium
**Topics:** Stack, Linked Lists

### Problem Statement
Implement a stack using a linked list (dynamic size, no overflow).

### Input Format
```
Operations: PUSH value, POP, PEEK, DISPLAY
```

### Output Format
Result of each operation.

### Constraints
- Limited by available memory

### Example Test Cases

**Test Case 1:**
```
Input:
PUSH 10
PUSH 20
PUSH 30
DISPLAY
POP
DISPLAY
Output:
Stack: 30 -> 20 -> 10 -> NULL
Popped: 30
Stack: 20 -> 10 -> NULL
```

<details>
<summary>Hint</summary>
Use linked list with insertions/deletions at head (top of stack). Push: insert at beginning. Pop: remove from beginning. No size limit.
</details>

---

## Problem 13: Balanced Parentheses Checker
**Difficulty:** Medium
**Topics:** Stack, String Processing

### Problem Statement
Check if parentheses/brackets in an expression are balanced. Support (), {}, [].

### Input Format
```
Expression string
```

### Output Format
```
Balanced or Not Balanced
```

### Constraints
- 1 ≤ string length ≤ 10000

### Example Test Cases

**Test Case 1:**
```
Input: {[()]}
Output: Balanced
```

**Test Case 2:**
```
Input: {[(])}
Output: Not Balanced
```

**Test Case 3:**
```
Input: ((()))
Output: Balanced
```

<details>
<summary>Hint</summary>
Push opening brackets onto stack. For closing brackets, check if stack top matches. If stack is empty or doesn't match, not balanced. At end, stack should be empty.
</details>

---

## Problem 14: Infix to Postfix Conversion
**Difficulty:** Hard
**Topics:** Stack, Expression Evaluation

### Problem Statement
Convert infix expression to postfix notation using stack.

### Input Format
```
Infix expression
```

### Output Format
```
Postfix expression
```

### Constraints
- Valid infix expression
- Operators: +, -, *, /, ^
- May include parentheses

### Example Test Cases

**Test Case 1:**
```
Input: A+B*C
Output: ABC*+
```

**Test Case 2:**
```
Input: (A+B)*C
Output: AB+C*
```

**Test Case 3:**
```
Input: A+B*C-D/E
Output: ABC*+DE/-
```

<details>
<summary>Hint</summary>
Rules:
1. Operands go directly to output
2. Push '(' onto stack
3. For ')', pop until '(' found
4. For operators, pop higher/equal precedence operators, then push current
5. At end, pop all remaining operators
</details>

---

## Problem 15: Evaluate Postfix Expression
**Difficulty:** Medium
**Topics:** Stack, Expression Evaluation

### Problem Statement
Evaluate a postfix expression using stack.

### Input Format
```
Postfix expression with space-separated tokens
```

### Output Format
```
Result: [value]
```

### Constraints
- Valid postfix expression
- Single digit operands or space-separated multi-digit numbers

### Example Test Cases

**Test Case 1:**
```
Input: 5 3 + 2 *
Output: Result: 16
Explanation: (5+3)*2 = 16
```

**Test Case 2:**
```
Input: 8 2 / 3 +
Output: Result: 7
Explanation: 8/2+3 = 7
```

<details>
<summary>Hint</summary>
Scan expression left to right. If operand, push to stack. If operator, pop two operands, apply operator, push result. Final stack element is answer.
</details>

---

## Queues (Problems 16-20)

## Problem 16: Queue Implementation Using Array
**Difficulty:** Easy
**Topics:** Queue, Arrays

### Problem Statement
Implement a circular queue using arrays with operations: enqueue, dequeue, front, rear, isEmpty, isFull.

### Input Format
```
Queue capacity
Operations: ENQUEUE value, DEQUEUE, FRONT, REAR
```

### Output Format
Result of each operation.

### Constraints
- 1 ≤ capacity ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input:
5
ENQUEUE 10
ENQUEUE 20
FRONT
DEQUEUE
FRONT
Output:
Enqueued: 10
Enqueued: 20
Front: 10
Dequeued: 10
Front: 20
```

<details>
<summary>Hint</summary>
Use circular array with front and rear pointers. Enqueue: rear = (rear + 1) % capacity. Dequeue: front = (front + 1) % capacity. Check full: (rear + 1) % capacity == front.
</details>

---

## Problem 17: Queue Implementation Using Linked List
**Difficulty:** Medium
**Topics:** Queue, Linked Lists

### Problem Statement
Implement a queue using linked list with dynamic size.

### Input Format
```
Operations: ENQUEUE value, DEQUEUE, DISPLAY
```

### Output Format
Result of each operation.

### Constraints
- Limited by available memory

### Example Test Cases

**Test Case 1:**
```
Input:
ENQUEUE 10
ENQUEUE 20
ENQUEUE 30
DISPLAY
DEQUEUE
DISPLAY
Output:
Queue: 10 -> 20 -> 30 -> NULL
Dequeued: 10
Queue: 20 -> 30 -> NULL
```

<details>
<summary>Hint</summary>
Maintain front and rear pointers. Enqueue: add at rear. Dequeue: remove from front. No size limit (unlike array implementation).
</details>

---

## Problem 18: Implement Stack Using Two Queues
**Difficulty:** Medium
**Topics:** Stack, Queue, Data Structure Design

### Problem Statement
Implement a stack using two queues.

### Input Format
```
Operations: PUSH value, POP, TOP
```

### Output Format
Result of each operation.

### Constraints
- 1 ≤ operations ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input:
PUSH 10
PUSH 20
TOP
POP
TOP
Output:
Pushed: 10
Pushed: 20
Top: 20
Popped: 20
Top: 10
```

<details>
<summary>Hint</summary>
Method 1 (costly push): For push, enqueue to q2, then move all of q1 to q2, swap q1 and q2.
Method 2 (costly pop): For pop, dequeue all except last from q1 to q2, dequeue last from q1, swap queues.
</details>

---

## Problem 19: Implement Queue Using Two Stacks
**Difficulty:** Medium
**Topics:** Queue, Stack, Data Structure Design

### Problem Statement
Implement a queue using two stacks.

### Input Format
```
Operations: ENQUEUE value, DEQUEUE, FRONT
```

### Output Format
Result of each operation.

### Constraints
- 1 ≤ operations ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input:
ENQUEUE 10
ENQUEUE 20
DEQUEUE
ENQUEUE 30
DEQUEUE
Output:
Enqueued: 10
Enqueued: 20
Dequeued: 10
Enqueued: 30
Dequeued: 20
```

<details>
<summary>Hint</summary>
Use two stacks: s1 (for enqueue) and s2 (for dequeue). Enqueue: push to s1. Dequeue: if s2 empty, move all from s1 to s2, then pop from s2.
</details>

---

## Problem 20: Priority Queue Implementation
**Difficulty:** Medium
**Topics:** Priority Queue, Heaps

### Problem Statement
Implement a priority queue where elements with higher priority are dequeued first.

### Input Format
```
Operations: ENQUEUE value priority, DEQUEUE, PEEK
```

### Output Format
Result of each operation.

### Constraints
- 1 ≤ priority ≤ 10
- Higher number = higher priority

### Example Test Cases

**Test Case 1:**
```
Input:
ENQUEUE 10 2
ENQUEUE 20 5
ENQUEUE 30 1
DEQUEUE
PEEK
Output:
Enqueued: 10 (priority: 2)
Enqueued: 20 (priority: 5)
Enqueued: 30 (priority: 1)
Dequeued: 20 (highest priority: 5)
Front: 10 (priority: 2)
```

<details>
<summary>Hint</summary>
Method 1: Use array/linked list, dequeue by finding highest priority element.
Method 2: Use heap (binary heap) for efficient insertion and deletion.
Method 3: Maintain sorted order while inserting.
</details>

---

## Trees (Problems 21-25)

## Problem 21: Binary Tree Traversals
**Difficulty:** Medium
**Topics:** Binary Trees, Recursion

### Problem Statement
Implement all three DFS traversals: Inorder, Preorder, Postorder. Also implement level-order traversal.

### Input Format
```
Number of nodes
Nodes in level-order (use -1 for NULL)
```

### Output Format
```
Inorder: [elements]
Preorder: [elements]
Postorder: [elements]
Level-order: [elements]
```

### Constraints
- 1 ≤ nodes ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input:
7
1 2 3 4 5 6 7
Output:
Inorder: 4 2 5 1 6 3 7
Preorder: 1 2 4 5 3 6 7
Postorder: 4 5 2 6 7 3 1
Level-order: 1 2 3 4 5 6 7
```

<details>
<summary>Hint</summary>
Inorder: Left, Root, Right
Preorder: Root, Left, Right
Postorder: Left, Right, Root
Level-order: Use queue, process level by level
</details>

---

## Problem 22: Binary Search Tree Operations
**Difficulty:** Medium
**Topics:** BST, Recursion

### Problem Statement
Implement BST with insert, search, delete, find min, find max, and inorder traversal.

### Input Format
```
Operations: INSERT value, SEARCH value, DELETE value, FINDMIN, FINDMAX, DISPLAY
```

### Output Format
Result of each operation.

### Constraints
- 1 ≤ values ≤ 10^6

### Example Test Cases

**Test Case 1:**
```
Input:
INSERT 50
INSERT 30
INSERT 70
INSERT 20
INSERT 40
DISPLAY
SEARCH 40
FINDMIN
FINDMAX
Output:
Inserted: 50, 30, 70, 20, 40
Inorder: 20 30 40 50 70
Found: 40
Minimum: 20
Maximum: 70
```

<details>
<summary>Hint</summary>
BST property: left subtree < root < right subtree.
Insert: Compare with root, recursively insert in left or right.
Search: Similar to insert.
Delete: Three cases: leaf, one child, two children (replace with inorder successor).
</details>

---

## Problem 23: Height and Depth of Binary Tree
**Difficulty:** Medium
**Topics:** Binary Trees, Recursion

### Problem Statement
Calculate the height of a binary tree and depth of each node.

### Input Format
```
Nodes in level-order
```

### Output Format
```
Height: [value]
Node depths: [node: depth pairs]
```

### Constraints
- 1 ≤ nodes ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input: 1 2 3 4 5 -1 6
Output:
Height: 3
Depths: 1:0, 2:1, 3:1, 4:2, 5:2, 6:2
```

<details>
<summary>Hint</summary>
Height: Height of tree = 1 + max(height of left, height of right). Base case: empty tree has height 0.
Depth: Depth of root = 0, depth of child = depth of parent + 1.
</details>

---

## Problem 24: Check if Binary Tree is BST
**Difficulty:** Medium
**Topics:** BST, Tree Validation

### Problem Statement
Validate whether a binary tree is a valid Binary Search Tree.

### Input Format
```
Tree structure
```

### Output Format
```
Valid BST: Yes/No
```

### Constraints
- 1 ≤ nodes ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input:
    5
   / \
  3   7
 / \ / \
1  4 6  8
Output: Valid BST: Yes
```

**Test Case 2:**
```
Input:
    5
   / \
  3   7
 / \ / \
1  6 6  8
Output: Valid BST: No
```

<details>
<summary>Hint</summary>
Method 1: Do inorder traversal, check if result is sorted.
Method 2: Recursively check if each node falls within valid range [min, max].
</details>

---

## Problem 25: Lowest Common Ancestor in BST
**Difficulty:** Medium
**Topics:** BST, Tree Algorithms

### Problem Statement
Find the lowest common ancestor (LCA) of two nodes in a BST.

### Input Format
```
BST nodes
Node 1 value
Node 2 value
```

### Output Format
```
LCA: [value]
```

### Constraints
- 1 ≤ values ≤ 10^6
- Both nodes exist in tree

### Example Test Cases

**Test Case 1:**
```
Input:
Tree: 20 10 30 5 15 25 35
Node1: 5
Node2: 15
Output: LCA: 10
```

<details>
<summary>Hint</summary>
Use BST property: if both nodes are smaller than root, LCA is in left subtree. If both larger, LCA is in right subtree. Otherwise, root is LCA.
</details>

---

## Graphs (Problems 26-30)

## Problem 26: Graph Representation
**Difficulty:** Easy
**Topics:** Graphs, Adjacency Matrix, Adjacency List

### Problem Statement
Implement graph using both adjacency matrix and adjacency list representations.

### Input Format
```
Number of vertices
Number of edges
Edge pairs (u v)
```

### Output Format
```
Adjacency Matrix:
[matrix]
Adjacency List:
[lists]
```

### Constraints
- 1 ≤ vertices ≤ 100
- 0 ≤ edges ≤ vertices²

### Example Test Cases

**Test Case 1:**
```
Input:
4
5
0 1
0 2
1 2
2 3
3 0
Output:
Adjacency Matrix:
0 1 1 1
1 0 1 0
1 1 0 1
1 0 1 0

Adjacency List:
0: 1 -> 2 -> 3
1: 0 -> 2
2: 0 -> 1 -> 3
3: 0 -> 2
```

<details>
<summary>Hint</summary>
Adjacency Matrix: 2D array, matrix[i][j] = 1 if edge exists.
Adjacency List: Array of linked lists, each index stores list of adjacent vertices.
</details>

---

## Problem 27: BFS Traversal
**Difficulty:** Medium
**Topics:** Graphs, BFS, Queue

### Problem Statement
Implement Breadth-First Search traversal of a graph.

### Input Format
```
Number of vertices
Edges
Starting vertex
```

### Output Format
```
BFS Traversal: [vertices in order]
```

### Constraints
- 1 ≤ vertices ≤ 1000
- Graph may be disconnected

### Example Test Cases

**Test Case 1:**
```
Input:
5
0 1
0 2
1 3
2 4
Start: 0
Output:
BFS: 0 1 2 3 4
```

<details>
<summary>Hint</summary>
Use queue and visited array. Start with source, mark as visited, enqueue. While queue not empty: dequeue vertex, process it, enqueue all unvisited neighbors.
</details>

---

## Problem 28: DFS Traversal
**Difficulty:** Medium
**Topics:** Graphs, DFS, Recursion/Stack

### Problem Statement
Implement Depth-First Search traversal of a graph (both recursive and iterative).

### Input Format
```
Number of vertices
Edges
Starting vertex
```

### Output Format
```
DFS (Recursive): [vertices]
DFS (Iterative): [vertices]
```

### Constraints
- 1 ≤ vertices ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input:
5
0 1
0 2
1 3
2 4
Start: 0
Output:
DFS Recursive: 0 1 3 2 4
DFS Iterative: 0 2 4 1 3
```

<details>
<summary>Hint</summary>
Recursive: Mark current as visited, recursively visit all unvisited neighbors.
Iterative: Use stack instead of recursion. Push source, while stack not empty: pop vertex, if not visited, mark visited and push all neighbors.
</details>

---

## Problem 29: Detect Cycle in Undirected Graph
**Difficulty:** Medium
**Topics:** Graphs, Cycle Detection, DFS

### Problem Statement
Detect if an undirected graph contains a cycle.

### Input Format
```
Number of vertices
Number of edges
Edge pairs
```

### Output Format
```
Cycle exists: Yes/No
```

### Constraints
- 1 ≤ vertices ≤ 1000

### Example Test Cases

**Test Case 1:**
```
Input:
5
5
0 1
1 2
2 3
3 4
4 1
Output: Cycle exists: Yes
```

**Test Case 2:**
```
Input:
3
2
0 1
1 2
Output: Cycle exists: No
```

<details>
<summary>Hint</summary>
Use DFS. During traversal, if you encounter a visited vertex that is not the parent of current vertex, cycle exists. Handle disconnected components.
</details>

---

## Problem 30: Dijkstra's Shortest Path
**Difficulty:** Hard
**Topics:** Graphs, Shortest Path, Priority Queue

### Problem Statement
Find shortest path from source to all vertices in a weighted graph using Dijkstra's algorithm.

### Input Format
```
Number of vertices
Number of edges
Edges with weights (u v weight)
Source vertex
```

### Output Format
```
Vertex: Distance from source
Path to each vertex
```

### Constraints
- 1 ≤ vertices ≤ 1000
- Non-negative edge weights
- Connected graph

### Example Test Cases

**Test Case 1:**
```
Input:
5
7
0 1 4
0 2 1
1 3 1
2 1 2
2 3 5
3 4 3
1 4 6
Source: 0
Output:
Vertex 0: Distance = 0, Path: 0
Vertex 1: Distance = 3, Path: 0 -> 2 -> 1
Vertex 2: Distance = 1, Path: 0 -> 2
Vertex 3: Distance = 4, Path: 0 -> 2 -> 1 -> 3
Vertex 4: Distance = 7, Path: 0 -> 2 -> 1 -> 3 -> 4
```

<details>
<summary>Hint</summary>
Initialize distances to infinity, source to 0. Use min-heap/priority queue. Extract minimum distance vertex, update distances of its neighbors (relaxation). Repeat until all vertices processed.
</details>

---

## Additional Practice Tips

1. **Understand Fundamentals:** Master basic operations before complex algorithms
2. **Draw Diagrams:** Visualize data structures on paper
3. **Analyze Complexity:** Calculate time and space complexity for each operation
4. **Test Edge Cases:** Empty structures, single elements, cycles, etc.
5. **Compare Implementations:** Array vs linked list, iterative vs recursive
6. **Practice Tracing:** Manually trace algorithm execution step by step

## Next Steps

After completing these exercises, move on to:
- **05-algorithms-problems.md** for algorithm challenges
- **06-coding-challenges.md** for comprehensive multi-concept problems
- Check the **solutions/** directory for detailed solutions and explanations
