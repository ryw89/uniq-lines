#include <stdbool.h>

#define MAP_SIZE 512  // Arbitrary choice

typedef struct MapElem {
    char *data;
    unsigned long count;
    struct MapElem *next;
} MapElem;

unsigned long hash(char *str);

int hash_to_index(int hash, int divisor);

unsigned long get_index(char *key);

bool in_map(char *key, MapElem map[]);

void insert_key(char *key, MapElem map[], bool already_checked);

bool inc_count(char *key, MapElem map[]);

unsigned long get_count(char *key, MapElem map[]);
