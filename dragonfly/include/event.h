// event.h — Base class for engine events

#pragma once

// System
#include <string>

namespace df {

const std::string UNDEFINED_EVENT = "df::undefined";

class Event {
    public:
    Event() = default;
    virtual ~Event() = default;

    void setType(const std::string& type) { m_event_type = type; }
    auto getType() const noexcept -> std::string;

    private:
    std::string m_event_type{UNDEFINED_EVENT};
};

}  // namespace df
