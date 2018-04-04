include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console thread c++11
CONFIG -= app_bundle

QT += widgets network sql
QT -= gui

SOURCES += \
    main.cpp \
    tst_networkobject.cpp \
    tst_recurringtime.cpp \
    tst_simpleclass.cpp \
    test_timepoint.cpp \
    tst_clientnetworkmgr.cpp \
    tst_venue.cpp \
    tst_databaseconnection.cpp \
    tst_event.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../base-app/release/ -lbase-app
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../base-app/debug/ -lbase-app
else:unix: LIBS += -L$$OUT_PWD/../base-app/ -lbase-app

DEPENDPATH += $$PWD/../base-app

