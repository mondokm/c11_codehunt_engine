#include <QTextEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QFrame>
#include <string>

#ifndef CODE_FIELD_H
#define CODE_FIELD_H

class code_field: public QFrame{
    QTextEdit *edit;
    QLabel *includes;
    QLabel *header;
    QLabel *end;
public:
    code_field(QWidget *parent);
    std::string getText();
    void setHeader(std::string header);
    void setIncludes(std::string header);
    void clear();
};

#endif