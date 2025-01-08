#include "hashmap.h"
#include <assert.h>
#include <string.h>



void test_deterministic() {
    assert(universal_hash("key1", 1024) == universal_hash("key1", 1024));
}

void test_linear() {
    assert(universal_hash("key1", 1024) < universal_hash("key2", 1024));
}

int main(int argc, char* argv[]) {
    test_deterministic();
    test_linear();
    return 0;
}