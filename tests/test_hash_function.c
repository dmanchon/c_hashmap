#include "hashmap.h"
#include <assert.h>
#include <string.h>



void test_universal_hash_function() {
    assert(universal_hash("key1", 1024) == universal_hash("key1", 1024));
}


int main(int argc, char* argv[]) {
    test_universal_hash_function();
    return 0;
}