QT       += core

QT       -= gui

TARGET = Server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

HEADERS += \
    Text.h \
    textserver.h

win32:LIBS += -lws2_32
