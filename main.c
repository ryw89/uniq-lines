#define _GNU_SOURCE

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "args.h"
#include "linked-list.h"
#include "set.h"

int main(int argc, char **argv) {
    // Parse CLI args
    Args args = {NULL, false};
    parse_args(argc, argv, &args, 3);

    FILE *fp;
    if (args.file == NULL) {
        // Open file description 0, i.e. stdin
        fp = fdopen(0, "r");
    } else {
        fp = fopen(args.file, "r");
    }

    // Error handling
    if (fp == NULL) {
        fprintf(stderr, "uniq-lines: Could not open file.\n");
        return EXIT_FAILURE;
    }

    // Create a set, using an array of SET_SIZE
    SetElem set[SET_SIZE] = {{NULL, 0, NULL}};

    // Root node of linked list for storing unique lines
    Node root = {NULL, NULL};

    // Iterate over lines
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, fp) != -1) {
        // Check if the line is in the set. If not, print add to
        // set.
        bool is_in_set = in_set(line, set);

        // Just (optionally) increment the count of times we've seen this line
        if (is_in_set) {
            if (args.count) {
                inc_count(line, set);
            }
            continue;
        }

        // Clone the char -- Note that each iteration of getline will
        // change the address that 'line' points to
        char *key = malloc(strlen(line));
        strncpy(key, line, strlen(line));

        // The line wasn't seen before, so let's append it to the list
        // (That is, if we need it as determined by the command-line
        // args.)
        if (args.count) {
            append(key, &root);
        }

        // Insert the key into the set
        bool already_checked = true;
        insert_key(key, set, already_checked);

        // If we're using the -c, --count args, we can't print until
        // we've counted every line
        if (!args.count) {
            printf("%s", line);
        }
    }

    // Iterate over list of lines input and print their counts, too
    if (args.count) {
        Node *current = &root;
        while (current != NULL) {
			// Get count of times this element has been seen
			unsigned long count = get_count(current->data, set);

            printf("%lu %s", count, current->data);
            current = current->next;
        }
    }
}
