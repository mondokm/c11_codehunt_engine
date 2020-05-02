#include<string>
#include<functional>
#include<iostream>
#include<vector>
#include"dynamic_library.h"

#ifndef TASK_H
#define TASK_H

class task_interface{
    void test(dynamic_library);
};

template <typename ... ARGS>
class task;

template <typename RET, typename ... ARGS>
class task<RET(ARGS...)>: public task_interface{
    std::string _desc;
    std::string _header;
    std::string _name;
    std::vector<std::function<bool(std::function<RET(ARGS...)>)>> testcases;
public:
    task(std::string desc, std::string header, std::string name):_desc{desc},_header{header}, _name{name}{};

    void add(std::function<bool(std::function<RET(ARGS...)>)> f){
        testcases.push_back(f);
    }

    void add(RET ret, ARGS ... args){
        add([=](std::function<RET(ARGS...)> f){return f(args...)==ret;});
    }

    void test(dynamic_library& lib){
        auto func=lib.read_function<RET,ARGS...>(_name);
        for(auto testcase:testcases){
            std::cout<<testcase(func)<<std::endl;
        }
    }

    std::string get_header(){
        return _header;
    }

    std::string get_desc(){
        return _desc;
    }

    std::string get_name(){
        return _name;
    }
};

#endif