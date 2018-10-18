
#include "cache.hh"
#include <unordered_map>
#include <cassert>
#include <iostream>

using namespace std;

struct Cache::Impl{
/*
    struct MyHasherWrapper {
      index_type operator()(key_type key) const {
        return hasher_(key);
      }
    };
*/
    index_type maxmem=32*sizeof(char); //starting by implementing a Very Small Cache for Testing
    std::unordered_map<std::string, const void*, hash_func> umap;
    std::unordered_map<std::string, unsigned int> space_map;
    int space = 0;
    evictor_type evictor_;
    hash_func hasher_;

    Impl(hash_func hasher, evictor_type evictor, int maxmem)

    : umap(0, hasher), evictor_(evictor)
    {
      umap.max_load_factor(0.5);
    //other stuff to initialize
    //set max_load_factor for unordered map! (to 0.5)
    //
    }

    void del(key_type key){
      space = space - space_map[key];
      umap.erase(key);
      return;
    }

    val_type get(key_type key, index_type& val_size){
      if (umap.count(key) == 0){
        return NULL;
      }
      else {
      val_size = space_map[key];
      return umap[key];
      }
    }

    index_type space_used(){
      return space;

    }

    void set(key_type key, val_type value, index_type size){
      if (space + size <= maxmem){
        auto void_val = static_cast<const void*>(value);
        umap[key] = void_val;
        space_map[key] = size;
        space += size;
      } else {
        //call evictor policy here!!!
        printf("no more space!");
      }
    
    }

    key_type key=0;
};

//* Retrieve a pointer to the value associated with key in the cache,
//* or NULL if not found.
//* Sets the actual size of the returned value (in bytes) in val_size.
Cache::Cache(index_type maxmem, evictor_type evictor, hash_func hasher)
    :pImpl_(new Impl(hasher,evictor,maxmem))
    {}

Cache::~Cache(){

}

Cache::val_type Cache::get(key_type key, index_type& val_size)const{
    //need to point to a pointer
    return pImpl_->get(key,val_size);
}
//* Compute the total amount of memory used up by all cache values (not keys)
Cache::index_type Cache::space_used()const{
    //unsure of how it's pointing to all of the places in memory
    //very unsure of how to traverse this
    return pImpl_->space_used();
}
//* Delete an object from the cache, if it's still there
void Cache::del(key_type key){
    pImpl_->del(key);
    return;
}
//* Add a <key, value> pair to the cache.
//* If key already exists, it will overwrite the old value.
//* Both the key and the value are to be deep-copied (not just pointer copied).
//* If maxmem capacity is exceeded, sufficient values will be removed
//* from the cache to accomodate the new value.
void Cache::set(key_type key, val_type value, index_type size){
    pImpl_->set(key,value,size);
    return;
}

int main(){
  hash<string> hash_function;  

  unsigned int asize = sizeof(unsigned int);

  Cache* cache_pointer = new Cache(32,NULL, hash_function);

  int* eight = (int*)malloc(sizeof(int));
  *eight = 8;

  cache_pointer->set("key1",eight,sizeof(unsigned int&));
  Cache::val_type get_val = cache_pointer->get("key1",asize);
  assert(*(unsigned int*)get_val==8);
  cout << "The set and get methods did the thing!\n";

  cache_pointer->del("key1");
  Cache::val_type get_val_del = cache_pointer->get("key1",asize);
  assert((unsigned int*)get_val_del==NULL);
  cout << "The del method did the thing!\n";  

  //add like 20 things and check size
 //check space used
}
