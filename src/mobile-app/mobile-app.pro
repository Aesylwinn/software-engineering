QT += core gui widgets network testlib

TARGET = mobile-app
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
    loginpage.cpp \
    registerpage.cpp \
    mainpage.cpp \
    createeventpage.cpp \
    eventtablewidget.cpp

HEADERS += \
    loginpage.h \
    registerpage.h \
    mainpage.h \
    createeventpage.h \
    eventtablewidget.h

FORMS += \
    loginpage.ui \
    registerpage.ui \
    mainpage.ui \
    createeventpage.ui \
    eventtablewidget.ui

# base-app
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../base-app/release/ -lbase-app
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../base-app/debug/ -lbase-app
else:unix: LIBS += -L$$OUT_PWD/../base-app/ -lbase-app

DEPENDPATH += $$PWD/../base-app
