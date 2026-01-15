# C Programming - Comprehensive Coding Challenges

This file contains 25 comprehensive coding challenges that combine multiple concepts including data structures, algorithms, dynamic memory, file handling, and advanced programming techniques.

---

## Challenge 1: Student Management System
**Difficulty:** Medium
**Topics:** Structures, File Handling, Dynamic Memory, Menu-Driven Program

### Problem Statement
Create a complete student management system with the following features:
- Add student (name, roll number, marks in 5 subjects)
- Display all students
- Search student by roll number
- Calculate and display grade (average of marks)
- Update student information
- Delete student
- Save to file and load from file
- Sort students by roll number or marks

### Input Format
Menu-driven interface with options.

### Output Format
Formatted display of student information, operation confirmations.

### Constraints
- Maximum 1000 students
- Roll numbers are unique
- Marks: 0-100

### Features to Implement
1. Dynamic memory allocation for student array
2. Binary file operations for persistence
3. Search functionality
4. Sorting algorithms
5. Grade calculation with proper formatting

<details>
<summary>Hint</summary>
Define student structure with name, roll number, marks array, and average. Use dynamic array that grows as needed. Implement menu using switch case. Use fwrite/fread for binary file operations.
</details>

---

## Challenge 2: Text File Analyzer
**Difficulty:** Medium
**Topics:** File Handling, String Processing, Data Structures

### Problem Statement
Create a comprehensive text file analyzer that:
- Counts total words, lines, characters
- Finds most frequent word
- Counts unique words
- Displays word frequency distribution
- Finds longest word and sentence
- Counts vowels and consonants
- Displays statistics in formatted table

### Input Format
```
Filename
```

### Output Format
```
File Statistics:
Lines: [count]
Words: [count]
Characters: [count]
Unique words: [count]
Most frequent word: [word] ([count] times)
Longest word: [word] ([length] chars)
Vowels: [count]
Consonants: [count]

Word Frequency (top 10):
[word]: [count]
...
```

### Constraints
- File size up to 10 MB
- Handle punctuation properly

<details>
<summary>Hint</summary>
Use hash table or array to store word frequencies. Parse file line by line. Use string functions for processing. Handle edge cases like punctuation, case sensitivity.
</details>

---

## Challenge 3: Expression Evaluator
**Difficulty:** Hard
**Topics:** Stack, String Processing, Parsing

### Problem Statement
Build a complete expression evaluator that:
- Converts infix to postfix
- Evaluates postfix expressions
- Supports operators: +, -, *, /, ^, ()
- Handles multi-digit numbers
- Detects and reports syntax errors
- Shows step-by-step evaluation

### Input Format
```
Infix expression
```

### Output Format
```
Infix: [expression]
Postfix: [expression]
Step-by-step evaluation:
[steps]
Result: [value]
```

### Constraints
- Support operators with proper precedence
- Handle negative numbers
- Validate parentheses

### Example
```
Input: (3 + 5) * 2 - 8 / 4
Output:
Infix: (3 + 5) * 2 - 8 / 4
Postfix: 3 5 + 2 * 8 4 / -
Steps:
  Push 3
  Push 5
  Pop 5, 3: 3 + 5 = 8, Push 8
  Push 2
  Pop 2, 8: 8 * 2 = 16, Push 16
  Push 8
  Push 4
  Pop 4, 8: 8 / 4 = 2, Push 2
  Pop 2, 16: 16 - 2 = 14, Push 14
Result: 14
```

<details>
<summary>Hint</summary>
Use two stacks: one for operators, one for operands. Implement operator precedence function. Parse expression token by token. Handle edge cases like division by zero.
</details>

---

## Challenge 4: Custom Memory Allocator
**Difficulty:** Hard
**Topics:** Dynamic Memory, Pointers, Memory Management

### Problem Statement
Implement a custom memory allocator with:
- my_malloc(size) - allocate memory block
- my_free(ptr) - free memory block
- my_realloc(ptr, new_size) - resize allocation
- Memory pool management
- Fragmentation handling
- Memory leak detection
- Usage statistics

### Input Format
Series of allocation/deallocation commands.

### Output Format
```
Memory operations log
Current memory usage
Fragmentation report
Memory leaks (if any)
```

### Features
1. Maintain free list
2. Coalesce adjacent free blocks
3. Track all allocations
4. Report memory leaks
5. Display memory map

<details>
<summary>Hint</summary>
Use a large static array as memory pool. Maintain linked list of free blocks with size information. Implement first-fit or best-fit allocation strategy. Keep track of allocated blocks.
</details>

---

## Challenge 5: Sparse Matrix Operations
**Difficulty:** Medium
**Topics:** Arrays, Structures, Algorithms

### Problem Statement
Implement sparse matrix representation and operations:
- Create sparse matrix from 2D array
- Add two sparse matrices
- Multiply two sparse matrices
- Transpose sparse matrix
- Display in both formats (sparse and normal)
- Calculate space savings

### Input Format
```
Rows Columns
Matrix elements (mostly zeros)
```

### Output Format
```
Original matrix
Sparse representation: (row, col, value) triplets
After operation: result
Space saved: [percentage]
```

### Constraints
- At least 70% zeros for meaningful sparse representation
- Support up to 1000x1000 matrices

<details>
<summary>Hint</summary>
Use array of structures to store (row, col, value) triplets. Only store non-zero elements. For multiplication, use hash table for efficient lookup. Calculate space as: (non-zeros * 3 * 4) vs (rows * cols * 4) bytes.
</details>

---

## Challenge 6: Mini Database System
**Difficulty:** Hard
**Topics:** File Handling, B-Trees/Indexing, Structures, Strings

### Problem Statement
Create a simple database system supporting:
- CREATE TABLE (define schema)
- INSERT record
- SELECT with WHERE conditions
- UPDATE records
- DELETE records
- CREATE INDEX for fast search
- Save/load database from file

### Input Format
SQL-like commands:
```
CREATE TABLE students (id INT, name STRING, age INT)
INSERT INTO students VALUES (1, "John", 20)
SELECT * FROM students WHERE age > 18
UPDATE students SET age = 21 WHERE id = 1
DELETE FROM students WHERE id = 2
```

### Output Format
Query results in tabular format, operation confirmations.

### Constraints
- Maximum 10 tables
- Maximum 100 records per table
- Simple WHERE conditions (field = value, field > value)

<details>
<summary>Hint</summary>
Parse commands using string functions. Store schema in structure array. Store data in linked list or dynamic array. Implement index using hash table or BST for fast lookups.
</details>

---

## Challenge 7: Multi-threaded Task Scheduler
**Difficulty:** Hard
**Topics:** Structures, Priority Queue, Scheduling Algorithms

### Problem Statement
Simulate a task scheduler with:
- Add tasks with priority and execution time
- Schedule using different algorithms (FCFS, SJF, Priority, Round Robin)
- Calculate waiting time, turnaround time
- Display Gantt chart
- Compare algorithm performance

### Input Format
```
Number of tasks
For each task: arrival_time, burst_time, priority
Scheduling algorithm choice
```

### Output Format
```
Gantt Chart: [visual representation]
Task completion order
Average waiting time
Average turnaround time
CPU utilization
```

### Algorithms to Implement
1. First Come First Serve (FCFS)
2. Shortest Job First (SJF)
3. Priority Scheduling
4. Round Robin

<details>
<summary>Hint</summary>
Define task structure with all timing information. Use priority queue for priority scheduling. For Round Robin, use queue with time quantum. Calculate metrics: waiting_time = turnaround_time - burst_time.
</details>

---

## Challenge 8: Graph Algorithms Toolkit
**Difficulty:** Hard
**Topics:** Graphs, Algorithms, Multiple Data Structures

### Problem Statement
Comprehensive graph toolkit with:
- Graph creation (directed/undirected, weighted/unweighted)
- BFS and DFS traversal
- Shortest path (Dijkstra, Bellman-Ford)
- Minimum Spanning Tree (Prim's, Kruskal's)
- Cycle detection
- Topological sort (for DAG)
- Connected components
- Visualization in adjacency matrix/list

### Input Format
```
Operation choice
Graph specification (vertices, edges)
Operation-specific inputs
```

### Output Format
Results based on operation, visual representation of graphs.

### Features
- Support both directed and undirected graphs
- Handle negative weights (for Bellman-Ford)
- Detect negative cycles
- Display step-by-step algorithm execution

<details>
<summary>Hint</summary>
Use adjacency list for sparse graphs, matrix for dense graphs. Implement Union-Find for Kruskal's. Use priority queue for Dijkstra. For topological sort, use DFS with recursion stack.
</details>

---

## Challenge 9: Huffman File Compressor
**Difficulty:** Hard
**Topics:** Trees, File Handling, Bit Manipulation

### Problem Statement
Build a file compression tool using Huffman coding:
- Analyze file to build frequency table
- Build Huffman tree
- Generate codes
- Compress file using codes
- Decompress file
- Display compression ratio
- Save tree structure for decompression

### Input Format
```
Operation: COMPRESS/DECOMPRESS
Input filename
Output filename
```

### Output Format
```
Original size: [bytes]
Compressed size: [bytes]
Compression ratio: [percentage]
Huffman codes: [character: code pairs]
```

### Constraints
- Handle binary and text files
- Preserve original file perfectly on decompression

<details>
<summary>Hint</summary>
Build min-heap of character frequencies. Construct Huffman tree. Serialize tree structure to compressed file header. Read file bit-by-bit for decompression. Use bit manipulation for packing/unpacking bits.
</details>

---

## Challenge 10: LRU Cache Implementation
**Difficulty:** Hard
**Topics:** Hash Table, Doubly Linked List, Caching

### Problem Statement
Implement Least Recently Used (LRU) cache with:
- get(key) - O(1) retrieval
- put(key, value) - O(1) insertion
- Fixed capacity
- Evict least recently used when full
- Display cache state
- Track hit/miss statistics

### Input Format
```
Cache capacity
Operations: GET key, PUT key value
```

### Output Format
```
Operation result
Cache state after each operation
Statistics: hits, misses, hit ratio
```

### Constraints
- O(1) time complexity for both operations
- 1 ≤ capacity ≤ 10000

<details>
<summary>Hint</summary>
Use hash table for O(1) lookup and doubly linked list for O(1) insertion/deletion. Hash table stores key → node mapping. DLL maintains order (most recent at head). On access, move node to head.
</details>

---

## Challenge 11: Tic-Tac-Toe with AI
**Difficulty:** Medium
**Topics:** Game Theory, Minimax Algorithm, Recursion

### Problem Statement
Create Tic-Tac-Toe game with:
- Human vs Human mode
- Human vs AI mode
- AI vs AI mode
- AI using Minimax algorithm (unbeatable)
- Display board after each move
- Detect win/draw conditions
- Show optimal move suggestions

### Input Format
```
Game mode
Player moves (row col)
```

### Output Format
```
Board display
Move validation
Game result
Move suggestion (if enabled)
```

### Features
1. Minimax algorithm with alpha-beta pruning
2. Move validation
3. Undo functionality
4. Game statistics

<details>
<summary>Hint</summary>
Implement minimax recursively: evaluate all possible moves, choose maximum for AI, minimum for opponent. Base cases: win (+10), loss (-10), draw (0). Alpha-beta pruning for optimization.
</details>

---

## Challenge 12: Calculator with History
**Difficulty:** Medium
**Topics:** Stack, Linked List, File Handling, String Processing

### Problem Statement
Scientific calculator with:
- Basic operations (+, -, *, /, %)
- Advanced (power, sqrt, log, sin, cos, tan)
- Expression evaluation
- Variable storage (x = 5)
- History of calculations
- Save/load history
- Multiple number systems (binary, octal, hex, decimal)

### Input Format
```
Expression or command
ANS for previous result
Variables in expressions
```

### Output Format
```
Result
Operation history
Variable values
```

### Features
- Support parentheses
- Handle errors gracefully
- Persistent history across sessions

<details>
<summary>Hint</summary>
Use stack for expression evaluation. Store history in linked list. Use map/hash table for variables. For number system conversion, implement conversion functions. Use math.h for scientific functions.
</details>

---

## Challenge 13: Airline Reservation System
**Difficulty:** Hard
**Topics:** Structures, Multiple Data Structures, File Handling

### Problem Statement
Complete airline reservation system:
- Add flights (number, source, destination, seats, price)
- Book ticket (passenger details, seat selection)
- Cancel reservation
- Display available flights
- Search flights by route
- Generate ticket
- Maintain waiting list
- Save/load data from files

### Input Format
Menu-driven interface with all operations.

### Output Format
```
Flight details
Booking confirmation
Ticket printout
Available seats visualization
```

### Data to Manage
1. Flights (graph of routes)
2. Bookings (hash table for fast lookup)
3. Passengers (linked list)
4. Waiting list (queue)

<details>
<summary>Hint</summary>
Use graph for flight network. Hash table for quick booking lookup. Queue for waiting list. Structure for flight with seat array. Use file I/O for data persistence.
</details>

---

## Challenge 14: Spell Checker with Suggestions
**Difficulty:** Hard
**Topics:** Tries, String Algorithms, Edit Distance

### Problem Statement
Spell checker that:
- Build dictionary from word file
- Check spelling of words in document
- Suggest corrections using edit distance
- Handle common typos
- Add words to dictionary
- Generate statistics (misspelled word count)

### Input Format
```
Dictionary file
Document to check
```

### Output Format
```
Misspelled words: [word] (suggestions: [word1, word2, ...])
Total errors: [count]
Accuracy: [percentage]
```

### Features
1. Trie for efficient dictionary storage
2. Edit distance (Levenshtein) for suggestions
3. Common typo patterns (swapped letters, etc.)

<details>
<summary>Hint</summary>
Build Trie from dictionary. For each word, search in Trie. If not found, calculate edit distance with all words (optimize using Trie traversal with bounded distance). Suggest top 5 closest matches.
</details>

---

## Challenge 15: JSON Parser
**Difficulty:** Hard
**Topics:** Recursive Descent Parsing, Trees, Strings

### Problem Statement
Simple JSON parser that:
- Parse JSON string to internal structure
- Support objects, arrays, strings, numbers, booleans, null
- Pretty print JSON with indentation
- Query values using path (e.g., "user.name")
- Modify values
- Convert back to JSON string
- Validate JSON syntax

### Input Format
```
JSON string
Operations: PARSE, QUERY path, SET path value, DISPLAY
```

### Output Format
```
Parsed structure
Query results
Formatted JSON output
Validation errors (if any)
```

### Example
```
Input: {"name": "John", "age": 30, "hobbies": ["reading", "coding"]}
QUERY name → "John"
QUERY hobbies.1 → "coding"
SET age 31
```

<details>
<summary>Hint</summary>
Use recursive descent parser. Define structures for different JSON types. Build tree during parsing. For queries, tokenize path and traverse tree. Handle escaping in strings.
</details>

---

## Challenge 16: Directory Tree Display
**Difficulty:** Medium
**Topics:** Trees, Recursion, File System

### Problem Statement
Display directory structure as tree with:
- Recursive directory traversal
- File/folder size calculation
- Filter by extension
- Sort by name/size/date
- Display permissions
- Calculate total size
- Export to text file

### Input Format
```
Directory path
Display options (show hidden, sort by, filter)
```

### Output Format
```
└── folder1
    ├── file1.txt (1.2 KB)
    ├── file2.pdf (340 KB)
    └── subfolder
        └── file3.c (2.1 KB)
Total: 343.3 KB, 3 files, 2 folders
```

### Features
- Visual tree with box-drawing characters
- Color coding by file type (if terminal supports)
- Depth limiting

<details>
<summary>Hint</summary>
Use recursion for directory traversal. On Windows: use dirent.h or Windows API. Use DFS to traverse. Track depth for indentation. Calculate sizes recursively.
</details>

---

## Challenge 17: Bank Management System
**Difficulty:** Medium
**Topics:** Structures, File Handling, Linked List, Validation

### Problem Statement
Banking system with:
- Create account (name, account number, balance)
- Deposit money
- Withdraw money (with validation)
- Transfer between accounts
- Display account details
- Transaction history
- Calculate interest
- Monthly statement generation
- Authentication (PIN)

### Input Format
Menu-driven with authentication.

### Output Format
```
Transaction confirmations
Account statements
Balance details
Transaction history
```

### Features
1. Transaction logging to file
2. PIN-based authentication
3. Minimum balance check
4. Transaction limits
5. Account types (savings, current)

<details>
<summary>Hint</summary>
Define account structure. Use linked list for accounts. Store transactions in array/list within account. Hash PIN for security. Use file I/O for persistence. Validate all operations.
</details>

---

## Challenge 18: Sudoku Solver with Generation
**Difficulty:** Hard
**Topics:** Backtracking, Algorithms, Validation

### Problem Statement
Complete Sudoku tool:
- Solve Sudoku puzzles (backtracking)
- Generate valid Sudoku puzzles
- Multiple difficulty levels (easy, medium, hard)
- Validate user input
- Provide hints
- Show solution steps
- Save/load puzzles

### Input Format
```
9x9 grid (0 for empty)
OR
GENERATE difficulty
```

### Output Format
```
Solved sudoku
Generation steps (if generating)
Validation results
```

### Features
1. Efficient backtracking with constraint propagation
2. Puzzle generation with unique solution
3. Difficulty based on number of empty cells
4. Hint system

<details>
<summary>Hint</summary>
Solve: Use backtracking, check row/col/box constraints. Generate: Start with valid solved grid, remove numbers randomly while ensuring unique solution. Validate uniqueness by checking if solve() finds only one solution.
</details>

---

## Challenge 19: Process Synchronization Simulator
**Difficulty:** Hard
**Topics:** Semaphores, Producer-Consumer, Deadlock

### Problem Statement
Simulate process synchronization problems:
- Producer-Consumer with bounded buffer
- Readers-Writers problem
- Dining Philosophers
- Detect and prevent deadlock
- Visualize process states
- Show resource allocation

### Input Format
```
Problem type
Number of processes
Simulation parameters
```

### Output Format
```
Process states over time
Resource allocation table
Deadlock detection results
Performance metrics
```

### Problems to Simulate
1. Producer-Consumer
2. Readers-Writers (reader/writer priority)
3. Dining Philosophers (with deadlock prevention)

<details>
<summary>Hint</summary>
Use arrays to represent semaphores. Simulate time steps. For each process, check conditions before accessing resources. Implement wait() and signal() operations. Detect deadlock using resource allocation graph or banker's algorithm.
</details>

---

## Challenge 20: Polynomial Calculator
**Difficulty:** Medium
**Topics:** Linked List, Algorithms, Mathematics

### Problem Statement
Polynomial calculator supporting:
- Add polynomials
- Subtract polynomials
- Multiply polynomials
- Divide polynomials
- Differentiate polynomial
- Integrate polynomial
- Evaluate at given x
- Display polynomial

### Input Format
```
Polynomial as: coefficient exponent pairs
Operations: ADD, SUB, MUL, DIV, DIFF, INT, EVAL x
```

### Output Format
```
Result polynomial
Evaluation result
```

### Example
```
P1(x) = 3x^4 + 2x^2 + 5
P2(x) = 2x^2 + 3x + 1
ADD: 3x^4 + 4x^2 + 3x + 6
MUL: 6x^6 + 9x^5 + 7x^4 + 6x^3 + 13x^2 + 15x + 5
```

<details>
<summary>Hint</summary>
Use linked list with nodes containing (coefficient, exponent). Keep terms sorted by exponent. Addition: merge lists, combine like terms. Multiplication: nested loops, add exponents, multiply coefficients. Differentiation: coef = coef × exp, exp = exp - 1.
</details>

---

## Challenge 21: Image Processing Tool
**Difficulty:** Hard
**Topics:** 2D Arrays, File Handling, Algorithms

### Problem Statement
Basic image processor for PPM format:
- Load/save PPM images
- Convert to grayscale
- Adjust brightness/contrast
- Rotate (90°, 180°, 270°)
- Flip (horizontal/vertical)
- Apply filters (blur, sharpen, edge detection)
- Crop and resize
- Histogram generation

### Input Format
```
Input image file (PPM format)
Operations with parameters
Output image file
```

### Output Format
```
Processed image
Operation statistics
Histogram data
```

### Filters to Implement
1. Gaussian blur
2. Sharpen
3. Edge detection (Sobel)
4. Emboss

<details>
<summary>Hint</summary>
PPM is simple text format: header + RGB values. Store as 2D array of RGB structures. For filters, use convolution with kernel matrices. Blur: average of neighbors. Edge: gradient calculation.
</details>

---

## Challenge 22: URL Shortener
**Difficulty:** Medium
**Topics:** Hash Table, Base Conversion, File Handling

### Problem Statement
URL shortening service:
- Shorten long URLs (generate short code)
- Expand short URLs to original
- Custom short URLs (if available)
- Track click statistics
- Expiry time for URLs
- Collision handling
- Save mappings to file

### Input Format
```
SHORTEN long_url [custom_code]
EXPAND short_code
STATS short_code
DELETE short_code
```

### Output Format
```
Short URL: domain.com/abc123
Original URL: [long url]
Clicks: [count]
```

### Features
1. Base62 encoding (a-z, A-Z, 0-9)
2. Collision detection and resolution
3. Analytics (clicks, access time)
4. URL validation

<details>
<summary>Hint</summary>
Use counter, convert to base62 for short code. Store mapping in hash table (short → long URL). For custom URLs, check if already exists. Store metadata (creation time, clicks, last access). Use file for persistence.
</details>

---

## Challenge 23: Music Playlist Manager
**Difficulty:** Medium
**Topics:** Doubly Linked List, Sorting, File Handling

### Problem Statement
Music playlist application:
- Add songs (title, artist, duration, genre)
- Create playlists
- Play (simulate: current, next, previous)
- Shuffle mode
- Repeat mode (off, one, all)
- Search by title/artist/genre
- Sort by various criteria
- Display now playing
- Save/load playlists

### Input Format
```
Operations: ADD, CREATE_PLAYLIST, PLAY, NEXT, PREV, SHUFFLE, etc.
Song details
```

### Output Format
```
Now playing: [song] by [artist] ([duration])
Playlist: [songs]
Queue: [upcoming songs]
```

### Features
1. Circular doubly linked list for playlist
2. Multiple playlists
3. Shuffle using random
4. Queue for upcoming songs

<details>
<summary>Hint</summary>
Use doubly linked list for easy prev/next navigation. Circular for repeat all. Maintain current song pointer. Shuffle: create random order array. Search: traverse list. Sort: convert to array, sort, rebuild list.
</details>

---

## Challenge 24: Maze Generator and Solver
**Difficulty:** Hard
**Topics:** Graph Algorithms, Backtracking, Randomization

### Problem Statement
Maze generator and solver:
- Generate random maze (DFS, Prim's)
- Solve maze (DFS, BFS, A*)
- Multiple paths visualization
- Adjustable maze size
- Ensure single solution
- Display generation process
- Show solving steps
- Save/load mazes

### Input Format
```
GENERATE rows cols algorithm
SOLVE start_row start_col end_row end_col algorithm
DISPLAY
```

### Output Format
```
Maze visualization (# for wall, space for path)
Solution path marked with *
Path length
Nodes explored
```

### Algorithms
Generation: Recursive backtracking, Randomized Prim's
Solving: DFS, BFS, A* (with Manhattan distance)

<details>
<summary>Hint</summary>
Represent maze as 2D array. Generate: start with all walls, carve passages using chosen algorithm. Solve: mark visited cells, try all directions, backtrack if dead end. A*: use priority queue with f = g + h.
</details>

---

## Challenge 25: Compiler - Lexical Analyzer
**Difficulty:** Hard
**Topics:** Finite Automata, String Processing, Token Recognition

### Problem Statement
Lexical analyzer (lexer) for C-like language:
- Identify tokens (keywords, identifiers, operators, literals)
- Classify token types
- Generate symbol table
- Report lexical errors
- Handle comments (single-line, multi-line)
- Line and column tracking for errors
- Output token stream

### Input Format
```
Source code file
```

### Output Format
```
Token stream: <TOKEN_TYPE, lexeme, line, column>
Symbol table
Errors (if any)
```

### Tokens to Recognize
- Keywords: if, else, while, int, float, return, etc.
- Identifiers: variable names
- Operators: +, -, *, /, =, ==, !=, <, >, etc.
- Literals: integers, floats, strings
- Delimiters: (, ), {, }, ;, ,

<details>
<summary>Hint</summary>
Use finite state machine (FSM) approach. Read character by character. Transition between states based on character. When terminal state reached, emit token. Maintain keyword table. Track line and column for error reporting.
</details>

---

## General Tips for Challenges

### Planning
1. Break down into smaller modules
2. Design data structures first
3. Plan file formats for persistence
4. Think about error handling

### Implementation
1. Start with core functionality
2. Add features incrementally
3. Test each module independently
4. Use meaningful variable names
5. Comment complex logic

### Testing
1. Test with edge cases
2. Test with invalid input
3. Test with large datasets
4. Check memory leaks (valgrind)
5. Verify file I/O works correctly

### Optimization
1. Profile code to find bottlenecks
2. Use appropriate data structures
3. Avoid unnecessary copying
4. Cache frequently accessed data

## Grading Rubric

Each challenge can be evaluated on:
- **Functionality (40%):** Does it work correctly?
- **Code Quality (20%):** Clean, readable, well-organized?
- **Error Handling (15%):** Handles edge cases and errors?
- **Efficiency (15%):** Uses appropriate algorithms and data structures?
- **Documentation (10%):** Comments, README, usage instructions?

## Next Steps

After completing these challenges:
- Participate in coding competitions
- Contribute to open-source C projects
- Build your own projects combining multiple concepts
- Study operating systems and system programming
- Explore embedded systems programming

Check the **solutions/** directory for reference implementations!
