// Google test
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

// Qt
#include <QCoreApplication>
#include <QTimer>

// Class being tested
#include "../base-app/clientnetworkmgr.h"

using namespace testing;
using namespace base;

TEST(base, NetworkManager_logToServer_case1) {
    // Workaround for const char* to char* issue
    char AppName[] = { 'T', 'S', 'T', '\n' };

    // Set up an event loop
    int argc = 1;
    char* argv[2] = { AppName, NULL };
    QCoreApplication app(argc, argv);

    // Set up network
    ClientNetworkMgr* client = new ClientNetworkMgr(&app);
    client->connect("::1", 1942);

    // Quit in a second
    QTimer::singleShot(1000, &app, SLOT(quit()));

    // Run
    ASSERT_EQ(app.exec(), 0);
}
