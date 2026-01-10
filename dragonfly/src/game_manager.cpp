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

auto GameManager::startUp() -> int {
    LM.startUp();
    LM.setClock(m_game_clock);

    m_game_clock.bumpFrame();

    return Manager::startUp();
}

void GameManager::shutDown() {
    LM.shutDown();
    setGameOver();
}

void GameManager::run() {
    LM.writeLog(df::LogLevel::DEBUG, "GameManager: run()");
    while (!m_game_over) {
        // Start the frame
        m_game_clock.bumpFrame();  // Increments frame ref num and sets frame
                                   // start time
        LM.writeLog(df::LogLevel::DEBUG,
                    std::format("GameManager: start frame {}",
                                m_game_clock.getFrame()));

        // Debug time check
        LM.writeLog(df::LogLevel::DEBUG,
                    std::format("GameManager: start frame time check {}",
                                m_game_clock.split()));

        // Game loop here
        std::this_thread::sleep_for(std::chrono::milliseconds(15));

        // Sleep the remainder of the frame time
        const Clock::duration_t remainder = m_game_clock.getFrameRemainder();
        LM.writeLog(df::LogLevel::DEBUG,
                    std::format("GameManager: frame sleep {}", remainder));
        std::this_thread::sleep_for(remainder);

        // Debug time check
        LM.writeLog(
            df::LogLevel::DEBUG,
            std::format("GameManager: end frame time check {}",
                        m_game_clock.delta()));  // Resets m_previous_time
    }
}

void GameManager::setGameOver(bool game_over) { m_game_over = game_over; }

auto GameManager::getGameOver() const -> bool { return m_game_over; }

auto GameManager::getFrame() const -> int { return m_game_clock.getFrame(); }
}  // namespace df
