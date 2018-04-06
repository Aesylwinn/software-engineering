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

TEST(NetworkObject, defaultCtor) {
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

TEST(NetworkObject, parametizedCtor) {
    auto type = PT_Message;
    auto payload = QString("10 .. 9 .. 8 ..").toUtf8();
    NetworkObject netObj(type, payload);
    ASSERT_EQ(netObj.getPayloadType(), type);
    ASSERT_EQ(netObj.getPayload(), payload);
}

TEST(NetworkObject, createAccountRequestCtor) {
    CreateAccountRequest request;
    request.username = "WillyWonka";
    request.password = "chocolate";
    request.profile.setEmail("thegreatestchocolatier@delicious.com");
    request.profile.setFirstName("Willy");
    request.profile.setLastName("Wonka");
    request.profile.setGender("Male");
    request.profile.setBirthday(QDate(1,24,1950));

    NetworkObject netObj((const CreateAccountRequest) request);

    CreateAccountRequest converted = netObj.convert<CreateAccountRequest>();
    ASSERT_EQ(request.username, converted.username);
    ASSERT_EQ(request.password, converted.password);
    ASSERT_EQ(request.profile, converted.profile);
}

TEST(NetworkObject, loginRequestCtor) {
    const LoginRequest request{ "Bob", "password" };
    NetworkObject netObj(request);

    LoginRequest converted = netObj.convert<LoginRequest>();
    ASSERT_EQ(request.username, converted.username);
    ASSERT_EQ(request.password, converted.password);
}

TEST(NetworkObject, EventCreateRequest){
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

TEST(NetworkObject, suggestEventsRequest) {
    // Set up state
    const SuggestEventsRequest request = { 5 };

    // Test conversion to and back again
    NetworkObject netObj(request);
    SuggestEventsRequest converted = netObj.convert<SuggestEventsRequest>();

    // Oracle
    ASSERT_EQ(request.count, converted.count);
}

TEST(NetworkObject, createHostRequest) {
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

TEST(NetworkObject, joinEventRequest) {
    // State
    const JoinEventRequest request = { 42 };

    // Test
    NetworkObject netObj(request);
    JoinEventRequest converted = netObj.convert<JoinEventRequest>();

    // Oracle
    ASSERT_EQ(request.eventId, converted.eventId);
}

TEST(NetworkObject, retrieveMyEventsRequest) {
    // State
    const RetrieveMyEventsRequest request = { 199 };

    // Test
    NetworkObject netObj(request);
    RetrieveMyEventsRequest converted = netObj.convert<RetrieveMyEventsRequest>();

    // Oracle
    ASSERT_EQ(request.count, converted.count);
}

TEST(NetworkObject, setInterestsRequest) {
    // State
    const SetInterestsRequest request = { { "Fun", "Horror", "Bbop"} };

    // Test
    NetworkObject netObj(request);
    SetInterestsRequest converted = netObj.convert<SetInterestsRequest>();

    // Oracle
    ASSERT_EQ(request.interests.count(), converted.interests.count());
    ASSERT_EQ(request.interests, converted.interests);
}

TEST(NetworkObject, findMatchRequest) {
    // State
    const FindMatchRequest request = { 2788591231 };

    // Test
    NetworkObject netObj(request);
    auto converted = netObj.convert<FindMatchRequest>();

    // Oracle
    ASSERT_EQ(request.event_id, converted.event_id);
}

TEST(NetworkObject, retrieveMatchesRequest) {
    // State
    const RetrieveMatchesRequest request = { 827 };

    // Test
    NetworkObject netObj(request);
    auto converted = netObj.convert<RetrieveMatchesRequest>();

    // Oracle
    ASSERT_EQ(request.unused, converted.unused);
}

TEST(NetworkObject, messageCtor) {
    const base::Message message = { "general", "Hello!!!" };
    NetworkObject netObj(message);

    base::Message converted = netObj.convert<base::Message>();
    ASSERT_EQ(message.category, converted.category);
    ASSERT_EQ(message.message, converted.message);
}

TEST(NetworkObject, createAccountResponse) {
    const CreateAccountRequest request{ "1", "2", UserProfile() };
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

TEST(NetworkObject, loginResponseCtor_isnotvalid) {
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

TEST(NetworkObject, loginResponseCtor_isvalid) {
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

TEST(NetworkObject, createEventResponseCtor) {
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

TEST(NetworkObject, suggestEventsResponseCtor) {
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

TEST(NetworkObject, createHostResponse) {
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

TEST(NetworkObject, joinEventResponse) {
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

TEST(NetworkObject, retrieveMyEventsResponse) {
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

TEST(NetworkObject, setInterestsResponse) {
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

TEST(NetworkObject, findMatchResponse) {
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

TEST(NetworkObject, retrieveMatchesResponse) {
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

TEST(NetworkObject, write) {
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

TEST(NetworkObject, read) {
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

TEST(NetworkObject, partialRead) {
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

TEST(NetworkObject, invalidDevice) {
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

TEST(NetworkObject, invalidSocket) {
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
