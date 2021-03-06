// Google test
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

// Qt
#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

// Class being tested
#include "../base-app/clientnetworkmgr.h"

using namespace testing;
using namespace base;

/* Implemented by Kyle and Anthony */

TEST(ClientNetworkMgr, connection) {
    // Workaround for const char* to char* issue
    char AppName[] = { 'T', 'S', 'T', '\n' };
    int Port = 1923;

    // Set up an event loop
    int argc = 1;
    char* argv[2] = { AppName, NULL };
    QCoreApplication app(argc, argv);

    // Create a dummy socket to listen for the connection
    QTcpServer* server = new QTcpServer(&app);
    server->listen(QHostAddress::Any, Port);
    // Connection test
    bool wasConnected = false;
    QObject::connect(server, &QTcpServer::newConnection, [&]() {
        wasConnected = true;
    });

    // Set up network
    ClientNetworkMgr* client = new ClientNetworkMgr(&app);

    // Quit after connecting
    QObject::connect(client, &ClientNetworkMgr::connected,
            &app, &QCoreApplication::quit);

    // Connect
    client->connect("::1", Port);

    // Wait no more than 1 second
    QTimer::singleShot(1000, &app, SLOT(quit()));

    // Run
    ASSERT_EQ(app.exec(), 0);
    ASSERT_TRUE(wasConnected);
}

TEST(ClientNetworkMgr, sendRequest) {
    // Workaround for const char* to char* issue
    char AppName[] = { 'T', 'S', 'T', '\n' };
    int Port = 1984;

    // What gets sent
    NetworkObject request(base::Message{ "TST", "Hello world!" });

    // Set up an event loop
    int argc = 1;
    char* argv[2] = { AppName, NULL };
    QCoreApplication app(argc, argv);

    // Create a dummy socket to listen for the connection
    QTcpServer* server = new QTcpServer(&app);
    server->listen(QHostAddress::Any, Port);
    // Connection test
    bool wasRecieved = false;
    QObject::connect(server, &QTcpServer::newConnection, [&]() {
        QTcpSocket* socket = server->nextPendingConnection();
        if (socket) {
            QObject::connect(socket, &QTcpSocket::readyRead, [&]() {
                wasRecieved = true;
                app.quit();
            });
        }
    });

    // Set up network
    ClientNetworkMgr* client = new ClientNetworkMgr(&app);

    // Send a message after connecting
    bool wasSent = false;
    QObject::connect(client, &ClientNetworkMgr::connected, [&](){
        client->sendRequest(request);
        wasSent = true;
    });
    // Connect
    client->connect("::1", Port);

    // Wait no more than 1 second
    QTimer::singleShot(1000, &app, SLOT(quit()));

    // Run
    ASSERT_EQ(app.exec(), 0);
    ASSERT_TRUE(wasSent);
    ASSERT_TRUE(wasRecieved);
}
