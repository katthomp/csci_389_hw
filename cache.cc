/* 


*/
#include "cache.hh"
#include <unordered_map>
struct Cache::Impl{
    index_type maxmem=32*sizeof(char); //starting by implementing a Very Small Cache for Testing
    index_type memused=0;
    std::unordered_map<std::string, void*> map_;
    void del(key_type key){
        map_.erase(key);
        return;
    }
    val_type get(key_type key, index_type& val_size) const{
        return map_.find(key);
    }
    index_type space_used()const{
        return memused;
    }
    void set(key_type key, val_type value, index_type size){
        if (size>maxmem){
            printf("This size cannot fit in this cache");
            exit(-1);
        }
        //making sure that the size can fit in the cache
        if ((size+memused)<maxmem){
            map_[key]=value;
            memused+=size;
            maxmem-=size;
            return;
        }
    }
    

};

//* Retrieve a pointer to the value associated with key in the cache,
//* or NULL if not found.
//* Sets the actual size of the returned value (in bytes) in val_size.
Cache::Cache(index_type maxmem, evictor_type evictor, hash_func hasher)
    :pImpl_(new Impl())
{
    
}

Cache::val_type Cache::get(key_type key, index_type& val_size)const{
    //need to point to a pointer
    return pImpl_->get(key, val_size);
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

}




