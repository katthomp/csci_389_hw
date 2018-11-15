#include "cache.hh"
//#include <cxxopts.hpp>
//#include <algorithm>
#include <pistache/http.h>
#include <pistache/router.h>
//#include <pistache/endpoint.h>
#include <string>
#include <pistache/http_headers.h>

//connect cache.cc anx server.cc in makefile
Cache *cache_ptr;


using namespace std;
using namespace Pistache;

class Handler : public Http::Handler {
    HTTP_PROTOTYPE(Handler)

    //write methods that interact with cache here
    //std::string get_key_value(auto k, auto s){
    //    uint32_t val = cache_ptr->get(k,s);
    //    std:: string json = "{ key: " + k + ", value: " + std::to_string(val) + " }";
     //   return json;
    //}

    //std::string get_memused(){
     //   auto mem_used = cache_ptr->space_used();
    //    auto s_mem_used = std::to_string(mem_used);
    //    auto json = "{ memsize: " + s_mem_used + " }";
    //    return json;
   // }

    //void put(auto k, auto v){
    //    cache_ptr->set(k,v);
    //    return;
    //}

    //void del(auto k){
     //   cache_ptr->del(k);
     //   return;
    //}


void onRequest(const Http::Request& req, Http::ResponseWriter response) override {

        //parse resource here 
        auto req_string = req.resource(); 
        //loop to compare req_string 
        std::string words[3] = {"", "", ""};
        auto current_word = words[0];
        auto first_slash_unimportant = req_string.find("/");
        auto slash_pos_one = req_string.find("/");
        auto slash_pos_two = req_string.find("/");

        if (slash_pos_one != string::npos){
            if (slash_pos_two != string::npos){
                words[1] == req_string.substr(slash_pos_one,slash_pos_two);
                words[2] == req_string.substr(slash_pos_two);
            } else {
                words[1] == req_string.substr(slash_pos_one);
            }
        }

        //for (i=1;i=req_string.length();i++){
         //   char& current_char = req_string[i];
         //   if (current_char.find("/")){
         //      current_word += current_char*;
         //   } else {
         //       current_word = current_word + words[i];
         //       i += 1;
         //   }

        if (req.method() == Http::Method::Get) {
            using namespace Http;
                if (words[1] == ""){
                    auto mem_used = cache_ptr->space_used();
                    auto s_mem_used = std::to_string(mem_used);
                    auto json = ("{ memsize: " + s_mem_used + " }");
                    //auto mem_used = Handler.get_memused();
                    response.send(Http::Code::Ok,json);
                } else {
                    Cache::index_type s;
                    auto val = cache_ptr->get(words[1],s);
                    void* b = const_cast<void*>(val);
                    uint32_t* c = static_cast<uint32_t>(b);
                    std::string* e = static_cast<std::string>(c);
                    std::string json = ("{ key: " + words[1] + ", value: " + e + " }");
                    //auto get = Handler.get_key_value(words[1],s);
                    response.send(Http::Code::Ok, json);
                }
        } else if (req.method() == Http::Method::Put) {
            using namespace Http;
                Cache::index_type s;
                int v_1 = std::stoi(words[2]);
                Cache::val_type v = (Cache::val_type)v_1;
                cache_ptr->set(words[1],v,s);
                //Handler.put(words[1],v);

        } else if (req.method() == Http::Method::Delete){
            using namespace Http;
                cache_ptr->del(words[1]);
                //Handler.del(words[1]);

        } else if (req.method() == Http::Method::Head){
            auto head = req.headers();
            response.send(Http::Code::Ok, head);

        } else if (req.method() == Http::Method::Post){
            using namespace Http;
                exit(0);
              //che k that words[0]==shutdown
              //exit handler 
            //stop accepting requests, clean up cache, exit cleanly??
        } else {
            exit(-1);
        }

        //parse string
        //wrtite header (if someone requests memused?)
        //response.send(Http::Code::ok, "string goes here")
    }
};

//"/key/name/value/"
    


int main(int argc, char *argv[]){//argv){
    //string port = argv[1] 
    //int maxmem = argv[2]
    auto maxmem = 32*sizeof(char);
    auto portnum = 2345;
    if (argc = 4){
        maxmem = (int)argv[2];
        portnum = (int)argv[4];
    } else if (argc = 2){
        if (argv[1] == "-m"){
            maxmem = (int)argv[2];
        } else if (argv[1] == "-t"){
            portnum = (int)argv[2];
        }
    }

    Port port(portnum);

    //how many clients?
    int thr = 1;

    //if (argc >= 2) {
     //   port = std::stol(argv[1]);
    //}

    cache_ptr = new Cache(maxmem);

    Address addr(Ipv4::any(), portnum);

    cout << "Cores = " << hardware_concurrency() << endl;
    cout << "Using " << thr << " threads" << endl;

    auto server = std::make_shared<Http::Endpoint>(addr);

    auto opts = Http::Endpoint::options();
        .threads(thr);
        .flags(Tcp::Options::InstallSignalHandler);
    server->init(opts);
    server->setHandler(Http::make_handler<Handler>());
    server->serve();

    std::cout << "Shutdowning server" << std::endl;
    server->shutdown();
    delete cache_ptr;
}
