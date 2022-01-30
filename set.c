#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SET_SIZE 512  // Arbitrary choice

// A single element in a bucket of the set
typedef struct SetElem {
    char *data;
    unsigned long count;
    struct SetElem *next;
} SetElem;

// Jenkins hash function
unsigned long hash(char *key) {
    unsigned long hash = 0;
    int i = 0;
    int len = strlen(key);
    for (hash = i = 0; i < len; ++i) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

unsigned long hash_to_index(unsigned long hash, int divisor) {
    return hash % divisor;
}

unsigned long get_index(char *key) {
    return (hash_to_index(hash(key), SET_SIZE));
}

// Determine whether certain key is in a set.
bool in_set(char *key, SetElem set[]) {
    // Find the index of the bucket the key would have if it's in the
    // set
    unsigned long index = get_index(key);
    SetElem elem = set[index];

    // Empty bucket in set, so return false
    if (elem.data == NULL) {
        return false;
    }

    // Check first entry in bucket
    if (strcmp(key, elem.data) == 0) {
        return true;
    }

    // Otherwise, iterate through the bucket's elements using the
    // 'next' pointers, until we find the key or hit a null pointer
    SetElem *current = &elem;
    while (current != NULL) {
        // Compare this element's data with the key
        if ((strcmp(key, current->data) == 0)) {
            return true;
        }

        // Didn't match, so we'll continue with the next element. If
        // it's a null pointer, we'll end up breaking out of the loop
        current = current->next;
    }

    // Couldn't find anything
    return false;
}

// Insert a key into a set
void insert_key(char *key, SetElem set[], bool skip_check) {
    // First, fetch index of the key
    unsigned long index = get_index(key);

    // We may have just checked the set, so no need to traverse again
    if (!skip_check) {
        // Check if the key is in the set. If so, just return.
        if (in_set(key, set)) {
            return;
        }
    }

    // Iterate through this bucket's elements until we hit a null next
    // pointer. (Which could very well happen on the first element of
    // the bucket.)
    SetElem *current = &set[index];
    while (current->next != NULL) {
        current = current->next;
    }

    // If current.data is NULL, just update its data & counts fields.
    // (This happens if we have an empty bucket.)
    if (current->data == NULL) {
        current->data = key;
        current->count = 1;
        return;
    }

    // Allocate a new set element.
    SetElem *new_elem = (SetElem *)malloc(sizeof(SetElem));

    // Insert data
    new_elem->data = key;
    new_elem->count = 1;
    new_elem->next = NULL;

    // Update next pointer
    current->next = new_elem;
}

// Increment the count of times we've seen this element in the set
bool inc_count(char *key, SetElem set[]) {
    // First, fetch index of the key
    unsigned long index = get_index(key);

    // Otherwise, iterate through the bucket's elements using the
    // 'next' pointers, until we find the key or hit a null pointer
    SetElem *current = &set[index];
    while (current != NULL) {
        // Compare this element's data with the key
        if ((strcmp(key, current->data) == 0)) {
            ++current->count;
            return true;
        }

        // Didn't match, so we'll continue with the next element. If
        // it's a null pointer, we'll end up breaking out of the loop
        current = current->next;
    }

    // Couldn't find the key -- return false to indicate failure
    return false;
}

// Get the count of times this element has been seen.
unsigned long get_count(char *key, SetElem set[]) {
    // First, fetch index of the key
    unsigned long index = get_index(key);

    // Iterate through the bucket's elements using the 'next'
    // pointers, until we find the key or hit a null pointer
    SetElem *current = &set[index];
    while (current != NULL) {
        // Compare this element's data with the key
        if ((strcmp(key, current->data) == 0)) {
            return current->count;
        }

        // Didn't match, so we'll continue with the next element. If
        // it's a null pointer, we'll end up breaking out of the loop
        current = current->next;
    }

    // Couldn't find the key -- return zero count
    return 0;
}
