#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct for holding data on command line args
typedef struct Args {
    char *file;
    bool count;
} Args;

// Parse command-line arguments
void parse_args(int argc, char **argv, Args *args, int max_args) {
    if (argc > max_args) {
        fprintf(stderr, "uniq-lines: Too many arguments.\n");
        exit(0);
    }

    // Iterate over non-program name args
    bool found_filename = false;
    for (int i = 1; i < argc; ++i) {
        // Check for help arguments
        if (strcmp(argv[i], "-h") == 0) {
            printf("uniq-lines: Help placeholder.\n");
            exit(0);
        }

        // Check for count argument
        if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--count") == 0) {
            args->count = true;
            continue;
        }

        if (found_filename) {
            fprintf(stderr, "uniq-lines: More than one filename found.\n");
            exit(0);
        }
        args->file = argv[i];
        found_filename = true;
    }
}
