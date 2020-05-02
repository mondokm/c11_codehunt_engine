#include <iostream>
#include <dlfcn.h>
#include <functional>
#include <fstream>
#include <cassert>
#include <vector>
#include "task.h"
#include "dynamic_library.h"

class testing_env{

};

bool testcase(std::function<int(int,int)> f){
    return f(1,2)==3;
}

auto prog=R"~(
    extern "C" {
        int add(int a, int b){
            return a+b;
        }
    }
)~";

int main(){
    std::ofstream("temp.cpp")<<prog;
    std::system("g++ -Wall -shared -fPIC -o add.so temp.cpp");

    dynamic_library add_so{"./add.so"};
    
    task<int(int,int)> task1{"Write a function that adds two numbers.","int add(int a, int b)","add"};
    task1.add(testcase);
    task1.add([](std::function<int(int,int)> f){return f(2,4)==6;});
    task1.add(22,20,2);
    task1.test(add_so);
}