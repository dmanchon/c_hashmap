#include <stdio.h>
#include "hashmap.h"

unsigned int constant_hash(const char* key, unsigned int m) {
    return 4;
}

int main(int argc, char** argv) {

    // test hashing
    unsigned int hash = universal_hash("hello", 1024);
    printf("Hash: %u\n", hash);

    hash = universal_hash("dani", 1024);
    printf("Hash: %u\n", hash);

    hash = universal_hash("world", 1024);
    printf("Hash: %u\n", hash);

    hash = universal_hash("proga adf adf dadsf fadsf dasf ads asdfdsafadsfasdf fdf ramming", 1024);
    printf("Hash: %u\n", hash);

    // test w/o collisions
    struct hashmap *hm = hashmap_create(1024);
    hashmap_set(hm, "datsss", "dani");
    hashmap_set(hm, "hola", "dani");
    hashmap_set(hm, "asdf asdf sadf", "dani");
    hashmap_set(hm, "asdfasdf asd f", "dani");
    
    const char* s = hashmap_get(hm, "datsss1");
    printf("%s ...", s);

    s = hashmap_get(hm, "asdfasdf asd f");
    printf("%s ...", s);

    // test collisions
    struct hashmap *hm_ch = hashmap_create_with_custom_hash_fn(1024, constant_hash);
    hashmap_set(hm_ch, "datsss", "dani");
    hashmap_set(hm_ch, "hola", "dani");
    hashmap_set(hm_ch, "asdf asdf sadf", "dani");
    hashmap_set(hm_ch, "asdfasdf asd f", "dani");
    
    s = hashmap_get(hm_ch, "datsss1");
    printf("%s ...", s);

    s = hashmap_get(hm_ch, "asdfasdf asd f");
    printf("%s ...", s);

    hashmap_free(hm);
    hashmap_free(hm_ch);
}
