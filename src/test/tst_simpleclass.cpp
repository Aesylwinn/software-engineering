// Google test
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

// Class being tested
#include "../base-app/simpleclass.h"

using namespace testing;
using namespace base;

TEST(base, SimpleClass_alwaysTrue_case1) {
	SimpleClass* obj = new SimpleClass();
	ASSERT_TRUE(obj->alwaysTrue());
	delete obj;
}

TEST(base, SimpleClass_alwaysFalse_case1) {
	SimpleClass* obj = new SimpleClass();
    ASSERT_FALSE(obj->alwaysFalse());
	delete obj;
}
