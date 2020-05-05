#include <iostream>
#include <dlfcn.h>
#include <functional>
#include <fstream>

#ifndef DYNAMIC_LIB_H
#define DYNAMIC_LIB_H

class dynamic_library{
    void* handle;
public:
    dynamic_library();
    dynamic_library(std::string filename);

    template <typename RET, typename ... ARGS>
    std::function<RET(ARGS...)> read_function(std::string funcname){
        return reinterpret_cast<RET(*)(ARGS...)>(dlsym(handle,funcname.c_str()));
    }
    
    dynamic_library(dynamic_library&& other);

    dynamic_library& operator=(dynamic_library&& other);

    dynamic_library(const dynamic_library&) = delete;
    dynamic_library& operator=(const dynamic_library&) = delete;
    
    void close();

    ~dynamic_library();
};

#endif