// manager.cpp — Manager class for engine subsystems

#include "manager.h"

#include <world_manager.h>

namespace df {

auto Manager::getType() const noexcept -> std::string { return m_type; }

auto Manager::startUp() -> StartupResult {
    m_is_started = true;
    return StartupResult::Ok;
}

void Manager::shutDown() noexcept { m_is_started = false; }

auto Manager::isStarted() const -> bool { return m_is_started; }

auto Manager::onEvent(const Event* p_e) -> int {
    int count = 0;

    for (const auto objects = WM.getAllObjects();
         const auto& object : objects) {
        object->eventHandler(p_e);
    }
    count++;

    return count;
}

}  // namespace df
