// Google test
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

// Class being tested
#include "../base-app/recurringtime.h"

using namespace testing;
using namespace base;

TEST(base, RecurringTime_defaultCtor) {
	RecurringTime* obj = new RecurringTime();
	ASSERT_EQ(obj->getHour(), 0);
	ASSERT_EQ(obj->getMinute(), 0);
	ASSERT_EQ(obj->getDays(), QString("-------"));
	delete obj;
}

TEST(base, RecurringTime_paramaterizedCtor_case1) {
	const unsigned int Days = RecurringTime::Sunday | RecurringTime::Friday;
	RecurringTime* obj = new RecurringTime(Days, 14, 25);
	ASSERT_EQ(obj->getHour(), 14);
	ASSERT_EQ(obj->getMinute(), 25);
	ASSERT_EQ(obj->getDays(), QString("S----F-"));
	delete obj;
}

TEST(base, RecurringTime_paramaterizedCtor_case2) {
	RecurringTime* obj = new RecurringTime(0, 0, 0);
	ASSERT_EQ(obj->getDays(), QString("-------"));
	delete obj;
}

TEST(base, RecurringTime_parameterizedCtor_case3) {
	const unsigned int Days = (RecurringTime::Saturday * 2) | RecurringTime::Wednesday;
	RecurringTime* obj = new RecurringTime(Days, 3, 30);
	ASSERT_EQ(obj->getDays(), QString("---W---"));
	ASSERT_FALSE(obj->availableOnAny(RecurringTime::Saturday * 2));
	delete obj;
}

TEST(base, RecurringTime_formattedCtor) {
	RecurringTime* obj = new RecurringTime("-M-W-F-.13:50");
    ASSERT_EQ(obj->getHour(), 13);
    ASSERT_EQ(obj->getMinute(), 50);
    ASSERT_TRUE(obj->availableOnAny(RecurringTime::Monday));
	delete obj;
}

TEST(base, RecurringTime_reset) {
	RecurringTime* obj = new RecurringTime("-M----S.02:13");
	obj->reset();
	ASSERT_EQ(obj->getHour(), 0);
	ASSERT_EQ(obj->getMinute(), 0);
	ASSERT_EQ(obj->getDays(), QString("-------"));
	delete obj;
}

TEST(base, RecurringTime_fromString_case1) {
	RecurringTime* obj = new RecurringTime();
	obj->fromString("SMTWRFS.01:05");
	ASSERT_EQ(obj->getHour(), 1);
	ASSERT_EQ(obj->getMinute(), 5);
	ASSERT_EQ(obj->getDays(), QString("SMTWRFS"));
	ASSERT_TRUE(obj->availableOnAll(~0));
	delete obj;
}

TEST(base, RecurringTime_toString) {
	RecurringTime* obj = new RecurringTime(RecurringTime::Sunday, 5, 50);
	ASSERT_EQ(obj->toString(), QString("S------.05:50"));
	delete obj;
}
