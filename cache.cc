
#include "cache.hh"
#include <unordered_map>
using namespace std;

struct Cache::Impl{
    index_type maxmem=32*sizeof(char); //starting by implementing a Very Small Cache for Testing
    std::unordered_map<std::string, const void*> umap;
    std::unordered_map<std::string, unsigned int> space_map;
    int space = 0;
    hash_func hasher_;
    evictor_type evictor_;

    Impl(hash_func hasher, evictor_type evictor, int maxmem)

    : hasher_(hasher), evictor_(evictor)
    {
    //other stuff to initialize
    }

    void del(key_type key){
      umap.erase(key);
      return;
    }

    val_type get(key_type key, index_type& val_size){
      val_size = space_map[key];
      return umap[key];
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
        printf("no more space!");
      }
    


    }
    

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

    return pImpl_->get(key, val_size);

}
//* Compute the total amount of memory used up by all cache values (not keys)
Cache::index_type Cache::space_used()const{
    //unsure of how it's pointing to all of the places in memory
    //very unsure of how to traverse this
    return pImpl_->space_used();}
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


    // if (pImpl_->space_used())>=pImpl_->maxmem{
    //     for pImpl_->space_used()>=maxmem{
    //         pImpl_->del(key_type key);
    //     }
    // }
    pImpl_->set(key,value,size);
    return;
}

int main(){

  Cache* cache_pointer = new Cache(32, NULL, NULL);
}
