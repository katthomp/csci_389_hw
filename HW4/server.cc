# include "cache.hh"
#include <cxxopts.hpp>
#include <algorithm>
#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <string>

//connect cache.cc anx server.cc in makefile

using namespace std;
using namespace Pistache;

struct Handler : public Http::Handler {
    HTTP_PROTOTYPE(Handler)
    Cache* cache_ = nullptr;


    void GET(const Http::Request& request, Http::ResponseWriter writer){
        writer.send(Http::Code::Ok, cache_.get("yohoo"));
    }

    void SET(const Http::Request& request, Http::ResponseWriter writer){
        cache_ = new Cache(requst.maxmemvalue)
    }

    void HEAD(){}
    void PUT()
    void GET_MEMSIZE
    void 
};


private:
    void setupRoutes() {
        using namespace Rest;

        Routes::Post(router, "/record/:name/:value?", Routes::bind(&StatsEndpoint::doRecordMetric, this));
        Routes::Get(router, "/value/:name", Routes::bind(&StatsEndpoint::doGetMetric, this));
        Routes::Get(router, "/ready", Routes::bind(&Generic::handleReady));
        Routes::Get(router, "/auth", Routes::bind(&StatsEndpoint::doAuth, this));

    }
//we need to make sure that cache.cc is associated with a URl of some kind 
//






int main(argv){
    string port = argv[1] 
    int maxmem = argv[2]

    Http::listenAndServe<HelloHandler>("*:"+port);
}
