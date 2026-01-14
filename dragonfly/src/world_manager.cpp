// world_manager.h — Manager of the game world

// Engine
#include "world_manager.h"

#include "log_manager.h"
#include "object_list.h"

namespace df {

GameManager::GameManager() { setType("GameManager"); }

auto GameManager::getInstance() -> GameManager& {
    static GameManager instance;
    return instance;
}

auto GameManager::startUp() -> StartupResult {
    LM.writeLog(LogLevel::INFO, "WorldManager: starting up");

    return Manager::startUp();
}

void GameManager::shutDown() noexcept {
    LM.writeLog(LogLevel::INFO, "WorldManager: shutting down");

    // Note: No manual destructor calls required here
    // When the GameManager object is destroyed, the ObjectList m_updates which
    // owns all game Objects is also destroyed
    Manager::shutDown();
}

}  // namespace df
