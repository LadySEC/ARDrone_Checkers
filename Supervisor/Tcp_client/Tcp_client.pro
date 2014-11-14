#-------------------------------------------------
#
# Project created by QtCreator 2014-11-11T16:10:46
#
#-------------------------------------------------

QT       += core gui
QT       += network
CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tcp_client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        client.cpp

HEADERS  += mainwindow.h \
            client.h

FORMS    += mainwindow.ui
