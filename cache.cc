
#include "cache.hh"
#include <unordered_map>
#include <cassert>
#include <iostream>
#include <list>
<<<<<<< HEAD
=======

>>>>>>> refs/remotes/origin/master
using namespace std;

struct Cache::Impl{
/*
    struct MyHasherWrapper {
      index_type operator()(key_type key) const {
        return hasher_(key);
      }
    };
*/

    const index_type maxmem = 32*sizeof(char); //starting by implementing a Very Small Cache for Testing
    std::unordered_map<std::string, const void*, hash_func> umap;
    std::unordered_map<std::string, unsigned int> space_map;
    int space = 0; //unsure if we need this, because we can just call .size for unordered map
    hash_func hasher_;
    list<key_type> actual_cache_struct; //actually how the cache is structured, I think. 
    Impl(hash_func hasher, evictor_type evictor, int maxmem)

    : umap(0, hasher)
    {
      umap.max_load_factor(0.5);
      actual_cache_struct.resize(maxmem);
      //space_map.resize(maxmem);
    //other stuff to initialize
    }
    void del(key_type key){
      space = space - space_map[key];
      umap.erase(key);
      actual_cache_struct.remove(key);
      return;
    }
    //implementing FIFO policy, will make a new file with LRU
    void evictor(){
        key_type k = actual_cache_struct.front(); //get key from front of actual_cache_struct
        space = space - space_map[k];
        space_map.erase(k);
        actual_cache_struct.pop_front(); //ideally, would use del here, but, unsure of how to make it work
        return;
    }
    // double load_factor(unordered_map space_map, index_type maxmem){
    //     if (space_map.empty()){
    //         return 0;
    //     }
    //     double load_factor=space_map.size()/maxmem;
    //     return load_factor;
    // }
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
        index_type space=space_used();
      while (space + size > maxmem){
        evictor();
      }
      auto void_val = static_cast<const void*>(value);
      umap[key] = void_val;
      space_map[key] = size;
      space += size; 
    }

    //key_type key=0;
};

//* Retrieve a pointer to the value associated with key in the cache,
//* or NULL if not found.
//* Sets the actual size of the returned value (in bytes) in val_size.
Cache::Cache(index_type maxmem, evictor, hash_func hasher)
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

/*
So, my data is itself void* containers of memory, which are indexed by keys. But right now there
is no organization over the keys themselves. I need to make some sort of linked structure to implement FIFO, and 
later to implement LRU.
*/
