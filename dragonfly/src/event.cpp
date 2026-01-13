// evnent.h — Base class for engine events

#include "event.h"

namespace df {

auto Event::getType() const noexcept -> std::string { return m_event_type; }

}  // namespace df
