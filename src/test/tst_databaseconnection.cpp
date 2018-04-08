// Google test
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

// Class being tested
#include "../base-app/databaseconnection.h"
#include <QTimer>
#include <QCoreApplication>

using namespace testing;
using namespace base;

/* Implemented by Kyle and Anthony */

bool testDbIsAvailable() {
    try {
        DatabaseConnection db("test");
        return true;
    } catch (std::runtime_error) {
        return false;
    }
}

TEST(DatabaseConnection, default) {
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

TEST(DatabaseConnection, createAccount){
    if (!testDbIsAvailable()) {
        std::cerr << "!!!Warning!!! Unable to run database tests!\n";
        return;
    }

    char AppName[] = { 'a', 'b' , 'c', '\0'};
    int argc = 1;
    char* argv[] = {AppName, nullptr};
    QCoreApplication app(argc, argv);

    try{
        DatabaseConnection db("se");
        db.createAccount("testUsername","pass");
    }
    catch ( std::runtime_error ex ) {
        std::cerr << ex.what();
        FAIL();
    }

    QTimer::singleShot(100, &app, SLOT(quit()));
    app.exec();
}

TEST(DatabaseConnection, createHost) {
    if (!testDbIsAvailable()) {
        std::cerr << "!!!Warning!!! Unable to run database tests!\n";
        return;
    }

    char AppName[] = { 'a', 'b', 'c', '\0' };
    int argc = 1;
    char* argv[] = { AppName, nullptr };
    QCoreApplication app(argc, argv);

    try {
        DatabaseConnection db("se");
        db.createHost(56, "Bob's Funzone", "Bob Incorporated", "Fun! Fun! Fun! For one and all!");
    } catch (std::runtime_error ex) {
        std::cerr << ex.what() << std::endl;
        FAIL();
    }

    QTimer::singleShot(100, &app, SLOT(quit()));
    app.exec();
}
