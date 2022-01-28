#define _GNU_SOURCE

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"

int main(int argc, char const **argv) {
    FILE *fp;
    if (argc == 1) {
        // Open file description 0, i.e. stdin
        fp = fdopen(0, "r");
    } else if (argc == 2) {
        fp = fopen(argv[1], "r");
    } else {
        fprintf(stderr, "uniq-lines: Too many arguments.\n");
        return EXIT_SUCCESS;
    }

    // Error handling
    if (fp == NULL) {
        fprintf(stderr, "uniq-lines: Could not open file.\n");
        return EXIT_FAILURE;
    }

    // Create a set, using an array of SET_SIZE
    SetElem set[SET_SIZE] = {{NULL, NULL}};

    // Print lines
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, fp) != -1) {
        // Check if the line is in the set. If not, print and add to
        // set.
        bool is_in_set = in_set(line, set);
        if (is_in_set) {
            continue;
        }

		// Clone the char -- Note that each iteration of getline will
		// change the address that 'line' points to
		char *key = malloc(strlen(line));
		strncpy(key, line, strlen(line));

        // Insert the key into the set
		bool already_checked = true;
        insert_key(key, set, already_checked);

        // This is a new line that was newly-added to the set, so
        // print
        printf("%s", line);
    }
}
