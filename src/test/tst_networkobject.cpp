// Google test
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <condition_variable>
#include <mutex>
#include <thread>

#include <QTcpSocket>

// Class being tested
#include "../base-app/networkobject.h"

using namespace testing;
using namespace base;

TEST(base, NetworkObject_defaultCtor) {
    NetworkObject netObj;
    ASSERT_EQ(netObj.getPayloadType(), NetworkObject::PT_None);
    try {
        QByteArray payload = netObj.getPayload();
        // Shold have thrown
        FAIL();
    } catch (...) {
        // If it threw then the test was a success
    }
}

TEST(base, NetworkObject_parametizedCtor) {
    auto type = NetworkObject::PT_Message;
    auto payload = QString("10 .. 9 .. 8 ..").toUtf8();
    NetworkObject netObj(type, payload);
    ASSERT_EQ(netObj.getPayloadType(), type);
    ASSERT_EQ(netObj.getPayload(), payload);
}

TEST(base, NetworkObject_createAccountRequestCtor) {
    CreateAccountRequest request;
    request.username = "WillyWonka";
    request.password = "chocolate";
    request.email = "thegreatestchocolatier@delicious.com";
    request.firstName = "Willy";
    request.lastName = "Wonka";
    request.gender = "Male";
    request.birthDate = "01/24/1950";

    NetworkObject netObj((const CreateAccountRequest) request);

    CreateAccountRequest converted = netObj.getCreateAccountRequest();
    ASSERT_EQ(request.username, converted.username);
    ASSERT_EQ(request.password, converted.password);
    ASSERT_EQ(request.email, converted.email);
    ASSERT_EQ(request.firstName, converted.firstName);
    ASSERT_EQ(request.lastName, converted.lastName);
    ASSERT_EQ(request.gender, converted.gender);
    ASSERT_EQ(request.birthDate, converted.birthDate);
}

TEST(base, NetworkObject_loginRequestCtor) {
    const LoginRequest request{ "Bob", "password" };
    NetworkObject netObj(request);

    LoginRequest converted = netObj.getLoginRequest();
    ASSERT_EQ(request.username, converted.username);
    ASSERT_EQ(request.password, converted.password);
}

TEST(base, NetworkObject_EventCreateRequest){
    const CreateEventRequest myEvent{event("bob", 0, "This event is the best", "Bob's dad")};
    NetworkObject netObj(myEvent);

    CreateEventRequest converted = netObj.getCreateEventRequest();
    // TODO
    ASSERT_EQ(myEvent.data.getName(), converted.data.getName());
    ASSERT_EQ(myEvent.data.getCategory(), converted.data.getCategory());
    ASSERT_EQ(myEvent.data.getAttendingUsers(), converted.data.getAttendingUsers());
    ASSERT_EQ(myEvent.data.getMainHost(), converted.data.getMainHost());
    ASSERT_EQ(myEvent.data.getDescription(), converted.data.getDescription());
    ASSERT_EQ(myEvent.data.getLocation(), converted.data.getLocation());
    ASSERT_EQ(myEvent.data.getID(), converted.data.getID());
}

TEST(base, NetworkObject_suggestEventsRequest) {
    // Set up state
    const SuggestEventsRequest request = { 5 };

    // Test conversion to and back again
    NetworkObject netObj(request);
    SuggestEventsRequest converted = netObj.getSuggestEventsRequest();

    // Oracle
    ASSERT_EQ(request.count, converted.count);
}

TEST(base, NetworkObject_createHostRequest) {
    // State
    const CreateHostRequest request = {
        "bob", "ducky",
        "Master",
        "The Universe",
        "Master of the Universe... is proud to present our business to you."
    };

    // Test
    NetworkObject netObj(request);
    CreateHostRequest converted = netObj.getCreateHostRequest();

    // Oracle
    ASSERT_EQ(request.username, converted.username);
    ASSERT_EQ(request.password, converted.password);
    ASSERT_EQ(request.displayName, converted.displayName);
    ASSERT_EQ(request.businessName, converted.businessName);
    ASSERT_EQ(request.bio, converted.bio);
}

TEST(base, NetworkObject_messageCtor) {
    const base::Message message = { "general", "Hello!!!" };
    NetworkObject netObj(message);

    base::Message converted = netObj.getMessage();
    ASSERT_EQ(message.category, converted.category);
    ASSERT_EQ(message.message, converted.message);
}

TEST(base, NetworkObject_createAccountResponse) {
    const CreateAccountRequest request{ "1", "2", "3", "4", "5", "6", "7" };
    const CreateAccountResponse response{ 1, "What interesting tastes you have..." };
    const qint32 ticketNumber = 14;

    NetworkObject netObj(request);
    netObj.setTicket(ticketNumber);

    NetworkObject netObjResponse = netObj.createResponse(response);

    CreateAccountResponse converted = netObjResponse.getCreateAccountResponse();
    ASSERT_EQ(netObjResponse.getTicket(), ticketNumber);
    ASSERT_EQ(response.valid, converted.valid);
    ASSERT_EQ(response.details, converted.details);
}

TEST(base, NetworkObject_loginResponseCtor_isnotvalid) {
    // Set up state
    const LoginRequest request{ "muah", "hahaha!!!" };
    const LoginResponse response{ 0, "User password is wrong" };
    const qint32 ticketNumber = 11;

    NetworkObject netObj(request);
    netObj.setTicket(ticketNumber);

    // Method being tested
    NetworkObject netObjResponse = netObj.createResponse(response);

    // The all seeing Oracle
    LoginResponse converted = netObjResponse.getLoginResponse();
    ASSERT_EQ(netObjResponse.getTicket(), ticketNumber);
    ASSERT_EQ(response.valid, converted.valid);
    ASSERT_EQ(response.details, converted.details);
}

TEST(base, NetworkObject_loginResponseCtor_isvalid) {
    // Set up state
    const LoginRequest request{ "oh", "dear" };
    const LoginResponse response{ 1, "" };
    const qint32 ticketNumber = 11;

    NetworkObject netObj(request);
    netObj.setTicket(ticketNumber);

    // Method being tested
    NetworkObject netObjResponse = netObj.createResponse(response);

    // The all seeing Oracle
    LoginResponse converted = netObjResponse.getLoginResponse();
    ASSERT_EQ(netObjResponse.getTicket(), ticketNumber);
    ASSERT_EQ(response.valid, converted.valid);
    ASSERT_EQ(response.details, converted.details);
}

TEST(base, NetworkObject_createEventResponseCtor) {
    const CreateEventRequest request{ event("Jade's Salon", 5, "Drink up...", "Jade") };
    const CreateEventResponse response{ 1, "success" };
    const qint32 ticketNumber = 324;

    NetworkObject netObj(request);
    netObj.setTicket(ticketNumber);

    NetworkObject netObjResponse = netObj.createResponse(response);

    CreateEventResponse converted = netObjResponse.getCreateEventResponse();
    ASSERT_EQ(netObjResponse.getTicket(), ticketNumber);
    ASSERT_EQ(response.valid, 1);
}

TEST(base, NetworkObject_suggestEventsResponseCtor) {
    // Set up state
    const SuggestEventsRequest request { 2 };
    const SuggestEventsResponse response {{
        event("Bob's Emporium", 12, "Fun!"),
        event("Middle Earth", 232, "Dangerous!")
    }};
    const qint32 ticketNumber = 89;

    NetworkObject netObj(request);
    netObj.setTicket(ticketNumber);

    // Test
    NetworkObject netObjResponse = netObj.createResponse(response);
    SuggestEventsResponse converted = netObjResponse.getSuggestEventsResponse();

    // Oracle
    ASSERT_EQ(netObjResponse.getTicket(), ticketNumber);
    ASSERT_EQ(response.events.size(), converted.events.size());
    ASSERT_EQ(response.events, converted.events);
}

TEST(base, NetworkObject_createHostResponse) {
    // Set up state
    const CreateHostRequest request {
        "bob", "baileyR0K2",
        "Bob",
        "Wonderman",
        "Tight ropes are cool. So are you. Why don't we rope our way to a bar together?"
    };
    const CreateHostResponse response { 1 };
    const qint32 ticketNumber = 42;

    NetworkObject netObj(request);
    netObj.setTicket(ticketNumber);

    // Test
    NetworkObject netObjResponse = netObj.createResponse(response);
    CreateHostResponse converted = netObjResponse.getCreateHostResponse();

    // Oracle
    ASSERT_EQ(netObjResponse.getTicket(), ticketNumber);
    ASSERT_EQ(response.valid, converted.valid);
}

TEST(base, NetworkObject_write) {
    // Set up state
    const base::Message msg{ "random", "You won!!!" };
    NetworkObject netObj(msg);

    // Set up test device
    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    // Write to the device
    netObj.write(&buffer);
    buffer.close();
    // Make sure something was written
    ASSERT_TRUE(data.size() > 0);
}

TEST(base, NetworkObject_read) {
    // Set up state
    const base::Message msg{ "billy", "He's playing hooky!" };
    const qint32 ticketNum = 5;

    NetworkObject netObj(msg);
    netObj.setTicket(ticketNum);

    NetworkObject outputObj;

    // Set up test device
    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    // Write to the device
    netObj.write(&buffer);
    buffer.close();

    // Set up to read
    buffer.open(QIODevice::ReadOnly);
    ASSERT_TRUE(outputObj.tryRead(&buffer));
    buffer.close();

    base::Message output = outputObj.getMessage();
    ASSERT_EQ(outputObj.getTicket(), ticketNum);
    ASSERT_EQ(msg.category, output.category);
    ASSERT_EQ(msg.message, output.message);
}

TEST(base, NetworkObject_partialRead) {
    // Set up state
    const base::Message msg{ "billy", "He's gone fishing!" };
    NetworkObject netObj(msg);

    NetworkObject outputObj;

    // Set up test device
    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    // Write to the device
    netObj.write(&buffer);
    buffer.close();

    // Test partial reads
    for (qint64 i = 4; i > 1; --i) {
        // Make a copy of the data
        QByteArray tempData = data;
        tempData.resize(data.size() / i);
        // Read
        buffer.setBuffer(&tempData);
        buffer.open(QIODevice::ReadOnly);
        ASSERT_FALSE(outputObj.tryRead(&buffer));
        buffer.close();
        // Make sure values are the same
        for (qint64 j = 0; j < data.size() / i; ++j) {
            ASSERT_EQ(data.at(j), tempData.at(j));
        }
    }
}

TEST(base, NetworkObject_invalidDevice) {
    std::condition_variable childDone;
    std::mutex mutex;
    bool done = false;

    std::thread child([&](){
        // Set up state
        const base::Message msg{ "billy", "He's gone fishing!" };
        NetworkObject netObj(msg);

        // Set up test device
        QByteArray data;
        QBuffer buffer(&data);
        // Write to the device
        netObj.write(&buffer);

        // Signal parent
        std::unique_lock<std::mutex> lock(mutex);
        done = true;
        lock.unlock();
        childDone.notify_one();
    });

    // Wait for child or timeout
    std::unique_lock<std::mutex> lock(mutex);
    if (!done) {
        childDone.wait_until(lock, std::chrono::system_clock::now() +
            std::chrono::milliseconds(10), [&]{ return done; });
    }
    ASSERT_EQ(done, true);
    lock.unlock();

    // Join with child thread
    child.join();
}

TEST(base, NetworkObject_invalidSocket) {
    std::condition_variable childDone;
    std::mutex mutex;
    bool done = false;

    std::thread child([&](){
        // Set up state
        const base::Message msg{ "billy", "He's gone fishing!" };
        NetworkObject netObj(msg);

        // Set up test device
        QTcpSocket socket;
        // Write to the device
        netObj.write(&socket);

        // Signal parent
        std::unique_lock<std::mutex> lock(mutex);
        done = true;
        lock.unlock();
        childDone.notify_one();
    });

    // Wait for child or timeout
    std::unique_lock<std::mutex> lock(mutex);
    if (!done) {
        childDone.wait_until(lock, std::chrono::system_clock::now() +
            std::chrono::milliseconds(10), [&]{ return done; });
    }
    ASSERT_EQ(done, true);
    lock.unlock();

    // Join with child thread
    child.join();
}
