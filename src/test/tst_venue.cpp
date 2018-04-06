// Google test
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

// Qt
#include <QString>

// Class being tested
#include "../base-app/venue.h"

using namespace testing;
using namespace base;

TEST(venue, defaultCtor) {
    venue obj;
    ASSERT_EQ(obj.getName(), QString(""));
    ASSERT_EQ(obj.getAddress(), QString(""));
    ASSERT_EQ(obj.getPhoneNumber(), QString("867-5309"));
    ASSERT_EQ(obj.getEntryFee(), 0);
}

TEST(venue, fullCtor) {
    venue obj("name", "123 place", "456", 7.89);
    ASSERT_EQ(obj.getName(), QString("name"));
    ASSERT_EQ(obj.getAddress(), QString("123 place"));
    ASSERT_EQ(obj.getPhoneNumber(), QString("456"));
    ASSERT_EQ(obj.getEntryFee(), 7.89);
}

TEST(venue, conversionCtor) {
    venue obj("name, 123 place, 456, 7.89");
    ASSERT_EQ(obj.getName(), QString("name"));
    ASSERT_EQ(obj.getAddress(), QString("123 place"));
    ASSERT_EQ(obj.getPhoneNumber(), QString("456"));
    ASSERT_EQ(obj.getEntryFee(), 7.89);
}
