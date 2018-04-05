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
    ASSERT_EQ(netObj.getPayloadType(), PT_None);
    try {
        QByteArray payload = netObj.getPayload();
        // Shold have thrown
        FAIL();
    } catch (...) {
        // If it threw then the test was a success
    }
}

TEST(base, NetworkObject_parametizedCtor) {
    auto type = PT_Message;
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

    CreateAccountRequest converted = netObj.convert<CreateAccountRequest>();
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

    LoginRequest converted = netObj.convert<LoginRequest>();
    ASSERT_EQ(request.username, converted.username);
    ASSERT_EQ(request.password, converted.password);
}

TEST(base, NetworkObject_EventCreateRequest){
    const CreateEventRequest myEvent{Event("bob", 0, "This event is the best", "Bob's dad")};
    NetworkObject netObj(myEvent);

    CreateEventRequest converted = netObj.convert<CreateEventRequest>();
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
    SuggestEventsRequest converted = netObj.convert<SuggestEventsRequest>();

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
    CreateHostRequest converted = netObj.convert<CreateHostRequest>();

    // Oracle
    ASSERT_EQ(request.username, converted.username);
    ASSERT_EQ(request.password, converted.password);
    ASSERT_EQ(request.displayName, converted.displayName);
    ASSERT_EQ(request.businessName, converted.businessName);
    ASSERT_EQ(request.bio, converted.bio);
}

TEST(base, NetworkObject_joinEventRequest) {
    // State
    const JoinEventRequest request = { 42 };

    // Test
    NetworkObject netObj(request);
    JoinEventRequest converted = netObj.convert<JoinEventRequest>();

    // Oracle
    ASSERT_EQ(request.eventId, converted.eventId);
}

TEST(base, NetworkObject_retrieveMyEventsRequest) {
    // State
    const RetrieveMyEventsRequest request = { 199 };

    // Test
    NetworkObject netObj(request);
    RetrieveMyEventsRequest converted = netObj.convert<RetrieveMyEventsRequest>();

    // Oracle
    ASSERT_EQ(request.count, converted.count);
}

TEST(base, NetworkObject_setInterestsRequest) {
    // State
    const SetInterestsRequest request = { { "Fun", "Horror", "Bbop"} };

    // Test
    NetworkObject netObj(request);
    SetInterestsRequest converted = netObj.convert<SetInterestsRequest>();

    // Oracle
    ASSERT_EQ(request.interests.count(), converted.interests.count());
    ASSERT_EQ(request.interests, converted.interests);
}

TEST(base, NetworkObject_findMatchRequest) {
    // State
    const FindMatchRequest request = { 2788591231 };

    // Test
    NetworkObject netObj(request);
    auto converted = netObj.convert<FindMatchRequest>();

    // Oracle
    ASSERT_EQ(request.event_id, converted.event_id);
}

TEST(base, NetworkObject_retrieveMatchesRequest) {
    // State
    const RetrieveMatchesRequest request = { 827 };

    // Test
    NetworkObject netObj(request);
    auto converted = netObj.convert<RetrieveMatchesRequest>();

    // Oracle
    ASSERT_EQ(request.unused, converted.unused);
}

TEST(base, NetworkObject_messageCtor) {
    const base::Message message = { "general", "Hello!!!" };
    NetworkObject netObj(message);

    base::Message converted = netObj.convert<base::Message>();
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

    CreateAccountResponse converted = netObjResponse.convert<CreateAccountResponse>();
    ASSERT_EQ(netObjResponse.getTicket(), ticketNumber);
    ASSERT_EQ(response.valid, converted.valid);
    ASSERT_EQ(response.details, converted.details);
}

TEST(base, NetworkObject_loginResponseCtor_isnotvalid) {
    // Set up state
    const LoginRequest request{ "muah", "hahaha!!!" };
    const LoginResponse response{ 0, "User password is wrong", 0 };
    const qint32 ticketNumber = 11;

    NetworkObject netObj(request);
    netObj.setTicket(ticketNumber);

    // Method being tested
    NetworkObject netObjResponse = netObj.createResponse(response);

    // The all seeing Oracle
    LoginResponse converted = netObjResponse.convert<LoginResponse>();
    ASSERT_EQ(netObjResponse.getTicket(), ticketNumber);
    ASSERT_EQ(response.valid, converted.valid);
    ASSERT_EQ(response.details, converted.details);
    ASSERT_EQ(response.isHost, converted.isHost);
}

TEST(base, NetworkObject_loginResponseCtor_isvalid) {
    // Set up state
    const LoginRequest request{ "oh", "dear" };
    const LoginResponse response{ 1, "", 1 };
    const qint32 ticketNumber = 11;

    NetworkObject netObj(request);
    netObj.setTicket(ticketNumber);

    // Method being tested
    NetworkObject netObjResponse = netObj.createResponse(response);

    // The all seeing Oracle
    LoginResponse converted = netObjResponse.convert<LoginResponse>();
    ASSERT_EQ(netObjResponse.getTicket(), ticketNumber);
    ASSERT_EQ(response.valid, converted.valid);
    ASSERT_EQ(response.details, converted.details);
    ASSERT_EQ(response.isHost, converted.isHost);
}

TEST(base, NetworkObject_createEventResponseCtor) {
    const CreateEventRequest request{ Event("Jade's Salon", 5, "Drink up...", "Jade") };
    const CreateEventResponse response{ 1, "success" };
    const qint32 ticketNumber = 324;

    NetworkObject netObj(request);
    netObj.setTicket(ticketNumber);

    NetworkObject netObjResponse = netObj.createResponse(response);

    CreateEventResponse converted = netObjResponse.convert<CreateEventResponse>();
    ASSERT_EQ(netObjResponse.getTicket(), ticketNumber);
    ASSERT_EQ(response.valid, 1);
}

TEST(base, NetworkObject_suggestEventsResponseCtor) {
    // Set up state
    const SuggestEventsRequest request { 2 };
    const SuggestEventsResponse response {{
        Event("Bob's Emporium", 12, "Fun!"),
        Event("Middle Earth", 232, "Dangerous!")
    }};
    const qint32 ticketNumber = 89;

    NetworkObject netObj(request);
    netObj.setTicket(ticketNumber);

    // Test
    NetworkObject netObjResponse = netObj.createResponse(response);
    SuggestEventsResponse converted = netObjResponse.convert<SuggestEventsResponse>();

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
    CreateHostResponse converted = netObjResponse.convert<CreateHostResponse>();

    // Oracle
    ASSERT_EQ(netObjResponse.getTicket(), ticketNumber);
    ASSERT_EQ(response.valid, converted.valid);
}

TEST(base, NetworkObject_joinEventResponse) {
    // Setup state
    const JoinEventRequest request{ 829 };
    const JoinEventResponse response { 1, "You got it!!!" };
    const qint32 ticketNumber = 46;

    NetworkObject netObj(request);
    netObj.setTicket(ticketNumber);

    // Test
    NetworkObject netObjResponse = netObj.createResponse(response);
    JoinEventResponse converted = netObjResponse.convert<JoinEventResponse>();

    ASSERT_EQ(netObjResponse.getTicket(), ticketNumber);
    ASSERT_EQ(response.valid, converted.valid);
    ASSERT_EQ(response.details, converted.details);
}

TEST(base, NetworkObject_retrieveMyEventsResponse) {
    // Set up state
    const RetrieveMyEventsRequest request { 2 };
    const RetrieveMyEventsResponse response {{
        Event("Bob's Funner Emporium", 799, "Fun!"),
        Event("Earth", 92, "Nuclear waste!")
    }};
    const qint32 ticketNumber = 31;

    NetworkObject netObj(request);
    netObj.setTicket(ticketNumber);

    // Test
    NetworkObject netObjResponse = netObj.createResponse(response);
    RetrieveMyEventsResponse converted = netObjResponse.convert<RetrieveMyEventsResponse>();

    // Oracle
    ASSERT_EQ(netObjResponse.getTicket(), ticketNumber);
    ASSERT_EQ(response.events.size(), converted.events.size());
    ASSERT_EQ(response.events, converted.events);
}

TEST(base, NetworkObject_setInterestsResponse) {
    // Set up state
    const SetInterestsRequest request {{ "Romance", "Love", "Heartbreak"}};
    const SetInterestsResponse response { IsValid, "Hahaha!" };
    const qint32 ticketNumber = 999999999;

    NetworkObject netObj(request);
    netObj.setTicket(ticketNumber);

    // Test
    NetworkObject netObjResponse = netObj.createResponse(response);
    SetInterestsResponse converted = netObjResponse.convert<SetInterestsResponse>();

    // Oracle
    ASSERT_EQ(netObjResponse.getTicket(), ticketNumber);
    ASSERT_EQ(response.valid, converted.valid);
    ASSERT_EQ(response.details, converted.details);
}

TEST(base, NetworkObject_findMatchResponse) {
    // Set up state
    const FindMatchRequest request { 168924 };
    const FindMatchResponse response { IsValid, "You have been matched with TheGrinch!" };
    const qint32 ticketNumber = 9314;

    NetworkObject netObj(request);
    netObj.setTicket(ticketNumber);

    // Test
    NetworkObject netObjResponse = netObj.createResponse(response);
    auto converted = netObjResponse.convert<FindMatchResponse>();

    // Oracle
    ASSERT_EQ(netObjResponse.getTicket(), ticketNumber);
    ASSERT_EQ(response.valid, converted.valid);
    ASSERT_EQ(response.details, converted.details);
}

TEST(base, NetworkObject_retrieveMatchesResponse) {
    // Set up state
    UserProfile profile1;
    profile1.setFirstName("Bob");
    profile1.setLastName("Jones");
    profile1.setEmail("wondergirl@hero.com");
    profile1.setBirthday(QDate::currentDate());
    profile1.setGender("Female");
    profile1.setBio("I love super hero flicks!");
    profile1.setUserId(45);

    UserProfile profile2;
    profile2.setFirstName("Anne");
    profile2.setLastName("Redguard");
    profile2.setEmail("joinus@bob.com");
    profile2.setBirthday(QDate::currentDate());
    profile2.setGender("Male");
    profile2.setBio("I hate super hero flicks!");
    profile2.setUserId(15);

    const RetrieveMatchesRequest request { 998 };
    const RetrieveMatchesResponse response {{ profile1, profile2 }, { base::Event("Yey!!!"), base::Event("Ooohhh!!!") }};
    const qint32 ticketNumber = 555;

    NetworkObject netObj(request);
    netObj.setTicket(ticketNumber);

    // Test
    NetworkObject netObjResponse = netObj.createResponse(response);
    auto converted = netObjResponse.convert<RetrieveMatchesResponse>();

    // Oracle
    ASSERT_EQ(netObjResponse.getTicket(), ticketNumber);
    ASSERT_EQ(response.matches, converted.matches);
    ASSERT_EQ(response.events, converted.events);
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

    base::Message output = outputObj.convert<base::Message>();
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
