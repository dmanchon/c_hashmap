#include <stdio.h>
#include "hashmap.h"

int main(int argc, char** argv) {

    struct hashmap *hm = hashmap_create(1024);
    hashmap_set(hm, "key1", "val1");

    const char *s = hashmap_get(hm, "key1");
    printf("key1 = %s\n", s);
    hashmap_free(hm);
}
