// Google test
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

// Qt
#include <QVector>
#include <QString>

// Class being tested
#include "../base-app/eventchooser.h"
#include "../base-app/event.h"


using namespace testing;
using namespace base;

TEST(base, EventList_noDuplicates){
    EventChooser list;
    Event event1("1"), event2("2"), event3("3"), event4("4");
    QVector<Event> testVector{event1, event2, event3, event4};
    QVector<Event> narrowed = list.narrow(testVector, 4);
    ASSERT_TRUE(narrowed[0] != narrowed[1]
            && narrowed[0] != narrowed[2]
            && narrowed[0] != narrowed[3]
            && narrowed[1] != narrowed[2]
            && narrowed[1] != narrowed[3]
            && narrowed[2] != narrowed[3]);
}

TEST(base, EventList_sizeTooBig){
    EventChooser list;
    Event event1("1"), event2("2"), event3("3"), event4("4");
    QVector<Event> testVector{event1, event2, event3, event4};
    QVector<Event> narrowed = list.narrow(testVector, 10);
    ASSERT_TRUE(narrowed.size() == testVector.size());
}
