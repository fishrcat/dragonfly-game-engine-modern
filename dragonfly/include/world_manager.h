// world_manager.h — Manager of the game world

#pragma once

// Engine
#include <vector>

#include "manager.h"
#include "object.h"
#include "object_list.h"

#define WM df::WorldManager::getInstance()

namespace df {

class WorldManager : public Manager {
    public:
    static auto getInstance() -> WorldManager &;  // Singleton
    ~WorldManager() override = default;
    WorldManager(const WorldManager &) = delete;  // Disable copy
    auto operator=(const WorldManager &) -> WorldManager & =
                                                delete;  // Disable assignment

    [[nodiscard]] auto startUp() -> StartupResult override;
    void shutDown() noexcept override;

    auto insertObject(Object *p_obj) -> int;
    auto removeObject(const Object *p_obj) -> int;

    auto getAllObjects() const -> std::vector<Object *>;
    [[nodiscard]] auto objectsOfType(std::string_view type) const
        -> std::vector<Object *>;

    void update();
    void draw() const;

    auto markForDelete(Object *p_obj) -> int;
    auto removeDeletions() -> int;

    private:
    WorldManager();

    ObjectList m_updates;
    std::vector<Object *> m_deletions;
};

}  // namespace df
