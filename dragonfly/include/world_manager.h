// world_manager.h — Manager of the game world

#pragma once

// Engine
#include <vector>

#include "manager.h"
#include "object.h"
#include "object_list.h"

#define GM df::GameManager::getInstance()

namespace df {

class GameManager : public Manager {
    public:
    static auto getInstance() -> GameManager &;  // Singleton
    ~GameManager() override;
    GameManager(const GameManager &) = delete;  // Disable copy
    auto operator=(const GameManager &) -> GameManager & =
                                               delete;  // Disable assignment

    [[nodiscard]] auto startUp() -> StartupResult override;
    void shutDown() noexcept override;

    auto insertObject(Object *p_obj) -> int;
    auto removeObject(Object *p_obj) -> int;

    auto getAllObjects() -> ObjectList;
    [[nodiscard]] auto objectsOfType(std::string type) -> ObjectList;

    void update();

    auto markForDelete(Object *p_obj) -> int;

    private:
    GameManager();

    ObjectList m_updates;
    ObjectList m_deletions;
};

}  // namespace df
