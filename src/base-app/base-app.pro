QT += widgets network sql
QT -= gui
CONFIG += c++11
TARGET = base-app
TEMPLATE = lib

DEFINES += BASEAPP_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    baseapp.cpp \
    clientnetworkmgr.cpp \
    date.cpp \
    event.cpp \
    match.cpp \
    networkobject.cpp \
    recurringtime.cpp \
    servernetworkmgr.cpp \
    simpleclass.cpp \
    venue.cpp \
    timepoint.cpp \
    mytime.cpp \
    databaseconnection.cpp

HEADERS += \
    baseapp.h \
    base-app_global.h \
    clientnetworkmgr.h \
    event.h \
    match.h \
    networkobject.h \
    recurringtime.h \
    servernetworkmgr.h \
    simpleclass.h \
    venue.h \
    timepoint.h \
    mytime.h \
    databaseconnection.h \
    networkpackets.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
