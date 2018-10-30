#include "cache.hh"
#include <unordered_map>
#include <cassert>
#include <iostream>
#include <list>

using namespace std;

struct Cache::Impl{

    index_type maxmem = 4*sizeof(char); //implementing a Very Small Cache for Testing
    std::unordered_map<std::string, const void*, hash_func> umap;
    std::unordered_map<std::string, unsigned int> space_map;
    int space = 0; 
    hash_func hasher_;
    list<key_type> actual_cache_struct; 

    Impl(hash_func hasher, evictor_type evictor, int maxmem_)

    : umap(0, hasher)
    {
      maxmem = maxmem_;
      umap.max_load_factor(0.5);
    }
    
    void del(key_type key){
      space = space - space_map[key];
      umap.erase(key);
      space_map.erase(key);
      actual_cache_struct.remove(key);
      return;
    }
    //implementing FIFO policy
    void evictor(){
      if (actual_cache_struct.size() == 0){
          cout << "The cache is already empty, what are you doing?\n";
          return;
        }
        key_type k = actual_cache_struct.front(); 
        space = space - space_map[k];
        space_map.erase(k);
        umap.erase(k);
        actual_cache_struct.pop_front();
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
      printf("maxmem: %d\n",maxmem);
      printf("size: %d\n",size);
      if (size > maxmem){
          cout << "Sorry, that item is too large for this cache\n";
          return;
          }
      while (space + size > maxmem){
  
        evictor();
      }
      auto void_val = static_cast<const void*>(value);
      umap[key] = void_val;
      space_map[key] = size;
      space += size; 
      actual_cache_struct.push_back(key);

    }

};

Cache::Cache(index_type maxmem, evictor_type evictor, hash_func hasher)
    :pImpl_(new Impl(hasher,evictor,maxmem))
    {}

Cache::~Cache(){

}

Cache::val_type Cache::get(key_type key, index_type& val_size)const{
  
    return pImpl_->get(key,val_size);
}

Cache::index_type Cache::space_used()const{

    return pImpl_->space_used();
}

void Cache::del(key_type key){
    pImpl_->del(key);
    return;
}

void Cache::set(key_type key, val_type value, index_type size){
    pImpl_->set(key,value,size);
    return;
}



