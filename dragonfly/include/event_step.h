// event_step.h — Event of type df::step

#pragma once

// Engine
#include "event.h"

namespace df {
const std::string STEP_EVENT = "df::step";

class EventStep : public Event {
    public:
    EventStep();

    auto getStepCount() const -> int { return m_step_count; }

    private:
    static int s_step_global;
    int m_step_count{};
};
}  // namespace df
