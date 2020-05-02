#include <iostream>
#include <dlfcn.h>
#include <functional>
#include <fstream>

#ifndef DYN_LIB_H
#define DYN_LIB_H

class dynamic_library{
    void* handle;
public:
    dynamic_library(std::string filename){
        handle = dlopen(filename.c_str(), RTLD_NOW);
        if(!handle) throw std::runtime_error{"Couldn't open dynamic librar"};
    }
    template <typename RET, typename ... ARGS>
    std::function<RET(ARGS...)> read_function(std::string funcname){
        return reinterpret_cast<RET(*)(ARGS...)>(dlsym(handle,funcname.c_str()));
    }
    
    dynamic_library(dynamic_library&& other){
        handle=other.handle;
        other.handle=nullptr;
    }

    dynamic_library(const dynamic_library&) = delete;
    dynamic_library& operator=(const dynamic_library&) = delete;
    dynamic_library& operator=(dynamic_library&&) = delete;
    
    ~dynamic_library(){
        if(handle!=nullptr) dlclose(handle);
    }
};

#endif