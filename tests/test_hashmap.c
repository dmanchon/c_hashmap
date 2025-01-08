#include "hashmap.h"
#include <assert.h>
#include <string.h>


void test_set_keys() {
    // test w/o collisions
    struct hashmap *hm = hashmap_create(1024);
    assert(hm != NULL);

    hashmap_set(hm, "key1", "val1");

    const char* s = hashmap_get(hm, "key1");
    assert(s != NULL);
    assert(strcmp("val1", s) == 0);

    hashmap_free(hm);
}


int main(int argc, char* argv[]) {
    test_set_keys();
    return 0;
}