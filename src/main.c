#include <stdio.h>
#include "hashmap.h"



int main(int argc, char** argv) {
    unsigned int hash = universal_hash("hello", 1024);
    printf("Hash: %u\n", hash);

    hash = universal_hash("dani", 1024);
    printf("Hash: %u\n", hash);

    hash = universal_hash("world", 1024);
    printf("Hash: %u\n", hash);

    hash = universal_hash("proga adf adf dadsf fadsf dasf ads asdfdsafadsfasdf fdf ramming", 1024);
    printf("Hash: %u\n", hash);

    struct hashmap *hm = hashmap_create(1024);


    hashmap_set(hm, "datsss", "dani");
    hashmap_set(hm, "hola", "dani");
    hashmap_set(hm, "asdf asdf sadf", "dani");
    hashmap_set(hm, "asdfasdf asd f", "dani");
    
    const char* s = hashmap_get(hm, "datsss1");
    printf("%s ...", s);

    s = hashmap_get(hm, "asdfasdf asd f");
    printf("%s ...", s);


    hashmap_free(hm);

}
