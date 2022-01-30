#include <stdlib.h>

// Simple linked list implementation. For this program, this is for
// storing unique lines in order.
typedef struct Node {
    char *data;
    struct Node *next;
} Node;

// Insert an element to the end of linked list
void append(char *data, Node *current) {
    // Iterate to end of list
    while (current->next != NULL) {
        current = current->next;
    }

    // If current.data is NULL, just update its data.
    // (This happens if we have an empty list.)
    if (current->data == NULL) {
        current->data = data;
        return;
    }

    // Otherwise, allocate a new node and point current.next to it
    Node *node = (Node *)malloc(sizeof(Node));

    // Insert data
    current->next = node;
}
