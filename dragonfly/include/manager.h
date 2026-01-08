#pragma once

#include <string>

namespace df {

class Manager {
    private:
    std::string m_type;
    bool m_is_started{false};

    public:
    Manager() = default;
    virtual ~Manager() = default;

    auto getType() const -> std::string;

    virtual auto startUp() -> int;
    virtual void shutDown();

    auto isStarted() const -> bool;

    protected:
    void setType(const std::string& type) { m_type = type; }
};

}  // namespace df
