// event_step.cpp — Event of type df::step

// Project
#include "event_step.h"

namespace df {

int EventStep::s_step_global = 0;

EventStep::EventStep() : m_step_count(s_step_global++) { setType(STEP_EVENT); }

}  // namespace df
