// Google test
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

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

TEST(base, NetworkObject_loginRequestCtor) {
    using LoginRequest = NetworkObject::LoginRequest;

    const LoginRequest request{ "Bob", "password" };
    NetworkObject netObj(request);

    LoginRequest converted = netObj.getLoginRequest();
    ASSERT_EQ(request.username, converted.username);
    ASSERT_EQ(request.password, converted.password);
}

TEST(base, NetworkObject_messageCtor) {
    using Message = NetworkObject::Message;

    const Message message = { "general", "Hello!!!" };
    NetworkObject netObj(message);

    Message converted = netObj.getMessage();
    ASSERT_EQ(message.category, converted.category);
    ASSERT_EQ(message.message, converted.message);
}

TEST(base, NetworkObject_loginResponseCtor_isnotvalid) {
    using LoginRequest = NetworkObject::LoginRequest;
    using LoginResponse = NetworkObject::LoginResponse;

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
    using LoginRequest = NetworkObject::LoginRequest;
    using LoginResponse = NetworkObject::LoginResponse;

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

TEST(base, NetworkObject_write) {
    using Message = NetworkObject::Message;

    // Set up state
    const Message msg{ "random", "You won!!!" };
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
    using Message = NetworkObject::Message;

    // Set up state
    const Message msg{ "billy", "He's playing hooky!" };
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

    Message output = outputObj.getMessage();
    ASSERT_EQ(outputObj.getTicket(), ticketNum);
    ASSERT_EQ(msg.category, output.category);
    ASSERT_EQ(msg.message, output.message);
}

TEST(base, NetworkObject_partialRead) {
    using Message = NetworkObject::Message;

    // Set up state
    const Message msg{ "billy", "He's gone fishing!" };
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
