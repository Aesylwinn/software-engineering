QT += widgets network testlib
QT -= gui

TARGET = base-app
TEMPLATE = lib

DEFINES += BASEAPP_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    baseapp.cpp \
    match.cpp \
    simpleclass.cpp \
    Time.cpp

HEADERS += \
    baseapp.h \
    base-app_global.h \
    match.h \
    simpleclass.h
    Time.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
