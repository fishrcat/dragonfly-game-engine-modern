// clock.h — System time interface with frame-specific references

// Project
#include "clock.h"

// System
#include <config.h>

#include <chrono>

namespace df {

Clock::Clock() : m_previous_time(clock_t::now()) {}

// Human-readable time for logging
auto Clock::getSystemTimeString() -> std::string {
    using namespace std::chrono;

    const auto now = system_clock::now();
    const auto ttime = system_clock::to_time_t(now);
    std::tm tm{};
    localtime_r(&ttime, &tm);
    const auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << '.' << std::setw(3)
        << std::setfill('0') << ms.count();

    return oss.str();
}

// Clock time
auto Clock::delta() -> duration_t {
    const auto current = clock_t::now();
    const auto elapsed =
        std::chrono::duration_cast<duration_t>(current - m_previous_time);

    m_previous_time = current;
    return elapsed;
}

auto Clock::split() const -> duration_t {
    return std::chrono::duration_cast<duration_t>(clock_t::now() -
                                                  m_previous_time);
}

auto Clock::getPreviousTime() const -> point_t { return m_previous_time; }

// Frame reference time
void Clock::setFrameStart() { m_frame_start = clock_t::now(); }

auto Clock::getFrameRemainder() const -> duration_t {
    const auto now = clock_t::now();
    const auto frame_end = m_frame_start + TARGET_TIME;

    // TODO: Research handling for frame target_time overflow
    if (frame_end <= now) {
        return duration_t::zero();
    }

    return std::chrono::duration_cast<duration_t>(frame_end - now);
}

auto Clock::getFrame() const -> int { return m_frame; }

auto Clock::bumpFrame() -> int {
    m_frame++;
    return m_frame;
}

}  // namespace df
