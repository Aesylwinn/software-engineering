QT += widgets network
QT -= gui
!android:QT += sql

CONFIG += c++11
TARGET = base-app
TEMPLATE = lib

DEFINES += BASEAPP_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    clientnetworkmgr.cpp \
    event.cpp \
    networkobject.cpp \
    recurringtime.cpp \
    venue.cpp \
    networkpackets.cpp \
    userprofile.cpp \
    eventchooser.cpp

!android:SOURCES += servernetworkmgr.cpp databaseconnection.cpp

HEADERS += \
    base-app_global.h \
    clientnetworkmgr.h \
    event.h \
    networkobject.h \
    recurringtime.h \
    venue.h \
    networkpackets.h \
    userprofile.h \
    eventchooser.h

!android:HEADERS += servernetworkmgr.h databaseconnection.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
