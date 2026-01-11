// clock_test.cpp — Unit tests for df::Clock

#include "clock.h"

#include <gtest/gtest.h>

#include <chrono>
#include <regex>
#include <string>
#include <thread>

using namespace df;

class ClockTest : public ::testing::Test {
    protected:
    Clock clock;
};

TEST_F(ClockTest, SystemTimeStringFormat) {
    const std::string timeStr = df::Clock::getSystemTimeString();

    // Ensure it’s not empty
    EXPECT_FALSE(timeStr.empty());

    // Regex for YYYY-MM-DD HH:MM:SS.mmm
    const std::regex dateRegex(R"(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\.\d{3})");

    // Match the regex
    EXPECT_TRUE(std::regex_match(timeStr, dateRegex));
}

TEST_F(ClockTest, DeltaIncreases) {
    (void)clock.delta();  // Ensure we do reset the previous time with delta
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    const auto d2 = clock.delta();
    EXPECT_GT(d2.count(), 0);
}

TEST_F(ClockTest, SplitDoesNotReset) {
    (void)clock.split();  // Ensure we don't reset the prev time with split
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    const auto d2 = clock.split();
    // Should be larger than the first split (time has advanced)
    EXPECT_GT(d2.count(), 0);
}

TEST_F(ClockTest, FrameManagement) {
    const int startFrame = clock.getFrame();
    clock.setFrameStart();

    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    const auto remainder = clock.getFrameRemainder();
    EXPECT_GE(remainder.count(), 0);

    const int bumpedFrame = clock.bumpFrame();
    EXPECT_EQ(bumpedFrame, startFrame + 1);
    EXPECT_EQ(clock.getFrame(), startFrame + 1);
}
