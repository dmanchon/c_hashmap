#include <stdio.h>
#include "hashmap.h"

unsigned int constant_hash(const char* key, unsigned int m) {
    return 4;
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

int main(int argc, char** argv) {

    // test hashing
    unsigned int hash = universal_hash("key1", 1024);
    printf("Hash: %u\n", hash);
    hash = universal_hash("key2", 1024);
    printf("Hash: %u\n", hash);
    hash = universal_hash("key3", 1024);
    printf("Hash: %u\n", hash);
    hash = universal_hash("key4", 1024);
    printf("Hash: %u\n", hash);

    hash = fnv1a_hash("key1", 1024);
    printf("Hash: %u\n", hash);
    hash = fnv1a_hash("key2", 1024);
    printf("Hash: %u\n", hash);
    hash = fnv1a_hash("key3", 1024);
    printf("Hash: %u\n", hash);
    hash = fnv1a_hash("key4", 1024);
    printf("Hash: %u\n", hash);

    // test w/o collisions
    struct hashmap *hm = hashmap_create(1024);
    hashmap_set(hm, "key1", "val1");
    hashmap_set(hm, "key2", "val2");
    hashmap_set(hm, "key3", "val3");
    hashmap_set(hm, "key4", "val4");

    const char* s = hashmap_get(hm, "notfound");
    printf("notfound = %s\n", s);

    s = hashmap_get(hm, "key3");
    printf("key3 = %s\n", s);

    hashmap_remove(hm, "key3");
    s = hashmap_get(hm, "key3");
    printf("key3 = %s\n", s);
    s = hashmap_get(hm, "key4");
    printf("key4 = %s\n", s);

    // test collisions
    struct hashmap *hm_ch = hashmap_create_with_custom_hash_fn(1024, constant_hash);
    hashmap_set(hm_ch, "key1", "val1");
    hashmap_set(hm_ch, "key2", "val2");
    hashmap_set(hm_ch, "key3", "val3");
    hashmap_set(hm_ch, "key4", "val4");

    s = hashmap_get(hm_ch, "notfound");
    printf("notfound = %s\n", s);

    s = hashmap_get(hm_ch, "key3");
    printf("key3 = %s\n", s);
    hashmap_remove(hm_ch, "key3");
    s = hashmap_get(hm_ch, "key3");
    printf("key3 = %s\n", s);
    s = hashmap_get(hm_ch, "key4");
    printf("key4 = %s\n", s);


    hashmap_free(hm);
    hashmap_free(hm_ch);
}
