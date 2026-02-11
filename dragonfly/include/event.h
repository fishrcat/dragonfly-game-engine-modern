// event.h — Base class for engine events

#pragma once

// System
#include <string>

namespace df {

// TODO: Replace event type strings with templating
inline constexpr auto UNDEFINED_EVENT = "df::undefined";

class Event {
    public:
    Event() = default;
    virtual ~Event() = default;

    void setType(const std::string& type) { m_event_type = type; }
    auto getType() const noexcept -> std::string { return m_event_type; }

    private:
    std::string m_event_type{UNDEFINED_EVENT};
};

}  // namespace df
