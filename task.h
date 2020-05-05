#include<string>
#include<functional>
#include<iostream>
#include<vector>
#include<initializer_list>
#include"dynamic_library.h"

#ifndef TASK_H
#define TASK_H

class task_interface{
public:
    virtual bool test(dynamic_library&)=0;
    virtual std::string get_header()=0;
    virtual std::string get_desc()=0;
    virtual std::string get_name()=0;
    virtual std::vector<std::string> get_includes()=0;
};

template <typename SIGNATURE>
class task;

template <typename RET, typename ... ARGS>
class task<RET(ARGS...)>: public task_interface{
    std::string _desc;
    std::string _header;
    std::string _name;
    std::vector<std::string> _includes;
    std::vector<std::function<bool(std::function<RET(ARGS...)>)>> testcases;
public:
    task(std::string desc, std::string header, std::string name, std::initializer_list<std::string> includes={}):_desc{std::move(desc)}, _header{std::move(header)}, _name{std::move(name)}, _includes{std::move(includes)}{}

    void add(std::function<bool(std::function<RET(ARGS...)>)> f){
        testcases.push_back(std::move(f));
    }

    void add(RET ret, ARGS ... args){
        add([=, ret{std::move(ret)}](std::function<RET(ARGS...)> f){return f(args...)==ret;});
    }

    virtual bool test(dynamic_library& lib){
        auto func=lib.read_function<RET,ARGS...>(_name);
        for(auto testcase:testcases){
            if(!testcase(func)) return false;
        }
        return true;
    }

    virtual std::string get_header(){
        return _header;
    }

    virtual std::string get_desc(){
        return _desc;
    }

    virtual std::string get_name(){
        return _name;
    }

    virtual std::vector<std::string> get_includes(){
        return _includes;
    }
};

#endif