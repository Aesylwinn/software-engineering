QT += core gui widgets network testlib

TARGET = GetGoing
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
    loginpage.cpp \
    registerpage.cpp \
    mainpage.cpp \
    createeventpage.cpp \
    eventtablewidget.cpp \
    myeventtablewidget.cpp \
    matchespage.cpp \
    matchitemwidget.cpp

HEADERS += \
    loginpage.h \
    registerpage.h \
    mainpage.h \
    createeventpage.h \
    eventtablewidget.h \
    myeventtablewidget.h \
    matchespage.h \
    matchitemwidget.h

FORMS += \
    loginpage.ui \
    registerpage.ui \
    mainpage.ui \
    createeventpage.ui \
    eventtablewidget.ui \
    myeventtablewidget.ui \
    matchespage.ui \
    matchitemwidget.ui

# base-app
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../base-app/release/ -lbase-app
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../base-app/debug/ -lbase-app
else:unix: LIBS += -L$$OUT_PWD/../base-app/ -lbase-app

DEPENDPATH += $$PWD/../base-app

RESOURCES += \
    utilities.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
