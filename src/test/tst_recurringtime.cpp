// Google test
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

// Class being tested
#include "../base-app/recurringtime.h"

using namespace testing;
using namespace base;

TEST(base, RecurringTime_defaultCtor) {
	RecurringTime* obj = new RecurringTime();
	ASSERT_TRUE(obj->getHour() == 0);
	ASSERT_TRUE(obj->getMinute() == 0);
	ASSERT_TRUE(obj->getDays() == "");
	delete obj;
}

TEST(base, RecurringTime_formattedCtor) {
	RecurringTime* obj = new RecurringTime("MWF.13:50");
    ASSERT_TRUE(obj->getHour() == 13);
    ASSERT_TRUE(obj->getMinute() == 50);
    ASSERT_TRUE(obj->availableOnAny(RecurringTime::Monday));
	delete obj;
}
