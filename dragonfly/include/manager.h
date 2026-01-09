// manager.h — Manager class for engine subsystems

#pragma once

#include <string>

namespace df {

class Manager {
    public:
    Manager() = default;
    virtual ~Manager() = default;

    auto getType() const -> std::string;

    virtual auto startUp() -> int;
    virtual void shutDown();

    auto isStarted() const -> bool;

    protected:
    void setType(const std::string& type) { m_type = type; }

    private:
    std::string m_type{"Manager"};
    bool m_is_started{false};
};
}  // namespace df
