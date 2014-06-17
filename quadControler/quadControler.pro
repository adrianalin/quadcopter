#-------------------------------------------------
#
# Project created by QtCreator 2014-05-02T15:22:10
#
#-------------------------------------------------

QT       += core gui bluetooth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = quadControler
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    joystickwidget.cpp \
    slider.cpp \
    bluetoothhandler.cpp

HEADERS  += mainwindow.h \
    joystickwidget.h \
    slider.h \
    bluetoothhandler.h

FORMS    += mainwindow.ui

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml
