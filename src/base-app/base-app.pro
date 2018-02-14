QT += widgets network testlib
QT -= gui

TARGET = base-app
TEMPLATE = lib

DEFINES += BASEAPP_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    baseapp.cpp \
    date.cpp \
    match.cpp \
    networkmanager.cpp \
    simpleclass.cpp \
    Time.cpp \
    venue.cpp

HEADERS += \
    baseapp.h \
    base-app_global.h \
    match.h \
    networkmanager.h \
    simpleclass.h \
    Time.h \
    venue.cpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
