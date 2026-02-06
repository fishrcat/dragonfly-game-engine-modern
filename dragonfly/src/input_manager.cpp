// input_manager.cpp — Manager of player input (keyboard and mouse)

// Engine
#include "input_manager.h"

#include "display_manager.h"
#include "log_manager.h"

namespace df {

InputManager::InputManager() { setType("InputManager"); }

auto InputManager::startUp() -> StartupResult {
    LM.writeLog(LogLevel::INFO, "InputManager: starting up");

    if (!DM.isStarted()) {
        LM.writeLog(LogLevel::INFO,
                    "InputManager dependency DisplayManager not started");
        return StartupResult::Failed;
    }

    sf::RenderWindow* window = DM.getWindow();
    window->setKeyRepeatEnabled(false);

    return Manager::startUp();
}

void InputManager::shutDown() noexcept {
    LM.writeLog(LogLevel::INFO, "InputManager: shutting down");

    sf::RenderWindow* window = DM.getWindow();
    window->setKeyRepeatEnabled(false);

    Manager::shutDown();
}

}  // namespace df
