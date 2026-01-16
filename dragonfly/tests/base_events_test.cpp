// event_test.cpp — Unit tests for df::Event base class

#include <gtest/gtest.h>

#include "event.h"
#include "event_step.h"

using namespace df;

class TestEvent : public Event {
    public:
    using Event::setType;
};

TEST(EventTest, TypeIsSetCorrectly) {
    TestEvent event;

    event.setType("df::undefined");

    EXPECT_EQ(event.getType(), "df::undefined");
}

TEST(EventStepTest, StepEventInitsCorrectly) {
    const EventStep step_event(5);

    EXPECT_EQ(step_event.getType(), "df::step");
    EXPECT_EQ(step_event.getStepCount(), 5);
}
