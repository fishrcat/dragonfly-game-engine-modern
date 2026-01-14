// event_step.h — Event of type df::step

#pragma once

// Engine
#include "event.h"

namespace df {
const std::string STEP_EVENT = "df::step";

class EventStep : public Event {
    public:
    EventStep() : EventStep(0){};
    explicit EventStep(int init_step_count);

    void setStepCount(const int new_step_count) {
        m_step_count = new_step_count;
    };
    auto getStepCount() const -> int { return m_step_count; };

    private:
    int m_step_count{};
};
}  // namespace df
