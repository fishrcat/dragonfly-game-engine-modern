// clock.h — System time interface with frame-specific references

#pragma once

// System
#include <chrono>

namespace df {

class Clock {
    public:
    using duration_t = std::chrono::milliseconds;
    using point_t = std::chrono::steady_clock::time_point;

    Clock();

    // Readable time (system_time)
    static auto getSystemTimeString() -> std::string;

    // Clock time (steady_time)
    auto delta() -> duration_t;
    auto split() const -> duration_t;
    auto getPreviousTime() const -> point_t;

    // Frame reference time
    void setFrameStart();
    auto getFrameRemainder() const -> duration_t;

    auto getFrame() const -> int;
    auto bumpFrame() -> int;

    private:
    using clock_t = std::chrono::steady_clock;
    clock_t::time_point m_previous_time;
    clock_t::time_point m_frame_start;
    int m_frame{0};
};
}  // namespace df
