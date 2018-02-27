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
