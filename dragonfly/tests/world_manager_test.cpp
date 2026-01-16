// world_manager_test.cpp — single test for WorldManager singleton

#include "world_manager.h"

#include "gtest/gtest.h"

using namespace df;

class TestObject : public Object {
    public:
    explicit TestObject(const std::string &type) { setType(type); }
};

TEST(WorldManagerTest, SingletonBehavior) {
    WorldManager &gm = WorldManager::getInstance();

    // Insert objects
    gm.insertObject(new TestObject("A"));
    gm.insertObject(new TestObject("B"));
    gm.insertObject(new TestObject("C"));

    // Verify all objects
    const auto all = gm.getAllObjects();
    EXPECT_EQ(all.size(), 3);

    const auto vecC = gm.objectsOfType("C");
    EXPECT_EQ(vecC.size(), 1);
    EXPECT_EQ(vecC[0]->getType(), "C");

    // Remove some objects (A and B)
    gm.markForDelete(all[0]);
    gm.markForDelete(all[1]);
    EXPECT_EQ(gm.removeDeletions(), 2);

    // Verify remaining object
    const auto remaining = gm.getAllObjects();
    EXPECT_EQ(remaining.size(), 1);
    EXPECT_EQ(remaining[0]->getType(), "C");

    // Cleanup the last object
    gm.markForDelete(remaining[0]);
    EXPECT_EQ(gm.removeDeletions(), 1);
    EXPECT_TRUE(gm.getAllObjects().empty());
}
