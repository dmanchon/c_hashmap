
#ifndef HASHMAP_H_INCLUDE
#define HASHMAP_H_INCLUDE

struct hashmap;

unsigned int universal_hash(const char* str_key, unsigned int m);

struct hashmap *hashmap_create(unsigned int capacity);
struct hashmap *hashmap_create_with_custom_hash_fn(unsigned int capacity, unsigned int (*fn) (const char*, unsigned int));

void hashmap_free(struct hashmap *hm);

unsigned int hashmap_size(const struct hashmap *hm);
const char* hashmap_get(const struct hashmap *hm, const char *key);
void hashmap_set(struct hashmap *hm, const char *key, const char *value);
void hashmap_remove(struct hashmap *hm, const char *key);

#endif