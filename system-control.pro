#-------------------------------------------------
#
# Project created by QtCreator 2016-11-03T13:58:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = system-control
TEMPLATE = app


SOURCES += main.cpp\
    maindialog.cpp \
    buttonconfig.cpp \
    mybutton.cpp

HEADERS  += maindialog.h \
    buttonconfig.h \
    mybutton.h

FORMS    += maindialog.ui

RESOURCES += \
    res.qrc
