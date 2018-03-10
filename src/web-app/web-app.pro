QT += core gui widgets network testlib

TARGET = web-app
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp\
        interestdata.cpp \
    eventpopup.cpp \
    verified.cpp \
    matches.cpp

HEADERS += \
        interestdata.h \
    eventpopup.h \
    verified.h \
    matches.h

FORMS += \
        interestdata.ui \
    eventpopup.ui \
    verified.ui \
    matches.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../base-app/release/ -lbase-app
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../base-app/debug/ -lbase-app
else:unix: LIBS += -L$$OUT_PWD/../base-app/ -lbase-app

DEPENDPATH += $$PWD/../base-app

DISTFILES +=

RESOURCES += \
    utilities.qrc
