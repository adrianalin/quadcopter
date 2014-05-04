#-------------------------------------------------
#
# Project created by QtCreator 2014-05-02T15:22:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = quadControler
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    joystickwidget.cpp \
    slider.cpp

HEADERS  += mainwindow.h \
    joystickwidget.h \
    slider.h

FORMS    += mainwindow.ui
