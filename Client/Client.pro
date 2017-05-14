#-------------------------------------------------
#
# Project created by QtCreator 2017-05-09T17:56:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    textclient.cpp \
    textclient.cpp

HEADERS  += \
    mainwindow.h \
    textclient.h \
    textclient.h

FORMS    += \
    mainwindow.ui

win32:LIBS += -lws2_32

