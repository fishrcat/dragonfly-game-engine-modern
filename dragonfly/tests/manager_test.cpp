// manager_test.cpp — Unit tests for df::Manager

#include "manager.h"

#include <gtest/gtest.h>

class TestManager : public df::Manager {
    public:
    using Manager::setType;
};

class ManagerTest : public ::testing::Test {
    protected:
    TestManager manager;
};

TEST_F(ManagerTest, StartUpAndShutDown) {
    EXPECT_FALSE(manager.isStarted());

    const df::StartupResult result = manager.startUp();
    EXPECT_EQ(result, df::StartupResult::Ok);
    EXPECT_TRUE(manager.isStarted());

    manager.shutDown();
    EXPECT_FALSE(manager.isStarted());
}

TEST_F(ManagerTest, TypeIsSetCorrectly) {
    manager.setType("Manager");

    EXPECT_EQ(manager.getType(), "Manager");
}
