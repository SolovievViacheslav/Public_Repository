#-------------------------------------------------
#
# Project created by QtCreator 2019-11-07T12:03:39
#
#-------------------------------------------------

QT += core gui
QT += serialport
QT +=  network
include(./qextserialport/qextserialport.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = port_sender
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    utils.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
