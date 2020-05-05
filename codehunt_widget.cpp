#include "codehunt_widget.h"

codehunt_widget::codehunt_widget(std::vector<std::shared_ptr<task_interface>> tasks, QWidget *parent): QWidget(parent), _tasks{std::move(tasks)}{

    it=_tasks.begin();

    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setSpacing(0);

    QFrame *toolbar= new QFrame(this);
    QHBoxLayout *hbox = new QHBoxLayout(toolbar);

    QFrame *textcontainer = new QFrame(toolbar);
    QVBoxLayout *innervbox = new QVBoxLayout(textcontainer);

    tasknum = new QLabel(textcontainer);
    tasknum->setStyleSheet("QLabel {font-weight: bold;}");
    desc = new QLabel("Add 2 numbers",textcontainer);
    desc->setStyleSheet("QLabel { margin-bottom: 10px;}");

    innervbox->addWidget(tasknum);
    innervbox->addWidget(desc);

    QPushButton *run = new QPushButton("Run tests", toolbar);
    run->setFixedWidth(100);

    hbox->addWidget(textcontainer);
    hbox->addWidget(run);

    codefield = new code_field(this);
    area = new QScrollArea(this);
    area->setFrameStyle(QFrame::NoFrame);

    results = new QLabel();
    results->setStyleSheet("QLabel { margin: 10px;}");
    area->setWidget(results);
    
    vbox->addWidget(toolbar);
    vbox->addWidget(codefield);
    vbox->addWidget(area);

    displayRes("");
    loadCurrent();

    connect(run, SIGNAL(clicked()), this, SLOT(buttonPressed()));
}

void codehunt_widget::buttonPressed(){
    if(it==_tasks.end()) return;
    
    std::string code = codefield->getText();
    std::string includes = build_includes((*it)->get_includes());
    std::string wrappedcode = wrap_code((*it)->get_header(),code);

    std::string completecode = includes + (includes.size()>0?"\n":"") +wrappedcode;

    auto res=compile_library(completecode, "./temp.so");
    if(res.size()>0){
        displayRes(res);
    }else{
        auto lib=dynamic_library("./temp.so");
        try{
            if((*it)->test(lib)){
                ++it;
                loadCurrent();
                displayRes("All tests passed, loading next task.");
            } else {
                displayRes("One or more tests failed");
            }
        } catch (const std::exception& e){
            displayRes(e.what());
        }
        lib.close();
    }
}

void codehunt_widget::loadCurrent(){
    if(it<_tasks.end()){
        tasknum->setText("Task "+QString::number((it-_tasks.begin())+1));
        codefield->setHeader((*it)->get_header());
        codefield->setIncludes(build_includes((*it)->get_includes()));
        codefield->clear();
        desc->setText(QString::fromUtf8((*it)->get_desc().c_str()));
    } else {
        displayRes("All tasks completed");
    }
}

void codehunt_widget::displayRes(std::string res){
    results->setText(QString::fromUtf8(res.c_str()));
    results->adjustSize();
    auto size = results->sizeHint();
    if(size.height()<300) area->setFixedSize(area->maximumSize().width(),size.height());
    else area->setFixedSize(area->maximumSize().width(),300);
}