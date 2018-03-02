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

TEST(base, ClientNetworkMgr_connect_case1) {
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
    bool wasRecieved = false;
    QObject::connect(server, &QTcpServer::newConnection, [&]() {
        wasConnected = true;
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
        client->log("Hello world!");
        wasSent = true;
    });
    // Connect
    client->connect("::1", Port);

    // Wait no more than 1 second
    QTimer::singleShot(1000, &app, SLOT(quit()));

    // Run
    ASSERT_EQ(app.exec(), 0);
    ASSERT_TRUE(wasConnected);
    ASSERT_TRUE(wasSent);
    ASSERT_TRUE(wasRecieved);
}

TEST(base, ClientNetworkMgr_sendRequest) {
    // Workaround for const char* to char* issue
    char AppName[] = { 'T', 'S', 'T', '\n' };
    int Port = 1984;

    // What gets sent
    NetworkObject request(NetworkObject::Message{ "TST", "Hello world!" });

    // Set up an event loop
    int argc = 1;
    char* argv[2] = { AppName, NULL };
    QCoreApplication app(argc, argv);

    // Create a dummy socket to listen for the connection
    QTcpServer* server = new QTcpServer(&app);
    server->listen(QHostAddress::Any, Port);
    // Connection test
    bool wasConnected = false;
    bool wasRecieved = false;
    QObject::connect(server, &QTcpServer::newConnection, [&]() {
        wasConnected = true;
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
    ASSERT_TRUE(wasConnected);
    ASSERT_TRUE(wasSent);
    ASSERT_TRUE(wasRecieved);
}
