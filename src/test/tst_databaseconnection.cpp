// Google test
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

// Class being tested
#include "../base-app/databaseconnection.h"
#include <QTimer>
#include <QCoreApplication>

using namespace testing;
using namespace base;

TEST(base, dbconnection) {
    char AppName[] = { 'a', 'b' , 'c', '\0'};
    int argc = 1;
    char* argv[] = {AppName, nullptr};
    QCoreApplication app(argc, argv);

    try{
        DatabaseConnection myboi("fake");
        FAIL(); //should throw runtime_error
    }
    catch ( std::runtime_error ex) {}

    QTimer::singleShot(100, &app, SLOT(quit()));
    app.exec();

}
