QT += widgets network testlib
QT -= gui
CONFIG += c++11
TARGET = base-app
TEMPLATE = lib

DEFINES += BASEAPP_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    baseapp.cpp \
    date.cpp \
    match.cpp \
    simpleclass.cpp \
    venue.cpp \
    timepoint.cpp \
    mytime.cpp

HEADERS += \
    baseapp.h \
    base-app_global.h \
    match.h \
    simpleclass.h \
    venue.h \
    timepoint.h \
    mytime.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
