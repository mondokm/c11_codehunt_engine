#include <fstream>
#include <streambuf>
#include <string>
#include <vector>

#ifndef LIB_UTIL_H
#define LIB_UTIL_H

std::string compile_library(std::string code, std::string lib_path);
std::string wrap_code(std::string header, std::string code);
std::string build_includes(std::vector<std::string>);

#endif