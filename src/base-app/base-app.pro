QT += widgets network testlib
QT -= gui

TARGET = base-app
TEMPLATE = lib

DEFINES += BASEAPP_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    baseapp.cpp \
    simpleclass.cpp

HEADERS += \
    baseapp.h \
    base-app_global.h \
    simpleclass.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
