# include "cache.hh"
//#include <cxxopts.hpp>
//#include <algorithm>
#include <pistache/http.h>
#include <pistache/router.h>
//#include <pistache/endpoint.h>
#include <string>

//connect cache.cc anx server.cc in makefile
Cache *cache_ptr;


using namespace std;
using namespace Pistache;

struct Handler : public Http::Handler {
    HTTP_PROTOTYPE(Handler)

    //write methods that interact with cache here
    std::string get_key_value(k,s){
        val_type val = cache_ptr.get(k,s);
        std:: string json = "{ key: " + k + ", value: " + std::to_string(val) + " }"
        return json;
    }

    std::string get_memused(){
        int mem_used = cache_ptr.space_used();
        s_mem_used = std::to_string(mem_used);
        json = "{ memsize: " + s_mem_used + " }"
        return json;
    }

    void put(k,v){
        cache_ptr.set(k,v);
        return;
    }

    void del(k){
        cache_ptr.del(k);
        return;
    }


void onRequest(
            const Http::Request& req, Http::ResponseWriter response) override {

        //parse resource here 
        auto req_string = req.resource(); 
        //loop to compare req_string 
        std::string words[3] = {"", "", ""};
        auto current_word = words[0];
        int i = 1;
        for (i=1;i=length(req_string),i++){
            char current_char = req_string[i];
            if (current_char != "/"){
                current_word += current_char;
            } else{
                current_word = words[i];
                i += 1;
            }
        }

        if (req.method() == Http::Method::Get) {
            using namespace Http;
                if (words[1] == ""){
                    get_memused();
                } else {
                    int v = std::stoi(words[1]);
                    get_key_value(words[0],v);
                }

            //if memsize
            
        else if (req.method() == Http::Method::Put){
              using namespace Http;
            //parse key/k and set in cache
        }

        else if (req.method() == Http::Method::Delete){
              using namespace Http;
            //parse key/k, and delete key
        }

        else if (req.method() == Http::Method::Head){
              using namespace Http;
            //return a header 
        }

        else if (req.method() == Http::Method::Post){
              using namespace Http;
            //stop accepting requests, clean up cache, exit cleanly??
        }

        else {
            //report error 
        }

        //parse string
        //wrtite header (if someone requests memused?)
        //response.send(Http::Code::ok, "string goes here")

};

//"/key/name/value/"



int main(){//argv){
    //string port = argv[1] 
    //int maxmem = argv[2]
    get maxmem from cmd line 
    cache_ptr = new Cache(maxmem);

    Http::listenAndServe<Handler>("*:8090");
    delete cache_ptr;
}
