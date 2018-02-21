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

TEST(base, ClientNetworkMgr_connect_case1) {
    // Workaround for const char* to char* issue
    char AppName[] = { 'T', 'S', 'T', '\n' };

    // Set up an event loop
    int argc = 1;
    char* argv[2] = { AppName, NULL };
    QCoreApplication app(argc, argv);

    // Set up network
    ClientNetworkMgr* client = new ClientNetworkMgr(&app);

    // Send a message after connecting
    bool wasSent = false;
    QObject::connect(client, &ClientNetworkMgr::connected, [&](){
        client->log("Hello world!");
        wasSent = true;
    });
    // Connect
    client->connect("::1", 1942);

    // Wait no more than 1 second
    QTimer::singleShot(1000, &app, SLOT(quit()));

    // Run
    ASSERT_EQ(app.exec(), 0);
    ASSERT_TRUE(wasSent);
}
