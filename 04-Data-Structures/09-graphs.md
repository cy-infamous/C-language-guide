# Graphs - Complete Guide

## Table of Contents
1. [Introduction to Graphs](#introduction-to-graphs)
2. [Graph Representations](#graph-representations)
3. [Graph Traversal - BFS](#breadth-first-search-bfs)
4. [Graph Traversal - DFS](#depth-first-search-dfs)
5. [Shortest Path Algorithms](#shortest-path-algorithms)
6. [Minimum Spanning Tree](#minimum-spanning-tree)
7. [Advanced Graph Algorithms](#advanced-graph-algorithms)
8. [Practice Problems](#practice-problems)

---

## Introduction to Graphs

### What is a Graph?
A **graph** G = (V, E) is a collection of:
- **V**: Set of vertices (nodes)
- **E**: Set of edges (connections between vertices)

### Graph Types

#### 1. Directed vs Undirected
```
Undirected Graph:        Directed Graph (Digraph):
    A --- B                  A ---> B
    |     |                  ↑      ↓
    C --- D                  C <--- D
```

#### 2. Weighted vs Unweighted
```
Weighted Graph:          Unweighted Graph:
    A -5- B                  A --- B
    |     |                  |     |
    3     2                  C --- D
    |     |
    C -4- D
```

#### 3. Cyclic vs Acyclic
```
Cyclic:                  Acyclic (DAG):
    A --- B                  A --> B
    |     |                  |
    C --- D                  ↓
                             C --> D
```

### Graph Terminology

| Term | Definition | Example |
|------|------------|---------|
| **Vertex** | Node in graph | A, B, C |
| **Edge** | Connection between vertices | (A, B) |
| **Degree** | Number of edges connected to vertex | deg(A) = 2 |
| **Path** | Sequence of vertices | A → B → C |
| **Cycle** | Path that starts and ends at same vertex | A → B → C → A |
| **Connected** | Path exists between all pairs | |
| **Neighbor** | Adjacent vertices | B is neighbor of A |
| **Weight** | Cost/distance of edge | w(A,B) = 5 |

### Graph Visualization
```
Graph with 5 vertices and 6 edges:

      1 ---- 2
     / \      \
    /   \      \
   0     3 ---- 4

Vertices: {0, 1, 2, 3, 4}
Edges: {(0,1), (1,2), (1,3), (2,4), (3,4), (0,3)}
```

---

## Graph Representations

### 1. Adjacency Matrix

**2D array** where matrix[i][j] = 1 if edge exists from i to j.

```c
#define V 5  // Number of vertices

typedef struct {
    int matrix[V][V];
    int numVertices;
} AdjMatrix;

// Initialize matrix
void initMatrix(AdjMatrix* graph) {
    graph->numVertices = V;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph->matrix[i][j] = 0;
        }
    }
}

// Add edge (undirected)
void addEdgeMatrix(AdjMatrix* graph, int src, int dest) {
    graph->matrix[src][dest] = 1;
    graph->matrix[dest][src] = 1;  // For undirected graph
}

// Add edge (directed)
void addDirectedEdgeMatrix(AdjMatrix* graph, int src, int dest) {
    graph->matrix[src][dest] = 1;
}

// Add weighted edge
void addWeightedEdge(int matrix[][V], int src, int dest, int weight) {
    matrix[src][dest] = weight;
    matrix[dest][src] = weight;  // For undirected
}

// Print matrix
void printMatrix(AdjMatrix* graph) {
    printf("Adjacency Matrix:\n");
    printf("  ");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d ", i);
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
}

// Example:
//   0 1 2 3 4
// 0 0 1 0 1 0
// 1 1 0 1 1 0
// 2 0 1 0 0 1
// 3 1 1 0 0 1
// 4 0 0 1 1 0
```

**Advantages:**
- Edge lookup: O(1)
- Simple implementation
- Good for dense graphs

**Disadvantages:**
- Space: O(V²)
- Iterating over edges: O(V²)
- Inefficient for sparse graphs

### 2. Adjacency List

**Array of linked lists** where each list contains neighbors of a vertex.

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    Node** array;
    int numVertices;
} AdjList;

// Create new node
Node* createNode(int vertex, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Initialize adjacency list
AdjList* createGraph(int vertices) {
    AdjList* graph = (AdjList*)malloc(sizeof(AdjList));
    graph->numVertices = vertices;
    graph->array = (Node**)malloc(vertices * sizeof(Node*));

    for (int i = 0; i < vertices; i++) {
        graph->array[i] = NULL;
    }

    return graph;
}

// Add edge (undirected)
void addEdge(AdjList* graph, int src, int dest, int weight) {
    // Add edge from src to dest
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->array[src];
    graph->array[src] = newNode;

    // Add edge from dest to src (for undirected)
    newNode = createNode(src, weight);
    newNode->next = graph->array[dest];
    graph->array[dest] = newNode;
}

// Add directed edge
void addDirectedEdge(AdjList* graph, int src, int dest, int weight) {
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->array[src];
    graph->array[src] = newNode;
}

// Print graph
void printGraph(AdjList* graph) {
    printf("Adjacency List:\n");
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->array[v];
        printf("%d: ", v);
        while (temp) {
            printf("-> %d(%d) ", temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Visual:
// 0: -> 1(5) -> 3(2)
// 1: -> 0(5) -> 2(3) -> 3(1)
// 2: -> 1(3) -> 4(4)
// 3: -> 0(2) -> 1(1) -> 4(6)
// 4: -> 2(4) -> 3(6)
```

**Advantages:**
- Space: O(V + E)
- Efficient for sparse graphs
- Easy to iterate over neighbors

**Disadvantages:**
- Edge lookup: O(V) worst case
- More complex implementation

### 3. Edge List

**List of all edges** (src, dest, weight).

```c
typedef struct {
    int src;
    int dest;
    int weight;
} Edge;

typedef struct {
    Edge* edges;
    int numEdges;
    int numVertices;
} EdgeList;

EdgeList* createEdgeList(int vertices, int maxEdges) {
    EdgeList* graph = (EdgeList*)malloc(sizeof(EdgeList));
    graph->edges = (Edge*)malloc(maxEdges * sizeof(Edge));
    graph->numEdges = 0;
    graph->numVertices = vertices;
    return graph;
}

void addEdgeToList(EdgeList* graph, int src, int dest, int weight) {
    graph->edges[graph->numEdges].src = src;
    graph->edges[graph->numEdges].dest = dest;
    graph->edges[graph->numEdges].weight = weight;
    graph->numEdges++;
}

// Example:
// edges[0] = {0, 1, 5}
// edges[1] = {1, 2, 3}
// edges[2] = {1, 3, 1}
```

**Use cases:** Kruskal's MST, edge-centric algorithms

---

## Breadth-First Search (BFS)

### Concept
**BFS** explores graph level by level using a queue.

### Visual BFS Execution
```
Graph:
    0 --- 1 --- 3
    |     |     |
    2 --- 4 --- 5

BFS from 0:
Level 0: 0
Level 1: 1, 2
Level 2: 3, 4
Level 3: 5

Order: 0 → 1 → 2 → 3 → 4 → 5
```

### Implementation

```c
#include <stdbool.h>

#define MAX_VERTICES 100

// BFS using adjacency list
void BFS(AdjList* graph, int start) {
    bool visited[MAX_VERTICES] = {false};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    // Mark start as visited and enqueue
    visited[start] = true;
    queue[rear++] = start;

    printf("BFS Traversal: ");

    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);

        // Visit all adjacent vertices
        Node* temp = graph->array[current];
        while (temp) {
            int adjacent = temp->vertex;
            if (!visited[adjacent]) {
                visited[adjacent] = true;
                queue[rear++] = adjacent;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

// BFS with level tracking
void BFSLevel(AdjList* graph, int start) {
    bool visited[MAX_VERTICES] = {false};
    int queue[MAX_VERTICES];
    int level[MAX_VERTICES] = {0};
    int front = 0, rear = 0;

    visited[start] = true;
    queue[rear++] = start;
    level[start] = 0;

    while (front < rear) {
        int current = queue[front++];
        printf("Vertex %d at level %d\n", current, level[current]);

        Node* temp = graph->array[current];
        while (temp) {
            int adjacent = temp->vertex;
            if (!visited[adjacent]) {
                visited[adjacent] = true;
                queue[rear++] = adjacent;
                level[adjacent] = level[current] + 1;
            }
            temp = temp->next;
        }
    }
}

// Shortest path in unweighted graph
int shortestPath(AdjList* graph, int start, int end) {
    bool visited[MAX_VERTICES] = {false};
    int dist[MAX_VERTICES];
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    for (int i = 0; i < graph->numVertices; i++) {
        dist[i] = -1;
    }

    visited[start] = true;
    dist[start] = 0;
    queue[rear++] = start;

    while (front < rear) {
        int current = queue[front++];

        if (current == end) {
            return dist[end];
        }

        Node* temp = graph->array[current];
        while (temp) {
            int adjacent = temp->vertex;
            if (!visited[adjacent]) {
                visited[adjacent] = true;
                dist[adjacent] = dist[current] + 1;
                queue[rear++] = adjacent;
            }
            temp = temp->next;
        }
    }

    return -1;  // No path exists
}
```

**Time Complexity:** O(V + E)
**Space Complexity:** O(V)

**Applications:**
- Shortest path in unweighted graph
- Level order traversal
- Finding connected components
- Web crawling

---

## Depth-First Search (DFS)

### Concept
**DFS** explores graph by going as deep as possible before backtracking.

### Visual DFS Execution
```
Graph:
    0 --- 1 --- 3
    |     |     |
    2 --- 4 --- 5

DFS from 0:
0 → 1 → 3 → 5 → 4 → 2

(Goes deep into 1, then 3, then 5, backtracks)
```

### Implementation

```c
// DFS recursive
void DFSUtil(AdjList* graph, int vertex, bool visited[]) {
    visited[vertex] = true;
    printf("%d ", vertex);

    Node* temp = graph->array[vertex];
    while (temp) {
        int adjacent = temp->vertex;
        if (!visited[adjacent]) {
            DFSUtil(graph, adjacent, visited);
        }
        temp = temp->next;
    }
}

void DFS(AdjList* graph, int start) {
    bool visited[MAX_VERTICES] = {false};
    printf("DFS Traversal: ");
    DFSUtil(graph, start, visited);
    printf("\n");
}

// DFS iterative using stack
void DFSIterative(AdjList* graph, int start) {
    bool visited[MAX_VERTICES] = {false};
    int stack[MAX_VERTICES];
    int top = -1;

    stack[++top] = start;

    printf("DFS Iterative: ");

    while (top >= 0) {
        int current = stack[top--];

        if (!visited[current]) {
            visited[current] = true;
            printf("%d ", current);

            // Push all adjacent vertices
            Node* temp = graph->array[current];
            while (temp) {
                if (!visited[temp->vertex]) {
                    stack[++top] = temp->vertex;
                }
                temp = temp->next;
            }
        }
    }
    printf("\n");
}

// Detect cycle in undirected graph using DFS
bool hasCycleUtil(AdjList* graph, int vertex, bool visited[], int parent) {
    visited[vertex] = true;

    Node* temp = graph->array[vertex];
    while (temp) {
        int adjacent = temp->vertex;

        if (!visited[adjacent]) {
            if (hasCycleUtil(graph, adjacent, visited, vertex)) {
                return true;
            }
        } else if (adjacent != parent) {
            return true;  // Back edge found
        }

        temp = temp->next;
    }

    return false;
}

bool hasCycle(AdjList* graph) {
    bool visited[MAX_VERTICES] = {false};

    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            if (hasCycleUtil(graph, i, visited, -1)) {
                return true;
            }
        }
    }

    return false;
}

// Topological sort (for DAG) using DFS
void topologicalSortUtil(AdjList* graph, int vertex, bool visited[], int stack[], int* top) {
    visited[vertex] = true;

    Node* temp = graph->array[vertex];
    while (temp) {
        if (!visited[temp->vertex]) {
            topologicalSortUtil(graph, temp->vertex, visited, stack, top);
        }
        temp = temp->next;
    }

    stack[++(*top)] = vertex;
}

void topologicalSort(AdjList* graph) {
    bool visited[MAX_VERTICES] = {false};
    int stack[MAX_VERTICES];
    int top = -1;

    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            topologicalSortUtil(graph, i, visited, stack, &top);
        }
    }

    printf("Topological Sort: ");
    while (top >= 0) {
        printf("%d ", stack[top--]);
    }
    printf("\n");
}
```

**Time Complexity:** O(V + E)
**Space Complexity:** O(V)

**Applications:**
- Cycle detection
- Topological sorting
- Finding connected components
- Solving mazes
- Path finding

---

## Shortest Path Algorithms

### 1. Dijkstra's Algorithm

**Finds shortest path** from source to all vertices (non-negative weights).

```c
#include <limits.h>

#define INF INT_MAX

// Find vertex with minimum distance
int minDistance(int dist[], bool visited[], int V) {
    int min = INF, minIndex = -1;

    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Dijkstra's algorithm - O(V²) with array, O(E log V) with heap
void dijkstra(int graph[][V], int src, int V) {
    int dist[V];
    bool visited[V];

    // Initialize distances
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        visited[u] = true;

        // Update distances of adjacent vertices
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] &&
                dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print distances
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }
}

// Example:
//     0
//    /|\
//   4 2 7
//  /  |  \
// 1   3   4
//  \  |  /
//   5 3 8
//    \|/
//     2
//
// Shortest paths from 0:
// 0→0: 0
// 0→1: 4
// 0→2: 12
// 0→3: 19
// 0→4: 21
```

### 2. Bellman-Ford Algorithm

**Finds shortest path** with negative weights, detects negative cycles.

```c
// Bellman-Ford - O(VE)
void bellmanFord(EdgeList* graph, int src) {
    int V = graph->numVertices;
    int dist[V];

    // Initialize distances
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
    }
    dist[src] = 0;

    // Relax all edges V-1 times
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < graph->numEdges; j++) {
            int u = graph->edges[j].src;
            int v = graph->edges[j].dest;
            int weight = graph->edges[j].weight;

            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Check for negative cycles
    for (int j = 0; j < graph->numEdges; j++) {
        int u = graph->edges[j].src;
        int v = graph->edges[j].dest;
        int weight = graph->edges[j].weight;

        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            printf("Graph contains negative cycle\n");
            return;
        }
    }

    // Print distances
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t%d\n", i, dist[i] == INF ? -1 : dist[i]);
    }
}
```

### 3. Floyd-Warshall Algorithm

**All pairs shortest path** - O(V³)

```c
void floydWarshall(int graph[][V], int V) {
    int dist[V][V];

    // Initialize distance matrix
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // Floyd-Warshall algorithm
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print solution
    printf("Shortest distances between every pair:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}
```

---

## Minimum Spanning Tree

### 1. Prim's Algorithm

```c
// Prim's MST - O(V²)
void primMST(int graph[][V], int V) {
    int parent[V];
    int key[V];
    bool inMST[V];

    for (int i = 0; i < V; i++) {
        key[i] = INF;
        inMST[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(key, inMST, V);
        inMST[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("Edge\tWeight\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d\t%d\n", parent[i], i, graph[i][parent[i]]);
    }
}
```

### 2. Kruskal's Algorithm

```c
// Find set of element (Union-Find)
int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

// Union of two sets
void unionSets(int parent[], int x, int y) {
    parent[x] = y;
}

// Compare function for qsort
int compareEdges(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    return e1->weight - e2->weight;
}

// Kruskal's MST - O(E log E)
void kruskalMST(EdgeList* graph) {
    int V = graph->numVertices;
    Edge result[V];
    int e = 0;
    int i = 0;

    // Sort edges by weight
    qsort(graph->edges, graph->numEdges, sizeof(Edge), compareEdges);

    int parent[V];
    for (int v = 0; v < V; v++) {
        parent[v] = -1;
    }

    while (e < V - 1 && i < graph->numEdges) {
        Edge nextEdge = graph->edges[i++];

        int x = find(parent, nextEdge.src);
        int y = find(parent, nextEdge.dest);

        if (x != y) {
            result[e++] = nextEdge;
            unionSets(parent, x, y);
        }
    }

    printf("Edges in MST:\n");
    for (i = 0; i < e; i++) {
        printf("%d - %d: %d\n", result[i].src, result[i].dest, result[i].weight);
    }
}
```

---

## Practice Problems

### Problem 1: Check if Graph is Bipartite
```c
bool isBipartite(AdjList* graph, int src) {
    int color[MAX_VERTICES];
    for (int i = 0; i < graph->numVertices; i++) {
        color[i] = -1;
    }

    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    color[src] = 1;
    queue[rear++] = src;

    while (front < rear) {
        int u = queue[front++];

        Node* temp = graph->array[u];
        while (temp) {
            int v = temp->vertex;

            if (color[v] == -1) {
                color[v] = 1 - color[u];
                queue[rear++] = v;
            } else if (color[v] == color[u]) {
                return false;
            }

            temp = temp->next;
        }
    }

    return true;
}
```

---

## Summary

### Algorithm Comparison

| Algorithm | Problem | Complexity | Notes |
|-----------|---------|------------|-------|
| BFS | Shortest path (unweighted) | O(V + E) | Level-order |
| DFS | Traversal, cycle detection | O(V + E) | Recursive |
| Dijkstra | Shortest path (non-negative) | O(V² or E log V) | Greedy |
| Bellman-Ford | Shortest path (negative allowed) | O(VE) | DP |
| Floyd-Warshall | All pairs shortest path | O(V³) | DP |
| Prim | MST | O(V²) | Greedy |
| Kruskal | MST | O(E log E) | Union-Find |

**Master graphs - they model real-world networks and solve complex problems!**
