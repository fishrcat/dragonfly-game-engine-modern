// vector.cpp — 2D vector object and math overrides

// Engine
#include "vector.h"

// System
#include <cmath>

namespace df {

auto Vector::magnitude() const noexcept -> float {
    return std::sqrt((x * x) + (y * y));
}

void Vector::normalize() noexcept {
    if (const float mag = magnitude(); mag > 0.F) {
        x /= mag;
        y /= mag;
    }
}

void Vector::scale(const float s) noexcept {
    x = x * s;
    y = y * s;
}

}  // namespace df
