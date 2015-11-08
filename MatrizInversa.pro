#-------------------------------------------------
#
# Project created by QtCreator 2015-11-08T09:53:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MatrizInversa
TEMPLATE = app


SOURCES += main.cpp\
        Widget.cpp \
    DoubleSpinBoxDelegate.cpp

HEADERS  += Widget.h \
    DoubleSpinBoxDelegate.h

FORMS    += Widget.ui

QMAKE_CXXFLAGS += -std=gnu++14
