#-------------------------------------------------
#
# Project created by QtCreator 2018-02-07T14:37:11
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DLG_BK-AVR128
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
        utils.cpp \
        build_time.cpp

HEADERS  += mainwindow.h \
    utils.h

FORMS    += mainwindow.ui
