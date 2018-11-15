
#include "cache.hh"
#include <unordered_map>
#include <cassert>
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include <boost/asio.hpp>
using namespace std;

struct Cache::Impl{

    index_type maxmem = 4*sizeof(char); //implementing a Very Small Cache for Testing
    hash_func hasher_;
    list<key_type> actual_cache_struct; 
    int port= 9080;
    std::string server_name = "rhody_kathy";
    Impl(hash_func hasher, evictor_type evictor, int maxmem_) 
    {
      maxmem = maxmem_;
      
    }
    
    void del(key_type key){
      // char * cstr =new char [request.length()+1];
      // std::strcpy (cstr, request.c_str());
      //requests
      boost::asio::streambuf request;
      std::ostream request_stream(&request);
      request_stream << "DEL " << key << " HTTP/1.0\r\n";
      boost::asio::write(socket, request);
      //response parsing
      boost::asio::streambuf response;
      boost::asio::read_until(socket, response, "\r\n");
      std::istream response_stream(&response);
      std::string http_version;
      response_stream >> http_version;
      unsigned int status_code;
      response_stream >> status_code;
      std::string status_message;
      std::getline(response_stream, status_message);
    if (!response_stream || http_version.substr(0, 5) != "HTTP/")
    {
      std::cout << "Invalid response\n";
      return ;
    }
    if (status_code != 200)
    {
      std::cout << "Response returned with status code " << status_code << "\n";
      return ;
    }
      return;

    }
    //implementing FIFO policy
    void evictor(){
      return;
    }

    Cache::val_type get(key_type key, index_type& val_size){

      //std::string get_key= ur
      boost::asio::streambuf request;
      std::ostream request_stream(&request);
      request_stream << "GET " << key << " HTTP/1.0\r\n";
      // std::string request="GET "+key+" HTTP/1.0\r\n";
      // char * cstr =new char [request.length()+1];
      // std::strcpy (cstr, request.c_str());
      boost::asio::write(socket, request);
      boost::asio::streambuf response;
      boost::asio::read_until(socket, response, "\r\n");
      std::istream response_stream(&response);
      std::string http_version;
      response_stream >> http_version;
      unsigned int status_code;
      response_stream >> status_code;
      std::string status_message;
      std::getline(response_stream, status_message);
    if (!response_stream || http_version.substr(0, 5) != "HTTP/")
    {
      std::cout << "Invalid response\n";
      return 0;
    }
    if (status_code != 200)
    {
      std::cout << "Response returned with status code " << status_code << "\n";
      return 0;
    }
      return 0;
    }

    int space_used(){
      return 0;
    }

    void set(key_type key, val_type value, index_type size){
      
      // char * cstr =new char [request.length()+1];
      // std::strcpy (cstr, request.c_str());
      boost::asio::streambuf request;
      std::ostream request_stream(&request);
      request_stream << "SET "<<key<< " HTTP/1.0\r\n";
      boost::asio::write(socket, request);
      //getting response
      boost::asio::streambuf response;
      boost::asio::read_until(socket, response, "\r\n");
      std::istream response_stream(&response);
      std::string http_version;
      response_stream >> http_version;
      unsigned int status_code;
      response_stream >> status_code;
      std::string status_message;
      std::getline(response_stream, status_message);
    if (!response_stream || http_version.substr(0, 5) != "HTTP/")
    {
      std::cout << "Invalid response\n";
      return ;
    }
    if (status_code != 200)
    {
      std::cout << "Response returned with status code " << status_code << "\n";
      return ;
    }
      return;
    }
    void head_get(key_type key){ //need a special thing
      boost::asio::streambuf request;
     std::ostream request_stream(&request);
      request_stream<<"POST "<<key<<" HTTP/1.0\r\n";
      // char * cstr =new char [request.length()+1];
      // std::strcpy (cstr, request.c_str());
      boost::asio::write(socket, request);
      std::string header;

      boost::asio::streambuf response;
      boost::asio::read_until(socket, response, "\r\n");
      std::istream response_stream(&response);
      while (std::getline(response_stream, header) && header != "\r"){
        std::cout << header << "\n";
        std::cout << "\n";
      }
      
      return;
    }

    void get_memsize(std::string memsize){
      boost::asio::streambuf request;
      std::ostream request_stream(&request);
      request_stream<<"GET "<<memsize<<" HTTP/1.0\r\n";
      // char * cstr =new char [request.length()+1];
      // std::strcpy (cstr, request.c_str());
      boost::asio::write(socket, request);

      boost::asio::streambuf response;
      boost::asio::read_until(socket, response, "\r\n");
      return;
    }
    void shutdown(std::string req){
      boost::asio::streambuf request;
      std::ostream request_stream(&request);
      request_stream<<"POST "<<req<<" HTTP/1.0\r\n";
      // char * cstr =new char [request.length()+1];
      // std::strcpy (cstr, request.c_str());
      boost::asio::write(socket, request);
      boost::asio::streambuf response;
      boost::asio::read_until(socket, response, "\r\n");

      return;
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



