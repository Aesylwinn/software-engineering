QT       += widgets network testlib

QT       -= gui

TARGET = base-app
TEMPLATE = lib

DEFINES += BASEAPP_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += baseapp.cpp \
    Time.cpp \
    match.cpp

HEADERS += baseapp.h\
        base-app_global.h \
        Time.h \
    match.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
