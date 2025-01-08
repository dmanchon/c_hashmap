#include "hashmap.h"
#include "arena.h"
#include <stdlib.h>
#include <string.h>

struct node {
    struct node *next;
    const char* key;
    const char* value;
};

struct hashmap {
    unsigned int capacity;
    unsigned int size;
    struct node** table;
    struct arena *arena;

};

unsigned int universal_hash(const char* str_key, unsigned int m) {
    unsigned int hash = 0;
    for (int i = 0; str_key[i] != '\0'; i++) {
        hash = (hash * SMALL_PRIME + str_key[i]) % LARGE_PRIME;
    }
    return hash % m;
}

struct hashmap *hashmap_create(unsigned int capacity) {
    struct arena *a = arena_create(sizeof(struct node*) * capacity * 32);

    struct hashmap *h = arena_malloc(a, sizeof(struct hashmap));
    h->arena = a;
    h->capacity = capacity;
    h->size = 0;
    h->table = arena_malloc(h->arena, sizeof(struct node*) * capacity);
    
    return h;
}

void hashmap_free(struct hashmap *hm) {
    arena_free(hm->arena);
}


unsigned int hashmap_size(const struct hashmap *hm) {
    return hm->size;
}

const char* hashmap_get(const struct hashmap *hm, const char *key) {
    unsigned int pos = universal_hash(key, hm->capacity);
    
    struct node *ll = hm->table[pos];

    if (ll == NULL) {
        return NULL;
    }

    do {
        if (strcmp(ll->key, key) == 0) {
            return ll->value;
        }
        ll = ll->next;
    } while (ll);

    return NULL;
}

void hashmap_set(struct hashmap *hm, const char *key, const char *value) {
    unsigned int pos = universal_hash(key, hm->capacity);

    struct node *n = arena_malloc(hm->arena, sizeof(struct node));
    n->value = value;
    n->key = key;

    struct node *root = hm->table[pos];

    if (root == NULL) {
        root = n;
    } else {
        struct node *ll = root;

        while (ll->next) {
            ll = ll->next;
        }
        ll->next = n;
    }

    hm->table[pos] = root;
    hm->size++;
}

int hashmap_remove(struct hashmap *hm, const char *key) {
    hashmap_set(hm, key, NULL);
    hm->size--;

    return 0;
}
