//test1
#include "cache.hh"
#include <cassert>

void test_one() {unsigned int asize = sizeof(unsigned int);

Cache* cache_pointer = new Cache(4,NULL, hash_function);

int* eight = (int*)malloc(sizeof(int));
*eight = 8;

cache_pointer->set("key1",eight,sizeof(unsigned int&));
Cache::val_type get_val = cache_pointer->get("key1",asize);
assert(*(unsigned int*)get_val==8);
cout << "The set and get methods did the thing!\n";
}


int main(){
    test_one()
}
