#pragma once

#include "event.h"

namespace df {

inline constexpr const char* STEP_EVENT = "df::step";

class EventStep : public Event {
    public:
    EventStep() : m_step_count(s_step_global++) { setType(STEP_EVENT); }

    auto getStepCount() const -> int { return m_step_count; }

    private:
    inline static int s_step_global = 0;
    int m_step_count{0};
};

}  // namespace df
