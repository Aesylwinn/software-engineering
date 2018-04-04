QT += widgets network
QT -= gui
!android:QT += sql

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
    simpleclass.cpp \
    venue.cpp \
    timepoint.cpp \
    mytime.cpp \
    eventlist.cpp

!android:SOURCES += servernetworkmgr.cpp databaseconnection.cpp

HEADERS += \
    baseapp.h \
    base-app_global.h \
    clientnetworkmgr.h \
    event.h \
    match.h \
    networkobject.h \
    recurringtime.h \
    simpleclass.h \
    venue.h \
    timepoint.h \
    mytime.h \
    networkpackets.h \
    eventlist.h

!android:HEADERS += servernetworkmgr.h databaseconnection.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
