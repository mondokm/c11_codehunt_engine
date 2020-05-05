#include <QDesktopWidget>
#include <QScrollArea>
#include <QPushButton>
#include "code_field.h"
#include "task.h"
#include "library_util.h"

#ifndef CODEHUNT_H
#define CODEHUNT_H

class codehunt_widget: public QWidget{
    Q_OBJECT
    code_field* codefield;
    QLabel *desc;
    QLabel *results;
    QScrollArea *area;
    QLabel *tasknum;
    std::vector<std::shared_ptr<task_interface>> _tasks;
    std::vector<std::shared_ptr<task_interface>>::iterator it;
    void loadCurrent();
    void displayRes(std::string res);
public:
    codehunt_widget(std::vector<std::shared_ptr<task_interface>> _tasks, QWidget *parent=0);
public slots:
    void buttonPressed();
};

#endif