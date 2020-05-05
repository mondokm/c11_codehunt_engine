# include "dynamic_library.h"

dynamic_library::dynamic_library():handle{nullptr}{}

dynamic_library::dynamic_library(std::string filename){
    handle = dlopen(filename.c_str(), RTLD_NOW);
    if(!handle) throw std::runtime_error{"Couldn't open dynamic librar"};
}

dynamic_library::dynamic_library(dynamic_library&& other){
    handle=other.handle;
    other.handle=nullptr;
}

dynamic_library& dynamic_library::operator=(dynamic_library&& other){
    if(handle!=nullptr) dlclose(handle);
    handle=other.handle;
    other.handle=nullptr;
    return *this;
}

void dynamic_library::close(){
    if(handle!=nullptr) dlclose(handle);
    handle=nullptr;
}

dynamic_library::~dynamic_library(){
    if(handle!=nullptr) dlclose(handle);
}
