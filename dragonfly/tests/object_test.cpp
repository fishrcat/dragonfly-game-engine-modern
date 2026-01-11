// object_test.cpp — Unit tests for df::Object

#include <gtest/gtest.h>

// Engine
#include "object.h"
#include "vector.h"

namespace df {

TEST(ObjectTest, ConstructorAssignsMonotonicIds) {
    const Object a;
    const Object b;

    EXPECT_EQ(b.getId(), a.getId() + 1);
}

TEST(ObjectTest, SetAndGetId) {
    Object obj;
    obj.setId(7);
    EXPECT_EQ(obj.getId(), 7);
}

TEST(ObjectTest, TypeDefaultsEmptyAndCanBeSet) {
    Object obj;

    EXPECT_TRUE(obj.getType().empty());

    obj.setType("player");
    EXPECT_EQ(obj.getType(), "player");
}

TEST(ObjectTest, PositionDefaultsAndCanBeSet) {
    Object obj;

    EXPECT_EQ(obj.getPosition(), Vector{});

    obj.setPosition(Vector(1, 2));
    EXPECT_EQ(obj.getPosition(), Vector(1, 2));
}

}  // namespace df
