#include "cache.hh"
#include <cassert>
#include <iostream>

using namespace std;

void test_one() {

    hash<string> hash_function;

    unsigned int asize = sizeof(unsigned int);

    Cache* cache_pointer = new Cache(32,NULL, hash_function);

    int* eight = (int*)malloc(sizeof(int));
    *eight = 8;

    cache_pointer->set("key1",eight,sizeof(unsigned int&));
    Cache::val_type get_val = cache_pointer->get("key1",asize);
    assert(*(unsigned int*)get_val==8);
    cout << "The set and get methods did the thing!\n";

    free(eight);
    return;
}

void test_two(){

    hash<string> hash_function;

    Cache* cache_pointer = new Cache(4,NULL, hash_function);

    unsigned int asize = sizeof(unsigned int);

    int* six = (int*)malloc(sizeof(int));
    *six = 6;

    cache_pointer->del("key1");
    Cache::val_type get_val_del = cache_pointer->get("key1",asize);
    assert((unsigned int*)get_val_del==NULL);
    cout << "The del method did the thing!\n";

    free(six);
    return;

}

void test_three(){

    hash<string> hash_function;

    Cache* cache_pointer = new Cache(4,NULL, hash_function);

    unsigned int asize = sizeof(unsigned int);

    int* six = (int*)malloc(sizeof(int));
    *six = 6;

    int* eight = (int*)malloc(sizeof(int));
    *eight = 8;

    cache_pointer->set("key1",eight,sizeof(unsigned int&));
    Cache::val_type get_val = cache_pointer->get("key1",asize);

    cache_pointer->del("key1");
    Cache::val_type get_val_del = cache_pointer->get("key1",asize);

    cache_pointer->set("key1",six,sizeof(unsigned int&));
    Cache::val_type get_va = cache_pointer->get("key1",asize);
    assert(*(unsigned int*)get_va == 6);
    cout << "Deleting and replacing a key works!\n";

    free(six);
    free(eight);
}

void test_four(){

    hash<string> hash_function;

    Cache* cache_pointer = new Cache(4,NULL, hash_function);

    unsigned int asize = sizeof(unsigned int);

    int* six = (int*)malloc(sizeof(int)); 
    *six = 6;

    int* eight = (int*)malloc(sizeof(int));
    *eight = 8;

    cache_pointer->set("key1",six,sizeof(unsigned int&));

    cache_pointer->set("key2",eight,sizeof(unsigned int&));
  
    Cache::val_type get_val = cache_pointer->get("key1",asize);
      
    assert(get_val == NULL);
    cout << "the evictor worked! \n";

    free(six);
    free(eight);
}

void test_five(){
    hash<string> hash_function;

    Cache* cache_pointer = new Cache(4,NULL, hash_function);
    
    int* eight = (int*)malloc(sizeof(int));
    *eight = 8;

    cache_pointer->set("key1",eight,sizeof(unsigned int&));

    int s_p = cache_pointer->space_used() ;
    assert(s_p==4);
    cout << "space_used worked!\n";

}

void test_six(){
    hash<string> hash_function;

    Cache* cache_pointer = new Cache(2,NULL, hash_function);

    unsigned int asize = sizeof(unsigned int);

    int* six = (int*)malloc(sizeof(int)); 
    *six = 6;

    cache_pointer->set("key1",six,sizeof(unsigned int&));

    Cache::val_type get_val = cache_pointer->get("key1",asize);

    assert(get_val == NULL);
    cout << "checking that we can't add a value that's too big works!\n";
    
    free(six);

}


int main(){
    test_one();
    test_two();
    test_three();
    test_four();
    test_five();
    test_six();

    return 0;
}

