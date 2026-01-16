// event_step.cpp — Event of type df::step

// Project
#include "event_step.h"

namespace df {

EventStep::EventStep(const int init_step_count)
    : m_step_count(init_step_count) {
    setType(STEP_EVENT);
}

}  // namespace df
