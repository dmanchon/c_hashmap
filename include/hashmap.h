
#ifndef HASHMAP_H_INCLUDE
#define HASHMAP_H_INCLUDE

#define LARGE_PRIME 4294967291U
#define SMALL_PRIME 33U

struct hashmap;

unsigned int universal_hash(const char* str_key, unsigned int m);

struct hashmap *hashmap_create(unsigned int capacity);
void hashmap_free(struct hashmap *hm);

unsigned int hashmap_size(const struct hashmap *hm);
const char* hashmap_get(const struct hashmap *hm, const char *key);
void hashmap_set(struct hashmap *hm, const char *key, const char *value);
int hashmap_remove(struct hashmap *hm, const char *key);

#endif