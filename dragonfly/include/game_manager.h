// game_manager.cpp — Manager of the game loop

#pragma once

// Project
#include "clock.h"
#include "manager.h"

// System

#define GM df::GameManager::getInstance()

namespace df {

class GameManager : public Manager {
    private:
    GameManager();

    bool m_game_over{false};
    Clock m_game_clock;

    public:
    GameManager(const GameManager&) = delete;  // Disable copy
    auto operator=(const GameManager&) -> GameManager& =
                                              delete;  // Disable assignment
    static auto getInstance() -> GameManager&;         // Singleton

    auto startUp() -> int override;
    void shutDown() override;

    void run();

    void setGameOver(bool game_over = true);
    auto getGameOver() const -> bool;

    auto getFrame() const -> int;
};
}  // namespace df
