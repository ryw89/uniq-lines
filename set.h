#include <stdbool.h>

#define SET_SIZE 512  // Arbitrary choice

typedef struct SetElem {
    char *data;
	unsigned long count;
    struct SetElem *next;
} SetElem;

unsigned long hash(char *str);

int hash_to_index(int hash, int divisor);

unsigned long get_index(char *key);

bool in_set(char *key, SetElem set[]);

void insert_key(char *key, SetElem set[], bool already_checked);

bool inc_count(char *key, SetElem set[]);

unsigned long get_count(char *key, SetElem set[]);
