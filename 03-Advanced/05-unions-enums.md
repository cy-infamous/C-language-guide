# Unions and Enumerations in C

## Table of Contents
1. [Enumerations (enum)](#enumerations)
2. [Unions](#unions)
3. [Bit Fields](#bit-fields)
4. [Practical Applications](#practical-applications)
5. [Advanced Techniques](#advanced-techniques)
6. [Practice Exercises](#practice-exercises)

---

## Enumerations (enum)

Enumerations provide a way to define named integer constants, making code more readable and maintainable.

### 1. Basic Enum Syntax

```c
enum EnumName {
    CONSTANT1,
    CONSTANT2,
    CONSTANT3
};
```

By default, values start at 0 and increment by 1.

**Example:**

```c
#include <stdio.h>

enum Day {
    MONDAY,    // 0
    TUESDAY,   // 1
    WEDNESDAY, // 2
    THURSDAY,  // 3
    FRIDAY,    // 4
    SATURDAY,  // 5
    SUNDAY     // 6
};

int main() {
    enum Day today = WEDNESDAY;

    printf("Today is day %d\n", today);  // 2

    if (today == WEDNESDAY) {
        printf("It's Wednesday!\n");
    }

    return 0;
}
```

### 2. Custom Values

You can assign specific values to enum constants:

```c
enum Status {
    SUCCESS = 0,
    ERROR = -1,
    PENDING = 100,
    TIMEOUT = 200
};

enum HTTPStatus {
    HTTP_OK = 200,
    HTTP_CREATED = 201,
    HTTP_BAD_REQUEST = 400,
    HTTP_UNAUTHORIZED = 401,
    HTTP_NOT_FOUND = 404,
    HTTP_SERVER_ERROR = 500
};
```

### 3. Sequential Assignment

Only some values need explicit assignment:

```c
enum Month {
    JAN = 1,  // 1
    FEB,      // 2
    MAR,      // 3
    APR,      // 4
    MAY,      // 5
    JUN,      // 6
    JUL,      // 7
    AUG,      // 8
    SEP,      // 9
    OCT,      // 10
    NOV,      // 11
    DEC       // 12
};
```

### 4. Typedef with Enum

```c
typedef enum {
    NORTH,
    SOUTH,
    EAST,
    WEST
} Direction;

// Usage: No need for "enum" keyword
Direction heading = NORTH;
```

### 5. Complete Example: Traffic Light System

```c
#include <stdio.h>

typedef enum {
    RED,
    YELLOW,
    GREEN
} TrafficLight;

const char* get_light_name(TrafficLight light) {
    switch (light) {
        case RED:    return "Red";
        case YELLOW: return "Yellow";
        case GREEN:  return "Green";
        default:     return "Unknown";
    }
}

const char* get_action(TrafficLight light) {
    switch (light) {
        case RED:    return "STOP";
        case YELLOW: return "SLOW DOWN";
        case GREEN:  return "GO";
        default:     return "ERROR";
    }
}

TrafficLight next_light(TrafficLight current) {
    switch (current) {
        case RED:    return GREEN;
        case GREEN:  return YELLOW;
        case YELLOW: return RED;
        default:     return RED;
    }
}

int main() {
    TrafficLight light = RED;

    for (int i = 0; i < 6; i++) {
        printf("Light: %s - Action: %s\n",
               get_light_name(light),
               get_action(light));
        light = next_light(light);
    }

    return 0;
}
```

**Output:**
```
Light: Red - Action: STOP
Light: Green - Action: GO
Light: Yellow - Action: SLOW DOWN
Light: Red - Action: STOP
Light: Green - Action: GO
Light: Yellow - Action: SLOW DOWN
```

### 6. Enum as Flags (Bit Flags)

```c
#include <stdio.h>

typedef enum {
    READ    = 1 << 0,  // 0001 = 1
    WRITE   = 1 << 1,  // 0010 = 2
    EXECUTE = 1 << 2,  // 0100 = 4
    DELETE  = 1 << 3   // 1000 = 8
} Permission;

int main() {
    // Combine permissions using bitwise OR
    int user_perms = READ | WRITE | EXECUTE;  // 0111 = 7

    // Check permission using bitwise AND
    if (user_perms & READ) {
        printf("User has READ permission\n");
    }

    if (user_perms & WRITE) {
        printf("User has WRITE permission\n");
    }

    if (user_perms & DELETE) {
        printf("User has DELETE permission\n");
    } else {
        printf("User does NOT have DELETE permission\n");
    }

    // Add permission
    user_perms |= DELETE;
    printf("\nAfter adding DELETE:\n");
    if (user_perms & DELETE) {
        printf("User has DELETE permission\n");
    }

    // Remove permission
    user_perms &= ~WRITE;
    printf("\nAfter removing WRITE:\n");
    if (user_perms & WRITE) {
        printf("User has WRITE permission\n");
    } else {
        printf("User does NOT have WRITE permission\n");
    }

    return 0;
}
```

### 7. Enum Best Practices

```c
// Good: Descriptive names
typedef enum {
    FILE_NOT_FOUND,
    PERMISSION_DENIED,
    OUT_OF_MEMORY
} ErrorCode;

// Good: Use for related constants
typedef enum {
    SMALL = 1,
    MEDIUM = 2,
    LARGE = 3,
    EXTRA_LARGE = 4
} Size;

// Good: Prefix to avoid name conflicts
typedef enum {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE
} Color;

typedef enum {
    STATE_RED,
    STATE_GREEN,
    STATE_BLUE
} State;
```

---

## Unions

A union is a user-defined type that allows storing different data types in the same memory location. Only one member can hold a value at any given time.

### 1. Basic Union Syntax

```c
union UnionName {
    type1 member1;
    type2 member2;
    type3 member3;
};
```

### 2. Memory Layout

**Structure (all members exist simultaneously):**
```c
struct Point {
    int x;     // 4 bytes
    int y;     // 4 bytes
};  // Total: 8 bytes
```

```
Memory Layout (struct):
[x: 4 bytes][y: 4 bytes]
```

**Union (members share same memory):**
```c
union Data {
    int i;      // 4 bytes
    float f;    // 4 bytes
    char str[4]; // 4 bytes
};  // Total: 4 bytes (size of largest member)
```

```
Memory Layout (union):
[Shared: 4 bytes]
Can hold: i OR f OR str
```

### 3. Basic Union Example

```c
#include <stdio.h>

union Data {
    int i;
    float f;
    char c;
};

int main() {
    union Data data;

    // Store integer
    data.i = 10;
    printf("data.i = %d\n", data.i);

    // Store float (overwrites integer)
    data.f = 3.14;
    printf("data.f = %.2f\n", data.f);
    printf("data.i = %d (garbage)\n", data.i);  // Garbage value

    // Store character (overwrites float)
    data.c = 'A';
    printf("data.c = %c\n", data.c);
    printf("data.f = %.2f (garbage)\n", data.f);  // Garbage value

    printf("\nSize of union: %zu bytes\n", sizeof(data));

    return 0;
}
```

**Output:**
```
data.i = 10
data.f = 3.14
data.i = 1078523331 (garbage)
data.c = A
data.f = 0.00 (garbage)

Size of union: 4 bytes
```

### 4. Tagged Union (Discriminated Union)

Use an enum to track which member is currently active:

```c
#include <stdio.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
} DataType;

typedef struct {
    DataType type;
    union {
        int i;
        float f;
        char str[50];
    } value;
} Data;

void print_data(Data *data) {
    switch (data->type) {
        case TYPE_INT:
            printf("Integer: %d\n", data->value.i);
            break;
        case TYPE_FLOAT:
            printf("Float: %.2f\n", data->value.f);
            break;
        case TYPE_STRING:
            printf("String: %s\n", data->value.str);
            break;
    }
}

int main() {
    Data data;

    // Store integer
    data.type = TYPE_INT;
    data.value.i = 42;
    print_data(&data);

    // Store float
    data.type = TYPE_FLOAT;
    data.value.f = 3.14159;
    print_data(&data);

    // Store string
    data.type = TYPE_STRING;
    strcpy(data.value.str, "Hello, Union!");
    print_data(&data);

    return 0;
}
```

### 5. Union for Type Conversion

```c
#include <stdio.h>

union FloatBytes {
    float f;
    unsigned char bytes[4];
};

int main() {
    union FloatBytes fb;
    fb.f = 3.14159;

    printf("Float value: %.5f\n", fb.f);
    printf("Byte representation: ");
    for (int i = 0; i < 4; i++) {
        printf("%02X ", fb.bytes[i]);
    }
    printf("\n");

    return 0;
}
```

### 6. Union for Memory Efficient Storage

```c
#include <stdio.h>
#include <string.h>

// Large structure - wastes memory
struct LargeData {
    int type;
    int int_data;
    double double_data;
    char string_data[100];
};  // Size: ~112 bytes (all fields always allocated)

// Efficient tagged union
typedef enum { INT_TYPE, DOUBLE_TYPE, STRING_TYPE } Type;

typedef struct {
    Type type;
    union {
        int int_data;
        double double_data;
        char string_data[100];
    } data;
} EfficientData;  // Size: ~104 bytes (only one field allocated)

int main() {
    printf("LargeData size: %zu bytes\n", sizeof(struct LargeData));
    printf("EfficientData size: %zu bytes\n", sizeof(EfficientData));

    // Can store 10x more EfficientData in same memory!

    return 0;
}
```

### 7. Anonymous Unions (C11)

```c
#include <stdio.h>

typedef struct {
    int type;
    union {  // Anonymous union
        int i;
        float f;
        char c;
    };  // No name needed
} Value;

int main() {
    Value v;
    v.type = 1;
    v.i = 42;  // Direct access, no "union_name.i"

    printf("Integer: %d\n", v.i);

    return 0;
}
```

---

## Bit Fields

Bit fields allow packing multiple variables into a single byte or word, saving memory.

### 1. Basic Bit Field Syntax

```c
struct BitFieldName {
    unsigned int field1 : bit_count;
    unsigned int field2 : bit_count;
};
```

### 2. Simple Example

```c
#include <stdio.h>

struct Flags {
    unsigned int flag1 : 1;  // 1 bit
    unsigned int flag2 : 1;  // 1 bit
    unsigned int flag3 : 1;  // 1 bit
    unsigned int value : 5;  // 5 bits
};  // Total: 8 bits = 1 byte

int main() {
    struct Flags f = {0};

    printf("Size: %zu bytes\n", sizeof(f));  // 1 byte

    f.flag1 = 1;
    f.flag2 = 0;
    f.flag3 = 1;
    f.value = 15;  // Max: 31 (5 bits = 2^5 - 1)

    printf("flag1: %u\n", f.flag1);
    printf("flag2: %u\n", f.flag2);
    printf("flag3: %u\n", f.flag3);
    printf("value: %u\n", f.value);

    return 0;
}
```

### 3. Hardware Register Mapping

```c
#include <stdio.h>
#include <stdint.h>

// Typical microcontroller status register
typedef struct {
    uint8_t carry     : 1;  // Bit 0
    uint8_t zero      : 1;  // Bit 1
    uint8_t interrupt : 1;  // Bit 2
    uint8_t decimal   : 1;  // Bit 3
    uint8_t break_flag: 1;  // Bit 4
    uint8_t unused    : 1;  // Bit 5
    uint8_t overflow  : 1;  // Bit 6
    uint8_t negative  : 1;  // Bit 7
} StatusRegister;

void print_status(StatusRegister *sr) {
    printf("Status Register:\n");
    printf("  Carry: %d\n", sr->carry);
    printf("  Zero: %d\n", sr->zero);
    printf("  Interrupt: %d\n", sr->interrupt);
    printf("  Overflow: %d\n", sr->overflow);
    printf("  Negative: %d\n", sr->negative);
}

int main() {
    StatusRegister sr = {0};

    // Set some flags
    sr.carry = 1;
    sr.zero = 0;
    sr.overflow = 1;

    print_status(&sr);

    return 0;
}
```

### 4. Date Representation

```c
#include <stdio.h>

typedef struct {
    unsigned int day   : 5;   // 1-31 (5 bits = 0-31)
    unsigned int month : 4;   // 1-12 (4 bits = 0-15)
    unsigned int year  : 12;  // 0-4095 (12 bits, offset from base year)
} Date;  // Total: 21 bits (packed into 3-4 bytes depending on compiler)

int main() {
    Date birthday;

    birthday.day = 15;
    birthday.month = 6;
    birthday.year = 2024 - 2000;  // Store offset from 2000

    printf("Date: %02u/%02u/%u\n",
           birthday.day,
           birthday.month,
           birthday.year + 2000);

    printf("Size: %zu bytes\n", sizeof(Date));

    return 0;
}
```

### 5. RGB Color

```c
#include <stdio.h>

typedef struct {
    unsigned char red   : 5;  // 0-31
    unsigned char green : 6;  // 0-63
    unsigned char blue  : 5;  // 0-31
} RGB16;  // 16-bit color (5-6-5 format)

typedef struct {
    unsigned char red;    // 0-255
    unsigned char green;  // 0-255
    unsigned char blue;   // 0-255
} RGB24;  // 24-bit color

int main() {
    printf("RGB16 size: %zu bytes\n", sizeof(RGB16));  // 2 bytes
    printf("RGB24 size: %zu bytes\n", sizeof(RGB24));  // 3 bytes

    RGB16 color16;
    color16.red = 31;
    color16.green = 63;
    color16.blue = 31;

    printf("RGB16: (%u, %u, %u)\n", color16.red, color16.green, color16.blue);

    return 0;
}
```

### 6. Bit Field Limitations and Cautions

```c
// WARNING: Bit fields are not portable!

// 1. Order depends on endianness
struct BitOrder {
    unsigned int a : 4;
    unsigned int b : 4;
};  // Order of 'a' and 'b' in memory varies by platform

// 2. Cannot take address of bit field
struct Flags {
    unsigned int flag : 1;
};

// int *ptr = &flags.flag;  // ERROR: Cannot take address

// 3. Arrays of bit fields not allowed
// unsigned int bits[10] : 1;  // ERROR

// 4. Signedness matters
struct Signed {
    signed int value : 3;  // Range: -4 to 3
};

struct Unsigned {
    unsigned int value : 3;  // Range: 0 to 7
};
```

---

## Practical Applications

### 1. Network Packet Header

```c
#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint8_t version    : 4;
    uint8_t header_len : 4;
    uint8_t tos;
    uint16_t total_length;
    uint16_t identification;
    uint16_t flags     : 3;
    uint16_t fragment  : 13;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t checksum;
    uint32_t source_ip;
    uint32_t dest_ip;
} IPHeader;

void print_ip_header(IPHeader *header) {
    printf("IP Header:\n");
    printf("  Version: %u\n", header->version);
    printf("  Header Length: %u\n", header->header_len);
    printf("  Total Length: %u\n", header->total_length);
    printf("  TTL: %u\n", header->ttl);
    printf("  Protocol: %u\n", header->protocol);
}

int main() {
    IPHeader header = {0};
    header.version = 4;
    header.header_len = 5;
    header.total_length = 60;
    header.ttl = 64;
    header.protocol = 6;  // TCP

    print_ip_header(&header);

    printf("\nSize: %zu bytes\n", sizeof(IPHeader));

    return 0;
}
```

### 2. File Attributes System

```c
#include <stdio.h>
#include <stdbool.h>

typedef enum {
    ATTR_READONLY  = 1 << 0,  // 0001
    ATTR_HIDDEN    = 1 << 1,  // 0010
    ATTR_SYSTEM    = 1 << 2,  // 0100
    ATTR_ARCHIVE   = 1 << 3,  // 1000
    ATTR_DIRECTORY = 1 << 4   // 10000
} FileAttribute;

typedef struct {
    char name[256];
    unsigned int attributes;
} FileInfo;

void set_attribute(FileInfo *file, FileAttribute attr) {
    file->attributes |= attr;
}

void clear_attribute(FileInfo *file, FileAttribute attr) {
    file->attributes &= ~attr;
}

bool has_attribute(FileInfo *file, FileAttribute attr) {
    return (file->attributes & attr) != 0;
}

void print_attributes(FileInfo *file) {
    printf("File: %s\n", file->name);
    printf("  Read-only: %s\n", has_attribute(file, ATTR_READONLY) ? "Yes" : "No");
    printf("  Hidden: %s\n", has_attribute(file, ATTR_HIDDEN) ? "Yes" : "No");
    printf("  System: %s\n", has_attribute(file, ATTR_SYSTEM) ? "Yes" : "No");
    printf("  Archive: %s\n", has_attribute(file, ATTR_ARCHIVE) ? "Yes" : "No");
    printf("  Directory: %s\n", has_attribute(file, ATTR_DIRECTORY) ? "Yes" : "No");
}

int main() {
    FileInfo file = {"document.txt", 0};

    set_attribute(&file, ATTR_READONLY);
    set_attribute(&file, ATTR_ARCHIVE);

    print_attributes(&file);

    printf("\nRemoving read-only...\n");
    clear_attribute(&file, ATTR_READONLY);

    print_attributes(&file);

    return 0;
}
```

### 3. Configuration Settings Union

```c
#include <stdio.h>
#include <string.h>

typedef enum {
    CONFIG_INT,
    CONFIG_FLOAT,
    CONFIG_STRING,
    CONFIG_BOOL
} ConfigType;

typedef struct {
    char key[50];
    ConfigType type;
    union {
        int int_val;
        float float_val;
        char string_val[100];
        int bool_val;
    } value;
} ConfigItem;

void set_int_config(ConfigItem *item, const char *key, int value) {
    strcpy(item->key, key);
    item->type = CONFIG_INT;
    item->value.int_val = value;
}

void set_string_config(ConfigItem *item, const char *key, const char *value) {
    strcpy(item->key, key);
    item->type = CONFIG_STRING;
    strcpy(item->value.string_val, value);
}

void print_config(ConfigItem *item) {
    printf("%s = ", item->key);
    switch (item->type) {
        case CONFIG_INT:
            printf("%d\n", item->value.int_val);
            break;
        case CONFIG_FLOAT:
            printf("%.2f\n", item->value.float_val);
            break;
        case CONFIG_STRING:
            printf("\"%s\"\n", item->value.string_val);
            break;
        case CONFIG_BOOL:
            printf("%s\n", item->value.bool_val ? "true" : "false");
            break;
    }
}

int main() {
    ConfigItem configs[10];
    int count = 0;

    set_int_config(&configs[count++], "max_connections", 100);
    set_string_config(&configs[count++], "server_name", "MyServer");

    configs[count].type = CONFIG_FLOAT;
    strcpy(configs[count].key, "timeout");
    configs[count].value.float_val = 30.5;
    count++;

    configs[count].type = CONFIG_BOOL;
    strcpy(configs[count].key, "debug_mode");
    configs[count].value.bool_val = 1;
    count++;

    printf("Configuration:\n");
    for (int i = 0; i < count; i++) {
        print_config(&configs[i]);
    }

    return 0;
}
```

### 4. Expression Evaluator with Union

```c
#include <stdio.h>

typedef enum {
    NODE_NUMBER,
    NODE_OPERATOR
} NodeType;

typedef struct Node {
    NodeType type;
    union {
        double number;
        struct {
            char operator;
            struct Node *left;
            struct Node *right;
        } op;
    } data;
} Node;

Node* create_number(double value) {
    Node *node = malloc(sizeof(Node));
    node->type = NODE_NUMBER;
    node->data.number = value;
    return node;
}

Node* create_operator(char op, Node *left, Node *right) {
    Node *node = malloc(sizeof(Node));
    node->type = NODE_OPERATOR;
    node->data.op.operator = op;
    node->data.op.left = left;
    node->data.op.right = right;
    return node;
}

double evaluate(Node *node) {
    if (node->type == NODE_NUMBER) {
        return node->data.number;
    }

    double left = evaluate(node->data.op.left);
    double right = evaluate(node->data.op.right);

    switch (node->data.op.operator) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return right != 0 ? left / right : 0;
        default: return 0;
    }
}

// Example: (5 + 3) * 2
int main() {
    Node *left = create_operator('+', create_number(5), create_number(3));
    Node *root = create_operator('*', left, create_number(2));

    double result = evaluate(root);
    printf("Result: %.2f\n", result);  // 16.00

    // Memory cleanup omitted for brevity

    return 0;
}
```

---

## Advanced Techniques

### 1. Union Type Punning

```c
#include <stdio.h>
#include <stdint.h>

// View float as integer bits
union FloatInt {
    float f;
    uint32_t i;
};

void analyze_float(float value) {
    union FloatInt fi;
    fi.f = value;

    uint32_t sign = (fi.i >> 31) & 1;
    uint32_t exponent = (fi.i >> 23) & 0xFF;
    uint32_t mantissa = fi.i & 0x7FFFFF;

    printf("Float: %f\n", value);
    printf("  Sign: %u\n", sign);
    printf("  Exponent: %u\n", exponent);
    printf("  Mantissa: %06X\n", mantissa);
    printf("  Hex: %08X\n", fi.i);
}

int main() {
    analyze_float(3.14159);
    printf("\n");
    analyze_float(-42.0);

    return 0;
}
```

### 2. Enum with String Conversion

```c
#include <stdio.h>

#define FOREACH_STATUS(STATUS) \
    STATUS(SUCCESS)   \
    STATUS(PENDING)   \
    STATUS(ERROR)     \
    STATUS(TIMEOUT)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

typedef enum {
    FOREACH_STATUS(GENERATE_ENUM)
} Status;

static const char *status_strings[] = {
    FOREACH_STATUS(GENERATE_STRING)
};

const char* status_to_string(Status status) {
    return status_strings[status];
}

int main() {
    Status s = ERROR;
    printf("Status: %s\n", status_to_string(s));

    for (int i = 0; i < 4; i++) {
        printf("%d: %s\n", i, status_to_string(i));
    }

    return 0;
}
```

---

## Practice Exercises

### Exercise 1: Day Planner with Enums (Medium)
Create a day planner using enums:
```c
typedef enum { MON, TUE, WED, THU, FRI, SAT, SUN } Day;
typedef enum { WORK, STUDY, EXERCISE, LEISURE, SLEEP } Activity;
```

Implement:
- Schedule activities for each day
- Find free time slots
- Calculate total hours per activity type
- Print weekly schedule

---

### Exercise 2: Variant Type System (Hard)
Implement a variant type that can hold any C data type:
```c
typedef struct {
    enum { INT, FLOAT, DOUBLE, STRING, POINTER } type;
    union {
        int i;
        float f;
        double d;
        char *str;
        void *ptr;
    } data;
} Variant;
```

Implement:
- `variant_create_*()` functions for each type
- `variant_get_*()` with type checking
- `variant_to_string()` for display
- `variant_compare()` for equality
- `variant_free()` for cleanup

---

### Exercise 3: Packet Protocol (Hard)
Design a network packet structure using bit fields:
```c
typedef struct {
    // Your bit fields here
    // Version (4 bits), Type (3 bits), Priority (3 bits), etc.
} PacketHeader;

typedef struct {
    PacketHeader header;
    union {
        char text_data[256];
        int binary_data[64];
        float sensor_data[64];
    } payload;
} Packet;
```

Implement packet creation, validation, serialization functions.

---

### Exercise 4: State Machine with Enums (Medium)
Create a vending machine state machine:
```c
typedef enum {
    STATE_IDLE,
    STATE_SELECTING,
    STATE_PAYMENT,
    STATE_DISPENSING,
    STATE_ERROR
} VendingState;

typedef enum {
    EVENT_COIN_INSERTED,
    EVENT_PRODUCT_SELECTED,
    EVENT_CANCEL,
    EVENT_DISPENSE_COMPLETE
} VendingEvent;
```

Implement state transitions and actions for each state.

---

### Exercise 5: CPU Flags Register (Medium)
Simulate a CPU flags register using bit fields:
```c
typedef struct {
    unsigned carry : 1;
    unsigned zero : 1;
    unsigned sign : 1;
    unsigned overflow : 1;
    unsigned parity : 1;
    unsigned auxiliary : 1;
} CPUFlags;
```

Implement arithmetic operations (add, subtract) that properly set flags.

---

### Exercise 6: JSON-like Data Structure (Advanced)
Create a JSON-like data structure using unions:
```c
typedef enum {
    JSON_NULL,
    JSON_BOOL,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} JSONType;

typedef struct JSONValue {
    JSONType type;
    union {
        int bool_val;
        double number_val;
        char *string_val;
        struct {
            struct JSONValue *items;
            int count;
        } array_val;
        // Add object support
    } data;
} JSONValue;
```

Implement create, get, set, print, and free functions.

---

### Exercise 7: Graphics Shape Union (Medium)
```c
typedef enum { CIRCLE, RECTANGLE, TRIANGLE } ShapeType;

typedef struct {
    ShapeType type;
    union {
        struct { double radius; } circle;
        struct { double width, height; } rectangle;
        struct { double a, b, c; } triangle;
    } data;
} Shape;
```

Implement:
- `calculate_area()`
- `calculate_perimeter()`
- `print_shape()`
- `is_valid_shape()` (check valid dimensions)

---

### Exercise 8: Bit-Packed File Format (Hard)
Design an efficient binary file format using bit fields:
```c
typedef struct {
    unsigned type : 3;        // 8 types max
    unsigned compressed : 1;
    unsigned encrypted : 1;
    unsigned reserved : 3;
    unsigned version : 8;     // 0-255
    unsigned size : 16;       // Size in KB
} FileHeader;
```

Implement:
- Read/write file with this header
- Validation functions
- Conversion to/from human-readable format

---

## Summary

### Enumerations

**Advantages:**
- Improves code readability
- Type-safe constants
- Easy to maintain related constants
- Works well with switch statements

**Best Practices:**
- Use meaningful names
- Use typedef for convenience
- Assign values explicitly for file formats/protocols
- Use bit flags for combinable options

### Unions

**Advantages:**
- Memory efficient (shares space)
- Type punning and low-level manipulation
- Variant types
- Hardware register mapping

**Best Practices:**
- Use tagged unions (track active member)
- Be aware of size = largest member
- Understand portability issues
- Use for memory-constrained environments

### Bit Fields

**Advantages:**
- Extreme memory efficiency
- Natural hardware mapping
- Compact data structures

**Cautions:**
- Non-portable (endianness, alignment)
- Cannot take address
- Slower access than regular members
- Use primarily for hardware, protocols, packed data

**When to Use:**
- Enums: Related named constants, state machines
- Unions: Memory efficiency, variant types, type conversion
- Bit Fields: Hardware registers, network packets, memory-constrained systems

Master these and you'll write efficient, readable, professional C code!
