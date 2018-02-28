// Google test
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

// Class being tested
#include "../base-app/venue.h"

using namespace testing;
using namespace base;

TEST(base, venue_fullCTOR){
    venue ven("name", "123 place", "456", 7.89);
    ASSERT_TRUE(ven.getName() == "name");
    ASSERT_TRUE(ven.getAddress() == "123 place");
    ASSERT_TRUE(ven.getPhoneNumber() == "456");
    ASSERT_TRUE(ven.getEntryFee() == 7.89);
}

TEST(base, venue_stringCTOR) {
}

TEST(base, venue_toString) {
}
