#include "cache.hh"
#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <string>
#include <pistache/http_headers.h>
#include <pistache/net.h>
#include <pistache/peer.h>
#include <pistache/cookie.h>


//connect cache.cc and server.cc in makefile
Cache *cache_ptr;

using namespace std;
using namespace Pistache;

class Handler : public Http::Handler {
    HTTP_PROTOTYPE(Handler)



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
                    char *character_value = (char*)val;
                    std::string string_value(character_value);
                    std::string json = ("{ key: " + words[1] + ", value: " + string_value + " }");
                    //auto get = Handler.get_key_value(words[1],s);
                    response.send(Http::Code::Ok, json);
                }
        } else if (req.method() == Http::Method::Put) {
            using namespace Http;
                uint32_t size = words[2].size();
                const void* v = words[2].c_str();
                cache_ptr->set(words[1],v,size);
                //Handler.put(words[1],v);

        } else if (req.method() == Http::Method::Delete){
            using namespace Http;
                cache_ptr->del(words[1]);
                //Handler.del(words[1]);

        } else if (req.method() == Http::Method::Head){
            auto head = response.headers();
            //response.send(Http::Code::Ok, head);

        } else if (req.method() == Http::Method::Post){
            using namespace Http;
                exit(0);
        } else {
            exit(-1);
        }
    }
};

int main(int argc, char *argv[]){
    auto maxmem = 32*sizeof(char);
    auto portnum = 2345;
    if (argc = 4){
        int maxmem = atoi(argv[2]);
        portnum = atoi(argv[4]);
    } else if (argc = 2){
        if (argv[1] == "-m"){
            maxmem = atoi(argv[2]);
        } else if (argv[1] == "-t"){
            portnum = atoi(argv[2]);
        }
    }

    Port port(portnum);

    //how many clients?
    int thr = 1;

    cache_ptr = new Cache(maxmem);

    Address addr(Ipv4::any(), portnum);

    cout << "Cores = " << hardware_concurrency() << endl;
    cout << "Using " << thr << " threads" << endl;

    auto server = std::make_shared<Http::Endpoint>(addr);

    auto opts = Http::Endpoint::options()
        .threads(thr)
        .flags(Tcp::Options::InstallSignalHandler);
    server->init(opts);
    server->setHandler(Http::make_handler<Handler>());
    server->serve();

    std::cout << "Shutdowning server" << std::endl;
    server->shutdown();
    delete cache_ptr;
}
