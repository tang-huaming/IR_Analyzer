#-------------------------------------------------
#
# Project created by QtCreator 2015-12-18T17:06:59
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IR_Analyzer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    basicsettingsdlg.cpp

HEADERS  += mainwindow.h \
    basicsettingsdlg.h

DISTFILES += \
    ChangeLog.txt

RESOURCES += \
    icons.qrc
