#include "hashmap.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>


void test_set_and_keys() {
    // test w/o collisions
    struct hashmap *hm = hashmap_create(1024);
    assert(hm != NULL);

    hashmap_set(hm, "key1", "val1");
    hashmap_set(hm, "key2", "val2");
    hashmap_set(hm, "key3", "val3");
    hashmap_set(hm, "key4", "val4");
    const char* s = hashmap_get(hm, "key1");
    assert(s != NULL);
    assert(strcmp("val1", s) == 0);

    hashmap_free(hm);
}


void test_get_not_found_keys() {
    // test w/o collisions
    struct hashmap *hm = hashmap_create(1024);
    assert(hm != NULL);

    const char* s = hashmap_get(hm, "key1");
    assert(s == NULL);
    
    hashmap_set(hm, "key2", "val4");
    s = hashmap_get(hm, "key1");
    assert(s == NULL);
    
    hashmap_free(hm);
}

int main(int argc, char* argv[]) {
    test_set_and_keys();
    test_get_not_found_keys();
    return 0;
}