#include "hashmap.h"
#include "arena.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ALLOWED_OVERHEAD 5

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
    unsigned int (*hashfn) (const char*, unsigned int);
};

unsigned int universal_hash(const char* str_key, unsigned int m) {
    const unsigned int LARGE_PRIME = 4294967291U;
    const unsigned int SMALL_PRIME = 33U;
    unsigned int hash = 0;
    for (int i = 0; str_key[i] != '\0'; i++) {
        hash = (hash * SMALL_PRIME + str_key[i]) % LARGE_PRIME;
    }
    return hash % m;
}

unsigned int constant_hash(const char* key, unsigned int m) {
    return 42;
}

unsigned int fnv1a_hash(const char* str_key, unsigned int m) {
    const unsigned int FNV_OFFSET_BASIS = 2166136261U;
    const unsigned int FNV_PRIME = 16777619U;

    unsigned int hash = FNV_OFFSET_BASIS;
    for (int i = 0; str_key[i] != '\0'; i++) {
        hash ^= (unsigned char)str_key[i];
        hash *= FNV_PRIME;
    }
    return hash % m;
}

struct hashmap *hashmap_create(unsigned int capacity) {
    struct arena *a = arena_create(sizeof(struct node*) * capacity * (1+ALLOWED_OVERHEAD));

    struct hashmap *h = arena_malloc(a, sizeof(struct hashmap));
    h->arena = a;
    h->capacity = capacity;
    h->size = 0;
    h->table = arena_malloc(h->arena, sizeof(struct node*) * capacity);
    h->hashfn = fnv1a_hash;
    return h;
}

struct hashmap *hashmap_create_with_custom_hash_fn(unsigned int capacity, unsigned int (*fn) (const char*, unsigned int)) {
    struct hashmap *h = hashmap_create(capacity);
    h->hashfn = fn;
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
    assert(n != NULL);

    n->value = value;
    n->key = key;
    
    struct node *root = hm->table[pos];

    if (root == NULL) {
        root = n;
    } else {
        struct node *ll = root;

        while (ll->next) {
            if (strcmp(ll->key, key) == 0) {
                ll->value = value;
                return;
            }
            ll = ll->next;
        }
        
        ll->next = n;
    }

    hm->table[pos] = root;
    hm->size++;
}

void hashmap_remove(struct hashmap *hm, const char *key) {
    unsigned int pos = universal_hash(key, hm->capacity);

    struct node *n = arena_malloc(hm->arena, sizeof(struct node));
    struct node *root = hm->table[pos];

    if (root && root->next) {
        struct node *ll = root;

        while (ll->next) {
            if (strcmp(ll->key, key) == 0) {
                ll = ll->next;
                return;
            }
            ll = ll->next;
        }
    } else {
        root = NULL;
    }

    hm->table[pos] = root;
    hm->size--;
}
