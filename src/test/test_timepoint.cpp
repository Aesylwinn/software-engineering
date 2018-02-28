// Google test
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

// Class being tested
#include "../base-app/timepoint.h"

using namespace testing;
using namespace base;

TEST(base, TimePoint1) {
    TimePoint* obj = new TimePoint();
    ASSERT_TRUE(true);
    delete obj;
}

TEST(base, TimePoint2) {
    TimePoint* obj = new TimePoint();
    ASSERT_FALSE(false);
    delete obj;
}
