// Google test
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

// Threading
#include <mutex>
#include <thread>

// Class being tested
#include "../base-app/networkmanager.h"

using namespace testing;
using namespace base;

TEST(base, NetworkManager_logToServer_case1) {
	NetworkManager* client = new NetworkManager();

	// Server needs to listen on another thread
	std::thread threadServer([]() {
		// Allocate and run
		NetworkManager* server = new NetworkManager();
		server->startServer(50);
		delete server;
	});

	// Connect to server and send a message
	client->connectToServer("127.0.0.1", 50);
	client->logToServer("Hello World!\n");

	// Wait for server to finish
	threadServer.join();

	delete client;
}
