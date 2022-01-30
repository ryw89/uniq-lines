// Simple linked list implementation. For this program, this is for
// storing unique lines in order.
typedef struct Node {
    char *data;
    struct Node *next;
} Node;

// Insert an element to the end of linked list
Node *append(char *data, Node *current);
