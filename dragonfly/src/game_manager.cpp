// game_manager.cpp — Manager of the game loop

// System
#include <thread>

// Engine
#include "config.h"
#include "display_manager.h"
#include "event_step.h"
#include "game_manager.h"
#include "input_manager.h"
#include "log_manager.h"
#include "world_manager.h"

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

    if (DM.startUp() != StartupResult::Ok) {
        return StartupResult::Failed;
    }

    if (IM.startUp() != StartupResult::Ok) {
        return StartupResult::Failed;
    }

    if (WM.startUp() != StartupResult::Ok) {
        return StartupResult::Failed;
    }

    return Manager::startUp();
}

void GameManager::shutDown() noexcept {
    LM.writeLog(LogLevel::INFO, "GameManager: shutting down");

    DM.shutDown();

    IM.shutDown();

    WM.shutDown();

    LM.shutDown();

    Manager::shutDown();
}

void GameManager::run() {
    LM.writeLog(LogLevel::DEBUG, "GameManager: run()");

#ifdef DEBUG_MODE
    Clock dev_clock;
#endif

    while (!m_game_over) {
        // Start the frame
        m_game_clock.bumpFrame();  // Increments frame ref num and sets frame
                                   // start time

        // Send the step event to all objects
        EventStep step;
        onEvent(&step);

        // Update the world state based on event resolutions and redraw
        WM.update();
        WM.draw();
        DM.swapBuffers();

        // Sleep the remainder of the frame time
        const Clock::duration_t remainder = m_game_clock.getFrameRemainder();
        LM.writeLog(LogLevel::TRACE,
                    std::format("GameManager: frame sleep {}", remainder));
        std::this_thread::sleep_for(remainder);

        // Debug time check
        LM.writeLog(
            LogLevel::TRACE,
            std::format("GameManager: Total frame time check {}",
                        m_game_clock.delta()));  // Resets m_previous_time
#ifdef DEBUG_MODE
        if (dev_clock.split() >= dev_runtime) {
            GM.setGameOver();
        }
#endif
    }
}

void GameManager::setGameOver(const bool game_over) { m_game_over = game_over; }

auto GameManager::getGameOver() const -> bool { return m_game_over; }

auto GameManager::getFrame() const -> int { return m_game_clock.getFrame(); }
}  // namespace df
