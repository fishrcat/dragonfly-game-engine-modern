// manager.h — Manager class for engine subsystems

#pragma once

// System
#include <cstdint>
#include <string>

namespace df {

enum class StartupResult : std::uint8_t {
    Ok,
    Failed,
};

class Manager {
    public:
    Manager() = default;
    virtual ~Manager() = default;

    auto getType() const noexcept -> std::string;

    [[nodiscard]] virtual auto startUp()
        -> StartupResult;  // Enforce startup checks
    virtual void shutDown() noexcept;

    auto isStarted() const -> bool;

    protected:
    void setType(const std::string& type) { m_type = type; }

    private:
    std::string m_type{"Manager"};
    bool m_is_started{false};
};
}  // namespace df
