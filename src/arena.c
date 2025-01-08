#include "arena.h"
#include <stdlib.h>

struct arena {
    void* buffer;
    unsigned int offset;
    unsigned int capacity;
};

struct arena* arena_create(unsigned int capacity) {
    struct arena *arena = malloc(sizeof(struct arena));
    arena->buffer = malloc(capacity);
    arena->offset = 0;
    arena->capacity = capacity;
    return arena;
}

void* arena_malloc(struct arena *arena, unsigned int size) {
    if ((arena->offset + size) > arena->capacity) {
        return NULL;
    }
    void *ptr = &arena->buffer[arena->offset];
    arena->offset += size;
    return ptr;
}

void arena_free(struct arena *arena) {
    free(arena->buffer);
    free(arena);
}

