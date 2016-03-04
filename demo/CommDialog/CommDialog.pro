#-------------------------------------------------
#
# Project created by QtCreator 2016-03-03T20:57:54
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CommDialog
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
