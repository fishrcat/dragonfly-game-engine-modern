#include "manager.h"

namespace df {

auto Manager::getType() const -> std::string { return m_type; }

auto Manager::startUp() -> int {
    m_is_started = true;
    return 0;
}

void Manager::shutDown() { m_is_started = false; }

auto Manager::isStarted() const -> bool { return m_is_started; }

}  // namespace df
