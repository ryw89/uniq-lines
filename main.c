#define _GNU_SOURCE

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "args.h"
#include "linked-list.h"
#include "map.h"

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

    // Create a map, using an array of MAP_SIZE
    MapElem map[MAP_SIZE] = {{NULL, 0, NULL}};

    // Root node of linked list for storing unique lines
    Node root = {NULL, NULL};
    Node *current = &root;

    // Iterate over lines
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, fp) != -1) {
        // Check if the line is in the map. If not, print add to
        // map.
        bool is_in_map = in_map(line, map);

        // Just (optionally) increment the count of times we've seen this line
        if (is_in_map) {
            if (args.count) {
                inc_count(line, map);
            }
            continue;
        }

        // Clone the char -- Note that each iteration of getline will
        // change the address that 'line' points to
        char *key = malloc(strlen(line));

#pragma GCC diagnostic warning "-Wstringop-overflow"
        strncpy(key, line, strlen(line));

        // The line wasn't seen before, so let's append it to the list
        // (That is, if we need it as determined by the command-line
        // args.)
        if (args.count) {
            current = append(key, current);
        }

        // Insert the key into the map
        bool already_checked = true;
        insert_key(key, map, already_checked);

        // If we're using the -c, --count args, we can't print until
        // we've counted every line
        if (!args.count) {
            printf("%s", line);
        }
    }

    // Iterate over list of lines input and print their counts, too
    if (args.count) {
        Node *current = &root;
        while (current != NULL && current->data != NULL) {
            // Get count of times this element has been seen
            unsigned long count = get_count(current->data, map);

            printf("%lu %s", count, current->data);
            current = current->next;
        }
    }
}
