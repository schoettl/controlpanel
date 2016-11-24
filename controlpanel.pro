#-------------------------------------------------
#
# Project created by QtCreator 2016-11-03T13:58:32
#
#-------------------------------------------------

QT       += core gui

CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = controlpanel
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
