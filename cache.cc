/* 


*/

#include "cache.hh"

struct Cache::Impl{
    index_type maxmem=32*sizeof(char); //starting by implementing a Very Small Cache for Testing
    void del(key_type key){

    }
    val_type get(key_type key, index_type& val_size)const{

    }
    index_type space_used()const{

    }
    void set(key_type key, val_type value, index_type size){

    }
    key_type key=0;
};

//* Retrieve a pointer to the value associated with key in the cache,
//* or NULL if not found.
//* Sets the actual size of the returned value (in bytes) in val_size.
Cache::Cache(index_type maxmem, evictor_type evictor, hash_func hasher)
    :pImpl_(new Impl())
{}


Cache::val_type Cache::get(key_type key, index_type& val_size)const{
    //need to point to a pointer
    pImpl_->key;
    return 0;
}
//* Compute the total amount of memory used up by all cache values (not keys)
Cache::index_type Cache::space_used()const{
    //unsure of how it's pointing to all of the places in memory
    //very unsure of how to traverse this
    pImpl_->space_used();
    return 0;
}
//* Delete an object from the cache, if it's still there
void Cache::del(key_type key){
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
    return;
}

int main(){

}




