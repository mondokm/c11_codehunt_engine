#include "code_field.h"

code_field::code_field(QWidget *parent=0): QFrame(parent){
    this->setStyleSheet("QFrame {background-color : black;}");

    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setSpacing(0);

    includes = new QLabel("", this);
    includes->setStyleSheet("QLabel {background-color : black; color:white; font: 11pt monospace;}");

    header = new QLabel("int add(int a, int b) {",this);
    header->setStyleSheet("QLabel {background-color : black; color:white; font: 11pt monospace;}");

    edit = new QTextEdit(this);
    edit->setFrameStyle(QFrame::NoFrame);
    edit->setStyleSheet("QTextEdit {padding-left:10; color: white; background-color: black; font: 11pt monospace;}");
    edit->setTabStopDistance(QFontMetrics(edit->font()).horizontalAdvance('a')*4);

    end = new QLabel("}",this);
    end->setStyleSheet("QLabel {background-color : black; color:white; font: 11pt monospace;}");

    vbox->addWidget(includes);
    vbox->addWidget(header);
    vbox->addWidget(edit);
    vbox->addWidget(end);
}

std::string code_field::getText(){
    return edit->toPlainText().toStdString();
}

void code_field::setHeader(std::string headertext){
    header->setText(QString::fromUtf8((headertext+" {").c_str()));
}

void code_field::setIncludes(std::string includetext){
    includes->setText(QString::fromUtf8(includetext.c_str()));
    if(includetext.size()>0) includes->show();
    else includes->hide();
}

void code_field::clear(){
    edit->clear();
}
