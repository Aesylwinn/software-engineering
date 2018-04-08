/*Implemented by Jake and Kyle*/

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

/* Implemented by Jake and Kyle */

TEST(EventChooser, noDuplicates){ //checks for duplicate entries
    EventChooser list;
    Event event1("1"), event2("2"), event3("3"), event4("4");
    QVector<Event> testVector{event1, event2, event3, event4};
    QVector<QString> interests{"Fun", "Country", "Chess"};

    QVector<Event> narrowed = list.narrow(interests, testVector, 4);

    ASSERT_TRUE(narrowed[0] != narrowed[1]
            && narrowed[0] != narrowed[2]
            && narrowed[0] != narrowed[3]
            && narrowed[1] != narrowed[2]
            && narrowed[1] != narrowed[3]
            && narrowed[2] != narrowed[3]);
}

TEST(EventChooser, sizeTooBig){ //checks for requested number of events > actual amount of events
    EventChooser list;
    Event event1("1"), event2("2"), event3("3"), event4("4");
    QVector<Event> testVector{event1, event2, event3, event4};
    QVector<QString> interests{"Boredom", "Metal", "Dancing"};

    QVector<Event> narrowed = list.narrow(interests, testVector, 10);

    ASSERT_EQ(narrowed.size(), testVector.size());
}

TEST(EventChooser, noEvents){ //checks for empty list of events passed through
    EventChooser list;
    QVector<Event> testVector;
    QVector<QString> interests{"long walks on the beach", "martinis"};
    QVector<Event> narrowed = list.narrow(interests, testVector, 5);
    ASSERT_TRUE(narrowed.isEmpty());
}

TEST(EventChooser, notEnoughInterestMatches){ //checks for extra random events if not enough matches for 70/30 split
    EventChooser list;
    QVector<Event> testVector = {Event("e1"),Event("e2"),Event("e3"),Event("e4"),Event("e5"),Event("e6"),Event("e7"),Event("e8"),Event("e9"),Event("e10")};
    testVector[1].setCategory("bowling");
    testVector[2].setCategory("larping");
    testVector[3].setCategory("cricket");
    QVector<QString> interests{"bowling", "larping", "cricket"};
    QVector<Event> narrowed = list.narrow(interests, testVector, 8);
    ASSERT_EQ(narrowed.size(), 8);
}

TEST(EventChooser, notEnoughRandomEvents){ //checks for extra matches if not enough matches for 70/30 split
    EventChooser list;
    QVector<Event> testVector = {Event("e1"),Event("e2"),Event("e3"),Event("e4"),Event("e5"),Event("e6"),Event("e7"),Event("e8"),Event("e9"),Event("e10")};
    testVector[1].setCategory("Darius");
    testVector[2].setCategory("being short");
    testVector[3].setCategory("being lame");
    testVector[4].setCategory("Darius");
    testVector[5].setCategory("being short");
    testVector[6].setCategory("being short");
    testVector[7].setCategory("being lame");
    QVector<QString> interests{"Darius", "being short", "being lame"};
    QVector<Event> narrowed = list.narrow(interests, testVector, 8);
    ASSERT_EQ(narrowed.size(), 8);
}
