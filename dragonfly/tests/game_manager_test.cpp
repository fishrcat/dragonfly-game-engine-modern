// Project
#include "game_manager.h"

#include "clock.h"

// System
#include <gtest/gtest.h>

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

namespace df {

TEST(GameManagerTest, RunsAtApproximately30FPS) {
    ASSERT_EQ(GM.startUp(), 0);

    constexpr int kTargetFrames = 60;
    constexpr double kExpectedFPS = 30.0;
    constexpr double kToleranceFPS = 2.0;

    auto start_time = std::chrono::steady_clock::now();

    // Run game loop in background
    std::thread game_thread([&]() { GM.run(); });

    // Wait until frames elapsed
    while (GM.getFrame() < kTargetFrames) {
        std::this_thread::sleep_for(1ms);
    }

    auto end_time = std::chrono::steady_clock::now();

    // Stop the loop
    GM.setGameOver(true);
    game_thread.join();

    auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(
        end_time - start_time);

    const double actual_fps =
        static_cast<double>(kTargetFrames) / elapsed.count();

    EXPECT_NEAR(actual_fps, kExpectedFPS, kToleranceFPS)
        << "Actual FPS: " << actual_fps;

    GM.shutDown();
}

}  // namespace df
