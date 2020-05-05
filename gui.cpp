#include <QApplication>
#include <QDesktopWidget>
#include <QScrollArea>
#include <QPushButton>
#include "code_field.h"
#include "task.h"
#include "codehunt_widget.h"

int main( int argc, char **argv )
{
    QApplication app( argc, argv );

    std::vector<std::shared_ptr<task_interface>> tasks;

    auto task1=std::make_shared<task<int(int,int)>>("Write a function that sums two numbers!","int sum(int a, int b)","sum");
    task1->add([](std::function<int(int,int)> f){return f(2,4)==6;});
    task1->add(22,20,2);

    auto task2=std::make_shared<task<int(int,int)>>("Write a function that subtracts b from a!","int sub(int a, int b)","sub");
    task2->add([](std::function<int(int,int)> f){return f(2,4)==-2;});
    task2->add(18,20,2);

    auto task3=std::make_shared<task<double(double,double)>>("Write a function that sums two floating point numbers!","double sum(double a, double b)","sum");
    task3->add([](std::function<double(double,double)> f){return f(2.0,4.0)==6.0;});    
    task3->add(22.0,20.0,2.0);

    auto task4=std::make_shared<task<bool(std::string)>>("Write a function that decides whether a string is a palindrome!","bool palindrome(std::string str)","palindrome",std::initializer_list<std::string>{"string","vector"});
    task4->add([](std::function<bool(std::string)> f){return f("asd")==false;});    
    task4->add(true,"racecar");

    tasks.push_back(task1);
    tasks.push_back(task2);
    tasks.push_back(task3);
    tasks.push_back(task4);

    codehunt_widget ch(tasks);
    ch.resize(800,600);
    ch.show();
    
    return app.exec();
}