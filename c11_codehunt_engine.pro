######################################################################
# Automatically generated by qmake (3.1) Sat May 2 20:33:42 2020
######################################################################

TEMPLATE = app
TARGET = c11_codehunt_engine
INCLUDEPATH += .

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += dynamic_library.h task.h code_field.h library_util.h codehunt_widget.h
SOURCES += gui.cpp code_field.cpp codehunt_widget.cpp library_util.cpp dynamic_library.cpp
QMAKE_LFLAGS += -ldl
QT += widgets
