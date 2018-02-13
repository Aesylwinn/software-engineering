GOOGLETEST_DIR = /home/aesylwinn/Dev/rep/googletest
include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console thread
CONFIG -= app_bundle

QT += widgets network testlib
QT -= gui

SOURCES += \
	main.cpp \
	tst_simpleclass.cpp	\

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../base-app/release/ -lbase-app
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../base-app/debug/ -lbase-app
else:unix: LIBS += -L$$OUT_PWD/../base-app/ -lbase-app

DEPENDPATH += $$PWD/../base-app
