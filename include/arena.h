
#ifndef ARENA_H_INCLUDE
#define ARENA_H_INCLUDE

struct arena;

struct arena* arena_create(unsigned int capacity);
void* arena_malloc(struct arena *arena, unsigned int size);
void arena_free(struct arena *arena);

#endif