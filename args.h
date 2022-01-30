#include <stdbool.h>

// Struct for holding data on command line args
typedef struct Args {
    char *file;
    bool count;
} Args;

void parse_args(int argc, char **argv, Args *args, int max_args);
