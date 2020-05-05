#include "library_util.h"

std::string compile_library(std::string code, std::string lib_path){
    std::ofstream("temp.cpp")<<code;
    std::string cmd="g++ temp.cpp -Wall -shared -fPIC -o "+lib_path+" >& log";
    std::system(cmd.c_str());
    std::ifstream logfile("log");
    return std::string(std::istreambuf_iterator<char>(logfile), std::istreambuf_iterator<char>());
}

std::string wrap_code(std::string header, std::string code){
    return "extern \"C\" {" +header + "{\n" + code + "} }";
}

std::string build_includes(std::vector<std::string> includes){
    std::string ret;
    for(auto incl: includes){
        ret+="#include <"+incl+">\n";
    }
    return ret;
}