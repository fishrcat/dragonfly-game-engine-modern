// game_manager.cpp — Manager of the game loop

// Project
#include "game_manager.h"

#include <thread>

#include "config.h"
#include "log_manager.h"

namespace df {

GameManager::GameManager() { setType("GameManager"); }

auto GameManager::getInstance() -> GameManager& {
    static GameManager instance;
    return instance;
}

auto GameManager::startUp() -> StartupResult {
    if (LM.startUp() != StartupResult::Ok) {
        return StartupResult::Failed;
    }
    LM.setClock(m_game_clock);
    LM.writeLog(LogLevel::INFO, "GameManager: starting up");

    m_game_clock.bumpFrame();

    return Manager::startUp();
}

void GameManager::shutDown() noexcept {
    LM.writeLog(LogLevel::INFO, "GameManager: shutting down");
    LM.shutDown();

    Manager::shutDown();
}

void GameManager::run() {
    LM.writeLog(LogLevel::DEBUG, "GameManager: run()");

    Clock dev_clock;  // DEV WRAPPER - TODO: Rem when there is a way to shut
                      // down the game loop
    const auto dev_runtime = Clock::duration_t(60);

    while (!m_game_over) {
        // Start the frame
        m_game_clock.bumpFrame();  // Increments frame ref num and sets frame
                                   // start time

        // Game loop here
        std::this_thread::sleep_for(std::chrono::milliseconds(15));

        // Sleep the remainder of the frame time
        const Clock::duration_t remainder = m_game_clock.getFrameRemainder();
        LM.writeLog(LogLevel::DEBUG,
                    std::format("GameManager: frame sleep {}", remainder));
        std::this_thread::sleep_for(remainder);

        // Debug time check
        LM.writeLog(
            LogLevel::DEBUG,
            std::format("GameManager: Total frame time check {}",
                        m_game_clock.delta()));  // Resets m_previous_time

        if (dev_clock.split() >= dev_runtime) {
            GM.setGameOver();
        }
    }
}

void GameManager::setGameOver(bool game_over) { m_game_over = game_over; }

auto GameManager::getGameOver() const -> bool { return m_game_over; }

auto GameManager::getFrame() const -> int { return m_game_clock.getFrame(); }
}  // namespace df
