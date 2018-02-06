QT       += widgets network testlib

QT       -= gui

TARGET = base-app
TEMPLATE = lib

DEFINES += BASEAPP_LIBRARY

SOURCES += baseapp.cpp

HEADERS += baseapp.h\
        base-app_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
