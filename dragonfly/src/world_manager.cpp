// world_manager.h — Manager of the game world

// Engine
#include "world_manager.h"

#include "log_manager.h"
#include "object_list.h"

// System
#include <format>

namespace df {

WorldManager::WorldManager() { setType("WorldManager"); }

auto WorldManager::getInstance() -> WorldManager& {
    static WorldManager instance;
    return instance;
}

auto WorldManager::startUp() -> StartupResult {
    LM.writeLog(LogLevel::INFO, "WorldManager: starting up");

    return Manager::startUp();
}

void WorldManager::shutDown() noexcept {
    LM.writeLog(LogLevel::INFO, "WorldManager: shutting down");

    // Note: No manual destructor calls required here
    // When the WorldManager object is destroyed, the ObjectList m_updates which
    // owns all game Objects is also destroyed
    Manager::shutDown();
}

auto WorldManager::insertObject(Object* p_obj) -> int {
    m_updates.append(p_obj);
    LM.writeLog(
        LogLevel::DEBUG,
        std::format("WorldManager: added object {} to world", p_obj->getId()));
    return 0;
}

auto WorldManager::removeObject(const Object* p_obj) -> int {
    if (!m_updates.remove(p_obj)) {
        LM.writeLog(LogLevel::DEBUG,
                    std::format("WorldManager: Failed to remove object {} of "
                                "type {} from world",
                                p_obj->getId(), p_obj->getType()));
        return -1;
    }

    LM.writeLog(
        LogLevel::DEBUG,
        std::format("WorldManager: Removed object {} of type {} from world",
                    p_obj->getId(), p_obj->getType()));
    return 0;
}

// Usage: for (auto* obj : GM.objectsOfType("Enemy")) {obj->update();}
auto WorldManager::getAllObjects() const -> std::vector<Object*> {
    // Non-owning filtered view
    return m_updates.getAll();
}

// Usage: for (auto* obj : GM.objectsOfType("Enemy")) {obj->update();}
// TODO: Convert to template
auto WorldManager::objectsOfType(const std::string_view type) const
    -> std::vector<Object*> {
    // Non-owning filtered view
    return m_updates.getByType(type);
}

void WorldManager::update() { removeDeletions(); }

void WorldManager::draw() const {
    for (auto* obj : getAllObjects()) {
        obj->draw();
    }
}

auto WorldManager::markForDelete(Object* p_obj) -> int {
    m_deletions.push_back(p_obj);  // just store raw pointer
    return 0;
}

auto WorldManager::removeDeletions() -> int {
    int count = 0;

    for (const auto* obj : m_deletions) {
        LM.writeLog(
            LogLevel::DEBUG,
            std::format(
                "WorldManager: Removing object {} of type {} from world",
                obj->getId(), obj->getType()));
        if (!m_updates.remove(obj)) {
            LM.writeLog(
                LogLevel::WARN,
                std::format(
                    "WorldManager: Tried to remove object {} of type {} "
                    "but it was not in world",
                    obj->getId(), obj->getType()));
        }

        count++;
    }

    m_deletions.clear();  // reset for next frame
    return count;
}

}  // namespace df
