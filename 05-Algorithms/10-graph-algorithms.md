# Graph Algorithms

## Table of Contents
1. [Introduction to Graphs](#introduction)
2. [Graph Representations](#graph-representations)
3. [Graph Traversal](#graph-traversal)
4. [Shortest Path Algorithms](#shortest-path)
5. [Minimum Spanning Tree](#minimum-spanning-tree)
6. [Practice Problems](#practice-problems)

---

## Introduction to Graphs

A **graph** is a non-linear data structure consisting of vertices (nodes) and edges connecting them.

### Graph Terminology

- **Vertex (Node)**: Fundamental unit
- **Edge**: Connection between vertices
- **Degree**: Number of edges connected to vertex
- **Path**: Sequence of vertices connected by edges
- **Cycle**: Path that starts and ends at same vertex
- **Connected Graph**: Path exists between every pair of vertices
- **Weighted Graph**: Edges have weights/costs

### Types of Graphs

```
Undirected Graph:      Directed Graph (Digraph):
    A --- B                A → B
    |     |                ↓   ↓
    C --- D                C ← D

Weighted Graph:        Cyclic vs Acyclic:
    A --5-- B             A → B → C        A → B → C
    |3      |2            ↑       ↓        |       |
    C --4-- D             D ← --- E        D       E
```

---

## Graph Representations

### 1. Adjacency Matrix

2D array where matrix[i][j] = 1 if edge exists from i to j.

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

typedef struct {
    int vertices;
    int matrix[MAX_VERTICES][MAX_VERTICES];
} GraphMatrix;

// Create graph using adjacency matrix
GraphMatrix* createGraphMatrix(int vertices) {
    GraphMatrix* graph = (GraphMatrix*)malloc(sizeof(GraphMatrix));
    graph->vertices = vertices;

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->matrix[i][j] = 0;
        }
    }

    return graph;
}

// Add edge (undirected)
void addEdgeMatrix(GraphMatrix* graph, int src, int dest) {
    graph->matrix[src][dest] = 1;
    graph->matrix[dest][src] = 1;  // For undirected
}

// Print adjacency matrix
void printGraphMatrix(GraphMatrix* graph) {
    printf("Adjacency Matrix:\n");
    printf("   ");
    for (int i = 0; i < graph->vertices; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < graph->vertices; i++) {
        printf("%d: ", i);
        for (int j = 0; j < graph->vertices; j++) {
            printf("%d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
}
```

**Pros**: Fast edge lookup O(1), simple implementation
**Cons**: Space O(V²), iterating neighbors O(V)

---

### 2. Adjacency List

Array of lists, each list contains neighbors of a vertex.

```c
#include <stdio.h>
#include <stdlib.h>

// Node in adjacency list
typedef struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
} AdjListNode;

// Adjacency list
typedef struct AdjList {
    AdjListNode* head;
} AdjList;

// Graph structure
typedef struct Graph {
    int vertices;
    AdjList* array;
} Graph;

// Create new adjacency list node
AdjListNode* newAdjListNode(int dest, int weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Create graph
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->array = (AdjList*)malloc(vertices * sizeof(AdjList));

    for (int i = 0; i < vertices; i++) {
        graph->array[i].head = NULL;
    }

    return graph;
}

// Add edge (directed)
void addEdge(Graph* graph, int src, int dest, int weight) {
    // Add edge from src to dest
    AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // For undirected graph, add reverse edge
    // newNode = newAdjListNode(src, weight);
    // newNode->next = graph->array[dest].head;
    // graph->array[dest].head = newNode;
}

// Print adjacency list
void printGraph(Graph* graph) {
    printf("Adjacency List:\n");
    for (int v = 0; v < graph->vertices; v++) {
        AdjListNode* temp = graph->array[v].head;
        printf("Vertex %d: ", v);
        while (temp) {
            printf("-> %d(w:%d) ", temp->dest, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}
```

**Pros**: Space O(V+E), efficient iteration over neighbors
**Cons**: Edge lookup O(V), more complex

---

## Graph Traversal

### 1. Breadth-First Search (BFS)

Explores level by level using queue.

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Queue for BFS
typedef struct Queue {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

bool isEmpty(Queue* q) {
    return q->rear == -1;
}

void enqueue(Queue* q, int value) {
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue* q) {
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

// BFS traversal
void BFS(Graph* graph, int startVertex) {
    bool* visited = (bool*)calloc(graph->vertices, sizeof(bool));
    Queue* queue = createQueue();

    visited[startVertex] = true;
    enqueue(queue, startVertex);

    printf("BFS Traversal starting from vertex %d:\n", startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        // Visit all adjacent vertices
        AdjListNode* temp = graph->array[currentVertex].head;
        while (temp) {
            int adjVertex = temp->dest;

            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                enqueue(queue, adjVertex);
            }

            temp = temp->next;
        }
    }

    printf("\n");
    free(visited);
    free(queue);
}

// BFS for shortest path
void BFSShortestPath(Graph* graph, int start, int end) {
    bool* visited = (bool*)calloc(graph->vertices, sizeof(bool));
    int* distance = (int*)malloc(graph->vertices * sizeof(int));
    int* parent = (int*)malloc(graph->vertices * sizeof(int));

    for (int i = 0; i < graph->vertices; i++) {
        distance[i] = -1;
        parent[i] = -1;
    }

    Queue* queue = createQueue();

    visited[start] = true;
    distance[start] = 0;
    enqueue(queue, start);

    while (!isEmpty(queue)) {
        int current = dequeue(queue);

        AdjListNode* temp = graph->array[current].head;
        while (temp) {
            int adj = temp->dest;

            if (!visited[adj]) {
                visited[adj] = true;
                distance[adj] = distance[current] + 1;
                parent[adj] = current;
                enqueue(queue, adj);
            }

            temp = temp->next;
        }
    }

    if (distance[end] == -1) {
        printf("No path from %d to %d\n", start, end);
    } else {
        printf("Shortest path from %d to %d (distance=%d):\n",
               start, end, distance[end]);

        // Reconstruct path
        int path[MAX_VERTICES];
        int pathLen = 0;
        int current = end;

        while (current != -1) {
            path[pathLen++] = current;
            current = parent[current];
        }

        for (int i = pathLen - 1; i >= 0; i--) {
            printf("%d", path[i]);
            if (i > 0) printf(" -> ");
        }
        printf("\n");
    }

    free(visited);
    free(distance);
    free(parent);
    free(queue);
}
```

**Applications**: Shortest path in unweighted graph, level-order traversal
**Time Complexity**: O(V + E)
**Space Complexity**: O(V)

---

### 2. Depth-First Search (DFS)

Explores as far as possible before backtracking.

```c
#include <stdio.h>
#include <stdbool.h>

// DFS recursive
void DFSUtil(Graph* graph, int vertex, bool* visited) {
    visited[vertex] = true;
    printf("%d ", vertex);

    AdjListNode* temp = graph->array[vertex].head;
    while (temp) {
        int adjVertex = temp->dest;

        if (!visited[adjVertex]) {
            DFSUtil(graph, adjVertex, visited);
        }

        temp = temp->next;
    }
}

void DFS(Graph* graph, int startVertex) {
    bool* visited = (bool*)calloc(graph->vertices, sizeof(bool));

    printf("DFS Traversal starting from vertex %d:\n", startVertex);
    DFSUtil(graph, startVertex, visited);
    printf("\n");

    free(visited);
}

// DFS iterative (using stack)
void DFSIterative(Graph* graph, int startVertex) {
    bool* visited = (bool*)calloc(graph->vertices, sizeof(bool));
    int stack[MAX_VERTICES];
    int top = -1;

    stack[++top] = startVertex;

    printf("DFS Iterative starting from vertex %d:\n", startVertex);

    while (top >= 0) {
        int vertex = stack[top--];

        if (!visited[vertex]) {
            printf("%d ", vertex);
            visited[vertex] = true;
        }

        AdjListNode* temp = graph->array[vertex].head;
        while (temp) {
            int adjVertex = temp->dest;

            if (!visited[adjVertex]) {
                stack[++top] = adjVertex;
            }

            temp = temp->next;
        }
    }

    printf("\n");
    free(visited);
}

// Detect cycle using DFS
bool isCyclicUtil(Graph* graph, int v, bool* visited, bool* recStack) {
    visited[v] = true;
    recStack[v] = true;

    AdjListNode* temp = graph->array[v].head;
    while (temp) {
        int adj = temp->dest;

        if (!visited[adj]) {
            if (isCyclicUtil(graph, adj, visited, recStack)) {
                return true;
            }
        } else if (recStack[adj]) {
            return true;
        }

        temp = temp->next;
    }

    recStack[v] = false;
    return false;
}

bool isCyclic(Graph* graph) {
    bool* visited = (bool*)calloc(graph->vertices, sizeof(bool));
    bool* recStack = (bool*)calloc(graph->vertices, sizeof(bool));

    for (int i = 0; i < graph->vertices; i++) {
        if (!visited[i]) {
            if (isCyclicUtil(graph, i, visited, recStack)) {
                free(visited);
                free(recStack);
                return true;
            }
        }
    }

    free(visited);
    free(recStack);
    return false;
}
```

**Applications**: Cycle detection, topological sort, pathfinding
**Time Complexity**: O(V + E)
**Space Complexity**: O(V)

---

## Shortest Path Algorithms

### 1. Dijkstra's Algorithm

Finds shortest paths from source to all vertices (non-negative weights).

```c
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

// Find vertex with minimum distance
int minDistance(int dist[], bool sptSet[], int vertices) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < vertices; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Print shortest path
void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%d ", j);
        return;
    }

    printPath(parent, parent[j]);
    printf("%d ", j);
}

// Dijkstra's algorithm
void dijkstra(Graph* graph, int src) {
    int vertices = graph->vertices;
    int* dist = (int*)malloc(vertices * sizeof(int));
    bool* sptSet = (bool*)calloc(vertices, sizeof(bool));
    int* parent = (int*)malloc(vertices * sizeof(int));

    // Initialize
    for (int i = 0; i < vertices; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < vertices - 1; count++) {
        int u = minDistance(dist, sptSet, vertices);
        sptSet[u] = true;

        // Update dist values of adjacent vertices
        AdjListNode* temp = graph->array[u].head;
        while (temp) {
            int v = temp->dest;
            int weight = temp->weight;

            if (!sptSet[v] && dist[u] != INT_MAX &&
                dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }

            temp = temp->next;
        }
    }

    // Print solution
    printf("Dijkstra's Shortest Paths from vertex %d:\n", src);
    printf("Vertex\t Distance\tPath\n");

    for (int i = 0; i < vertices; i++) {
        printf("%d\t %d\t\t", i, dist[i]);
        printPath(parent, i);
        printf("\n");
    }

    free(dist);
    free(sptSet);
    free(parent);
}
```

**Visual Example**:
```
Graph:        0 --4-- 1
              |  \    |
              8   2   11
              |    \  |
              7 --1-- 2
              |       |
              7       6
              |       |
              8 --2-- 6

Dijkstra from 0:
Vertex  Distance  Path
0       0         0
1       4         0 1
2       2         0 2
7       8         0 7
8       10        0 7 8
6       8         0 2 6
```

**Time Complexity**: O(V²) or O(E log V) with min-heap
**Space Complexity**: O(V)

---

### 2. Bellman-Ford Algorithm

Handles negative weights, detects negative cycles.

```c
#include <stdio.h>
#include <limits.h>

// Edge structure
typedef struct Edge {
    int src, dest, weight;
} Edge;

// Graph with edge list
typedef struct GraphEdges {
    int V, E;
    Edge* edges;
} GraphEdges;

// Bellman-Ford algorithm
void bellmanFord(GraphEdges* graph, int src) {
    int V = graph->V;
    int E = graph->E;
    int* dist = (int*)malloc(V * sizeof(int));

    // Initialize distances
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    // Relax all edges V-1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edges[j].src;
            int v = graph->edges[j].dest;
            int weight = graph->edges[j].weight;

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Check for negative-weight cycles
    bool hasNegativeCycle = false;
    for (int j = 0; j < E; j++) {
        int u = graph->edges[j].src;
        int v = graph->edges[j].dest;
        int weight = graph->edges[j].weight;

        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            hasNegativeCycle = true;
            printf("Graph contains negative weight cycle\n");
            break;
        }
    }

    if (!hasNegativeCycle) {
        printf("Bellman-Ford Shortest Paths from vertex %d:\n", src);
        printf("Vertex\t Distance\n");
        for (int i = 0; i < V; i++) {
            printf("%d\t %d\n", i, dist[i]);
        }
    }

    free(dist);
}
```

**Time Complexity**: O(V × E)
**Space Complexity**: O(V)

---

### 3. Floyd-Warshall Algorithm

All-pairs shortest paths.

```c
#include <stdio.h>
#include <limits.h>

#define INF 99999

// Floyd-Warshall algorithm
void floydWarshall(int graph[][MAX_VERTICES], int vertices) {
    int dist[MAX_VERTICES][MAX_VERTICES];

    // Initialize
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (graph[i][j] == 0 && i != j) {
                dist[i][j] = INF;
            } else {
                dist[i][j] = graph[i][j];
            }
        }
    }

    // Consider all vertices as intermediate
    for (int k = 0; k < vertices; k++) {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print solution
    printf("Floyd-Warshall All-Pairs Shortest Paths:\n");
    printf("     ");
    for (int i = 0; i < vertices; i++) {
        printf("%4d ", i);
    }
    printf("\n");

    for (int i = 0; i < vertices; i++) {
        printf("%4d ", i);
        for (int j = 0; j < vertices; j++) {
            if (dist[i][j] == INF) {
                printf(" INF ");
            } else {
                printf("%4d ", dist[i][j]);
            }
        }
        printf("\n");
    }
}
```

**Time Complexity**: O(V³)
**Space Complexity**: O(V²)

---

## Minimum Spanning Tree

### 1. Kruskal's Algorithm

Greedy algorithm using union-find.

```c
#include <stdio.h>
#include <stdlib.h>

// Disjoint Set Union (Union-Find)
typedef struct Subset {
    int parent;
    int rank;
} Subset;

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void unionSets(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Compare edges by weight
int compareEdges(const void* a, const void* b) {
    Edge* edge1 = (Edge*)a;
    Edge* edge2 = (Edge*)b;
    return edge1->weight - edge2->weight;
}

// Kruskal's MST algorithm
void kruskalMST(GraphEdges* graph) {
    int V = graph->V;
    Edge result[V];
    int e = 0;
    int i = 0;

    // Sort edges by weight
    qsort(graph->edges, graph->E, sizeof(Edge), compareEdges);

    Subset* subsets = (Subset*)malloc(V * sizeof(Subset));

    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < graph->E) {
        Edge next_edge = graph->edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            unionSets(subsets, x, y);
        }
    }

    printf("Kruskal's Minimum Spanning Tree:\n");
    printf("Edge\t Weight\n");

    int totalWeight = 0;
    for (i = 0; i < e; i++) {
        printf("%d - %d\t %d\n", result[i].src, result[i].dest,
               result[i].weight);
        totalWeight += result[i].weight;
    }

    printf("Total weight: %d\n", totalWeight);

    free(subsets);
}
```

**Time Complexity**: O(E log E) or O(E log V)
**Space Complexity**: O(V)

---

### 2. Prim's Algorithm

Greedy algorithm growing MST from starting vertex.

```c
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

// Prim's MST algorithm
void primMST(Graph* graph) {
    int vertices = graph->vertices;
    int* parent = (int*)malloc(vertices * sizeof(int));
    int* key = (int*)malloc(vertices * sizeof(int));
    bool* mstSet = (bool*)calloc(vertices, sizeof(bool));

    // Initialize
    for (int i = 0; i < vertices; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;
    }

    key[0] = 0;

    for (int count = 0; count < vertices - 1; count++) {
        // Find minimum key vertex
        int min = INT_MAX, min_index;

        for (int v = 0; v < vertices; v++) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                min_index = v;
            }
        }

        int u = min_index;
        mstSet[u] = true;

        // Update key values
        AdjListNode* temp = graph->array[u].head;
        while (temp) {
            int v = temp->dest;
            int weight = temp->weight;

            if (!mstSet[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }

            temp = temp->next;
        }
    }

    printf("Prim's Minimum Spanning Tree:\n");
    printf("Edge\t Weight\n");

    int totalWeight = 0;
    for (int i = 1; i < vertices; i++) {
        printf("%d - %d\t %d\n", parent[i], i, key[i]);
        totalWeight += key[i];
    }

    printf("Total weight: %d\n", totalWeight);

    free(parent);
    free(key);
    free(mstSet);
}
```

**Time Complexity**: O(V²) or O(E log V) with min-heap
**Space Complexity**: O(V)

---

## Practice Problems

### Problem 1: Number of Islands
Count number of islands in 2D grid (connected components).

### Problem 2: Course Schedule
Check if courses can be finished given prerequisites (topological sort).

### Problem 3: Clone Graph
Create deep copy of undirected graph.

### Problem 4: Word Ladder
Find shortest transformation sequence from start to end word.

### Problem 5: Network Delay Time
Find time for signal to reach all nodes.

### Problem 6: Cheapest Flights Within K Stops
Find cheapest price with at most k stops.

### Problem 7: Critical Connections
Find bridges in network (Tarjan's algorithm).

### Problem 8: Alien Dictionary
Find order of characters in alien language (topological sort).

### Problem 9: Reconstruct Itinerary
Find valid itinerary from tickets (Eulerian path).

### Problem 10: Minimum Height Trees
Find roots of minimum height trees.

---

## Summary

### Algorithm Comparison

| Algorithm | Type | Time | Use Case |
|-----------|------|------|----------|
| BFS | Traversal | O(V+E) | Shortest path (unweighted) |
| DFS | Traversal | O(V+E) | Cycle detection, topological sort |
| Dijkstra | Shortest Path | O(V²) or O(E log V) | Non-negative weights |
| Bellman-Ford | Shortest Path | O(VE) | Negative weights |
| Floyd-Warshall | All-Pairs | O(V³) | Dense graphs |
| Kruskal | MST | O(E log E) | Sparse graphs |
| Prim | MST | O(V²) or O(E log V) | Dense graphs |

### Key Concepts
1. **Graph representation** affects performance
2. **Choose algorithm** based on problem constraints
3. **BFS for shortest path** in unweighted graphs
4. **DFS for connectivity** and cycles
5. **Dijkstra for weighted** shortest path
6. **MST for optimization** problems

### Common Patterns
- Connected components: DFS/BFS
- Shortest path: BFS (unweighted), Dijkstra (weighted)
- Cycle detection: DFS with recursion stack
- Topological sort: DFS or Kahn's algorithm
- Minimum spanning tree: Kruskal or Prim

---

**Congratulations!** You've completed the comprehensive algorithms guide!
